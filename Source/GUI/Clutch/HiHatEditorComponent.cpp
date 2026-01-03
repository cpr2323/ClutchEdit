#include "HiHatEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

HiHatEditorComponent::HiHatEditorComponent ()
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
    accClAmpModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4).trimCharactersAtEnd ("0").trimCharactersAtEnd ("."); };
    accClAmpModEditor.updateDataCallback = [this] (double value) { accClAmpModUiChanged (value); };
    accClAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [this, dragSpeed] ()
        {
            if (dragSpeed == DragSpeed::slow)
                return 0.01f;
            else if (dragSpeed == DragSpeed::medium)
                return 0.1f;
            else
                return 1.0f;
        } ();
        const auto newValue { hiHatProperties.getAccClAmpMod () + (multiplier * direction) };
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
    accClRelModEditor.getMinValueCallback = [this] () { return 0.0; };
    accClRelModEditor.getMaxValueCallback = [this] () { return 1.0; };
    accClRelModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    accClRelModEditor.updateDataCallback = [this] (double value) { accClRelModUiChanged (value); };
    accClRelModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        accClRelModEditor.setValue (hiHatProperties.getAccClRelMod () + (multiplier * direction));
    };
    accClRelModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accClRelModEditor, accClRelModLabel, "Acc Cl Rel Mod");

    accOpAmpModEditor.setTooltip ("Acc Op Amp Mod");
    accOpAmpModEditor.getMinValueCallback = [this] () { return 0.0; };
    accOpAmpModEditor.getMaxValueCallback = [this] () { return 1.0; };
    accOpAmpModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    accOpAmpModEditor.updateDataCallback = [this] (double value) { accOpAmpModUiChanged (value); };
    accOpAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        accOpAmpModEditor.setValue (hiHatProperties.getAccOpAmpMod () + (multiplier * direction));
    };
    accOpAmpModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accOpAmpModEditor, accOpAmpModLabel, "Acc Op Amp Mod");

    accOpAmpModEditor.setTooltip ("Acc Op Amp Mod");
    accOpAmpModEditor.getMinValueCallback = [this] () { return 0.0; };
    accOpAmpModEditor.getMaxValueCallback = [this] () { return 1.0; };
    accOpAmpModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    accOpAmpModEditor.updateDataCallback = [this] (double value) { accOpAmpModUiChanged (value); };
    accOpAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        accOpAmpModEditor.setValue (hiHatProperties.getAccOpAmpMod () + (multiplier * direction));
    };
    accOpAmpModEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (accOpRelModEditor, accOpRelModLabel, "Acc Op Rel Mod");

    chokeReleaseEditor.setTooltip ("Choke Release");
    chokeReleaseEditor.getMinValueCallback = [this] () { return 0.0; };
    chokeReleaseEditor.getMaxValueCallback = [this] () { return 1.0; };
    chokeReleaseEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    chokeReleaseEditor.updateDataCallback = [this] (double value) { chokeReleaseUiChanged (value); };
    chokeReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        chokeReleaseEditor.setValue (hiHatProperties.getChokeRelease () + (multiplier * direction));
    };
    chokeReleaseEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (chokeReleaseEditor, chokeReleaseLabel, "Choke Release");

    chokeReleaseEditor.setTooltip ("Choke Release");
    chokeReleaseEditor.getMinValueCallback = [this] () { return 0.0; };
    chokeReleaseEditor.getMaxValueCallback = [this] () { return 1.0; };
    chokeReleaseEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    chokeReleaseEditor.updateDataCallback = [this] (double value) { chokeReleaseUiChanged (value); };
    chokeReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        chokeReleaseEditor.setValue (hiHatProperties.getChokeRelease () + (multiplier * direction));
    };
    chokeReleaseEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (clsdMaxReleaseEditor, clsdMaxReleaseLabel, "Clsd Max Release");

    chokeReleaseEditor.setTooltip ("Choke Release");
    chokeReleaseEditor.getMinValueCallback = [this] () { return 0.0; };
    chokeReleaseEditor.getMaxValueCallback = [this] () { return 1.0; };
    chokeReleaseEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    chokeReleaseEditor.updateDataCallback = [this] (double value) { chokeReleaseUiChanged (value); };
    chokeReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        chokeReleaseEditor.setValue (hiHatProperties.getChokeRelease () + (multiplier * direction));
    };
    chokeReleaseEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu m;
        m.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        m.showMenuAsync ({}, [this] (int) {});
    };
    setupDoubleEditor (clsdRelOfstScaleEditor, clsdRelOfstScaleLabel, "Clsd Rel Ofst Scale");

    // 0: Independent Release for Closed
    // 1: Release Offset mode
    clsdReleaseModeEditor.setLookAndFeel (&noArrowComboBoxLnF);
    clsdReleaseModeEditor.setTooltip ("");
    clsdReleaseModeEditor.addItem ("Independent", 1);
    clsdReleaseModeEditor.addItem ("Offset", 2);
    clsdReleaseModeEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto clsdReleaseMode { clsdReleaseModeEditor.getSelectedId () - 1 };
        hiHatProperties.setClsdReleaseMode (std::clamp (clsdReleaseMode + scrollAmount, 0, 1), true);
    };
    clsdReleaseModeEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (clsdReleaseModeEditor, clsdReleaseModeLabel, "Clsd Release Mode");

    // 0: FX CV Always On
    // 1: CV Disable : Freeze FX CV
    cvDisableFxEditor.setLookAndFeel (&noArrowComboBoxLnF);
    cvDisableFxEditor.setTooltip ("");
    cvDisableFxEditor.addItem ("FX CV On", 1);
    cvDisableFxEditor.addItem ("FX CV Off", 2);
    cvDisableFxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto cvDisableFx { cvDisableFxEditor.getSelectedId () - 1 };
        hiHatProperties.setCvDisableFx (std::clamp (cvDisableFx + scrollAmount, 0, 1), true);
    };
    cvDisableFxEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (cvDisableFxEditor, cvDisableFxLabel, "CV Disable FX");

    // 0: Velocity always enabled
    // 1: CV Off SW affects velocity
    cvDisableVelocityEditor.setLookAndFeel (&noArrowComboBoxLnF);
    cvDisableVelocityEditor.setTooltip ("");
    cvDisableVelocityEditor.addItem ("Always On", 1);
    cvDisableVelocityEditor.addItem ("CV Off", 2);
    cvDisableVelocityEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto cvDisableVelocity { cvDisableVelocityEditor.getSelectedId () - 1 };
        hiHatProperties.setCvDisableVelocity (std::clamp (cvDisableVelocity + scrollAmount, 0, 1), true);
    };
    cvDisableVelocityEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (cvDisableVelocityEditor, cvDisableVelocityLabel, "CV Disable Velocity");

    envelopeMaxReleaseEditor.setTooltip ("Envelope Max Release");
    envelopeMaxReleaseEditor.getMinValueCallback = [this] () { return 0.0; };
    envelopeMaxReleaseEditor.getMaxValueCallback = [this] () { return 1.0; };
    envelopeMaxReleaseEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    envelopeMaxReleaseEditor.updateDataCallback = [this] (double value) { envelopeMaxReleaseUiChanged (value); };
    envelopeMaxReleaseEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        envelopeMaxReleaseEditor.setValue (hiHatProperties.getEnvelopeMaxRelease () + (multiplier * direction));
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
    feelAmpModEditor.getMaxValueCallback = [this] () { return 1.0; };
    feelAmpModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    feelAmpModEditor.updateDataCallback = [this] (double value) { feelAmpModUiChanged (value); };
    feelAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = (dragSpeed == DragSpeed::slow ? 1 : dragSpeed == DragSpeed::medium ? 10 : 25);
        feelAmpModEditor.setValue (hiHatProperties.getFeelAmpMod () + (multiplier * direction));
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
    feelAttackModEditor.getMaxValueCallback = [this] () { return 1.0; };
    feelAttackModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    feelAttackModEditor.updateDataCallback = [this] (double value) { feelAttackModUiChanged (value); };
    feelAttackModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFeelAttackMod () + (multiplier * direction) };
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
    feelReleaseModEditor.getMaxValueCallback = [this] () { return 1.0; };
    feelReleaseModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    feelReleaseModEditor.updateDataCallback = [this] (double value) { feelReleaseModUiChanged (value); };
    feelReleaseModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFeelReleaseMod () + (multiplier * direction) };
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
    fltrHpfMaxFreqEditor.getMinValueCallback = [this] () { return 0; };
    fltrHpfMaxFreqEditor.getMaxValueCallback = [this] () { return 1; };
    fltrHpfMaxFreqEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fltrHpfMaxFreqEditor.updateDataCallback = [this] (int value) { fltrHpfMaxFreqUiChanged (value); };
    fltrHpfMaxFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFltrHpfMaxFreq () + (multiplier * direction) };
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
    fltrHpfMinFreqEditor.getMinValueCallback = [this] () { return 0; };
    fltrHpfMinFreqEditor.getMaxValueCallback = [this] () { return 1; };
    fltrHpfMinFreqEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fltrHpfMinFreqEditor.updateDataCallback = [this] (int value) { fltrHpfMinFreqUiChanged (value); };
    fltrHpfMinFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFltrHpfMinFreq () + (multiplier * direction) };
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
    fltrHpfQEditor.getMinValueCallback = [this] () { return 0.0; };
    fltrHpfQEditor.getMaxValueCallback = [this] () { return 1.0; };
    fltrHpfQEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fltrHpfQEditor.updateDataCallback = [this] (double value) { fltrHpfQUiChanged (value); };
    fltrHpfQEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFltrHpfQ () + (multiplier * direction) };
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
    fltrLpfMaxFreqEditor.getMinValueCallback = [this] () { return 0; };
    fltrLpfMaxFreqEditor.getMaxValueCallback = [this] () { return 1; };
    fltrLpfMaxFreqEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fltrLpfMaxFreqEditor.updateDataCallback = [this] (int value) { fltrLpfMaxFreqUiChanged (value); };
    fltrLpfMaxFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFltrLpfMaxFreq () + (multiplier * direction) };
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
    fltrLpfMinFreqEditor.getMinValueCallback = [this] () { return 0; };
    fltrLpfMinFreqEditor.getMaxValueCallback = [this] () { return 1; };
    fltrLpfMinFreqEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fltrLpfMinFreqEditor.updateDataCallback = [this] (int value) { fltrLpfMinFreqUiChanged (value); };
    fltrLpfMinFreqEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFltrLpfMinFreq () + (multiplier * direction) };
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
    fltrLpfQEditor.getMinValueCallback = [this] () { return 0.0; };
    fltrLpfQEditor.getMaxValueCallback = [this] () { return 1.0; };
    fltrLpfQEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fltrLpfQEditor.updateDataCallback = [this] (double value) { fltrLpfQUiChanged (value); };
    fltrLpfQEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFltrLpfQ () + (multiplier * direction) };
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
    fxChorusCenterEditor.getMinValueCallback = [this] () { return 0.0; };
    fxChorusCenterEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusCenterEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxChorusCenterEditor.updateDataCallback = [this] (double value) { fxChorusCenterUiChanged (value); };
    fxChorusCenterEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxChorusCenter () + (multiplier * direction) };
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
    fxChorusDepthEditor.getMinValueCallback = [this] () { return 0.0; };
    fxChorusDepthEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusDepthEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxChorusDepthEditor.updateDataCallback = [this] (double value) { fxChorusDepthUiChanged (value); };
    fxChorusDepthEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxChorusDepth () + (multiplier * direction) };
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
    fxChorusLfoBEditor.getMinValueCallback = [this] () { return 0.0; };
    fxChorusLfoBEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusLfoBEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxChorusLfoBEditor.updateDataCallback = [this] (double value) { fxChorusLfoBUiChanged (value); };
    fxChorusLfoBEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxChorusLfoB () + (multiplier * direction) };
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
    fxChorusLfoTEditor.getMinValueCallback = [this] () { return 0; };
    fxChorusLfoTEditor.getMaxValueCallback = [this] () { return 1; };
    fxChorusLfoTEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxChorusLfoTEditor.updateDataCallback = [this] (int value) { fxChorusLfoTUiChanged (value); };
    fxChorusLfoTEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxChorusLfoT () + (multiplier * direction) };
        fxChorusLfoTEditor.setValue (newValue);
    };
    fxChorusLfoTEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupIntEditor (fxChorusLfoTEditor, fxChorusLfoTLabel, "FX Chorus LFO T");

    fxChorusMixEditor.setTooltip ("FX Chorus Mix");
    fxChorusMixEditor.getMinValueCallback = [this] () { return 0.0; };
    fxChorusMixEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusMixEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxChorusMixEditor.updateDataCallback = [this] (double value) { fxChorusMixUiChanged (value); };
    fxChorusMixEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxChorusMix () + (multiplier * direction) };
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
    fxChorusSpreadEditor.getMinValueCallback = [this] () { return 0.0; };
    fxChorusSpreadEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxChorusSpreadEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxChorusSpreadEditor.updateDataCallback = [this] (double value) { fxChorusSpreadUiChanged (value); };
    fxChorusSpreadEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxChorusSpread () + (multiplier * direction) };
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
    fxChorusTapsEditor.setLookAndFeel (&noArrowComboBoxLnF);
    fxChorusTapsEditor.setTooltip ("");
    fxChorusTapsEditor.addItem ("1", 1);
    fxChorusTapsEditor.addItem ("2", 2);
    fxChorusTapsEditor.addItem ("3", 3);
    fxChorusTapsEditor.addItem ("4", 4);
    fxChorusTapsEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto fxChorusTaps { fxChorusTapsEditor.getSelectedId () };
        hiHatProperties.setFxChorusTaps (std::clamp (fxChorusTaps + scrollAmount, 1, 4), true);
    };
    fxChorusTapsEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (fxChorusTapsEditor, fxChorusTapsLabel, "FX Chorus Taps");

    // 0: -5 to 5V, 1: 0 to 5V 
    fxCvUnipolarEditor.setLookAndFeel (&noArrowComboBoxLnF);
    fxCvUnipolarEditor.setTooltip ("");
    fxCvUnipolarEditor.addItem ("-5v to 5v", 1);
    fxCvUnipolarEditor.addItem ("0v to 5v", 2);
    fxCvUnipolarEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto fxCvUnipolar { fxCvUnipolarEditor.getSelectedId () - 1 };
        hiHatProperties.setFxCvUnipolar (std::clamp (fxCvUnipolar + scrollAmount, 0, 1), true);
    };
    fxCvUnipolarEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (fxCvUnipolarEditor, fxCvUnipolarLabel, "FX CV Unipolar");

    fxDjfilterHpfMaxEditor.setTooltip ("FX DJ Filter HPF Max");
    fxDjfilterHpfMaxEditor.getMinValueCallback = [this] () { return 0; };
    fxDjfilterHpfMaxEditor.getMaxValueCallback = [this] () { return 1; };
    fxDjfilterHpfMaxEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterHpfMaxEditor.updateDataCallback = [this] (int value) { fxDjfilterHpfMaxUiChanged (value); };
    fxDjfilterHpfMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterHpfMax () + (multiplier * direction) };
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
    fxDjfilterHpfMinEditor.getMinValueCallback = [this] () { return 0; };
    fxDjfilterHpfMinEditor.getMaxValueCallback = [this] () { return 1; };
    fxDjfilterHpfMinEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterHpfMinEditor.updateDataCallback = [this] (int value) { fxDjfilterHpfMinUiChanged (value); };
    fxDjfilterHpfMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterHpfMin () + (multiplier * direction) };
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
    fxDjfilterLpfMaxEditor.getMinValueCallback = [this] () { return 0; };
    fxDjfilterLpfMaxEditor.getMaxValueCallback = [this] () { return 1; };
    fxDjfilterLpfMaxEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterLpfMaxEditor.updateDataCallback = [this] (int value) { fxDjfilterLpfMaxUiChanged (value); };
    fxDjfilterLpfMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterLpfMax () + (multiplier * direction) };
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
    fxDjfilterLpfMinEditor.getMinValueCallback = [this] () { return 0; };
    fxDjfilterLpfMinEditor.getMaxValueCallback = [this] () { return 1; };
    fxDjfilterLpfMinEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDjfilterLpfMinEditor.updateDataCallback = [this] (int value) { fxDjfilterLpfMinUiChanged (value); };
    fxDjfilterLpfMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterLpfMin () + (multiplier * direction) };
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
    fxDjfilterQGainReductionEditor.getMinValueCallback = [this] () { return 0.0; };
    fxDjfilterQGainReductionEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxDjfilterQGainReductionEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxDjfilterQGainReductionEditor.updateDataCallback = [this] (double value) { fxDjfilterQGainReductionUiChanged (value); };
    fxDjfilterQGainReductionEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterQGainReduction () + (multiplier * direction) };
        fxDjfilterQGainReductionEditor.setValue (newValue);
    };
    fxDjfilterQGainReductionEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxDjfilterQGainReductionEditor, fxDjfilterQGainReductionLabel, "FX DJ Filter Q Gain Reduction");

    fxDjfilterQGainReductionEditor.setTooltip ("FX DJ Filter Q Gain Reduction");
    fxDjfilterQGainReductionEditor.getMinValueCallback = [this] () { return 0.0; };
    fxDjfilterQGainReductionEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxDjfilterQGainReductionEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxDjfilterQGainReductionEditor.updateDataCallback = [this] (double value) { fxDjfilterQGainReductionUiChanged (value); };
    fxDjfilterQGainReductionEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterQGainReduction () + (multiplier * direction) };
        fxDjfilterQGainReductionEditor.setValue (newValue);
    };
    fxDjfilterQGainReductionEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.addItem ("NEED TO IMPLEMENT FUNCTIONS", [this] () {});
        editMenu.showMenuAsync ({}, [this] (int) {});
    }; 
    setupDoubleEditor (fxDjfilterQMaxEditor, fxDjfilterQMaxLabel, "FX DJ Filter Q Max");

    fxDjfilterQMinEditor.setTooltip ("FX DJ Filter Q Min");
    fxDjfilterQMinEditor.getMinValueCallback = [this] () { return 0.0; };
    fxDjfilterQMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxDjfilterQMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxDjfilterQMinEditor.updateDataCallback = [this] (double value) { fxDjfilterQMinUiChanged (value); };
    fxDjfilterQMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDjfilterQMin () + (multiplier * direction) };
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
    fxDubEchoHpfEditor.getMinValueCallback = [this] () { return 0; };
    fxDubEchoHpfEditor.getMaxValueCallback = [this] () { return 1; };
    fxDubEchoHpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDubEchoHpfEditor.updateDataCallback = [this] (int value) { fxDubEchoHpfUiChanged (value); };
    fxDubEchoHpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDubEchoHpf () + (multiplier * direction) };
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
    fxDubEchoLpfEditor.getMinValueCallback = [this] () { return 0; };
    fxDubEchoLpfEditor.getMaxValueCallback = [this] () { return 1; };
    fxDubEchoLpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDubEchoLpfEditor.updateDataCallback = [this] (int value) { fxDubEchoLpfUiChanged (value); };
    fxDubEchoLpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDubEchoLpf () + (multiplier * direction) };
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
    fxDubEchoMixEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxDubEchoMixEditor.updateDataCallback = [this] (double value) { fxDubEchoMixUiChanged (value); };
    fxDubEchoMixEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDubEchoMix () + (multiplier * direction) };
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
    fxDubEchoTminEditor.getMaxValueCallback = [this] () { return 1; };
    fxDubEchoTminEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxDubEchoTminEditor.updateDataCallback = [this] (int value) { fxDubEchoTminUiChanged (value); };
    fxDubEchoTminEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxDubEchoTmin () + (multiplier * direction) };
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
    fxGlitchCrushTimeMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchCrushTimeMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchCrushTimeMaxEditor.updateDataCallback = [this] (double value) { fxGlitchCrushTimeMaxUiChanged (value); };
    fxGlitchCrushTimeMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchCrushTimeMax () + (multiplier * direction) };
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
    fxGlitchCrushTimeMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchCrushTimeMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchCrushTimeMinEditor.updateDataCallback = [this] (double value) { fxGlitchCrushTimeMinUiChanged (value); };
    fxGlitchCrushTimeMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchCrushTimeMin () + (multiplier * direction) };
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
    fxGlitchDropKeepLevelMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchDropKeepLevelMaxEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepLevelMaxUiChanged (value); };
    fxGlitchDropKeepLevelMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchDropKeepLevelMax () + (multiplier * direction) };
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
    fxGlitchDropKeepLevelMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchDropKeepLevelMinEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepLevelMinUiChanged (value); };
    fxGlitchDropKeepLevelMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchDropKeepLevelMin () + (multiplier * direction) };
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
    fxGlitchDropKeepTimeMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchDropKeepTimeMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchDropKeepTimeMaxEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepTimeMaxUiChanged (value); };
    fxGlitchDropKeepTimeMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchDropKeepTimeMax () + (multiplier * direction) };
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
    fxGlitchDropKeepTimeMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchDropKeepTimeMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchDropKeepTimeMinEditor.updateDataCallback = [this] (double value) { fxGlitchDropKeepTimeMinUiChanged (value); };
    fxGlitchDropKeepTimeMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchDropKeepTimeMin () + (multiplier * direction) };
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
    fxGlitchMicroloopPlayTMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchMicroloopPlayTMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchMicroloopPlayTMaxEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopPlayTMaxUiChanged (value); };
    fxGlitchMicroloopPlayTMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchMicroloopPlayTMax () + (multiplier * direction) };
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
    fxGlitchMicroloopPlayTMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchMicroloopPlayTMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchMicroloopPlayTMinEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopPlayTMinUiChanged (value); };
    fxGlitchMicroloopPlayTMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchMicroloopPlayTMin () + (multiplier * direction) };
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
    fxGlitchMicroloopSmplTMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchMicroloopSmplTMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchMicroloopSmplTMaxEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopSmplTMaxUiChanged (value); };
    fxGlitchMicroloopSmplTMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchMicroloopSmplTMax () + (multiplier * direction) };
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
    fxGlitchMicroloopSmplTMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchMicroloopSmplTMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchMicroloopSmplTMinEditor.updateDataCallback = [this] (double value) { fxGlitchMicroloopSmplTMinUiChanged (value); };
    fxGlitchMicroloopSmplTMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchMicroloopSmplTMin () + (multiplier * direction) };
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
    fxGlitchProbabilityMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchProbabilityMaxEditor.updateDataCallback = [this] (double value) { fxGlitchProbabilityMaxUiChanged (value); };
    fxGlitchProbabilityMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchProbabilityMax () + (multiplier * direction) };
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
    fxGlitchProbabilityMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchProbabilityMinEditor.updateDataCallback = [this] (double value) { fxGlitchProbabilityMinUiChanged (value); };
    fxGlitchProbabilityMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchProbabilityMin () + (multiplier * direction) };
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
    fxGlitchStutterNumMaxEditor.getMaxValueCallback = [this] () { return 1; };
    fxGlitchStutterNumMaxEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxGlitchStutterNumMaxEditor.updateDataCallback = [this] (int value) { fxGlitchStutterNumMaxUiChanged (value); };
    fxGlitchStutterNumMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchStutterNumMax () + (multiplier * direction) };
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
    fxGlitchStutterNumMinEditor.getMaxValueCallback = [this] () { return 1; };
    fxGlitchStutterNumMinEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxGlitchStutterNumMinEditor.updateDataCallback = [this] (int value) { fxGlitchStutterNumMinUiChanged (value); };
    fxGlitchStutterNumMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchStutterNumMin () + (multiplier * direction) };
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
    fxGlitchStutterSmplTMaxEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchStutterSmplTMaxEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchStutterSmplTMaxEditor.updateDataCallback = [this] (double value) { fxGlitchStutterSmplTMaxUiChanged (value); };
    fxGlitchStutterSmplTMaxEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchStutterSmplTMax () + (multiplier * direction) };
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
    fxGlitchStutterSmplTMinEditor.getMaxValueCallback = [this] () { return 1.0; };
    fxGlitchStutterSmplTMinEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchStutterSmplTMinEditor.updateDataCallback = [this] (double value) { fxGlitchStutterSmplTMinUiChanged (value); };
    fxGlitchStutterSmplTMinEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchStutterSmplTMin () + (multiplier * direction) };
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
    fxGlitchStutterWindowEditor.getMaxValueCallback = [this] () { return 1; };
    fxGlitchStutterWindowEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxGlitchStutterWindowEditor.updateDataCallback = [this] (int value) { fxGlitchStutterWindowUiChanged (value); };
    fxGlitchStutterWindowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchStutterWindow () + (multiplier * direction) };
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
    fxGlitchWeightCrushLowEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightCrushLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightCrushLowUiChanged (value); };
    fxGlitchWeightCrushLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightCrushLow () + (multiplier * direction) };
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
    fxGlitchWeightDropHighEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightDropHighEditor.updateDataCallback = [this] (double value) { fxGlitchWeightDropHighUiChanged (value); };
    fxGlitchWeightDropHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightDropHigh () + (multiplier * direction) };
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
    fxGlitchWeightDropLowEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightDropLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightDropLowUiChanged (value); };
    fxGlitchWeightDropLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightDropLow () + (multiplier * direction) };
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
    fxGlitchWeightHoldHighEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightHoldHighEditor.updateDataCallback = [this] (double value) { fxGlitchWeightHoldHighUiChanged (value); };
    fxGlitchWeightHoldHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightHoldHigh () + (multiplier * direction) };
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
    fxGlitchWeightHoldLowEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightHoldLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightHoldLowUiChanged (value); };
    fxGlitchWeightHoldLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightHoldLow () + (multiplier * direction) };
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
    fxGlitchWeightStutterHighEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightStutterHighEditor.updateDataCallback = [this] (double value) { fxGlitchWeightStutterHighUiChanged (value); };
    fxGlitchWeightStutterHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightStutterHigh () + (multiplier * direction) };
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
    fxGlitchWeightStutterLowEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    fxGlitchWeightStutterLowEditor.updateDataCallback = [this] (double value) { fxGlitchWeightStutterLowUiChanged (value); };
    fxGlitchWeightStutterLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxGlitchWeightStutterLow () + (multiplier * direction) };
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
    fxReverbHpfEditor.getMinValueCallback = [this] () { return 0; };
    fxReverbHpfEditor.getMaxValueCallback = [this] () { return 1; };
    fxReverbHpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxReverbHpfEditor.updateDataCallback = [this] (int value) { fxReverbHpfUiChanged (value); };
    fxReverbHpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxReverbHpf () + (multiplier * direction) };
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
    fxReverbLpfEditor.getMinValueCallback = [this] () { return 0; };
    fxReverbLpfEditor.getMaxValueCallback = [this] () { return 1; };
    fxReverbLpfEditor.toStringCallback = [this] (int value) { return juce::String (value); };
    fxReverbLpfEditor.updateDataCallback = [this] (int value) { fxReverbLpfUiChanged (value); };
    fxReverbLpfEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getFxReverbLpf () + (multiplier * direction) };
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
    gateModeEditor.setLookAndFeel (&noArrowComboBoxLnF);
    gateModeEditor.setTooltip ("");
    gateModeEditor.addItem ("Immediate", 1);
    gateModeEditor.addItem ("After Gate Falls", 2);
    gateModeEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto gateMode { gateModeEditor.getSelectedId () - 1 };
        hiHatProperties.setGateMode (std::clamp (gateMode + scrollAmount, 0, 1), true);
    };
    gateModeEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (gateModeEditor, gateModeLabel, "Gate Mode");

    // 0 to sense small movement (wiggle)
    // 1 to require passing old value
    knobPosTakeupEditor.setLookAndFeel (&noArrowComboBoxLnF);
    knobPosTakeupEditor.setTooltip ("");
    knobPosTakeupEditor.addItem ("Small Movement", 1);
    knobPosTakeupEditor.addItem ("Pass Old Value", 2);
    knobPosTakeupEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto fxCvUnipolar { knobPosTakeupEditor.getSelectedId () - 1 };
        hiHatProperties.setKnobPosTakeup (std::clamp (fxCvUnipolar + scrollAmount, 0, 1), true);
    };
    knobPosTakeupEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (knobPosTakeupEditor, knobPosTakeupLabel, "Knob Pos Takeup");

    pitchHighEditor.setTooltip ("Pitch High");
    pitchHighEditor.getMinValueCallback = [this] () { return 0.0; };
    pitchHighEditor.getMaxValueCallback = [this] () { return 1.0; };
    pitchHighEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    pitchHighEditor.updateDataCallback = [this] (double value) { pitchHighUiChanged (value); };
    pitchHighEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getPitchHigh () + (multiplier * direction) };
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
    pitchLowEditor.getMinValueCallback = [this] () { return 0.0; };
    pitchLowEditor.getMaxValueCallback = [this] () { return 1.0; };
    pitchLowEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    pitchLowEditor.updateDataCallback = [this] (double value) { pitchLowUiChanged (value); };
    pitchLowEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto multiplier = [dragSpeed] ()
            {
                if (dragSpeed == DragSpeed::slow)   return 1;
                if (dragSpeed == DragSpeed::medium) return 10;
                return 25;
            } ();

        const auto newValue { hiHatProperties.getPitchLow () + (multiplier * direction) };
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
    velocityUnipolarEditor.setLookAndFeel (&noArrowComboBoxLnF);
    velocityUnipolarEditor.setTooltip ("");
    velocityUnipolarEditor.addItem ("0%-100%-200%", 1);
    velocityUnipolarEditor.addItem ("0%-100%", 2);
    velocityUnipolarEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
    {
        const auto scrollAmount { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
        const auto velocityUnipolar { velocityUnipolarEditor.getSelectedId () - 1 };
        hiHatProperties.setVelocityUnipolar (std::clamp (velocityUnipolar + scrollAmount, 0, 1), true);
    };
    velocityUnipolarEditor.onPopupMenuCallback = [this] ()
    {
        juce::PopupMenu editMenu;
        editMenu.showMenuAsync ({}, [this] (int) {});
    };
    setupComboBox (velocityUnipolarEditor, velocityUnipolarLabel, "Velocity Unipolar");
}

