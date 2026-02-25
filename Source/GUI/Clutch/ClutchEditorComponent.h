#pragma once

#include "EffectEditorComponent.h"
#include "SettingsEditorComponent.h"
#include "PatternListEditorComponent.h"
#include "SampleManagerComponent.h"
#include "../../AppProperties.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Clutch/ProjectManagerProperties.h"
#include "../../Clutch/Audio/AudioPlayerProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

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
    PatternListEditorComponent patternListEditorComponent;
    ProjectManagerProperties projectManagerProperties;
    RuntimeRootProperties runtimeRootProperties;
    SampleManagerComponent sampleManagerComponent;
    SettingsEditorComponent settingsEditorComponent;
    juce::TextButton saveButton;
    juce::TextButton openButton;
    juce::TextButton settingsButton;
    juce::TabbedComponent editorTabs { juce::TabbedButtonBar::Orientation::TabsAtTop };
    std::unique_ptr<juce::FileChooser> fileChooser;

    void paint (juce::Graphics& g) override;
    void resized () override;
};