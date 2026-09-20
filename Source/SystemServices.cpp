#include "SystemServices.h"

void SystemServices::setAudioDeviceManager (juce::AudioDeviceManager* audioDeviceManager)
{
    setValue (audioDeviceManager, AudioDeviceManagerPropertyId, false);
}

juce::AudioDeviceManager* SystemServices::getAudioDeviceManager ()
{
    return getValue<juce::AudioDeviceManager*> (AudioDeviceManagerPropertyId, data);
}
