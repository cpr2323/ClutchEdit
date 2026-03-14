#include "SampleManagerComponent.h"
#include "../../Clutch/BankListProperties.h"
#include "../../Clutch/BankProperties.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/PersistentRootProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

SampleManagerComponent::SampleManagerComponent ()
{
    for (auto sampleBankIndex { 0 }; sampleBankIndex < sampleBankComponents.size (); ++sampleBankIndex)
    {
        auto& sampleBankComponent { sampleBankComponents[sampleBankIndex] };
        sampleBankComponent.setComponentID ("SBC" + juce::String (sampleBankIndex));
        addAndMakeVisible (sampleBankComponent);
    }
}

SampleManagerComponent::~SampleManagerComponent ()
{
}

void SampleManagerComponent::init (juce::ValueTree rootPropertiesVT)
{
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::client, AppProperties::EnableCallbacks::yes);
    appProperties.onMostRecentFileChange = [this] ([[maybe_unused]] juce::String folderName)
    {
        // TODO : this should be handled elsewhere
        updateBanks ();
    };

    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no);
    ClutchProperties editedClutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "edited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    BankListProperties bankListProperties { editedClutchProperties.getValueTree (), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    BankListProperties uneditedBankListProperties { runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no };
    bankListProperties.forEachBank ([this, rootPropertiesVT, uneditedBankListPropertiesVT = uneditedBankListProperties.getValueTree ()] (juce::ValueTree bankPropertiesVT, int bankIndex)
    {
        auto* sampleBankComponent { dynamic_cast<SampleBankComponent*> (findChildWithID ("SBC" + juce::String (bankIndex))) };
        jassert (sampleBankComponent != nullptr);
        BankListProperties uneditedBankListProperties (uneditedBankListPropertiesVT, BankListProperties::WrapperType::client, BankListProperties::EnableCallbacks::no);

        BankProperties uneditedBankProperties (uneditedBankListProperties.getBankVT (bankIndex), BankProperties::WrapperType::client, BankProperties::EnableCallbacks::no);
        sampleBankComponent->init (rootPropertiesVT, bankPropertiesVT, uneditedBankProperties.getValueTree ());
        return true;
    });

    // TODO : this should be handled elsewhere
    updateBanks ();
}

void SampleManagerComponent::updateBanks ()
{
    for (auto& sampleBankComponent : sampleBankComponents)
        sampleBankComponent.setBankFolder (juce::File (appProperties.getRecentlyUsedFile (0)).getParentDirectory ().getFullPathName ());
}

void SampleManagerComponent::paint (juce::Graphics& g)
{
    const auto kSectionOutlineColour { juce::Colour (0xff6a6a6a) };
    g.setColour (kSectionOutlineColour.brighter (0.4f));
    constexpr auto kSectionCornerSize { 4.0f };
    constexpr auto kSectionOutlineThickness { 1.0f };
    for (auto& sampleBankComponent : sampleBankComponents)
        g.drawRoundedRectangle (sampleBankComponent.getBounds ().toFloat (), kSectionCornerSize, kSectionOutlineThickness);
}

void SampleManagerComponent::resized ()
{
    constexpr auto kXOffset { 10 };
    constexpr auto kYOffset { 10 };
    constexpr auto kBankWidth { 150 };
    constexpr auto kSpaceBetweenBanks { 5 };
    for (auto bankIndex { 0 }; bankIndex < sampleBankComponents.size (); ++bankIndex)
        sampleBankComponents[bankIndex].setBounds (kXOffset + (bankIndex * (kBankWidth + kSpaceBetweenBanks)), kYOffset, kBankWidth, getHeight () - (kYOffset * 2));
}