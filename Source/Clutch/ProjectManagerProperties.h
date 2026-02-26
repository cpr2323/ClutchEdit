#pragma once

#include "../Utility/ValueTreeWrapper.h"

class ProjectManagerProperties : public ValueTreeWrapper<ProjectManagerProperties>
{
public:
    ProjectManagerProperties () noexcept : ValueTreeWrapper<ProjectManagerProperties> (ProjectManagerTypeId)
    {
    }
    ProjectManagerProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<ProjectManagerProperties> (ProjectManagerTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setProjectEdited (bool projectEdited, bool includeSelfCallback);
    void doSaveProject (bool includeSelfCallback);

    bool getProjectEdited ();

    std::function<void (bool projectEdited)> onProjectEditedChange;
    std::function<void ()> onSaveProject;

    static inline const juce::Identifier ProjectManagerTypeId { "ProjectManager" };
    static inline const juce::Identifier DoSaveProjectPropertyId { "doSaveProject" };
    static inline const juce::Identifier ProjectEditedPropertyId { "projectEdited" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};