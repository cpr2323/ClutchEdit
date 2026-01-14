#include "SampleBankComponent.h"
#include "../../SRC/libsamplerate-0.1.9/src/samplerate.h"

SampleBankComponent::SampleBankComponent ()
{
    addAndMakeVisible(bankName);
    for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
    {
        auto& surfaceComponent { surfaceComponents [surfaceIndex] };
        surfaceComponent.name.setText (juce::String (surfaceIndex + 1), juce::NotificationType::dontSendNotification);

        surfaceComponent.openedName.setJustificationType (juce::Justification::centred);
        surfaceComponent.openedName.setText ("Opened", juce::NotificationType::dontSendNotification);
        surfaceComponent.openedName.onFilesSelected = [this, surfaceIndex] (juce::StringArray files)
        {
            jassert (files.size () == 1);
            copySampleFile(juce::File (files[0]), surfaceIndex, WhichHiHat::opened);
        };

        surfaceComponent.closedName.setJustificationType (juce::Justification::centred);
        surfaceComponent.closedName.setText ("Closed", juce::NotificationType::dontSendNotification);
        surfaceComponent.closedName.onFilesSelected = [this, surfaceIndex] (juce::StringArray files)
        {
            jassert (files.size () == 1);
            copySampleFile (juce::File (files [0]), surfaceIndex, WhichHiHat::closed);
        };
        addAndMakeVisible (surfaceComponent.name);
        addAndMakeVisible (surfaceComponent.openedName);
        addAndMakeVisible (surfaceComponent.closedName);
    }

    updateFileStatus ();
    startTimer (2000);
}

SampleBankComponent::~SampleBankComponent ()
{

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
void SampleBankComponent::copySampleFile (juce::File sourceFile, int surfaceIndex, WhichHiHat whichHiHat)
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

    juce::String destinationFileName { juce::String (surfaceIndex + 1).paddedLeft ('0', 2) + (whichHiHat == WhichHiHat::closed ? "C" : "O") + "H.wav" };
    juce::File destFile { bankFolder.getChildFile (bankName.getText ()).getChildFile (destinationFileName) };

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
    updateFileStatus ();
}

// TODO : move this to a thread
void SampleBankComponent::updateFileStatus ()
{
    if (bankFolder != juce::File ())
    {
        for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
        {
            auto doesFileExist = [this] (int surfaceIndex, WhichHiHat whichHiHat)
            {
                juce::String fileName { juce::String (surfaceIndex + 1).paddedLeft ('0', 2) + juce::String (whichHiHat == WhichHiHat::opened ? "OH" : "CH") };
                auto file { bankFolder.getChildFile (bankName.getText ()).getChildFile (fileName).withFileExtension ("wav") };
                return file.existsAsFile ();
            };
            surfaceComponents [surfaceIndex].openedName.setFileExists (doesFileExist (surfaceIndex, WhichHiHat::opened));
            surfaceComponents [surfaceIndex].closedName.setFileExists (doesFileExist (surfaceIndex, WhichHiHat::closed));
        }
    }
    repaint ();
}

void SampleBankComponent::setBankFolder (const juce::File& newBankFolder)
{
    bankFolder = newBankFolder;
}

void SampleBankComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::black);
    for (auto lineIndex { 0 }; lineIndex < 15; ++lineIndex)
    {
        g.drawLine (surfaceComponents [lineIndex].openedName.getX (), surfaceComponents [lineIndex].openedName.getBottom (),
                    surfaceComponents [lineIndex].closedName.getRight (), surfaceComponents [lineIndex].openedName.getBottom (), 1.0f);
    }
    g.drawLine (surfaceComponents [0].openedName.getRight (), surfaceComponents [0].openedName.getY (),
                surfaceComponents [0].openedName.getRight (), surfaceComponents [15].openedName.getBottom () + 2, 1.0f);
    g.drawRect (surfaceComponents [0].openedName.getX (), surfaceComponents [0].openedName.getY (),
                surfaceComponents [0].closedName.getRight () - surfaceComponents [0].openedName.getX (),
                surfaceComponents [15].openedName.getBottom () - surfaceComponents [0].openedName.getY () + 2);
}

void SampleBankComponent::resized ()
{
    auto bounds { getLocalBounds ().reduced (3) };
    bankName.setBounds (bounds.removeFromTop (20));
    for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
    {
        auto& surfaceComponent { surfaceComponents [surfaceIndex] };
        auto surfaceBounds { bounds.removeFromTop (20).withTrimmedLeft (1) };
        surfaceComponent.name.setBounds (surfaceBounds.removeFromLeft (25));

        surfaceComponent.openedName.setBounds (surfaceBounds.removeFromLeft (57));
        surfaceComponent.closedName.setBounds (surfaceBounds.removeFromLeft (57));
    }
}

void SampleBankComponent::timerCallback ()
{
    updateFileStatus ();
}

void SampleBankComponent::setBankName (const juce::String& newBankName)
{
    bankName.setText (newBankName, juce::NotificationType::dontSendNotification);
    updateFileStatus ();
}
