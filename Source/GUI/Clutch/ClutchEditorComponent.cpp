#include "ClutchEditorComponent.h"
#include "../../Clutch/HiHatIniData.h"
#include "../../Utility/RuntimeRootProperties.h"

void FillInDataFromVt (HiHatData& data, const juce::ValueTree vt);
extern HiHatData gHiHatData;

ClutchEditorComponent::ClutchEditorComponent ()
{
    // SAVE BUTTON
    saveButton.setButtonText ("SAVE");
    //saveButton.setEnabled (false);
    saveButton.onClick = [this] ()
    {
        HiHatProperties hihatProperties { clutchProperties.getValueTree ().getChildWithName (HiHatProperties::HiHatTypeId),
                                          ValueTreeWrapper<HiHatProperties>::WrapperType::client, ValueTreeWrapper<HiHatProperties>::EnableCallbacks::no };
        FillInDataFromVt (gHiHatData, hihatProperties.getValueTreeRef ());
        gHiHatData.writeToFile (juce::File::getCurrentWorkingDirectory ().getChildFile ("HIHAT_edit.INI"));
    };
    addAndMakeVisible (saveButton);

    addAndMakeVisible (hiHatEditorComponent);
}

ClutchEditorComponent::~ClutchEditorComponent ()
{
}

void ClutchEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    clutchProperties.wrap (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    hiHatEditorComponent.init (rootPropertiesVT);
}

void ClutchEditorComponent::resized()
{
    auto bounds { getLocalBounds () };
    auto topLine { bounds.removeFromTop (30) };
    saveButton.setBounds (topLine.removeFromRight (100).reduced (5));
    hiHatEditorComponent.setBounds (bounds);
}

void ClutchEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey.darker(0.7f));
}