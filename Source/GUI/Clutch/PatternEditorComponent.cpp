#include "PatternEditorComponent.h"
#include "../../Clutch/HiHatIniKeys.h"

constexpr auto kEnabledStepColor { 0.8f };
constexpr auto kDisabledStepColor { 0.15f };

constexpr auto kStepComboBoxHeight { 20 };
constexpr auto kStepComboBoxWidth { 57 };
constexpr auto kSpaceBetweenStepEditors { 2 };

static const std::array<std::pair<const juce::String, const juce::String>, 8> gDefaultPatterns
{{
    { kPtnWhiteKey,  "6, 5, 7, 5, 0" },
    { kPtnRedKey,    "6, 5, 5, 7, 5, 6, 5, 6, 4, 0" },
    { kPtnGreenKey,  "4, 3, 6, 3, 4, 7, 1, 2, 6, 4, 3, 6, 3, 6, 4, 5, 0" },
    { kPtnBlueKey,   "5, 2, 3, 5, 1, 5, 1, 0" },
    { kPtnOrangeKey, "3, 2, 8, 5, 2, 6, 2, 2, 0" },
    { kPtnCyanKey,   "5, 5, 5, 7, 0" },
    { kPtnVioletKey, "5, 4, 5, 5, 9, 5, 5, 4, 5, 5, 7, 4, 6, 4, 5, 3, 0" },
    { kPtnYellowKey, "7, 3, 5, 7, 3, 5, 2, 5, 7, 3, 5, 3, 2, 8, 3, 2, 0" }
}};

PatternEditorComponent::PatternEditorComponent ()
{
    // create the step numbers at the top of the columns
    for (auto columnIndex { 0 }; columnIndex < stepNumbers.size (); ++columnIndex)
    {
        auto& stepNumber { stepNumbers [columnIndex] };
        stepNumber.setJustificationType (juce::Justification::centredTop);
        stepNumber.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white.darker (0.4f));
        stepNumber.setText (juce::String (columnIndex + 1), juce::NotificationType::dontSendNotification);
        addAndMakeVisible (stepNumber);
    }

    numberOfStepsEditor.setTooltip ("The number of steps in this pattern. Min 0. Max 32");
    numberOfStepsEditor.getMinValueCallback = [this] () { return 0; };
    numberOfStepsEditor.getMaxValueCallback = [this] () { return 32; };
    numberOfStepsEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    numberOfStepsEditor.updateDataCallback = [this] ([[maybe_unused]] int value) { onPatternUiChanged (); };
    numberOfStepsEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 2;
            else
                return 3;
        } ();
        const auto patternString { patternProperties.getPattern () };
        const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
        const auto newValue { (stepValues.size () - 1) + (multiplier * direction)};
        //DebugLog ("CustomTextEditor", "mult: " + juce::String (multiplier) + ", pattern: " + patternString + ", numStepValues: " + juce::String(stepValues.size ()) + ", newValue: " + juce::String (newValue));
        numberOfStepsEditor.setValue (newValue);
    };
    numberOfStepsEditor.onPopupMenuCallback = [this] ()
    {
        auto* popupMenuLnF { new juce::LookAndFeel_V4 };
        popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));
        juce::PopupMenu pm;
        pm.setLookAndFeel (popupMenuLnF);
        pm.addSectionHeader ("Pattern " + patternProperties.getId().substring (4));
        pm.addSeparator ();
        juce::PopupMenu lengthOptions;
        lengthOptions.addItem ("Default", true, false, [this] ()
        {
            const auto stepValues { juce::StringArray::fromTokens (defaultPattern, ",", "") };
            numberOfStepsEditor.setText (juce::String (stepValues.size () - 1), juce::NotificationType::sendNotification);
        });
        lengthOptions.addItem ("Revert", true, false, [this] ()
        {
            const auto pattern { uneditedPatternProperties.getPattern () };
            const auto stepValues { juce::StringArray::fromTokens (pattern, ",", "") };
            numberOfStepsEditor.setText (juce::String (stepValues.size () - 1), juce::NotificationType::sendNotification);
        });
        pm.addSubMenu ("Length", lengthOptions, true);
        juce::PopupMenu patternOptions;
        patternOptions.addItem ("Default", true, false, [this] ()
        {
            updateUiFromPatternString (defaultPattern, true);
        });
        patternOptions.addItem ("Revert", true, false, [this] ()
        {
            updateUiFromPatternString (uneditedPatternProperties.getPattern (), true);
        });
        pm.addSubMenu ("Length and Step Values", patternOptions, true);
        pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
    };

    numberOfStepsEditor.setColour (juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.darker (kEnabledStepColor));
    numberOfStepsEditor.setJustification (juce::Justification::centred);
    numberOfStepsEditor.setIndents (3, 0);
    numberOfStepsEditor.setFont (numberOfStepsEditor.getFont ().withPointHeight (numberOfStepsEditor.getFont ().getHeightInPoints () + 3));
    numberOfStepsEditor.onFocusLost = [this] () { updateUiFromLengthChange (numberOfStepsEditor.getText ().getIntValue ()); };
    numberOfStepsEditor.onReturnKey = [this] () { updateUiFromLengthChange (numberOfStepsEditor.getText ().getIntValue ()); };
    numberOfStepsEditor.onTextChange = [this] () { updateUiFromLengthChange (numberOfStepsEditor.getText ().getIntValue ()); };
    addAndMakeVisible (numberOfStepsEditor);

    numberOfStepsLabel.setText ("Steps", juce::NotificationType::dontSendNotification);
    numberOfStepsLabel.setJustificationType (juce::Justification::centredTop);
    numberOfStepsLabel.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white.darker (0.4f));
    addAndMakeVisible (numberOfStepsLabel);

    for (auto curStepIndex { 0 }; curStepIndex < 32; ++curStepIndex)
    {
        auto& stepComboBox { stepEditors [curStepIndex] };

        stepComboBox.setTooltip ("");
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
        stepComboBox.onDragCallback = [this, &stepComboBox] (DragSpeed dragSpeed, int direction)
        {
            const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
            const auto stepValue { stepComboBox.getSelectedId () };
            stepComboBox.setSelectedId (std::clamp (stepValue + scrollAmount, 1, 9), juce::NotificationType::dontSendNotification);
            onPatternUiChanged ();
        };
        stepComboBox.onPopupMenuCallback = [this, curStepIndex, &stepComboBox] ()
        {
            auto* popupMenuLnF { new juce::LookAndFeel_V4 };
            popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));

            juce::PopupMenu pm;
            pm.setLookAndFeel (popupMenuLnF);
            pm.addSectionHeader ("Step " + juce::String(curStepIndex + 1));
            pm.addSeparator ();
            pm.addItem ("Default", true, false, [&stepComboBox] ()
            {
                stepComboBox.setSelectedId (1, juce::NotificationType::sendNotification);
            });
            pm.addItem ("Revert", true, false, [this, &stepComboBox, curStepIndex, &pm] ()
            {
                const auto patternString { uneditedPatternProperties.getPattern () };
                const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
                jassert (curStepIndex < stepValues.size () - 1);
                stepComboBox.setSelectedId (stepValues[curStepIndex].getIntValue (), juce::NotificationType::sendNotification);
            });
            pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
        };
        stepComboBox.onChange = [this] ()
        {
            onPatternUiChanged ();
        };
        addAndMakeVisible (stepComboBox);
    }
}

