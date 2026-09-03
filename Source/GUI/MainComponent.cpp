#include "MainComponent.h"
#include "oolib/Properties/PersistentRootProperties.h"

const auto toolWindowHeight { 30 };

MainComponent::MainComponent (juce::ValueTree rootPropertiesVT)
{
    setSize (1260, 760);

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
}

void MainComponent::saveLayoutChanges ()
{
}

void MainComponent::resized ()
{
    auto localBounds { getLocalBounds () };
    currentFolderComponent.setBounds (localBounds.removeFromTop (30));
    clutchEditorComponent.setBounds (localBounds);
}
