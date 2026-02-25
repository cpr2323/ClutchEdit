#include "ProjectManagerProperties.h"

void ProjectManagerProperties::initValueTree ()
{
    doSaveProject (false);
}

void ProjectManagerProperties::doSaveProject (bool includeSelfCallback)
{
    setValue (! getValue<bool>(DoSaveProjectPropertyId), DoSaveProjectPropertyId, includeSelfCallback);
}

void ProjectManagerProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (data != vt)
        return;

    if (property == DoSaveProjectPropertyId)
    {
        if (onSaveProject)
            onSaveProject();
    }
}
