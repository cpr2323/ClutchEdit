#include "BankListProperties.h"
#include "BankProperties.h"

void BankListProperties::initValueTree ()
{
    std::array<juce::String, 8> bankColors
    {
        "WHITE",
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "BLUE",
        "CYAN",
        "VIOLET"
    };
    for (auto& bank : bankColors)
    {
        BankProperties bankProp ({}, ValueTreeWrapper<BankProperties>::WrapperType::owner, ValueTreeWrapper<BankProperties>::EnableCallbacks::no);
        bankProp.setName (bank, false);
        getValueTree ().addChild (bankProp.getValueTree (), -1, nullptr);
    }
}

void BankListProperties::forEachBank (std::function<bool (juce::ValueTree bankVT, int bankIndex)> bankVTCallback)
{
    jassert (bankVTCallback != nullptr);
    auto curBankIndex { 0 };
    ValueTreeHelpers::forEachChildOfType (data, BankProperties::BankTypeId, [this, &curBankIndex, bankVTCallback] (juce::ValueTree bankVT)
    {
        auto keepIterating { bankVTCallback (bankVT, curBankIndex) };
        ++curBankIndex;
        return keepIterating;
    });
}

juce::ValueTree BankListProperties::getBankVT (int bankIndex)
{
    jassert (bankIndex < 8);
    juce::ValueTree requestedBankPropertiesVT;
    forEachBank ([this, &requestedBankPropertiesVT, bankIndex] (juce::ValueTree bankVT, int curBankIndex)
    {
        if (curBankIndex == bankIndex)
        {
            requestedBankPropertiesVT = bankVT;
            return false;
        }
        return true;
    });
    jassert (requestedBankPropertiesVT.isValid ());
    return requestedBankPropertiesVT;
}
