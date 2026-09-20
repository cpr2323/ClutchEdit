#include "SampleBankComponent.h"
#include "../Theme/UiComponents.h"
#include "../../Clutch/BankProperties.h"
#include "../../Clutch/LedColorList.h"
#include "../../Clutch/SamplePairProperties.h"
#include "../../SRC/libsamplerate-0.1.9/src/samplerate.h"
#include "oolib/Properties/PersistentRootProperties.h"
#include "oolib/Properties/RuntimeRootProperties.h"

SampleBankComponent::SampleBankComponent ()
{
    bankName.setFont (ClutchType::sectionHeader ());
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
                juce::PopupMenu pm;
                pm.addSectionHeader ((sampleType == SampleProperties::SampleType::open ? "Opened " : "Closed ") + sampleIndexString);
                pm.addSeparator ();
                const auto sampleFile { juce::File (getFullPath (hiHatSampleIndex, sampleType)) };
                const auto otherSampleFile { juce::File (getFullPath (hiHatSampleIndex, sampleType == SampleProperties::SampleType::open ? SampleProperties::SampleType::closed : SampleProperties::SampleType::open)) };
                pm.addItem ("Swap", sampleFile.exists () || otherSampleFile.exists (), false, [this, sampleFile, otherSampleFile, sampleType, &hiHatSampleInfo] ()
                {
                    if (sampleFile.exists () && ! otherSampleFile.exists ())
                    {
                        sampleFile.copyFileTo (otherSampleFile.withFileExtension ("._wav"));
                        sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true);
                    }
                    else if (! sampleFile.exists () && otherSampleFile.exists ())
                    {
                        otherSampleFile.copyFileTo (sampleFile.withFileExtension ("._wav"));
                        sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true);
                    }
                    else
                    {
                        // if both files exist, we need to use a temp file to swap them
                        // todo handle temp files
                        const auto sampleIsOriginal { sampleFile.getFileExtension ().toLowerCase () == ".wav" };
                        const auto otherSampleIsOriginal { otherSampleFile.getFileExtension ().toLowerCase () == ".wav" };
                        if (sampleIsOriginal && otherSampleIsOriginal)
                        {
                            sampleFile.copyFileTo (otherSampleFile.withFileExtension ("._wav"));
                            otherSampleFile.copyFileTo (sampleFile.withFileExtension ("._wav"));
                            hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true);
                            hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true);
                        }
                        else if (sampleIsOriginal && ! otherSampleIsOriginal)
                        {
                            otherSampleFile.copyFileTo (sampleFile.withFileExtension ("._wav"));
                            sampleFile.copyFileTo (otherSampleFile.withFileExtension ("._wav"));
                            sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true);
                        }
                        else if (! sampleIsOriginal && otherSampleIsOriginal)
                        {
                            sampleFile.copyFileTo (otherSampleFile.withFileExtension ("._wav"));
                            otherSampleFile.copyFileTo (sampleFile.withFileExtension ("._wav"));
                            sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true);
                        }
                        else // ! sampleIsOriginal && ! otherSampleIsOriginal
                        {
                            auto tempFile { sampleFile.withFileExtension (".tmp") };
                            sampleFile.copyFileTo (tempFile);
                            otherSampleFile.copyFileTo (sampleFile.withFileExtension ("._wav"));
                            tempFile.copyFileTo (otherSampleFile.withFileExtension ("._wav"));
                            tempFile.deleteFile ();
                            if (sampleFile.withFileExtension (".wav").exists ())
                                sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true);
                            if (otherSampleFile.withFileExtension (".wav").exists ())
                                sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true);

                        }
                    }
                });
                pm.addItem ("Delete", sampleFile.exists (), false, [this, sampleFile, &hiHatSampleInfo, sampleType] ()
                {
                    // if we are deleted a temp file, then we just delete the file.
                    // if we are deleting the original file, then we mark the sample properties as deleted, but we don't actually delete the file. the original file will be deleted when the project is SAVED
                    if (sampleFile.getFileExtension ().toLowerCase () == "._wav")
                        sampleFile.deleteFile ();
                    else
                        sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true);
                });
                pm.addItem ("Revert", true, false, [this, sampleFile, &hiHatSampleInfo, sampleType] ()
                {
                    // if we are reverting a temp file, then we just delete the file.
                    if (sampleFile.getFileExtension ().toLowerCase () == "._wav")
                        sampleFile.deleteFile ();

                    // for both temp and original files, we also set the deleted flag to false, and copy the exists flag from the unedited properties
                    auto& sampleProperties { sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties : hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties };
                    sampleProperties.setDeleted (false, true);
                    auto& uneditedSampleProperties { sampleType == SampleProperties::SampleType::open ? hiHatSampleInfo.uneditedSamplePropertiesPair.openedSampleProperties : hiHatSampleInfo.uneditedSamplePropertiesPair.closedSampleProperties };
                    sampleProperties.setExists (uneditedSampleProperties.getExists (), true);
                });
                pm.showMenuAsync ({});
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
                audioPlayerProperties.setSampleId ((getLedColorIndex (bankProperties.getName ()) * 32) + ((hiHatSampleIndex * 2) + (sampleType == SampleProperties::SampleType::open ? 0 : 1)) , false);
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
            copyToTempSampleFile (juce::File (files[0]), hiHatSampleIndex, HiHatState::opened);
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
            copyToTempSampleFile (juce::File (files [0]), hiHatSampleIndex, HiHatState::closed);
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

