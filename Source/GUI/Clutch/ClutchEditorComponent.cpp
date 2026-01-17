#include "ClutchEditorComponent.h"
#include "../../Clutch/HiHatIniData.h"
#include "../../Utility/PersistentRootProperties.h"

void FillInDataFromVt (HiHatData& data, const juce::ValueTree vt);
void FillInVtFromData (juce::ValueTree clutchVt, const HiHatData& data);
extern HiHatData gHiHatData;

ClutchEditorComponent::ClutchEditorComponent ()
{
    editorTabs.addTab ("GLOBAL", juce::Colours::darkgrey, &hiHatEditorComponent, false);
    editorTabs.addTab ("PATTERNS", juce::Colours::darkgrey, &patternListEditorComponent, false);
    editorTabs.addTab ("EFFECTS", juce::Colours::darkgrey, &effectEditorComponent, false);
    editorTabs.addTab ("SAMPLES", juce::Colours::darkgrey, &sampleManagerComponent, false);
    addAndMakeVisible (editorTabs);

    // SETTINGS BUTTON
    settingsButton.setButtonText ("SETTINGS");
    settingsButton.onClick = [this] ()
    {
        audioPlayerProperties.showConfigDialog (false);
    };
    addAndMakeVisible (settingsButton);

    // OPEN BUTTON
    openButton.setButtonText ("OPEN");
    openButton.onClick = [this] ()
    {
        fileChooser.reset (new juce::FileChooser ("Please select the Clutch HIHAT.INI file you want to edit...", {}, "*.INI;*.*"));
        fileChooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles , [this] (const juce::FileChooser& fc) mutable
        {
            if (fc.getURLResults ().size () == 1 && fc.getURLResults () [0].isLocalFile ())
            {
                auto urlResult { fc.getURLResults () [0] };
                juce::File fileToLoad (urlResult.getLocalFile ().getFullPathName ());
                if (fileToLoad.isDirectory ())
                    return;
                // TODO - need to reset gHiHatData to default state before reading from file
                gHiHatData.readFromFile (fileToLoad);
                FillInVtFromData (clutchProperties.getValueTree (), gHiHatData);
                appProperties.setMostRecentFolder (fc.getURLResults () [0].getLocalFile ().getParentDirectory ().getFullPathName ());
                appProperties.addRecentlyUsedFile(fc.getURLResults () [0].getLocalFile ().getFullPathName ());
            }
        }, nullptr);
    };
    addAndMakeVisible (openButton);

    // SAVE BUTTON
    saveButton.setButtonText ("SAVE");
    //saveButton.setEnabled (false); // TODO: do this when the edit compare functionallity is working
    saveButton.onClick = [this] ()
    {
        FillInDataFromVt (gHiHatData, clutchProperties.getValueTreeRef ());
        gHiHatData.writeToFile (appProperties.getRecentlyUsedFile(0));
    };
    addAndMakeVisible (saveButton);
}

ClutchEditorComponent::~ClutchEditorComponent ()
{
}

void ClutchEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::owner, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::owner, AppProperties::EnableCallbacks::yes);
    runtimeRootProperties.wrap (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    audioPlayerProperties.wrap (runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::client, AudioPlayerProperties::EnableCallbacks::no);
    clutchProperties.wrap (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    // TODO pass in the clutch VT directly instead of root VT
    hiHatEditorComponent.init (rootPropertiesVT);
    patternListEditorComponent.init (rootPropertiesVT);
    effectEditorComponent.init (rootPropertiesVT);
    sampleManagerComponent.init (rootPropertiesVT);
}

void ClutchEditorComponent::resized()
{
    auto bounds { getLocalBounds () };
    auto topLine { bounds.removeFromTop (30) };
    settingsButton.setBounds (topLine.removeFromRight (100).reduced (5));
    saveButton.setBounds (topLine.removeFromRight (100).reduced (5));
    openButton.setBounds (topLine.removeFromRight (100).reduced (5));
    editorTabs.setBounds (getLocalBounds ());
}

void ClutchEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey.darker(0.7f));
}