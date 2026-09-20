#pragma once

#include <JuceHeader.h>
#include "CurrentFolderComponent.h"
#include "GuiProperties.h"
#include "SettingsDialogComponent.h"
#include "Clutch/ClutchEditorComponent.h"

class MainComponent : public juce::Component
{
public:
    MainComponent (juce::ValueTree rootPropertiesVT);
    ~MainComponent () = default;

private:
    juce::ValueTree rootProperties;
    ClutchEditorComponent clutchEditorComponent;
    GuiProperties guiProperties;
    CurrentFolderComponent currentFolderComponent;
    juce::TooltipWindow tooltipWindow;

    void restoreLayout ();
    void saveLayoutChanges ();
    void showSettingsDialog ();

    void paint (juce::Graphics& g) override;
    void resized () override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
