#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

class EffectListProperties : public ValueTreeWrapper<EffectListProperties>
{
public:
    EffectListProperties () noexcept : ValueTreeWrapper<EffectListProperties> (BankListTypeId)
    {
    }
    EffectListProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<EffectListProperties> (BankListTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    // void setPitchLow (float value, bool includeSelfCallback);
    // juce::String getPitchLowKey ();
    // std::function<void (float value)> onPitchLowChange;

    void forEachEffect (std::function<bool (juce::ValueTree patternVT, int patternIndex)> patternVTCallback);
    juce::ValueTree getEffectVT (int patternIndex);

    static inline const juce::Identifier BankListTypeId { "EffectList" };

    void initValueTree ();
    void processValueTree () {}

private:
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