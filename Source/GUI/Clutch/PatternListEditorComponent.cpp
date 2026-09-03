#include "PatternListEditorComponent.h"
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
        patternLabel.setColour (juce::Label::textColourId, juce::Colours::white);
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

void PatternListEditorComponent::paintOverChildren (juce::Graphics& g)
{
    const auto kSectionOutlineColour { juce::Colour (0xff6a6a6a) };
    g.setColour (kSectionOutlineColour.brighter (0.4f));
    constexpr auto kSectionCornerSize { 4.0f };
    constexpr auto kSectionOutlineThickness { 1.0f };
    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        auto& patternLabel { patternLabels [patternIndex] };
        auto& patternEditor { patternEditors [patternIndex] };
        const auto x { patternLabel.getX () };
        const auto y { patternEditor.getY () };
        const auto width { patternLabel.getWidth () + patternEditor.getWidth () - 65 };
        const auto height { patternEditor.getHeight () - 5 };
        g.drawRoundedRectangle (juce::Rectangle<int> (x, y, width, height).toFloat(), kSectionCornerSize, kSectionOutlineThickness);
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
