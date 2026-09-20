#pragma once

#include <JuceHeader.h>
#include "ClutchColourIds.h"
#include "ClutchFonts.h"

/*
    Small pieces the app repeats often enough that they should only exist once.
    All of them resolve their colours at paint time, so they follow the palette
    without needing to be told a change happened.

    Anything that can be clicked answers the pointer the same way: its border
    takes the deep accent.
*/

namespace ClutchPaint
{
    /*
        The chrome of a value field: the recessed fill, and the hairline around it
        that takes the deep accent while the pointer is on it.

        This lives here rather than inside the LookAndFeel because not every field
        in the app is a juce::TextEditor or juce::ComboBox - a sample slot is a
        juce::Label - and all of them have to be the same kind of object to the eye.
        The LookAndFeel draws its own fields through these too, so there is one
        description of what a field looks like.
    */
    inline constexpr float kFieldCornerSize { 2.0f };

    // A control that JUCE gives a background role of its own - a TextEditor, a
    // ComboBox - passes that role in, so a single control can still be tinted on
    // its own. Anything else takes the app's field role.
    inline void fieldBackground (juce::Graphics& g, const juce::Component& colourSource,
                                 juce::Rectangle<int> bounds, bool enabled,
                                 int enabledColourId = ClutchColours::fieldBackground)
    {
        // an unusable field sinks into the panel rather than staying recessed
        const auto colourId { enabled ? enabledColourId : static_cast<int> (ClutchColours::listBackground) };
        g.setColour (colourSource.findColour (colourId));
        g.fillRoundedRectangle (bounds.toFloat (), kFieldCornerSize);
    }

    inline void fieldOutline (juce::Graphics& g, const juce::Component& colourSource,
                              juce::Rectangle<int> bounds, bool enabled, bool highlighted)
    {
        const auto colourId { ! enabled ? ClutchColours::outlineDim
                                        : (highlighted ? ClutchColours::accentDeep : ClutchColours::outline) };
        g.setColour (colourSource.findColour (colourId));
        g.drawRoundedRectangle (bounds.toFloat ().reduced (0.5f), kFieldCornerSize, 1.0f);
    }

    // A section of the editor, or a whole pane: a filled, outlined panel lifted
    // off the background.
    inline void card (juce::Graphics& g, const juce::Component& colourSource, juce::Rectangle<int> bounds,
                      int fillColourId = ClutchColours::listBackground, float cornerSize = 3.0f)
    {
        const auto area { bounds.toFloat ().reduced (0.5f) };
        g.setColour (colourSource.findColour (fillColourId));
        g.fillRoundedRectangle (area, cornerSize);
        g.setColour (colourSource.findColour (ClutchColours::outline));
        g.drawRoundedRectangle (area, cornerSize, 1.0f);
    }

    // The outline alone, for a section drawn over a pane that has already been filled.
    inline void sectionOutline (juce::Graphics& g, const juce::Component& colourSource, juce::Rectangle<int> bounds,
                                float cornerSize = 3.0f)
    {
        g.setColour (colourSource.findColour (ClutchColours::outline));
        g.drawRoundedRectangle (bounds.toFloat ().reduced (0.5f), cornerSize, 1.0f);
    }

    // The width a line of text takes in a font, tracking included.
    inline int textWidth (const juce::Font& font, const juce::String& text)
    {
        return juce::roundToInt (std::ceil (juce::GlyphArrangement::getStringWidth (font, text)));
    }

    // A small solid triangle pointing down, centred on a point. Drawn rather than
    // typed, as the embedded faces do not carry the arrow glyphs.
    inline void caretDown (juce::Graphics& g, juce::Point<float> centre, float width)
    {
        const auto height { width * 0.55f };
        juce::Path caret;
        caret.addTriangle (centre.x - (width * 0.5f), centre.y - (height * 0.5f),
                           centre.x + (width * 0.5f), centre.y - (height * 0.5f),
                           centre.x, centre.y + (height * 0.5f));
        g.fillPath (caret);
    }
}

/*
    Repaints a control whenever the pointer enters or leaves it, or any of its
    children.

    A ComboBox or TextEditor is almost entirely covered by child components, so
    the pointer enters and leaves those rather than the control itself, and the
    control's own repaint-on-hover rarely fires: its highlight would either not
    appear, or not go away. Listening to the children as well fixes both.
*/
class HoverHighlight : private juce::MouseListener
{
public:
    static void attach (juce::Component& control)
    {
        control.getProperties ().set (kHoverTargetId, true);
        control.addMouseListener (&getInstance (), true);
    }

private:
    static inline const juce::Identifier kHoverTargetId { "hoverHighlightTarget" };

