#include "SampleBankComponent.h"
#include "../../Clutch/BankProperties.h"
#include "../../Clutch/SamplePairProperties.h"
#include "../../SRC/libsamplerate-0.1.9/src/samplerate.h"
#include "../../Utility/PersistentRootProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

SampleBankComponent::SampleBankComponent ()
{
    addAndMakeVisible(bankName);
    for (auto hiHatSampleIndex { 0 }; hiHatSampleIndex < hiHatSampleInfoList.size (); ++hiHatSampleIndex)
    {
        auto& hiHatSampleInfo { hiHatSampleInfoList [hiHatSampleIndex] };

        auto handleMouseClickOnSample = [this, hiHatSampleIndex, &hiHatSampleInfo] (SampleProperties::SampleType sampleType, bool isPopupMenu)
        {
            const auto sampleLabel { sampleType == SampleProperties::SampleType::open ? &hiHatSampleInfo.openedNameLabel : &hiHatSampleInfo.closedNameLabel };
            const auto sampleIndexString { juce::String (hiHatSampleIndex + 1).paddedLeft ('0', 2) };
            if (isPopupMenu)
            {
                auto* popupMenuLnF { new juce::LookAndFeel_V4 };
                popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));
                juce::PopupMenu pm;
                pm.setLookAndFeel (popupMenuLnF);
                pm.addSectionHeader ((sampleType == SampleProperties::SampleType::open ? "Opened " : "Closed ") + sampleIndexString);
                pm.addSeparator ();
                pm.addItem ("Delete", true, false, [this] ()
                            {
                            });
                pm.addItem ("Swap", true, false, [this] ()
                            {
                            });
                pm.addItem ("Revert", true, false, [this] ()
                            {
                            });
                pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
            }
            else
            {
                if (auditioningSampleLabelComponent != nullptr)
                    auditioningSampleLabelComponent->enablePlayBlink (false);
                auditioningSampleLabelComponent = sampleLabel;
                sampleLabel->enablePlayBlink (true);
                startTimer (16);

                audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
                audioPlayerProperties.setSampleSource (getBankAndFileName (hiHatSampleIndex, sampleType), false);
                audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::play, false);
            }
        };
        
        ////////////////////////////////////////////
        // add bank name (aka WHITE, RED, etc) label
        hiHatSampleInfo.name.setJustificationType (juce::Justification::centredRight);
        hiHatSampleInfo.name.setText (juce::String (hiHatSampleIndex + 1), juce::NotificationType::dontSendNotification);
        addAndMakeVisible (hiHatSampleInfo.name);

        //////////////////////////
        // add opened sample label
        hiHatSampleInfo.openedNameLabel.setJustificationType (juce::Justification::centred);
        hiHatSampleInfo.openedNameLabel.setText ("Opened", juce::NotificationType::dontSendNotification);
        hiHatSampleInfo.openedNameLabel.onFilesSelected = [this, hiHatSampleIndex] (juce::StringArray files)
        {
            jassert (files.size () == 1);
            audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
            copySampleFile (juce::File (files[0]), hiHatSampleIndex, HiHatState::opened);
        };
        hiHatSampleInfo.openedNameLabel.onMouseUp = [this, handleMouseClickOnSample] ([[maybe_unused]] const juce::MouseEvent& mouseEvent)
        {
            handleMouseClickOnSample (SampleProperties::SampleType::open, mouseEvent.mods.isPopupMenu ());
        };
        addAndMakeVisible (hiHatSampleInfo.openedNameLabel);

        //////////////////////////
        // add closed sample label
        hiHatSampleInfo.closedNameLabel.setJustificationType (juce::Justification::centred);
        hiHatSampleInfo.closedNameLabel.setText ("Closed", juce::NotificationType::dontSendNotification);
        hiHatSampleInfo.closedNameLabel.onFilesSelected = [this, hiHatSampleIndex] (juce::StringArray files)
        {
            jassert (files.size () == 1);
            audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
            copySampleFile (juce::File (files [0]), hiHatSampleIndex, HiHatState::closed);
        };
        hiHatSampleInfo.closedNameLabel.onMouseUp = [this, handleMouseClickOnSample] ([[maybe_unused]] const juce::MouseEvent& mouseEvent)
        {
            handleMouseClickOnSample (SampleProperties::SampleType::closed, mouseEvent.mods.isPopupMenu ());
        };
        addAndMakeVisible (hiHatSampleInfo.closedNameLabel);
    }
}

SampleBankComponent::~SampleBankComponent ()
{
}

