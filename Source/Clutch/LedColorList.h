#pragma once

#include <JuceHeader.h>

enum class LedColor
{
    white = 0,
    red,
    green,
    blue,
    orange,
    cyan,
    violet,
    yellow
};

const std::array<juce::String, 8> gLedColorList
{
    "WHITE", "RED", "GREEN", "BLUE", "ORANGE", "CYAN", "VIOLET", "YELLOW"
};
