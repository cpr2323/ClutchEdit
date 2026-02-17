#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

class BankListProperties : public ValueTreeWrapper<BankListProperties>
{
public:
    BankListProperties () noexcept : ValueTreeWrapper<BankListProperties> (BankListTypeId)
    {
    }
    BankListProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<BankListProperties> (BankListTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void forEachBank (std::function<bool (juce::ValueTree bankVT, int bankIndex)> bankVTCallback);
    juce::ValueTree getBankVT (int bankIndex);

    static inline const juce::Identifier BankListTypeId { "BankList" };

    void initValueTree ();
    void processValueTree () {}

private:
};
