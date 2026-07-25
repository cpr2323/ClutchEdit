#include "PatternListProperties.h"
#include "HiHatIniKeys.h"
#include "PatternProperties.h"

void PatternListProperties::initValueTree ()
{
    std::pair<juce::String, juce::String> defaultPatterns []
    {
        { kPtnWhiteKey, "6,5,7,5,0" },
        { kPtnRedKey, "6,5,5,7,5,6,5,6,4,0" },
        { kPtnGreenKey, "4,3,6,3,4,7,1,2,6,4,3,6,3,6,4,5,0" },
        { kPtnBlueKey, "5,2,3,5,1,5,1,0" },
        { kPtnOrangeKey, "3,2,8,5,2,6,2,2,0" },
        { kPtnCyanKey, "5,5,5,7,0" },
        { kPtnVioletKey, "5,4,5,5,9,5,5,4,5,5,7,4,6,4,5,3,0" },
        { kPtnYellowKey, "7,3,5,7,3,5,2,5,7,3,5,3,2,8,3,2,0" }
    };
    for (auto& pattern : defaultPatterns)
    {
        PatternProperties patternProp ({}, ValueTreeWrapper<PatternProperties>::WrapperType::owner, ValueTreeWrapper<PatternProperties>::EnableCallbacks::no);
        patternProp.setId (pattern.first, false);
        patternProp.setPattern (pattern.second, false);
        getValueTree ().addChild (patternProp.getValueTree (), -1, nullptr);
    }
}

void PatternListProperties::forEachPattern (std::function<bool (juce::ValueTree patternVT, int patternIndex)> patternVTCallback)
{
    jassert (patternVTCallback != nullptr);
    auto curPatternIndex { 0 };
    ValueTreeHelpers::forEachChildOfType (data, PatternProperties::PatternTypeId, [this, &curPatternIndex, patternVTCallback] (juce::ValueTree patternVT)
    {
        auto keepIterating { patternVTCallback (patternVT, curPatternIndex) };
        ++curPatternIndex;
        return keepIterating;
    });
}

juce::ValueTree PatternListProperties::getPatternVT (int patternIndex)
{
    jassert (patternIndex < 8);
    juce::ValueTree requestedPatternPropertiesVT;
    forEachPattern ([this, &requestedPatternPropertiesVT, patternIndex] (juce::ValueTree patternVT, int curPatternIndex)
    {
        if (curPatternIndex == patternIndex)
        {
            requestedPatternPropertiesVT = patternVT;
            return false;
        }
        return true;
    });
    jassert (requestedPatternPropertiesVT.isValid ());
    return requestedPatternPropertiesVT;
}
