#pragma once

#include <JuceHeader.h>
#include "../../Clutch/PatternListProperties.h"
#include "../../Utility/CustomComboBox.h"
#include "../../Utility/NoArrowComboBoxLnF.h"

class PatternListEditorComponent : public juce::Component
{
public:
    PatternListEditorComponent ();
    ~PatternListEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    PatternListProperties patternListProperties;
    int curPatternIndex { 0 };
    std::array<CustomComboBox, 32> stepEditor;
    NoArrowComboBoxLnF noArrowComboBoxLnF;

    void paint (juce::Graphics& g) override;
    void resized () override;
};