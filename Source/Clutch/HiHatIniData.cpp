#include "HiHatIniData.h"

constexpr auto kKeyColumn { 0 };
constexpr auto kValueColumn { 34 };
constexpr auto kCommentColumn { 53 };
constexpr auto kDefaultValueColumn { 111 };

void HiHatData::readFromFile (const juce::File& file)
{
    juce::FileInputStream inputStream (file);
    if (inputStream.openedOk ())
    {
        juce::String currentSection;
        while (!inputStream.isExhausted ())
        {
            juce::String line { inputStream.readNextLine () };
            HiHatIniFileLine iniLine;
            iniLine.section = currentSection;
            iniLine.rawLine = line;
            auto trimmedLine = line.trim ();
            if (trimmedLine.isEmpty ())
            {
                iniLine.lineType = LineType::unknown;
            }
            else if (trimmedLine.startsWithChar (';'))
            {
                iniLine.lineType = LineType::comment;
                iniLine.comment = trimmedLine.substring (1);
            }
            else if (trimmedLine.startsWithChar ('['))
            {
                iniLine.lineType = LineType::section;
                currentSection = trimmedLine.fromFirstOccurrenceOf ("[", false, false).upToLastOccurrenceOf ("]", false, false).trim ();
                iniLine.section = currentSection;
            }
            else
            {
                auto key { trimmedLine.upToFirstOccurrenceOf (" ", false, false).trim () };
                if (!key.isEmpty ())
                {
                    auto afterKey = trimmedLine.fromFirstOccurrenceOf (" ", false, false).trim ();
                    if (afterKey.startsWithChar ('='))
                    {
                        auto valuePart = afterKey.fromFirstOccurrenceOf ("=", false, false).trim ();
                        if (!valuePart.isEmpty ())
                        {
                            iniLine.lineType = LineType::keyValuePair;
                            iniLine.key = key;
                            iniLine.value = valuePart.upToFirstOccurrenceOf (" ;", false, false).trim ();
                            auto comment = valuePart.fromFirstOccurrenceOf (" ;", true, false).trim ();
                            if (!comment.isEmpty ())
                            {
                                iniLine.comment = comment;
                                auto defaultValueIndex = comment.lastIndexOf ("d:");
                                if (defaultValueIndex != -1)
                                    iniLine.defaultValue = comment.substring (defaultValueIndex + 2).trim ();
                            }
                        }
                    }
                }
                else
                {
                    iniLine.lineType = LineType::unknown;
                }
            }
            iniLines.push_back (iniLine);
        }
    }
}
void HiHatData::writeToFile (juce::File outputFile)
{
    juce::FileOutputStream outputStream (outputFile);
    if (outputStream.openedOk ())
    {
        for (const auto& iniLine : iniLines)
        {
            switch (iniLine.lineType)
            {
                case LineType::section:
                    outputStream << "[" << iniLine.section << "]\n";
                break;

                case LineType::unknown:
                case LineType::comment:
                    outputStream << iniLine.rawLine << "\n";
                break;

                case LineType::keyValuePair:
                {
                    const auto valueColumn = [section = iniLine.section] ()
                    {
                        if (section == "HIHAT")
                            return kValueColumn;
                        else if (section == "PATTERNS")
                            return 12;
                        else if (section == "EFFECTS")
                            return 11;
                        else
                            return 5;
                    } ();
                    outputStream << iniLine.key.paddedRight (' ', valueColumn) << "= " << iniLine.value.paddedRight (' ', kCommentColumn - kValueColumn - 2);
                    if (!iniLine.comment.isEmpty ())
                        outputStream << iniLine.comment.paddedRight (' ', kDefaultValueColumn - kCommentColumn);
                    outputStream << "\n";
                }
                break;

                default:
                break;
            }
        }
    }
}

juce::String HiHatData::getValue (const juce::String& section, const juce::String& key) const
{
    for (const auto& iniLine : iniLines)
    {
        if (iniLine.lineType == LineType::keyValuePair)
        {
            if (iniLine.section == section && iniLine.key == key)
                return iniLine.value;
        }
    }
    return {};
}