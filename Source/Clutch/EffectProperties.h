#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

class EffectProperties : public ValueTreeWrapper<EffectProperties>
{
public:
    EffectProperties () noexcept : ValueTreeWrapper<EffectProperties> (BankTypeId)
    {
    }
    EffectProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<EffectProperties> (BankTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setId (juce::String, bool includeSelfCallback);
    void setEffect (juce::String, bool includeSelfCallback);
    juce::String getId ();
    juce::String getEffect ();
    std::function<void (juce::String id)> onIdChange;
    std::function<void (juce::String pattern)> onEffectChange;

    static inline const juce::Identifier BankTypeId { "Effect" };
    static inline const juce::Identifier IdPropertyId { "id" };
    static inline const juce::Identifier EffectPropertyId { "effect" };

    void initValueTree () {}
    void processValueTree () {}

private:
    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};