void SampleBankComponent::init (juce::ValueTree rootPropertiesVT, juce::ValueTree bankPropertiesVT)
{
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::client, AppProperties::EnableCallbacks::no);

    RuntimeRootProperties runtimeRootProperties { rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no };
    audioPlayerProperties.wrap (runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::client, AudioPlayerProperties::EnableCallbacks::no);
    
    bankProperties.wrap (bankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::yes);
    setBankName (bankProperties.getName ());
    bankProperties.forEachSamplePair ([this] (juce::ValueTree samplePairVT, int samplePairIndex)
    {
        SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
        HiHatSampleInfo& hiHatSampleInfo { hiHatSampleInfoList [samplePairIndex] };

        hiHatSampleInfo.openSampleProperties.wrap (samplePairProperties.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::yes);
        hiHatSampleInfo.openSampleProperties.onExistsChange = [this, &hiHatSampleInfo] (bool exists)
        {
            hiHatSampleInfo.openedNameLabel.setFileExistState (exists);
        };

        hiHatSampleInfo.closedSampleProperties.wrap (samplePairProperties.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::yes);
        hiHatSampleInfo.closedSampleProperties.onExistsChange = [this, &hiHatSampleInfo] (bool exists)
        {
            hiHatSampleInfo.closedNameLabel.setFileExistState (exists);
        };

        hiHatSampleInfo.openedNameLabel.setFileExistState (hiHatSampleInfo.openSampleProperties.getExists ());
        hiHatSampleInfo.closedNameLabel.setFileExistState (hiHatSampleInfo.closedSampleProperties.getExists ());
        return true;
    });
}

juce::String SampleBankComponent::getBankAndFileNameWithoutExtension (int hiHatSampleIndex, SampleProperties::SampleType sampleType)
{
    return bankName.getText () + juce::File::getSeparatorString () + juce::String (hiHatSampleIndex + 1).paddedLeft ('0', 2) + (sampleType == SampleProperties::SampleType::open ? "OH" : "CH");
}

juce::String SampleBankComponent::getBankAndFileName (int hiHatSampleIndex, SampleProperties::SampleType sampleType)
{
    const auto bankAndFileNameWithouExtension { getBankAndFileNameWithoutExtension (hiHatSampleIndex, sampleType) };
    auto fullFileNameWithoutExtension { juce::File (appProperties.getMostRecentFolder ()).getChildFile (bankAndFileNameWithouExtension) };
    if (fullFileNameWithoutExtension.withFileExtension ("._wav").existsAsFile ())
        return bankAndFileNameWithouExtension + "._wav";
    return bankAndFileNameWithouExtension + ".wav";
}

void SampleBankComponent::sampleConvert (juce::AudioFormatReader* reader, juce::AudioBuffer<float>& outputBuffer)
{
    juce::AudioBuffer<float> inputBuffer;
    const auto numChannels { reader->numChannels };
    const auto numSamples { reader->lengthInSamples };
    inputBuffer.setSize (numChannels, static_cast<int> (numSamples), false, true, false);
    reader->read (&inputBuffer, 0, static_cast<int> (numSamples), 0, true, true);

    const double ratio { 44100. / reader->sampleRate };
    const int outputNumSamples { static_cast<int> (numSamples * ratio) };
    outputBuffer.setSize (numChannels, outputNumSamples, false, true, false);
    SRC_STATE* srcState = src_new (SRC_SINC_BEST_QUALITY, numChannels, nullptr);
    if (srcState == nullptr)
    {
        // TODO - handle error
        jassertfalse;
    }

    SRC_DATA srcData;
    srcData.data_in = inputBuffer.getReadPointer (0);
    srcData.input_frames = static_cast<int> (numSamples);
    srcData.data_out = outputBuffer.getWritePointer (0);
    srcData.output_frames = outputNumSamples;
    srcData.src_ratio = ratio;
    srcData.end_of_input = 0;

    int error { src_process (srcState, &srcData) };
    src_delete (srcState);

    if (error != 0)
    {
        // TODO - handle error
        jassertfalse;
    }
}
void SampleBankComponent::copySampleFile (juce::File sourceFile, int hiHatSampleIndex, HiHatState hiHatState)
{
    // TODO - move to centralized place
    juce::AudioFormatManager audioFormatManager;
    audioFormatManager.registerBasicFormats ();
    auto reader { std::unique_ptr<juce::AudioFormatReader> (audioFormatManager.createReaderFor (sourceFile)) };
    if (reader == nullptr)
    {
        jassertfalse; // Failed to create reader for source file
        // TODO : reflect error up to UI
        return;
    }

    juce::String destinationFileName { juce::String (hiHatSampleIndex + 1).paddedLeft ('0', 2) + (hiHatState == HiHatState::closed ? "C" : "O") + "H._wav" };
    juce::File bankFolder { banksRootFolder.getChildFile (bankName.getText ()) };
    if (! bankFolder.exists ())
    {
        if (auto createdBankFolder { bankFolder.createDirectory () }; createdBankFolder.failed ())
        {
            // TODO reflect this error up to the UI
            jassertfalse;
            return;
        }

    }
    if (! bankFolder.isDirectory ())
    {
        // TODO reflect this issue to the UI
        jassertfalse;
        return;
    }

    juce::File destFile { bankFolder.getChildFile (destinationFileName) };
    if (reader->getFormatName () == "WAV file" && reader->numChannels == 1 && reader->bitsPerSample == 16 && (reader->sampleRate == 44100 || reader->sampleRate == 48000))
    {
        sourceFile.copyFileTo (destFile);
    }
    else
    {
        // Source file does not meet required format
        auto destinationFileStream { std::make_unique<juce::FileOutputStream> (destFile) };
        destinationFileStream->setPosition (0);
        destinationFileStream->truncate ();

        juce::WavAudioFormat wavAudioFormat;
        // TODO : do I need to do a proper L/R mix for stereo input?
        if (std::unique_ptr<juce::AudioFormatWriter> writer { wavAudioFormat.createWriterFor (destinationFileStream.get (),
                                                                48000, 1, 16, {}, 0) }; writer != nullptr)
        {
            // audioFormatWriter will delete the file stream when done
            destinationFileStream.release ();

            if (reader->bitsPerSample == 48000)
            {
                // copy the whole thing
                // TODO - two things
                //   a) this needs to be done in a thread
                //   b) we should locally read into a buffer and then write that, so we can display progress if needed
                if (writer->writeFromAudioReader (*reader.get (), 0, -1) == true)
                {
                    // close the writer and reader, so that we can manipulate the files
                    writer.reset ();
                    reader.reset ();
                }
                else
                {
                    // failure to convert
                    jassertfalse;
                    return;
                }
            }
            else
            {
                juce::AudioBuffer<float> outputBuffer;
                sampleConvert (reader.get (), outputBuffer);
                if (writer->writeFromAudioSampleBuffer (outputBuffer, 0, outputBuffer.getNumSamples ()) == true)
                {
                    // close the writer and reader, so that we can manipulate the files
                    writer.reset ();
                    reader.reset ();
                }
                else
                {
                    // failure to convert
                    jassertfalse;
                    return;
                }
            }
        }
        else
        {
            //failure to create writer
            jassertfalse;
            return;
        }

    }
}

