#include "AudioPlayer.h"
//#include "../../Assimil8or/PresetManagerProperties.h"
//#include "../Bank/BankManagerProperties.h"
#include "../../Utility/DebugLog.h"
#include "../../Utility/PersistentRootProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

#define LOG_AUDIO_PLAYER 0
#if LOG_AUDIO_PLAYER
#define LogAudioPlayer(text) DebugLog ("AudioPlayer", text);
#else
#define LogAudioPlayer(text) ;
#endif

void AudioPlayer::init (juce::ValueTree rootPropertiesVT)
{
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no);

    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::client, AppProperties::EnableCallbacks::yes);

    audioSettingsProperties.wrap (persistentRootProperties.getValueTree (), AudioSettingsProperties::WrapperType::owner, AudioSettingsProperties::EnableCallbacks::yes);
    audioSettingsProperties.onConfigChange = [this] (juce::String config)
    {
        // TODO - do we need this callback?
        //configureAudioDevice (deviceName);
    };

    audioPlayerProperties.wrap (runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::owner, AudioPlayerProperties::EnableCallbacks::yes);
    audioPlayerProperties.onShowConfigDialog = [this] ()
    {
        showConfigDialog ();
    };
    audioPlayerProperties.onPlayStateChange = [this] (AudioPlayerProperties::PlayState newPlayState)
    {
        LogAudioPlayer ("init: audioPlayerProperties.onPlayStateChange");
        handlePlayState (newPlayState);
    };
    audioPlayerProperties.onPlayModeChange = [this] (AudioPlayerProperties::PlayMode newPlayMode)
    {
        LogAudioPlayer ("init: audioPlayerProperties.onPlayStateChange");
        handlePlayMode (newPlayMode);
    };
    // Clients call this to setup the sample source
    audioPlayerProperties.onSampleSourceChanged = [this] (juce::String filename)
    {
        LogAudioPlayer ("init: audioPlayerProperties.onSampleSourceChanged");
        initFromFile (filename);
    };
    audioDeviceManager.addChangeListener (this);
    configureAudioDevice (audioSettingsProperties.getConfig ());
}

void AudioPlayer::initFromFile (juce::String filename)
{
    LogAudioPlayer ("initFromFile");
    sampleFile = juce::File (appProperties.getMostRecentFolder ()).getChildFile (filename);
    prepareSampleForPlayback ();
}

void AudioPlayer::prepareSampleForPlayback ()
{
    jassert (playState == AudioPlayerProperties::PlayState::stop);
    if (sampleFile.existsAsFile())
    {
        LogAudioPlayer ("prepareSampleForPlayback: sample is ready");
        auto inputStream { sampleFile.createInputStream () };
        juce::WavAudioFormat wavAudioFormat;
        if (std::unique_ptr<juce::AudioFormatReader> sampleFileReader { wavAudioFormat.createReaderFor (inputStream.get (), true) }; sampleFileReader != nullptr)
        {
            inputStream.release ();

            // convert mono file to stereo for stereo output
            juce::AudioBuffer<float> sampleAudioBuffer;
            sampleAudioBuffer.setSize (1, static_cast<int> (sampleFileReader->lengthInSamples), false, true, false);
            sampleFileReader->read (&sampleAudioBuffer, 0, static_cast<int> (sampleFileReader->lengthInSamples), 0, true, false);
            std::unique_ptr <juce::MemoryAudioSource> readerSource { std::make_unique<juce::MemoryAudioSource> (sampleAudioBuffer, false, false) };
            std::unique_ptr<MonoToStereoAudioSource> monoToStereoAudioSource { std::make_unique<MonoToStereoAudioSource> (readerSource.get (), false) };
            std::unique_ptr<juce::ResamplingAudioSource> resamplingAudioSource { std::make_unique<juce::ResamplingAudioSource> (monoToStereoAudioSource.get (), false, 2) };
            sampleRateRatio = sampleRate / sampleFileReader->sampleRate;
            resamplingAudioSource->setResamplingRatio (sampleFileReader->sampleRate / sampleRate);
            resamplingAudioSource->prepareToPlay (blockSize, sampleRate);
            sampleBuffer = std::make_unique<juce::AudioBuffer<float>> (2, static_cast<int> (sampleFileReader->lengthInSamples * sampleRate / sampleFileReader->sampleRate));
            resamplingAudioSource->getNextAudioBlock (juce::AudioSourceChannelInfo (*sampleBuffer.get ()));
            curSampleOffset = 0;

            sampleStart = static_cast<int> (0 * sampleRateRatio);
            sampleLength = static_cast<int> (sampleFileReader->lengthInSamples * sampleRateRatio);
        }
    }
    else
    {
        LogAudioPlayer ("prepareSampleForPlayback: sample file does NOT exist");
        sampleBuffer = std::make_unique<juce::AudioBuffer<float>> (2, 0);
        curSampleOffset = 0;
        sampleStart = 0;
        sampleLength = 0;
    }
}

