#include "EffectEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

EffectEditorComponent::EffectEditorComponent ()
{
    for (auto curStepIndex { 0 }; curStepIndex < 8; ++curStepIndex)
    {
        auto& effectEditor { effectEditors [curStepIndex] };
        effectEditor.addItem ("NONE", 1);
        effectEditor.addItem ("BITCRUSH", 2);
        effectEditor.addItem ("CHORUS", 3);
        effectEditor.addItem ("COMBFILTER", 4);
        effectEditor.addItem ("DJFILTER", 5);
        effectEditor.addItem ("DUBECHO", 6);
        effectEditor.addItem ("GLITCH", 7);
        effectEditor.addItem ("REVERB", 8);
        effectEditor.addItem ("SPUTTER", 9);
        effectEditor.setLookAndFeel (&noArrowComboBoxLnF);
        effectEditor.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (0.7f));
        effectEditor.setSelectedId (1);
        effectEditor.setComponentID ("StepComboBox" + juce::String (curStepIndex));
        effectEditor.onChange = [this] ()
        {
            onEffectUiChanged ();
        };
        addAndMakeVisible (effectEditor);
    }

    for (auto effectIndex { 0 }; effectIndex < 8; ++effectIndex)
    {
        const juce::StringArray effectSelectNames { "WHITE", "RED", "ORANGE", "YELLOW", "GREEN", "BLUE", "CYAN", "VIOLET" };
        auto& effectLabel { effectLabels [effectIndex] };
        effectLabel.setText (effectSelectNames [effectIndex], juce::NotificationType::dontSendNotification);
        effectLabel.setJustificationType (juce::Justification::centredLeft);
        addAndMakeVisible (effectLabel);
        auto& effectEditor { effectEditors [effectIndex] };
        effectEditor.setJustificationType (juce::Justification::centredLeft);
        effectEditor.setSelectedId (1);
        addAndMakeVisible (effectEditor);

    }
}

EffectEditorComponent::~EffectEditorComponent ()
{
    for (auto& effectEditor : effectEditors)
        effectEditor.setLookAndFeel (nullptr);
}

void EffectEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    effectListProperties.wrap (clutchProperties.getValueTree (), ValueTreeWrapper<EffectListProperties>::WrapperType::client, ValueTreeWrapper<EffectListProperties>::EnableCallbacks::no);
    effectListProperties.forEachEffect ([this] (juce::ValueTree effectVT, int effectIndex)
    {
        effectProperties [effectIndex].wrap (effectVT, ValueTreeWrapper<EffectProperties>::WrapperType::client, ValueTreeWrapper<EffectProperties>::EnableCallbacks::yes);
        effectProperties [effectIndex].onEffectChange = [this, effectIndex] (juce::String) { onEffectDataChanged (effectIndex); };
        onEffectDataChanged (effectIndex);
        return true;
    });
}

void EffectEditorComponent::paint (juce::Graphics& g)
{

}

void EffectEditorComponent::resized ()
{
    for (auto effectIndex { 0 }; effectIndex < effectEditors.size (); ++effectIndex)
    {
        effectLabels [effectIndex].setBounds (0, effectIndex * 30, 100, 25);
        effectEditors [effectIndex].setBounds (100, effectIndex * 30, 100, 25);
    }
}

void EffectEditorComponent::onEffectUiChanged ()
{
//     const auto patternLength { getPatternLength () };
//     juce::String patternString;
//     for (auto stepIndex { 0 }; stepIndex < patternLength; ++stepIndex)
//     {
//         if (stepIndex > 0)
//             patternString += ",";
//         patternString += juce::String (stepEditors [stepIndex].getSelectedId ());
//     }
//     patternString += (patternString.isNotEmpty () ? "," : "") + juce::String ("0");
//     patternProperties.setPattern (patternString, false);
}

void EffectEditorComponent::onEffectDataChanged (int effectIndex)
{
//     const auto patternString { patternProperties.getPattern () };
//     const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
//     for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
//     {
//         if (stepIndex < stepValues.size () - 1)
//             stepEditors [stepIndex].setSelectedId (stepValues [stepIndex].getIntValue (), juce::NotificationType::dontSendNotification);
//         else
//             stepEditors [stepIndex].setSelectedId (1, juce::NotificationType::dontSendNotification);
//     }
//     const auto patternLength { stepValues.size () - 2 };
//     updateUiFromLengthChange (patternLength);
//     auto lengthSelector { dynamic_cast <juce::ToggleButton*> (findChildWithID ("LengthSelector" + juce::String (patternLength))) };
//     lengthSelector->setToggleState (true, juce::NotificationType::dontSendNotification);
}

