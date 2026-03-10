#include "GuiProperties.h"

const auto defaultXPos { -1 };
const auto defaultYPos { -1 };
const auto defaultWidth { 1117 };
const auto defaultHeight { 609 };

void GuiProperties::initValueTree ()
{
    setPosition (defaultXPos, defaultYPos, false);
    setSize (defaultWidth, defaultHeight, false);
    setActiveTab (0, false);
}

void GuiProperties::processValueTree ()
{
    if (! data.hasProperty (PositionPropertyId))
        setPosition (defaultXPos, defaultYPos, false);
    if (! data.hasProperty (SizePropertyId))
        setSize (defaultWidth, defaultHeight, false);
    if (! data.hasProperty (ActiveTabPropertyId))
        setActiveTab (0, false);
}

void GuiProperties::setPosition (int x, int y, bool includeSelfCallback)
{
    setValue (juce::String (x) + "," + juce::String (y), PositionPropertyId, includeSelfCallback);
}

void GuiProperties::setSize (int width, int height, bool includeSelfCallback)
{
    setValue (juce::String (width) + "," + juce::String (height), SizePropertyId, includeSelfCallback);
}

void GuiProperties::setActiveTab (int tabIndex, bool includeSelfCallback)
{
    setValue (tabIndex, ActiveTabPropertyId, includeSelfCallback);
}

std::tuple<int, int> GuiProperties::getPosition ()
{
    const auto values { juce::StringArray::fromTokens (getValue<juce::String> (PositionPropertyId), ",", {}) };
    jassert (values.size () == 2);
    return { values [0].getIntValue (), values [1].getIntValue () };
}

std::tuple<int, int> GuiProperties::getSize ()
{
    const auto values { juce::StringArray::fromTokens (getValue<juce::String> (SizePropertyId), ",", {}) };
    jassert (values.size () == 2);
    return { values [0].getIntValue (), values [1].getIntValue () };
}

int GuiProperties::getActiveTab ()
{
    return getValue<int> (ActiveTabPropertyId);
}