    static HoverHighlight& getInstance ()
    {
        static HoverHighlight instance;
        return instance;
    }

    // the event arrives for whichever child is under the pointer; the control to
    // repaint is the nearest one that asked for this
    static void repaintTarget (const juce::MouseEvent& mouseEvent)
    {
        for (auto* component { mouseEvent.eventComponent }; component != nullptr; component = component->getParentComponent ())
        {
            if (component->getProperties ().contains (kHoverTargetId))
            {
                component->repaint ();
                return;
            }
        }
    }

    void mouseEnter (const juce::MouseEvent& mouseEvent) override { repaintTarget (mouseEvent); }
    void mouseExit (const juce::MouseEvent& mouseEvent) override  { repaintTarget (mouseEvent); }
    void mouseUp (const juce::MouseEvent& mouseEvent) override    { repaintTarget (mouseEvent); }
};

/*
    The small outlined buttons of the chrome. Two sizes of the same idea: a mini
    for pane tools, and a chip for the path bar (OUT, SETTINGS). A chip can carry
    a value after its label and a caret after that, which is how the output device
    reads as "OUT  Speakers (HD Audio)  v".

    A toggled on button takes the selection tint and the accent, so an on state
    is visible without hovering over it.
*/
class ChromeButton : public juce::TextButton
{
public:
    enum class Size { mini, chip };

    explicit ChromeButton (juce::String text, Size theSize = Size::mini)
        : size (theSize)
    {
        setButtonText (text);
    }

    void setValueText (juce::String newValueText)
    {
        valueText = std::move (newValueText);
        repaint ();
    }

    void setShowsCaret (bool shouldShowCaret)
    {
        showsCaret = shouldShowCaret;
        repaint ();
    }

    static constexpr int kMiniHeight { 19 };
    static constexpr int kChipHeight { 22 };

    int getIdealWidth () const
    {
        const auto padding { size == Size::mini ? 6 : 8 };
        auto width { padding * 2 + ClutchPaint::textWidth (labelFont (), getButtonText ()) };
        if (valueText.isNotEmpty ())
            width += kGap + ClutchPaint::textWidth (ClutchType::chipValue (), valueText);
        if (showsCaret)
            width += kGap + kChipCaretWidth;
        return width + 2;
    }

    void paintButton (juce::Graphics& g, bool isMouseOver, bool isMouseDown) override
    {
        const auto area { getLocalBounds ().toFloat ().reduced (0.5f) };
        const auto enabled { isEnabled () };
        const auto on { getToggleState () };
        const auto hovered { enabled && (isMouseOver || isMouseDown) };

        g.setColour (findColour (on ? ClutchColours::selectedRow
                                    : (size == Size::mini ? ClutchColours::buttonBackground : ClutchColours::panelHeader)));
        g.fillRoundedRectangle (area, 2.0f);
        g.setColour (findColour (on || hovered ? ClutchColours::accentDeep : ClutchColours::outline));
        g.drawRoundedRectangle (area, 2.0f, 1.0f);

        const auto labelColour { findColour (! enabled ? ClutchColours::textGhost
                                                       : (on ? ClutchColours::accentText
                                                             : (hovered ? ClutchColours::text : ClutchColours::textDim))) };

        if (valueText.isEmpty () && ! showsCaret)
        {
            g.setFont (labelFont ());
            g.setColour (labelColour);
            g.drawText (getButtonText (), getLocalBounds (), juce::Justification::centred, false);
            return;
        }

        auto content { getLocalBounds ().reduced (size == Size::mini ? 6 : 8, 0) };
        g.setFont (labelFont ());
        g.setColour (labelColour);
        const auto labelWidth { ClutchPaint::textWidth (labelFont (), getButtonText ()) };
        g.drawText (getButtonText (), content.removeFromLeft (labelWidth), juce::Justification::centredLeft, false);

        if (showsCaret)
        {
            const auto caretArea { content.removeFromRight (kChipCaretWidth) };
            g.setColour (findColour (ClutchColours::menuHeaderText));
            ClutchPaint::caretDown (g, caretArea.toFloat ().getCentre (), static_cast<float> (kChipCaretWidth));
            content.removeFromRight (kGap);
        }

        if (valueText.isNotEmpty ())
        {
            content.removeFromLeft (kGap);
            g.setFont (ClutchType::chipValue ());
            g.setColour (findColour (enabled ? ClutchColours::text : ClutchColours::textGhost));
            g.drawFittedText (valueText, content, juce::Justification::centredLeft, 1, 1.0f);
        }
    }

private:
    static constexpr int kGap { 6 };
    static constexpr int kChipCaretWidth { 6 };

