#pragma once

#include <JuceHeader.h>

/*
    The app's type: IBM Plex, in the three families the theme uses. Plex was drawn
    for technical interfaces, and its condensed cut sets the small caps labels at
    a width the parameter grid can afford.

    Every size here is a CSS font-size, which is the em size, so it goes through
    withPointHeight. withHeight would read it as ascent + descent, which for Plex
    is 1.3 em, and draw everything about a quarter too small.

    Letter spacing is also given in em, as CSS gives it. JUCE's tracking is a
    fraction of the JUCE height rather than of the em, so it is converted using
    the typeface's own metrics rather than passed straight through.
*/
class ClutchFonts : private juce::DeletedAtShutdown
{
public:
    enum class Face
    {
        sans,
        sansMedium,
        condensed,
        condensedSemiBold,
        mono,
        monoMedium
    };

    static juce::Font make (Face face, float emSize, float letterSpacingEm = 0.0f);

    // the regular sans face, which the LookAndFeel installs as the default for
    // anything that does not ask for a font of its own
    static juce::Typeface::Ptr getDefaultTypeface ();

    ~ClutchFonts () override;

    JUCE_DECLARE_SINGLETON_SINGLETHREADED_MINIMAL_INLINE (ClutchFonts)

private:
    ClutchFonts ();
    juce::Typeface::Ptr getTypeface (Face face) const;

    // Held here rather than in function statics, so they are released with the
    // rest of JUCE at shutdown instead of after it.
    juce::Typeface::Ptr sansRegular;
    juce::Typeface::Ptr condensedRegular;
    juce::Typeface::Ptr condensedSemiBold;
    juce::Typeface::Ptr monoRegular;
};

/*
    One function per role, so a size or spacing is decided in one place. The
    names say where a style is used, not what it looks like.
*/
namespace ClutchType
{
    // condensed semi bold, upper case
    juce::Font sectionHeader ();    // the name of a section, and of the group within one
    juce::Font parameterLabel ();   // the name beside a value field
    juce::Font button ();           // SAVE, OPEN, TOOLS
    juce::Font buttonSmall ();
    juce::Font editorTab ();        // SAMPLES, SETTINGS, PATTERNS, EFFECTS
    juce::Font stepNumber ();       // the step numbers over a pattern

    // condensed regular
    juce::Font chip ();             // OUT, SETTINGS
    juce::Font mini ();
    juce::Font menuSectionHeader ();

    // mono
    juce::Font value ();            // parameter fields and combo boxes
    juce::Font chipValue ();        // the device name in the OUT chip

    // sans
    juce::Font body ();             // breadcrumbs, popup menus
    juce::Font bodyStrong ();       // the open file in the breadcrumbs
}
