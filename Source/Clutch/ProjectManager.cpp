#include "ProjectManager.h"
#include "BankListProperties.h"
#include "BankProperties.h"
#include "EffectListProperties.h"
#include "EffectProperties.h"
#include "HiHatIniData.h"
#include "PatternProperties.h"
#include "PatternListProperties.h"
#include "SamplePairProperties.h"
#include "SampleProperties.h"
#include "SettingsProperties.h"
#include "Audio/AudioPlayerProperties.h"
#include "../AppProperties.h"
#include "oolib/Properties/RuntimeRootProperties.h"
#include "oolib/Properties/PersistentRootProperties.h"

ProjectManager::ProjectManager ()
{
}

void ProjectManager::init (juce::ValueTree theRootPropertiesVT)
{
    rootPropertiesVT = theRootPropertiesVT;

    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::client, AppProperties::EnableCallbacks::yes);
    appProperties.onMostRecentFileChange = [this] (const juce::File& mostRecentFile)
    {
        openProject (mostRecentFile);
    };

    runtimeRootProperties.wrap (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::yes);
    runtimeRootProperties.onSystemRequestedQuit = [this] ()
    {
        AudioPlayerProperties audioPlayerProperties { runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::client, AudioPlayerProperties::EnableCallbacks::no };
        audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
        runtimeRootProperties.setPreferredQuitState (RuntimeRootProperties::QuitState::idle, false);
        auto doQuit = [this] ()
        {
            cleanUpTempFiles ();
            // since this is an async operation, and we are quitting the app, let's be safe take a reference to the ValueTree we need
            juce::MessageManager::callAsync ([runtimeRootPropertiesVT = runtimeRootProperties.getValueTree ()] ()
            {
                RuntimeRootProperties runtimeRootProperties { runtimeRootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no };
                runtimeRootProperties.setQuitState (RuntimeRootProperties::QuitState::now, false);
            });
        };

        if (! projectManagerProperties.getProjectEdited ())
        {
            doQuit ();
        }
        else
        {
            juce::AlertWindow::showOkCancelBox (juce::AlertWindow::WarningIcon, "WARNING: Edits Have Been Made",
                                                "You have not saved the project that you have edited.\n  Select Continue to lose your changes.\n  Select Cancel to go back and save.", "Continue (lose changes)", "Cancel", nullptr,
                                                juce::ModalCallbackFunction::create ([this, doQuit] (int option)
                                                {
                                                    juce::MessageManager::callAsync ([this, option, doQuit] ()
                                                    {
                                                        if (option == 1) // Continue
                                                            doQuit ();
                                                    });
                                                }));
        }
    };
    projectManagerProperties.wrap (runtimeRootProperties.getValueTree(), ProjectManagerProperties::WrapperType::owner, ProjectManagerProperties::EnableCallbacks::yes);
    projectManagerProperties.onSaveProject = [this] ()
    {
        saveProject ();
    };
    projectManagerProperties.onCleanupTempFiles = [this] ()
    {
        cleanUpTempFiles ();
    };
    unEditedClutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    editedClutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "edited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);

    openProject (appProperties.getRecentlyUsedFile (0));

    // scan sample folders and check for edits every 1/2 second
    startTimer (500);
}

void ProjectManager::openProject (const juce::File& hiHatIniFile)
{
    // ensure there are no temp files left over from a program crash or something
    cleanUpTempFiles ();

    // verification that the file exists is done in the caller, so we can assume it exists here
    jassert (hiHatIniFile.existsAsFile ());
    hiHatIniData.readFromFile (hiHatIniFile);
    hiHatIniData.FillInPropertiesFromData (unEditedClutchProperties.getValueTree ());
    hiHatIniData.FillInPropertiesFromData (editedClutchProperties.getValueTree ());

    // create bank list properties on the unedited branch, so we can track sample changes
    scanSamples (unEditedClutchProperties.getValueTree ());
    // initialize the edited sample properties by copying from the unedited sample properties
    copySampleProperties (unEditedClutchProperties.getValueTree (), editedClutchProperties.getValueTree (), false);
}

