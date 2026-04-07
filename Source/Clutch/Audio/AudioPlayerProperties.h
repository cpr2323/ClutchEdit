#pragma once

#include <JuceHeader.h>
#include "../../Utility/ValueTreeWrapper.h"

class AudioPlayerProperties : public ValueTreeWrapper<AudioPlayerProperties>
{
public:
    AudioPlayerProperties () noexcept : ValueTreeWrapper<AudioPlayerProperties> (AudioPlayerTypeId) {}
    AudioPlayerProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks)
        : ValueTreeWrapper<AudioPlayerProperties> (AudioPlayerTypeId, vt, wrapperType, shouldEnableCallbacks) {}

    enum class PlayState { stop, play };
    enum class PlayMode { once, loop };
    enum class HiHatState { opened, closed };
    void setPlayState (PlayState playState, bool includeSelfCallback);
    void setPlayMode (PlayMode playMode, bool includeSelfCallback);
    void setSampleSource (juce::String sampleSource, bool includeSelfCallback);
    void setSampleId (int id, bool includeSelfCallback);
    void showConfigDialog (bool includeSelfCallback);

    PlayState getPlayState ();
    PlayMode getPlayMode ();
    juce::String getSampleSource ();
    int getSampleId ();

    std::function<void (PlayState playState)> onPlayStateChange;
    std::function<void (PlayMode playMode)> onPlayModeChange;
    std::function<void (juce::String fileName)> onSampleSourceChanged;
    std::function<void (int id)> onSampleIdChanged;
    std::function<void ()> onShowConfigDialog;

    static inline const juce::Identifier AudioPlayerTypeId { "AudioPlayer" };
    static inline const juce::Identifier PlayStatePropertyId        { "playState" };
    static inline const juce::Identifier PlayModePropertyId         { "playMode" };
    static inline const juce::Identifier SampleSourcePropertyId     { "sampleSource" };
    static inline const juce::Identifier SampleIdPropertyId         { "sampleId" };
    static inline const juce::Identifier ShowConfigDialogPropertyId { "showConfigDialog" };

    void initValueTree ();
    void processValueTree () {}

private:
    void valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
};
