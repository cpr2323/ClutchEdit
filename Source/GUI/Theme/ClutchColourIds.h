#pragma once

/*
    Colour IDs for the roles this app paints itself, as opposed to the ones JUCE
    already defines for its own widgets (juce::Label::textColourId and friends).

    These are looked up the normal JUCE way, with Component::findColour, which
    falls through to whichever LookAndFeel is in scope. ClutchLookAndFeel registers
    every one of them from a Palette, so changing the Palette and repainting the
    top level windows re-colours the whole app.

    The base value is arbitrary but has to be unlikely to collide with JUCE's own
    IDs (which sit around 0x1000000-0x1010000) or oolib's (0x6f6f0000).
*/
namespace ClutchColours
{
    enum ColourIds
    {
        // surfaces
        windowBackground = 0x43750001,  // the background every editor pane fills with
        fieldBackground,                // text editors, combo boxes
        listBackground,                 // panes and the strips behind rows
        panelHeader,                    // strips that sit above a pane's content

        // ink
        text,                           // default label / value text
        textDim,                        // labels beside a value, rows at rest
        textGhost,                      // the quietest ink: separators, a sample slot with no file
        menuHeaderText,                 // the muted ink: inactive tabs, section headers in menus

        selectedRow,                    // tint behind a selected row or an active toggle

        outline,                        // hairlines and section outlines
        outlineDim,                     // the quieter divider between columns
        outlineStrong,                  // a border that has to be seen: scroll thumbs, pressed chips

        accent,                         // the cyan: selection and action
        accentText,                     // the same cyan, dark enough to read as text
        accentDeep,                     // borders and rails in the accent hue
        accentInk,                      // text drawn on top of an accent fill
        accentEdge,                     // the lighter rim of an accent fill
        accentGlow,                     // halo around a lit accent control; none on a light background

        ledOn,                          // the lit lens of a state lamp: the chosen item in a menu
        ledEdge,                        // the rim of that lens
        ledGlow,                        // its halo; none on a light background

        buttonBackground,               // action buttons and pane tools at rest

        // sample slots
        audition,                       // the pulse on the name of the sample being auditioned
        dropTarget,                     // a slot that will take the file being dragged over it

        // chrome
        tabBackground,
        dialogBackground
    };
}
