#include "ProjectManagerProperties.h"

void ProjectManagerProperties::initValueTree ()
{
    setProjectEdited (false, false);
    doSaveProject (false);
}

void ProjectManagerProperties::setProjectEdited (bool projectEdited, bool includeSelfCallback)
{
    setValue (projectEdited, ProjectEditedPropertyId, includeSelfCallback);
}

void ProjectManagerProperties::doCleanUpTempFiles (bool includeSelfCallback)
{
    setValue (! getValue<bool> (DoCleanUpTempFilesPropertyId), DoCleanUpTempFilesPropertyId, includeSelfCallback);
}

void ProjectManagerProperties::doSaveProject (bool includeSelfCallback)
{
    setValue (! getValue<bool> (DoSaveProjectPropertyId), DoSaveProjectPropertyId, includeSelfCallback);
}

bool ProjectManagerProperties::getProjectEdited ()
{
    return getValue<bool> (ProjectEditedPropertyId);
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
    else if (property == DoCleanUpTempFilesPropertyId)
    {
        if (onCleanupTempFiles)
            onCleanupTempFiles ();
    }

    else if (property == ProjectEditedPropertyId)
    {
        if (onProjectEditedChange)
            onProjectEditedChange (getProjectEdited ());
    }
}
