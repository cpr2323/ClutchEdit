#pragma once

#include "HiHatEditorComponent.h"
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
    juce::TextButton saveButton;

    void paint (juce::Graphics& g) override;
    void resized () override;
};