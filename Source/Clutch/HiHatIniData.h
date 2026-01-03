#pragma once
#include <JuceHeader.h>

// layout of HIHAT.INI file
// 
//     |-section-
//     |[HIHAT]
//     |-comment-
//     |; Pitch control multiplier (both Surface A and Surface B)
//     |-key-                               -value-          -comment-                                                 -default-
//     |0         0         0         0         0         0         0         0         0         0         1         1         1
//     |0         1         2         3         4         5         6         7         8         9         0         1         2
//     |0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
//     |PITCH_LOW                         = 0.125            ; Min pitch 0.001 to 0.5                                  d: 0.125

class HiHatData
{
public:
    HiHatData () = default;
    ~HiHatData () = default;

    void readFromFile (const juce::File& file);
    void writeToFile (juce::File outputFile);

    juce::String getValue (const juce::String& section, const juce::String& key) const;
    void setValue (const juce::String& section, const juce::String& key, const juce::String& value);

private:
    enum class LineType
    {
        unknown,
        comment,
        section,
        keyValuePair
    };
    struct HiHatIniFileLine
    {
        LineType lineType { LineType::unknown };
        juce::String section;
        juce::String key;
        juce::String value;
        juce::String comment;
        juce::String defaultValue;
        juce::String rawLine;
    };
    std::vector<HiHatIniFileLine> iniLines;
};