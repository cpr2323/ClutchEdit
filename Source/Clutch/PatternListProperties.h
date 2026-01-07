#pragma once

#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

// { FX_LED, FX_NAME }

struct PatternAssignments
{
    juce::String patternLed;
    juce::String pattern;
};

// <Patterns>
//     <Pattern patternId="PTN_WHITE" pattern="6, 5, 7, 5, 0"/>
// </Patterns>
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

class PatternProperties : public ValueTreeWrapper<PatternProperties>
{
public:
    PatternProperties () noexcept : ValueTreeWrapper<PatternProperties> (PatternTypeId)
    {
    }
    PatternProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<PatternProperties> (PatternTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setId (juce::String , bool includeSelfCallback);
    void setPattern (juce::String, bool includeSelfCallback);
    juce::String getId ();
    juce::String getPattern ();
    std::function<void (juce::String id)> onIdChange;
    std::function<void (juce::String pattern)> onPatternChange;

    static inline const juce::Identifier PatternTypeId { "Pattern" };
    static inline const juce::Identifier IdPropertyId      { "id" };
    static inline const juce::Identifier PatternPropertyId { "pattern" };

    void initValueTree () {}
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};

class PatternListProperties : public ValueTreeWrapper<PatternListProperties>
{
public:
    PatternListProperties () noexcept : ValueTreeWrapper<PatternListProperties> (PatternListTypeId)
    {
    }
    PatternListProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<PatternListProperties> (PatternListTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    // void setPitchLow (float value, bool includeSelfCallback);
    // juce::String getPitchLowKey ();
    // std::function<void (float value)> onPitchLowChange;

    void forEachPattern (std::function<bool (juce::ValueTree patternVT, int patternIndex)> patternVTCallback);
    juce::ValueTree getPatternVT (int patternIndex);

    static inline const juce::Identifier PatternListTypeId { "PatternList" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
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