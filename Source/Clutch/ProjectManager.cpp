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
    projectManagerProperties.onSaveProject = [this] ()
    {
        saveProject ();
    };
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

    copySamplePropertiesExistsFlags (unEditedClutchProperties.getValueTree (), editedClutchProperties.getValueTree ());
}

void ProjectManager::copySamplePropertiesExistsFlags (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT)
{
        // copy unedited bank list properties to edited bank list properties so that they can be edited
    BankListProperties sourceBankListProperties { sourceClutchPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    BankListProperties destBankListProperties { destClutchPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };

    // copy the exist flag in the SampleProperties for each sample from the unEditedBankListProperties to sample sample in the editedBankListProperties
    sourceBankListProperties.forEachBank ([&] (juce::ValueTree sourceBankVT, int bankIndex)
    {
        auto destBankVT = destBankListProperties.getBankVT (bankIndex);
        BankProperties sourceBank { sourceBankVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };
        BankProperties destBank { destBankVT, BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no };

        sourceBank.forEachSamplePair ([&destBank] (juce::ValueTree sourceSamplePairVT, int samplePairIndex)
        {
            auto destSamplePairVT { destBank.getSamplePairVT (samplePairIndex) };
            SamplePairProperties sourceSamplePair { sourceSamplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };
            SamplePairProperties destSamplePair { destSamplePairVT, SamplePairProperties::WrapperType::client, SamplePairProperties::EnableCallbacks::no };

            // open sample
            SampleProperties sourceOpenProperties { sourceSamplePair.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties destOpenProperties { destSamplePair.getOpenSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            destOpenProperties.setExists (sourceOpenProperties.getExists (), false);

            // closed sample
            SampleProperties sourceClosedProperties { sourceSamplePair.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            SampleProperties destClosedProperties { destSamplePair.getClosedSampleVT (), SampleProperties::WrapperType::client, SampleProperties::EnableCallbacks::no };
            destClosedProperties.setExists (sourceClosedProperties.getExists (), false);

            return true;
        });

        return true;
    });
}

void ProjectManager::saveProject ()
{
    // copy the data from the edited properties into the HiHatIniData object, and write it back out to the file
    hiHatIniData.FillInDataFromProperties (editedClutchProperties.getValueTreeRef ());
    hiHatIniData.writeToFile (appProperties.getRecentlyUsedFile (0));

    // copy the edited data to the unedited properties, to get them back into sync
    // NOTE: I am copying from the data, instead of the other properties, because this function is already doing the work
    //       I would like to eventually change it to copy from the properties
    hiHatIniData.FillInPropertiesFromData (unEditedClutchProperties.getValueTree ());
    copySamplePropertiesExistsFlags (editedClutchProperties.getValueTree (), unEditedClutchProperties.getValueTree ());
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
