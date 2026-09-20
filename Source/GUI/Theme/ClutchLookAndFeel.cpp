#include "ClutchLookAndFeel.h"
#include "ClutchFonts.h"
#include "UiComponents.h"

namespace
{
    constexpr auto kFieldPadding { 7 };
    constexpr auto kComboCaretWidth { 7.0f };

    // padding either side of a tab's name
    constexpr auto kTabPadding { 15 };
    // the accent bar that marks the front tab
    constexpr auto kTabUnderlineHeight { 2 };

    // A field shows the pointer the same way every other control does.
    bool isHovered (const juce::Component& component)
    {
        return component.isEnabled () && component.isMouseOver (true);
    }

    // A dense grid can ask for a box with no room for a caret; it says so with a
    // property rather than with a LookAndFeel, and therefore a palette, of its own.
    bool comboShowsCaret (const juce::ComboBox& box)
    {
        return ! box.getProperties ().contains (ClutchLnFProperties::noCaret);
    }

    // How much of a combo box its value has to fit inside.
    int comboTextWidth (const juce::ComboBox& box)
    {
        const auto rightInset { comboShowsCaret (box) ? 5 + static_cast<int> (kComboCaretWidth) + 2 : kFieldPadding };
        return box.getWidth () - kFieldPadding - rightInset;
    }

    // a value set smaller than this stops reading as the same kind of thing as
    // the values around it, so a longer one is left to be shortened instead
    constexpr auto kMinValueScale { 0.72f };

    // the tab drawing here assumes a bar along the top of its pages, which is the
    // only way the app uses tabs; anything else falls back to JUCE's own drawing
    bool isTopTabBar (const juce::TabbedButtonBar& buttonBar)
    {
        return buttonBar.getOrientation () == juce::TabbedButtonBar::TabsAtTop;
    }

    // The lamp that marks a chosen item in a menu, in place of a tick: a lit lens
    // with a halo, the size of the indicator on a piece of hardware rather than
    // the size of the row it sits in.
    constexpr auto kMenuLedDiameter { 7.0f };

    void drawLed (juce::Graphics& g, const juce::LookAndFeel& colours, juce::Point<float> centre, bool dimmed)
    {
        const auto lens { juce::Rectangle<float> (kMenuLedDiameter, kMenuLedDiameter).withCentre (centre) };
        const auto alpha { dimmed ? 0.5f : 1.0f };

        const auto glow { colours.findColour (ClutchColours::ledGlow) };
        if (! glow.isTransparent ())
        {
            juce::Path lensPath;
            lensPath.addEllipse (lens);
            juce::DropShadow (glow.withMultipliedAlpha (alpha), 6, {}).drawForPath (g, lensPath);
        }

        g.setColour (colours.findColour (ClutchColours::ledOn).withMultipliedAlpha (alpha));
        g.fillEllipse (lens);
        g.setColour (colours.findColour (ClutchColours::ledEdge).withMultipliedAlpha (alpha));
        g.drawEllipse (lens.reduced (0.5f), 1.0f);
    }

    // Where LookAndFeel_V4 puts an item's icon, and so where its tick would have
    // gone. Kept in step with the base class by following the same arithmetic.
    juce::Rectangle<int> popupMenuIconArea (const juce::Rectangle<int>& area)
    {
        auto row { area.reduced (1) };
        row.reduce (juce::jmin (5, area.getWidth () / 20), 0);
        return row.removeFromLeft (juce::roundToInt (static_cast<float> (row.getHeight ()) / 1.3f));
    }

    constexpr auto kTooltipMaxWidth { 400.0f };
    constexpr auto kTooltipPaddingX { 8 };
    constexpr auto kTooltipPaddingY { 5 };

    juce::TextLayout layoutTooltip (const juce::String& text, juce::Colour colour)
    {
        juce::AttributedString attributedText;
        attributedText.setJustification (juce::Justification::centredLeft);
        attributedText.append (text, ClutchType::body (), colour);

        juce::TextLayout layout;
        layout.createLayoutWithBalancedLineLengths (attributedText, kTooltipMaxWidth);
        return layout;
    }
}

