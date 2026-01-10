#pragma once

#include <JuceHeader.h>
#include "../../Clutch/PatternListProperties.h"
#include "../../Utility/CustomComboBox.h"
#include "../../Utility/NoArrowComboBoxLnF.h"

class ToggleButtonLnF : public juce::LookAndFeel_V4
{
public:
    void drawToggleButton (juce::Graphics& g, juce::ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
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

    void init (juce::ValueTree rootPropertiesVT);
    void updateUiFromLengthChange (int length);
    std::vector<float> getColumnCenters ();

private:
    PatternProperties patternProperties;
    std::array<CustomComboBox, 32> stepEditors;
    std::array<juce::ToggleButton, 32> lengthSelectors;
    NoArrowComboBoxLnF noArrowComboBoxLnF;
    ToggleButtonLnF toggleButtonLnF;

    int getPatternLength ();
    void onPatternUiChanged ();
    void onPatternDataChanged ();

    void paint (juce::Graphics& g) override;
    void resized () override;
};
