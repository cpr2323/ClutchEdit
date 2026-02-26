#pragma once

#include <JuceHeader.h>
#include "ClutchProperties.h"
#include "ProjectManagerProperties.h"
#include "../AppProperties.h"
#include "../Clutch/HiHatIniData.h"

class ProjectManager : public juce::Timer
{
public:
    ProjectManager ();
    void init (juce::ValueTree rootPropertiesVT);

private:
    juce::ValueTree rootPropertiesVT;
    ProjectManagerProperties projectManagerProperties;
    AppProperties appProperties;
    ClutchProperties unEditedClutchProperties;
    ClutchProperties editedClutchProperties;
    HiHatIniData hiHatIniData;

    bool areEntireClutchPropertiesEqual (juce::ValueTree clutchPropertiesVT1, juce::ValueTree clutchPropertiesVT2);
    void copySamplePropertiesExistsFlags (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT);
    void openProject (const juce::File& hiHatIniFile);
    void saveProject ();
    void scanSamples (juce::ValueTree clutchPropertiesVT);

    void timerCallback () override;
};