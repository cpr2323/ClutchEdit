#pragma once

#include <JuceHeader.h>
#include "ClutchProperties.h"
#include "../AppProperties.h"

class ProjectManager : public juce::Timer
{
public:
    ProjectManager (juce::ValueTree rootPropertiesVT);

private:
    AppProperties appProperties;
    ClutchProperties unEditedClutchProperties;
    ClutchProperties editedClutchProperties;

    void openProject (const juce::File& hiHatIniFile, juce::ValueTree rootPropertiesVT);
    void scanSamples (juce::ValueTree clutchPropertiesVT);

    void timerCallback () override;
};