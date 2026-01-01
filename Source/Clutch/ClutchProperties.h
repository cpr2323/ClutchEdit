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

    static inline const juce::Identifier ClutchTypeId { "Clutch" };

    void initValueTree () {}
    void processValueTree () {}
private:
};