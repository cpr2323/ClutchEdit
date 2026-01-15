#pragma once

#include <JuceHeader.h>
#include "../../Utility/ValueTreeWrapper.h"

class AudioPlayerProperties : public ValueTreeWrapper<AudioPlayerProperties>
{
public:
    AudioPlayerProperties () noexcept : ValueTreeWrapper<AudioPlayerProperties> (AudioConfigTypeId) {}
    AudioPlayerProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks)
        : ValueTreeWrapper<AudioPlayerProperties> (AudioConfigTypeId, vt, wrapperType, shouldEnableCallbacks) {}

    enum class PlayState { stop, play };
    enum class PlayMode { once, loop };
    enum class WhichHiHat { opened, closed };
    void setPlayState (PlayState playState, bool includeSelfCallback);
    void setPlayMode (PlayMode playMode, bool includeSelfCallback);
    void setSampleSource (int surfaceIndex, WhichHiHat whichHiHat, bool includeSelfCallback);
    void showConfigDialog (bool includeSelfCallback);

    PlayState getPlayState ();
    PlayMode getPlayMode ();
    juce::String getSampleSource ();

    std::function<void (PlayState playState)> onPlayStateChange;
    std::function<void (PlayMode playMode)> onPlayModeChange;
    std::function<void (juce::String fileName)> onSampleSourceChanged;
    std::function<void ()> onShowConfigDialog;

    static inline const juce::Identifier AudioConfigTypeId { "AudioPlayer" };
    static inline const juce::Identifier PlayStatePropertyId        { "playState" };
    static inline const juce::Identifier PlayModePropertyId         { "playMode" };
    static inline const juce::Identifier SampleSourcePropertyId     { "sampleSource" };
    static inline const juce::Identifier ShowConfigDialogPropertyId { "showConfigDialog" };

    void initValueTree ();
    void processValueTree () {}

private:
    void valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
};
