#pragma once

#include <JuceHeader.h>
#include "CurrentFolderComponent.h"
#include "GuiProperties.h"
#include "Clutch/ClutchEditorComponent.h"

class MainComponent : public juce::Component
{
public:
    MainComponent (juce::ValueTree rootPropertiesVT);
    ~MainComponent () = default;

private:
    ClutchEditorComponent clutchEditorComponent;
    GuiProperties guiProperties;
    CurrentFolderComponent currentFolderComponent;
    juce::TooltipWindow tooltipWindow;

    void restoreLayout ();
    void saveLayoutChanges ();

    void resized () override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
