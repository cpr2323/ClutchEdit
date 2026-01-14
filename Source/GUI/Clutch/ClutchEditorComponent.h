#pragma once

#include "EffectEditorComponent.h"
#include "HiHatEditorComponent.h"
#include "PatternListEditorComponent.h"
#include "SampleManagerComponent.h"
#include "../../AppProperties.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

class ClutchEditorComponent : public juce::Component
{
public:
    ClutchEditorComponent ();
    ~ClutchEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    AppProperties appProperties;
    ClutchProperties clutchProperties;
    RuntimeRootProperties runtimeRootProperties;
    EffectEditorComponent effectEditorComponent;
    HiHatEditorComponent hiHatEditorComponent;
    PatternListEditorComponent patternListEditorComponent;
    SampleManagerComponent sampleManagerComponent;
    juce::TextButton saveButton;
    juce::TextButton openButton;
    juce::TabbedComponent editorTabs { juce::TabbedButtonBar::Orientation::TabsAtTop };
    std::unique_ptr<juce::FileChooser> fileChooser;

    void paint (juce::Graphics& g) override;
    void resized () override;
};