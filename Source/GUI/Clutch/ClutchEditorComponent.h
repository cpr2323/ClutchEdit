#pragma once

#include "EffectEditorComponent.h"
#include "HiHatEditorComponent.h"
#include "PatternListEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"

class ClutchEditorComponent : public juce::Component
{
public:
    ClutchEditorComponent ();
    ~ClutchEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    ClutchProperties clutchProperties;
    HiHatEditorComponent hiHatEditorComponent;
    PatternListEditorComponent patternListEditorComponent;
    EffectEditorComponent effectEditorComponent;
    juce::TextButton saveButton;
    juce::TabbedComponent editorTabs { juce::TabbedButtonBar::Orientation::TabsAtTop };

    void paint (juce::Graphics& g) override;
    void resized () override;
};