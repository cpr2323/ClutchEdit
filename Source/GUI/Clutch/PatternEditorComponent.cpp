#include "PatternEditorComponent.h"

constexpr auto kEnabledStepColor { 0.7f };
constexpr auto kDisabledStepColor { 0.1f };

constexpr auto kStepComboBoxHeight { 20 };
constexpr auto kStepComboBoxWidth { 57 };
constexpr auto kSpaceBetweenStepEditors { 2 };

PatternEditorComponent::PatternEditorComponent ()
{
    // create the step numbers at the top of the columns
    for (auto columnIndex { 0 }; columnIndex < stepNumbers.size (); ++columnIndex)
    {
        auto& stepNumber { stepNumbers [columnIndex] };
        stepNumber.setJustificationType (juce::Justification::centredTop);
        stepNumber.setText (juce::String (columnIndex + 1), juce::NotificationType::dontSendNotification);
        addAndMakeVisible (stepNumber);
    }

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
        stepComboBox.onChange = [this] ()
        {
            onPatternUiChanged ();
        };
        addAndMakeVisible (stepComboBox);
    }

    numberOfStepsEditor.setColour (juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.darker (kEnabledStepColor));
    numberOfStepsEditor.setJustification (juce::Justification::centred);
    numberOfStepsEditor.setIndents (0, 0);
    numberOfStepsEditor.onFocusLost = [this] () { updateUiFromLengthChange (numberOfStepsEditor.getText ().getIntValue ()); };
    numberOfStepsEditor.onReturnKey = [this] () { updateUiFromLengthChange (numberOfStepsEditor.getText ().getIntValue ()); };
    numberOfStepsEditor.onTextChange = [this] () { updateUiFromLengthChange (numberOfStepsEditor.getText ().getIntValue ()); };
    addAndMakeVisible (numberOfStepsEditor);
}

PatternEditorComponent::~PatternEditorComponent ()
{
    for (auto& stepComboBox : stepEditors)
        stepComboBox.setLookAndFeel (nullptr);
}

void PatternEditorComponent::init (juce::ValueTree patternVT)
{
    patternProperties.wrap (patternVT, PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::yes);
    patternProperties.onPatternChange = [this] (juce::String) { onPatternDataChanged (); };
    onPatternDataChanged ();
}

void PatternEditorComponent::updateUiFromLengthChange (int length)
{
    numberOfStepsEditor.setText (juce::String (length), juce::NotificationType::dontSendNotification);
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
        stepEditors [stepIndex].setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (stepIndex < length ? kEnabledStepColor : kDisabledStepColor));
}

void PatternEditorComponent::paint (juce::Graphics& g)
{
}

void PatternEditorComponent::resized ()
{
    const auto numberOfStepsWidth { (getHeight () / 2.0f) * 0.75f };
    numberOfStepsEditor.setBounds (0, 23, numberOfStepsWidth, getHeight () / 2);

    const auto initialStepsOffset { numberOfStepsEditor.getRight () };
    auto curButtonX { initialStepsOffset };
    // position the step numbers in the middle/top of each column
    for (auto stepIndex { 0 }; stepIndex < stepNumbers.size () / 2; ++stepIndex)
    {
        auto setStepNumberBounds = [this, &curButtonX] (juce::Label& stepNumber, int yOffset)
        {
            const auto numberWidth { stepNumber.getFont ().getStringWidth (stepNumber.getText ()) };
            const auto halfNumberWidth { numberWidth / 2 };
            stepNumber.setBounds (curButtonX + (kStepComboBoxWidth / 2) - halfNumberWidth, yOffset, numberWidth + 10, 15);
        };

        auto setStepEditorBounds = [this, &curButtonX] (int stepIndex, int yOffset)
        {
            auto comboBox { findChildWithID ("StepComboBox" + juce::String (stepIndex)) };
            comboBox->setBounds (5 + curButtonX, yOffset + 15, kStepComboBoxWidth, kStepComboBoxHeight);
        };

        setStepNumberBounds (stepNumbers [stepIndex], 0);
        setStepNumberBounds (stepNumbers [stepIndex + 16], 35);
        setStepEditorBounds (stepIndex, 0);
        setStepEditorBounds (stepIndex + 16, 35);

        curButtonX += kStepComboBoxWidth + kSpaceBetweenStepEditors;
    }
}

void PatternEditorComponent::onPatternUiChanged ()
{
    const auto patternLength { numberOfStepsEditor.getText ().getIntValue () };
    juce::String patternString;
    for (auto stepIndex { 0 }; stepIndex < patternLength; ++stepIndex)
    {
        if (stepIndex > 0)
            patternString += ",";
        patternString += juce::String (stepEditors [stepIndex].getSelectedId ());
    }
    patternString += (patternString.isNotEmpty () ? "," : "") + juce::String ("0");
    patternProperties.setPattern (patternString, false);
}

void PatternEditorComponent::onPatternDataChanged ()
{
    const auto patternString { patternProperties.getPattern () };
    const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
    {
        if (stepIndex < stepValues.size () - 1)
            stepEditors [stepIndex].setSelectedId (stepValues [stepIndex].getIntValue (), juce::NotificationType::dontSendNotification);
        else
            stepEditors [stepIndex].setSelectedId (1, juce::NotificationType::dontSendNotification);
    }
    const auto patternLength { stepValues.size () - 2 };
    updateUiFromLengthChange (patternLength);
}

