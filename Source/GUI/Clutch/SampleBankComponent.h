#pragma once
#include <JuceHeader.h>
#include "../../Clutch/Audio/AudioPlayerProperties.h"

class FileDropLabel : public juce::Label,
                      public juce::FileDragAndDropTarget,
                      public juce::Timer
{
public:
    FileDropLabel ()
    {
        startTimer (2);
    }

    std::function<void (juce::StringArray)> onFilesSelected;
    std::function<void (const juce::MouseEvent& mouseEvent)> onMouseUp;

    void setFileExistState (bool doesFileExist)
    {
        fileExists = doesFileExist;
        setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
    }
private:
    bool fileExists { false };
    juce::Colour hoverColor { juce::Colours::lightseagreen };
    int dropIndicatorTime { 0 };
    juce::Colour fadingColor { juce::Colours::green };

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
        dropIndicatorTime = 300;
        fadingColor = juce::Colours::green;
        setColour (juce::Label::ColourIds::textColourId, fadingColor);
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
        if (dropIndicatorTime > 0)
        {
            dropIndicatorTime -= 1;
            setColour (juce::Label::ColourIds::textColourId, fadingColor);
            if (dropIndicatorTime < 0)
            {
                setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
            }
            fadingColor = fadingColor.brighter (0.006);
            repaint ();
        }
    }
};

class SampleBankComponent : public juce::Component,
                                   juce::Timer
{
public:
    enum class HiHatState { opened, closed };

    SampleBankComponent ();
    ~SampleBankComponent ();

    void init (juce::ValueTree rootPropertiesVT);

    void setBankName (const juce::String& newBankName);
    void updateFileStatus ();
    void setBankFolder (const juce::File& newBankFolder);

private:
    juce::Label bankName;
    struct SurfaceInfo
    {
        juce::Label name;
        FileDropLabel openedName;
        FileDropLabel closedName;
    };
    std::array<SurfaceInfo, 16> surfaceComponents;
    juce::File banksRootFolder;
    AudioPlayerProperties audioPlayerProperties;

    void copySampleFile (juce::File sourceFile, int surfaceIndex, HiHatState hiHatState);
    void sampleConvert (juce::AudioFormatReader* reader, juce::AudioBuffer<float>& outputBuffer);

    void paint (juce::Graphics& g) override;
    void resized () override;
    void timerCallback () override;
};
