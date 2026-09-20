#pragma once

#include <JuceHeader.h>
#include "../../Clutch/PatternProperties.h"
#include "oolib/GUI/CustomComboBox.h"
#include "oolib/GUI/CustomTextEditor.h"

class PatternEditorComponent : public juce::Component
{
public:
    PatternEditorComponent ();
    ~PatternEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT, juce::ValueTree uneditedPatterPropertiesVT);

private:
    PatternProperties patternProperties;
    PatternProperties uneditedPatternProperties;

    CustomTextEditorInt numberOfStepsEditor;
    juce::Label numberOfStepsLabel;
    std::array<CustomComboBox, 32> stepEditors;
    std::array<juce::Label, 32> stepNumbers;

    juce::String defaultPattern;
    // steps beyond this are drawn as not part of the pattern
    int stepsInPattern { 0 };

    void onPatternUiChanged ();
    void onPatternDataChanged ();
    void updateUiFromLengthChange (int length);
    void setPatternFromString (juce::String patternString);
    void updateUiFromPatternString (juce::String patternString);
    void applyExplicitColours ();

    void lookAndFeelChanged () override;
    void resized () override;
};
