#include "HiHatEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

HiHatEditorComponent::HiHatEditorComponent ()
{
}

HiHatEditorComponent::~HiHatEditorComponent ()
{
}

void HiHatEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    hiHatProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("HiHat"), ValueTreeWrapper<HiHatProperties>::WrapperType::client, ValueTreeWrapper<HiHatProperties>::EnableCallbacks::yes);
}

void HiHatEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void HiHatEditorComponent::resized ()
{
}
