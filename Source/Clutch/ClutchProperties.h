#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

class ClutchProperties : public ValueTreeWrapper<ClutchProperties>
{
public:
    ClutchProperties () noexcept : ValueTreeWrapper<ClutchProperties> (ClutchTypeId)
    {
    }
    ClutchProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<ClutchProperties> (ClutchTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setName (juce::String name, bool includeSelfCallback);
    juce::String getName ();
    std::function<void (juce::String)> onNameChange;

    static inline const juce::Identifier ClutchTypeId { "Clutch" };
    static inline const juce::Identifier NamePropertyId { "name" };

    void initValueTree ();
    void processValueTree () {}
private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};