void AudioPlayer::shutdownAudio ()
{
    audioSourcePlayer.setSource (nullptr);
    audioDeviceManager.removeAudioCallback (&audioSourcePlayer);
    audioDeviceManager.closeAudioDevice ();
}

void AudioPlayer::configureAudioDevice (juce::String config)
{
    juce::String audioConfigError;
    if (config.isEmpty ())
    {
        audioConfigError = audioDeviceManager.initialise (0, 2, nullptr, true);
    }
    else
    {
        auto audioConfigXml { juce::XmlDocument::parse (config) };
        audioConfigError = audioDeviceManager.initialise (0, 2, audioConfigXml.get (), true, {}, nullptr);
    }

    if (! audioConfigError.isEmpty ())
    {
        jassertfalse;
    }

    audioDeviceManager.addAudioCallback (&audioSourcePlayer);
    audioSourcePlayer.setSource (this);
}

void AudioPlayer::handlePlayMode (AudioPlayerProperties::PlayMode newPlayMode)
{
    juce::ScopedLock sl (dataCS);
    playMode = newPlayMode;
}

void AudioPlayer::handlePlayState (AudioPlayerProperties::PlayState newPlayState)
{
    juce::ScopedLock sl (dataCS);
    if (newPlayState == AudioPlayerProperties::PlayState::stop)
    {
        LogAudioPlayer ("AudioPlayer::handlePlayState: stop");
    }
    else if (newPlayState == AudioPlayerProperties::PlayState::play)
    {
        LogAudioPlayer ("AudioPlayer::handlePlayState: play");
        curSampleOffset = sampleStart;
    }
    playState = newPlayState;
}

void AudioPlayer::showConfigDialog ()
{
    juce::DialogWindow::LaunchOptions o;
    o.escapeKeyTriggersCloseButton = true;
    o.dialogBackgroundColour = juce::Colours::grey;
    o.dialogTitle = "AUDIO SETTTINGS";
    audioSetupComp.setBounds (0, 0, 400, 600);
    o.content.set (&audioSetupComp, false);
    o.launchAsync ();
}

void AudioPlayer::prepareToPlay (int samplesPerBlockExpected, double newSampleRate)
{
    LogAudioPlayer ("prepareToPlay");
    sampleRate = newSampleRate;
    blockSize = samplesPerBlockExpected;
    prepareSampleForPlayback ();
}

void AudioPlayer::releaseResources ()
{
}

void AudioPlayer::changeListenerCallback (juce::ChangeBroadcaster*)
{
    LogAudioPlayer ("audio device settings changed");
    auto audioDeviceSettings { audioDeviceManager.createStateXml () };
    if (audioDeviceSettings != nullptr)
    {
        auto xmlString { audioDeviceSettings->toString () };
        audioSettingsProperties.setConfig (xmlString, false);
    }
}

void AudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion ();
    // fill buffer with data

    if (playState == AudioPlayerProperties::PlayState::stop)
        return;

    const auto numOutputSamples { bufferToFill.numSamples };
    auto& outputBuffer { *bufferToFill.buffer };
    const auto channels { juce::jmin (outputBuffer.getNumChannels (), sampleBuffer->getNumChannels ()) };

    auto originalSampleOffset { 0 };
    auto cachedSampleLength { 0 };
    auto cachedSampleStart { 0 };
    auto cachedLocalSampleOffset { 0 };
    auto chachedPlayMode { AudioPlayerProperties::PlayMode::once };
    {
        // NOTE: I am using a lock in the audio callback ONLY BECAUSE the audio play back is a simple audition feature, not recording or performance playback
        juce::ScopedLock sl (dataCS);
        jassert (curSampleOffset >= sampleStart);
        //jassert (curSampleOffset < sampleStart + sampleLength);
        originalSampleOffset =  curSampleOffset; // should be >= sampleStart and < sampleStart + sampleLength
        cachedSampleLength = sampleLength;
        cachedSampleStart = sampleStart;
        chachedPlayMode = playMode;
        cachedLocalSampleOffset = curSampleOffset - sampleStart;
        LogAudioPlayer ("AudioPlayer::getNextAudioBlock - cachedSampleStart: " + juce::String (cachedSampleStart) + ", chachedSampleLength: " + juce::String (cachedSampleLength) +
                        ", curSampleOffset: " + juce::String (curSampleOffset) + ", cachedLocalSampleOffset: " + juce::String (cachedLocalSampleOffset));
    }

    if (cachedSampleLength <= 0)
    {
        playState = AudioPlayerProperties::PlayState::stop;
        return;
    }

    auto numSamplesToCopy { 0 };
    auto outputBufferWritePos { 0 };
    while (cachedSampleLength > 0 && outputBufferWritePos < numOutputSamples)
    {
        numSamplesToCopy = juce::jmin (numOutputSamples - outputBufferWritePos, cachedSampleLength - cachedLocalSampleOffset);
        LogAudioPlayer ("AudioPlayer::getNextAudioBlock - numSamplesToCopy: " + juce::String (numSamplesToCopy));
        jassert (numSamplesToCopy >= 0);

        // copy data from sample buffer to output buffer, this may, or may not, fill the entire output buffer
        auto ch { 0 };
        for (; ch < channels; ++ch)
            outputBuffer.copyFrom (ch, bufferToFill.startSample + outputBufferWritePos, *sampleBuffer, ch, cachedSampleStart + cachedLocalSampleOffset, numSamplesToCopy);

        // clear any unused channels
        for (; ch < outputBuffer.getNumChannels (); ++ch)
            outputBuffer.clear (ch, bufferToFill.startSample + outputBufferWritePos, numSamplesToCopy);

        outputBufferWritePos += numSamplesToCopy;
        cachedLocalSampleOffset += numSamplesToCopy;
        if (chachedPlayMode == AudioPlayerProperties::PlayMode::loop)
        {
            if (cachedLocalSampleOffset >= cachedSampleLength)
                cachedLocalSampleOffset = 0;
        }
        else
        {
            LogAudioPlayer ("AudioPlayer::getNextAudioBlock - outputBufferWritePos : " + juce::String (outputBufferWritePos) + ", numOutputSamples: " + juce::String (numOutputSamples));
            if (outputBufferWritePos < numOutputSamples)
            {
                outputBuffer.clear (bufferToFill.startSample + outputBufferWritePos, numOutputSamples - outputBufferWritePos);
                audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, true);
                break;
            }
        }
    }
    {
        // NOTE: I am using a lock in the audio callback ONLY BECAUSE the audio play back is a simple audition feature, not recording or performance playback
        juce::ScopedLock sl (dataCS);
        if (originalSampleOffset == curSampleOffset && cachedSampleStart == sampleStart && cachedSampleLength == sampleLength) // if the offset has not changed externally
        {
            curSampleOffset = cachedSampleStart + cachedLocalSampleOffset;
            LogAudioPlayer ("AudioPlayer::getNextAudioBlock setting new curSampleOffset: " + juce::String (curSampleOffset) + ", cachedSampleStart: " + juce::String (cachedSampleStart) + ", chachedSampleLength: " + juce::String (cachedSampleLength) +
                            ", cachedLocalSampleOffset: " + juce::String (cachedLocalSampleOffset));
        }
        else
        {
            LogAudioPlayer ("AudioPlayer::getNextAudioBlock - curSampleOffset: " + juce::String (cachedSampleStart) + " != originalSampleOffset: " + juce::String (originalSampleOffset));
        }
    }
}
