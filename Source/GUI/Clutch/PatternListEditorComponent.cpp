#include "PatternListEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

PatternListEditorComponent::PatternListEditorComponent ()
{
    std::array<juce::String, 8> patternNames
    {
        "WHITE",
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "BLUE",
        "CYAN",
        "VIOLET"
    };

    // create the step numbers at the top of the columns
    for (auto columnIndex { 0 }; columnIndex < stepNumbers.size (); ++columnIndex)
    {
        auto& stepNumber { stepNumbers [columnIndex] };
        stepNumber.setJustificationType (juce::Justification::centred);
        stepNumber.setText (juce::String (columnIndex + 1), juce::NotificationType::dontSendNotification);
        addAndMakeVisible (stepNumber);
    }
    // create the pattern label and pattern editor rows
    for (auto patternIndex { 0 }; patternIndex < patternLabels.size (); ++patternIndex)
    {
        addAndMakeVisible (patternEditors [patternIndex]);

        auto& patternLabel { patternLabels [patternIndex] };
        patternLabel.setColour (juce::Label::textColourId, juce::Colours::white);
        patternLabel.setText (patternNames [patternIndex], juce::NotificationType::dontSendNotification);
        patternLabel.setJustificationType (juce::Justification::topLeft);
        addAndMakeVisible (patternLabel);
    }
}

PatternListEditorComponent::~PatternListEditorComponent ()
{

}

void PatternListEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    patternListProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("PatternList"), ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::yes);

    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternEditors[patternIndex].init (patternListProperties.getPatternVT (patternIndex));
    }
}

void PatternListEditorComponent::paint (juce::Graphics& g)
{
//     g.setColour (juce::Colours::red);
//     for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
//     {
//         g.drawRect (patternLabels [patternIndex].getBounds ());
//     }
}

void PatternListEditorComponent::resized ()
{
    constexpr auto kInitialYOffset { 25 };
    constexpr auto kInitialXOffset { 55 };
    constexpr auto kPatternEditorHeight { 60 };
    auto bounds { getLocalBounds ().reduced (5, 5) };
    
    // position the step numbers in the middle/top of each column
    auto columnCenters { patternEditors [0].getColumnCenters () };
    for (auto columnIndex { 0 }; columnIndex < stepNumbers.size (); ++columnIndex)
    {
        auto& stepNumber { stepNumbers [columnIndex] };
        auto numberWidth { stepNumber.getFont ().getStringWidth (stepNumber.getText ()) };
        auto halfNumberWidth { numberWidth / 2 };
        stepNumber.setBounds (kInitialXOffset + (columnCenters [columnIndex] - halfNumberWidth) - 5, 0, numberWidth + 10, 20);
    }
    // position the pattern name and pattern editor rows
    for (auto patternIndex { 0 }; patternIndex < patternEditors.size (); ++patternIndex)
    {
        patternLabels [patternIndex].setBounds (0, kInitialYOffset + (patternIndex * kPatternEditorHeight), kInitialXOffset, kPatternEditorHeight);
        patternEditors [patternIndex].setBounds (kInitialXOffset, kInitialYOffset + (patternIndex * kPatternEditorHeight), bounds.getWidth (), kPatternEditorHeight);
    }
}
