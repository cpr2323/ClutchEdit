#include "PatternListEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

constexpr auto kEnabledStepColor { 0.7f };
constexpr auto kDisabledStepColor { 0.1f };

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
        stepComboBox.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (curStepIndex == 0 ? kEnabledStepColor : kDisabledStepColor));
        stepComboBox.setSelectedId (1);
        stepComboBox.setComponentID ("StepComboBox" + juce::String (curStepIndex));
        addAndMakeVisible (stepComboBox);

        auto& lengthSelector { lengthSelectors [curStepIndex] };
        lengthSelector.setComponentID ("LengthSelector" + juce::String (curStepIndex));
        lengthSelector.setLookAndFeel (&toggleButtonLnF);
        lengthSelector.setRadioGroupId (1, juce::NotificationType::dontSendNotification);
        lengthSelector.onClick = [this, curStepIndex] ()
        {
            setLength (curStepIndex);
        };
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
    const auto patternString { patternProperties.getPattern () };
    const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
    {
        if (stepIndex < stepValues.size () - 1)
            stepEditors [stepIndex].setSelectedId (stepValues [stepIndex].getIntValue (), juce::NotificationType::dontSendNotification);
        else
            stepEditors [stepIndex].setSelectedId (1, juce::NotificationType::dontSendNotification);
    }
    setLength (stepValues.size () - 2);
    const auto patternLength { stepValues.size () - 1 };
    auto lengthSelector { dynamic_cast <juce::ToggleButton*> (findChildWithID ("LengthSelector" + juce::String (patternLength - 1))) };
    lengthSelector->setToggleState (true, juce::NotificationType::dontSendNotification);
}

void PatternEditorComponent::setLength (int length)
{
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
        stepEditors [stepIndex].setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (stepIndex <= length ? kEnabledStepColor : kDisabledStepColor));
}

void PatternEditorComponent::paint (juce::Graphics& g)
{

}

std::vector<float> PatternEditorComponent::getColumnCenters()
{
    constexpr auto kStepComboBoxHeight { 20 };
    constexpr auto kStepComboBoxWidth { 57 };
    constexpr auto kSpaceBetweenStepEditors { 2 };
    auto curButtonX { 10 };
    std::vector<float> centers;
    for (auto step { 0 }; step < 32; ++step)
    {
        centers.push_back (curButtonX + (kStepComboBoxWidth / 2));
        curButtonX += kStepComboBoxWidth + kSpaceBetweenStepEditors;
    }

    return centers;
}

void PatternEditorComponent::resized ()
{
    constexpr auto kStepComboBoxHeight { 20 };
    constexpr auto kStepComboBoxWidth { 57 };
    constexpr auto kSpaceBetweenStepEditors { 2 };
    auto curButtonX { 10 };
    for (auto step { 0 }; step < 32; ++step)
    {
        auto comboBox { findChildWithID ("StepComboBox" + juce::String (step)) };
        comboBox->setBounds (curButtonX, 0, kStepComboBoxWidth, kStepComboBoxHeight);
        curButtonX += kStepComboBoxWidth + kSpaceBetweenStepEditors;

        constexpr auto kWidthOfLegnthSelector { 15 };
        auto lengthSelector { findChildWithID ("LengthSelector" + juce::String (step)) };
        lengthSelector->setBounds (comboBox->getX () + (kStepComboBoxWidth / 2) - (kWidthOfLegnthSelector / 2) - 1, comboBox->getBottom () + 5, kWidthOfLegnthSelector + 3, kWidthOfLegnthSelector);
    }
}

PatternListEditorComponent::PatternListEditorComponent ()
{
    std::array<juce::String, 8> patternIds
    {
        "WHITE",
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "BLUE",
        "CYAN",
        "VIOLET"
    };

    for (auto columnIndex { 0 }; columnIndex < stepNumbers.size (); ++columnIndex)
    {
        auto& stepNumber { stepNumbers [columnIndex] };
        stepNumber.setJustificationType (juce::Justification::centred);
        stepNumber.setText (juce::String (columnIndex + 1), juce::NotificationType::dontSendNotification);
        addAndMakeVisible (stepNumber);
    }
    for (auto patternIndex { 0 }; patternIndex < patternLabels.size (); ++patternIndex)
    {
        addAndMakeVisible (patternEditors [patternIndex]);

        auto& patternLabel { patternLabels [patternIndex] };
        patternLabel.setColour (juce::Label::textColourId, juce::Colours::white);
        patternLabel.setText (patternIds [patternIndex], juce::NotificationType::dontSendNotification);
        patternLabel.setJustificationType (juce::Justification::topLeft);
        addAndMakeVisible (patternLabel);
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
//     g.setColour (juce::Colours::red);
//     for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
//     {
//         g.drawRect (patternLabels [patternIndex].getBounds ());
//     }
}

void PatternListEditorComponent::resized ()
{
    constexpr auto kInitialYOffset { 25 };
    constexpr auto kInitialXOffset { 55 };
    constexpr auto kPatternEditorHeight { 60 };
    auto bounds { getLocalBounds ().reduced (5, 5) };
    
    auto columnCenters { patternEditors [0].getColumnCenters () };
    for (auto columnIndex { 0 }; columnIndex < stepNumbers.size (); ++columnIndex)
    {
        auto& stepNumber { stepNumbers [columnIndex] };
        auto numberWidth { stepNumber.getFont ().getStringWidth (stepNumber.getText ()) };
        auto halfNumberWidth { numberWidth / 2 };
        stepNumber.setBounds (kInitialXOffset + (columnCenters [columnIndex] - halfNumberWidth) - 5, 0, numberWidth + 10, 20);
    }
    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternLabels [patternIndex].setBounds (0, kInitialYOffset + (patternIndex * kPatternEditorHeight), kInitialXOffset, kPatternEditorHeight);
        patternEditors [patternIndex].setBounds (kInitialXOffset, kInitialYOffset + (patternIndex * kPatternEditorHeight), bounds.getWidth (), kPatternEditorHeight);
    }
}