void SampleBankComponent::init (juce::ValueTree rootPropertiesVT, juce::ValueTree bankPropertiesVT, juce::ValueTree uneditedBankPropertiesVT)
{
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::client, AppProperties::EnableCallbacks::no);

    RuntimeRootProperties runtimeRootProperties { rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no };
    audioPlayerProperties.wrap (runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::client, AudioPlayerProperties::EnableCallbacks::no);
    
    bankProperties.wrap (bankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::yes);
    uneditedBankProperties.wrap (uneditedBankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::yes);

    setBankName (bankProperties.getName ());
    bankProperties.forEachSamplePair ([this, uneditedBankPropertiesVT = uneditedBankProperties.getValueTree ()] (juce::ValueTree samplePairVT, int samplePairIndex)
    {
        HiHatSampleInfo& hiHatSampleInfo { hiHatSampleInfoList [samplePairIndex] };

        SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
        BankProperties uneditedBankProperties (uneditedBankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::yes);
        SamplePairProperties uneditedSamplePairProperties { uneditedBankProperties.getSamplePairVT( samplePairIndex), SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };

        auto isTempFile = [this] (int samplePairIndex, SampleProperties::SampleType sampleType) -> bool
        {
            return juce::File (getFullPath(samplePairIndex, sampleType)).getFileExtension().toLowerCase() == "._wav";
        };

        hiHatSampleInfo.uneditedSamplePropertiesPair.openedSampleProperties.wrap (uneditedSamplePairProperties.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::yes);
        hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.wrap (samplePairProperties.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::yes);
        hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.onExistsChange = [this, &hiHatSampleInfo, isTempFile, samplePairIndex] (bool exists)
        {
            hiHatSampleInfo.openedNameLabel.setFileExistState (exists && (isTempFile (samplePairIndex, SampleProperties::SampleType::open) || ! hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.getDeleted ()));
        };
        hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.onDeletedChange = [this, &hiHatSampleInfo, isTempFile, samplePairIndex] (bool deleted)
        {
            hiHatSampleInfo.openedNameLabel.setFileExistState ((isTempFile (samplePairIndex, SampleProperties::SampleType::open) || ! deleted) && hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.getExists());
        };

        hiHatSampleInfo.uneditedSamplePropertiesPair.closedSampleProperties.wrap (uneditedSamplePairProperties.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::yes);
        hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.wrap (samplePairProperties.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::yes);
        hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.onExistsChange = [this, &hiHatSampleInfo, isTempFile, samplePairIndex] (bool exists)
        {
            hiHatSampleInfo.closedNameLabel.setFileExistState (exists && (isTempFile (samplePairIndex, SampleProperties::SampleType::closed) || ! hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.getDeleted ()));
        };
        hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.onDeletedChange = [this, &hiHatSampleInfo, isTempFile, samplePairIndex] (bool deleted)
        {
            hiHatSampleInfo.closedNameLabel.setFileExistState ((isTempFile (samplePairIndex, SampleProperties::SampleType::closed) || ! deleted) && hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.getExists ());
        };

        hiHatSampleInfo.openedNameLabel.setFileExistState (hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.getExists ());
        hiHatSampleInfo.closedNameLabel.setFileExistState (hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.getExists ());
        return true;
    });
}

juce::String SampleBankComponent::getBankAndFileNameWithoutExtension (int hiHatSampleIndex, SampleProperties::SampleType sampleType)
{
    return bankName.getText () + juce::File::getSeparatorString () + juce::String (hiHatSampleIndex + 1).paddedLeft ('0', 2) + (sampleType == SampleProperties::SampleType::open ? "OH" : "CH");
}

