#include "PatternListProperties.h"

void PatternProperties::setId (juce::String id, bool includeSelfCallback)
{
    setValue (id, IdPropertyId, includeSelfCallback);
}

void PatternProperties::setPattern (juce::String pattern, bool includeSelfCallback)
{
    setValue (pattern, PatternPropertyId, includeSelfCallback);
}

juce::String PatternProperties::getId ()
{
    return getValue<juce::String> (IdPropertyId);
}

juce::String PatternProperties::getPattern ()
{
    return getValue<juce::String> (PatternPropertyId);
}

void PatternProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (vt != data)
        return;

    if (property == IdPropertyId)
    {
        if (onIdChange)
            onIdChange (getId ());
    }
    else if (property == PatternPropertyId)
    {
        if (onPatternChange)
            onPatternChange (getPattern ());
    }
}

void PatternListProperties::initValueTree ()
{
    std::pair<juce::String, juce::String> defaultPatterns []
    {
        {"PTN_WHITE", "6, 5, 7, 5, 0" },
        {"PTN_RED", "6, 5, 5, 7, 5, 6, 5, 6, 4, 0" },
        {"PTN_ORANGE", "3, 2, 8, 5, 2, 6, 2, 2, 0" },
        {"PTN_YELLOW", "7, 3, 5, 7, 3, 5, 2, 5, 7, 3, 5, 3, 2, 8, 3, 2, 0" },
        {"PTN_GREEN", "4, 3, 6, 3, 4, 7, 1, 2, 6, 4, 3, 6, 3, 6, 4, 5, 0" },
        {"PTN_BLUE", "5, 2, 3, 5, 1, 5, 1, 0" },
        {"PTN_CYAN", "5, 5, 5, 7, 0" },
        {"PTN_VIOLET", "5, 4, 5, 5, 9, 5, 5, 4, 5, 5, 7, 4, 6, 4, 5, 3, 0" }
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

void PatternListProperties::valueTreePropertyChanged (juce::ValueTree & vt, const juce::Identifier & property)
{
}