#include "EffectListProperties.h"

void EffectProperties::setId (juce::String id, bool includeSelfCallback)
{
    setValue (id, IdPropertyId, includeSelfCallback);
}

void EffectProperties::setEffect (juce::String effect, bool includeSelfCallback)
{
    setValue (effect, EffectPropertyId, includeSelfCallback);
}

juce::String EffectProperties::getId ()
{
    return getValue<juce::String> (IdPropertyId);
}

juce::String EffectProperties::getEffect ()
{
    return getValue<juce::String> (EffectPropertyId);
}

void EffectProperties::valueTreePropertyChanged (juce::ValueTree& vt,
                                                 const juce::Identifier& property)
{
    if (vt != data)
        return;

    if (property == IdPropertyId)
    {
        if (onIdChange)
            onIdChange (getId ());
    }
    else if (property == EffectPropertyId)
    {
        if (onEffectChange)
            onEffectChange (getEffect ());
    }
}

void EffectListProperties::initValueTree ()
{
    std::pair<juce::String, juce::String> defaultEffects []
    {
        {"FX_WHITE", "SPUTTER" },
        {"FX_RED", "BITCRUSH" },
        {"FX_GREEN", "COMBFILTER" },
        {"FX_BLUE", "DJFILTER" },
        {"FX_ORANGE", "DUBECHO" },
        {"FX_CYAN", "CHORUS" },
        {"FX_VIOLET", "REVERB" },
        {"FX_YELLOW", "GLITCH" },
    };
    for (auto& effect : defaultEffects)
    {
        EffectProperties effectProp ({}, ValueTreeWrapper<EffectProperties>::WrapperType::owner, ValueTreeWrapper<EffectProperties>::EnableCallbacks::no);
        effectProp.setId (effect.first, false);
        effectProp.setEffect (effect.second, false);
        getValueTreeRef ().addChild (effectProp.getValueTree (), -1, nullptr);
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


void EffectListProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
}