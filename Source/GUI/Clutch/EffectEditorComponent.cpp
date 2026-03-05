#include "EffectEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Clutch/LedColorList.h"
#include "../../Utility/RuntimeRootProperties.h"

enum EffectId
{
    none,
    bitcrush,
    chorus,
    combfilter,
    djfilter,
    dubecho,
    glitch,
    reverb,
    sputter
};

const std::array<juce::String, 9> effectNames
{
    "NONE",         // 0
    "BITCRUSH",     // 1
    "CHORUS",       // 2
    "COMBFILTER",   // 3
    "DJFILTER",     // 4
    "DUBECHO",      // 5
    "GLITCH",       // 6
    "REVERB",       // 7
    "SPUTTER"       // 8
};

const std::array<int, 8> effectDefaults
{
    EffectId::sputter,    // WHITE
    EffectId::bitcrush,   // RED
    EffectId::combfilter, // GREEN
    EffectId::djfilter,   // BLUE
    EffectId::dubecho,    // ORANGE
    EffectId::chorus,     // CYAN
    EffectId::reverb,     // VIOLET
    EffectId::glitch      // YELLOW
};

EffectEditorComponent::EffectEditorComponent ()
{
    for (auto curEffectIndex { 0 }; curEffectIndex < 8; ++curEffectIndex)
    {
        auto& effectEditor { effectEditors [curEffectIndex] };
        effectEditor.setTooltip ("");
        for (auto effectIndex { 0 }; effectIndex < effectNames.size (); ++effectIndex)
            effectEditor.addItem (effectNames [effectIndex], effectIndex + 1);
        effectEditor.setLookAndFeel (&noArrowComboBoxLnF);
        effectEditor.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (0.7f));
        effectEditor.setSelectedId (1);
        effectEditor.setComponentID ("StepComboBox" + juce::String (curEffectIndex));
        effectEditor.onDragCallback = [this, &effectEditor, curEffectIndex] (DragSpeed dragSpeed, int direction)
        {
            const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
            const auto stepValue { effectEditor.getSelectedId () };
            effectEditor.setSelectedId (std::clamp (stepValue + scrollAmount, 1, 9), juce::NotificationType::dontSendNotification);
            onEffectUiChanged (curEffectIndex);
        };
        effectEditor.onPopupMenuCallback = [this, curEffectIndex] ()
        {
            auto* popupMenuLnF { new juce::LookAndFeel_V4 };
            popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));
            juce::PopupMenu pm;
            pm.setLookAndFeel (popupMenuLnF);
            pm.addSectionHeader ("Effect " + juce::String (curEffectIndex + 1));
            pm.addSeparator ();
            pm.addItem ("Default", true, false, [this, curEffectIndex] ()
            {
                effectEditors [curEffectIndex].setText (effectNames[effectDefaults[curEffectIndex]], juce::NotificationType::sendNotification);
            });
            pm.addItem ("Revert", true, false, [this, curEffectIndex] ()
            {
                effectEditors [curEffectIndex].setText (uneditedEffectProperties[curEffectIndex].getEffect (), juce::NotificationType::sendNotification);
            });

            pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
        };
        effectEditor.onChange = [this, curEffectIndex] ()
        {
            onEffectUiChanged (curEffectIndex);
        };
        addAndMakeVisible (effectEditor);
    }

    for (auto effectIndex { 0 }; effectIndex < 8; ++effectIndex)
    {
        auto& effectLabel { effectLabels [effectIndex] };
        effectLabel.setText (gLedColorList [effectIndex], juce::NotificationType::dontSendNotification);
        effectLabel.setJustificationType (juce::Justification::centredLeft);
        addAndMakeVisible (effectLabel);
        auto& effectEditor { effectEditors [effectIndex] };
        effectEditor.setJustificationType (juce::Justification::centredLeft);
        effectEditor.setSelectedId (1);
        addAndMakeVisible (effectEditor);
    }
}

EffectEditorComponent::~EffectEditorComponent ()
{
    for (auto& effectEditor : effectEditors)
        effectEditor.setLookAndFeel (nullptr);
}

void EffectEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, RuntimeRootProperties::WrapperType::client, RuntimeRootProperties::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "edited"), ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    EffectListProperties effectListProperties (clutchProperties.getValueTree (), EffectListProperties::WrapperType::client, EffectListProperties::EnableCallbacks::no);
    effectListProperties.forEachEffect ([this] (juce::ValueTree effectVT, int effectIndex)
    {
        effectProperties [effectIndex].wrap (effectVT, EffectProperties::WrapperType::client, EffectProperties::EnableCallbacks::yes);
        effectProperties [effectIndex].onEffectChange = [this, effectIndex] (juce::String) { onEffectDataChanged (effectIndex); };
        onEffectDataChanged (effectIndex);
        return true;
    });
    ClutchProperties uneditedClutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), ClutchProperties::WrapperType::client, ClutchProperties::EnableCallbacks::no);
    EffectListProperties uneditedEffectListProperties (uneditedClutchProperties.getValueTree (), EffectListProperties::WrapperType::client, EffectListProperties::EnableCallbacks::no);
    uneditedEffectListProperties.forEachEffect ([this] (juce::ValueTree effectVT, int effectIndex)
    {
        uneditedEffectProperties [effectIndex].wrap (effectVT, EffectProperties::WrapperType::client, EffectProperties::EnableCallbacks::yes);
        return true;
    });
}

void EffectEditorComponent::paintOverChildren (juce::Graphics& g)
{
    g.setColour (juce::Colours::black);
    g.drawRect (effectLabels [0].getX (), effectLabels [0].getY () - 5, effectEditors [0].getRight () - effectLabels [0].getX () + 5,
                effectLabels [7].getBottom () - effectLabels [0].getY () + 10);
}

void EffectEditorComponent::resized ()
{
    for (auto effectIndex { 0 }; effectIndex < effectEditors.size (); ++effectIndex)
    {
        effectLabels [effectIndex].setBounds (10, 15 + (effectIndex * 30), 100, 25);
        effectEditors [effectIndex].setBounds (10 + 100, 15 + (effectIndex * 30), 100, 25);
    }
}

void EffectEditorComponent::onEffectUiChanged (int effectIndex)
{
    effectProperties [effectIndex].setEffect (effectEditors [effectIndex].getText (), juce::NotificationType::dontSendNotification);
}

void EffectEditorComponent::onEffectDataChanged (int effectIndex)
{
    effectEditors [effectIndex].setText (effectProperties [effectIndex].getEffect (), juce::NotificationType::dontSendNotification);
}