ClutchLookAndFeel::ClutchLookAndFeel ()
{
    applyPalette ();
    // anything that does not ask for a font of its own is set in Plex Sans
    setDefaultSansSerifTypeface (ClutchFonts::getDefaultTypeface ());
}

void ClutchLookAndFeel::setBackground (float newBackground)
{
    palette.setBackground (newBackground);
    applyPalette ();
}

void ClutchLookAndFeel::applyPalette ()
{
    for (const auto& [colourId, colour] : palette.getColours ())
        setColour (colourId, colour);
}

//==============================================================================
void ClutchLookAndFeel::fillTextEditorBackground (juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
{
    ClutchPaint::fieldBackground (g, textEditor, { 0, 0, width, height }, textEditor.isEnabled (),
                                  juce::TextEditor::backgroundColourId);
}

void ClutchLookAndFeel::drawTextEditorOutline (juce::Graphics& g, int width, int height, juce::TextEditor& textEditor)
{
    ClutchPaint::fieldOutline (g, textEditor, { 0, 0, width, height }, textEditor.isEnabled (),
                               textEditor.hasKeyboardFocus (true) || isHovered (textEditor));
}

void ClutchLookAndFeel::drawComboBox (juce::Graphics& g, int width, int height, bool,
                                      int, int, int, int, juce::ComboBox& box)
{
    const juce::Rectangle<int> area { 0, 0, width, height };
    const auto enabled { box.isEnabled () };
    const auto hovered { isHovered (box) };
    const auto showsCaret { comboShowsCaret (box) };

    // a combo box keeps its own background role, so a pattern step can be tinted
    // without every other field following it
    ClutchPaint::fieldBackground (g, box, area, enabled, juce::ComboBox::backgroundColourId);
    ClutchPaint::fieldOutline (g, box, area, enabled, hovered || box.isPopupActive ());

    if (! showsCaret)
        return;

    g.setColour (box.findColour (hovered ? ClutchColours::accent : ClutchColours::menuHeaderText));
    ClutchPaint::caretDown (g, { static_cast<float> (width) - 5.0f - (kComboCaretWidth * 0.5f), (static_cast<float> (height) * 0.5f) + 0.5f },
                            kComboCaretWidth);
}

void ClutchLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
{
    const auto showsCaret { comboShowsCaret (box) };
    label.setBorderSize ({ 0, 0, 0, 0 });
    label.setBounds (kFieldPadding, 0, comboTextWidth (box), box.getHeight ());
    label.setJustificationType (showsCaret ? juce::Justification::centredLeft : juce::Justification::centred);
    label.setFont (getComboBoxFont (box));
    // A value too long for its box is set smaller rather than squeezed narrower:
    // the default squeeze runs the glyphs of a mono face into each other.
    label.setMinimumHorizontalScale (1.0f);
}

juce::Font ClutchLookAndFeel::getComboBoxFont (juce::ComboBox& box)
{
    const auto font { ClutchType::value () };
    const auto available { comboTextWidth (box) };
    if (available <= 0)
        return font;

    // Sized to the longest choice rather than to the one showing, so the value
    // does not change size as it is changed.
    auto widest { 0 };
    for (auto itemIndex { 0 }; itemIndex < box.getNumItems (); ++itemIndex)
        widest = std::max (widest, ClutchPaint::textWidth (font, box.getItemText (itemIndex)));
    if (widest <= available)
        return font;

    const auto scale { std::max (kMinValueScale, static_cast<float> (available) / static_cast<float> (widest)) };
    return font.withHeight (font.getHeight () * scale);
}

//==============================================================================
juce::Font ClutchLookAndFeel::getTextButtonFont (juce::TextButton&, int)
{
    return ClutchType::button ();
}

void ClutchLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                                              bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    const auto area { button.getLocalBounds ().toFloat ().reduced (0.5f) };
    const auto hovered { button.isEnabled () && (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown) };

    g.setColour (backgroundColour);
    g.fillRoundedRectangle (area, ClutchPaint::kFieldCornerSize);
    g.setColour (button.findColour (hovered ? ClutchColours::accentDeep : ClutchColours::outline));
    g.drawRoundedRectangle (area, ClutchPaint::kFieldCornerSize, 1.0f);
}

