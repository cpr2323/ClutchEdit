#pragma once

#include <JuceHeader.h>
#include "oolib/ValueTree/ValueTreeWrapper.h"

class BankProperties : public ValueTreeWrapper<BankProperties>
{
public:
    BankProperties () noexcept : ValueTreeWrapper<BankProperties> (BankTypeId)
    {
    }
    BankProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<BankProperties> (BankTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setName (juce::String, bool includeSelfCallback);
    juce::String getName ();
    std::function<void (juce::String name)> onNameChange;

    void forEachSamplePair (std::function<bool (juce::ValueTree samplePairVT, int samplePairIndex)> samplePairVTCallback);
    juce::ValueTree getSamplePairVT (int samplePairIndex);

    static inline const juce::Identifier BankTypeId { "Bank" };
    static inline const juce::Identifier NamePropertyId { "name" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};
