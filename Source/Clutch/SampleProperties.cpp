#include "SampleProperties.h"

void SampleProperties::initValueTree ()
{
    setExists (false, false);
    setFilename ("", false);
}

void SampleProperties::setExists (bool exists, bool includeSelfCallback)
{
    setValue (exists, ExistsPropertyId, includeSelfCallback);
}

void SampleProperties::setFilename (const juce::String& filename, bool includeSelfCallback)
{
    setValue (filename, FilenamePropertyId, includeSelfCallback);
}

void SampleProperties::setType (SampleType sampleType, bool includeSelfCallback)
{
    setValue (juce::String (sampleType == SampleType::open ? "open" : "closed"), TypePropertyId, includeSelfCallback);
}

bool SampleProperties::getExists ()
{
    return getValue<bool> (ExistsPropertyId);
}

juce::String SampleProperties::getFilename ()
{
    return getValue<juce::String> (FilenamePropertyId);
}

SampleProperties::SampleType SampleProperties::getType ()
{
    return getValue<juce::String> (TypePropertyId) == "open" ? SampleType::open : SampleType::closed;
}

void SampleProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (vt != data)
        return;

    if (property == ExistsPropertyId)
    {
        if (onExistsChange)
            onExistsChange (getExists ());
    }
    else if (property == FilenamePropertyId)
    {
        if (onFilenameChange)
            onFilenameChange (getFilename ());
    }
    else if (property == TypePropertyId)
    {
        if (onTypeChange)
            onTypeChange (getType ());
    }
}
