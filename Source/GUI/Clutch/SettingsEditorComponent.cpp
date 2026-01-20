#include "SettingsEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

juce::String getRoundedFloatString (float value, int decimalPlaces)
{
    return juce::String (value, decimalPlaces).trimCharactersAtEnd ("0").trimCharactersAtEnd (".");
}

SettingsEditorComponent::SettingsEditorComponent ()
{
    auto setupDoubleEditor = [this] (CustomTextEditorDouble& editor,
                                     juce::Label& label,
                                     const juce::String& labelText)
    {
        label.setText (labelText, juce::dontSendNotification);
        addAndMakeVisible (label);
        editor.setColour (juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
        editor.setIndents (5, 2);
        addAndMakeVisible (editor);
    };
    auto setupIntEditor = [this] (CustomTextEditorInt& editor,
                                 juce::Label& label,
                                 const juce::String& labelText)
    {
        label.setText (labelText, juce::dontSendNotification);
        addAndMakeVisible (label);
        editor.setColour (juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
        editor.setIndents (5, 2);
        addAndMakeVisible (editor);
    };
    auto setupComboBox = [this] (CustomComboBox& comboBox,
                                 juce::Label& label,
                                 const juce::String& labelText)
    {
        label.setText (labelText, juce::dontSendNotification);
        addAndMakeVisible (label);
        comboBox.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
        addAndMakeVisible (comboBox);
    };

    accClAmpModEditor.setTooltip ("Amp Mod CLOSED ACC hit");
    accClAmpModEditor.getMinValueCallback = [this] () { return 0.1; };
    accClAmpModEditor.getMaxValueCallback = [this] () { return 10.0; };
    accClAmpModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    accClAmpModEditor.updateDataCallback = [this] (double value) { accClAmpModUiChanged ( static_cast<float> (value)); };
    accClAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.01f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3f;
            else
                return 1.0f;
        } ();
        const auto newValue { settingsProperties.getAccClAmpMod () + (multiplier * direction) };
        accClAmpModEditor.setValue (newValue);
    };
    accClAmpModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accClAmpModEditor, accClAmpModLabel, "Acc Cl Amp Mod");

    accClRelModEditor.setTooltip ("Acc Cl Rel Mod");
    accClRelModEditor.getMinValueCallback = [this] () { return 0.1; };
    accClRelModEditor.getMaxValueCallback = [this] () { return 10.0; };
    accClRelModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    accClRelModEditor.updateDataCallback = [this] (double value) { accClRelModUiChanged (static_cast<float> (value)); };
    accClRelModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.01f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3f;
            else
                return 1.0f;
        } ();
        accClRelModEditor.setValue (settingsProperties.getAccClRelMod () + (multiplier * direction));
    };
    accClRelModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accClRelModEditor, accClRelModLabel, "Acc Cl Rel Mod");

    accOpAmpModEditor.setTooltip ("Acc Op Amp Mod");
    accOpAmpModEditor.getMinValueCallback = [this] () { return 0.1; };
    accOpAmpModEditor.getMaxValueCallback = [this] () { return 10.0; };
    accOpAmpModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    accOpAmpModEditor.updateDataCallback = [this] (double value) { accOpAmpModUiChanged (static_cast<float> (value)); };
    accOpAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.5f;
            else
                return 1.0f;
        } ();
        accOpAmpModEditor.setValue (settingsProperties.getAccOpAmpMod () + (multiplier * direction));
    };
    accOpAmpModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accOpAmpModEditor, accOpAmpModLabel, "Acc Op Amp Mod");

    accOpRelModEditor.setTooltip ("Acc Op Rel Mod");
    accOpRelModEditor.getMinValueCallback = [this] () { return 0.1; };
    accOpRelModEditor.getMaxValueCallback = [this] () { return 10.0; };
    accOpRelModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    accOpRelModEditor.updateDataCallback = [this] (double value) { accOpRelModUiChanged (static_cast<float> (value)); };
    accOpRelModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.5f;
            else
                return 1.0f;
        } ();
        accOpRelModEditor.setValue (settingsProperties.getAccOpRelMod () + (multiplier * direction));
    };
    accOpRelModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accOpRelModEditor, accOpRelModLabel, "Acc Op Rel Mod");

    chokeReleaseEditor.setTooltip ("Choke Release");
    chokeReleaseEditor.getMinValueCallback = [this] () { return 0.001; };
    chokeReleaseEditor.getMaxValueCallback = [this] () { return 10.0; };
    chokeReleaseEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    chokeReleaseEditor.updateDataCallback = [this] (double value) { chokeReleaseUiChanged (static_cast<float> (value)); };
    chokeReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.001;
            else if (dragSpeed == DragSpeed::medium)
                return 0.5;
            else
                return 3.0;
        } ();
        chokeReleaseEditor.setValue (settingsProperties.getChokeRelease () + (multiplier * direction));
    };
    chokeReleaseEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (chokeReleaseEditor, chokeReleaseLabel, "Choke Release");

    clsdMaxReleaseEditor.setTooltip ("Choke Release");
    clsdMaxReleaseEditor.getMinValueCallback = [this] () { return 0.3; };
    clsdMaxReleaseEditor.getMaxValueCallback = [this] () { return 2.0; };
    clsdMaxReleaseEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    clsdMaxReleaseEditor.updateDataCallback = [this] (double value) { clsdMaxReleaseUiChanged (static_cast<float> (value)); };
    clsdMaxReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3f;
            else
                return 1.0f;
        } ();
        clsdMaxReleaseEditor.setValue (settingsProperties.getClsdMaxRelease () + (multiplier * direction));
    };
    clsdMaxReleaseEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (clsdMaxReleaseEditor, clsdMaxReleaseLabel, "Clsd Max Release");

    clsdRelOfstScaleEditor.setTooltip ("Choke Release");
    clsdRelOfstScaleEditor.getMinValueCallback = [this] () { return 0.1; };
    clsdRelOfstScaleEditor.getMaxValueCallback = [this] () { return 0.9; };
    clsdRelOfstScaleEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    clsdRelOfstScaleEditor.updateDataCallback = [this] (double value) { clsdRelOfstScaleUiChanged (static_cast<float> (value)); };
    clsdRelOfstScaleEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow || dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 0.3f;
        } ();
        clsdRelOfstScaleEditor.setValue (settingsProperties.getClsdRelOfstScale () + (multiplier * direction));
    };
    clsdRelOfstScaleEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (clsdRelOfstScaleEditor, clsdRelOfstScaleLabel, "Clsd Rel Ofst Scale");

    // 0: Independent Release for Closed
    // 1: Release Offset mode
    clsdReleaseModeComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    clsdReleaseModeComboBox.setTooltip ("");
    clsdReleaseModeComboBox.addItem ("Independent", 1);
    clsdReleaseModeComboBox.addItem ("Offset", 2);
    clsdReleaseModeComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto clsdReleaseMode { clsdReleaseModeComboBox.getSelectedId () - 1 };
        settingsProperties.setClsdReleaseMode (std::clamp (clsdReleaseMode + scrollAmount, 0, 1), true);
    };
    clsdReleaseModeComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (clsdReleaseModeComboBox, clsdReleaseModeLabel, "Clsd Release Mode");

    // 0: FX CV Always On
    // 1: CV Disable : Freeze FX CV
    cvDisableFxComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    cvDisableFxComboBox.setTooltip ("");
    cvDisableFxComboBox.addItem ("FX CV On", 1);
    cvDisableFxComboBox.addItem ("FX CV Off", 2);
    cvDisableFxComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto cvDisableFx { cvDisableFxComboBox.getSelectedId () - 1 };
        settingsProperties.setCvDisableFx (std::clamp (cvDisableFx + scrollAmount, 0, 1), true);
    };
    cvDisableFxComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (cvDisableFxComboBox, cvDisableFxLabel, "CV Disable FX");

    // 0: Velocity always enabled
    // 1: CV Off SW affects velocity
    cvDisableVelocityComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    cvDisableVelocityComboBox.setTooltip ("");
    cvDisableVelocityComboBox.addItem ("Always On", 1);
    cvDisableVelocityComboBox.addItem ("CV Off", 2);
    cvDisableVelocityComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto cvDisableVelocity { cvDisableVelocityComboBox.getSelectedId () - 1 };
        settingsProperties.setCvDisableVelocity (std::clamp (cvDisableVelocity + scrollAmount, 0, 1), true);
    };
    cvDisableVelocityComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (cvDisableVelocityComboBox, cvDisableVelocityLabel, "CV Disable Velocity");

    envelopeMaxReleaseEditor.setTooltip ("Envelope Max Release");
    envelopeMaxReleaseEditor.getMinValueCallback = [this] () { return 0.6; };
    envelopeMaxReleaseEditor.getMaxValueCallback = [this] () { return 20.0; };
    envelopeMaxReleaseEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    envelopeMaxReleaseEditor.updateDataCallback = [this] (double value) { envelopeMaxReleaseUiChanged (static_cast<float> (value)); };
    envelopeMaxReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.5f;
            else
                return 1.0f;
        } ();
        envelopeMaxReleaseEditor.setValue (settingsProperties.getEnvelopeMaxRelease () + (multiplier * direction));
    };
    envelopeMaxReleaseEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (envelopeMaxReleaseEditor, envelopeMaxReleaseLabel, "Envelope Max Release");

    feelAmpModEditor.setTooltip ("Feel Amp Mod");
    feelAmpModEditor.getMinValueCallback = [this] () { return 0.0; };
    feelAmpModEditor.getMaxValueCallback = [this] () { return 2.0; };
    feelAmpModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    feelAmpModEditor.updateDataCallback = [this] (double value) { feelAmpModUiChanged (static_cast<float> (value)); };
    feelAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow || dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 1.0f;
        } ();
        feelAmpModEditor.setValue (settingsProperties.getFeelAmpMod () + (multiplier * direction));
    };
    feelAmpModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (feelAmpModEditor, feelAmpModLabel, "Feel Amp Mod");

    feelAttackModEditor.setTooltip ("Feel Attack Mod");
    feelAttackModEditor.getMinValueCallback = [this] () { return 0.0; };
    feelAttackModEditor.getMaxValueCallback = [this] () { return 5.0; };
    feelAttackModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    feelAttackModEditor.updateDataCallback = [this] (double value) { feelAttackModUiChanged (static_cast<float> (value)); };
    feelAttackModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow || dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 1.0f;
        } ();
        const auto newValue { settingsProperties.getFeelAttackMod () + (multiplier * direction) };
        feelAttackModEditor.setValue (newValue);
    }; 
    feelAttackModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (feelAttackModEditor, feelAttackModLabel, "Feel Attack Mod");

    feelReleaseModEditor.setTooltip ("Feel Release Mod");
    feelReleaseModEditor.getMinValueCallback = [this] () { return 0.0; };
    feelReleaseModEditor.getMaxValueCallback = [this] () { return 5.0; };
    feelReleaseModEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    feelReleaseModEditor.updateDataCallback = [this] (double value) { feelReleaseModUiChanged (static_cast<float> (value)); };
    feelReleaseModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow || dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 1.0f;
        } ();
        const auto newValue { settingsProperties.getFeelReleaseMod () + (multiplier * direction) };
        feelReleaseModEditor.setValue (newValue);
    };
    feelReleaseModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (feelReleaseModEditor, feelReleaseModLabel, "Feel Release Mod");

    fltrHpfMaxFreqEditor.setTooltip ("Fltr HPF Max Freq");
    fltrHpfMaxFreqEditor.getMinValueCallback = [this] () { return 20; };
    fltrHpfMaxFreqEditor.getMaxValueCallback = [this] () { return 20000; };
    fltrHpfMaxFreqEditor.toStringCallback = [this] (int value) { return getRoundedFloatString (value, 4); };
    fltrHpfMaxFreqEditor.updateDataCallback = [this] (int value) { fltrHpfMaxFreqUiChanged (value); };
    fltrHpfMaxFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFltrHpfMaxFreq () + (multiplier * direction) };
        fltrHpfMaxFreqEditor.setValue (newValue);
    };
    fltrHpfMaxFreqEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fltrHpfMaxFreqEditor, fltrHpfMaxFreqLabel, "Fltr HPF Max Freq");

    fltrHpfMinFreqEditor.setTooltip ("Fltr HPF Min Freq");
    fltrHpfMinFreqEditor.getMinValueCallback = [this] () { return 20; };
    fltrHpfMinFreqEditor.getMaxValueCallback = [this] () { return 20000; };
    fltrHpfMinFreqEditor.toStringCallback = [this] (int value) { return getRoundedFloatString (value, 4); };
    fltrHpfMinFreqEditor.updateDataCallback = [this] (int value) { fltrHpfMinFreqUiChanged (value); };
    fltrHpfMinFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFltrHpfMinFreq () + (multiplier * direction) };
        fltrHpfMinFreqEditor.setValue (newValue);
    };
    fltrHpfMinFreqEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fltrHpfMinFreqEditor, fltrHpfMinFreqLabel, "Fltr HPF Min Freq");

    fltrHpfQEditor.setTooltip ("Fltr HPF Q");
    fltrHpfQEditor.getMinValueCallback = [this] () { return 0.25; };
    fltrHpfQEditor.getMaxValueCallback = [this] () { return 4.0; };
    fltrHpfQEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fltrHpfQEditor.updateDataCallback = [this] (double value) { fltrHpfQUiChanged (static_cast<float> (value)); };
    fltrHpfQEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.001;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1;
            else
                return 1.0;
        } ();
        const auto newValue { settingsProperties.getFltrHpfQ () + (multiplier * direction) };
        fltrHpfQEditor.setValue (newValue);
    };
    fltrHpfQEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fltrHpfQEditor, fltrHpfQLabel, "Fltr HPF Q");

    fltrLpfMaxFreqEditor.setTooltip ("Fltr LPF Max Freq");
    fltrLpfMaxFreqEditor.getMinValueCallback = [this] () { return 20; };
    fltrLpfMaxFreqEditor.getMaxValueCallback = [this] () { return 20000; };
    fltrLpfMaxFreqEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fltrLpfMaxFreqEditor.updateDataCallback = [this] (int value) { fltrLpfMaxFreqUiChanged (value); };
    fltrLpfMaxFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFltrLpfMaxFreq () + (multiplier * direction) };
        fltrLpfMaxFreqEditor.setValue (newValue);
    };
    fltrLpfMaxFreqEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fltrLpfMaxFreqEditor, fltrLpfMaxFreqLabel, "Fltr LPF Max Freq");

    fltrLpfMinFreqEditor.setTooltip ("Fltr LPF Min Freq");
    fltrLpfMinFreqEditor.getMinValueCallback = [this] () { return 20; };
    fltrLpfMinFreqEditor.getMaxValueCallback = [this] () { return 20000; };
    fltrLpfMinFreqEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fltrLpfMinFreqEditor.updateDataCallback = [this] (int value) { fltrLpfMinFreqUiChanged (value); };
    fltrLpfMinFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFltrLpfMinFreq () + (multiplier * direction) };
        fltrLpfMinFreqEditor.setValue (newValue);
    };
    fltrLpfMinFreqEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fltrLpfMinFreqEditor, fltrLpfMinFreqLabel, "Fltr LPF Min Freq");

    fltrLpfQEditor.setTooltip ("Fltr LPF Q");
    fltrLpfQEditor.getMinValueCallback = [this] () { return 0.25; };
    fltrLpfQEditor.getMaxValueCallback = [this] () { return 4.0; };
    fltrLpfQEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fltrLpfQEditor.updateDataCallback = [this] (double value) { fltrLpfQUiChanged (static_cast<float> (value)); };
    fltrLpfQEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.001f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 1.0f;
        } ();
        const auto newValue { settingsProperties.getFltrLpfQ () + (multiplier * direction) };
        fltrLpfQEditor.setValue (newValue);
    };
    fltrLpfQEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (fltrLpfQEditor, fltrLpfQLabel, "Fltr LPF Q");

    fxChorusCenterEditor.setTooltip ("FX Chorus Center");
    fxChorusCenterEditor.getMinValueCallback = [this] () { return 1.0; };
    fxChorusCenterEditor.getMaxValueCallback = [this] () { return 20.0; };
    fxChorusCenterEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxChorusCenterEditor.updateDataCallback = [this] (double value) { fxChorusCenterUiChanged (static_cast<float> (value)); };
    fxChorusCenterEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1.0;
            else if (dragSpeed == DragSpeed::medium)
                return 3.0;
            else
                return 10.0;
        } ();
        const auto newValue { settingsProperties.getFxChorusCenter () + (multiplier * direction) };
        fxChorusCenterEditor.setValue (newValue);
    };
    fxChorusCenterEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxChorusCenterEditor, fxChorusCenterLabel, "FX Chorus Center");

    fxChorusDepthEditor.setTooltip ("FX Chorus Depth");
    fxChorusDepthEditor.getMinValueCallback = [this] () { return 1.0; };
    fxChorusDepthEditor.getMaxValueCallback = [this] () { return settingsProperties.getFxChorusCenter (); };
    fxChorusDepthEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxChorusDepthEditor.updateDataCallback = [this] (double value) { fxChorusDepthUiChanged (static_cast<float> (value)); };
    fxChorusDepthEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1.0;
            else if (dragSpeed == DragSpeed::medium)
                return 3.0;
            else
                return 10.0;
        } ();
        const auto newValue { settingsProperties.getFxChorusDepth () + (multiplier * direction) };
        fxChorusDepthEditor.setValue (newValue);
    };
    fxChorusDepthEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxChorusDepthEditor, fxChorusDepthLabel, "FX Chorus Depth");

    fxChorusLfoBEditor.setTooltip ("FX Chorus LFO B");
    fxChorusLfoBEditor.getMinValueCallback = [this] () { return 0.002; };
    fxChorusLfoBEditor.getMaxValueCallback = [this] () { return 3.0; };
    fxChorusLfoBEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxChorusLfoBEditor.updateDataCallback = [this] (double value) { fxChorusLfoBUiChanged (static_cast<float> (value)); };
    fxChorusLfoBEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.001f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 0.5f;
        } ();
        const auto newValue { settingsProperties.getFxChorusLfoB () + (multiplier * direction) };
        fxChorusLfoBEditor.setValue (newValue);
    };
    fxChorusLfoBEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (fxChorusLfoBEditor, fxChorusLfoBLabel, "FX Chorus LFO B");

    fxChorusLfoTEditor.setTooltip ("FX Chorus LFO T");
    fxChorusLfoTEditor.getMinValueCallback = [this] () { return 0.002; };
    fxChorusLfoTEditor.getMaxValueCallback = [this] () { return 3.0; };
    fxChorusLfoTEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxChorusLfoTEditor.updateDataCallback = [this] (double value) { fxChorusLfoTUiChanged (static_cast<float> (value)); };
    fxChorusLfoTEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.001f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 0.5f;
        } ();
        const auto newValue { settingsProperties.getFxChorusLfoT () + (multiplier * direction) };
        fxChorusLfoTEditor.setValue (newValue);
    };
    fxChorusLfoTEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxChorusLfoTEditor, fxChorusLfoTLabel, "FX Chorus LFO T");

    fxChorusMixEditor.setTooltip ("FX Chorus Mix");
    fxChorusMixEditor.getMinValueCallback = [this] () { return 0.1; };
    fxChorusMixEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusMixEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxChorusMixEditor.updateDataCallback = [this] (double value) { fxChorusMixUiChanged (static_cast<float> (value)); };
    fxChorusMixEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow || dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 0.3f;
        } ();
        const auto newValue { settingsProperties.getFxChorusMix () + (multiplier * direction) };
        fxChorusMixEditor.setValue (newValue);
    };
    fxChorusMixEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxChorusMixEditor, fxChorusMixLabel, "FX Chorus Mix");

    fxChorusSpreadEditor.setTooltip ("FX Chorus Spread");
    fxChorusSpreadEditor.getMinValueCallback = [this] () { return 0.01; };
    fxChorusSpreadEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusSpreadEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxChorusSpreadEditor.updateDataCallback = [this] (double value) { fxChorusSpreadUiChanged (static_cast<float> (value)); };
    fxChorusSpreadEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.01f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 0.3f;
        } ();
        const auto newValue { settingsProperties.getFxChorusSpread () + (multiplier * direction) };
        fxChorusSpreadEditor.setValue (newValue);
    };
    fxChorusSpreadEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxChorusSpreadEditor, fxChorusSpreadLabel, "FX Chorus Spread");

    // Integer # of Taps (1–4)
    fxChorusTapsComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    fxChorusTapsComboBox.setTooltip ("");
    fxChorusTapsComboBox.addItem ("1", 1);
    fxChorusTapsComboBox.addItem ("2", 2);
    fxChorusTapsComboBox.addItem ("3", 3);
    fxChorusTapsComboBox.addItem ("4", 4);
    fxChorusTapsComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto fxChorusTaps { fxChorusTapsComboBox.getSelectedId () };
        settingsProperties.setFxChorusTaps (std::clamp (fxChorusTaps + scrollAmount, 1, 4), true);
    };
    fxChorusTapsComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (fxChorusTapsComboBox, fxChorusTapsLabel, "FX Chorus Taps");

    // 0: -5 to 5V, 1: 0 to 5V 
    fxCvUnipolarComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    fxCvUnipolarComboBox.setTooltip ("");
    fxCvUnipolarComboBox.addItem ("-5v to 5v", 1);
    fxCvUnipolarComboBox.addItem ("0v to 5v", 2);
    fxCvUnipolarComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto fxCvUnipolar { fxCvUnipolarComboBox.getSelectedId () - 1 };
        settingsProperties.setFxCvUnipolar (std::clamp (fxCvUnipolar + scrollAmount, 0, 1), true);
    };
    fxCvUnipolarComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (fxCvUnipolarComboBox, fxCvUnipolarLabel, "FX CV Unipolar");

    fxDjfilterHpfMaxEditor.setTooltip ("FX DJ Filter HPF Max");
    fxDjfilterHpfMaxEditor.getMinValueCallback = [this] () { return 20; };
    fxDjfilterHpfMaxEditor.getMaxValueCallback = [this] () { return 20000; };
    fxDjfilterHpfMaxEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterHpfMaxEditor.updateDataCallback = [this] (int value) { fxDjfilterHpfMaxUiChanged (value); };
    fxDjfilterHpfMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterHpfMax () + (multiplier * direction) };
        fxDjfilterHpfMaxEditor.setValue (newValue);
    };
    fxDjfilterHpfMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxDjfilterHpfMaxEditor, fxDjfilterHpfMaxLabel, "FX DJ Filter HPF Max");

    fxDjfilterHpfMinEditor.setTooltip ("FX DJ Filter HPF Min");
    fxDjfilterHpfMinEditor.getMinValueCallback = [this] () { return 20; };
    fxDjfilterHpfMinEditor.getMaxValueCallback = [this] () { return 20000; };
    fxDjfilterHpfMinEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterHpfMinEditor.updateDataCallback = [this] (int value) { fxDjfilterHpfMinUiChanged (value); };
    fxDjfilterHpfMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterHpfMin () + (multiplier * direction) };
        fxDjfilterHpfMinEditor.setValue (newValue);
    };
    fxDjfilterHpfMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupIntEditor (fxDjfilterHpfMinEditor, fxDjfilterHpfMinLabel, "FX DJ Filter HPF Min");

    fxDjfilterLpfMaxEditor.setTooltip ("FX DJ Filter LPF Max");
    fxDjfilterLpfMaxEditor.getMinValueCallback = [this] () { return 20; };
    fxDjfilterLpfMaxEditor.getMaxValueCallback = [this] () { return 20000; };
    fxDjfilterLpfMaxEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterLpfMaxEditor.updateDataCallback = [this] (int value) { fxDjfilterLpfMaxUiChanged (value); };
    fxDjfilterLpfMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterLpfMax () + (multiplier * direction) };
        fxDjfilterLpfMaxEditor.setValue (newValue);
    };
    fxDjfilterLpfMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupIntEditor (fxDjfilterLpfMaxEditor, fxDjfilterLpfMaxLabel, "FX DJ Filter LPF Max");

    fxDjfilterLpfMinEditor.setTooltip ("FX DJ Filter LPF Min");
    fxDjfilterLpfMinEditor.getMinValueCallback = [this] () { return 20; };
    fxDjfilterLpfMinEditor.getMaxValueCallback = [this] () { return 20000; };
    fxDjfilterLpfMinEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterLpfMinEditor.updateDataCallback = [this] (int value) { fxDjfilterLpfMinUiChanged (value); };
    fxDjfilterLpfMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterLpfMin () + (multiplier * direction) };
        fxDjfilterLpfMinEditor.setValue (newValue);
    };
    fxDjfilterLpfMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxDjfilterLpfMinEditor, fxDjfilterLpfMinLabel, "FX DJ Filter LPF Min");

    fxDjfilterQGainReductionEditor.setTooltip ("FX DJ Filter Q Gain Reduction");
    fxDjfilterQGainReductionEditor.getMinValueCallback = [this] () { return 0.01; };
    fxDjfilterQGainReductionEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxDjfilterQGainReductionEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxDjfilterQGainReductionEditor.updateDataCallback = [this] (double value) { fxDjfilterQGainReductionUiChanged (static_cast<float> (value)); };
    fxDjfilterQGainReductionEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.01f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 0.3f;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterQGainReduction () + (multiplier * direction) };
        fxDjfilterQGainReductionEditor.setValue (newValue);
    };
    fxDjfilterQGainReductionEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxDjfilterQGainReductionEditor, fxDjfilterQGainReductionLabel, "FX DJ Filter Q Gain Reduction");

    fxDjfilterQMaxEditor.setTooltip ("FX DJ Filter Q Max");
    fxDjfilterQMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxDjfilterQMaxEditor.getMaxValueCallback = [this] () { return 20.0; };
    fxDjfilterQMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxDjfilterQMaxEditor.updateDataCallback = [this] (double value) { fxDjfilterQMaxUiChanged (static_cast<float> (value)); };
    fxDjfilterQMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 3.0f;
            else
                return 10.0f;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterQMax () + (multiplier * direction) };
        fxDjfilterQMaxEditor.setValue (newValue);
    };
    fxDjfilterQMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxDjfilterQMaxEditor, fxDjfilterQMaxLabel, "FX DJ Filter Q Max");

    fxDjfilterQMinEditor.setTooltip ("FX DJ Filter Q Min");
    fxDjfilterQMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxDjfilterQMinEditor.getMaxValueCallback = [this] () { return 20.0; };
    fxDjfilterQMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxDjfilterQMinEditor.updateDataCallback = [this] (double value) { fxDjfilterQMinUiChanged (static_cast<float> (value)); };
    fxDjfilterQMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 3.0f;
            else
                return 10.0f;
        } ();
        const auto newValue { settingsProperties.getFxDjfilterQMin () + (multiplier * direction) };
        fxDjfilterQMinEditor.setValue (newValue);
    };
    fxDjfilterQMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxDjfilterQMinEditor, fxDjfilterQMinLabel, "FX DJ Filter Q Min");

    fxDubEchoHpfEditor.setTooltip ("FX Dub Echo HPF");
    fxDubEchoHpfEditor.getMinValueCallback = [this] () { return 20; };
    fxDubEchoHpfEditor.getMaxValueCallback = [this] () { return 20000; };
    fxDubEchoHpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDubEchoHpfEditor.updateDataCallback = [this] (int value) { fxDubEchoHpfUiChanged (value); };
    fxDubEchoHpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFxDubEchoHpf () + (multiplier * direction) };
        fxDubEchoHpfEditor.setValue (newValue);
    };
    fxDubEchoHpfEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxDubEchoHpfEditor, fxDubEchoHpfLabel, "FX Dub Echo HPF");

    fxDubEchoLpfEditor.setTooltip ("FX Dub Echo LPF");
    fxDubEchoLpfEditor.getMinValueCallback = [this] () { return 20; };
    fxDubEchoLpfEditor.getMaxValueCallback = [this] () { return 20000; };
    fxDubEchoLpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDubEchoLpfEditor.updateDataCallback = [this] (int value) { fxDubEchoLpfUiChanged (value); };
    fxDubEchoLpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 25;
            else
                return 100;
        } ();
        const auto newValue { settingsProperties.getFxDubEchoLpf () + (multiplier * direction) };
        fxDubEchoLpfEditor.setValue (newValue);
    };
    fxDubEchoLpfEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxDubEchoLpfEditor, fxDubEchoLpfLabel, "FX Dub Echo LPF");

    fxDubEchoMixEditor.setTooltip ("FX Dub Echo Mix");
    fxDubEchoMixEditor.getMinValueCallback = [this] () { return 0.0; };
    fxDubEchoMixEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxDubEchoMixEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxDubEchoMixEditor.updateDataCallback = [this] (double value) { fxDubEchoMixUiChanged (static_cast<float> (value)); };
    fxDubEchoMixEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3f;
            else
                return 0.5f;
        } ();
        const auto newValue { settingsProperties.getFxDubEchoMix () + (multiplier * direction) };
        fxDubEchoMixEditor.setValue (newValue);
    };
    fxDubEchoMixEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxDubEchoMixEditor, fxDubEchoMixLabel, "FX Dub Echo Mix");

    fxDubEchoTminEditor.setTooltip ("FX Dub Echo Tmin");
    fxDubEchoTminEditor.getMinValueCallback = [this] () { return 0; };
    fxDubEchoTminEditor.getMaxValueCallback = [this] () { return 100; };
    fxDubEchoTminEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDubEchoTminEditor.updateDataCallback = [this] (int value) { fxDubEchoTminUiChanged (value); };
    fxDubEchoTminEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 10;
            else
                return 25;
        } ();
        const auto newValue { settingsProperties.getFxDubEchoTmin () + (multiplier * direction) };
        fxDubEchoTminEditor.setValue (newValue);
    };
    fxDubEchoTminEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupIntEditor (fxDubEchoTminEditor, fxDubEchoTminLabel, "FX Dub Echo Tmin");

    fxGlitchCrushTimeMaxEditor.setTooltip ("FX Glitch Crush Time Max");
    fxGlitchCrushTimeMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchCrushTimeMaxEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchCrushTimeMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchCrushTimeMaxEditor.updateDataCallback = [this] (double value) { fxGlitchCrushTimeMaxUiChanged (static_cast<float> (value)); };
    fxGlitchCrushTimeMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 5.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchCrushTimeMax () + (multiplier * direction) };
        fxGlitchCrushTimeMaxEditor.setValue (newValue);
    };
    fxGlitchCrushTimeMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchCrushTimeMaxEditor, fxGlitchCrushTimeMaxLabel, "FX Glitch Crush Time Max");

    fxGlitchCrushTimeMinEditor.setTooltip ("FX Glitch Crush Time Min");
    fxGlitchCrushTimeMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchCrushTimeMinEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchCrushTimeMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchCrushTimeMinEditor.updateDataCallback = [this] (double value) { fxGlitchCrushTimeMinUiChanged (static_cast<float> (value)); };
    fxGlitchCrushTimeMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 5.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchCrushTimeMin () + (multiplier * direction) };
        fxGlitchCrushTimeMinEditor.setValue (newValue);
    };
    fxGlitchCrushTimeMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchCrushTimeMinEditor, fxGlitchCrushTimeMinLabel, "FX Glitch Crush Time Min");

    fxGlitchDropKeepLevelMaxEditor.setTooltip ("FX Glitch Drop Keep Level Max");
    fxGlitchDropKeepLevelMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchDropKeepLevelMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchDropKeepLevelMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchDropKeepLevelMaxEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepLevelMaxUiChanged (static_cast<float> (value)); };
    fxGlitchDropKeepLevelMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchDropKeepLevelMax () + (multiplier * direction) };
        fxGlitchDropKeepLevelMaxEditor.setValue (newValue);
    };
    fxGlitchDropKeepLevelMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (fxGlitchDropKeepLevelMaxEditor, fxGlitchDropKeepLevelMaxLabel, "FX Glitch Drop Keep Level Max");

    fxGlitchDropKeepLevelMinEditor.setTooltip ("FX Glitch Drop Keep Level Min");
    fxGlitchDropKeepLevelMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchDropKeepLevelMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchDropKeepLevelMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchDropKeepLevelMinEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepLevelMinUiChanged (static_cast<float> (value)); };
    fxGlitchDropKeepLevelMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchDropKeepLevelMin () + (multiplier * direction) };
        fxGlitchDropKeepLevelMinEditor.setValue (newValue);
    };
    fxGlitchDropKeepLevelMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchDropKeepLevelMinEditor, fxGlitchDropKeepLevelMinLabel, "FX Glitch Drop Keep Level Min");

    fxGlitchDropKeepTimeMaxEditor.setTooltip ("FX Glitch Drop Keep Time Max");
    fxGlitchDropKeepTimeMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchDropKeepTimeMaxEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchDropKeepTimeMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchDropKeepTimeMaxEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepTimeMaxUiChanged (static_cast<float> (value)); };
    fxGlitchDropKeepTimeMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchDropKeepTimeMax () + (multiplier * direction) };
        fxGlitchDropKeepTimeMaxEditor.setValue (newValue);
    };
    fxGlitchDropKeepTimeMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (fxGlitchDropKeepTimeMaxEditor, fxGlitchDropKeepTimeMaxLabel, "FX Glitch Drop Keep Time Max");

    fxGlitchDropKeepTimeMinEditor.setTooltip ("FX Glitch Drop Keep Time Min");
    fxGlitchDropKeepTimeMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchDropKeepTimeMinEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchDropKeepTimeMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchDropKeepTimeMinEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepTimeMinUiChanged (static_cast<float> (value)); };
    fxGlitchDropKeepTimeMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchDropKeepTimeMin () + (multiplier * direction) };
        fxGlitchDropKeepTimeMinEditor.setValue (newValue);
    };
    fxGlitchDropKeepTimeMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchDropKeepTimeMinEditor, fxGlitchDropKeepTimeMinLabel, "FX Glitch Drop Keep Time Min");

    fxGlitchMicroloopPlayTMaxEditor.setTooltip ("FX Glitch Microloop Play T Max");
    fxGlitchMicroloopPlayTMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchMicroloopPlayTMaxEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchMicroloopPlayTMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchMicroloopPlayTMaxEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopPlayTMaxUiChanged (static_cast<float> (value)); };
    fxGlitchMicroloopPlayTMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchMicroloopPlayTMax () + (multiplier * direction) };
        fxGlitchMicroloopPlayTMaxEditor.setValue (newValue);
    };
    fxGlitchMicroloopPlayTMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchMicroloopPlayTMaxEditor, fxGlitchMicroloopPlayTMaxLabel, "FX Glitch Microloop Play T Max");

    fxGlitchMicroloopPlayTMinEditor.setTooltip ("FX Glitch Microloop Play T Min");
    fxGlitchMicroloopPlayTMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchMicroloopPlayTMinEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchMicroloopPlayTMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchMicroloopPlayTMinEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopPlayTMinUiChanged (static_cast<float> (value)); };
    fxGlitchMicroloopPlayTMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchMicroloopPlayTMin () + (multiplier * direction) };
        fxGlitchMicroloopPlayTMinEditor.setValue (newValue);
    };
    fxGlitchMicroloopPlayTMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchMicroloopPlayTMinEditor, fxGlitchMicroloopPlayTMinLabel, "FX Glitch Microloop Play T Min");

    fxGlitchMicroloopSmplTMaxEditor.setTooltip ("FX Glitch Microloop Smpl T Max");
    fxGlitchMicroloopSmplTMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchMicroloopSmplTMaxEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchMicroloopSmplTMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchMicroloopSmplTMaxEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopSmplTMaxUiChanged (static_cast<float> (value)); };
    fxGlitchMicroloopSmplTMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchMicroloopSmplTMax () + (multiplier * direction) };
        fxGlitchMicroloopSmplTMaxEditor.setValue (newValue);
    };
    fxGlitchMicroloopSmplTMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchMicroloopSmplTMaxEditor, fxGlitchMicroloopSmplTMaxLabel, "FX Glitch Microloop Smpl T Max");

    fxGlitchMicroloopSmplTMinEditor.setTooltip ("FX Glitch Microloop Smpl T Min");
    fxGlitchMicroloopSmplTMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchMicroloopSmplTMinEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchMicroloopSmplTMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchMicroloopSmplTMinEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopSmplTMinUiChanged (static_cast<float> (value)); };
    fxGlitchMicroloopSmplTMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchMicroloopSmplTMin () + (multiplier * direction) };
        fxGlitchMicroloopSmplTMinEditor.setValue (newValue);
    };
    fxGlitchMicroloopSmplTMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchMicroloopSmplTMinEditor, fxGlitchMicroloopSmplTMinLabel, "FX Glitch Microloop Smpl T Min");

    fxGlitchProbabilityMaxEditor.setTooltip ("FX Glitch Probability Max");
    fxGlitchProbabilityMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchProbabilityMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchProbabilityMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchProbabilityMaxEditor.updateDataCallback = [this] (double value) { fxGlitchProbabilityMaxUiChanged (static_cast<float> (value)); };
    fxGlitchProbabilityMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchProbabilityMax () + (multiplier * direction) };
        fxGlitchProbabilityMaxEditor.setValue (newValue);
    };
    fxGlitchProbabilityMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchProbabilityMaxEditor, fxGlitchProbabilityMaxLabel, "FX Glitch Probability Max");

    fxGlitchProbabilityMinEditor.setTooltip ("FX Glitch Probability Min");
    fxGlitchProbabilityMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchProbabilityMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchProbabilityMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchProbabilityMinEditor.updateDataCallback = [this] (double value) { fxGlitchProbabilityMinUiChanged (static_cast<float> (value)); };
    fxGlitchProbabilityMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchProbabilityMin () + (multiplier * direction) };
        fxGlitchProbabilityMinEditor.setValue (newValue);
    };
    fxGlitchProbabilityMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchProbabilityMinEditor, fxGlitchProbabilityMinLabel, "FX Glitch Probability Min");

    fxGlitchStutterNumMaxEditor.setTooltip ("FX Glitch Stutter Num Max");
    fxGlitchStutterNumMaxEditor.getMinValueCallback = [this] () { return 0; };
    fxGlitchStutterNumMaxEditor.getMaxValueCallback = [this] () { return 100; };
    fxGlitchStutterNumMaxEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxGlitchStutterNumMaxEditor.updateDataCallback = [this] (int value) { fxGlitchStutterNumMaxUiChanged (value); };
    fxGlitchStutterNumMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 10;
            else
                return 25;
        } ();
        const auto newValue { settingsProperties.getFxGlitchStutterNumMax () + (multiplier * direction) };
        fxGlitchStutterNumMaxEditor.setValue (newValue);
    };
    fxGlitchStutterNumMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxGlitchStutterNumMaxEditor, fxGlitchStutterNumMaxLabel, "FX Glitch Stutter Num Max");

    fxGlitchStutterNumMinEditor.setTooltip ("FX Glitch Stutter Num Min");
    fxGlitchStutterNumMinEditor.getMinValueCallback = [this] () { return 0; };
    fxGlitchStutterNumMinEditor.getMaxValueCallback = [this] () { return 100; };
    fxGlitchStutterNumMinEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxGlitchStutterNumMinEditor.updateDataCallback = [this] (int value) { fxGlitchStutterNumMinUiChanged (value); };
    fxGlitchStutterNumMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 10;
            else
                return 25;
        } ();
        const auto newValue { settingsProperties.getFxGlitchStutterNumMin () + (multiplier * direction) };
        fxGlitchStutterNumMinEditor.setValue (newValue);
    };
    fxGlitchStutterNumMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxGlitchStutterNumMinEditor, fxGlitchStutterNumMinLabel, "FX Glitch Stutter Num Min");

    fxGlitchStutterSmplTMaxEditor.setTooltip ("FX Glitch Stutter Smpl T Max");
    fxGlitchStutterSmplTMaxEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchStutterSmplTMaxEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchStutterSmplTMaxEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchStutterSmplTMaxEditor.updateDataCallback = [this] (double value) { fxGlitchStutterSmplTMaxUiChanged (static_cast<float> (value)); };
    fxGlitchStutterSmplTMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchStutterSmplTMax () + (multiplier * direction) };
        fxGlitchStutterSmplTMaxEditor.setValue (newValue);
    };
    fxGlitchStutterSmplTMaxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchStutterSmplTMaxEditor, fxGlitchStutterSmplTMaxLabel, "FX Glitch Stutter Smpl T Max");

    fxGlitchStutterSmplTMinEditor.setTooltip ("FX Glitch Stutter Smpl T Min");
    fxGlitchStutterSmplTMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchStutterSmplTMinEditor.getMaxValueCallback = [this] () { return 100.0; };
    fxGlitchStutterSmplTMinEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchStutterSmplTMinEditor.updateDataCallback = [this] (double value) { fxGlitchStutterSmplTMinUiChanged (static_cast<float> (value)); };
    fxGlitchStutterSmplTMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 10.0;
            else
                return 25.0;
        } ();
        const auto newValue { settingsProperties.getFxGlitchStutterSmplTMin () + (multiplier * direction) };
        fxGlitchStutterSmplTMinEditor.setValue (newValue);
    };
    fxGlitchStutterSmplTMinEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchStutterSmplTMinEditor, fxGlitchStutterSmplTMinLabel, "FX Glitch Stutter Smpl T Min");

    fxGlitchStutterWindowEditor.setTooltip ("FX Glitch Stutter Window");
    fxGlitchStutterWindowEditor.getMinValueCallback = [this] () { return 0; };
    fxGlitchStutterWindowEditor.getMaxValueCallback = [this] () { return 100; };
    fxGlitchStutterWindowEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxGlitchStutterWindowEditor.updateDataCallback = [this] (int value) { fxGlitchStutterWindowUiChanged (value); };
    fxGlitchStutterWindowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 10;
            else
                return 25;
        } ();
        const auto newValue { settingsProperties.getFxGlitchStutterWindow () + (multiplier * direction) };
        fxGlitchStutterWindowEditor.setValue (newValue);
    };
    fxGlitchStutterWindowEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxGlitchStutterWindowEditor, fxGlitchStutterWindowLabel, "FX Glitch Stutter Window");

    fxGlitchWeightCrushLowEditor.setTooltip ("FX Glitch Weight Crush Low");
    fxGlitchWeightCrushLowEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightCrushLowEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightCrushLowEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightCrushLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightCrushLowUiChanged (static_cast<float> (value)); };
    fxGlitchWeightCrushLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightCrushLow () + (multiplier * direction) };
        fxGlitchWeightCrushLowEditor.setValue (newValue);
    };
    fxGlitchWeightCrushLowEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightCrushLowEditor, fxGlitchWeightCrushLowLabel, "FX Glitch Weight Crush Low");

    fxGlitchWeightDropHighEditor.setTooltip ("FX Glitch Weight Drop High");
    fxGlitchWeightDropHighEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightDropHighEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightDropHighEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightDropHighEditor.updateDataCallback = [this] (double value) { fxGlitchWeightDropHighUiChanged (static_cast<float> (value)); };
    fxGlitchWeightDropHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightDropHigh () + (multiplier * direction) };
        fxGlitchWeightDropHighEditor.setValue (newValue);
    };
    fxGlitchWeightDropHighEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightDropHighEditor, fxGlitchWeightDropHighLabel, "FX Glitch Weight Drop High");

    fxGlitchWeightDropLowEditor.setTooltip ("FX Glitch Weight Drop Low");
    fxGlitchWeightDropLowEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightDropLowEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightDropLowEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightDropLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightDropLowUiChanged (static_cast<float> (value)); };
    fxGlitchWeightDropLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightDropLow () + (multiplier * direction) };
        fxGlitchWeightDropLowEditor.setValue (newValue);
    };
    fxGlitchWeightDropLowEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightDropLowEditor, fxGlitchWeightDropLowLabel, "FX Glitch Weight Drop Low");

    fxGlitchWeightHoldHighEditor.setTooltip ("FX Glitch Weight Hold High");
    fxGlitchWeightHoldHighEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightHoldHighEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightHoldHighEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightHoldHighEditor.updateDataCallback = [this] (double value) { fxGlitchWeightHoldHighUiChanged (static_cast<float> (value)); };
    fxGlitchWeightHoldHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightHoldHigh () + (multiplier * direction) };
        fxGlitchWeightHoldHighEditor.setValue (newValue);
    };
    fxGlitchWeightHoldHighEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightHoldHighEditor, fxGlitchWeightHoldHighLabel, "FX Glitch Weight Hold High");

    fxGlitchWeightHoldLowEditor.setTooltip ("FX Glitch Weight Hold Low");
    fxGlitchWeightHoldLowEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightHoldLowEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightHoldLowEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightHoldLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightHoldLowUiChanged (static_cast<float> (value)); };
    fxGlitchWeightHoldLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightHoldLow () + (multiplier * direction) };
        fxGlitchWeightHoldLowEditor.setValue (newValue);
    };
    fxGlitchWeightHoldLowEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightHoldLowEditor, fxGlitchWeightHoldLowLabel, "FX Glitch Weight Hold Low");

    fxGlitchWeightStutterHighEditor.setTooltip ("FX Glitch Weight Stutter High");
    fxGlitchWeightStutterHighEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightStutterHighEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightStutterHighEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightStutterHighEditor.updateDataCallback = [this] (double value) { fxGlitchWeightStutterHighUiChanged (static_cast<float> (value)); };
    fxGlitchWeightStutterHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightStutterHigh () + (multiplier * direction) };
        fxGlitchWeightStutterHighEditor.setValue (newValue);
    };
    fxGlitchWeightStutterHighEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightStutterHighEditor, fxGlitchWeightStutterHighLabel, "FX Glitch Weight Stutter High");

    fxGlitchWeightStutterLowEditor.setTooltip ("FX Glitch Weight Stutter Low");
    fxGlitchWeightStutterLowEditor.getMinValueCallback = [this] () { return 0.0; };
    fxGlitchWeightStutterLowEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchWeightStutterLowEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    fxGlitchWeightStutterLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightStutterLowUiChanged (static_cast<float> (value)); };
    fxGlitchWeightStutterLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getFxGlitchWeightStutterLow () + (multiplier * direction) };
        fxGlitchWeightStutterLowEditor.setValue (newValue);
    };
    fxGlitchWeightStutterLowEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxGlitchWeightStutterLowEditor, fxGlitchWeightStutterLowLabel, "FX Glitch Weight Stutter Low");

    fxReverbHpfEditor.setTooltip ("FX Reverb HPF");
    fxReverbHpfEditor.getMinValueCallback = [this] () { return 20; };
    fxReverbHpfEditor.getMaxValueCallback = [this] () { return 20000; };
    fxReverbHpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxReverbHpfEditor.updateDataCallback = [this] (int value) { fxReverbHpfUiChanged (value); };
    fxReverbHpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 10;
            else
                return 25;
        } ();
        const auto newValue { settingsProperties.getFxReverbHpf () + (multiplier * direction) };
        fxReverbHpfEditor.setValue (newValue);
    };
    fxReverbHpfEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupIntEditor (fxReverbHpfEditor, fxReverbHpfLabel, "FX Reverb HPF");

    fxReverbLpfEditor.setTooltip ("FX Reverb LPF");
    fxReverbLpfEditor.getMinValueCallback = [this] () { return 20; };
    fxReverbLpfEditor.getMaxValueCallback = [this] () { return 20000; };
    fxReverbLpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxReverbLpfEditor.updateDataCallback = [this] (int value) { fxReverbLpfUiChanged (value); };
    fxReverbLpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 1;
            else if (dragSpeed == DragSpeed::medium)
                return 10;
            else
                return 25;
        } ();
        const auto newValue { settingsProperties.getFxReverbLpf () + (multiplier * direction) };
        fxReverbLpfEditor.setValue (newValue);
    };
    fxReverbLpfEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxReverbLpfEditor, fxReverbLpfLabel, "FX Reverb LPF");

    // 0: 0V = 100 % -5 = 0 % +5 = 200 %
    // 1: 0V = 10 % +5 = 100 %
    gateModeComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    gateModeComboBox.setTooltip ("");
    gateModeComboBox.addItem ("Immediate", 1);
    gateModeComboBox.addItem ("After Gate Falls", 2);
    gateModeComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto gateMode { gateModeComboBox.getSelectedId () - 1 };
        settingsProperties.setGateMode (std::clamp (gateMode + scrollAmount, 0, 1), true);
    };
    gateModeComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (gateModeComboBox, gateModeLabel, "Gate Mode");

    // 0 to sense small movement (wiggle)
    // 1 to require passing old value
    knobPosTakeupComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    knobPosTakeupComboBox.setTooltip ("");
    knobPosTakeupComboBox.addItem ("Small Movement", 1);
    knobPosTakeupComboBox.addItem ("Pass Old Value", 2);
    knobPosTakeupComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto fxCvUnipolar { knobPosTakeupComboBox.getSelectedId () - 1 };
        settingsProperties.setKnobPosTakeup (std::clamp (fxCvUnipolar + scrollAmount, 0, 1), true);
    };
    knobPosTakeupComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (knobPosTakeupComboBox, knobPosTakeupLabel, "Knob Pos Takeup");

    pitchHighEditor.setTooltip ("Pitch High");
    pitchHighEditor.getMinValueCallback = [this] () { return 1.5; };
    pitchHighEditor.getMaxValueCallback = [this] () { return 3.7; };
    pitchHighEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    pitchHighEditor.updateDataCallback = [this] (double value) { pitchHighUiChanged (static_cast<float> (value)); };
    pitchHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.1;
            else if (dragSpeed == DragSpeed::medium)
                return 0.3;
            else
                return 0.5;
        } ();
        const auto newValue { settingsProperties.getPitchHigh () + (multiplier * direction) };
        pitchHighEditor.setValue (newValue);
    };
    pitchHighEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (pitchHighEditor, pitchHighLabel, "Pitch High");

    pitchLowEditor.setTooltip ("Pitch Low");
    pitchLowEditor.getMinValueCallback = [this] () { return 0.001; };
    pitchLowEditor.getMaxValueCallback = [this] () { return 0.5; };
    pitchLowEditor.toStringCallback = [this] (double value) { return getRoundedFloatString (value, 4); };
    pitchLowEditor.updateDataCallback = [this] (double value) { pitchLowUiChanged (static_cast<float> (value)); };
    pitchLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.001;
            else if (dragSpeed == DragSpeed::medium)
                return 0.01;
            else
                return 0.1;
        } ();
        const auto newValue { settingsProperties.getPitchLow () + (multiplier * direction) };
        pitchLowEditor.setValue (newValue);
    };
    pitchLowEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (pitchLowEditor, pitchLowLabel, "Pitch Low");

    // 0: 0V = 100 % -5 = 0 % +5 = 200 %
    // 1: 0V = 10 % +5 = 100 %
    velocityUnipolarComboBox.setLookAndFeel (&noArrowComboBoxLnF);
    velocityUnipolarComboBox.setTooltip ("");
    velocityUnipolarComboBox.addItem ("0%-100%-200%", 1);
    velocityUnipolarComboBox.addItem ("0%-100%", 2);
    velocityUnipolarComboBox.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto velocityUnipolar { velocityUnipolarComboBox.getSelectedId () - 1 };
        settingsProperties.setVelocityUnipolar (std::clamp (velocityUnipolar + scrollAmount, 0, 1), true);
    };
    velocityUnipolarComboBox.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (velocityUnipolarComboBox, velocityUnipolarLabel, "Velocity Unipolar");
}

