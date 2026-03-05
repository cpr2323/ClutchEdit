#include "EffectProperties.h"

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