//==============================================================================
int ClutchLookAndFeel::getTabButtonBestWidth (juce::TabBarButton& button, int tabDepth)
{
    if (! isTopTabBar (button.getTabbedButtonBar ()))
        return juce::LookAndFeel_V4::getTabButtonBestWidth (button, tabDepth);

    return (kTabPadding * 2) + ClutchPaint::textWidth (ClutchType::editorTab (), button.getButtonText ());
}

int ClutchLookAndFeel::getTabButtonOverlap (int)
{
    // tabs sit edge to edge, divided by their own hairline
    return 0;
}

void ClutchLookAndFeel::drawTabbedButtonBarBackground (juce::TabbedButtonBar& buttonBar, juce::Graphics& g)
{
    g.fillAll (buttonBar.findColour (ClutchColours::tabBackground));
    if (! isTopTabBar (buttonBar))
        return;

    g.setColour (buttonBar.findColour (ClutchColours::outline));
    g.drawHorizontalLine (buttonBar.getHeight () - 1, 0.0f, static_cast<float> (buttonBar.getWidth ()));
}

void ClutchLookAndFeel::drawTabAreaBehindFrontButton (juce::TabbedButtonBar&, juce::Graphics&, int, int)
{
    // the front tab marks itself with its own underline, so there is no shadow behind it
}

void ClutchLookAndFeel::drawTabButton (juce::TabBarButton& button, juce::Graphics& g, bool isMouseOver, bool isMouseDown)
{
    if (! isTopTabBar (button.getTabbedButtonBar ()))
    {
        juce::LookAndFeel_V4::drawTabButton (button, g, isMouseOver, isMouseDown);
        return;
    }

    const auto bounds { button.getLocalBounds () };
    const auto selected { button.getToggleState () };
    const auto hovered { (isMouseOver || isMouseDown) && ! selected };

    // the front tab takes the colour of the page under it, so the two read as one
    // surface; the others sit on the strip
    if (selected)
        g.fillAll (button.findColour (ClutchColours::windowBackground));
    else if (hovered)
        g.fillAll (button.findColour (ClutchColours::panelHeader));

    g.setColour (button.findColour (ClutchColours::outlineDim));
    g.fillRect (bounds.withLeft (bounds.getRight () - 1));

    g.setFont (ClutchType::editorTab ());
    g.setColour (button.findColour (selected ? ClutchColours::text
                                             : (hovered ? ClutchColours::textDim : ClutchColours::menuHeaderText)));
    g.drawText (button.getButtonText (), bounds.reduced (kTabPadding, 0), juce::Justification::centred, false);

    if (selected)
    {
        g.setColour (button.findColour (ClutchColours::accent));
        g.fillRect (bounds.withTop (bounds.getBottom () - kTabUnderlineHeight));
    }
    else if (hovered)
    {
        g.setColour (button.findColour (ClutchColours::accentDeep));
        g.drawRect (bounds.withTrimmedBottom (1), 1);
    }
}

//==============================================================================
juce::Font ClutchLookAndFeel::getPopupMenuFont ()
{
    return ClutchType::body ();
}

void ClutchLookAndFeel::drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
                                           bool isSeparator, bool isActive, bool isHighlighted, bool isTicked,
                                           bool hasSubMenu, const juce::String& text, const juce::String& shortcutKeyText,
                                           const juce::Drawable* icon, const juce::Colour* textColour)
{
    // the item is drawn without its tick, and the lamp is lit where that tick
    // would have been: a chosen value reads as a state the app is in, not as a
    // mark somebody made
    LookAndFeel_V4::drawPopupMenuItem (g, area, isSeparator, isActive, isHighlighted, false,
                                       hasSubMenu, text, shortcutKeyText, icon, textColour);

    // an item carrying an icon of its own has nowhere to put the lamp
    if (isSeparator || ! isTicked || icon != nullptr)
        return;

    drawLed (g, *this, popupMenuIconArea (area).toFloat ().getCentre (), ! isActive);
}

