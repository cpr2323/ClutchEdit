#pragma once
#include <JuceHeader.h>

class FileDropLabel : public juce::Label,
                      public juce::FileDragAndDropTarget
{
public:
    std::function<void (juce::StringArray)> onFilesSelected;
    void setFileExistState (bool doesFileExist)
    {
        fileExists = doesFileExist;
        setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
    }
private:
    bool fileExists { false };
    juce::Colour hoverColor { juce::Colours::lightseagreen };
    bool isInterestedInFileDrag ([[maybe_unused]] const juce::StringArray& files) override
    {
        return files.size () == 1;
    }

    void filesDropped (const juce::StringArray& files, int x, int y) override
    {
        if (onFilesSelected != nullptr)
            onFilesSelected (files);
    }

    void fileDragEnter (const juce::StringArray& files, int x, int y) override
    {
        setColour (juce::Label::ColourIds::textColourId, hoverColor);
    }

    void fileDragMove (const juce::StringArray& files, int, int) override
    {
        setColour (juce::Label::ColourIds::textColourId, hoverColor);
    }

    void fileDragExit (const juce::StringArray&) override
    {
        setColour (juce::Label::ColourIds::textColourId, fileExists ? juce::Colours::white : juce::Colours::grey);
    }
};

class SampleBankComponent : public juce::Component,
                                   juce::Timer
{
public:
    enum class WhichHiHat { opened, closed };

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

    void copySampleFile (juce::File sourceFile, int surfaceIndex, WhichHiHat whichHiHat);
    void sampleConvert (juce::AudioFormatReader* reader, juce::AudioBuffer<float>& outputBuffer);

    void paint (juce::Graphics& g) override;
    void resized () override;
    void timerCallback () override;
};
