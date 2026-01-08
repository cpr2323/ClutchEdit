#include "PatternListEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

PatternListEditorComponent::PatternListEditorComponent ()
{
    for (auto curStepIndex { 0 }; curStepIndex < 32; ++curStepIndex)
    {
        auto& stepComboBox { stepEditor [curStepIndex] };
        stepComboBox.addItem ("10%", 1);
        stepComboBox.addItem ("30%", 2);
        stepComboBox.addItem ("60%", 3);
        stepComboBox.addItem ("80%", 4);
        stepComboBox.addItem ("100%", 5);
        stepComboBox.addItem ("110%", 6);
        stepComboBox.addItem ("125%", 7);
        stepComboBox.addItem ("150%", 8);
        stepComboBox.addItem ("200%", 9);
        stepComboBox.setLookAndFeel (&noArrowComboBoxLnF);
        stepComboBox.setSelectedId (1);
        addAndMakeVisible (stepComboBox);
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
}

void PatternListEditorComponent::paint (juce::Graphics& g)
{

}

void PatternListEditorComponent::resized ()
{
    constexpr auto stepComboBoxHeight { 20 };
    constexpr auto stepComboBoxWidth { 60 };
    constexpr auto twoPiRadians { 2.0f * 3.14159f };
    constexpr auto sizeOfStepInRadians { twoPiRadians / 32.0f };
    constexpr auto radiusOfCircle { 360.0f };
    for (auto step { 0 }; step < 32; ++step)
    {
        const auto comboBoxCenter { step * sizeOfStepInRadians };
        const auto x { std::cos (comboBoxCenter) * (radiusOfCircle) + radiusOfCircle + stepComboBoxWidth };
        const auto y { std::sin (comboBoxCenter) * (radiusOfCircle) + radiusOfCircle + stepComboBoxHeight };
        auto comboBox { getChildComponent (step) };
        comboBox->setBounds (x - (stepComboBoxWidth / 2), y - (stepComboBoxHeight / 2), stepComboBoxWidth, stepComboBoxHeight);
    }
}
