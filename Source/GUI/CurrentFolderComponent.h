#pragma once

#include <JuceHeader.h>
#include "GuiProperties.h"
#include "Theme/UiComponents.h"
#include "../AppProperties.h"

/*
    The strip along the top of the window: which project is open, which output you
    are listening on, and the way in to Settings.

    The path is drawn as breadcrumbs rather than a raw path string - the file you
    are editing is the part that matters, so the folders leading to it are dimmed
    and the file name is not.
*/
class CurrentFolderComponent : public juce::Component
{
public:
    CurrentFolderComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    AppProperties appProperties;
    GuiProperties guiProperties;
    juce::AudioDeviceManager* audioDeviceManager { nullptr };

    static constexpr int kPadding { 9 };
    juce::StringArray pathSegments;
    // the last crumb is picked out only when it names the open file
    bool pathEndsInFile { false };

    ChromeButton outputButton { "OUT", ChromeButton::Size::chip };
    ChromeButton settingsButton { "SETTINGS", ChromeButton::Size::chip };

    void refreshPath ();
    void showOutputMenu ();
    void refreshOutputName ();

    void paint (juce::Graphics& g) override;
    void resized () override;
};