void ClutchLookAndFeel::drawPopupMenuSectionHeader (juce::Graphics& g, const juce::Rectangle<int>& area, const juce::String& sectionName)
{
    g.setFont (ClutchType::menuSectionHeader ());
    g.setColour (findColour (juce::PopupMenu::headerTextColourId));
    // sits slightly low in its row, so it reads as belonging to the items below it
    g.drawText (sectionName.toUpperCase (), area.reduced (11, 0).withTrimmedTop (3), juce::Justification::centredLeft, true);
}

void ClutchLookAndFeel::getIdealPopupMenuSectionHeaderSizeWithOptions (const juce::String& text, int,
                                                                       int& idealWidth, int& idealHeight,
                                                                       const juce::PopupMenu::Options&)
{
    // the default is one and a half item heights, which leaves a header floating
    // in empty space; the header text plus a little room is enough
    const auto font { ClutchType::menuSectionHeader () };
    idealHeight = juce::roundToInt (font.getHeight ()) + 9;
    idealWidth = ClutchPaint::textWidth (font, text.toUpperCase ()) + 22;
}

//==============================================================================
juce::Rectangle<int> ClutchLookAndFeel::getTooltipBounds (const juce::String& tipText, juce::Point<int> screenPos, juce::Rectangle<int> parentArea)
{
    const auto layout { layoutTooltip (tipText, juce::Colours::black) };
    const auto width { juce::roundToInt (std::ceil (layout.getWidth ())) + (kTooltipPaddingX * 2) };
    const auto height { juce::roundToInt (std::ceil (layout.getHeight ())) + (kTooltipPaddingY * 2) };

    // placed away from the pointer, on whichever side of it there is more room
    return juce::Rectangle<int> (screenPos.x > parentArea.getCentreX () ? screenPos.x - (width + 12) : screenPos.x + 24,
                                 screenPos.y > parentArea.getCentreY () ? screenPos.y - (height + 6) : screenPos.y + 6,
                                 width, height)
               .constrainedWithin (parentArea);
}

void ClutchLookAndFeel::drawTooltip (juce::Graphics& g, const juce::String& text, int width, int height)
{
    const juce::Rectangle<int> bounds { 0, 0, width, height };
    g.fillAll (findColour (juce::TooltipWindow::backgroundColourId));
    g.setColour (findColour (juce::TooltipWindow::outlineColourId));
    g.drawRect (bounds, 1);

    layoutTooltip (text, findColour (juce::TooltipWindow::textColourId))
        .draw (g, bounds.reduced (kTooltipPaddingX, kTooltipPaddingY).toFloat ());
}

//==============================================================================
int ClutchLookAndFeel::getDefaultScrollbarWidth ()
{
    return 8;
}

void ClutchLookAndFeel::drawScrollbar (juce::Graphics& g, juce::ScrollBar& scrollbar, int x, int y, int width, int height,
                                       bool isScrollbarVertical, int thumbStartPosition, int thumbSize,
                                       bool isMouseOver, bool isMouseDown)
{
    juce::Rectangle<int> thumbBounds { x, y, width, height };
    thumbBounds = isScrollbarVertical ? thumbBounds.withY (thumbStartPosition).withHeight (thumbSize)
                                      : thumbBounds.withX (thumbStartPosition).withWidth (thumbSize);
    const auto thumb { thumbBounds.toFloat ().reduced (1.0f) };

    g.setColour (scrollbar.findColour (isMouseOver || isMouseDown ? ClutchColours::accentDeep : ClutchColours::outlineStrong));
    g.fillRoundedRectangle (thumb, std::min (thumb.getWidth (), thumb.getHeight ()) * 0.5f);
}