juce::String SampleBankComponent::getFullPath (int hiHatSampleIndex, SampleProperties::SampleType sampleType)
{
    const auto bankAndFileNameWithouExtension { getBankAndFileNameWithoutExtension (hiHatSampleIndex, sampleType) };
    auto fullFileNameWithoutExtension { juce::File (appProperties.getMostRecentFolder ()).getChildFile (bankAndFileNameWithouExtension) };
    if (fullFileNameWithoutExtension.withFileExtension ("._wav").existsAsFile ())
        return fullFileNameWithoutExtension.getFullPathName () + "._wav";
    return fullFileNameWithoutExtension.getFullPathName () + ".wav";
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
void SampleBankComponent::copyToTempSampleFile (juce::File sourceFile, int hiHatSampleIndex, HiHatState hiHatState)
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
    if (destFile.withFileExtension (".wav").existsAsFile ())
    {
        auto& hiHatSampleInfo { hiHatSampleInfoList [hiHatSampleIndex] };
        hiHatState == HiHatState::opened ? hiHatSampleInfo.editedSamplePropertiesPair.openedSampleProperties.setDeleted (true, true) : hiHatSampleInfo.editedSamplePropertiesPair.closedSampleProperties.setDeleted (true, true);
    }

    if (reader->getFormatName () == "WAV file" && reader->numChannels == 1 && reader->bitsPerSample == 16 && (reader->sampleRate == 44100 || reader->sampleRate == 48000))
    {
        sourceFile.copyFileTo (destFile);
    }
    else
    {
        // Source file does not meet required format
        // truncate () is FileOutputStream only, so the setup has to happen while the pointer still
        // has that type
        auto destinationFileStream { std::make_unique<juce::FileOutputStream> (destFile) };
        destinationFileStream->setPosition (0);
        destinationFileStream->truncate ();
        // createWriterFor takes a unique_ptr<OutputStream>&, and a unique_ptr<FileOutputStream>
        // cannot bind to a reference to a different type, so the stream is moved into a base typed
        // pointer to hand over. this is the same stream: destinationFileStream is null from here on
        std::unique_ptr<juce::OutputStream> streamForWriter { std::move (destinationFileStream) };

        juce::WavAudioFormat wavAudioFormat;
        // TODO : do I need to do a proper L/R mix for stereo input?
        // on success, the writer takes ownership of the destination stream, and will delete it when done
        if (auto writer { wavAudioFormat.createWriterFor (streamForWriter, juce::AudioFormatWriterOptions {}.withSampleRate (48000)
                                                                                                           .withNumChannels (1)
                                                                                                           .withBitsPerSample (16)) }; writer != nullptr)
        {
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

// A label keeps a per-instance colour, so it has to be refreshed by hand when the
// palette changes.
void SampleBankComponent::applyExplicitColours ()
{
    bankName.setColour (juce::Label::ColourIds::textColourId, findColour (ClutchColours::accentText));
}

void SampleBankComponent::lookAndFeelChanged ()
{
    juce::Component::lookAndFeelChanged ();
    applyExplicitColours ();
}

void SampleBankComponent::resized ()
{
    // the slots carry their own borders now, so a row leaves a little air above and
    // below its fields rather than running them into the rows either side
    constexpr auto kRowHeight { 20 };
    constexpr auto kRowInset { 1 };
    constexpr auto kIndexWidth { 25 };
    constexpr auto kFieldGap { 3 };

    auto bounds { getLocalBounds ().reduced (3) };
    bankName.setBounds (bounds.removeFromTop (20));
    for (auto hiHatSampleInfoIndex { 0 }; hiHatSampleInfoIndex < hiHatSampleInfoList.size (); ++hiHatSampleInfoIndex)
    {
        auto& hiHatSampleInfo { hiHatSampleInfoList [hiHatSampleInfoIndex] };
        auto rowBounds { bounds.removeFromTop (kRowHeight).withTrimmedLeft (kRowInset) };
        hiHatSampleInfo.name.setBounds (rowBounds.removeFromLeft (kIndexWidth));

        // the two slots share whatever is left, so a wider bank gives them the room
        auto fieldBounds { rowBounds.reduced (0, kRowInset) };
        hiHatSampleInfo.openedNameLabel.setBounds (fieldBounds.removeFromLeft ((fieldBounds.getWidth () - kFieldGap) / 2));
        fieldBounds.removeFromLeft (kFieldGap);
        hiHatSampleInfo.closedNameLabel.setBounds (fieldBounds);
    }
}

void SampleBankComponent::timerCallback ()
{
    // stop auditioning after some time
    if (auditioningSampleLabelComponent != nullptr)
    {
        const auto bankId { (getLedColorIndex (bankProperties.getName ()) * 32) };
        const auto currentlyPlayingSampleId { audioPlayerProperties.getSampleId () };
        if (audioPlayerProperties.getPlayState () != AudioPlayerProperties::PlayState::play ||
            (audioPlayerProperties.getPlayState () == AudioPlayerProperties::PlayState::play && (currentlyPlayingSampleId < bankId || currentlyPlayingSampleId >= bankId + 32)))
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