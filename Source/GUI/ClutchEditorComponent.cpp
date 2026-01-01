#include "ClutchEditorComponent.h"
#include "../Clutch/ClutchProperties.h"
#include "../Utility/RuntimeRootProperties.h"

ClutchEditorComponent::ClutchEditorComponent ()
{

}

ClutchEditorComponent::~ClutchEditorComponent ()
{

}

void ClutchEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    hiHatProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("HiHat"), ValueTreeWrapper<HiHatProperties>::WrapperType::client, ValueTreeWrapper<HiHatProperties>::EnableCallbacks::yes);
}
