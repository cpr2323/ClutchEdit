#pragma once

#include <JuceHeader.h>
#include "../../Clutch/PatternListProperties.h"
#include "../../Utility/CustomComboBox.h"
#include "../../Utility/NoArrowComboBoxLnF.h"

class PatternEditorComponent : public juce::Component
{
public:
    PatternEditorComponent ();
    ~PatternEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    PatternProperties patternProperties;
    std::array<CustomComboBox, 32> stepEditors;
    std::array<juce::ToggleButton, 32> lengthSelectors;
    NoArrowComboBoxLnF noArrowComboBoxLnF;

    void paint (juce::Graphics& g) override;
    void resized () override;
};

class PatternListEditorComponent : public juce::Component
{
public:
    PatternListEditorComponent ();
    ~PatternListEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    PatternListProperties patternListProperties;
    std::array<PatternEditorComponent, 8> patternEditors;

    void paint (juce::Graphics& g) override;
    void resized () override;
};