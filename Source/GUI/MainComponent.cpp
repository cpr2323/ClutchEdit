#include "MainComponent.h"
#include "../Utility/PersistentRootProperties.h"

const auto toolWindowHeight { 30 };

MainComponent::MainComponent (juce::ValueTree rootPropertiesVT)
{
    setSize (1117, 609);

    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    guiProperties.wrap (persistentRootProperties.getValueTree (), GuiProperties::WrapperType::client, GuiProperties::EnableCallbacks::no);

    clutchEditorComponent.init (rootPropertiesVT);
    currentFolderComponent.init (rootPropertiesVT);

    restoreLayout ();

    addAndMakeVisible (currentFolderComponent);
    addAndMakeVisible (clutchEditorComponent);
}

void MainComponent::restoreLayout ()
{
    const auto [pane1Size, pane2Size, pane3Size] { guiProperties.getPaneSizes () };
}

void MainComponent::saveLayoutChanges ()
{
}

// void MainComponent::paint ([[maybe_unused]] juce::Graphics& g)
// {
//     g.setColour (juce::Colours::red);
// }

void MainComponent::resized ()
{
    auto localBounds { getLocalBounds () };
    currentFolderComponent.setBounds (localBounds.removeFromTop (30));
    clutchEditorComponent.setBounds (localBounds);
}
