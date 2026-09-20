#include "MainComponent.h"
#include "Theme/ClutchColourIds.h"
#include "oolib/Properties/PersistentRootProperties.h"

const auto kPathBarHeight { 34 };

MainComponent::MainComponent (juce::ValueTree rootPropertiesVT)
{
    setSize (1260, 760);
    rootProperties = rootPropertiesVT;

    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    guiProperties.wrap (persistentRootProperties.getValueTree (), GuiProperties::WrapperType::client, GuiProperties::EnableCallbacks::yes);
    guiProperties.onShowSettingsDialog = [this] () { showSettingsDialog (); };

    clutchEditorComponent.init (rootPropertiesVT);
    currentFolderComponent.init (rootPropertiesVT);

    restoreLayout ();

    addAndMakeVisible (currentFolderComponent);
    addAndMakeVisible (clutchEditorComponent);

    // The theme is installed before any window exists, so the startup pass of
    // sendLookAndFeelChange reached nothing. Without this, every component that
    // applies its own colours in lookAndFeelChanged stays unstyled until the
    // background slider is first moved.
    sendLookAndFeelChange ();
}

void MainComponent::showSettingsDialog ()
{
    juce::DialogWindow::LaunchOptions options;
    options.escapeKeyTriggersCloseButton = true;
    options.dialogBackgroundColour = findColour (ClutchColours::dialogBackground);
    options.dialogTitle = "SETTINGS";
    options.resizable = false;
    auto* settingsComponent { new SettingsDialogComponent () };
    settingsComponent->init (rootProperties);
    // sized to the largest page, measured after the pages are built
    settingsComponent->setBounds (settingsComponent->getPreferredBounds ());
    options.content.setOwned (settingsComponent);
    options.launchAsync ();
}

void MainComponent::restoreLayout ()
{
}

void MainComponent::saveLayoutChanges ()
{
}

void MainComponent::paint (juce::Graphics& g)
{
    // the children do not cover every pixel, so this has to paint the gaps -
    // without it, a palette change leaves the old background showing through
    g.fillAll (findColour (ClutchColours::windowBackground));
}

void MainComponent::resized ()
{
    auto localBounds { getLocalBounds () };
    currentFolderComponent.setBounds (localBounds.removeFromTop (kPathBarHeight));
    clutchEditorComponent.setBounds (localBounds);
}
