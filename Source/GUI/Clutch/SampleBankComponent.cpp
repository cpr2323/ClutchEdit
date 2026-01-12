#include "SampleBankComponent.h"

SampleBankComponent::SampleBankComponent ()
{
    addAndMakeVisible(bankName);
    for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
    {
        auto& surfaceComponent { surfaceComponents [surfaceIndex] };
        surfaceComponent.name.setText (juce::String (surfaceIndex + 1), juce::NotificationType::dontSendNotification);
        surfaceComponent.openedName.setText ("Opened", juce::NotificationType::dontSendNotification);
        surfaceComponent.openedName.onFilesSelected = [this, surfaceIndex] (juce::StringArray files)
        {
            if (files.size () == 1)
                copySampleFile(juce::File (files[0]), surfaceIndex, WhichHiHat::opened);
        };
        surfaceComponent.closedName.setText ("Closed", juce::NotificationType::dontSendNotification);
        surfaceComponent.closedName.onFilesSelected = [this, surfaceIndex] (juce::StringArray files)
        {
            if (files.size () == 1)
                copySampleFile (juce::File (files [0]), surfaceIndex, WhichHiHat::closed);
        };
        addAndMakeVisible (surfaceComponent.name);
        addAndMakeVisible (surfaceComponent.openedName);
        addAndMakeVisible (surfaceComponent.closedName);
    }

    updateFileStatus ();
    startTimer (2000);
}

SampleBankComponent::~SampleBankComponent ()
{

}

void SampleBankComponent::copySampleFile (juce::File sourceFile, int surfaceIndex, WhichHiHat whichHiHat)
{
    juce::String fileName { juce::String (surfaceIndex + 1).paddedLeft ('0', 2) + (whichHiHat == WhichHiHat::closed ? "C" : "O") + "H.wav"};
    juce::File destFile { bankFolder.getChildFile (bankName.getText ()).getChildFile (fileName) };
    sourceFile.copyFileTo (destFile);
    updateFileStatus ();
}

void SampleBankComponent::updateFileStatus ()
{
    if (bankFolder != juce::File ())
    {
        for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
        {
            auto doesFileExist = [this] (int surfaceIndex, WhichHiHat whichHiHat)
            {
                juce::String fileName { juce::String (surfaceIndex + 1).paddedLeft ('0', 2) + juce::String (whichHiHat == WhichHiHat::opened ? "OH" : "CH") };
                auto file { bankFolder.getChildFile (bankName.getText ()).getChildFile (fileName).withFileExtension ("wav") };
                return file.existsAsFile ();
            };
            surfaceComponents [surfaceIndex].openedName.setFileExists (doesFileExist (surfaceIndex, WhichHiHat::opened));
            surfaceComponents [surfaceIndex].closedName.setFileExists (doesFileExist (surfaceIndex, WhichHiHat::closed));
        }
    }
    repaint ();
}

void SampleBankComponent::setBankFolder (const juce::File& newBankFolder)
{
    bankFolder = newBankFolder;
}

void SampleBankComponent::paint (juce::Graphics& g)
{
}

void SampleBankComponent::resized ()
{
    auto bounds { getLocalBounds ().reduced (5) };
    bankName.setBounds (bounds.removeFromTop (20));
    for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
    {
        auto& surfaceComponent { surfaceComponents [surfaceIndex] };
        auto surfaceBounds { bounds.removeFromTop (20).withTrimmedLeft (1) };
        surfaceComponent.name.setBounds (surfaceBounds.removeFromLeft (25));

        surfaceComponent.openedName.setBounds (surfaceBounds.removeFromLeft (50));
        surfaceComponent.closedName.setBounds (surfaceBounds);
    }
}

void SampleBankComponent::timerCallback ()
{
    updateFileStatus ();
}

void SampleBankComponent::setBankName (const juce::String& newBankName)
{
    bankName.setText (newBankName, juce::NotificationType::dontSendNotification);
    updateFileStatus ();
}
