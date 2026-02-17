#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

class SamplePairProperties : public ValueTreeWrapper<SamplePairProperties>
{
public:
    SamplePairProperties () noexcept : ValueTreeWrapper<SamplePairProperties> (SamplePairTypeId)
    {
    }
    SamplePairProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<SamplePairProperties> (SamplePairTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    juce::ValueTree getOpenSampleVT ();
    juce::ValueTree getClosedSampleVT ();

    static inline const juce::Identifier SamplePairTypeId { "SamplePair" };
    static inline const juce::Identifier SampleTypePropertyId { "sampleType" };

    void initValueTree ();
    void processValueTree () {}

private:
};