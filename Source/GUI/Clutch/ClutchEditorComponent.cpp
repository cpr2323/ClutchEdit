#include "ClutchEditorComponent.h"
//#include "../../Clutch/HiHatIniData.h"
#include "../../Utility/PersistentRootProperties.h"

ClutchEditorComponent::ClutchEditorComponent ()
{
    auto addComponentWithViewPort = [this] (juce::String title, juce::Component* component, int width, int height)
    {
        auto* viewPort { new juce::Viewport () };
        component->setSize (width, height);
        viewPort->setViewedComponent (component, false);
        const auto thumbColor { juce::Colours::darkgrey.brighter (0.4f) };
        viewPort->getHorizontalScrollBar ().setColour (juce::ScrollBar::ColourIds::thumbColourId, thumbColor);
        viewPort->getVerticalScrollBar ().setColour (juce::ScrollBar::ColourIds::thumbColourId, thumbColor);
        editorTabs.addTab (title, juce::Colours::darkgrey, viewPort, true);
    };
    addComponentWithViewPort ("SAMPLES", &sampleManagerComponent, 1245, 375);
    addComponentWithViewPort ("SETTINGS", &settingsEditorComponent, 1200, 555);
    addComponentWithViewPort ("PATTERNS", &patternListEditorComponent, 1060, 697);
    addComponentWithViewPort ("EFFECTS", &effectEditorComponent, 223, 263);
    editorTabs.onTabChanged = [this] (int tabIndex)
    {
        guiProperties.setActiveTab (tabIndex, false);
    };
    addAndMakeVisible (editorTabs);

    // SETTINGS BUTTON
    settingsButton.setButtonText ("SETTINGS");
    settingsButton.onClick = [this] ()
    {
        audioPlayerProperties.showConfigDialog (false);
    };
    addAndMakeVisible (settingsButton);

    // OPEN BUTTON
    openButton.setButtonText ("OPEN");
    openButton.onClick = [this] ()
    {
    auto openFile = [this] ()
    {
        fileChooser.reset (new juce::FileChooser ("Please select the Clutch HIHAT.INI file you want to edit...", {}, "*.INI"));
        fileChooser->launchAsync (juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles, [this] (const juce::FileChooser& fc) mutable
        {
            if (fc.getURLResults ().size () == 1 && fc.getURLResults () [0].isLocalFile ())
            {
                projectManagerProperties.doCleanUpTempFiles (false);
                auto urlResult { fc.getURLResults () [0] };
                juce::File fileToLoad (urlResult.getLocalFile ().getFullPathName ());
                if (fileToLoad.isDirectory ())
                    return;
                audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
                appProperties.setMostRecentFolder (fileToLoad.getParentDirectory ().getFullPathName ());
                appProperties.addRecentlyUsedFile (fileToLoad.getFullPathName ());
            }
        }, nullptr);
    };

        if (! projectManagerProperties.getProjectEdited ())
        {
            openFile ();
        }
        else
        {
            juce::AlertWindow::showOkCancelBox (juce::AlertWindow::WarningIcon, "WARNING: Edits Have Been Made",
                                                "You have not saved the project that you have edited.\n  Select Continue to lose your changes.\n  Select Cancel to go back and save.", "Continue (lose changes)", "Cancel", nullptr,
                                                juce::ModalCallbackFunction::create ([this, openFile] (int option)
                                                {
                                                    juce::MessageManager::callAsync ([this, option, openFile] ()
                                                    {
                                                        if (option == 1) // Continue
                                                            openFile ();
                                                    });
                                                }));
        }
    };
    addAndMakeVisible (openButton);

    // SAVE BUTTON
    saveButton.setButtonText ("SAVE");
    saveButton.setEnabled (false); // TODO: do this when the edit compare functionality is working
    saveButton.onClick = [this] ()
    {
        projectManagerProperties.doSaveProject (false);
    };
    addAndMakeVisible (saveButton);
}

ClutchEditorComponent::~ClutchEditorComponent ()
{
}

void ClutchEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    PersistentRootProperties persistentRootProperties (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
    appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::client, AppProperties::EnableCallbacks::yes);
    guiProperties.wrap (persistentRootProperties.getValueTree (), GuiProperties::WrapperType::client, GuiProperties::EnableCallbacks::no);

    runtimeRootProperties.wrap (rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no);
    projectManagerProperties.wrap (runtimeRootProperties.getValueTree (), ProjectManagerProperties::WrapperType::owner, ProjectManagerProperties::EnableCallbacks::yes);
    projectManagerProperties.onProjectEditedChange = [this] (bool projectEdited)
    {
        saveButton.setEnabled (projectEdited);
    };
    audioPlayerProperties.wrap (runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::client, AudioPlayerProperties::EnableCallbacks::no);
    clutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty(ClutchProperties::NamePropertyId, "edited"), ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    // TODO pass in the clutch VT directly instead of root VT
    settingsEditorComponent.init (rootPropertiesVT);
    patternListEditorComponent.init (rootPropertiesVT);
    effectEditorComponent.init (rootPropertiesVT);
    sampleManagerComponent.init (rootPropertiesVT);

    saveButton.setEnabled (projectManagerProperties.getProjectEdited ());

    editorTabs.setCurrentTabIndex (guiProperties.getActiveTab ());
}

void ClutchEditorComponent::resized()
{
    auto bounds { getLocalBounds () };
    auto topLine { bounds.removeFromTop (30) };
    settingsButton.setBounds (topLine.removeFromRight (100).reduced (5));
    saveButton.setBounds (topLine.removeFromRight (100).reduced (5));
    openButton.setBounds (topLine.removeFromRight (100).reduced (5));
    editorTabs.setBounds (getLocalBounds ());
}

void ClutchEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey.darker(0.7f));
}