#pragma once

#include <JuceHeader.h>
#include "../../Clutch/EffectListProperties.h"
#include "../../Utility/CustomComboBox.h"
#include "../../Utility/NoArrowComboBoxLnF.h"

class EffectEditorComponent : public juce::Component
{
public:
    EffectEditorComponent ();
    ~EffectEditorComponent ();

    void init (juce::ValueTree rootPropertiesVT);

private:
    EffectListProperties effectListProperties;
    std::array<juce::Label, 8> effectLabels;
    std::array<CustomComboBox, 8> effectEditors;
    std::array<EffectProperties, 8> effectProperties;
    NoArrowComboBoxLnF noArrowComboBoxLnF;

    void paint (juce::Graphics& g) override;
    void resized () override;
    void onEffectUiChanged (int effectIndex);
    void onEffectDataChanged (int effectIndex);
};