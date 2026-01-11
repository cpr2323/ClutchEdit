#pragma once

#include <JuceHeader.h>
#include "../../Clutch/EffectListProperties.h"

class FileDropLabel : public juce::Label,
                      public juce::FileDragAndDropTarget
{
public:
private:
    bool fileExists { false };

    bool isInterestedInFileDrag ([[maybe_unused]] const juce::StringArray& files) override
    {
        // we do this check in the fileDragEnter and fileDragMove handlers, presenting more info regarding the drop operation
        return true;
    }

    void filesDropped (const juce::StringArray& files, int x, int y) override
    {
    }

    void fileDragEnter (const juce::StringArray& files, int x, int y) override
    {
        setColour (juce::Label::ColourIds::textColourId, juce::Colours::yellow);
    }

    void fileDragMove (const juce::StringArray& files, int x, int y) override
    {
    }

    void fileDragExit (const juce::StringArray&) override
    {
        setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    }
};

class SampleBankComponent : public juce::Component,
                                   juce::Timer
{
public:
    SampleBankComponent ();
    ~SampleBankComponent ();

    void init (juce::ValueTree rootPropertiesVT);

    void setBankName (const juce::String& newBankName);
    void updateFileStatus ();

private:
    //SampleProperties effectListProperties;
    juce::Label bankName;
    struct SurfaceInfo
    {
        juce::Label name;
        FileDropLabel openedName;
        FileDropLabel closedName;
    };
    std::array<SurfaceInfo, 16> surfaceComponents;

    void paint (juce::Graphics& g) override;
    void resized () override;
    void timerCallback () override;
};

class SampleManagerComponent : public juce::Component
{
public:
    SampleManagerComponent ();
    ~SampleManagerComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    EffectListProperties effectListProperties;
    std::array<SampleBankComponent, 8> sampleBankComponents;

    void paint (juce::Graphics& g) override;
    void resized () override;
};