    Size size;
    juce::String valueText;
    bool showsCaret { false };

    juce::Font labelFont () const { return size == Size::mini ? ClutchType::mini () : ClutchType::chip (); }
};

/*
    The editor's buttons: TOOLS, OPEN, SAVE. A primary one takes the accent fill -
    that is kept for the single action most worth finding, and only while it has
    something to do.
*/
class ActionButton : public juce::TextButton
{
public:
    enum class Size { normal, small };

    explicit ActionButton (juce::String text, Size theSize = Size::normal)
        : size (theSize)
    {
        setButtonText (text);
    }

    void setPrimary (bool shouldBePrimary)
    {
        if (primary == shouldBePrimary)
            return;
        primary = shouldBePrimary;
        repaint ();
    }

    void setShowsCaret (bool shouldShowCaret)
    {
        showsCaret = shouldShowCaret;
        repaint ();
    }

    static constexpr int kNormalHeight { 25 };
    static constexpr int kSmallHeight { 23 };

    int getIdealWidth () const
    {
        auto width { (horizontalPadding () * 2) + ClutchPaint::textWidth (font (), getButtonText ()) };
        if (showsCaret)
            width += kCaretGap + kCaretWidth;
        return width + 2;
    }

    void paintButton (juce::Graphics& g, bool isMouseOver, bool isMouseDown) override
    {
        const auto area { getLocalBounds ().toFloat ().reduced (0.5f) };
        const auto enabled { isEnabled () };
        const auto hovered { enabled && (isMouseOver || isMouseDown) };
        const auto asPrimary { primary && enabled };

        if (asPrimary)
        {
            const auto glow { findColour (ClutchColours::accentGlow) };
            if (! glow.isTransparent ())
            {
                juce::Path body;
                body.addRoundedRectangle (area, 2.0f);
                juce::DropShadow (glow, 12, {}).drawForPath (g, body);
            }
        }

        g.setColour (findColour (asPrimary ? ClutchColours::accent : ClutchColours::buttonBackground));
        g.fillRoundedRectangle (area, 2.0f);
        g.setColour (findColour (asPrimary ? (hovered ? ClutchColours::accentInk : ClutchColours::accentEdge)
                                           : (hovered ? ClutchColours::accentDeep : ClutchColours::outline)));
        g.drawRoundedRectangle (area, 2.0f, 1.0f);

        const auto textColour { findColour (asPrimary ? ClutchColours::accentInk
                                                      : (! enabled ? ClutchColours::textGhost
                                                                   : (hovered ? ClutchColours::text : ClutchColours::textDim))) };

        // label and caret are centred as one unit
        const auto labelWidth { ClutchPaint::textWidth (font (), getButtonText ()) };
        const auto contentWidth { labelWidth + (showsCaret ? kCaretGap + kCaretWidth : 0) };
        auto content { getLocalBounds ().withSizeKeepingCentre (contentWidth, getHeight ()) };

        g.setFont (font ());
        g.setColour (textColour);
        g.drawText (getButtonText (), content.removeFromLeft (labelWidth), juce::Justification::centredLeft, false);

        if (showsCaret)
        {
            content.removeFromLeft (kCaretGap);
            g.setColour (textColour.withMultipliedAlpha (0.7f));
            ClutchPaint::caretDown (g, content.toFloat ().getCentre ().translated (0.0f, 0.5f), static_cast<float> (kCaretWidth));
        }
    }

private:
    static constexpr int kCaretGap { 5 };
    static constexpr int kCaretWidth { 6 };

    Size size;
    bool primary { false };
    bool showsCaret { false };

    juce::Font font () const { return size == Size::normal ? ClutchType::button () : ClutchType::buttonSmall (); }
    int horizontalPadding () const { return size == Size::normal ? 13 : 10; }
};

/*
    A button that opens a menu, and says so with a caret after its label.
*/
class MenuButton : public ActionButton
{
public:
    explicit MenuButton (juce::String text, Size theSize = Size::normal)
        : ActionButton (std::move (text), theSize)
    {
        setShowsCaret (true);
    }
};
