#include "ClutchEditorComponent.h"


ClutchEditorComponent::ClutchEditorComponent ()
{
    addAndMakeVisible (hiHatEditorComponent);
}

ClutchEditorComponent::~ClutchEditorComponent ()
{
}

void ClutchEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    hiHatEditorComponent.init (rootPropertiesVT);
}

void ClutchEditorComponent::resized()
{
    hiHatEditorComponent.setBounds (getLocalBounds ());
}

// void ClutchEditorComponent::paint (juce::Graphics& g)
// {
//     g.fillAll (juce::Colours::darkgrey);
//     //hiHatEditorComponent.paint (g);
// }