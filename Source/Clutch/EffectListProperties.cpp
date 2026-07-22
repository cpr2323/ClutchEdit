#include "EffectListProperties.h"
#include "HiHatIniKeys.h"
#include "EffectProperties.h"

void EffectListProperties::initValueTree ()
{
    std::pair<juce::String, juce::String> defaultEffects []
    {
        {kFxWhiteKey, "SPUTTER" },
        {kFxRedKey, "BITCRUSH" },
        {kFxGreenKey, "COMBFILTER" },
        {kFxBlueKey, "DJFILTER" },
        {kFxOrangeKey, "DUBECHO" },
        {kFxCyanKey, "CHORUS" },
        {kFxVioletKey, "REVERB" },
        {kFxYellowKey, "GLITCH" },
    };
    for (auto& effect : defaultEffects)
    {
        EffectProperties effectProp ({}, ValueTreeWrapper<EffectProperties>::WrapperType::owner, ValueTreeWrapper<EffectProperties>::EnableCallbacks::no);
        effectProp.setId (effect.first, false);
        effectProp.setEffect (effect.second, false);
        getValueTree ().addChild (effectProp.getValueTree (), -1, nullptr);
    }
}

void EffectListProperties::forEachEffect (std::function<bool (juce::ValueTree effectVT, int effectIndex)> effectVTCallback)
{
    jassert (effectVTCallback != nullptr);
    auto curEffectIndex { 0 };
    ValueTreeHelpers::forEachChildOfType (data, EffectProperties::EffectTypeId, [this, &curEffectIndex, effectVTCallback] (juce::ValueTree effectVT)
    {
        auto keepIterating { effectVTCallback (effectVT, curEffectIndex) };
        ++curEffectIndex;
        return keepIterating;
    });
}

juce::ValueTree EffectListProperties::getEffectVT (int effectIndex)
{
    jassert (effectIndex < 8);
    juce::ValueTree requestedEffectPropertiesVT;
    forEachEffect ([this, &requestedEffectPropertiesVT, effectIndex] (juce::ValueTree effectVT, int curEffectIndex)
    {
        if (curEffectIndex == effectIndex)
        {
            requestedEffectPropertiesVT = effectVT;
            return false;
        }
        return true;
    });
    jassert (requestedEffectPropertiesVT.isValid ());
    return requestedEffectPropertiesVT;
}
