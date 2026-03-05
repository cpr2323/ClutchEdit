#include "PatternProperties.h"

void PatternProperties::setId (juce::String id, bool includeSelfCallback)
{
    setValue (id, IdPropertyId, includeSelfCallback);
}

void PatternProperties::setPattern (juce::String pattern, bool includeSelfCallback)
{
    setValue (pattern, PatternPropertyId, includeSelfCallback);
}

juce::String PatternProperties::getId ()
{
    return getValue<juce::String> (IdPropertyId);
}

juce::String PatternProperties::getPattern ()
{
    return getValue<juce::String> (PatternPropertyId);
}

void PatternProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (vt != data)
        return;

    if (property == IdPropertyId)
    {
        if (onIdChange)
            onIdChange (getId ());
    }
    else if (property == PatternPropertyId)
    {
        if (onPatternChange)
            onPatternChange (getPattern ());
    }
}