void SampleBankComponent::setBankFolder (const juce::File& newBankFolder)
{
    banksRootFolder = newBankFolder;
}

void SampleBankComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::black);
    // TODO juce docs recommend using drawRect for vertical and horizontal lines
    // draw horizontal lines
    for (auto lineIndex { 0 }; lineIndex < 15; ++lineIndex)
    {
        g.drawLine (juce::Line { hiHatSampleInfoList [lineIndex].openedNameLabel.getX (), hiHatSampleInfoList [lineIndex].openedNameLabel.getBottom () + 1,
                                 hiHatSampleInfoList [lineIndex].closedNameLabel.getRight (), hiHatSampleInfoList [lineIndex].openedNameLabel.getBottom () + 1 }.toFloat(), 1.0f);
    }
    // draw vertical center line
    g.drawLine (juce::Line { hiHatSampleInfoList [0].openedNameLabel.getRight () + 2, hiHatSampleInfoList [0].openedNameLabel.getY (),
                             hiHatSampleInfoList [0].openedNameLabel.getRight () + 2, hiHatSampleInfoList [15].openedNameLabel.getBottom () + 2 }.toFloat (), 1.0f);

    // draw box outline
    g.drawRect (hiHatSampleInfoList [0].openedNameLabel.getX (), hiHatSampleInfoList [0].openedNameLabel.getY (),
                hiHatSampleInfoList [0].closedNameLabel.getRight () - hiHatSampleInfoList [0].openedNameLabel.getX (),
                hiHatSampleInfoList [15].openedNameLabel.getBottom () - hiHatSampleInfoList [0].openedNameLabel.getY () + 2);
}

void SampleBankComponent::resized ()
{
    auto bounds { getLocalBounds ().reduced (3) };
    bankName.setBounds (bounds.removeFromTop (20));
    for (auto hiHatSampleInfoIndex { 0 }; hiHatSampleInfoIndex < hiHatSampleInfoList.size (); ++hiHatSampleInfoIndex)
    {
        auto& hiHatSampleInfo { hiHatSampleInfoList [hiHatSampleInfoIndex] };
        auto hiHatSampleIndoBounds { bounds.removeFromTop (20).withTrimmedLeft (1) };
        hiHatSampleInfo.name.setBounds (hiHatSampleIndoBounds.removeFromLeft (25));

        hiHatSampleInfo.openedNameLabel.setBounds (hiHatSampleIndoBounds.removeFromLeft (57));
        hiHatSampleInfo.closedNameLabel.setBounds (hiHatSampleIndoBounds.removeFromLeft (57));
    }
}

void SampleBankComponent::timerCallback ()
{
    // stop auditioning after some time
    if (auditioningSampleLabelComponent != nullptr)
    {
        if (audioPlayerProperties.getPlayState () != AudioPlayerProperties::PlayState::play)
        {
            auditioningSampleLabelComponent->enablePlayBlink (false);
            auditioningSampleLabelComponent = nullptr;
            stopTimer ();
        }
    }
}

void SampleBankComponent::setBankName (const juce::String& newBankName)
{
    bankName.setText (newBankName, juce::NotificationType::dontSendNotification);
}