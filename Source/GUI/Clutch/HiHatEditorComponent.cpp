#include "HiHatEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

HiHatEditorComponent::HiHatEditorComponent ()
{
    auto D { 0 };
    auto C { 0 };
    auto I { 0 };

    auto setupDoubleEditor = [this, &D] (CustomTextEditorDouble& editor,
                                     juce::Label& label,
                                     const juce::String& labelText)
    {
        label.setText (labelText, juce::dontSendNotification);
        addAndMakeVisible (label);
        addAndMakeVisible (editor);
        editor.setText ("D" + juce::String (D), false);
        D++;
    };
    auto setupIntEditor = [this, &I] (CustomTextEditorInt& editor,
                                 juce::Label& label,
                                 const juce::String& labelText)
    {
        label.setText (labelText, juce::dontSendNotification);
        addAndMakeVisible (label);
        addAndMakeVisible (editor);
        editor.setText ("I" + juce::String (I), false);
        I++;
    };
    auto setupComboBox = [this, &C] (CustomComboBox& comboBox,
                                 juce::Label& label,
                                 const juce::String& labelText)
    {
        label.setText (labelText, juce::dontSendNotification);
        addAndMakeVisible (label);
        addAndMakeVisible (comboBox);
        comboBox.setText ("C" + juce::String (C), false);
        C++;
    };

    accClAmpModEditor.setTooltip ("Amp Mod CLOSED ACC hit");
    accClAmpModEditor.getMinValueCallback = [this] () { return 0.1; };
    accClAmpModEditor.getMaxValueCallback = [this] () { return 10.0; };
    accClAmpModEditor.toStringCallback = [this] (double value) { return juce::String (value, 4); };
    accClAmpModEditor.updateDataCallback = [this] (double value) { accClAmpModUiChanged (value); };
    accClAmpModEditor.onDragCallback = [this] (DragSpeed dragSpeed, int direction)
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

    setupDoubleEditor (accClRelModEditor, accClRelModLabel, "Acc Cl Rel Mod");
    setupDoubleEditor (accOpAmpModEditor, accOpAmpModLabel, "Acc Op Amp Mod");
    setupDoubleEditor (accOpRelModEditor, accOpRelModLabel, "Acc Op Rel Mod");
    setupDoubleEditor (chokeReleaseEditor, chokeReleaseLabel, "Choke Release");
    setupDoubleEditor (clsdMaxReleaseEditor, clsdMaxReleaseLabel, "Clsd Max Release");
    setupDoubleEditor (clsdRelOfstScaleEditor, clsdRelOfstScaleLabel, "Clsd Rel Ofst Scale");
    setupComboBox (clsdReleaseModeEditor, clsdReleaseModeLabel, "Clsd Release Mode");
    setupComboBox (cvDisableFxEditor, cvDisableFxLabel, "CV Disable FX");
    setupComboBox (cvDisableVelocityEditor, cvDisableVelocityLabel, "CV Disable Velocity");
    setupDoubleEditor (envelopeMaxReleaseEditor, envelopeMaxReleaseLabel, "Envelope Max Release");
    setupDoubleEditor (feelAmpModEditor, feelAmpModLabel, "Feel Amp Mod");
    setupDoubleEditor (feelAttackModEditor, feelAttackModLabel, "Feel Attack Mod");
    setupDoubleEditor (feelReleaseModEditor, feelReleaseModLabel, "Feel Release Mod");
    setupIntEditor (fltrHpfMaxFreqEditor, fltrHpfMaxFreqLabel, "Fltr HPF Max Freq");
    setupIntEditor (fltrHpfMinFreqEditor, fltrHpfMinFreqLabel, "Fltr HPF Min Freq");
    setupDoubleEditor (fltrHpfQEditor, fltrHpfQLabel, "Fltr HPF Q");
    setupIntEditor (fltrLpfMaxFreqEditor, fltrLpfMaxFreqLabel, "Fltr LPF Max Freq");
    setupIntEditor (fltrLpfMinFreqEditor, fltrLpfMinFreqLabel, "Fltr LPF Min Freq");
    setupDoubleEditor (fltrLpfQEditor, fltrLpfQLabel, "Fltr LPF Q");
    setupDoubleEditor (fxChorusCenterEditor, fxChorusCenterLabel, "FX Chorus Center");
    setupDoubleEditor (fxChorusDepthEditor, fxChorusDepthLabel, "FX Chorus Depth");
    setupDoubleEditor (fxChorusLfoBEditor, fxChorusLfoBLabel, "FX Chorus LFO B");
    setupIntEditor (fxChorusLfoTEditor, fxChorusLfoTLabel, "FX Chorus LFO T");
    setupDoubleEditor (fxChorusMixEditor, fxChorusMixLabel, "FX Chorus Mix");
    setupDoubleEditor (fxChorusSpreadEditor, fxChorusSpreadLabel, "FX Chorus Spread");
    setupComboBox (fxChorusTapsEditor, fxChorusTapsLabel, "FX Chorus Taps");
    setupComboBox (fxCvUnipolarEditor, fxCvUnipolarLabel, "FX CV Unipolar");
    setupIntEditor (fxDjfilterHpfMaxEditor, fxDjfilterHpfMaxLabel, "FX DJ Filter HPF Max");
    setupIntEditor (fxDjfilterHpfMinEditor, fxDjfilterHpfMinLabel, "FX DJ Filter HPF Min");
    setupIntEditor (fxDjfilterLpfMaxEditor, fxDjfilterLpfMaxLabel, "FX DJ Filter LPF Max");
    setupIntEditor (fxDjfilterLpfMinEditor, fxDjfilterLpfMinLabel, "FX DJ Filter LPF Min");
    setupDoubleEditor (fxDjfilterQGainReductionEditor, fxDjfilterQGainReductionLabel, "FX DJ Filter Q Gain Reduction");
    setupDoubleEditor (fxDjfilterQMaxEditor, fxDjfilterQMaxLabel, "FX DJ Filter Q Max");
    setupDoubleEditor (fxDjfilterQMinEditor, fxDjfilterQMinLabel, "FX DJ Filter Q Min");
    setupIntEditor (fxDubEchoHpfEditor, fxDubEchoHpfLabel, "FX Dub Echo HPF");
    setupIntEditor (fxDubEchoLpfEditor, fxDubEchoLpfLabel, "FX Dub Echo LPF");
    setupDoubleEditor (fxDubEchoMixEditor, fxDubEchoMixLabel, "FX Dub Echo Mix");
    setupIntEditor (fxDubEchoTminEditor, fxDubEchoTminLabel, "FX Dub Echo Tmin");
    setupDoubleEditor (fxGlitchCrushTimeMaxEditor, fxGlitchCrushTimeMaxLabel, "FX Glitch Crush Time Max");
    setupDoubleEditor (fxGlitchCrushTimeMinEditor, fxGlitchCrushTimeMinLabel, "FX Glitch Crush Time Min");
    setupDoubleEditor (fxGlitchDropKeepLevelMaxEditor, fxGlitchDropKeepLevelMaxLabel, "FX Glitch Drop Keep Level Max");
    setupDoubleEditor (fxGlitchDropKeepLevelMinEditor, fxGlitchDropKeepLevelMinLabel, "FX Glitch Drop Keep Level Min");
    setupDoubleEditor (fxGlitchDropKeepTimeMaxEditor, fxGlitchDropKeepTimeMaxLabel, "FX Glitch Drop Keep Time Max");
    setupDoubleEditor (fxGlitchDropKeepTimeMinEditor, fxGlitchDropKeepTimeMinLabel, "FX Glitch Drop Keep Time Min");
    setupDoubleEditor (fxGlitchMicroloopPlayTMaxEditor, fxGlitchMicroloopPlayTMaxLabel, "FX Glitch Microloop Play T Max");
    setupDoubleEditor (fxGlitchMicroloopPlayTMinEditor, fxGlitchMicroloopPlayTMinLabel, "FX Glitch Microloop Play T Min");
    setupDoubleEditor (fxGlitchMicroloopSmplTMaxEditor, fxGlitchMicroloopSmplTMaxLabel, "FX Glitch Microloop Smpl T Max");
    setupDoubleEditor (fxGlitchMicroloopSmplTMinEditor, fxGlitchMicroloopSmplTMinLabel, "FX Glitch Microloop Smpl T Min");
    setupDoubleEditor (fxGlitchProbabilityMaxEditor, fxGlitchProbabilityMaxLabel, "FX Glitch Probability Max");
    setupDoubleEditor (fxGlitchProbabilityMinEditor, fxGlitchProbabilityMinLabel, "FX Glitch Probability Min");
    setupIntEditor (fxGlitchStutterNumMaxEditor, fxGlitchStutterNumMaxLabel, "FX Glitch Stutter Num Max");
    setupIntEditor (fxGlitchStutterNumMinEditor, fxGlitchStutterNumMinLabel, "FX Glitch Stutter Num Min");
    setupDoubleEditor (fxGlitchStutterSmplTMaxEditor, fxGlitchStutterSmplTMaxLabel, "FX Glitch Stutter Smpl T Max");
    setupDoubleEditor (fxGlitchStutterSmplTMinEditor, fxGlitchStutterSmplTMinLabel, "FX Glitch Stutter Smpl T Min");
    setupIntEditor (fxGlitchStutterWindowEditor, fxGlitchStutterWindowLabel, "FX Glitch Stutter Window");
    setupDoubleEditor (fxGlitchWeightCrushLowEditor, fxGlitchWeightCrushLowLabel, "FX Glitch Weight Crush Low");
    setupDoubleEditor (fxGlitchWeightDropHighEditor, fxGlitchWeightDropHighLabel, "FX Glitch Weight Drop High");
    setupDoubleEditor (fxGlitchWeightDropLowEditor, fxGlitchWeightDropLowLabel, "FX Glitch Weight Drop Low");
    setupDoubleEditor (fxGlitchWeightHoldHighEditor, fxGlitchWeightHoldHighLabel, "FX Glitch Weight Hold High");
    setupDoubleEditor (fxGlitchWeightHoldLowEditor, fxGlitchWeightHoldLowLabel, "FX Glitch Weight Hold Low");
    setupDoubleEditor (fxGlitchWeightStutterHighEditor, fxGlitchWeightStutterHighLabel, "FX Glitch Weight Stutter High");
    setupDoubleEditor (fxGlitchWeightStutterLowEditor, fxGlitchWeightStutterLowLabel, "FX Glitch Weight Stutter Low");
    setupIntEditor (fxReverbHpfEditor, fxReverbHpfLabel, "FX Reverb HPF");
    setupIntEditor (fxReverbLpfEditor, fxReverbLpfLabel, "FX Reverb LPF");
    setupComboBox (gateModeEditor, gateModeLabel, "Gate Mode");
    setupComboBox (knobPosTakeupEditor, knobPosTakeupLabel, "Knob Pos Takeup");
    setupDoubleEditor (pitchHighEditor, pitchHighLabel, "Pitch High");
    setupDoubleEditor (pitchLowEditor, pitchLowLabel, "Pitch Low");
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
    clsdReleaseModeEditor.setText (juce::String (value), juce::dontSendNotification);
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
    fxCvUnipolarEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::fxCvUnipolarUiChanged (int value)
{
    hiHatProperties.setFxCvUnipolar (value, false);
}

void HiHatEditorComponent::velocityUnipolarDataChanged (int value)
{
    velocityUnipolarEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::velocityUnipolarUiChanged (int value)
{
    hiHatProperties.setVelocityUnipolar (value, false);
}

void HiHatEditorComponent::cvDisableVelocityDataChanged (int value)
{
    cvDisableVelocityEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::cvDisableVelocityUiChanged (int value)
{
    hiHatProperties.setCvDisableVelocity (value, false);
}

void HiHatEditorComponent::cvDisableFxDataChanged (int value)
{
    cvDisableFxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::cvDisableFxUiChanged (int value)
{
    hiHatProperties.setCvDisableFx (value, false);
}

void HiHatEditorComponent::gateModeDataChanged (int value)
{
    gateModeEditor.setText (juce::String (value), juce::dontSendNotification);
}

void HiHatEditorComponent::gateModeUiChanged (int value)
{
    hiHatProperties.setGateMode (value, false);
}

void HiHatEditorComponent::knobPosTakeupDataChanged (int value)
{
    knobPosTakeupEditor.setText (juce::String (value), juce::dontSendNotification);
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
    fxChorusTapsEditor.setText (juce::String (value), juce::dontSendNotification);
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
