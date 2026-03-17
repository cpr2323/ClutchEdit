#include "LedColorList.h"

int getLedColorIndex (juce::String ledColor)
{
    if (ledColor.equalsIgnoreCase ("WHITE"))
        return 0;
    else if (ledColor.equalsIgnoreCase ("RED"))
        return 1;
    else if (ledColor.equalsIgnoreCase ("GREEN"))
        return 2;
    else if (ledColor.equalsIgnoreCase ("BLUE"))
        return 3;
    else if (ledColor.equalsIgnoreCase ("ORANGE"))
        return 4;
    else if (ledColor.equalsIgnoreCase ("CYAN"))
        return 5;
    else if (ledColor.equalsIgnoreCase ("VIOLET"))
        return 6;
    else if (ledColor.equalsIgnoreCase ("YELLOW"))
        return 7;
    else
        return 0;
}