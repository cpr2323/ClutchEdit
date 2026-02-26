#pragma once
#include <JuceHeader.h>
#include "../../Clutch/BankProperties.h"
#include "../../Clutch/SampleProperties.h"
#include "../../Clutch/Audio/AudioPlayerProperties.h"

class FileDropLabel : public juce::Label,
                      public juce::FileDragAndDropTarget,
                      public juce::Timer
{
public:
    FileDropLabel ()
    {
    }

    std::function<void (juce::StringArray)> onFilesSelected;
    std::function<void (const juce::MouseEvent& mouseEvent)> onMouseUp;

    void setFileExistState (bool doesFileExist)
    {
        fileExists = doesFileExist;
        setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
    }

    void enablePlayBlink (bool enable)
    {
        playBlinkEnabled = enable;
        if (playBlinkEnabled)
        {
            if (fileExists)
            {
                colorCrossfadePosition = 0.0;
                colorCrossfadeIncrement = kDefaultCrossfadeIncrement;
                startTimer (kAnimationTimer);
            }
            else
            {
                playBlinkEnabled = false;
            }
        }
        else
        {
            stopTimer ();
            setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
        }
    }

private:
    static inline constexpr float kDefaultCrossfadeIncrement { 0.03f };
    static inline constexpr int kAnimationTimer { 16 };
    bool fileExists { false };
    juce::Colour hoverColor { juce::Colours::lightseagreen };
    float colorCrossfadePosition { 0.0 };
    float colorCrossfadeIncrement { kDefaultCrossfadeIncrement };

    bool playBlinkEnabled { false };

    void mouseUp (const juce::MouseEvent& mouseEvent) override
    {    
        if (! mouseEvent.mods.isPopupMenu () && onMouseUp != nullptr)
            onMouseUp (mouseEvent);
    }

    bool isInterestedInFileDrag ([[maybe_unused]] const juce::StringArray& files) override
    {
        return files.size () == 1;
    }

    void filesDropped (const juce::StringArray& files, [[maybe_unused]] int x, [[maybe_unused]] int y) override
    {
        playBlinkEnabled = false;
        colorCrossfadeIncrement = kDefaultCrossfadeIncrement;
        colorCrossfadePosition = 0.0;
        startTimer (kAnimationTimer);
        if (onFilesSelected != nullptr)
            onFilesSelected (files);
        fileExists = true;
        repaint ();
    }

    void fileDragEnter ([[maybe_unused]] const juce::StringArray& files, [[maybe_unused]] int x, [[maybe_unused]] int y) override
    {
        setColour (juce::Label::ColourIds::textColourId, hoverColor);
    }

    void fileDragMove ([[maybe_unused]] const juce::StringArray& files, int, int) override
    {
        setColour (juce::Label::ColourIds::textColourId, hoverColor);
    }

    void fileDragExit (const juce::StringArray&) override
    {
        setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
    }

    void timerCallback () override
    {
        if (! playBlinkEnabled)
        {
            if (colorCrossfadePosition > 1.0)
            {
                setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
                stopTimer ();
            }
            else
            {
                setColour (juce::Label::ColourIds::textColourId, hoverColor.interpolatedWith (juce::Colours::white, colorCrossfadePosition));
                colorCrossfadePosition += colorCrossfadeIncrement;
            }
        }
        else
        {
            if (colorCrossfadePosition < 0.0f)
            {
                colorCrossfadePosition = 0.0f;
                colorCrossfadeIncrement = kDefaultCrossfadeIncrement;
            }
            else if (colorCrossfadePosition > 1.0f)
            {
                colorCrossfadePosition = 1.0f;
                colorCrossfadeIncrement = -kDefaultCrossfadeIncrement;
            }

            setColour (juce::Label::ColourIds::textColourId, juce::Colours::orange.interpolatedWith (juce::Colours::white, colorCrossfadePosition));
            colorCrossfadePosition += colorCrossfadeIncrement;
        }
        repaint ();
    }
};

class SampleBankComponent : public juce::Component,
                                   juce::Timer
{
public:
    enum class HiHatState { opened, closed };

    SampleBankComponent ();
    ~SampleBankComponent ();

    void init (juce::ValueTree rootPropertiesVT, juce::ValueTree bankPropertiesVT);

    void setBankName (const juce::String& newBankName);
    void setBankFolder (const juce::File& newBankFolder);

private:
    BankProperties bankProperties;
    juce::Label bankName;
    struct HiHatSampleInfo
    {
        juce::Label name;
        FileDropLabel openedNameLabel;
        FileDropLabel closedNameLabel;
        SampleProperties openSampleProperties;
        SampleProperties closedSampleProperties;
    };
    std::array<HiHatSampleInfo, 16> hiHatSampleInfoList;
    juce::File banksRootFolder;
    AudioPlayerProperties audioPlayerProperties;
    FileDropLabel* auditioningSampleLabelComponent { nullptr };

    void copySampleFile (juce::File sourceFile, int hiHatSampleIndex, HiHatState hiHatState);
    void sampleConvert (juce::AudioFormatReader* reader, juce::AudioBuffer<float>& outputBuffer);

    void paint (juce::Graphics& g) override;
    void resized () override;
    void timerCallback () override;
};