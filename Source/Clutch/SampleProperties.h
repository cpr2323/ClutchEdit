#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

// TODO move these notes elsewhere
// There are eight folders (banks) at the root level
//      "WHITE", "RED", "GREEN", "BLUE", "ORANGE", "CYAN", "VIOLET", "YELLOW"
// Each folder contains 32 samples, or 16 pairs of open/closed samples
//      01CH.wav, 01OH.wav, 02CH.wav, 02OH.wav, ..., 16CH.wav, 16OH.wav
// There is also a "Sample bank document - COLOR.rtf" file in each folder
// Since reading/writing RTF is not trivial, we will ignore it for now

// Each audio sample on the memory card must follow this naming format :
// 
// NNXX.WAV
// 
// NN = Two - digit surface number (01–16)
// XX = Sample type code (CH or OH)
// 
// Example :
//     01CH.WAV   →  Surface 01  (Closed Hat)
//     01OH.WAV   →  Surface 01  (Open Hat)
//     …
//     16CH.WAV   →  Surface 16  (Closed Hat)
//     16OH.WAV   →  Surface 16  (Open Hat)

// Filenames must be UPPERCASE and use 8.3 format.
// * Required format : MONO, 16 - bit
// * Sample rate recommended : 48kHz or 44.1kHz -
// — this is ignored internally, sample rate is determined by pitch control
// - 48kHz will yield best results

// Max sample length is limited by the length of the release envelope set in the HIHAT.INI file. 4 seconds default.

// <SAMPLES>
//     <BANK id=0>
//         <SAMPLE surface=0 state="open"
//     </BANK>
// </SAMPLES>

class SampleProperties : public ValueTreeWrapper<SampleProperties>
{
public:
    enum class SampleType { open, closed };
    SampleProperties () noexcept : ValueTreeWrapper<SampleProperties> (SampleTypeId)
    {
    }
    SampleProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<SampleProperties> (SampleTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setDeleted (bool deleted, bool includeSelfCallback);
    void setExists (bool exists, bool includeSelfCallback);
    void setFilename (const juce::String& filename, bool includeSelfCallback);
    void setType (SampleType sampleType, bool includeSelfCallback);

    bool getDeleted ();
    bool getExists ();
    juce::String getFilename ();
    SampleType getType ();

    std::function<void (bool deleted)> onDeletedChange;
    std::function<void (bool exists)> onExistsChange;
    std::function<void (const juce::String& filename)> onFilenameChange;
    std::function<void (SampleType sampleType)> onTypeChange;

    static inline const juce::Identifier SampleTypeId { "Sample" };
    static inline const juce::Identifier FilenamePropertyId { "filename" };
    static inline const juce::Identifier ExistsPropertyId   { "exists" };
    static inline const juce::Identifier DeletedPropertyId  { "deleted" };
    static inline const juce::Identifier TypePropertyId     { "type" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};
