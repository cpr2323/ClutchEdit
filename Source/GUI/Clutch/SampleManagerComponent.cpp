#include "SampleManagerComponent.h"
#include "../../Utility/PersistentRootProperties.h"

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
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::owner, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::owner, AppProperties::EnableCallbacks::yes);
    appProperties.onMostRecentFileChange = [this] (juce::String folderName)
    {
        updateBanks ();
    };
    updateBanks ();
}

void SampleManagerComponent::updateBanks ()
{
    for (auto& sampleBankComponent : sampleBankComponents)
    {
        sampleBankComponent.setBankFolder (juce::File (appProperties.getRecentlyUsedFile (0)).getParentDirectory ().getFullPathName ());
        sampleBankComponent.updateFileStatus ();
    }
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