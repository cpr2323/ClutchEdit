#include "PatternEditorComponent.h"
#include "../Theme/UiComponents.h"
#include "../Theme/ClutchLookAndFeel.h"
#include "../../Clutch/HiHatIniKeys.h"

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
        stepNumber.setFont (ClutchType::stepNumber ());
        stepNumber.setText (juce::String (columnIndex + 1), juce::NotificationType::dontSendNotification);
        addAndMakeVisible (stepNumber);
    }

    numberOfStepsEditor.setTooltip ("The number of steps in this pattern. Min 0. Max 32");
    numberOfStepsEditor.getMinValueCallback = [this] () { return 0; };
    numberOfStepsEditor.getMaxValueCallback = [this] () { return 32; };
    numberOfStepsEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    // the length decides both how much of the pattern is drawn as being in use and
    // how many steps the pattern string holds, so a committed length does both
    numberOfStepsEditor.updateDataCallback = [this] (int length) { updateUiFromLengthChange (length); onPatternUiChanged (); };
    numberOfStepsEditor.onDragCallback = [this] (double valueDelta)
    {
        const auto patternString { patternProperties.getPattern () };
        const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
        const auto newValue { (stepValues.size () - 1) + juce::roundToInt (valueDelta) };
        //DebugLog ("CustomTextEditor", "delta: " + juce::String (valueDelta) + ", pattern: " + patternString + ", numStepValues: " + juce::String(stepValues.size ()) + ", newValue: " + juce::String (newValue));
        numberOfStepsEditor.setValue (newValue);
    };
    numberOfStepsEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu pm;
        pm.addSectionHeader ("Pattern " + patternProperties.getId().substring (4));
        pm.addSeparator ();
        juce::PopupMenu lengthOptions;
        lengthOptions.addItem ("Default", true, false, [this] ()
        {
            const auto stepValues { juce::StringArray::fromTokens (defaultPattern, ",", "") };
            numberOfStepsEditor.setValue (stepValues.size () - 1);
        });
        lengthOptions.addItem ("Revert", true, false, [this] ()
        {
            const auto stepValues { juce::StringArray::fromTokens (uneditedPatternProperties.getPattern (), ",", "") };
            numberOfStepsEditor.setValue (stepValues.size () - 1);
        });
        pm.addSubMenu ("Length", lengthOptions, true);
        juce::PopupMenu patternOptions;
        patternOptions.addItem ("Default", true, false, [this] ()
        {
            setPatternFromString (defaultPattern);
        });
        patternOptions.addItem ("Revert", true, false, [this] ()
        {
            setPatternFromString (uneditedPatternProperties.getPattern ());
        });
        pm.addSubMenu ("Length and Step Values", patternOptions, true);
        pm.showMenuAsync ({});
    };

    numberOfStepsEditor.setJustification (juce::Justification::centred);
    numberOfStepsEditor.setIndents (3, 0);
    numberOfStepsEditor.setFont (ClutchType::value ());
    HoverHighlight::attach (numberOfStepsEditor);
    // the editor's own callbacks are left as CustomTextEditor set them: onFocusLost
    // and onReturnKey commit the typed length through updateDataCallback, and
    // onTextChange only marks an out of range value while it is being typed. A
    // half typed length is not written to the pattern, so the steps must not be
    // redrawn for it either - the steps shown as in use are the ones the pattern
    // actually holds, not the ones the field is on its way to asking for
    addAndMakeVisible (numberOfStepsEditor);

    numberOfStepsLabel.setText ("Steps", juce::NotificationType::dontSendNotification);
    numberOfStepsLabel.setJustificationType (juce::Justification::centredTop);
    numberOfStepsLabel.setFont (ClutchType::parameterLabel ());
    addAndMakeVisible (numberOfStepsLabel);

    for (auto curStepIndex { 0 }; curStepIndex < 32; ++curStepIndex)
    {
        auto& stepComboBox { stepEditors [curStepIndex] };

        stepComboBox.setTooltip ("Step " + juce::String (curStepIndex + 1) + " of this FEEL pattern, as a percentage of a normal hit. Steps past the Steps count are unused.");
        stepComboBox.addItem ("10%", 1);
        stepComboBox.addItem ("30%", 2);
        stepComboBox.addItem ("60%", 3);
        stepComboBox.addItem ("80%", 4);
        stepComboBox.addItem ("100%", 5);
        stepComboBox.addItem ("110%", 6);
        stepComboBox.addItem ("125%", 7);
        stepComboBox.addItem ("150%", 8);
        stepComboBox.addItem ("200%", 9);
        // a step is only 57 pixels wide, so it asks for the variation with no
        // caret rather than being given a LookAndFeel - and a palette - of its own
        stepComboBox.getProperties ().set (ClutchLnFProperties::noCaret, true);
        HoverHighlight::attach (stepComboBox);
        stepComboBox.setSelectedId (1);
        stepComboBox.setComponentID ("StepComboBox" + juce::String (curStepIndex));
        stepComboBox.onDragCallback = [this, &stepComboBox] (double valueDelta)
        {
            const auto stepValue { stepComboBox.getSelectedId () };
            stepComboBox.setSelectedId (std::clamp (stepValue + juce::roundToInt (valueDelta), 1, 9), juce::NotificationType::dontSendNotification);
            onPatternUiChanged ();
        };
        stepComboBox.onPopupMenuCallback = [this, curStepIndex, &stepComboBox] ()
        {
            juce::PopupMenu pm;
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
            pm.showMenuAsync ({});
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
}

// Step backgrounds and label inks are colours stored on the controls rather than
// looked up while painting, so they have to be re-applied when the palette changes.
void PatternEditorComponent::applyExplicitColours ()
{
    const auto labelColour { findColour (ClutchColours::textDim) };
    for (auto& stepNumber : stepNumbers)
        stepNumber.setColour (juce::Label::ColourIds::textColourId, labelColour);
    numberOfStepsLabel.setColour (juce::Label::ColourIds::textColourId, labelColour);

    // A step past the end of the pattern is not part of it, so it sinks into the
    // panel and its value is ghosted - the way an unusable field is drawn. It is
    // still editable, though, since setting it is how the pattern is lengthened.
    const auto inPatternBackground { findColour (ClutchColours::fieldBackground) };
    const auto pastEndBackground { findColour (ClutchColours::listBackground) };
    const auto inPatternText { findColour (ClutchColours::text) };
    const auto pastEndText { findColour (ClutchColours::textGhost) };
    for (auto stepIndex { 0 }; stepIndex < static_cast<int> (stepEditors.size ()); ++stepIndex)
    {
        const auto inPattern { stepIndex < stepsInPattern };
        stepEditors [stepIndex].setColour (juce::ComboBox::backgroundColourId, inPattern ? inPatternBackground : pastEndBackground);
        stepEditors [stepIndex].setColour (juce::ComboBox::textColourId, inPattern ? inPatternText : pastEndText);
    }
}

void PatternEditorComponent::lookAndFeelChanged ()
{
    juce::Component::lookAndFeelChanged ();
    applyExplicitColours ();
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
    stepsInPattern = length;
    applyExplicitColours ();
}

void PatternEditorComponent::resized ()
{
    const auto numberOfStepsWidth { static_cast<int>((getHeight () / 2.0f) * 0.75f) };

    // "Steps" is wider than the (narrow) editor, so inset the editor from the
    // left by the label's overhang. This lets the wider label sit centered
    // under the editor without being clipped at the component's left edge.
    const auto stepsLabelWidth { juce::jmax (numberOfStepsWidth,
                                             juce::roundToInt (juce::GlyphArrangement::getStringWidth (numberOfStepsLabel.getFont (), "Steps")) + 8) };
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
            const auto numberWidth { juce::roundToInt (juce::GlyphArrangement::getStringWidth (stepNumber.getFont (), stepNumber.getText ())) };
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
    // the committed length, not whatever the editor is currently showing: a length
    // that is still being typed has not been agreed to, and the steps drawn as in
    // use have not moved for it either. It also indexes the step editors, so it is
    // pinned to the range here
    const auto patternLength { std::clamp (stepsInPattern, 0, static_cast<int> (stepEditors.size ())) };
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
    updateUiFromPatternString (patternProperties.getPattern ());
}

// a whole pattern is replaced by filling the UI in silently and then writing the data
// from it once, rather than leaving the write to whichever step happens to change - a
// replacement that only differs in length changes no step at all
void PatternEditorComponent::setPatternFromString (juce::String patternString)
{
    updateUiFromPatternString (patternString);
    onPatternUiChanged ();
}

void PatternEditorComponent::updateUiFromPatternString (juce::String patternString)
{
    const auto stepValues { juce::StringArray::fromTokens (patternString, ",", "") };
    for (auto stepIndex { 0 }; stepIndex < 32; ++stepIndex)
            stepEditors [stepIndex].setSelectedId (stepIndex < stepValues.size () - 1 ? stepValues [stepIndex].getIntValue () : 1, juce::NotificationType::dontSendNotification);
    const auto patternLength { stepValues.size () - 1 };
    updateUiFromLengthChange (patternLength);
}