SettingsEditorComponent::~SettingsEditorComponent ()
{
}

void SettingsEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    settingsProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("HiHat"), ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::yes);

    // initialize fields when data first attached
    pitchLowDataChanged (settingsProperties.getPitchLow ());
    pitchHighDataChanged (settingsProperties.getPitchHigh ());
    envelopeMaxReleaseDataChanged (settingsProperties.getEnvelopeMaxRelease ());
    chokeReleaseDataChanged (settingsProperties.getChokeRelease ());
    clsdReleaseModeDataChanged (settingsProperties.getClsdReleaseMode ());
    clsdRelOfstScaleDataChanged (settingsProperties.getClsdRelOfstScale ());
    clsdMaxReleaseDataChanged (settingsProperties.getClsdMaxRelease ());
    accClRelModDataChanged (settingsProperties.getAccClRelMod ());
    accOpRelModDataChanged (settingsProperties.getAccOpRelMod ());
    accClAmpModDataChanged (settingsProperties.getAccClAmpMod ());
    accOpAmpModDataChanged (settingsProperties.getAccOpAmpMod ());
    fxCvUnipolarDataChanged (settingsProperties.getFxCvUnipolar ());
    velocityUnipolarDataChanged (settingsProperties.getVelocityUnipolar ());
    cvDisableVelocityDataChanged (settingsProperties.getCvDisableVelocity ());
    cvDisableFxDataChanged (settingsProperties.getCvDisableFx ());
    gateModeDataChanged (settingsProperties.getGateMode ());
    feelAttackModDataChanged (settingsProperties.getFeelAttackMod ());
    feelReleaseModDataChanged (settingsProperties.getFeelReleaseMod ());
    feelAmpModDataChanged (settingsProperties.getFeelAmpMod ());
    knobPosTakeupDataChanged (settingsProperties.getKnobPosTakeup ());
    fltrHpfMinFreqDataChanged (settingsProperties.getFltrHpfMinFreq ());
    fltrHpfMaxFreqDataChanged (settingsProperties.getFltrHpfMaxFreq ());
    fltrLpfMinFreqDataChanged (settingsProperties.getFltrLpfMinFreq ());
    fltrLpfMaxFreqDataChanged (settingsProperties.getFltrLpfMaxFreq ());
    fltrHpfQDataChanged (settingsProperties.getFltrHpfQ ());
    fltrLpfQDataChanged (settingsProperties.getFltrLpfQ ());
    fxDjfilterHpfMinDataChanged (settingsProperties.getFxDjfilterHpfMin ());
    fxDjfilterHpfMaxDataChanged (settingsProperties.getFxDjfilterHpfMax ());
    fxDjfilterLpfMinDataChanged (settingsProperties.getFxDjfilterLpfMin ());
    fxDjfilterLpfMaxDataChanged (settingsProperties.getFxDjfilterLpfMax ());
    fxDjfilterQMinDataChanged (settingsProperties.getFxDjfilterQMin ());
    fxDjfilterQMaxDataChanged (settingsProperties.getFxDjfilterQMax ());
    fxDjfilterQGainReductionDataChanged (settingsProperties.getFxDjfilterQGainReduction ());
    fxDubEchoTminDataChanged (settingsProperties.getFxDubEchoTmin ());
    fxDubEchoHpfDataChanged (settingsProperties.getFxDubEchoHpf ());
    fxDubEchoLpfDataChanged (settingsProperties.getFxDubEchoLpf ());
    fxDubEchoMixDataChanged (settingsProperties.getFxDubEchoMix ());
    fxChorusCenterDataChanged (settingsProperties.getFxChorusCenter ());
    fxChorusDepthDataChanged (settingsProperties.getFxChorusDepth ());
    fxChorusMixDataChanged (settingsProperties.getFxChorusMix ());
    fxChorusSpreadDataChanged (settingsProperties.getFxChorusSpread ());
    fxChorusTapsDataChanged (settingsProperties.getFxChorusTaps ());
    fxChorusLfoBDataChanged (settingsProperties.getFxChorusLfoB ());
    fxChorusLfoTDataChanged (settingsProperties.getFxChorusLfoT ());
    fxReverbLpfDataChanged (settingsProperties.getFxReverbLpf ());
    fxReverbHpfDataChanged (settingsProperties.getFxReverbHpf ());
    fxGlitchProbabilityMinDataChanged (settingsProperties.getFxGlitchProbabilityMin ());
    fxGlitchProbabilityMaxDataChanged (settingsProperties.getFxGlitchProbabilityMax ());
    fxGlitchWeightHoldLowDataChanged (settingsProperties.getFxGlitchWeightHoldLow ());
    fxGlitchWeightStutterLowDataChanged (settingsProperties.getFxGlitchWeightStutterLow ());
    fxGlitchWeightCrushLowDataChanged (settingsProperties.getFxGlitchWeightCrushLow ());
    fxGlitchWeightDropLowDataChanged (settingsProperties.getFxGlitchWeightDropLow ());
    fxGlitchWeightHoldHighDataChanged (settingsProperties.getFxGlitchWeightHoldHigh ());
    fxGlitchWeightStutterHighDataChanged (settingsProperties.getFxGlitchWeightStutterHigh ());
    fxGlitchWeightCrushHighDataChanged (settingsProperties.getFxGlitchWeightCrushHigh ());
    fxGlitchWeightDropHighDataChanged (settingsProperties.getFxGlitchWeightDropHigh ());
    fxGlitchDropKeepLevelMinDataChanged (settingsProperties.getFxGlitchDropKeepLevelMin ());
    fxGlitchDropKeepLevelMaxDataChanged (settingsProperties.getFxGlitchDropKeepLevelMax ());
    fxGlitchDropKeepTimeMinDataChanged (settingsProperties.getFxGlitchDropKeepTimeMin ());
    fxGlitchDropKeepTimeMaxDataChanged (settingsProperties.getFxGlitchDropKeepTimeMax ());
    fxGlitchCrushTimeMinDataChanged (settingsProperties.getFxGlitchCrushTimeMin ());
    fxGlitchCrushTimeMaxDataChanged (settingsProperties.getFxGlitchCrushTimeMax ());
    fxGlitchMicroloopSmplTMinDataChanged (settingsProperties.getFxGlitchMicroloopSmplTMin ());
    fxGlitchMicroloopSmplTMaxDataChanged (settingsProperties.getFxGlitchMicroloopSmplTMax ());
    fxGlitchMicroloopPlayTMinDataChanged (settingsProperties.getFxGlitchMicroloopPlayTMin ());
    fxGlitchMicroloopPlayTMaxDataChanged (settingsProperties.getFxGlitchMicroloopPlayTMax ());
    fxGlitchStutterSmplTMinDataChanged (settingsProperties.getFxGlitchStutterSmplTMin ());
    fxGlitchStutterSmplTMaxDataChanged (settingsProperties.getFxGlitchStutterSmplTMax ());
    fxGlitchStutterNumMinDataChanged (settingsProperties.getFxGlitchStutterNumMin ());
    fxGlitchStutterNumMaxDataChanged (settingsProperties.getFxGlitchStutterNumMax ());
    fxGlitchStutterWindowDataChanged (settingsProperties.getFxGlitchStutterWindow ());

    initializeCallbacks ();
}

