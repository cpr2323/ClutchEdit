#pragma once

#include <JuceHeader.h>
#include "SampleBankComponent.h"
#include "../../AppProperties.h"

class SampleManagerComponent : public juce::Component
{
public:
    SampleManagerComponent ();
    ~SampleManagerComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    std::array<SampleBankComponent, 8> sampleBankComponents;
    AppProperties appProperties;

    void updateBanks ();

    void paint (juce::Graphics& g) override;
    void resized () override;
};