#include "PatternListEditorComponent.h"
#include "../Theme/UiComponents.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Clutch/LedColorList.h"
#include "oolib/Properties/RuntimeRootProperties.h"

PatternListEditorComponent::PatternListEditorComponent ()
{
    // create the pattern label and pattern editor rows
    for (auto patternIndex { 0 }; patternIndex < patternLabels.size (); ++patternIndex)
    {
        addAndMakeVisible (patternEditors [patternIndex]);

        auto& patternLabel { patternLabels [patternIndex] };
        patternLabel.setFont (ClutchType::sectionHeader ());
        patternLabel.setText (gLedColorList [patternIndex], juce::NotificationType::dontSendNotification);
        patternLabel.setJustificationType (juce::Justification::topRight);
        addAndMakeVisible (patternLabel);
    }
}

PatternListEditorComponent::~PatternListEditorComponent ()
{

}

void PatternListEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "edited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    patternListProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("PatternList"), ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::yes);
    ClutchProperties uneditedClutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    PatternListProperties uneditedPatternListProperties (uneditedClutchProperties.getValueTree ().getChildWithName ("PatternList"), ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::yes);

    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternEditors[patternIndex].init (patternListProperties.getPatternVT (patternIndex), uneditedPatternListProperties.getPatternVT (patternIndex));
    }
}

// A label keeps a per-instance colour, so it has to be refreshed by hand when the
// palette changes.
void PatternListEditorComponent::applyExplicitColours ()
{
    const auto headerColour { findColour (ClutchColours::accentText) };
    for (auto& patternLabel : patternLabels)
        patternLabel.setColour (juce::Label::ColourIds::textColourId, headerColour);
}

void PatternListEditorComponent::lookAndFeelChanged ()
{
    juce::Component::lookAndFeelChanged ();
    applyExplicitColours ();
}

void PatternListEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (findColour (ClutchColours::windowBackground));

    // one panel per pattern, so the eight of them read as eight blocks rather than
    // one field of steps. Painted here rather than over the children, so the steps
    // sit on the panel instead of the panel's outline crossing them.
    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        auto& patternLabel { patternLabels [patternIndex] };
        auto& patternEditor { patternEditors [patternIndex] };
        const auto x { patternLabel.getX () };
        const auto y { patternEditor.getY () };
        const auto width { patternLabel.getWidth () + patternEditor.getWidth () - 65 };
        const auto height { patternEditor.getHeight () - 5 };
        ClutchPaint::card (g, *this, { x, y, width, height });
    }
}

void PatternListEditorComponent::resized ()
{
    constexpr auto kLabelXOffset { 5 };
    constexpr auto kInitialYOffset { 8 };
    constexpr auto kInitialXOffset { 60 };
    constexpr auto kPatternEditorHeight { 85 };
    auto bounds { getLocalBounds ().reduced (5, 5) };
    
    // position the pattern name and pattern editor rows
    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternLabels [patternIndex].setBounds (kLabelXOffset, kInitialYOffset + (patternIndex * kPatternEditorHeight) + 33, kInitialXOffset, kPatternEditorHeight);
        patternEditors [patternIndex].setBounds (kInitialXOffset + kLabelXOffset, kInitialYOffset + (patternIndex * kPatternEditorHeight), bounds.getWidth (), kPatternEditorHeight);
    }
}