void SettingsEditorComponent::initializeCallbacks ()
{
    jassert (settingsProperties.isValid ());
    settingsProperties.onPitchLowChange = [this] (float value) { pitchLowDataChanged (value); };
    settingsProperties.onPitchHighChange = [this] (float value) { pitchHighDataChanged (value); };
    settingsProperties.onEnvelopeMaxReleaseChange = [this] (float value) { envelopeMaxReleaseDataChanged (value); };
    settingsProperties.onChokeReleaseChange = [this] (float value) { chokeReleaseDataChanged (value); };
    settingsProperties.onClsdReleaseModeChange = [this] (int value) { clsdReleaseModeDataChanged (value); };
    settingsProperties.onClsdRelOfstScaleChange = [this] (float value) { clsdRelOfstScaleDataChanged (value); };
    settingsProperties.onClsdMaxReleaseChange = [this] (float value) { clsdMaxReleaseDataChanged (value); };
    settingsProperties.onAccClRelModChange = [this] (float value) { accClRelModDataChanged (value); };
    settingsProperties.onAccOpRelModChange = [this] (float value) { accOpRelModDataChanged (value); };
    settingsProperties.onAccClAmpModChange = [this] (float value) { accClAmpModDataChanged (value); };
    settingsProperties.onAccOpAmpModChange = [this] (float value) { accOpAmpModDataChanged (value); };
    settingsProperties.onFeelAttackModChange = [this] (float value) { feelAttackModDataChanged (value); };
    settingsProperties.onFeelReleaseModChange = [this] (float value) { feelReleaseModDataChanged (value); };
    settingsProperties.onFeelAmpModChange = [this] (float value) { feelAmpModDataChanged (value); };
    settingsProperties.onFxCvUnipolarChange = [this] (int value) { fxCvUnipolarDataChanged (value); };
    settingsProperties.onVelocityUnipolarChange = [this] (int value) { velocityUnipolarDataChanged (value); };
    settingsProperties.onCvDisableVelocityChange = [this] (int value) { cvDisableVelocityDataChanged (value); };
    settingsProperties.onCvDisableFxChange = [this] (int value) { cvDisableFxDataChanged (value); };
    settingsProperties.onGateModeChange = [this] (int value) { gateModeDataChanged (value); };
    settingsProperties.onKnobPosTakeupChange = [this] (int value) { knobPosTakeupDataChanged (value); };
    settingsProperties.onFltrHpfMinFreqChange = [this] (int value) { fltrHpfMinFreqDataChanged (value); };
    settingsProperties.onFltrHpfMaxFreqChange = [this] (int value) { fltrHpfMaxFreqDataChanged (value); };
    settingsProperties.onFltrLpfMinFreqChange = [this] (int value) { fltrLpfMinFreqDataChanged (value); };
    settingsProperties.onFltrLpfMaxFreqChange = [this] (int value) { fltrLpfMaxFreqDataChanged (value); };
    settingsProperties.onFltrHpfQChange = [this] (float value) { fltrHpfQDataChanged (value); };
    settingsProperties.onFltrLpfQChange = [this] (float value) { fltrLpfQDataChanged (value); };
    settingsProperties.onFxDjfilterHpfMinChange = [this] (int value) { fxDjfilterHpfMinDataChanged (value); };
    settingsProperties.onFxDjfilterHpfMaxChange = [this] (int value) { fxDjfilterHpfMaxDataChanged (value); };
    settingsProperties.onFxDjfilterLpfMinChange = [this] (int value) { fxDjfilterLpfMinDataChanged (value); };
    settingsProperties.onFxDjfilterLpfMaxChange = [this] (int value) { fxDjfilterLpfMaxDataChanged (value); };
    settingsProperties.onFxDjfilterQMinChange = [this] (float value) { fxDjfilterQMinDataChanged (value); };
    settingsProperties.onFxDjfilterQMaxChange = [this] (float value) { fxDjfilterQMaxDataChanged (value); };
    settingsProperties.onFxDjfilterQGainReductionChange = [this] (float value) { fxDjfilterQGainReductionDataChanged (value); };
    settingsProperties.onFxDubEchoTminChange = [this] (int value) { fxDubEchoTminDataChanged (value); };
    settingsProperties.onFxDubEchoHpfChange = [this] (int value) { fxDubEchoHpfDataChanged (value); };
    settingsProperties.onFxDubEchoLpfChange = [this] (int value) { fxDubEchoLpfDataChanged (value); };
    settingsProperties.onFxDubEchoMixChange = [this] (float value) { fxDubEchoMixDataChanged (value); };
    settingsProperties.onFxChorusCenterChange = [this] (float value) { fxChorusCenterDataChanged (value); };
    settingsProperties.onFxChorusDepthChange = [this] (float value) { fxChorusDepthDataChanged (value); };
    settingsProperties.onFxChorusMixChange = [this] (float value) { fxChorusMixDataChanged (value); };
    settingsProperties.onFxChorusSpreadChange = [this] (float value) { fxChorusSpreadDataChanged (value); };
    settingsProperties.onFxChorusTapsChange = [this] (int value) { fxChorusTapsDataChanged (value); };
    settingsProperties.onFxChorusLfoBChange = [this] (float value) { fxChorusLfoBDataChanged (value); };
    settingsProperties.onFxChorusLfoTChange = [this] (float value) { fxChorusLfoTDataChanged (value); };
    settingsProperties.onFxReverbLpfChange = [this] (int value) { fxReverbLpfDataChanged (value); };
    settingsProperties.onFxReverbHpfChange = [this] (int value) { fxReverbHpfDataChanged (value); };
    settingsProperties.onFxGlitchProbabilityMinChange = [this] (float value) { fxGlitchProbabilityMinDataChanged (value); };
    settingsProperties.onFxGlitchProbabilityMaxChange = [this] (float value) { fxGlitchProbabilityMaxDataChanged (value); };
    settingsProperties.onFxGlitchWeightHoldLowChange = [this] (float value) { fxGlitchWeightHoldLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightStutterLowChange = [this] (float value) { fxGlitchWeightStutterLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightCrushLowChange = [this] (float value) { fxGlitchWeightCrushLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightDropLowChange = [this] (float value) { fxGlitchWeightDropLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightHoldHighChange = [this] (float value) { fxGlitchWeightHoldHighDataChanged (value); };
    settingsProperties.onFxGlitchWeightStutterHighChange = [this] (float value) { fxGlitchWeightStutterHighDataChanged (value); };
    settingsProperties.onFxGlitchWeightCrushHighChange = [this] (float value) { fxGlitchWeightCrushHighDataChanged (value); };
    settingsProperties.onFxGlitchWeightDropHighChange = [this] (float value) { fxGlitchWeightDropHighDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepLevelMinChange = [this] (float value) { fxGlitchDropKeepLevelMinDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepLevelMaxChange = [this] (float value) { fxGlitchDropKeepLevelMaxDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepTimeMinChange = [this] (float value) { fxGlitchDropKeepTimeMinDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepTimeMaxChange = [this] (float value) { fxGlitchDropKeepTimeMaxDataChanged (value); };
    settingsProperties.onFxGlitchCrushTimeMinChange = [this] (float value) { fxGlitchCrushTimeMinDataChanged (value); };
    settingsProperties.onFxGlitchCrushTimeMaxChange = [this] (float value) { fxGlitchCrushTimeMaxDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopSmplTMinChange = [this] (float value) { fxGlitchMicroloopSmplTMinDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopSmplTMaxChange = [this] (float value) { fxGlitchMicroloopSmplTMaxDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopPlayTMinChange = [this] (float value) { fxGlitchMicroloopPlayTMinDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopPlayTMaxChange = [this] (float value) { fxGlitchMicroloopPlayTMaxDataChanged (value); };
    settingsProperties.onFxGlitchStutterSmplTMinChange = [this] (float value) { fxGlitchStutterSmplTMinDataChanged (value); };
    settingsProperties.onFxGlitchStutterSmplTMaxChange = [this] (float value) { fxGlitchStutterSmplTMaxDataChanged (value); };
    settingsProperties.onFxGlitchStutterNumMinChange = [this] (int value) { fxGlitchStutterNumMinDataChanged (value); };
    settingsProperties.onFxGlitchStutterNumMaxChange = [this] (int value) { fxGlitchStutterNumMaxDataChanged (value); };
    settingsProperties.onFxGlitchStutterWindowChange = [this] (int value) { fxGlitchStutterWindowDataChanged (value); };
}

void SettingsEditorComponent::pitchLowDataChanged (float value)
{
    pitchLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::pitchLowUiChanged (float value)
{
    settingsProperties.setPitchLow (value, false);
}

void SettingsEditorComponent::pitchHighDataChanged (float value)
{
    pitchHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::pitchHighUiChanged (float value)
{
    settingsProperties.setPitchHigh (value, false);
}

void SettingsEditorComponent::envelopeMaxReleaseDataChanged (float value)
{
    envelopeMaxReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::envelopeMaxReleaseUiChanged (float value)
{
    settingsProperties.setEnvelopeMaxRelease (value, false);
}

void SettingsEditorComponent::chokeReleaseDataChanged (float value)
{
    chokeReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::chokeReleaseUiChanged (float value)
{
    settingsProperties.setChokeRelease (value, false);
}

void SettingsEditorComponent::clsdReleaseModeDataChanged (int value)
{
    clsdReleaseModeComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::clsdReleaseModeUiChanged (int value)
{
    settingsProperties.setClsdReleaseMode (value, false);
}

void SettingsEditorComponent::clsdRelOfstScaleDataChanged (float value)
{
    clsdRelOfstScaleEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::clsdRelOfstScaleUiChanged (float value)
{
    settingsProperties.setClsdRelOfstScale (value, false);
}

void SettingsEditorComponent::clsdMaxReleaseDataChanged (float value)
{
    clsdMaxReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::clsdMaxReleaseUiChanged (float value)
{
    settingsProperties.setClsdMaxRelease (value, false);
}

void SettingsEditorComponent::accClRelModDataChanged (float value)
{
    accClRelModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accClRelModUiChanged (float value)
{
    settingsProperties.setAccClRelMod (value, false);
}

void SettingsEditorComponent::accOpRelModDataChanged (float value)
{
    accOpRelModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accOpRelModUiChanged (float value)
{
    settingsProperties.setAccOpRelMod (value, false);
}

void SettingsEditorComponent::accClAmpModDataChanged (float value)
{
    accClAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accClAmpModUiChanged (float value)
{
    settingsProperties.setAccClAmpMod (value, false);
}

void SettingsEditorComponent::accOpAmpModDataChanged (float value)
{
    accOpAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accOpAmpModUiChanged (float value)
{
    settingsProperties.setAccOpAmpMod (value, false);
}

void SettingsEditorComponent::feelAttackModDataChanged (float value)
{
    feelAttackModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::feelAttackModUiChanged (float value)
{
    settingsProperties.setFeelAttackMod (value, false);
}

void SettingsEditorComponent::feelReleaseModDataChanged (float value)
{
    feelReleaseModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::feelReleaseModUiChanged (float value)
{
    settingsProperties.setFeelReleaseMod (value, false);
}

void SettingsEditorComponent::feelAmpModDataChanged (float value)
{
    feelAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::feelAmpModUiChanged (float value)
{
    settingsProperties.setFeelAmpMod (value, false);
}

void SettingsEditorComponent::fxCvUnipolarDataChanged (int value)
{
    fxCvUnipolarComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::fxCvUnipolarUiChanged (int value)
{
    settingsProperties.setFxCvUnipolar (value, false);
}

void SettingsEditorComponent::velocityUnipolarDataChanged (int value)
{
    velocityUnipolarComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::velocityUnipolarUiChanged (int value)
{
    settingsProperties.setVelocityUnipolar (value, false);
}

void SettingsEditorComponent::cvDisableVelocityDataChanged (int value)
{
    cvDisableVelocityComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::cvDisableVelocityUiChanged (int value)
{
    settingsProperties.setCvDisableVelocity (value, false);
}

void SettingsEditorComponent::cvDisableFxDataChanged (int value)
{
    cvDisableFxComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::cvDisableFxUiChanged (int value)
{
    settingsProperties.setCvDisableFx (value, false);
}

void SettingsEditorComponent::gateModeDataChanged (int value)
{
    gateModeComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::gateModeUiChanged (int value)
{
    settingsProperties.setGateMode (value, false);
}

void SettingsEditorComponent::knobPosTakeupDataChanged (int value)
{
    knobPosTakeupComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::knobPosTakeupUiChanged (int value)
{
    settingsProperties.setKnobPosTakeup (value, false);
}

void SettingsEditorComponent::fltrHpfMinFreqDataChanged (int value)
{
    fltrHpfMinFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrHpfMinFreqUiChanged (int value)
{
    settingsProperties.setFltrHpfMinFreq (value, false);
}

void SettingsEditorComponent::fltrHpfMaxFreqDataChanged (int value)
{
    fltrHpfMaxFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrHpfMaxFreqUiChanged (int value)
{
    settingsProperties.setFltrHpfMaxFreq (value, false);
}

void SettingsEditorComponent::fltrLpfMinFreqDataChanged (int value)
{
    fltrLpfMinFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrLpfMinFreqUiChanged (int value)
{
    settingsProperties.setFltrLpfMinFreq (value, false);
}

void SettingsEditorComponent::fltrLpfMaxFreqDataChanged (int value)
{
    fltrLpfMaxFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrLpfMaxFreqUiChanged (int value)
{
    settingsProperties.setFltrLpfMaxFreq (value, false);
}

void SettingsEditorComponent::fltrHpfQDataChanged (float value)
{
    fltrHpfQEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrHpfQUiChanged (float value)
{
    settingsProperties.setFltrHpfQ (value, false);
}

void SettingsEditorComponent::fltrLpfQDataChanged (float value)
{
    fltrLpfQEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrLpfQUiChanged (float value)
{
    settingsProperties.setFltrLpfQ (value, false);
}

void SettingsEditorComponent::fxDjfilterHpfMinDataChanged (int value)
{
    fxDjfilterHpfMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterHpfMinUiChanged (int value)
{
    settingsProperties.setFxDjfilterHpfMin (value, false);
}

void SettingsEditorComponent::fxDjfilterHpfMaxDataChanged (int value)
{
    fxDjfilterHpfMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterHpfMaxUiChanged (int value)
{
    settingsProperties.setFxDjfilterHpfMax (value, false);
}

void SettingsEditorComponent::fxDjfilterLpfMinDataChanged (int value)
{
    fxDjfilterLpfMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterLpfMinUiChanged (int value)
{
    settingsProperties.setFxDjfilterLpfMin (value, false);
}

void SettingsEditorComponent::fxDjfilterLpfMaxDataChanged (int value)
{
    fxDjfilterLpfMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterLpfMaxUiChanged (int value)
{
    settingsProperties.setFxDjfilterLpfMax (value, false);
}

void SettingsEditorComponent::fxDjfilterQMinDataChanged (float value)
{
    fxDjfilterQMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterQMinUiChanged (float value)
{
    settingsProperties.setFxDjfilterQMin (value, false);
}

void SettingsEditorComponent::fxDjfilterQMaxDataChanged (float value)
{
    fxDjfilterQMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterQMaxUiChanged (float value)
{
    settingsProperties.setFxDjfilterQMax (value, false);
}

void SettingsEditorComponent::fxDjfilterQGainReductionDataChanged (float value)
{
    fxDjfilterQGainReductionEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterQGainReductionUiChanged (float value)
{
    settingsProperties.setFxDjfilterQGainReduction (value, false);
}

void SettingsEditorComponent::fxDubEchoTminDataChanged (int value)
{
    fxDubEchoTminEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoTminUiChanged (int value)
{
    settingsProperties.setFxDubEchoTmin (value, false);
}

void SettingsEditorComponent::fxDubEchoHpfDataChanged (int value)
{
    fxDubEchoHpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoHpfUiChanged (int value)
{
    settingsProperties.setFxDubEchoHpf (value, false);
}

void SettingsEditorComponent::fxDubEchoLpfDataChanged (int value)
{
    fxDubEchoLpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoLpfUiChanged (int value)
{
    settingsProperties.setFxDubEchoLpf (value, false);
}

void SettingsEditorComponent::fxDubEchoMixDataChanged (float value)
{
    fxDubEchoMixEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoMixUiChanged (float value)
{
    settingsProperties.setFxDubEchoMix (value, false);
}

void SettingsEditorComponent::fxChorusCenterDataChanged (float value)
{
    fxChorusCenterEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusCenterUiChanged (float value)
{
    settingsProperties.setFxChorusCenter (value, false);
}

void SettingsEditorComponent::fxChorusDepthDataChanged (float value)
{
    fxChorusDepthEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusDepthUiChanged (float value)
{
    settingsProperties.setFxChorusDepth (value, false);
}

void SettingsEditorComponent::fxChorusMixDataChanged (float value)
{
    fxChorusMixEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusMixUiChanged (float value)
{
    settingsProperties.setFxChorusMix (value, false);
}

void SettingsEditorComponent::fxChorusSpreadDataChanged (float value)
{
    fxChorusSpreadEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusSpreadUiChanged (float value)
{
    settingsProperties.setFxChorusSpread (value, false);
}

void SettingsEditorComponent::fxChorusTapsDataChanged (int value)
{
    fxChorusTapsComboBox.setSelectedId (value);
}

void SettingsEditorComponent::fxChorusTapsUiChanged (int value)
{
    settingsProperties.setFxChorusTaps (value, false);
}

void SettingsEditorComponent::fxChorusLfoBDataChanged (float value)
{
    fxChorusLfoBEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusLfoBUiChanged (float value)
{
    settingsProperties.setFxChorusLfoB (value, false);
}

void SettingsEditorComponent::fxChorusLfoTDataChanged (float value)
{
    fxChorusLfoTEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusLfoTUiChanged (float value)
{
    settingsProperties.setFxChorusLfoT (value, false);
}

void SettingsEditorComponent::fxReverbLpfDataChanged (int value)
{
    fxReverbLpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxReverbLpfUiChanged (int value)
{
    settingsProperties.setFxReverbLpf (value, false);
}

void SettingsEditorComponent::fxReverbHpfDataChanged (int value)
{
    fxReverbHpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxReverbHpfUiChanged (int value)
{
    settingsProperties.setFxReverbHpf (value, false);
}

void SettingsEditorComponent::fxGlitchProbabilityMinDataChanged (float value)
{
    fxGlitchProbabilityMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchProbabilityMinUiChanged (float value)
{
    settingsProperties.setFxGlitchProbabilityMin (value, false);
}

void SettingsEditorComponent::fxGlitchProbabilityMaxDataChanged (float value)
{
    fxGlitchProbabilityMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchProbabilityMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchProbabilityMax (value, false);
}

void SettingsEditorComponent::fxGlitchWeightHoldLowDataChanged (float value)
{
    fxGlitchWeightHoldLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightHoldLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightHoldLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightStutterLowDataChanged (float value)
{
    fxGlitchWeightStutterLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightStutterLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightStutterLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightCrushLowDataChanged (float value)
{
    fxGlitchWeightCrushLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightCrushLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightCrushLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightDropLowDataChanged (float value)
{
    fxGlitchWeightDropLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightDropLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightDropLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightHoldHighDataChanged (float value)
{
    fxGlitchWeightHoldHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightHoldHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightHoldHigh (value, false);
}

void SettingsEditorComponent::fxGlitchWeightStutterHighDataChanged (float value)
{
    fxGlitchWeightStutterHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightStutterHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightStutterHigh (value, false);
}

void SettingsEditorComponent::fxGlitchWeightCrushHighDataChanged (float value)
{
    fxGlitchWeightCrushHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightCrushHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightCrushHigh (value, false);
}

void SettingsEditorComponent::fxGlitchWeightDropHighDataChanged (float value)
{
    fxGlitchWeightDropHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightDropHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightDropHigh (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMinDataChanged (float value)
{
    fxGlitchDropKeepLevelMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMinUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepLevelMin (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMaxDataChanged (float value)
{
    fxGlitchDropKeepLevelMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepLevelMax (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMinDataChanged (float value)
{
    fxGlitchDropKeepTimeMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMinUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepTimeMin (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMaxDataChanged (float value)
{
    fxGlitchDropKeepTimeMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepTimeMax (value, false);
}

void SettingsEditorComponent::fxGlitchCrushTimeMinDataChanged (float value)
{
    fxGlitchCrushTimeMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchCrushTimeMinUiChanged (float value)
{
    settingsProperties.setFxGlitchCrushTimeMin (value, false);
}

void SettingsEditorComponent::fxGlitchCrushTimeMaxDataChanged (float value)
{
    fxGlitchCrushTimeMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchCrushTimeMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchCrushTimeMax (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMinDataChanged (float value)
{
    fxGlitchMicroloopSmplTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMinUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopSmplTMin (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMaxDataChanged (float value)
{
    fxGlitchMicroloopSmplTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopSmplTMax (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMinDataChanged (float value)
{
    fxGlitchMicroloopPlayTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMinUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopPlayTMin (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMaxDataChanged (float value)
{
    fxGlitchMicroloopPlayTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopPlayTMax (value, false);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMinDataChanged (float value)
{
    fxGlitchStutterSmplTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMinUiChanged (float value)
{
    settingsProperties.setFxGlitchStutterSmplTMin (value, false);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMaxDataChanged (float value)
{
    fxGlitchStutterSmplTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchStutterSmplTMax (value, false);
}

void SettingsEditorComponent::fxGlitchStutterNumMinDataChanged (int value)
{
    fxGlitchStutterNumMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterNumMinUiChanged (int value)
{
    settingsProperties.setFxGlitchStutterNumMin (value, false);
}

void SettingsEditorComponent::fxGlitchStutterNumMaxDataChanged (int value)
{
    fxGlitchStutterNumMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterNumMaxUiChanged (int value)
{
    settingsProperties.setFxGlitchStutterNumMax (value, false);
}

void SettingsEditorComponent::fxGlitchStutterWindowDataChanged (int value)
{
    fxGlitchStutterWindowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterWindowUiChanged (int value)
{
    settingsProperties.setFxGlitchStutterWindow (value, false);
}

void SettingsEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void SettingsEditorComponent::resized ()
{
    struct CompLabelPair
    {
        juce::Component* comp;
        juce::Label* label;
    };

    CompLabelPair pairs [] =
    {
        { &accClAmpModEditor, &accClAmpModLabel },
        { &accClRelModEditor, &accClRelModLabel },
        { &accOpAmpModEditor, &accOpAmpModLabel },
        { &accOpRelModEditor, &accOpRelModLabel },
        { &chokeReleaseEditor, &chokeReleaseLabel },
        { &clsdMaxReleaseEditor, &clsdMaxReleaseLabel },
        { &clsdRelOfstScaleEditor, &clsdRelOfstScaleLabel },
        { &clsdReleaseModeComboBox, &clsdReleaseModeLabel },
        { &cvDisableFxComboBox, &cvDisableFxLabel },
        { &cvDisableVelocityComboBox, &cvDisableVelocityLabel },
        { &envelopeMaxReleaseEditor, &envelopeMaxReleaseLabel },
        { &feelAmpModEditor, &feelAmpModLabel },
        { &feelAttackModEditor, &feelAttackModLabel },
        { &feelReleaseModEditor, &feelReleaseModLabel },
        { &fltrHpfMaxFreqEditor, &fltrHpfMaxFreqLabel },
        { &fltrHpfMinFreqEditor, &fltrHpfMinFreqLabel },
        { &fltrHpfQEditor, &fltrHpfQLabel },
        { &fltrLpfMaxFreqEditor, &fltrLpfMaxFreqLabel },
        { &fltrLpfMinFreqEditor, &fltrLpfMinFreqLabel },
        { &fltrLpfQEditor, &fltrLpfQLabel },
        { &fxChorusCenterEditor, &fxChorusCenterLabel },
        { &fxChorusDepthEditor, &fxChorusDepthLabel },
        { &fxChorusLfoBEditor, &fxChorusLfoBLabel },
        { &fxChorusLfoTEditor, &fxChorusLfoTLabel },
        { &fxChorusMixEditor, &fxChorusMixLabel },
        { &fxChorusSpreadEditor, &fxChorusSpreadLabel },
        { &fxChorusTapsComboBox, &fxChorusTapsLabel },
        { &fxCvUnipolarComboBox, &fxCvUnipolarLabel },
        { &fxDjfilterHpfMaxEditor, &fxDjfilterHpfMaxLabel },
        { &fxDjfilterHpfMinEditor, &fxDjfilterHpfMinLabel },
        { &fxDjfilterLpfMaxEditor, &fxDjfilterLpfMaxLabel },
        { &fxDjfilterLpfMinEditor, &fxDjfilterLpfMinLabel },
        { &fxDjfilterQGainReductionEditor, &fxDjfilterQGainReductionLabel },
        { &fxDjfilterQMaxEditor, &fxDjfilterQMaxLabel },
        { &fxDjfilterQMinEditor, &fxDjfilterQMinLabel },
        { &fxDubEchoHpfEditor, &fxDubEchoHpfLabel },
        { &fxDubEchoLpfEditor, &fxDubEchoLpfLabel },
        { &fxDubEchoMixEditor, &fxDubEchoMixLabel },
        { &fxDubEchoTminEditor, &fxDubEchoTminLabel },
        { &fxGlitchCrushTimeMaxEditor, &fxGlitchCrushTimeMaxLabel },
        { &fxGlitchCrushTimeMinEditor, &fxGlitchCrushTimeMinLabel },
        { &fxGlitchDropKeepLevelMaxEditor, &fxGlitchDropKeepLevelMaxLabel },
        { &fxGlitchDropKeepLevelMinEditor, &fxGlitchDropKeepLevelMinLabel },
        { &fxGlitchDropKeepTimeMaxEditor, &fxGlitchDropKeepTimeMaxLabel },
        { &fxGlitchDropKeepTimeMinEditor, &fxGlitchDropKeepTimeMinLabel },
        { &fxGlitchMicroloopPlayTMaxEditor, &fxGlitchMicroloopPlayTMaxLabel },
        { &fxGlitchMicroloopPlayTMinEditor, &fxGlitchMicroloopPlayTMinLabel },
        { &fxGlitchMicroloopSmplTMaxEditor, &fxGlitchMicroloopSmplTMaxLabel },
        { &fxGlitchMicroloopSmplTMinEditor, &fxGlitchMicroloopSmplTMinLabel },
        { &fxGlitchProbabilityMaxEditor, &fxGlitchProbabilityMaxLabel },
        { &fxGlitchProbabilityMinEditor, &fxGlitchProbabilityMinLabel },
        { &fxGlitchStutterNumMaxEditor, &fxGlitchStutterNumMaxLabel },
        { &fxGlitchStutterNumMinEditor, &fxGlitchStutterNumMinLabel },
        { &fxGlitchStutterSmplTMaxEditor, &fxGlitchStutterSmplTMaxLabel },
        { &fxGlitchStutterSmplTMinEditor, &fxGlitchStutterSmplTMinLabel },
        { &fxGlitchStutterWindowEditor, &fxGlitchStutterWindowLabel },
        { &fxGlitchWeightCrushLowEditor, &fxGlitchWeightCrushLowLabel },
        { &fxGlitchWeightDropHighEditor, &fxGlitchWeightDropHighLabel },
        { &fxGlitchWeightDropLowEditor, &fxGlitchWeightDropLowLabel },
        { &fxGlitchWeightHoldHighEditor, &fxGlitchWeightHoldHighLabel },
        { &fxGlitchWeightHoldLowEditor, &fxGlitchWeightHoldLowLabel },
        { &fxGlitchWeightStutterHighEditor, &fxGlitchWeightStutterHighLabel },
        { &fxGlitchWeightStutterLowEditor, &fxGlitchWeightStutterLowLabel },
        { &fxReverbHpfEditor, &fxReverbHpfLabel },
        { &fxReverbLpfEditor, &fxReverbLpfLabel },
        { &gateModeComboBox, &gateModeLabel },
        { &knobPosTakeupComboBox, &knobPosTakeupLabel },
        { &pitchHighEditor, &pitchHighLabel },
        { &pitchLowEditor, &pitchLowLabel },
        { &velocityUnipolarComboBox, &velocityUnipolarLabel }
    };


    auto curX { 10 };
    auto curY { 10 };
    constexpr auto kLabelWidth { 160 };
    constexpr auto kCompWidth { 100 };
    constexpr auto kLineHeight { 20 };
    constexpr auto kLinePerColumn { 20 };
    for (const auto& p : pairs)
    {
        p.label->setBounds (curX, curY, kLabelWidth, kLineHeight);
        p.comp->setBounds (curX + kLabelWidth + 2, curY, kCompWidth, kLineHeight);
        curY += kLineHeight + 2;
        if (curY + kLineHeight + 2 > kLinePerColumn * (kLineHeight + 2))
        {
            curY = 10;
            curX += kLabelWidth + kCompWidth + 10;
        }
    }
}
