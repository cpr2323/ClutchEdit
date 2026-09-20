#include "EffectEditorComponent.h"
#include "../Theme/UiComponents.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Clutch/LedColorList.h"
#include "oolib/Properties/RuntimeRootProperties.h"

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
        effectEditor.setTooltip ("The effect the " + gLedColorList [curEffectIndex] + " LED selects. Set to NONE to bypass.");
        for (auto effectIndex { 0 }; effectIndex < effectNames.size (); ++effectIndex)
            effectEditor.addItem (effectNames [effectIndex], effectIndex + 1);
        // the field is almost entirely covered by its label, so the pointer enters
        // that rather than the box; without this the hover outline never appears
        HoverHighlight::attach (effectEditor);
        effectEditor.setSelectedId (1);
        effectEditor.setComponentID ("StepComboBox" + juce::String (curEffectIndex));
        effectEditor.onDragCallback = [this, &effectEditor, curEffectIndex] (double valueDelta)
        {
            const auto stepValue { effectEditor.getSelectedId () };
            effectEditor.setSelectedId (std::clamp (stepValue + juce::roundToInt (valueDelta), 1, 9), juce::NotificationType::dontSendNotification);
            onEffectUiChanged (curEffectIndex);
        };
        effectEditor.onPopupMenuCallback = [this, curEffectIndex] ()
        {
            juce::PopupMenu pm;
            pm.addSectionHeader ("Effect " + effectProperties[curEffectIndex].getId ().substring (3));
            pm.addSeparator ();
            pm.addItem ("Default", true, false, [this, curEffectIndex] ()
            {
                effectEditors [curEffectIndex].setText (effectNames[effectDefaults[curEffectIndex]], juce::NotificationType::sendNotification);
            });
            pm.addItem ("Revert", true, false, [this, curEffectIndex] ()
            {
                effectEditors [curEffectIndex].setText (uneditedEffectProperties[curEffectIndex].getEffect (), juce::NotificationType::sendNotification);
            });

            pm.showMenuAsync ({});
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
        effectLabel.setFont (ClutchType::sectionHeader ());
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

// A label keeps a per-instance colour, so it has to be refreshed by hand when the
// palette changes.
void EffectEditorComponent::applyExplicitColours ()
{
    const auto headerColour { findColour (ClutchColours::accentText) };
    for (auto& effectLabel : effectLabels)
        effectLabel.setColour (juce::Label::ColourIds::textColourId, headerColour);
}

void EffectEditorComponent::lookAndFeelChanged ()
{
    juce::Component::lookAndFeelChanged ();
    applyExplicitColours ();
}

void EffectEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (findColour (ClutchColours::windowBackground));

    // the effects are one list, so they sit on one panel lifted off the background
    ClutchPaint::card (g, *this,
                       { effectLabels [0].getX (), effectLabels [0].getY () - 5,
                         effectEditors [0].getRight () - effectLabels [0].getX () + 5,
                         effectLabels [7].getBottom () - effectLabels [0].getY () + 10 });
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

