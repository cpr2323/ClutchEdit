#pragma once

#include "EffectEditorComponent.h"
#include "SettingsEditorComponent.h"
#include "PatternListEditorComponent.h"
#include "SampleManagerComponent.h"
#include "../../AppProperties.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Clutch/ProjectManagerProperties.h"
#include "../../Clutch/Audio/AudioPlayerProperties.h"
#include "../../GUI/GuiProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

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
    EffectEditorComponent effectEditorComponent;
    GuiProperties guiProperties;
    PatternListEditorComponent patternListEditorComponent;
    ProjectManagerProperties projectManagerProperties;
    RuntimeRootProperties runtimeRootProperties;
    SampleManagerComponent sampleManagerComponent;
    SettingsEditorComponent settingsEditorComponent;
    juce::TextButton saveButton;
    juce::TextButton optionsButton;
    TabbedComponentWithCallback editorTabs { juce::TabbedButtonBar::Orientation::TabsAtTop };
    std::unique_ptr<juce::FileChooser> fileChooser;

    void paint (juce::Graphics& g) override;
    void resized () override;
};