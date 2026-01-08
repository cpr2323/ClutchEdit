#pragma once

#include <JuceHeader.h>
#include "../../Clutch/EffectListProperties.h"

class SampleManagerComponent : public juce::Component
{
public:
    SampleManagerComponent ();
    ~SampleManagerComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    EffectListProperties effectListProperties;

    void paint (juce::Graphics& g) override;
    void resized () override;
};