PatternEditorComponent::~PatternEditorComponent ()
{
    for (auto& stepComboBox : stepEditors)
        stepComboBox.setLookAndFeel (nullptr);
}

void PatternEditorComponent::init (juce::ValueTree patternVT, juce::ValueTree uneditedPatterPropertiesVT)
{
    uneditedPatternProperties.wrap (uneditedPatterPropertiesVT, PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::yes);
    patternProperties.wrap (patternVT, PatternProperties::WrapperType::client, PatternProperties::EnableCallbacks::yes);
    patternProperties.onPatternChange = [this] (juce::String) { onPatternDataChanged (); };
    onPatternDataChanged ();
    [[maybe_unused]] const auto defaultPatternFound = [this, patternKey { patternProperties.getId () }] ()
    {
        for (const auto& curDefaultPattern : gDefaultPatterns)
        {
            if (curDefaultPattern.first == patternKey)
            {
                defaultPattern = curDefaultPattern.second;
                return true;
            }
        }
        return false;
    } ();
    jassert (defaultPatternFound == true);
}

void PatternEditorComponent::updateUiFromLengthChange (int length)
{
    numberOfStepsEditor.setText (juce::String (length), juce::NotificationType::dontSendNotification);
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
        stepEditors [stepIndex].setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (stepIndex < length ? kEnabledStepColor : kDisabledStepColor));
}

void PatternEditorComponent::resized ()
{
    const auto numberOfStepsWidth { static_cast<int>((getHeight () / 2.0f) * 0.75f) };

    // "Steps" is wider than the (narrow) editor, so inset the editor from the
    // left by the label's overhang. This lets the wider label sit centered
    // under the editor without being clipped at the component's left edge.
    const auto stepsLabelWidth { juce::jmax (numberOfStepsWidth,
                                             numberOfStepsLabel.getFont ().getStringWidth ("Steps") + 8) };
    const auto numberOfStepsX { juce::jmax (0, (stepsLabelWidth - numberOfStepsWidth) / 2) };

    numberOfStepsEditor.setBounds (numberOfStepsX, 21, numberOfStepsWidth, getHeight () / 2);
    numberOfStepsLabel.setBounds (numberOfStepsEditor.getX () + (numberOfStepsWidth - stepsLabelWidth) / 2,
                                  numberOfStepsEditor.getBottom (), stepsLabelWidth, 15);

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
    //DebugLog ("PatternEditorComponent::onPatternUiChanged", "patternLength: " + juce::String(patternLength));
    juce::String patternString;
    for (auto stepIndex { 0 }; stepIndex < patternLength; ++stepIndex)
        patternString += (stepIndex > 0 ? "," : "") + juce::String (stepEditors [stepIndex].getSelectedId ());
    patternString += (patternString.isNotEmpty () ? "," : "") + juce::String ("0");
    patternProperties.setPattern (patternString, false);
    //DebugLog ("PatternEditorComponent::onPatternUiChanged", "patternString: " + patternString);
}

void PatternEditorComponent::onPatternDataChanged ()
{
    updateUiFromPatternString (patternProperties.getPattern (), false);
}

void PatternEditorComponent::updateUiFromPatternString (juce::String patternString, bool haveUiSendNotification)
{
    const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
    const auto notificationType { haveUiSendNotification ? juce::NotificationType::sendNotification : juce::NotificationType::dontSendNotification };
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
            stepEditors [stepIndex].setSelectedId (stepIndex < stepValues.size () - 1 ? stepValues [stepIndex].getIntValue () : 1, notificationType);
    const auto patternLength { stepValues.size () - 1 };
    updateUiFromLengthChange (patternLength);
}