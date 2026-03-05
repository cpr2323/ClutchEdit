#pragma once

#include <JuceHeader.h>
#include "../../Clutch/EffectProperties.h"
#include "../../Clutch/EffectListProperties.h"
#include "../../Utility/CustomComboBox.h"
#include "../../Utility/NoArrowComboBoxLnF.h"

// FX_WHITE  = SPUTTER;    d: SPUTTER
// FX_RED    = BITCRUSH;   d: BITCRUSH
// FX_GREEN  = COMBFILTER; d: COMBFILTER
// FX_BLUE   = DJFILTER;   d: DJFILTER
// FX_ORANGE = DUBECHO;    d: DUBECHO
// FX_CYAN   = CHORUS;     d: CHORUS
// FX_VIOLET = REVERB;     d: REVERB
// FX_YELLOW = GLITCH;     d: GLITCH

class EffectEditorComponent : public juce::Component
{
public:
    EffectEditorComponent ();
    ~EffectEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    std::array<juce::Label, 8> effectLabels;
    std::array<CustomComboBox, 8> effectEditors;
    std::array<EffectProperties, 8> effectProperties;
    std::array<EffectProperties, 8> uneditedEffectProperties;
    NoArrowComboBoxLnF noArrowComboBoxLnF;

    void paintOverChildren (juce::Graphics& g) override;
    void resized () override;
    void onEffectUiChanged (int effectIndex);
    void onEffectDataChanged (int effectIndex);
};