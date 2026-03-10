#pragma once

#include <JuceHeader.h>
#include "../../Clutch/PatternProperties.h"
#include "../../Utility/CustomComboBox.h"
#include "../../Utility/CustomTextEditor.h"
#include "../../Utility/NoArrowComboBoxLnF.h"

class ToggleButtonLnF : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton (juce::Graphics& g, juce::ToggleButton& button, [[maybe_unused]] bool shouldDrawButtonAsHighlighted, [[maybe_unused]] bool shouldDrawButtonAsDown)
    {
        juce::Rectangle<float> tickBounds (button.getLocalBounds ().toFloat ());

        g.setColour (button.findColour (juce::ToggleButton::tickDisabledColourId));
        g.drawEllipse (tickBounds, 1.0f);

        if (button.getToggleState ())
        {
            g.setColour (button.findColour (juce::ToggleButton::tickColourId));
            g.fillEllipse (tickBounds.reduced (2.0f));
        }
    }
};

class PatternEditorComponent : public juce::Component
{
public:
    PatternEditorComponent ();
    ~PatternEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT, juce::ValueTree uneditedPatterPropertiesVT);
    void updateUiFromLengthChange (int length);

private:
    PatternProperties patternProperties;
    PatternProperties uneditedPatternProperties;

    CustomTextEditorInt numberOfStepsEditor;
    std::array<CustomComboBox, 32> stepEditors;
    std::array<juce::Label, 32> stepNumbers;

    NoArrowComboBoxLnF noArrowComboBoxLnF;
    ToggleButtonLnF toggleButtonLnF;

    juce::String defaultPattern;

    void onPatternUiChanged ();
    void onPatternDataChanged ();
    void updateUiFromPatternString (juce::String patternString, bool haveUiSendNotification);

    void resized () override;
};
