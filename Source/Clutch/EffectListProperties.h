#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

// { FX_LED, FX_NAME, FX_DEF_NAME }

struct FxAssignments
{
    juce::String fxLed;
    juce::String fxName;
    juce::String fxDefName;
};

const FxAssignments fxAssignments []
{
    {"FX_WHITE", "SPUTTER", "SPUTTER"},
    {"FX_RED", "BITCRUSH", "BITCRUSH"},
    {"FX_GREEN", "COMBFILTER", "COMBFILTER"},
    {"FX_BLUE", "DJFILTER", "DJFILTER"},
    {"FX_ORANGE", "DUBECHO", "DUBECHO"},
    {"FX_CYAN", "CHORUS", "CHORUS"},
    {"FX_VIOLET", "REVERB", "REVERB"},
    {"FX_YELLOW", "GLITCH", "GLITCH"},
};

class EffectProperties : public ValueTreeWrapper<EffectProperties>
{
public:
    EffectProperties () noexcept : ValueTreeWrapper<EffectProperties> (EffectTypeId)
    {
    }
    EffectProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<EffectProperties> (EffectTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setId (juce::String, bool includeSelfCallback);
    void setEffect (juce::String, bool includeSelfCallback);
    juce::String getId ();
    juce::String getEffect ();
    std::function<void (juce::String id)> onIdChange;
    std::function<void (juce::String pattern)> onEffectChange;

    static inline const juce::Identifier EffectTypeId { "Effect" };
    static inline const juce::Identifier IdPropertyId { "id" };
    static inline const juce::Identifier EffectPropertyId { "effect" };

    void initValueTree () {}
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};

class EffectListProperties : public ValueTreeWrapper<EffectListProperties>
{
public:
    EffectListProperties () noexcept : ValueTreeWrapper<EffectListProperties> (EffectListTypeId)
    {
    }
    EffectListProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<EffectListProperties> (EffectListTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    // void setPitchLow (float value, bool includeSelfCallback);
    // juce::String getPitchLowKey ();
    // std::function<void (float value)> onPitchLowChange;

    void forEachEffect (std::function<bool (juce::ValueTree patternVT, int patternIndex)> patternVTCallback);
    juce::ValueTree getEffectVT (int patternIndex);

    static inline const juce::Identifier EffectListTypeId { "EffectList" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};

/*
; ====================================================================================================================== =
[EFFECTS]
; Color - to - Effect Mapping
; Maps each LED color to an effect.Set to "NONE" to bypass.
; Available effects : SPUTTER, BITCRUSH, COMBFILTER, WAVEFOLD, DUBECHO, CHORUS, REVERB, GLITCH, DJFILTER, NONE
; ====================================================================================================================== =
FX_WHITE = SPUTTER; d: SPUTTER
FX_RED = BITCRUSH; d: BITCRUSH
FX_GREEN = COMBFILTER; d: COMBFILTER
FX_BLUE = DJFILTER; d: DJFILTER
FX_ORANGE = DUBECHO; d: DUBECHO
FX_CYAN = CHORUS; d: CHORUS
FX_VIOLET = REVERB; d: REVERB
FX_YELLOW = GLITCH; d: GLITCH
*/