#pragma once
#include <JuceHeader.h>

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