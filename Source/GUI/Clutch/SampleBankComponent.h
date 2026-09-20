#pragma once
#include <JuceHeader.h>
#include "../Theme/UiComponents.h"
#include "../../AppProperties.h"
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
        showAtRest ();
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
            showAtRest ();
        }
    }

private:
    static inline constexpr float kDefaultCrossfadeIncrement { 0.03f };
    static inline constexpr int kAnimationTimer { 16 };
    bool fileExists { false };
    float colorCrossfadePosition { 0.0 };
    float colorCrossfadeIncrement { kDefaultCrossfadeIncrement };

    bool playBlinkEnabled { false };
    // a file being dragged over the slot lights its border, as the pointer does
    bool dropTargetActive { false };

    // the slot is a value field like any other, so it is drawn as one
    void paint (juce::Graphics& g) override
    {
        const auto bounds { getLocalBounds () };
        ClutchPaint::fieldBackground (g, *this, bounds, true);
        ClutchPaint::fieldOutline (g, *this, bounds, true, dropTargetActive || isMouseOver (true));
        juce::Label::paint (g);
    }

    // a Label does not repaint itself as the pointer comes and goes, and its
    // border has to follow it
    void mouseEnter (const juce::MouseEvent&) override { repaint (); }
    void mouseExit (const juce::MouseEvent&) override  { repaint (); }

    // A slot names its own state with ink: a file it holds reads as text, an empty
    // one is the quietest ink there is, a slot the pointer is about to drop onto
    // takes the drop colour, and one that is sounding pulses in the audition colour.
    // Every one of them is resolved when it is used, so they follow the palette.
    juce::Colour restColour () const
    {
        return findColour (fileExists ? ClutchColours::text : ClutchColours::textGhost);
    }

    void showAtRest ()
    {
        setColour (juce::Label::ColourIds::textColourId, restColour ());
    }

    void showDropTarget ()
    {
        setColour (juce::Label::ColourIds::textColourId, findColour (ClutchColours::dropTarget));
    }

    // an animation in flight is left alone: its next tick sets the colour anyway
    void lookAndFeelChanged () override
    {
        juce::Label::lookAndFeelChanged ();
        if (! isTimerRunning ())
            showAtRest ();
    }

    void mouseUp (const juce::MouseEvent& mouseEvent) override
    {    
        if (onMouseUp != nullptr)
            onMouseUp (mouseEvent);
    }

    bool isInterestedInFileDrag ([[maybe_unused]] const juce::StringArray& files) override
    {
        return files.size () == 1;
    }

    void filesDropped (const juce::StringArray& files, [[maybe_unused]] int x, [[maybe_unused]] int y) override
    {
        dropTargetActive = false;
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
        dropTargetActive = true;
        showDropTarget ();
    }

    void fileDragMove ([[maybe_unused]] const juce::StringArray& files, int, int) override
    {
        dropTargetActive = true;
        showDropTarget ();
    }

    void fileDragExit (const juce::StringArray&) override
    {
        dropTargetActive = false;
        showAtRest ();
    }

    void timerCallback () override
    {
        if (! playBlinkEnabled)
        {
            if (colorCrossfadePosition > 1.0)
            {
                showAtRest ();
                stopTimer ();
            }
            else
            {
                setColour (juce::Label::ColourIds::textColourId,
                           findColour (ClutchColours::dropTarget).interpolatedWith (restColour (), colorCrossfadePosition));
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

            setColour (juce::Label::ColourIds::textColourId,
                       findColour (ClutchColours::audition).interpolatedWith (restColour (), colorCrossfadePosition));
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

    void init (juce::ValueTree rootPropertiesVT, juce::ValueTree bankPropertiesVT, juce::ValueTree uneditedBankPropertiesVT);

    void setBankName (const juce::String& newBankName);
    void setBankFolder (const juce::File& newBankFolder);

private:
    AppProperties appProperties;
    BankProperties bankProperties;
    BankProperties uneditedBankProperties;
    juce::Label bankName;
    struct HiHatSamplePair
    {
        SampleProperties openedSampleProperties;
        SampleProperties closedSampleProperties;
    };
    struct HiHatSampleInfo
    {
        juce::Label name;
        FileDropLabel openedNameLabel;
        FileDropLabel closedNameLabel;
        HiHatSamplePair editedSamplePropertiesPair;
        HiHatSamplePair uneditedSamplePropertiesPair;
    };
    std::array<HiHatSampleInfo, 16> hiHatSampleInfoList;
    juce::File banksRootFolder;
    AudioPlayerProperties audioPlayerProperties;
    FileDropLabel* auditioningSampleLabelComponent { nullptr };

    void copyToTempSampleFile (juce::File sourceFile, int hiHatSampleIndex, HiHatState hiHatState);
    juce::String getBankAndFileNameWithoutExtension (int hiHatSampleIndex, SampleProperties::SampleType sampleType);
    juce::String getFullPath (int hiHatSampleIndex, SampleProperties::SampleType sampleType);
    juce::String getBankAndFileName (int hiHatSampleIndex, SampleProperties::SampleType sampleType);
    void sampleConvert (juce::AudioFormatReader* reader, juce::AudioBuffer<float>& outputBuffer);

    void applyExplicitColours ();

    void lookAndFeelChanged () override;
    void resized () override;
    void timerCallback () override;
};