HiHatEditorComponent::~HiHatEditorComponent ()
{
}

void HiHatEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    hiHatProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("HiHat"), ValueTreeWrapper<HiHatProperties>::WrapperType::client, ValueTreeWrapper<HiHatProperties>::EnableCallbacks::yes);

    // initialize fields when data first attached
    pitchLowDataChanged (hiHatProperties.getPitchLow ());
    pitchHighDataChanged (hiHatProperties.getPitchHigh ());
    envelopeMaxReleaseDataChanged (hiHatProperties.getEnvelopeMaxRelease ());
    chokeReleaseDataChanged (hiHatProperties.getChokeRelease ());
    clsdReleaseModeDataChanged (hiHatProperties.getClsdReleaseMode ());
    clsdRelOfstScaleDataChanged (hiHatProperties.getClsdRelOfstScale ());
    clsdMaxReleaseDataChanged (hiHatProperties.getClsdMaxRelease ());
    accClRelModDataChanged (hiHatProperties.getAccClRelMod ());
    accOpRelModDataChanged (hiHatProperties.getAccOpRelMod ());
    accClAmpModDataChanged (hiHatProperties.getAccClAmpMod ());
    accOpAmpModDataChanged (hiHatProperties.getAccOpAmpMod ());
    fxCvUnipolarDataChanged (hiHatProperties.getFxCvUnipolar ());
    velocityUnipolarDataChanged (hiHatProperties.getVelocityUnipolar ());
    cvDisableVelocityDataChanged (hiHatProperties.getCvDisableVelocity ());
    cvDisableFxDataChanged (hiHatProperties.getCvDisableFx ());
    gateModeDataChanged (hiHatProperties.getGateMode ());
    feelAttackModDataChanged (hiHatProperties.getFeelAttackMod ());
    feelReleaseModDataChanged (hiHatProperties.getFeelReleaseMod ());
    feelAmpModDataChanged (hiHatProperties.getFeelAmpMod ());
    knobPosTakeupDataChanged (hiHatProperties.getKnobPosTakeup ());
    fltrHpfMinFreqDataChanged (hiHatProperties.getFltrHpfMinFreq ());
    fltrHpfMaxFreqDataChanged (hiHatProperties.getFltrHpfMaxFreq ());
    fltrLpfMinFreqDataChanged (hiHatProperties.getFltrLpfMinFreq ());
    fltrLpfMaxFreqDataChanged (hiHatProperties.getFltrLpfMaxFreq ());
    fltrHpfQDataChanged (hiHatProperties.getFltrHpfQ ());
    fltrLpfQDataChanged (hiHatProperties.getFltrLpfQ ());
    fxDjfilterHpfMinDataChanged (hiHatProperties.getFxDjfilterHpfMin ());
    fxDjfilterHpfMaxDataChanged (hiHatProperties.getFxDjfilterHpfMax ());
    fxDjfilterLpfMinDataChanged (hiHatProperties.getFxDjfilterLpfMin ());
    fxDjfilterLpfMaxDataChanged (hiHatProperties.getFxDjfilterLpfMax ());
    fxDjfilterQMinDataChanged (hiHatProperties.getFxDjfilterQMin ());
    fxDjfilterQMaxDataChanged (hiHatProperties.getFxDjfilterQMax ());
    fxDjfilterQGainReductionDataChanged (hiHatProperties.getFxDjfilterQGainReduction ());
    fxDubEchoTminDataChanged (hiHatProperties.getFxDubEchoTmin ());
    fxDubEchoHpfDataChanged (hiHatProperties.getFxDubEchoHpf ());
    fxDubEchoLpfDataChanged (hiHatProperties.getFxDubEchoLpf ());
    fxDubEchoMixDataChanged (hiHatProperties.getFxDubEchoMix ());
    fxChorusCenterDataChanged (hiHatProperties.getFxChorusCenter ());
    fxChorusDepthDataChanged (hiHatProperties.getFxChorusDepth ());
    fxChorusMixDataChanged (hiHatProperties.getFxChorusMix ());
    fxChorusSpreadDataChanged (hiHatProperties.getFxChorusSpread ());
    fxChorusTapsDataChanged (hiHatProperties.getFxChorusTaps ());
    fxChorusLfoBDataChanged (hiHatProperties.getFxChorusLfoB ());
    fxChorusLfoTDataChanged (hiHatProperties.getFxChorusLfoT ());
    fxReverbLpfDataChanged (hiHatProperties.getFxReverbLpf ());
    fxReverbHpfDataChanged (hiHatProperties.getFxReverbHpf ());
    fxGlitchProbabilityMinDataChanged (hiHatProperties.getFxGlitchProbabilityMin ());
    fxGlitchProbabilityMaxDataChanged (hiHatProperties.getFxGlitchProbabilityMax ());
    fxGlitchWeightHoldLowDataChanged (hiHatProperties.getFxGlitchWeightHoldLow ());
    fxGlitchWeightStutterLowDataChanged (hiHatProperties.getFxGlitchWeightStutterLow ());
    fxGlitchWeightCrushLowDataChanged (hiHatProperties.getFxGlitchWeightCrushLow ());
    fxGlitchWeightDropLowDataChanged (hiHatProperties.getFxGlitchWeightDropLow ());
    fxGlitchWeightHoldHighDataChanged (hiHatProperties.getFxGlitchWeightHoldHigh ());
    fxGlitchWeightStutterHighDataChanged (hiHatProperties.getFxGlitchWeightStutterHigh ());
    fxGlitchWeightCrushHighDataChanged (hiHatProperties.getFxGlitchWeightCrushHigh ());
    fxGlitchWeightDropHighDataChanged (hiHatProperties.getFxGlitchWeightDropHigh ());
    fxGlitchDropKeepLevelMinDataChanged (hiHatProperties.getFxGlitchDropKeepLevelMin ());
    fxGlitchDropKeepLevelMaxDataChanged (hiHatProperties.getFxGlitchDropKeepLevelMax ());
    fxGlitchDropKeepTimeMinDataChanged (hiHatProperties.getFxGlitchDropKeepTimeMin ());
    fxGlitchDropKeepTimeMaxDataChanged (hiHatProperties.getFxGlitchDropKeepTimeMax ());
    fxGlitchCrushTimeMinDataChanged (hiHatProperties.getFxGlitchCrushTimeMin ());
    fxGlitchCrushTimeMaxDataChanged (hiHatProperties.getFxGlitchCrushTimeMax ());
    fxGlitchMicroloopSmplTMinDataChanged (hiHatProperties.getFxGlitchMicroloopSmplTMin ());
    fxGlitchMicroloopSmplTMaxDataChanged (hiHatProperties.getFxGlitchMicroloopSmplTMax ());
    fxGlitchMicroloopPlayTMinDataChanged (hiHatProperties.getFxGlitchMicroloopPlayTMin ());
    fxGlitchMicroloopPlayTMaxDataChanged (hiHatProperties.getFxGlitchMicroloopPlayTMax ());
    fxGlitchStutterSmplTMinDataChanged (hiHatProperties.getFxGlitchStutterSmplTMin ());
    fxGlitchStutterSmplTMaxDataChanged (hiHatProperties.getFxGlitchStutterSmplTMax ());
    fxGlitchStutterNumMinDataChanged (hiHatProperties.getFxGlitchStutterNumMin ());
    fxGlitchStutterNumMaxDataChanged (hiHatProperties.getFxGlitchStutterNumMax ());
    fxGlitchStutterWindowDataChanged (hiHatProperties.getFxGlitchStutterWindow ());

    initializeCallbacks ();
}

