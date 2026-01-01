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
    accClAmpModEditor.updateDataCallback = [this] (int value) { accClAmpModUiChanged (value); };
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
        const auto newValue { (hiHatProperties.getAccClAmpMod ()) + (multiplier * direction) };
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
    accClAmpModDataChanged (hiHatProperties.getAccClAmpMod ());
}

void HiHatEditorComponent::initializeCallbacks ()
{
    jassert (hiHatProperties.isValid ());
    hiHatProperties.onAccClAmpModChange = [this] (int value) { accClAmpModDataChanged (value); };
}

void HiHatEditorComponent::accClAmpModDataChanged (int value)
{
    accClAmpModEditor.setText (juce::String (value), juce::NotificationType::dontSendNotification);
}

void HiHatEditorComponent::accClAmpModUiChanged (int value)
{
    hiHatProperties.setAccClAmpMod(value, false);
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
