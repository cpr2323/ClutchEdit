#pragma once
#include <JuceHeader.h>

// { FX_LED, FX_NAME, FX_DEF_NAME }

struct PatternAssignments
{
    juce::String patternLed;
    juce::String pattern;
};

const PatternAssignments patternAssignments []
{
    {"PTN_WHITE", "6, 5, 7, 5, 0"},
    {"PTN_RED", "6, 5, 5, 7, 5, 6, 5, 6, 4, 0"},
    {"PTN_ORANGE", "3, 2, 8, 5, 2, 6, 2, 2, 0"},
    {"PTN_YELLOW", "7, 3, 5, 7, 3, 5, 2, 5, 7, 3, 5, 3, 2, 8, 3, 2, 0"},
    {"PTN_GREEN", "4, 3, 6, 3, 4, 7, 1, 2, 6, 4, 3, 6, 3, 6, 4, 5, 0"},
    {"PTN_BLUE", "5, 2, 3, 5, 1, 5, 1, 0"},
    {"PTN_CYAN", "5, 5, 5, 7, 0"},
    {"PTN_VIOLET", "5, 4, 5, 5, 9, 5, 5, 4, 5, 5, 7, 4, 6, 4, 5, 3, 0"},
};

/*
[PATTERNS]
; User - customizable patterns for the FEEL option
; 8× patterns of numbers 1–9.A 0 ends the pattern.
; 1:10 %, 2 : 30 %, 3 : 60 %, 4 : 80 %, 5 : 100 %, 6 : 110 %, 7 : 125 %, 8 : 150 %, 9 : 200 %
; MAX STEPS is 32 + a trailing 0 to denote pattern end.
; Example: PTN_WHITE = 6, 5, 7, 5, 0  (four - step pattern)
; ====================================================================================================================== =
;             1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | END
PTN_WHITE = 6, 5, 7, 5, 0
PTN_RED = 6, 5, 5, 7, 5, 6, 5, 6, 4, 0
PTN_ORANGE = 3, 2, 8, 5, 2, 6, 2, 2, 0
PTN_YELLOW = 7, 3, 5, 7, 3, 5, 2, 5, 7, 3, 5, 3, 2, 8, 3, 2, 0
PTN_GREEN = 4, 3, 6, 3, 4, 7, 1, 2, 6, 4, 3, 6, 3, 6, 4, 5, 0
PTN_BLUE = 5, 2, 3, 5, 1, 5, 1, 0
PTN_CYAN = 5, 5, 5, 7, 0
PTN_VIOLET = 5, 4, 5, 5, 9, 5, 5, 4, 5, 5, 7, 4, 6, 4, 5, 3, 0
;             1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | END
; ====================================================================================================================== =
*/