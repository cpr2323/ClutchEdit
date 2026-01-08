#pragma once

#include <JuceHeader.h>
#include "../../Clutch/EffectListProperties.h"

class EffectEditorComponent : public juce::Component
{
public:
    EffectEditorComponent ();
    ~EffectEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    EffectListProperties effectListProperties;

    void paint (juce::Graphics& g) override;
    void resized () override;
};