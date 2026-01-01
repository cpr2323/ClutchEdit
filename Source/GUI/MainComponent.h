#pragma once

#include <JuceHeader.h>
//#include "CurrentFolderComponent.h"
#include "GuiProperties.h"
//#include "BottomStatusWindow.h"
#include "ClutchEditorComponent.h"
//#include "../Utility/SplitWindowComponent.h"

class MainComponent : public juce::Component
{
public:
    MainComponent (juce::ValueTree rootPropertiesVT);
    ~MainComponent () = default;

private:
    ClutchEditorComponent clutchEditorComponent;
    GuiProperties guiProperties;
    //CurrentFolderComponent currentFolderComponent;
    //MidiConfigComponent midiConfigComponent;
    //FileViewComponent fileViewComponent;
    //PresetListComponent presetListComponent;
    //SplitWindowComponent topAndBottomSplitter;
    //SplitWindowComponent presetListEditorSplitter;
    //SplitWindowComponent folderBrowserEditorSplitter;
    //BottomStatusWindow bottomStatusWindow;

    juce::TooltipWindow tooltipWindow;

    void restoreLayout ();
    void saveLayoutChanges ();

    void resized () override;
    void paint (juce::Graphics& g) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
