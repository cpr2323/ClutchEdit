#pragma once

#include "../Clutch/HiHatProperties.h"

class ClutchEditorComponent : public juce::Component
{
public:
    ClutchEditorComponent ();
    ~ClutchEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    HiHatProperties hiHatProperties;
};