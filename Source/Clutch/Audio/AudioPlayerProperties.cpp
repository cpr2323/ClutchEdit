#include "AudioPlayerProperties.h"

void AudioPlayerProperties::initValueTree ()
{
    setPlayState (PlayState::stop, false);
    setSampleSource ("", false);
}

void AudioPlayerProperties::setPlayState (PlayState playState, bool includeSelfCallback)
{
    setValue (static_cast<int> (playState), PlayStatePropertyId, includeSelfCallback);
}

void AudioPlayerProperties::setPlayMode (PlayMode playMode, bool includeSelfCallback)
{
    setValue (static_cast<int> (playMode), PlayModePropertyId, includeSelfCallback);
}

void AudioPlayerProperties::setSampleSource (juce::String sampleSource, bool includeSelfCallback)
{
    setValue (sampleSource, SampleSourcePropertyId, includeSelfCallback);
}

void AudioPlayerProperties::showConfigDialog (bool includeSelfCallback)
{
    toggleValue (ShowConfigDialogPropertyId, includeSelfCallback);
}

AudioPlayerProperties::PlayState AudioPlayerProperties::getPlayState ()
{
    return static_cast<PlayState> (getValue<int> (PlayStatePropertyId));
}

AudioPlayerProperties::PlayMode AudioPlayerProperties::getPlayMode ()
{
    return static_cast<PlayMode> (getValue<int> (PlayModePropertyId));
}

juce::String AudioPlayerProperties::getSampleSource ()
{
    return getValue<juce::String> (SampleSourcePropertyId);
}

void AudioPlayerProperties::valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property)
{
    if (treeWhosePropertyHasChanged == data)
    {
        if (property == PlayStatePropertyId)
        {
            if (onPlayStateChange != nullptr)
                onPlayStateChange (getPlayState ());
        }
        else if (property == PlayModePropertyId)
        {
            if (onPlayModeChange != nullptr)
                onPlayModeChange (getPlayMode ());
        }
        else if (property == SampleSourcePropertyId)
        {
            if (onSampleSourceChanged != nullptr)
                onSampleSourceChanged (getSampleSource ());
        }
        else if (property == ShowConfigDialogPropertyId)
        {
            if (onShowConfigDialog != nullptr)
                onShowConfigDialog ();
        }
    }
}

