#include "ClutchFonts.h"
#include <BinaryData.h>

namespace
{
    juce::Typeface::Ptr loadTypeface (const char* data, int size)
    {
        return juce::Typeface::createSystemTypefaceFor (data, static_cast<size_t> (size));
    }
}

ClutchFonts::ClutchFonts ()
    : sansRegular (loadTypeface (BinaryData::IBMPlexSansRegular_ttf, BinaryData::IBMPlexSansRegular_ttfSize)),
      condensedRegular (loadTypeface (BinaryData::IBMPlexSansCondensedRegular_ttf, BinaryData::IBMPlexSansCondensedRegular_ttfSize)),
      condensedSemiBold (loadTypeface (BinaryData::IBMPlexSansCondensedSemiBold_ttf, BinaryData::IBMPlexSansCondensedSemiBold_ttfSize)),
      monoRegular (loadTypeface (BinaryData::IBMPlexMonoRegular_ttf, BinaryData::IBMPlexMonoRegular_ttfSize))
{
}

ClutchFonts::~ClutchFonts ()
{
    clearSingletonInstance ();
}

juce::Typeface::Ptr ClutchFonts::getTypeface (Face face) const
{
    switch (face)
    {
        // A few roles want the 500 weight of Sans and Mono. Those cuts are not
        // embedded, so they fall back to the regular weight; the colour those
        // values are drawn in already sets them apart.
        case Face::sans:
        case Face::sansMedium:        return sansRegular;
        case Face::condensed:         return condensedRegular;
        case Face::condensedSemiBold: return condensedSemiBold;
        case Face::mono:
        case Face::monoMedium:        return monoRegular;
    }
    jassertfalse;
    return sansRegular;
}

juce::Typeface::Ptr ClutchFonts::getDefaultTypeface ()
{
    return getInstance ()->sansRegular;
}

juce::Font ClutchFonts::make (Face face, float emSize, float letterSpacingEm)
{
    juce::Font font { juce::FontOptions (getInstance ()->getTypeface (face)).withPointHeight (emSize) };
    if (juce::approximatelyEqual (letterSpacingEm, 0.0f))
        return font;

    // tracking is applied as a fraction of the JUCE height, so scale the em
    // spacing by how tall this face is per em
    const auto heightPerEm { font.getHeight () / emSize };
    font.setExtraKerningFactor (letterSpacingEm / heightPerEm);
    return font;
}

namespace ClutchType
{
    using Face = ClutchFonts::Face;

    juce::Font sectionHeader ()     { return ClutchFonts::make (Face::condensedSemiBold, 9.5f, 0.14f); }
    juce::Font parameterLabel ()    { return ClutchFonts::make (Face::condensedSemiBold, 10.0f, 0.10f); }
    juce::Font button ()            { return ClutchFonts::make (Face::condensedSemiBold, 10.5f, 0.10f); }
    juce::Font buttonSmall ()       { return ClutchFonts::make (Face::condensedSemiBold, 10.0f, 0.10f); }
    juce::Font editorTab ()         { return ClutchFonts::make (Face::condensedSemiBold, 11.5f, 0.09f); }
    juce::Font stepNumber ()        { return ClutchFonts::make (Face::condensedSemiBold, 9.5f, 0.10f); }

    juce::Font chip ()              { return ClutchFonts::make (Face::condensed, 10.5f, 0.08f); }
    juce::Font mini ()              { return ClutchFonts::make (Face::condensed, 10.0f, 0.07f); }
    juce::Font menuSectionHeader () { return ClutchFonts::make (Face::condensed, 9.5f, 0.13f); }

    juce::Font value ()             { return ClutchFonts::make (Face::mono, 12.0f); }
    juce::Font chipValue ()         { return ClutchFonts::make (Face::monoMedium, 10.5f); }

    juce::Font body ()              { return ClutchFonts::make (Face::sans, 12.0f); }
    juce::Font bodyStrong ()        { return ClutchFonts::make (Face::sansMedium, 12.0f); }
}