void HiHatEditorComponent::initializeCallbacks ()
{
    jassert (hiHatProperties.isValid ());
    hiHatProperties.onPitchLowChange = [this] (float value) { pitchLowDataChanged (value); };
    hiHatProperties.onPitchHighChange = [this] (float value) { pitchHighDataChanged (value); };
    hiHatProperties.onEnvelopeMaxReleaseChange = [this] (float value) { envelopeMaxReleaseDataChanged (value); };
    hiHatProperties.onChokeReleaseChange = [this] (float value) { chokeReleaseDataChanged (value); };
    hiHatProperties.onClsdReleaseModeChange = [this] (int value) { clsdReleaseModeDataChanged (value); };
    hiHatProperties.onClsdRelOfstScaleChange = [this] (float value) { clsdRelOfstScaleDataChanged (value); };
    hiHatProperties.onClsdMaxReleaseChange = [this] (float value) { clsdMaxReleaseDataChanged (value); };
    hiHatProperties.onAccClRelModChange = [this] (float value) { accClRelModDataChanged (value); };
    hiHatProperties.onAccOpRelModChange = [this] (float value) { accOpRelModDataChanged (value); };
    hiHatProperties.onAccClAmpModChange = [this] (float value) { accClAmpModDataChanged (value); };
    hiHatProperties.onAccOpAmpModChange = [this] (float value) { accOpAmpModDataChanged (value); };
    hiHatProperties.onFeelAttackModChange = [this] (float value) { feelAttackModDataChanged (value); };
    hiHatProperties.onFeelReleaseModChange = [this] (float value) { feelReleaseModDataChanged (value); };
    hiHatProperties.onFeelAmpModChange = [this] (float value) { feelAmpModDataChanged (value); };
    hiHatProperties.onFxCvUnipolarChange = [this] (int value) { fxCvUnipolarDataChanged (value); };
    hiHatProperties.onVelocityUnipolarChange = [this] (int value) { velocityUnipolarDataChanged (value); };
    hiHatProperties.onCvDisableVelocityChange = [this] (int value) { cvDisableVelocityDataChanged (value); };
    hiHatProperties.onCvDisableFxChange = [this] (int value) { cvDisableFxDataChanged (value); };
    hiHatProperties.onGateModeChange = [this] (int value) { gateModeDataChanged (value); };
    hiHatProperties.onKnobPosTakeupChange = [this] (int value) { knobPosTakeupDataChanged (value); };
    hiHatProperties.onFltrHpfMinFreqChange = [this] (int value) { fltrHpfMinFreqDataChanged (value); };
    hiHatProperties.onFltrHpfMaxFreqChange = [this] (int value) { fltrHpfMaxFreqDataChanged (value); };
    hiHatProperties.onFltrLpfMinFreqChange = [this] (int value) { fltrLpfMinFreqDataChanged (value); };
    hiHatProperties.onFltrLpfMaxFreqChange = [this] (int value) { fltrLpfMaxFreqDataChanged (value); };
    hiHatProperties.onFltrHpfQChange = [this] (float value) { fltrHpfQDataChanged (value); };
    hiHatProperties.onFltrLpfQChange = [this] (float value) { fltrLpfQDataChanged (value); };
    hiHatProperties.onFxDjfilterHpfMinChange = [this] (int value) { fxDjfilterHpfMinDataChanged (value); };
    hiHatProperties.onFxDjfilterHpfMaxChange = [this] (int value) { fxDjfilterHpfMaxDataChanged (value); };
    hiHatProperties.onFxDjfilterLpfMinChange = [this] (int value) { fxDjfilterLpfMinDataChanged (value); };
    hiHatProperties.onFxDjfilterLpfMaxChange = [this] (int value) { fxDjfilterLpfMaxDataChanged (value); };
    hiHatProperties.onFxDjfilterQMinChange = [this] (float value) { fxDjfilterQMinDataChanged (value); };
    hiHatProperties.onFxDjfilterQMaxChange = [this] (float value) { fxDjfilterQMaxDataChanged (value); };
    hiHatProperties.onFxDjfilterQGainReductionChange = [this] (float value) { fxDjfilterQGainReductionDataChanged (value); };
    hiHatProperties.onFxDubEchoTminChange = [this] (int value) { fxDubEchoTminDataChanged (value); };
    hiHatProperties.onFxDubEchoHpfChange = [this] (int value) { fxDubEchoHpfDataChanged (value); };
    hiHatProperties.onFxDubEchoLpfChange = [this] (int value) { fxDubEchoLpfDataChanged (value); };
    hiHatProperties.onFxDubEchoMixChange = [this] (float value) { fxDubEchoMixDataChanged (value); };
    hiHatProperties.onFxChorusCenterChange = [this] (float value) { fxChorusCenterDataChanged (value); };
    hiHatProperties.onFxChorusDepthChange = [this] (float value) { fxChorusDepthDataChanged (value); };
    hiHatProperties.onFxChorusMixChange = [this] (float value) { fxChorusMixDataChanged (value); };
    hiHatProperties.onFxChorusSpreadChange = [this] (float value) { fxChorusSpreadDataChanged (value); };
    hiHatProperties.onFxChorusTapsChange = [this] (int value) { fxChorusTapsDataChanged (value); };
    hiHatProperties.onFxChorusLfoBChange = [this] (float value) { fxChorusLfoBDataChanged (value); };
    hiHatProperties.onFxChorusLfoTChange = [this] (int value) { fxChorusLfoTDataChanged (value); };
    hiHatProperties.onFxReverbLpfChange = [this] (int value) { fxReverbLpfDataChanged (value); };
    hiHatProperties.onFxReverbHpfChange = [this] (int value) { fxReverbHpfDataChanged (value); };
    hiHatProperties.onFxGlitchProbabilityMinChange = [this] (float value) { fxGlitchProbabilityMinDataChanged (value); };
    hiHatProperties.onFxGlitchProbabilityMaxChange = [this] (float value) { fxGlitchProbabilityMaxDataChanged (value); };
    hiHatProperties.onFxGlitchWeightHoldLowChange = [this] (float value) { fxGlitchWeightHoldLowDataChanged (value); };
    hiHatProperties.onFxGlitchWeightStutterLowChange = [this] (float value) { fxGlitchWeightStutterLowDataChanged (value); };
    hiHatProperties.onFxGlitchWeightCrushLowChange = [this] (float value) { fxGlitchWeightCrushLowDataChanged (value); };
    hiHatProperties.onFxGlitchWeightDropLowChange = [this] (float value) { fxGlitchWeightDropLowDataChanged (value); };
    hiHatProperties.onFxGlitchWeightHoldHighChange = [this] (float value) { fxGlitchWeightHoldHighDataChanged (value); };
    hiHatProperties.onFxGlitchWeightStutterHighChange = [this] (float value) { fxGlitchWeightStutterHighDataChanged (value); };
    hiHatProperties.onFxGlitchWeightCrushHighChange = [this] (float value) { fxGlitchWeightCrushHighDataChanged (value); };
    hiHatProperties.onFxGlitchWeightDropHighChange = [this] (float value) { fxGlitchWeightDropHighDataChanged (value); };
    hiHatProperties.onFxGlitchDropKeepLevelMinChange = [this] (float value) { fxGlitchDropKeepLevelMinDataChanged (value); };
    hiHatProperties.onFxGlitchDropKeepLevelMaxChange = [this] (float value) { fxGlitchDropKeepLevelMaxDataChanged (value); };
    hiHatProperties.onFxGlitchDropKeepTimeMinChange = [this] (float value) { fxGlitchDropKeepTimeMinDataChanged (value); };
    hiHatProperties.onFxGlitchDropKeepTimeMaxChange = [this] (float value) { fxGlitchDropKeepTimeMaxDataChanged (value); };
    hiHatProperties.onFxGlitchCrushTimeMinChange = [this] (float value) { fxGlitchCrushTimeMinDataChanged (value); };
    hiHatProperties.onFxGlitchCrushTimeMaxChange = [this] (float value) { fxGlitchCrushTimeMaxDataChanged (value); };
    hiHatProperties.onFxGlitchMicroloopSmplTMinChange = [this] (float value) { fxGlitchMicroloopSmplTMinDataChanged (value); };
    hiHatProperties.onFxGlitchMicroloopSmplTMaxChange = [this] (float value) { fxGlitchMicroloopSmplTMaxDataChanged (value); };
    hiHatProperties.onFxGlitchMicroloopPlayTMinChange = [this] (float value) { fxGlitchMicroloopPlayTMinDataChanged (value); };
    hiHatProperties.onFxGlitchMicroloopPlayTMaxChange = [this] (float value) { fxGlitchMicroloopPlayTMaxDataChanged (value); };
    hiHatProperties.onFxGlitchStutterSmplTMinChange = [this] (float value) { fxGlitchStutterSmplTMinDataChanged (value); };
    hiHatProperties.onFxGlitchStutterSmplTMaxChange = [this] (float value) { fxGlitchStutterSmplTMaxDataChanged (value); };
    hiHatProperties.onFxGlitchStutterNumMinChange = [this] (int value) { fxGlitchStutterNumMinDataChanged (value); };
    hiHatProperties.onFxGlitchStutterNumMaxChange = [this] (int value) { fxGlitchStutterNumMaxDataChanged (value); };
    hiHatProperties.onFxGlitchStutterWindowChange = [this] (int value) { fxGlitchStutterWindowDataChanged (value); };
}

