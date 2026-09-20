#pragma once

#include "EffectEditorComponent.h"
#include "SettingsEditorComponent.h"
#include "PatternListEditorComponent.h"
#include "SampleManagerComponent.h"
#include "../Theme/UiComponents.h"
#include "../../AppProperties.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Clutch/ProjectManagerProperties.h"
#include "../../Clutch/Audio/AudioPlayerProperties.h"
#include "../../GUI/GuiProperties.h"
#include "oolib/Properties/RuntimeRootProperties.h"

class TabbedComponentWithCallback : public juce::TabbedComponent
{
public:
    TabbedComponentWithCallback (juce::TabbedButtonBar::Orientation orientation) : juce::TabbedComponent (orientation)
    {
    }

    void currentTabChanged (int newCurrentTabIndex, [[maybe_unused]] const juce::String& newCurrentTabName) override
    {
        if (onTabChanged)
            onTabChanged (newCurrentTabIndex);
    }
    std::function<void (int tabIndex)> onTabChanged;

};
class ClutchEditorComponent : public juce::Component
{
public:
    ClutchEditorComponent ();
    ~ClutchEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    AppProperties appProperties;
    AudioPlayerProperties audioPlayerProperties;
    ClutchProperties clutchProperties;
    ClutchProperties uneditedClutchProperties;
    ClutchProperties defaultClutchProperties;
    EffectEditorComponent effectEditorComponent;
    GuiProperties guiProperties;
    PatternListEditorComponent patternListEditorComponent;
    ProjectManagerProperties projectManagerProperties;
    RuntimeRootProperties runtimeRootProperties;
    SampleManagerComponent sampleManagerComponent;
    SettingsEditorComponent settingsEditorComponent;
    // SAVE takes the accent fill while, and only while, there is something to save
    ActionButton saveButton { "SAVE" };
    ActionButton openButton { "OPEN" };
    MenuButton toolsButton { "TOOLS" };
    TabbedComponentWithCallback editorTabs { juce::TabbedButtonBar::Orientation::TabsAtTop };
    std::unique_ptr<juce::FileChooser> fileChooser;

    // the tabs sit along the top, with the project tools at the right hand end
    // of the same strip
    static constexpr int kTabBarHeight { 31 };

    void applyTabColours ();

    void lookAndFeelChanged () override;
    void paint (juce::Graphics& g) override;
    void resized () override;
};
