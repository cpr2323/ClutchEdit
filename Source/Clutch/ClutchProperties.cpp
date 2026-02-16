#include "ClutchProperties.h"

void ClutchProperties::setName (juce::String name, bool includeSelfCallback)
{
    setValue (name, NamePropertyId, includeSelfCallback);
}

juce::String ClutchProperties::getName ()
{
    return getValue<juce::String> (NamePropertyId);
}

void ClutchProperties::initValueTree ()
{
    setName ("", false);
}

void ClutchProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (vt != data)
        return;

    if (property == NamePropertyId)
    {
        if (onNameChange)
            onNameChange (getName ());
    }
}
