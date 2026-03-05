#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

class PatternProperties : public ValueTreeWrapper<PatternProperties>
{
public:
    PatternProperties () noexcept : ValueTreeWrapper<PatternProperties> (PatternTypeId)
    {
    }
    PatternProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<PatternProperties> (PatternTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setId (juce::String, bool includeSelfCallback);
    void setPattern (juce::String, bool includeSelfCallback);
    juce::String getId ();
    juce::String getPattern ();
    std::function<void (juce::String id)> onIdChange;
    std::function<void (juce::String pattern)> onPatternChange;

    static inline const juce::Identifier PatternTypeId { "Pattern" };
    static inline const juce::Identifier IdPropertyId      { "id" };
    static inline const juce::Identifier PatternPropertyId { "pattern" };

    void initValueTree () {}
    void processValueTree () {}

private:
    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};