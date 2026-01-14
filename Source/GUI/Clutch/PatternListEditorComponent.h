#pragma once

#include <JuceHeader.h>
#include "PatternEditorComponent.h"
#include "../../Clutch/PatternListProperties.h"

class PatternListEditorComponent : public juce::Component
{
public:
    PatternListEditorComponent ();
    ~PatternListEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    PatternListProperties patternListProperties;
    std::array<PatternEditorComponent, 8> patternEditors;
    std::array<juce::Label, 8> patternLabels;

    void paint (juce::Graphics& g) override;
    void resized () override;
};