#include "PatternListEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

PatternEditorComponent::PatternEditorComponent ()
{
    for (auto curStepIndex { 0 }; curStepIndex < 32; ++curStepIndex)
    {
        auto& stepComboBox { stepEditors [curStepIndex] };
        stepComboBox.addItem ("10%", 1);
        stepComboBox.addItem ("30%", 2);
        stepComboBox.addItem ("60%", 3);
        stepComboBox.addItem ("80%", 4);
        stepComboBox.addItem ("100%", 5);
        stepComboBox.addItem ("110%", 6);
        stepComboBox.addItem ("125%", 7);
        stepComboBox.addItem ("150%", 8);
        stepComboBox.addItem ("200%", 9);
        stepComboBox.setLookAndFeel (&noArrowComboBoxLnF);
        stepComboBox.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
        stepComboBox.setSelectedId (1);
        stepComboBox.setComponentID ("StepComboBox" + juce::String (curStepIndex));
        addAndMakeVisible (stepComboBox);

        auto& lengthSelector { lengthSelectors [curStepIndex] };
        lengthSelector.setComponentID ("LengthSelector" + juce::String (curStepIndex));
        lengthSelector.setLookAndFeel (&toggleButtonLnF);
        lengthSelector.setRadioGroupId (1, juce::NotificationType::dontSendNotification);
        addAndMakeVisible (lengthSelector);
    }
    auto lengthSelector { dynamic_cast <juce::ToggleButton*> (findChildWithID ("LengthSelector" + juce::String (0))) };
    lengthSelector->setToggleState (true, juce::NotificationType::dontSendNotification);

}

PatternEditorComponent::~PatternEditorComponent ()
{
    for (auto& stepComboBox : stepEditors)
        stepComboBox.setLookAndFeel (nullptr);

    for (auto& lengthSelector : lengthSelectors)
        lengthSelector.setLookAndFeel (nullptr);
}

void PatternEditorComponent::init (juce::ValueTree patternVT)
{
    patternProperties.wrap (patternVT, PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::yes);
}

void PatternEditorComponent::paint (juce::Graphics& g)
{

}

void PatternEditorComponent::resized ()
{
    constexpr auto kStepComboBoxHeight { 20 };
    constexpr auto kStepComboBoxWidth { 57 };
    constexpr auto kSpaceBetweenStepEditors { 2 };
    auto curButtonY { 10 };
    for (auto step { 0 }; step < 32; ++step)
    {
        auto comboBox { findChildWithID ("StepComboBox" + juce::String (step)) };
        comboBox->setBounds (curButtonY, 0, kStepComboBoxWidth, kStepComboBoxHeight);
        curButtonY += kStepComboBoxWidth + kSpaceBetweenStepEditors;

        constexpr auto kWidthOfLegnthSelector { 15 };
        auto lengthSelector { findChildWithID ("LengthSelector" + juce::String (step)) };
        lengthSelector->setBounds (comboBox->getX () + (kStepComboBoxWidth / 2) - (kWidthOfLegnthSelector / 2) - 1, comboBox->getBottom () + 5, kWidthOfLegnthSelector + 3, kWidthOfLegnthSelector);
    }
}

PatternListEditorComponent::PatternListEditorComponent ()
{

    for (auto& patternEditorComponent : patternEditors)
    {
        addAndMakeVisible (patternEditorComponent);
    }
}

PatternListEditorComponent::~PatternListEditorComponent ()
{

}

void PatternListEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    patternListProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("PatternList"), ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::yes);

    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternEditors[patternIndex].init (patternListProperties.getPatternVT (patternIndex));
    }
}

void PatternListEditorComponent::paint (juce::Graphics& g)
{

}

void PatternListEditorComponent::resized ()
{
    constexpr auto kPatternEditorHeight { 60 };
    auto bounds { getLocalBounds ().reduced (5, 5) };
    
    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternEditors [patternIndex].setBounds (0, patternIndex * kPatternEditorHeight, bounds.getWidth (), kPatternEditorHeight);
    }
}
