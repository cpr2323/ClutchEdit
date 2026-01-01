#pragma once

#include "HiHatEditorComponent.h"

class ClutchEditorComponent : public juce::Component
{
public:
    ClutchEditorComponent ();
    ~ClutchEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    HiHatEditorComponent hiHatEditorComponent;

    //void paint (juce::Graphics& g) override;
    void resized () override;
};