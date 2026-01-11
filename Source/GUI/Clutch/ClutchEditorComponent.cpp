#include "ClutchEditorComponent.h"
#include "../../Clutch/HiHatIniData.h"

void FillInDataFromVt (HiHatData& data, const juce::ValueTree vt);
extern HiHatData gHiHatData;

ClutchEditorComponent::ClutchEditorComponent ()
{
    editorTabs.addTab ("GLOBAL", juce::Colours::darkgrey, &hiHatEditorComponent, false);
    editorTabs.addTab ("PATTERNS", juce::Colours::darkgrey, &patternListEditorComponent, false);
    editorTabs.addTab ("EFFECTS", juce::Colours::darkgrey, &effectEditorComponent, false);
    editorTabs.addTab ("SAMPLES", juce::Colours::darkgrey, &sampleManagerComponent, false);
    addAndMakeVisible (editorTabs);

    // SAVE BUTTON
    saveButton.setButtonText ("SAVE");
    //saveButton.setEnabled (false);
    saveButton.onClick = [this] ()
    {
        FillInDataFromVt (gHiHatData, clutchProperties.getValueTreeRef ());
        auto appDataPath = juce::File (runtimeRootProperties.getAppDataPath ()).getChildFile ("sdcard_test");
        gHiHatData.writeToFile (appDataPath.getChildFile ("HIHAT_edit.INI"));
    };
    addAndMakeVisible (saveButton);
}

ClutchEditorComponent::~ClutchEditorComponent ()
{
}

void ClutchEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    runtimeRootProperties.wrap (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
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
    saveButton.setBounds (topLine.removeFromRight (100).reduced (5));
    editorTabs.setBounds (getLocalBounds ());
}

void ClutchEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey.darker(0.7f));
}