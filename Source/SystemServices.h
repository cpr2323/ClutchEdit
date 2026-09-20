#pragma once

#include <JuceHeader.h>
#include "oolib/ValueTree/ValueTreeWrapper.h"

/*
    Where a layer publishes an object other layers need, without those layers
    having to know which layer owns it, or reach through it to get at it.

    Everything here is a borrowed pointer: the owner outlives the tree, and
    nothing read out of here is deleted by whoever reads it.
*/
class SystemServices : public ValueTreeWrapper<SystemServices>
{
public:
    SystemServices () noexcept : ValueTreeWrapper (SystemServicesTypeId)
    {
    }

    SystemServices (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper (SystemServicesTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    static inline const juce::Identifier SystemServicesTypeId { "SystemServices" };
    static inline const juce::Identifier AudioDeviceManagerPropertyId { "audioDeviceManager" };

    // published by the audio layer so the GUI can build a device selector, and
    // offer the output device menu, without owning one of its own
    void setAudioDeviceManager (juce::AudioDeviceManager* audioDeviceManager);
    juce::AudioDeviceManager* getAudioDeviceManager ();

    void initValueTree () {}
    void processValueTree () {}

private:
};