void HiHatEditorComponent::pitchLowDataChanged (float value)
{
    pitchLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::pitchLowUiChanged (float value)
{
    hiHatProperties.setPitchLow (value, false);
}

void HiHatEditorComponent::pitchHighDataChanged (float value)
{
    pitchHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::pitchHighUiChanged (float value)
{
    hiHatProperties.setPitchHigh (value, false);
}

void HiHatEditorComponent::envelopeMaxReleaseDataChanged (float value)
{
    envelopeMaxReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::envelopeMaxReleaseUiChanged (float value)
{
    hiHatProperties.setEnvelopeMaxRelease (value, false);
}

void HiHatEditorComponent::chokeReleaseDataChanged (float value)
{
    chokeReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::chokeReleaseUiChanged (float value)
{
    hiHatProperties.setChokeRelease (value, false);
}

void HiHatEditorComponent::clsdReleaseModeDataChanged (int value)
{
    clsdReleaseModeEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::clsdReleaseModeUiChanged (int value)
{
    hiHatProperties.setClsdReleaseMode (value, false);
}

void HiHatEditorComponent::clsdRelOfstScaleDataChanged (float value)
{
    clsdRelOfstScaleEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::clsdRelOfstScaleUiChanged (float value)
{
    hiHatProperties.setClsdRelOfstScale (value, false);
}

void HiHatEditorComponent::clsdMaxReleaseDataChanged (float value)
{
    clsdMaxReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::clsdMaxReleaseUiChanged (float value)
{
    hiHatProperties.setClsdMaxRelease (value, false);
}

void HiHatEditorComponent::accClRelModDataChanged (float value)
{
    accClRelModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::accClRelModUiChanged (float value)
{
    hiHatProperties.setAccClRelMod (value, false);
}

void HiHatEditorComponent::accOpRelModDataChanged (float value)
{
    accOpRelModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::accOpRelModUiChanged (float value)
{
    hiHatProperties.setAccOpRelMod (value, false);
}

void HiHatEditorComponent::accClAmpModDataChanged (float value)
{
    accClAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::accClAmpModUiChanged (float value)
{
    hiHatProperties.setAccClAmpMod (value, false);
}

void HiHatEditorComponent::accOpAmpModDataChanged (float value)
{
    accOpAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::accOpAmpModUiChanged (float value)
{
    hiHatProperties.setAccOpAmpMod (value, false);
}

void HiHatEditorComponent::feelAttackModDataChanged (float value)
{
    feelAttackModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::feelAttackModUiChanged (float value)
{
    hiHatProperties.setFeelAttackMod (value, false);
}

void HiHatEditorComponent::feelReleaseModDataChanged (float value)
{
    feelReleaseModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::feelReleaseModUiChanged (float value)
{
    hiHatProperties.setFeelReleaseMod (value, false);
}

void HiHatEditorComponent::feelAmpModDataChanged (float value)
{
    feelAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::feelAmpModUiChanged (float value)
{
    hiHatProperties.setFeelAmpMod (value, false);
}

void HiHatEditorComponent::fxCvUnipolarDataChanged (int value)
{
    fxCvUnipolarEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::fxCvUnipolarUiChanged (int value)
{
    hiHatProperties.setFxCvUnipolar (value, false);
}

void HiHatEditorComponent::velocityUnipolarDataChanged (int value)
{
    velocityUnipolarEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::velocityUnipolarUiChanged (int value)
{
    hiHatProperties.setVelocityUnipolar (value, false);
}

void HiHatEditorComponent::cvDisableVelocityDataChanged (int value)
{
    cvDisableVelocityEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::cvDisableVelocityUiChanged (int value)
{
    hiHatProperties.setCvDisableVelocity (value, false);
}

void HiHatEditorComponent::cvDisableFxDataChanged (int value)
{
    cvDisableFxEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::cvDisableFxUiChanged (int value)
{
    hiHatProperties.setCvDisableFx (value, false);
}

void HiHatEditorComponent::gateModeDataChanged (int value)
{
    gateModeEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::gateModeUiChanged (int value)
{
    hiHatProperties.setGateMode (value, false);
}

void HiHatEditorComponent::knobPosTakeupDataChanged (int value)
{
    knobPosTakeupEditor.setSelectedId (value + 1);
}

void HiHatEditorComponent::knobPosTakeupUiChanged (int value)
{
    hiHatProperties.setKnobPosTakeup (value, false);
}

void HiHatEditorComponent::fltrHpfMinFreqDataChanged (int value)
{
    fltrHpfMinFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fltrHpfMinFreqUiChanged (int value)
{
    hiHatProperties.setFltrHpfMinFreq (value, false);
}

void HiHatEditorComponent::fltrHpfMaxFreqDataChanged (int value)
{
    fltrHpfMaxFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fltrHpfMaxFreqUiChanged (int value)
{
    hiHatProperties.setFltrHpfMaxFreq (value, false);
}

void HiHatEditorComponent::fltrLpfMinFreqDataChanged (int value)
{
    fltrLpfMinFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fltrLpfMinFreqUiChanged (int value)
{
    hiHatProperties.setFltrLpfMinFreq (value, false);
}

void HiHatEditorComponent::fltrLpfMaxFreqDataChanged (int value)
{
    fltrLpfMaxFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fltrLpfMaxFreqUiChanged (int value)
{
    hiHatProperties.setFltrLpfMaxFreq (value, false);
}

void HiHatEditorComponent::fltrHpfQDataChanged (float value)
{
    fltrHpfQEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fltrHpfQUiChanged (float value)
{
    hiHatProperties.setFltrHpfQ (value, false);
}

void HiHatEditorComponent::fltrLpfQDataChanged (float value)
{
    fltrLpfQEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fltrLpfQUiChanged (float value)
{
    hiHatProperties.setFltrLpfQ (value, false);
}

void HiHatEditorComponent::fxDjfilterHpfMinDataChanged (int value)
{
    fxDjfilterHpfMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterHpfMinUiChanged (int value)
{
    hiHatProperties.setFxDjfilterHpfMin (value, false);
}

void HiHatEditorComponent::fxDjfilterHpfMaxDataChanged (int value)
{
    fxDjfilterHpfMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterHpfMaxUiChanged (int value)
{
    hiHatProperties.setFxDjfilterHpfMax (value, false);
}

void HiHatEditorComponent::fxDjfilterLpfMinDataChanged (int value)
{
    fxDjfilterLpfMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterLpfMinUiChanged (int value)
{
    hiHatProperties.setFxDjfilterLpfMin (value, false);
}

void HiHatEditorComponent::fxDjfilterLpfMaxDataChanged (int value)
{
    fxDjfilterLpfMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterLpfMaxUiChanged (int value)
{
    hiHatProperties.setFxDjfilterLpfMax (value, false);
}

void HiHatEditorComponent::fxDjfilterQMinDataChanged (float value)
{
    fxDjfilterQMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterQMinUiChanged (float value)
{
    hiHatProperties.setFxDjfilterQMin (value, false);
}

void HiHatEditorComponent::fxDjfilterQMaxDataChanged (float value)
{
    fxDjfilterQMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterQMaxUiChanged (float value)
{
    hiHatProperties.setFxDjfilterQMax (value, false);
}

void HiHatEditorComponent::fxDjfilterQGainReductionDataChanged (float value)
{
    fxDjfilterQGainReductionEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDjfilterQGainReductionUiChanged (float value)
{
    hiHatProperties.setFxDjfilterQGainReduction (value, false);
}

void HiHatEditorComponent::fxDubEchoTminDataChanged (int value)
{
    fxDubEchoTminEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDubEchoTminUiChanged (int value)
{
    hiHatProperties.setFxDubEchoTmin (value, false);
}

void HiHatEditorComponent::fxDubEchoHpfDataChanged (int value)
{
    fxDubEchoHpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDubEchoHpfUiChanged (int value)
{
    hiHatProperties.setFxDubEchoHpf (value, false);
}

void HiHatEditorComponent::fxDubEchoLpfDataChanged (int value)
{
    fxDubEchoLpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDubEchoLpfUiChanged (int value)
{
    hiHatProperties.setFxDubEchoLpf (value, false);
}

void HiHatEditorComponent::fxDubEchoMixDataChanged (float value)
{
    fxDubEchoMixEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxDubEchoMixUiChanged (float value)
{
    hiHatProperties.setFxDubEchoMix (value, false);
}

void HiHatEditorComponent::fxChorusCenterDataChanged (float value)
{
    fxChorusCenterEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxChorusCenterUiChanged (float value)
{
    hiHatProperties.setFxChorusCenter (value, false);
}

void HiHatEditorComponent::fxChorusDepthDataChanged (float value)
{
    fxChorusDepthEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxChorusDepthUiChanged (float value)
{
    hiHatProperties.setFxChorusDepth (value, false);
}

void HiHatEditorComponent::fxChorusMixDataChanged (float value)
{
    fxChorusMixEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxChorusMixUiChanged (float value)
{
    hiHatProperties.setFxChorusMix (value, false);
}

void HiHatEditorComponent::fxChorusSpreadDataChanged (float value)
{
    fxChorusSpreadEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxChorusSpreadUiChanged (float value)
{
    hiHatProperties.setFxChorusSpread (value, false);
}

void HiHatEditorComponent::fxChorusTapsDataChanged (int value)
{
    fxChorusTapsEditor.setSelectedId (value);
}

void HiHatEditorComponent::fxChorusTapsUiChanged (int value)
{
    hiHatProperties.setFxChorusTaps (value, false);
}

void HiHatEditorComponent::fxChorusLfoBDataChanged (float value)
{
    fxChorusLfoBEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxChorusLfoBUiChanged (float value)
{
    hiHatProperties.setFxChorusLfoB (value, false);
}

void HiHatEditorComponent::fxChorusLfoTDataChanged (int value)
{
    fxChorusLfoTEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxChorusLfoTUiChanged (int value)
{
    hiHatProperties.setFxChorusLfoT (value, false);
}

void HiHatEditorComponent::fxReverbLpfDataChanged (int value)
{
    fxReverbLpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxReverbLpfUiChanged (int value)
{
    hiHatProperties.setFxReverbLpf (value, false);
}

void HiHatEditorComponent::fxReverbHpfDataChanged (int value)
{
    fxReverbHpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxReverbHpfUiChanged (int value)
{
    hiHatProperties.setFxReverbHpf (value, false);
}

void HiHatEditorComponent::fxGlitchProbabilityMinDataChanged (float value)
{
    fxGlitchProbabilityMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchProbabilityMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchProbabilityMin (value, false);
}

void HiHatEditorComponent::fxGlitchProbabilityMaxDataChanged (float value)
{
    fxGlitchProbabilityMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchProbabilityMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchProbabilityMax (value, false);
}

void HiHatEditorComponent::fxGlitchWeightHoldLowDataChanged (float value)
{
    fxGlitchWeightHoldLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightHoldLowUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightHoldLow (value, false);
}

void HiHatEditorComponent::fxGlitchWeightStutterLowDataChanged (float value)
{
    fxGlitchWeightStutterLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightStutterLowUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightStutterLow (value, false);
}

void HiHatEditorComponent::fxGlitchWeightCrushLowDataChanged (float value)
{
    fxGlitchWeightCrushLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightCrushLowUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightCrushLow (value, false);
}

void HiHatEditorComponent::fxGlitchWeightDropLowDataChanged (float value)
{
    fxGlitchWeightDropLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightDropLowUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightDropLow (value, false);
}

void HiHatEditorComponent::fxGlitchWeightHoldHighDataChanged (float value)
{
    fxGlitchWeightHoldHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightHoldHighUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightHoldHigh (value, false);
}

void HiHatEditorComponent::fxGlitchWeightStutterHighDataChanged (float value)
{
    fxGlitchWeightStutterHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightStutterHighUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightStutterHigh (value, false);
}

void HiHatEditorComponent::fxGlitchWeightCrushHighDataChanged (float value)
{
    fxGlitchWeightCrushHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightCrushHighUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightCrushHigh (value, false);
}

void HiHatEditorComponent::fxGlitchWeightDropHighDataChanged (float value)
{
    fxGlitchWeightDropHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchWeightDropHighUiChanged (float value)
{
    hiHatProperties.setFxGlitchWeightDropHigh (value, false);
}

void HiHatEditorComponent::fxGlitchDropKeepLevelMinDataChanged (float value)
{
    fxGlitchDropKeepLevelMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchDropKeepLevelMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchDropKeepLevelMin (value, false);
}

void HiHatEditorComponent::fxGlitchDropKeepLevelMaxDataChanged (float value)
{
    fxGlitchDropKeepLevelMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchDropKeepLevelMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchDropKeepLevelMax (value, false);
}

void HiHatEditorComponent::fxGlitchDropKeepTimeMinDataChanged (float value)
{
    fxGlitchDropKeepTimeMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchDropKeepTimeMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchDropKeepTimeMin (value, false);
}

void HiHatEditorComponent::fxGlitchDropKeepTimeMaxDataChanged (float value)
{
    fxGlitchDropKeepTimeMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchDropKeepTimeMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchDropKeepTimeMax (value, false);
}

void HiHatEditorComponent::fxGlitchCrushTimeMinDataChanged (float value)
{
    fxGlitchCrushTimeMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchCrushTimeMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchCrushTimeMin (value, false);
}

void HiHatEditorComponent::fxGlitchCrushTimeMaxDataChanged (float value)
{
    fxGlitchCrushTimeMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchCrushTimeMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchCrushTimeMax (value, false);
}

void HiHatEditorComponent::fxGlitchMicroloopSmplTMinDataChanged (float value)
{
    fxGlitchMicroloopSmplTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchMicroloopSmplTMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchMicroloopSmplTMin (value, false);
}

void HiHatEditorComponent::fxGlitchMicroloopSmplTMaxDataChanged (float value)
{
    fxGlitchMicroloopSmplTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchMicroloopSmplTMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchMicroloopSmplTMax (value, false);
}

void HiHatEditorComponent::fxGlitchMicroloopPlayTMinDataChanged (float value)
{
    fxGlitchMicroloopPlayTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchMicroloopPlayTMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchMicroloopPlayTMin (value, false);
}

void HiHatEditorComponent::fxGlitchMicroloopPlayTMaxDataChanged (float value)
{
    fxGlitchMicroloopPlayTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchMicroloopPlayTMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchMicroloopPlayTMax (value, false);
}

void HiHatEditorComponent::fxGlitchStutterSmplTMinDataChanged (float value)
{
    fxGlitchStutterSmplTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchStutterSmplTMinUiChanged (float value)
{
    hiHatProperties.setFxGlitchStutterSmplTMin (value, false);
}

void HiHatEditorComponent::fxGlitchStutterSmplTMaxDataChanged (float value)
{
    fxGlitchStutterSmplTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchStutterSmplTMaxUiChanged (float value)
{
    hiHatProperties.setFxGlitchStutterSmplTMax (value, false);
}

void HiHatEditorComponent::fxGlitchStutterNumMinDataChanged (int value)
{
    fxGlitchStutterNumMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchStutterNumMinUiChanged (int value)
{
    hiHatProperties.setFxGlitchStutterNumMin (value, false);
}

void HiHatEditorComponent::fxGlitchStutterNumMaxDataChanged (int value)
{
    fxGlitchStutterNumMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchStutterNumMaxUiChanged (int value)
{
    hiHatProperties.setFxGlitchStutterNumMax (value, false);
}

void HiHatEditorComponent::fxGlitchStutterWindowDataChanged (int value)
{
    fxGlitchStutterWindowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxGlitchStutterWindowUiChanged (int value)
{
    hiHatProperties.setFxGlitchStutterWindow (value, false);
}

void HiHatEditorComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void HiHatEditorComponent::resized ()
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
        { &clsdReleaseModeEditor, &clsdReleaseModeLabel },
        { &cvDisableFxEditor, &cvDisableFxLabel },
        { &cvDisableVelocityEditor, &cvDisableVelocityLabel },
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
        { &fxChorusTapsEditor, &fxChorusTapsLabel },
        { &fxCvUnipolarEditor, &fxCvUnipolarLabel },
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
        { &gateModeEditor, &gateModeLabel },
        { &knobPosTakeupEditor, &knobPosTakeupLabel },
        { &pitchHighEditor, &pitchHighLabel },
        { &pitchLowEditor, &pitchLowLabel },
        { &velocityUnipolarEditor, &velocityUnipolarLabel }
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
