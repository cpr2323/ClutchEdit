#include "ProjectManager.h"
#include "BankListProperties.h"
#include "BankProperties.h"
#include "HiHatIniData.h"
#include "SamplePairProperties.h"
#include "SampleProperties.h"
#include "../AppProperties.h"
#include "../Utility/RuntimeRootProperties.h"
#include "../Utility/PersistentRootProperties.h"

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

    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    projectManagerProperties.wrap (runtimeRootProperties.getValueTree(), ProjectManagerProperties::WrapperType::owner, ProjectManagerProperties::EnableCallbacks::yes);
    unEditedClutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    editedClutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "edited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);

    openProject (appProperties.getRecentlyUsedFile (0));

    startTimer (2000);
}

void ProjectManager::openProject (const juce::File& hiHatIniFile)
{
    if (hiHatIniFile.existsAsFile ())
    {
        hiHatIniData.readFromFile (hiHatIniFile);
        hiHatIniData.FillInPropertiesFromData (unEditedClutchProperties.getValueTree ());
        hiHatIniData.FillInPropertiesFromData (editedClutchProperties.getValueTree ());
    }

    auto bankParentFolder { hiHatIniFile.getParentDirectory () };
    // create bank list properties on the unedited branch, so we can track sample changes
    scanSamples (unEditedClutchProperties.getValueTree ());

    // copy unedited bank list properties to edited bank list properties so that they can be edited
    BankListProperties unEditedBankListProperties { unEditedClutchProperties.getValueTree (), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    BankListProperties editedBankListProperties { editedClutchProperties.getValueTree (), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };

    // copy the exist flag in the SampleProperties for each sample from the unEditedBankListProperties to sample sample in the editedBankListProperties
    unEditedBankListProperties.forEachBank ([&] (juce::ValueTree unEditedBankVT, int bankIndex)
    {
        auto editedBankVT = editedBankListProperties.getBankVT (bankIndex);
        BankProperties unEditedBank { unEditedBankVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        BankProperties editedBank { editedBankVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };

        unEditedBank.forEachSamplePair ([&] (juce::ValueTree unEditedSamplePairVT, int samplePairIndex)
        {
            auto editedSamplePairVT = editedBank.getSamplePairVT (samplePairIndex);
            SamplePairProperties unEditedSamplePair { unEditedSamplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
            SamplePairProperties editedSamplePair { editedSamplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };

            // open sample
            SampleProperties unEditedOpen { unEditedSamplePair.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties editedOpen { editedSamplePair.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            editedOpen.setExists (unEditedOpen.getExists (), false);

            // closed sample
            SampleProperties unEditedClosed { unEditedSamplePair.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties editedClosed { editedSamplePair.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            editedClosed.setExists (unEditedClosed.getExists (), false);

            return true;
        });

        return true;
    });
}

void ProjectManager::saveProject ()
{
    hiHatIniData.FillInDataFromProperties (editedClutchProperties.getValueTreeRef ());
    hiHatIniData.writeToFile (appProperties.getRecentlyUsedFile (0));
}

void ProjectManager::scanSamples (juce::ValueTree clutchPropertiesVT)
{
    auto bankParentFolder { juce::File (appProperties.getMostRecentFolder ()) };
    BankListProperties bankListProperties { clutchPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    bankListProperties.forEachBank ([bankParentFolder] (juce::ValueTree bankPropertiesVT, int bankIndex)
    {
        BankProperties bankProperties { bankPropertiesVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        bankProperties.forEachSamplePair ([bankParentFolder, bankName = bankProperties.getName ()] (juce::ValueTree samplePairVT, int samplePairIndex)
        {
            // check for file and update exists
            SamplePairProperties samplePairProperties { samplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
            auto checkSampleExistence = [sampleBankFolder = bankParentFolder.getChildFile (bankName)] (juce::ValueTree samplePropertiesVT)
            {
                SampleProperties sampleProperties { samplePropertiesVT, SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
                sampleProperties.setExists (sampleBankFolder.getChildFile (sampleProperties.getFilename ()).withFileExtension ("wav").existsAsFile (), false);
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
    scanSamples (editedClutchProperties.getValueTree ());
}
