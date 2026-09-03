#pragma once

#include <JuceHeader.h>
#include "ClutchProperties.h"
#include "ProjectManagerProperties.h"
#include "../AppProperties.h"
#include "../Clutch/HiHatIniData.h"
#include "oolib/Properties/RuntimeRootProperties.h"

class ProjectManager : public juce::Timer
{
public:
    ProjectManager ();
    void init (juce::ValueTree rootPropertiesVT);
    static void copy (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT);

private:
    juce::ValueTree rootPropertiesVT;
    RuntimeRootProperties runtimeRootProperties;
    ProjectManagerProperties projectManagerProperties;
    AppProperties appProperties;
    ClutchProperties unEditedClutchProperties;
    ClutchProperties editedClutchProperties;
    HiHatIniData hiHatIniData;
    enum class TimerTask { scanSamples, checkForEdits };
    TimerTask timerTask { TimerTask::scanSamples };

    bool areEntireClutchPropertiesEqual (juce::ValueTree clutchPropertiesVT1, juce::ValueTree clutchPropertiesVT2);
    void cleanUpTempFiles ();
    void doQueuedDeletions ();
    void forEachSamplePair (std::function<void (juce::ValueTree samplePairPropertiesVT, juce::File sampleBankFolder)> samplePairCallback);
    void openProject (const juce::File& hiHatIniFile);
    void saveProject ();
    void scanSamples (juce::ValueTree clutchPropertiesVT);

    static void copySampleProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT, bool copySamplesReference);
    static void copySettingsProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT);
    static void copyEffectListProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT);
    static void copyPatternListProperties (juce::ValueTree sourceClutchPropertiesVT, juce::ValueTree destClutchPropertiesVT);

    void timerCallback () override;
    void convertTempFilesToPerm ();
};