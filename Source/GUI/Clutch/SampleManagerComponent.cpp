#include "SampleManagerComponent.h"

SampleBankComponent::SampleBankComponent ()
{
    addAndMakeVisible(bankName);
    for (auto surfaceIndex { 0 }; surfaceIndex < 8; ++surfaceIndex)
    {
        auto& surfaceComponent { surfaceComponents [surfaceIndex] };
        surfaceComponent.name.setText (juce::String (surfaceIndex + 1), juce::NotificationType::dontSendNotification);
        surfaceComponent.openedName.setText ("Opened", juce::NotificationType::dontSendNotification);
        surfaceComponent.closedName.setText ("Closed", juce::NotificationType::dontSendNotification);
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

void SampleBankComponent::updateFileStatus ()
{
    enum class WhichHiHat { opened, closed };
    for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
    {
        auto doesFileExist = [this] (int surfaceIndex, WhichHiHat whichHiHat)
        {
            //auto appDataPath = juce::File (runtimeRootProperties.getAppDataPath ()).getChildFile ("sdcard_test");
            juce::String fileName { juce::String (surfaceIndex + 1).paddedLeft ('0', 2) + juce::String (whichHiHat == WhichHiHat::opened ? "OH" : "CH") };
            auto file { juce::File ("C:/Users/cpran/AppData/Roaming/ClutchEdit/sdcard_test").getChildFile (bankName.getText ()).getChildFile (fileName).withFileExtension("wav")};
            return file.existsAsFile ();
        };
        surfaceComponents [surfaceIndex].openedName.setColour (juce::Label::ColourIds::textColourId,
                                                               doesFileExist (surfaceIndex, WhichHiHat::opened) ? juce::Colours::white : juce::Colours::grey);
        surfaceComponents [surfaceIndex].closedName.setColour (juce::Label::ColourIds::textColourId,
                                                               doesFileExist (surfaceIndex, WhichHiHat::closed) ? juce::Colours::white : juce::Colours::grey);
    }
    repaint ();
}

void SampleBankComponent::paint (juce::Graphics& g)
{
    updateFileStatus ();
}

void SampleBankComponent::resized ()
{
    auto bounds { getLocalBounds ().reduced (5) };
    bankName.setBounds (bounds.removeFromTop (20));
    for (auto surfaceIndex { 0 }; surfaceIndex < surfaceComponents.size (); ++surfaceIndex)
    {
        auto& surfaceComponent { surfaceComponents [surfaceIndex] };
        auto surfaceBounds { bounds.removeFromTop (20).withTrimmedLeft (15) };
        surfaceComponent.name.setBounds (surfaceBounds.removeFromLeft (15));

        surfaceComponent.openedName.setBounds (surfaceBounds);
        auto closedSurfaceBounds { bounds.removeFromTop (20).withTrimmedLeft (30) };
        surfaceComponent.closedName.setBounds (closedSurfaceBounds);
    }
}

void SampleBankComponent::timerCallback ()
{

}

void SampleBankComponent::setBankName (const juce::String& newBankName)
{
    bankName.setText (newBankName, juce::NotificationType::dontSendNotification);
    updateFileStatus ();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

SampleManagerComponent::SampleManagerComponent ()
{
    std::array<juce::String, 8> patternNames
    {
        "WHITE",
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "BLUE",
        "CYAN",
        "VIOLET"
    };

    for (auto sampleBankIndex { 0 }; sampleBankIndex < sampleBankComponents.size (); ++sampleBankIndex)
    {
        auto& sampleBankComponent { sampleBankComponents[sampleBankIndex] };
        sampleBankComponent.setBankName (patternNames [sampleBankIndex]);
        addAndMakeVisible (sampleBankComponent);
    }
}

SampleManagerComponent::~SampleManagerComponent ()
{

}

void SampleManagerComponent::init (juce::ValueTree rootPropertiesVT)
{

}

void SampleManagerComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::black);
    for (auto& sampleBankComponent : sampleBankComponents)
    {
        g.drawRect (sampleBankComponent.getBounds ());
    }
}

void SampleManagerComponent::resized ()
{
    constexpr auto kXOffset { 10 };
    constexpr auto kYOffset { 10 };
    constexpr auto kBankWidth { 150 };
    constexpr auto kSpaceBetweenBanks { 5 };
    for (auto bankIndex { 0 }; bankIndex < sampleBankComponents.size (); ++bankIndex)
    {
        sampleBankComponents[bankIndex].setBounds (kXOffset + (bankIndex * (kBankWidth + kSpaceBetweenBanks)), kYOffset, kBankWidth, getHeight () - (kYOffset * 2));
    }
}