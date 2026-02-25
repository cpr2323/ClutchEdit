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

    void doSaveProject (bool includeSelfCallback);


    std::function<void ()> onSaveProject;

    static inline const juce::Identifier ProjectManagerTypeId { "ProjectManager" };
    static inline const juce::Identifier DoSaveProjectPropertyId { "doSaveProject" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};