bool ProjectManager::areEntireClutchPropertiesEqual (juce::ValueTree clutchPropertiesVT1, juce::ValueTree clutchPropertiesVT2)
{
    ClutchProperties clutchProperties1 (clutchPropertiesVT1, ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    ClutchProperties clutchProperties2 (clutchPropertiesVT2, ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);

    SettingsProperties settingsProperties1 (clutchProperties1.getValueTree (), SettingsProperties::WrapperType::client, SettingsProperties::EnableCallbacks::no);
    SettingsProperties settingsProperties2 (clutchProperties2.getValueTree (), SettingsProperties::WrapperType::client, SettingsProperties::EnableCallbacks::no);
    if (settingsProperties1.getPitchLow () != settingsProperties2.getPitchLow () ||
        settingsProperties1.getPitchHigh () != settingsProperties2.getPitchHigh () ||
        settingsProperties1.getEnvelopeMaxRelease () != settingsProperties2.getEnvelopeMaxRelease () ||
        settingsProperties1.getChokeRelease () != settingsProperties2.getChokeRelease () ||
        settingsProperties1.getReleaseMode () != settingsProperties2.getReleaseMode () ||
        settingsProperties1.getClsdRelOfstScale () != settingsProperties2.getClsdRelOfstScale () ||
        settingsProperties1.getClsdMaxRelease () != settingsProperties2.getClsdMaxRelease () ||
        settingsProperties1.getAccClRelMod () != settingsProperties2.getAccClRelMod () ||
        settingsProperties1.getAccOpRelMod () != settingsProperties2.getAccOpRelMod () ||
        settingsProperties1.getAccClAmpMod () != settingsProperties2.getAccClAmpMod () ||
        settingsProperties1.getAccOpAmpMod () != settingsProperties2.getAccOpAmpMod () ||
        settingsProperties1.getFxCvUnipolar () != settingsProperties2.getFxCvUnipolar () ||
        settingsProperties1.getVelocityUnipolar () != settingsProperties2.getVelocityUnipolar () ||
        settingsProperties1.getCvDisableVelocity () != settingsProperties2.getCvDisableVelocity () ||
        settingsProperties1.getCvDisableFx () != settingsProperties2.getCvDisableFx () ||
        settingsProperties1.getGateMode () != settingsProperties2.getGateMode () ||
        settingsProperties1.getFeelAttackMod () != settingsProperties2.getFeelAttackMod () ||
        settingsProperties1.getFeelReleaseMod () != settingsProperties2.getFeelReleaseMod () ||
        settingsProperties1.getFeelAmpMod () != settingsProperties2.getFeelAmpMod () ||
        settingsProperties1.getKnobPosTakeup () != settingsProperties2.getKnobPosTakeup () ||
        settingsProperties1.getFltrHpfMinFreq () != settingsProperties2.getFltrHpfMinFreq () ||
        settingsProperties1.getFltrHpfMaxFreq () != settingsProperties2.getFltrHpfMaxFreq () ||
        settingsProperties1.getFltrLpfMinFreq () != settingsProperties2.getFltrLpfMinFreq () ||
        settingsProperties1.getFltrLpfMaxFreq () != settingsProperties2.getFltrLpfMaxFreq () ||
        settingsProperties1.getFltrHpfQ () != settingsProperties2.getFltrHpfQ () ||
        settingsProperties1.getFltrLpfQ () != settingsProperties2.getFltrLpfQ () ||
        settingsProperties1.getFxDjfilterHpfMin () != settingsProperties2.getFxDjfilterHpfMin () ||
        settingsProperties1.getFxDjfilterHpfMax () != settingsProperties2.getFxDjfilterHpfMax () ||
        settingsProperties1.getFxDjfilterLpfMin () != settingsProperties2.getFxDjfilterLpfMin () ||
        settingsProperties1.getFxDjfilterLpfMax () != settingsProperties2.getFxDjfilterLpfMax () ||
        settingsProperties1.getFxDjfilterQMin () != settingsProperties2.getFxDjfilterQMin () ||
        settingsProperties1.getFxDjfilterQMax () != settingsProperties2.getFxDjfilterQMax () ||
        settingsProperties1.getFxDjfilterQGainReduction () != settingsProperties2.getFxDjfilterQGainReduction () ||
        settingsProperties1.getFxDubEchoTmin () != settingsProperties2.getFxDubEchoTmin () ||
        settingsProperties1.getFxDubEchoHpf () != settingsProperties2.getFxDubEchoHpf () ||
        settingsProperties1.getFxDubEchoLpf () != settingsProperties2.getFxDubEchoLpf () ||
        settingsProperties1.getFxDubEchoMix () != settingsProperties2.getFxDubEchoMix () ||
        settingsProperties1.getFxChorusCenter () != settingsProperties2.getFxChorusCenter () ||
        settingsProperties1.getFxChorusDepth () != settingsProperties2.getFxChorusDepth () ||
        settingsProperties1.getFxChorusMix () != settingsProperties2.getFxChorusMix () ||
        settingsProperties1.getFxChorusSpread () != settingsProperties2.getFxChorusSpread () ||
        settingsProperties1.getFxChorusTaps () != settingsProperties2.getFxChorusTaps () ||
        settingsProperties1.getFxChorusLfoB () != settingsProperties2.getFxChorusLfoB () ||
        settingsProperties1.getFxChorusLfoT () != settingsProperties2.getFxChorusLfoT () ||
        settingsProperties1.getFxChorusType () != settingsProperties2.getFxChorusType () ||
        settingsProperties1.getFxChorusStagger () != settingsProperties2.getFxChorusStagger () ||
        settingsProperties1.getFxReverbLpf () != settingsProperties2.getFxReverbLpf () ||
        settingsProperties1.getFxReverbHpf () != settingsProperties2.getFxReverbHpf () ||
        settingsProperties1.getFxReverbType () != settingsProperties2.getFxReverbType () ||
        settingsProperties1.getFxReverbSizeMin () != settingsProperties2.getFxReverbSizeMin () ||
        settingsProperties1.getFxReverbSizeMax () != settingsProperties2.getFxReverbSizeMax () ||
        settingsProperties1.getFxReverbPredelay () != settingsProperties2.getFxReverbPredelay () ||
        settingsProperties1.getFxReverbModDepth () != settingsProperties2.getFxReverbModDepth () ||
        settingsProperties1.getFxReverbModRate () != settingsProperties2.getFxReverbModRate () ||
        settingsProperties1.getFxReverbDiffusion () != settingsProperties2.getFxReverbDiffusion () ||
        settingsProperties1.getFxReverbMix () != settingsProperties2.getFxReverbMix () ||
        settingsProperties1.getFxGlitchProbabilityMin () != settingsProperties2.getFxGlitchProbabilityMin () ||
        settingsProperties1.getFxGlitchProbabilityMax () != settingsProperties2.getFxGlitchProbabilityMax () ||
        settingsProperties1.getFxGlitchWeightHoldLow () != settingsProperties2.getFxGlitchWeightHoldLow () ||
        settingsProperties1.getFxGlitchWeightStutterLow () != settingsProperties2.getFxGlitchWeightStutterLow () ||
        settingsProperties1.getFxGlitchWeightCrushLow () != settingsProperties2.getFxGlitchWeightCrushLow () ||
        settingsProperties1.getFxGlitchWeightDropLow () != settingsProperties2.getFxGlitchWeightDropLow () ||
        settingsProperties1.getFxGlitchWeightHoldHigh () != settingsProperties2.getFxGlitchWeightHoldHigh () ||
        settingsProperties1.getFxGlitchWeightStutterHigh () != settingsProperties2.getFxGlitchWeightStutterHigh () ||
        settingsProperties1.getFxGlitchWeightCrushHigh () != settingsProperties2.getFxGlitchWeightCrushHigh () ||
        settingsProperties1.getFxGlitchWeightDropHigh () != settingsProperties2.getFxGlitchWeightDropHigh () ||
        settingsProperties1.getFxGlitchDropKeepLevelMin () != settingsProperties2.getFxGlitchDropKeepLevelMin () ||
        settingsProperties1.getFxGlitchDropKeepLevelMax () != settingsProperties2.getFxGlitchDropKeepLevelMax () ||
        settingsProperties1.getFxGlitchDropKeepTimeMin () != settingsProperties2.getFxGlitchDropKeepTimeMin () ||
        settingsProperties1.getFxGlitchDropKeepTimeMax () != settingsProperties2.getFxGlitchDropKeepTimeMax () ||
        settingsProperties1.getFxGlitchCrushTimeMin () != settingsProperties2.getFxGlitchCrushTimeMin () ||
        settingsProperties1.getFxGlitchCrushTimeMax () != settingsProperties2.getFxGlitchCrushTimeMax () ||
        settingsProperties1.getFxGlitchMicroloopSmplTMin () != settingsProperties2.getFxGlitchMicroloopSmplTMin () ||
        settingsProperties1.getFxGlitchMicroloopSmplTMax () != settingsProperties2.getFxGlitchMicroloopSmplTMax () ||
        settingsProperties1.getFxGlitchMicroloopPlayTMin () != settingsProperties2.getFxGlitchMicroloopPlayTMin () ||
        settingsProperties1.getFxGlitchMicroloopPlayTMax () != settingsProperties2.getFxGlitchMicroloopPlayTMax () ||
        settingsProperties1.getFxGlitchStutterSmplTMin () != settingsProperties2.getFxGlitchStutterSmplTMin () ||
        settingsProperties1.getFxGlitchStutterSmplTMax () != settingsProperties2.getFxGlitchStutterSmplTMax () ||
        settingsProperties1.getFxGlitchStutterNumMin () != settingsProperties2.getFxGlitchStutterNumMin () ||
        settingsProperties1.getFxGlitchStutterNumMax () != settingsProperties2.getFxGlitchStutterNumMax () ||
        settingsProperties1.getFxGlitchStutterWindow () != settingsProperties2.getFxGlitchStutterWindow ())
        return false;

    PatternListProperties patternListProperties1 (clutchProperties1.getValueTree (), PatternListProperties::WrapperType::client, PatternListProperties::EnableCallbacks::no);
    PatternListProperties patternListProperties2 (clutchProperties2.getValueTree (), PatternListProperties::WrapperType::client, PatternListProperties::EnableCallbacks::no);
    for (auto patternIndex { 0 }; patternIndex < patternListProperties1.getValueTree ().getNumChildren (); ++patternIndex)
    {
        auto patternVT1 { patternListProperties1.getPatternVT (patternIndex) };
        auto patternVT2 { patternListProperties2.getPatternVT (patternIndex) };
        PatternProperties patternProperties1 (patternVT1, PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::no);
        PatternProperties patternProperties2 (patternVT2, PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::no);
        if (patternProperties1.getPattern () != patternProperties2.getPattern ())
            return false;
    }

    EffectListProperties effectListProperties1 (clutchProperties1.getValueTree (), EffectListProperties::WrapperType::client, EffectListProperties::EnableCallbacks::no);
    EffectListProperties effectListProperties2 (clutchProperties2.getValueTree (), EffectListProperties::WrapperType::client, EffectListProperties::EnableCallbacks::no);
    for (auto effectIndex { 0 }; effectIndex < effectListProperties1.getValueTree ().getNumChildren (); ++effectIndex)
    {
        auto effectVT1 { effectListProperties1.getEffectVT (effectIndex) };
        auto effectVT2 { effectListProperties2.getEffectVT (effectIndex) };
        EffectProperties effectProperties1 (effectVT1, EffectProperties::WrapperType::client, EffectProperties::EnableCallbacks::no);
        EffectProperties effectProperties2 (effectVT2, EffectProperties::WrapperType::client, EffectProperties::EnableCallbacks::no);
        if (effectProperties1.getEffect () != effectProperties2.getEffect ())
            return false;
    }

    auto banksMatch { true };
    BankListProperties bankListProperties1 (clutchProperties1.getValueTree (), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no);
    BankListProperties bankListProperties2 (clutchProperties2.getValueTree (), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no);
    bankListProperties1.forEachBank ([&bankListProperties2, &banksMatch] (juce::ValueTree bankVT1, int bankIndex)
    {
        auto bankVT2 { bankListProperties2.getBankVT (bankIndex) };
        BankProperties bankProperties1 { bankVT1, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        BankProperties bankProperties2 { bankVT2, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        bankProperties1.forEachSamplePair ([&bankProperties2, &banksMatch] (juce::ValueTree samplePairVT1, int samplePairIndex)
        {
            auto samplePairVT2 { bankProperties2.getSamplePairVT (samplePairIndex) };
            SamplePairProperties samplePairProperties1 { samplePairVT1, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
            SamplePairProperties samplePairProperties2 { samplePairVT2, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };

            // check exists flags
            // open sample
            SampleProperties openProperties1 { samplePairProperties1.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties openProperties2 { samplePairProperties2.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            if (openProperties2.getExists () != openProperties1.getExists ())
            {
                banksMatch = false;
                return false;
            }

            // closed sample
            SampleProperties closedProperties1 { samplePairProperties1.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties closedProperties2 { samplePairProperties2.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            if (closedProperties2.getExists () != closedProperties1.getExists ())
            {
                banksMatch = false;
                return false;
            }

            // check deleted flags
            // open sample
            if (openProperties2.getDeleted () != openProperties1.getDeleted ())
            {
                banksMatch = false;
                return false;
            }

            // closed sample
            if (closedProperties2.getDeleted () != closedProperties1.getDeleted ())
            {
                banksMatch = false;
                return false;
            }

            return true;
        });

        return true;
    });
    return banksMatch;
}


void ProjectManager::saveProject ()
{
    doQueuedDeletions ();
    convertTempFilesToPerm ();

    // copy the data from the edited properties into the HiHatIniData object, and write it back out to the file
    hiHatIniData.FillInDataFromProperties (editedClutchProperties.getValueTreeRef ());
    hiHatIniData.writeToFile (appProperties.getRecentlyUsedFile (0));

    // copy the edited data to the unedited properties, to get them back into sync
    // NOTE: I am copying from the data, instead of the other properties, because this function is already doing the needed work
    //       I would like to eventually change it to copy from the properties
    hiHatIniData.FillInPropertiesFromData (unEditedClutchProperties.getValueTree ());
    copySampleProperties (editedClutchProperties.getValueTree (), unEditedClutchProperties.getValueTree (), true);
}

void ProjectManager::scanSamples (juce::ValueTree clutchPropertiesVT)
{
    auto bankParentFolder { juce::File (appProperties.getMostRecentFolder ()) };
    BankListProperties bankListProperties { clutchPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    bankListProperties.forEachBank ([bankParentFolder] (juce::ValueTree bankPropertiesVT, [[maybe_unused]] int bankIndex)
    {
        BankProperties bankProperties { bankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        bankProperties.forEachSamplePair ([bankParentFolder, bankName = bankProperties.getName ()] (juce::ValueTree samplePairVT, [[maybe_unused]] int samplePairIndex)
        {
            // check for file and update exists
            SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
            auto checkSampleExistence = [sampleBankFolder = bankParentFolder.getChildFile (bankName)] (juce::ValueTree samplePropertiesVT)
            {
                SampleProperties sampleProperties { samplePropertiesVT, SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
                auto fullPathWithExtension = [fileNameWithouExtension = sampleProperties.getFilename (), sampleBankFolder] ()
                    {
                        auto fullFileNameWithoutExtension { sampleBankFolder.getChildFile (fileNameWithouExtension) };
                        if (fullFileNameWithoutExtension.withFileExtension ("._wav").existsAsFile ())
                            return fullFileNameWithoutExtension.withFileExtension ("._wav");
                        return fullFileNameWithoutExtension.withFileExtension (".wav");
                    };

                sampleProperties.setExists (juce::File (fullPathWithExtension ()).existsAsFile (), false);
            };
            checkSampleExistence (samplePairProperties.getOpenSampleVT ());
            checkSampleExistence (samplePairProperties.getClosedSampleVT ());
            return true;
        });
        return true;
    });
}

void ProjectManager::timerCallback ()
{
    switch (timerTask)
    {   
        case ProjectManager::TimerTask::scanSamples:
        {
            scanSamples (editedClutchProperties.getValueTree ());
            timerTask = TimerTask::checkForEdits;
        }
        break;
        case ProjectManager::TimerTask::checkForEdits:
        {
            projectManagerProperties.setProjectEdited (! areEntireClutchPropertiesEqual (unEditedClutchProperties.getValueTree (), editedClutchProperties.getValueTree ()), false);
            timerTask = TimerTask::scanSamples;
        }
        break;
        default:
            jassertfalse;
        break;
    }
}

void ProjectManager::convertTempFilesToPerm ()
{
    forEachSamplePair ([this] (juce::ValueTree samplePairVT, juce::File sampleBankFolder)
    {
        auto checkSampleExistence = [&sampleBankFolder] (juce::ValueTree samplePropertiesVT)
        {
            SampleProperties sampleProperties { samplePropertiesVT, SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            auto tempFileName { sampleBankFolder.getChildFile (sampleProperties.getFilename ()).withFileExtension ("._wav") };
            if (tempFileName.existsAsFile ())
            {
                auto permFileName { sampleBankFolder.getChildFile (sampleProperties.getFilename ()).withFileExtension (".wav") };
                if (permFileName.existsAsFile ())
                    permFileName.deleteFile ();
                tempFileName.moveFileTo (permFileName);
            }
        };
        SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
        checkSampleExistence (samplePairProperties.getOpenSampleVT ());
        checkSampleExistence (samplePairProperties.getClosedSampleVT ());
        return true;
    });
}

void ProjectManager::cleanUpTempFiles ()
{
    forEachSamplePair ([this] (juce::ValueTree samplePairVT, juce::File sampleBankFolder)
    {
        auto checkSampleExistence = [&sampleBankFolder] (juce::ValueTree samplePropertiesVT)
        {
            SampleProperties sampleProperties { samplePropertiesVT, SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            auto tempFileName { sampleBankFolder.getChildFile (sampleProperties.getFilename ()).withFileExtension ("._wav") };
            if (tempFileName.existsAsFile ())
                tempFileName.deleteFile ();
        };
        // check for file and update exists
        SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
        checkSampleExistence (samplePairProperties.getOpenSampleVT ());
        checkSampleExistence (samplePairProperties.getClosedSampleVT ());
    });
}

void ProjectManager::doQueuedDeletions ()
{
    forEachSamplePair ([this] (juce::ValueTree samplePairVT, juce::File sampleBankFolder)
    {
        auto checkForFileDelete = [&sampleBankFolder] (juce::ValueTree samplePropertiesVT)
        {
            SampleProperties sampleProperties { samplePropertiesVT, SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            if (sampleProperties.getDeleted())
            {
                auto fileToDelete { sampleBankFolder.getChildFile (sampleProperties.getFilename ()).withFileExtension (".wav") };
                fileToDelete.deleteFile ();
                sampleProperties.setDeleted (false, false);
                sampleProperties.setExists (false, false);
            }
        };
        // check for file and update exists
        SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
        checkForFileDelete (samplePairProperties.getOpenSampleVT ());
        checkForFileDelete (samplePairProperties.getClosedSampleVT ());
    });
}

void ProjectManager::forEachSamplePair (std::function<void(juce::ValueTree samplePairPropertiesVT, juce::File sampleBankFolder)> samplePairCallback)
{
    auto bankParentFolder { juce::File (appProperties.getMostRecentFolder ()) };
    BankListProperties bankListProperties { editedClutchProperties.getValueTree (), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    bankListProperties.forEachBank ([bankParentFolder, samplePairCallback] (juce::ValueTree bankPropertiesVT, [[maybe_unused]] int bankIndex)
    {
        BankProperties bankProperties { bankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        bankProperties.forEachSamplePair ([bankParentFolder, bankName = bankProperties.getName (), samplePairCallback] (juce::ValueTree samplePairVT, [[maybe_unused]] int samplePairIndex)
        {
            samplePairCallback (samplePairVT, bankParentFolder.getChildFile (bankName));
            return true;
        });
        return true;
    });
}

void ProjectManager::copySampleProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT, bool copySamplesReference)
{
        // copy unedited bank list properties to edited bank list properties so that they can be edited
    BankListProperties sourceBankListProperties { sourceClutchPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    BankListProperties destBankListProperties { destClutchPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };

    // copy the exist flag in the SampleProperties for each sample from the unEditedBankListProperties to sample sample in the editedBankListProperties
    sourceBankListProperties.forEachBank ([&destBankListProperties, copySamplesReference] (juce::ValueTree sourceBankVT, int bankIndex)
    {
        auto destBankVT = destBankListProperties.getBankVT (bankIndex);
        BankProperties sourceBank { sourceBankVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        BankProperties destBank { destBankVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };

        sourceBank.forEachSamplePair ([&destBank, copySamplesReference] (juce::ValueTree sourceSamplePairVT, int samplePairIndex)
        {
            auto destSamplePairVT { destBank.getSamplePairVT (samplePairIndex) };
            SamplePairProperties sourceSamplePair { sourceSamplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
            SamplePairProperties destSamplePair { destSamplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };

            // open sample
            SampleProperties sourceOpenProperties { sourceSamplePair.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties destOpenProperties { destSamplePair.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            destOpenProperties.setExists (sourceOpenProperties.getExists (), false);
            destOpenProperties.setDeleted (sourceOpenProperties.getDeleted (), false);
            if (copySamplesReference)
                destOpenProperties.setFilename (sourceOpenProperties.getFilename (), false);

            // closed sample
            SampleProperties sourceClosedProperties { sourceSamplePair.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties destClosedProperties { destSamplePair.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            destClosedProperties.setExists (sourceClosedProperties.getExists (), false);
            destClosedProperties.setDeleted (sourceClosedProperties.getDeleted (), false);
            if (copySamplesReference)
                destClosedProperties.setFilename (destClosedProperties.getFilename (), false);

            return true;
        });

        return true;
    });
}

void ProjectManager::copySettingsProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT)
{
    SettingsProperties sourceSettings { sourceClutchPropertiesVT, SettingsProperties::WrapperType::client, SettingsProperties::EnableCallbacks::no };
    SettingsProperties destSettings { destClutchPropertiesVT, SettingsProperties::WrapperType::client, SettingsProperties::EnableCallbacks::no };

    destSettings.setPitchLow (sourceSettings.getPitchLow (), false);
    destSettings.setPitchHigh (sourceSettings.getPitchHigh (), false);
    destSettings.setEnvelopeMaxRelease (sourceSettings.getEnvelopeMaxRelease (), false);
    destSettings.setChokeRelease (sourceSettings.getChokeRelease (), false);
    destSettings.setReleaseMode (sourceSettings.getReleaseMode (), false);
    destSettings.setClsdRelOfstScale (sourceSettings.getClsdRelOfstScale (), false);
    destSettings.setClsdMaxRelease (sourceSettings.getClsdMaxRelease (), false);
    destSettings.setAccClRelMod (sourceSettings.getAccClRelMod (), false);
    destSettings.setAccOpRelMod (sourceSettings.getAccOpRelMod (), false);
    destSettings.setAccClAmpMod (sourceSettings.getAccClAmpMod (), false);
    destSettings.setAccOpAmpMod (sourceSettings.getAccOpAmpMod (), false);
    destSettings.setFxCvUnipolar (sourceSettings.getFxCvUnipolar (), false);
    destSettings.setVelocityUnipolar (sourceSettings.getVelocityUnipolar (), false);
    destSettings.setCvDisableVelocity (sourceSettings.getCvDisableVelocity (), false);
    destSettings.setCvDisableFx (sourceSettings.getCvDisableFx (), false);
    destSettings.setGateMode (sourceSettings.getGateMode (), false);
    destSettings.setFeelAttackMod (sourceSettings.getFeelAttackMod (), false);
    destSettings.setFeelReleaseMod (sourceSettings.getFeelReleaseMod (), false);
    destSettings.setFeelAmpMod (sourceSettings.getFeelAmpMod (), false);
    destSettings.setKnobPosTakeup (sourceSettings.getKnobPosTakeup (), false);
    destSettings.setFltrHpfMinFreq (sourceSettings.getFltrHpfMinFreq (), false);
    destSettings.setFltrHpfMaxFreq (sourceSettings.getFltrHpfMaxFreq (), false);
    destSettings.setFltrLpfMinFreq (sourceSettings.getFltrLpfMinFreq (), false);
    destSettings.setFltrLpfMaxFreq (sourceSettings.getFltrLpfMaxFreq (), false);
    destSettings.setFltrHpfQ (sourceSettings.getFltrHpfQ (), false);
    destSettings.setFltrLpfQ (sourceSettings.getFltrLpfQ (), false);
    destSettings.setFxDjfilterHpfMin (sourceSettings.getFxDjfilterHpfMin (), false);
    destSettings.setFxDjfilterHpfMax (sourceSettings.getFxDjfilterHpfMax (), false);
    destSettings.setFxDjfilterLpfMin (sourceSettings.getFxDjfilterLpfMin (), false);
    destSettings.setFxDjfilterLpfMax (sourceSettings.getFxDjfilterLpfMax (), false);
    destSettings.setFxDjfilterQMin (sourceSettings.getFxDjfilterQMin (), false);
    destSettings.setFxDjfilterQMax (sourceSettings.getFxDjfilterQMax (), false);
    destSettings.setFxDjfilterQGainReduction (sourceSettings.getFxDjfilterQGainReduction (), false);
    destSettings.setFxDubEchoTmin (sourceSettings.getFxDubEchoTmin (), false);
    destSettings.setFxDubEchoHpf (sourceSettings.getFxDubEchoHpf (), false);
    destSettings.setFxDubEchoLpf (sourceSettings.getFxDubEchoLpf (), false);
    destSettings.setFxDubEchoMix (sourceSettings.getFxDubEchoMix (), false);
    destSettings.setFxChorusCenter (sourceSettings.getFxChorusCenter (), false);
    destSettings.setFxChorusDepth (sourceSettings.getFxChorusDepth (), false);
    destSettings.setFxChorusMix (sourceSettings.getFxChorusMix (), false);
    destSettings.setFxChorusSpread (sourceSettings.getFxChorusSpread (), false);
    destSettings.setFxChorusTaps (sourceSettings.getFxChorusTaps (), false);
    destSettings.setFxChorusLfoB (sourceSettings.getFxChorusLfoB (), false);
    destSettings.setFxChorusLfoT (sourceSettings.getFxChorusLfoT (), false);
    destSettings.setFxChorusType (sourceSettings.getFxChorusType (), false);
    destSettings.setFxChorusStagger (sourceSettings.getFxChorusStagger (), false);
    destSettings.setFxReverbLpf (sourceSettings.getFxReverbLpf (), false);
    destSettings.setFxReverbHpf (sourceSettings.getFxReverbHpf (), false);
    destSettings.setFxReverbType (sourceSettings.getFxReverbType (), false);
    destSettings.setFxReverbSizeMin (sourceSettings.getFxReverbSizeMin (), false);
    destSettings.setFxReverbSizeMax (sourceSettings.getFxReverbSizeMax (), false);
    destSettings.setFxReverbPredelay (sourceSettings.getFxReverbPredelay (), false);
    destSettings.setFxReverbModDepth (sourceSettings.getFxReverbModDepth (), false);
    destSettings.setFxReverbModRate (sourceSettings.getFxReverbModRate (), false);
    destSettings.setFxReverbDiffusion (sourceSettings.getFxReverbDiffusion (), false);
    destSettings.setFxReverbMix (sourceSettings.getFxReverbMix (), false);
    destSettings.setFxGlitchProbabilityMin (sourceSettings.getFxGlitchProbabilityMin (), false);
    destSettings.setFxGlitchProbabilityMax (sourceSettings.getFxGlitchProbabilityMax (), false);
    destSettings.setFxGlitchWeightHoldLow (sourceSettings.getFxGlitchWeightHoldLow (), false);
    destSettings.setFxGlitchWeightStutterLow (sourceSettings.getFxGlitchWeightStutterLow (), false);
    destSettings.setFxGlitchWeightCrushLow (sourceSettings.getFxGlitchWeightCrushLow (), false);
    destSettings.setFxGlitchWeightDropLow (sourceSettings.getFxGlitchWeightDropLow (), false);
    destSettings.setFxGlitchWeightHoldHigh (sourceSettings.getFxGlitchWeightHoldHigh (), false);
    destSettings.setFxGlitchWeightStutterHigh (sourceSettings.getFxGlitchWeightStutterHigh (), false);
    destSettings.setFxGlitchWeightCrushHigh (sourceSettings.getFxGlitchWeightCrushHigh (), false);
    destSettings.setFxGlitchWeightDropHigh (sourceSettings.getFxGlitchWeightDropHigh (), false);
    destSettings.setFxGlitchDropKeepLevelMin (sourceSettings.getFxGlitchDropKeepLevelMin (), false);
    destSettings.setFxGlitchDropKeepLevelMax (sourceSettings.getFxGlitchDropKeepLevelMax (), false);
    destSettings.setFxGlitchDropKeepTimeMin (sourceSettings.getFxGlitchDropKeepTimeMin (), false);
    destSettings.setFxGlitchDropKeepTimeMax (sourceSettings.getFxGlitchDropKeepTimeMax (), false);
    destSettings.setFxGlitchCrushTimeMin (sourceSettings.getFxGlitchCrushTimeMin (), false);
    destSettings.setFxGlitchCrushTimeMax (sourceSettings.getFxGlitchCrushTimeMax (), false);
    destSettings.setFxGlitchMicroloopSmplTMin (sourceSettings.getFxGlitchMicroloopSmplTMin (), false);
    destSettings.setFxGlitchMicroloopSmplTMax (sourceSettings.getFxGlitchMicroloopSmplTMax (), false);
    destSettings.setFxGlitchMicroloopPlayTMin (sourceSettings.getFxGlitchMicroloopPlayTMin (), false);
    destSettings.setFxGlitchMicroloopPlayTMax (sourceSettings.getFxGlitchMicroloopPlayTMax (), false);
    destSettings.setFxGlitchStutterSmplTMin (sourceSettings.getFxGlitchStutterSmplTMin (), false);
    destSettings.setFxGlitchStutterSmplTMax (sourceSettings.getFxGlitchStutterSmplTMax (), false);
    destSettings.setFxGlitchStutterNumMin (sourceSettings.getFxGlitchStutterNumMin (), false);
    destSettings.setFxGlitchStutterNumMax (sourceSettings.getFxGlitchStutterNumMax (), false);
    destSettings.setFxGlitchStutterWindow (sourceSettings.getFxGlitchStutterWindow (), false);
}

void ProjectManager::copyPatternListProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT)
{
    PatternListProperties sourcePatternList { sourceClutchPropertiesVT, PatternListProperties::WrapperType::client, PatternListProperties::EnableCallbacks::no };
    PatternListProperties destPatternList { destClutchPropertiesVT, PatternListProperties::WrapperType::client, PatternListProperties::EnableCallbacks::no };

    for (auto patternIndex { 0 }; patternIndex < sourcePatternList.getValueTree ().getNumChildren (); ++patternIndex)
    {
        PatternProperties sourcePattern { sourcePatternList.getPatternVT (patternIndex), PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::no };
        PatternProperties destPattern { destPatternList.getPatternVT (patternIndex), PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::no };
        destPattern.setPattern (sourcePattern.getPattern (), false);
    }
}

void ProjectManager::copyEffectListProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT)
{
    EffectListProperties sourceEffectList { sourceClutchPropertiesVT, EffectListProperties::WrapperType::client, EffectListProperties::EnableCallbacks::no };
    EffectListProperties destEffectList { destClutchPropertiesVT, EffectListProperties::WrapperType::client, EffectListProperties::EnableCallbacks::no };

    for (auto effectIndex { 0 }; effectIndex < sourceEffectList.getValueTree ().getNumChildren (); ++effectIndex)
    {
        EffectProperties sourceEffect { sourceEffectList.getEffectVT (effectIndex), EffectProperties::WrapperType::client, EffectProperties::EnableCallbacks::no };
        EffectProperties destEffect { destEffectList.getEffectVT (effectIndex), EffectProperties::WrapperType::client, EffectProperties::EnableCallbacks::no };
        destEffect.setEffect (sourceEffect.getEffect (), false);
    }
}

void ProjectManager::copy (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT)
{
    // copy all the things
    copySettingsProperties (sourceClutchPropertiesVT, destClutchPropertiesVT);
    copyPatternListProperties (sourceClutchPropertiesVT, destClutchPropertiesVT);
    copyEffectListProperties (sourceClutchPropertiesVT, destClutchPropertiesVT);
    copySampleProperties (sourceClutchPropertiesVT, destClutchPropertiesVT, true);
}