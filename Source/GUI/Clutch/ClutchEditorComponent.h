#pragma once

#include "EffectEditorComponent.h"
#include "HiHatEditorComponent.h"
#include "PatternListEditorComponent.h"
#include "SampleManagerComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

class ClutchEditorComponent : public juce::Component
{
public:
    ClutchEditorComponent ();
    ~ClutchEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    RuntimeRootProperties runtimeRootProperties;
    ClutchProperties clutchProperties;
    HiHatEditorComponent hiHatEditorComponent;
    PatternListEditorComponent patternListEditorComponent;
    EffectEditorComponent effectEditorComponent;
    SampleManagerComponent sampleManagerComponent;
    juce::TextButton saveButton;
    juce::TabbedComponent editorTabs { juce::TabbedButtonBar::Orientation::TabsAtTop };

    void paint (juce::Graphics& g) override;
    void resized () override;
};