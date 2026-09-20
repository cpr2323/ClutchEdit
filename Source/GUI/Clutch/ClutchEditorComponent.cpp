#include "ClutchEditorComponent.h"
#include "../Theme/ClutchColourIds.h"
#include "oolib/Properties/PersistentRootProperties.h"
#include "../../Clutch/LedColorList.h"
#include "../../Clutch/ProjectManager.h"

ClutchEditorComponent::ClutchEditorComponent ()
{
    auto addComponentWithViewPort = [this] (juce::String title, juce::Component* component, int width, int height)
    {
        auto* viewPort { new juce::Viewport () };
        component->setSize (width, height);
        viewPort->setViewedComponent (component, false);
        editorTabs.addTab (title, findColour (ClutchColours::windowBackground), viewPort, true);
    };

    editorTabs.setTabBarDepth (kTabBarHeight);
    editorTabs.setOutline (0);
    addComponentWithViewPort ("SAMPLES", &sampleManagerComponent, 1245, 375);
    addComponentWithViewPort ("SETTINGS", &settingsEditorComponent, 1200, 650);
    addComponentWithViewPort ("PATTERNS", &patternListEditorComponent, 1060, 697);
    addComponentWithViewPort ("EFFECTS", &effectEditorComponent, 223, 263);
    editorTabs.onTabChanged = [this] (int tabIndex)
    {
        guiProperties.setActiveTab (tabIndex, false);
    };
    addAndMakeVisible (editorTabs);

    // TOOLS BUTTON
    toolsButton.onClick = [this] ()
    {
        juce::PopupMenu pm;
        pm.addSectionHeader ("TOOLS");
        pm.addSeparator ();
        pm.addItem ("New", true, false, [this] ()
        {
            auto doNew = [this] ()
            {
                fileChooser.reset (new juce::FileChooser ("Please select the Clutch HIHAT.INI file you want to create...", {}, "*.INI"));
                fileChooser->launchAsync (juce::FileBrowserComponent::saveMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::warnAboutOverwriting, [this] (const juce::FileChooser& fc) mutable
                {
                    if (fc.getURLResults ().size () == 1 && fc.getURLResults () [0].isLocalFile ())
                    {
                        juce::File fileToCreate (fc.getURLResults () [0].getLocalFile ().getFullPathName ());
                        if (fileToCreate.getFileExtension () == "")
                            fileToCreate = fileToCreate.withFileExtension (".INI");
                        if (fileToCreate.isDirectory ())
                            return;
                        projectManagerProperties.doCleanUpTempFiles (false);
                        fileToCreate.deleteFile ();
                        fileToCreate.appendData (BinaryData::HIHAT_INI, BinaryData::HIHAT_INISize);
                        auto projectPath { fileToCreate.getParentDirectory () };
                        for (auto& ledColor : gLedColorList)
                        {
                            auto bankAColorDirectory { projectPath.getChildFile (ledColor) };
                            bankAColorDirectory.createDirectory ();
                        }
                        audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
                        appProperties.setMostRecentFolder (fileToCreate.getParentDirectory ().getFullPathName ());
                        appProperties.addRecentlyUsedFile (fileToCreate.getFullPathName ());
                    }
                }, nullptr);
            };
            if (! projectManagerProperties.getProjectEdited ())
            {
                doNew ();
            }
            else
            {
                juce::AlertWindow::showOkCancelBox (juce::AlertWindow::WarningIcon, "WARNING: Edits Have Been Made",
                                                    "You have not saved the project that you have edited.\n  Select Continue to lose your changes.\n  Select Cancel to go back and save.", "Continue (lose changes)", "Cancel", nullptr,
                                                    juce::ModalCallbackFunction::create ([this, doNew] (int option)
                                                    {
                                                        juce::MessageManager::callAsync ([this, option, doNew] ()
                                                        {
                                                            if (option == 1) // Continue
                                                                doNew ();
                                                        });
                                                    }));
            }
        });
        pm.addItem ("Default", true, false, [this] ()
        {
            ProjectManager::copy (defaultClutchProperties.getValueTree (), clutchProperties.getValueTree ());
        });
        pm.addItem ("Revert", true, false, [this] ()
        {
            ProjectManager::copy (uneditedClutchProperties.getValueTree (), clutchProperties.getValueTree ());
        });
        pm.showMenuAsync (juce::PopupMenu::Options ().withTargetComponent (&toolsButton));
    };
    addAndMakeVisible (toolsButton);

    // SAVE BUTTON
    saveButton.setEnabled (false);
    saveButton.onClick = [this] ()
    {
        projectManagerProperties.doSaveProject (false);
    };
    addAndMakeVisible (saveButton);

    // OPEN BUTTON
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
                    juce::File fileToLoad (fc.getURLResults () [0].getLocalFile ().getFullPathName ());
                    if (fileToLoad.isDirectory ())
                        return;
                    audioPlayerProperties.setPlayState (AudioPlayerProperties::PlayState::stop, false);
                    appProperties.setMostRecentFolder (fileToLoad.getParentDirectory ().getFullPathName ());
                    appProperties.addRecentlyUsedFile (fileToLoad.getFullPathName ());
                }
            }, nullptr);
        };

        if (!projectManagerProperties.getProjectEdited ())
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
        saveButton.setPrimary (projectEdited);
    };
    audioPlayerProperties.wrap (runtimeRootProperties.getValueTree (), AudioPlayerProperties::WrapperType::client, AudioPlayerProperties::EnableCallbacks::no);
    uneditedClutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    defaultClutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "default"), ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    clutchProperties.wrap (runtimeRootProperties.getValueTree ().getChildWithProperty(ClutchProperties::NamePropertyId, "edited"), ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    // TODO pass in the clutch VT directly instead of root VT
    settingsEditorComponent.init (rootPropertiesVT);
    patternListEditorComponent.init (rootPropertiesVT);
    effectEditorComponent.init (rootPropertiesVT);
    sampleManagerComponent.init (rootPropertiesVT);

    saveButton.setEnabled (projectManagerProperties.getProjectEdited ());
    saveButton.setPrimary (projectManagerProperties.getProjectEdited ());

    editorTabs.setCurrentTabIndex (guiProperties.getActiveTab ());
}

// The tab background is a stored colour rather than one looked up while painting,
// so it has to be re-applied whenever the palette changes.
void ClutchEditorComponent::applyTabColours ()
{
    for (auto tabIndex { 0 }; tabIndex < editorTabs.getNumTabs (); ++tabIndex)
        editorTabs.setTabBackgroundColour (tabIndex, findColour (ClutchColours::windowBackground));
}

void ClutchEditorComponent::lookAndFeelChanged ()
{
    juce::Component::lookAndFeelChanged ();
    applyTabColours ();
}

void ClutchEditorComponent::resized ()
{
    editorTabs.setBounds (getLocalBounds ());

    // the tools sit in the tab strip, right aligned, so the tabs and the project
    // actions share one row
    auto toolsBounds { getLocalBounds ().removeFromTop (kTabBarHeight).reduced (6, 0) };
    auto place = [&toolsBounds] (ActionButton& button)
    {
        const auto width { button.getIdealWidth () };
        button.setBounds (toolsBounds.removeFromRight (width).withSizeKeepingCentre (width, ActionButton::kNormalHeight));
        toolsBounds.removeFromRight (6);
    };
    place (toolsButton);
    place (openButton);
    place (saveButton);
}

void ClutchEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (findColour (ClutchColours::windowBackground));
}
