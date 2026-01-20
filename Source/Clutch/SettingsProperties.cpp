#include "SettingsProperties.h"

void SettingsProperties::initValueTree ()
{
    // Core
    setPitchLow (0.125f, false);
    setPitchHigh (2.5f, false);
    setEnvelopeMaxRelease (4.0f, false);
    setChokeRelease (0.08f, false);
    setClsdReleaseMode (1, false);
    setClsdRelOfstScale (0.5f, false);
    setClsdMaxRelease (0.8f, false);
    setAccClRelMod (1.18f, false);
    setAccOpRelMod (1.25f, false);
    setAccClAmpMod (1.3f, false);
    setAccOpAmpMod (1.25f, false);

    // CV / control
    setFxCvUnipolar (1, false);
    setVelocityUnipolar (0, false);
    setCvDisableVelocity (0, false);
    setCvDisableFx (0, false);
    setGateMode (0, false);
    setFeelAttackMod (1.0f, false);
    setFeelReleaseMod (1.0f, false);
    setFeelAmpMod (1.0f, false);
    setKnobPosTakeup (1, false);

    // Filters
    setFltrHpfMinFreq (100, false);
    setFltrHpfMaxFreq (14000, false);
    setFltrLpfMinFreq (200, false);
    setFltrLpfMaxFreq (20000, false);
    setFltrHpfQ (1.0f, false);
    setFltrLpfQ (0.707f, false);

    // DJ Filter
    setFxDjfilterHpfMin (100, false);
    setFxDjfilterHpfMax (14000, false);
    setFxDjfilterLpfMin (200, false);
    setFxDjfilterLpfMax (20000, false);
    setFxDjfilterQMin (0.5f, false);
    setFxDjfilterQMax (4.0f, false);
    setFxDjfilterQGainReduction (0.12f, false);

    // Dub Echo
    setFxDubEchoTmin (30, false);
    setFxDubEchoHpf (400, false);
    setFxDubEchoLpf (8400, false);
    setFxDubEchoMix (0.38f, false);

    // Chorus
    setFxChorusCenter (12.0f, false);
    setFxChorusDepth (5.0f, false);
    setFxChorusMix (1.0f, false);
    setFxChorusSpread (0.01f, false);
    setFxChorusTaps (4, false);
    setFxChorusLfoB (0.002f, false);
    setFxChorusLfoT (3, false);

    // Reverb
    setFxReverbLpf (9000, false);
    setFxReverbHpf (700, false);

    // Glitch – probability
    setFxGlitchProbabilityMin (0.00005f, false);
    setFxGlitchProbabilityMax (0.003f, false);

    // Glitch – weights (low)
    setFxGlitchWeightHoldLow (0.15f, false);
    setFxGlitchWeightStutterLow (0.05f, false);
    setFxGlitchWeightCrushLow (0.30f, false);
    setFxGlitchWeightDropLow (0.02f, false);

    // Glitch – weights (high)
    setFxGlitchWeightHoldHigh (0.30f, false);
    setFxGlitchWeightStutterHigh (0.20f, false);
    setFxGlitchWeightCrushHigh (0.20f, false);
    setFxGlitchWeightDropHigh (0.07f, false);

    // Glitch – drop
    setFxGlitchDropKeepLevelMin (0.0f, false);
    setFxGlitchDropKeepLevelMax (0.75f, false);
    setFxGlitchDropKeepTimeMin (4.0f, false);
    setFxGlitchDropKeepTimeMax (40.0f, false);

    // Glitch – crush
    setFxGlitchCrushTimeMin (10.0f, false);
    setFxGlitchCrushTimeMax (50.0f, false);

    // Glitch – microloop
    setFxGlitchMicroloopSmplTMin (0.2f, false);
    setFxGlitchMicroloopSmplTMax (3.0f, false);
    setFxGlitchMicroloopPlayTMin (5.0f, false);
    setFxGlitchMicroloopPlayTMax (15.0f, false);

    // Glitch – stutter
    setFxGlitchStutterSmplTMin (3.0f, false);
    setFxGlitchStutterSmplTMax (10.0f, false);
    setFxGlitchStutterNumMin (2, false);
    setFxGlitchStutterNumMax (5, false);
    setFxGlitchStutterWindow (20, false);
}

void SettingsProperties::setPitchLow (float value, bool includeSelfCallback)
{
    setValue (value, PitchLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setPitchHigh (float value, bool includeSelfCallback)
{
    setValue (value, PitchHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setEnvelopeMaxRelease (float value, bool includeSelfCallback)
{
    setValue (value, EnvelopeMaxReleasePropertyId, includeSelfCallback);
}

void SettingsProperties::setChokeRelease (float value, bool includeSelfCallback)
{
    setValue (value, ChokeReleasePropertyId, includeSelfCallback);
}

void SettingsProperties::setClsdReleaseMode (int value, bool includeSelfCallback)
{
    setValue (value, ClsdReleaseModePropertyId, includeSelfCallback);
}

void SettingsProperties::setClsdRelOfstScale (float value, bool includeSelfCallback)
{
    setValue (value, ClsdRelOfstScalePropertyId, includeSelfCallback);
}

void SettingsProperties::setClsdMaxRelease (float value, bool includeSelfCallback)
{
    setValue (value, ClsdMaxReleasePropertyId, includeSelfCallback);
}

void SettingsProperties::setAccClRelMod (float value, bool includeSelfCallback)
{
    setValue (value, AccClRelModPropertyId, includeSelfCallback);
}

void SettingsProperties::setAccOpRelMod (float value, bool includeSelfCallback)
{
    setValue (value, AccOpRelModPropertyId, includeSelfCallback);
}

void SettingsProperties::setAccClAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, AccClAmpModPropertyId, includeSelfCallback);
}

void SettingsProperties::setAccOpAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, AccOpAmpModPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxCvUnipolar (int value, bool includeSelfCallback)
{
    setValue (value, FxCvUnipolarPropertyId, includeSelfCallback);
}

void SettingsProperties::setVelocityUnipolar (int value, bool includeSelfCallback)
{
    setValue (value, VelocityUnipolarPropertyId, includeSelfCallback);
}

void SettingsProperties::setCvDisableVelocity (int value, bool includeSelfCallback)
{
    setValue (value, CvDisableVelocityPropertyId, includeSelfCallback);
}

void SettingsProperties::setCvDisableFx (int value, bool includeSelfCallback)
{
    setValue (value, CvDisableFxPropertyId, includeSelfCallback);
}

void SettingsProperties::setGateMode (int value, bool includeSelfCallback)
{
    setValue (value, GateModePropertyId, includeSelfCallback);
}

void SettingsProperties::setFeelAttackMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelAttackModPropertyId, includeSelfCallback);
}

void SettingsProperties::setFeelReleaseMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelReleaseModPropertyId, includeSelfCallback);
}

void SettingsProperties::setFeelAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelAmpModPropertyId, includeSelfCallback);
}

void SettingsProperties::setKnobPosTakeup (int value, bool includeSelfCallback)
{
    setValue (value, KnobPosTakeupPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrHpfMinFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrHpfMinFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrHpfMaxFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrHpfMaxFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrLpfMinFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrLpfMinFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrLpfMaxFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrLpfMaxFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrHpfQ (float value, bool includeSelfCallback)
{
    setValue (value, FltrHpfQPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrLpfQ (float value, bool includeSelfCallback)
{
    setValue (value, FltrLpfQPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterHpfMin (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterHpfMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterHpfMax (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterHpfMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterLpfMin (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterLpfMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterLpfMax (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterLpfMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterQMin (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterQMax (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterQGainReduction (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQGainReductionPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDubEchoTmin (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoTminPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDubEchoHpf (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoHpfPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDubEchoLpf (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoLpfPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDubEchoMix (float value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoMixPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusCenter (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusCenterPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusDepth (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusDepthPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusMix (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusMixPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusSpread (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusSpreadPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusTaps (int value, bool includeSelfCallback)
{
    setValue (value, FxChorusTapsPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusLfoB (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusLfoBPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusLfoT (int value, bool includeSelfCallback)
{
    setValue (value, FxChorusLfoTPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbLpf (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbLpfPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbHpf (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbHpfPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchProbabilityMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchProbabilityMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchProbabilityMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchProbabilityMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightHoldLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightHoldLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightStutterLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightStutterLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightCrushLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightCrushLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightDropLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightDropLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightHoldHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightHoldHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightStutterHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightStutterHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightCrushHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightCrushHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightDropHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightDropHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepLevelMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepLevelMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepLevelMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepLevelMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepTimeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepTimeMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepTimeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepTimeMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchCrushTimeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchCrushTimeMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchCrushTimeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchCrushTimeMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopSmplTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopSmplTMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopSmplTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopSmplTMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopPlayTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopPlayTMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopPlayTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopPlayTMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterSmplTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterSmplTMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterSmplTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterSmplTMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterNumMin (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterNumMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterNumMax (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterNumMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterWindow (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterWindowPropertyId, includeSelfCallback);
}

float SettingsProperties::getPitchLow ()
{
    return getValue<float> (PitchLowPropertyId);
}

float SettingsProperties::getPitchHigh ()
{
    return getValue<float> (PitchHighPropertyId);
}

float SettingsProperties::getEnvelopeMaxRelease ()
{
    return getValue<float> (EnvelopeMaxReleasePropertyId);
}

float SettingsProperties::getChokeRelease ()
{
    return getValue<float> (ChokeReleasePropertyId);
}

int SettingsProperties::getClsdReleaseMode ()
{
    return getValue<int> (ClsdReleaseModePropertyId);
}

float SettingsProperties::getClsdRelOfstScale ()
{
    return getValue<float> (ClsdRelOfstScalePropertyId);
}

float SettingsProperties::getClsdMaxRelease ()
{
    return getValue<float> (ClsdMaxReleasePropertyId);
}

float SettingsProperties::getAccClRelMod ()
{
    return getValue<float> (AccClRelModPropertyId);
}

float SettingsProperties::getAccOpRelMod ()
{
    return getValue<float> (AccOpRelModPropertyId);
}

float SettingsProperties::getAccClAmpMod ()
{
    return getValue<float> (AccClAmpModPropertyId);
}

float SettingsProperties::getAccOpAmpMod ()
{
    return getValue<float> (AccOpAmpModPropertyId);
}

int SettingsProperties::getFxCvUnipolar ()
{
    return getValue<int> (FxCvUnipolarPropertyId);
}

int SettingsProperties::getVelocityUnipolar ()
{
    return getValue<int> (VelocityUnipolarPropertyId);
}

int SettingsProperties::getCvDisableVelocity ()
{
    return getValue<int> (CvDisableVelocityPropertyId);
}

int SettingsProperties::getCvDisableFx ()
{
    return getValue<int> (CvDisableFxPropertyId);
}

int SettingsProperties::getGateMode ()
{
    return getValue<int> (GateModePropertyId);
}

float SettingsProperties::getFeelAttackMod ()
{
    return getValue<float> (FeelAttackModPropertyId);
}

float SettingsProperties::getFeelReleaseMod ()
{
    return getValue<float> (FeelReleaseModPropertyId);
}

float SettingsProperties::getFeelAmpMod ()
{
    return getValue<float> (FeelAmpModPropertyId);
}

int SettingsProperties::getKnobPosTakeup ()
{
    return getValue<int> (KnobPosTakeupPropertyId);
}

int SettingsProperties::getFltrHpfMinFreq ()
{
    return getValue<int> (FltrHpfMinFreqPropertyId);
}

int SettingsProperties::getFltrHpfMaxFreq ()
{
    return getValue<int> (FltrHpfMaxFreqPropertyId);
}

int SettingsProperties::getFltrLpfMinFreq ()
{
    return getValue<int> (FltrLpfMinFreqPropertyId);
}

int SettingsProperties::getFltrLpfMaxFreq ()
{
    return getValue<int> (FltrLpfMaxFreqPropertyId);
}

float SettingsProperties::getFltrHpfQ ()
{
    return getValue<float> (FltrHpfQPropertyId);
}

float SettingsProperties::getFltrLpfQ ()
{
    return getValue<float> (FltrLpfQPropertyId);
}

int SettingsProperties::getFxDjfilterHpfMin ()
{
    return getValue<int> (FxDjfilterHpfMinPropertyId);
}

int SettingsProperties::getFxDjfilterHpfMax ()
{
    return getValue<int> (FxDjfilterHpfMaxPropertyId);
}

int SettingsProperties::getFxDjfilterLpfMin ()
{
    return getValue<int> (FxDjfilterLpfMinPropertyId);
}

int SettingsProperties::getFxDjfilterLpfMax ()
{
    return getValue<int> (FxDjfilterLpfMaxPropertyId);
}

float SettingsProperties::getFxDjfilterQMin ()
{
    return getValue<float> (FxDjfilterQMinPropertyId);
}

float SettingsProperties::getFxDjfilterQMax ()
{
    return getValue<float> (FxDjfilterQMaxPropertyId);
}

float SettingsProperties::getFxDjfilterQGainReduction ()
{
    return getValue<float> (FxDjfilterQGainReductionPropertyId);
}

int SettingsProperties::getFxDubEchoTmin ()
{
    return getValue<int> (FxDubEchoTminPropertyId);
}

int SettingsProperties::getFxDubEchoHpf ()
{
    return getValue<int> (FxDubEchoHpfPropertyId);
}

int SettingsProperties::getFxDubEchoLpf ()
{
    return getValue<int> (FxDubEchoLpfPropertyId);
}

float SettingsProperties::getFxDubEchoMix ()
{
    return getValue<float> (FxDubEchoMixPropertyId);
}

float SettingsProperties::getFxChorusCenter ()
{
    return getValue<float> (FxChorusCenterPropertyId);
}

float SettingsProperties::getFxChorusDepth ()
{
    return getValue<float> (FxChorusDepthPropertyId);
}

float SettingsProperties::getFxChorusMix ()
{
    return getValue<float> (FxChorusMixPropertyId);
}

float SettingsProperties::getFxChorusSpread ()
{
    return getValue<float> (FxChorusSpreadPropertyId);
}

int SettingsProperties::getFxChorusTaps ()
{
    return getValue<int> (FxChorusTapsPropertyId);
}

float SettingsProperties::getFxChorusLfoB ()
{
    return getValue<float> (FxChorusLfoBPropertyId);
}

int SettingsProperties::getFxChorusLfoT ()
{
    return getValue<int> (FxChorusLfoTPropertyId);
}

int SettingsProperties::getFxReverbLpf ()
{
    return getValue<int> (FxReverbLpfPropertyId);
}

int SettingsProperties::getFxReverbHpf ()
{
    return getValue<int> (FxReverbHpfPropertyId);
}

float SettingsProperties::getFxGlitchProbabilityMin ()
{
    return getValue<float> (FxGlitchProbabilityMinPropertyId);
}

float SettingsProperties::getFxGlitchProbabilityMax ()
{
    return getValue<float> (FxGlitchProbabilityMaxPropertyId);
}

float SettingsProperties::getFxGlitchWeightHoldLow ()
{
    return getValue<float> (FxGlitchWeightHoldLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightStutterLow ()
{
    return getValue<float> (FxGlitchWeightStutterLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightCrushLow ()
{
    return getValue<float> (FxGlitchWeightCrushLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightDropLow ()
{
    return getValue<float> (FxGlitchWeightDropLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightHoldHigh ()
{
    return getValue<float> (FxGlitchWeightHoldHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightStutterHigh ()
{
    return getValue<float> (FxGlitchWeightStutterHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightCrushHigh ()
{
    return getValue<float> (FxGlitchWeightCrushHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightDropHigh ()
{
    return getValue<float> (FxGlitchWeightDropHighPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepLevelMin ()
{
    return getValue<float> (FxGlitchDropKeepLevelMinPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepLevelMax ()
{
    return getValue<float> (FxGlitchDropKeepLevelMaxPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepTimeMin ()
{
    return getValue<float> (FxGlitchDropKeepTimeMinPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepTimeMax ()
{
    return getValue<float> (FxGlitchDropKeepTimeMaxPropertyId);
}

float SettingsProperties::getFxGlitchCrushTimeMin ()
{
    return getValue<float> (FxGlitchCrushTimeMinPropertyId);
}

float SettingsProperties::getFxGlitchCrushTimeMax ()
{
    return getValue<float> (FxGlitchCrushTimeMaxPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopSmplTMin ()
{
    return getValue<float> (FxGlitchMicroloopSmplTMinPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopSmplTMax ()
{
    return getValue<float> (FxGlitchMicroloopSmplTMaxPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopPlayTMin ()
{
    return getValue<float> (FxGlitchMicroloopPlayTMinPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopPlayTMax ()
{
    return getValue<float> (FxGlitchMicroloopPlayTMaxPropertyId);
}

float SettingsProperties::getFxGlitchStutterSmplTMin ()
{
    return getValue<float> (FxGlitchStutterSmplTMinPropertyId);
}

float SettingsProperties::getFxGlitchStutterSmplTMax ()
{
    return getValue<float> (FxGlitchStutterSmplTMaxPropertyId);
}

int SettingsProperties::getFxGlitchStutterNumMin ()
{
    return getValue<int> (FxGlitchStutterNumMinPropertyId);
}

int SettingsProperties::getFxGlitchStutterNumMax ()
{
    return getValue<int> (FxGlitchStutterNumMaxPropertyId);
}

int SettingsProperties::getFxGlitchStutterWindow ()
{
    return getValue<int> (FxGlitchStutterWindowPropertyId);
}

void SettingsProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (data == vt)
    {
        if (property == PitchLowPropertyId)
        {
            if (onPitchLowChange != nullptr)
                onPitchLowChange (getPitchLow ());
        }
        else if (property == PitchHighPropertyId)
        {
            if (onPitchHighChange != nullptr)
                onPitchHighChange (getPitchHigh ());
        }
        else if (property == EnvelopeMaxReleasePropertyId)
        {
            if (onEnvelopeMaxReleaseChange != nullptr)
                onEnvelopeMaxReleaseChange (getEnvelopeMaxRelease ());
        }
        else if (property == ChokeReleasePropertyId)
        {
            if (onChokeReleaseChange != nullptr)
                onChokeReleaseChange (getChokeRelease ());
        }
        else if (property == ClsdReleaseModePropertyId)
        {
            if (onClsdReleaseModeChange != nullptr)
                onClsdReleaseModeChange (getClsdReleaseMode ());
        }
        else if (property == ClsdRelOfstScalePropertyId)
        {
            if (onClsdRelOfstScaleChange != nullptr)
                onClsdRelOfstScaleChange (getClsdRelOfstScale ());
        }
        else if (property == ClsdMaxReleasePropertyId)
        {
            if (onClsdMaxReleaseChange != nullptr)
                onClsdMaxReleaseChange (getClsdMaxRelease ());
        }
        else if (property == AccClRelModPropertyId)
        {
            if (onAccClRelModChange != nullptr)
                onAccClRelModChange (getAccClRelMod ());
        }
        else if (property == AccOpRelModPropertyId)
        {
            if (onAccOpRelModChange != nullptr)
                onAccOpRelModChange (getAccOpRelMod ());
        }
        else if (property == AccClAmpModPropertyId)
        {
            if (onAccClAmpModChange != nullptr)
                onAccClAmpModChange (getAccClAmpMod ());
        }
        else if (property == AccOpAmpModPropertyId)
        {
            if (onAccOpAmpModChange != nullptr)
                onAccOpAmpModChange (getAccOpAmpMod ());
        }
        else if (property == FxCvUnipolarPropertyId)
        {
            if (onFxCvUnipolarChange != nullptr)
                onFxCvUnipolarChange (getFxCvUnipolar ());
        }
        else if (property == VelocityUnipolarPropertyId)
        {
            if (onVelocityUnipolarChange != nullptr)
                onVelocityUnipolarChange (getVelocityUnipolar ());
        }
        else if (property == CvDisableVelocityPropertyId)
        {
            if (onCvDisableVelocityChange != nullptr)
                onCvDisableVelocityChange (getCvDisableVelocity ());
        }
        else if (property == CvDisableFxPropertyId)
        {
            if (onCvDisableFxChange != nullptr)
                onCvDisableFxChange (getCvDisableFx ());
        }
        else if (property == GateModePropertyId)
        {
            if (onGateModeChange != nullptr)
                onGateModeChange (getGateMode ());
        }
        else if (property == FeelAttackModPropertyId)
        {
            if (onFeelAttackModChange != nullptr)
                onFeelAttackModChange (getFeelAttackMod ());
        }
        else if (property == FeelReleaseModPropertyId)
        {
            if (onFeelReleaseModChange != nullptr)
                onFeelReleaseModChange (getFeelReleaseMod ());
        }
        else if (property == FeelAmpModPropertyId)
        {
            if (onFeelAmpModChange != nullptr)
                onFeelAmpModChange (getFeelAmpMod ());
        }
        else if (property == KnobPosTakeupPropertyId)
        {
            if (onKnobPosTakeupChange != nullptr)
                onKnobPosTakeupChange (getKnobPosTakeup ());
        }
        else if (property == FltrHpfMinFreqPropertyId)
        {
            if (onFltrHpfMinFreqChange != nullptr)
                onFltrHpfMinFreqChange (getFltrHpfMinFreq ());
        }
        else if (property == FltrHpfMaxFreqPropertyId)
        {
            if (onFltrHpfMaxFreqChange != nullptr)
                onFltrHpfMaxFreqChange (getFltrHpfMaxFreq ());
        }
        else if (property == FltrLpfMinFreqPropertyId)
        {
            if (onFltrLpfMinFreqChange != nullptr)
                onFltrLpfMinFreqChange (getFltrLpfMinFreq ());
        }
        else if (property == FltrLpfMaxFreqPropertyId)
        {
            if (onFltrLpfMaxFreqChange != nullptr)
                onFltrLpfMaxFreqChange (getFltrLpfMaxFreq ());
        }
        else if (property == FltrHpfQPropertyId)
        {
            if (onFltrHpfQChange != nullptr)
                onFltrHpfQChange (getFltrHpfQ ());
        }
        else if (property == FltrLpfQPropertyId)
        {
            if (onFltrLpfQChange != nullptr)
                onFltrLpfQChange (getFltrLpfQ ());
        }
        else if (property == FxDjfilterHpfMinPropertyId)
        {
            if (onFxDjfilterHpfMinChange != nullptr)
                onFxDjfilterHpfMinChange (getFxDjfilterHpfMin ());
        }
        else if (property == FxDjfilterHpfMaxPropertyId)
        {
            if (onFxDjfilterHpfMaxChange != nullptr)
                onFxDjfilterHpfMaxChange (getFxDjfilterHpfMax ());
        }
        else if (property == FxDjfilterLpfMinPropertyId)
        {
            if (onFxDjfilterLpfMinChange != nullptr)
                onFxDjfilterLpfMinChange (getFxDjfilterLpfMin ());
        }
        else if (property == FxDjfilterLpfMaxPropertyId)
        {
            if (onFxDjfilterLpfMaxChange != nullptr)
                onFxDjfilterLpfMaxChange (getFxDjfilterLpfMax ());
        }
        else if (property == FxDjfilterQMinPropertyId)
        {
            if (onFxDjfilterQMinChange != nullptr)
                onFxDjfilterQMinChange (getFxDjfilterQMin ());
        }
        else if (property == FxDjfilterQMaxPropertyId)
        {
            if (onFxDjfilterQMaxChange != nullptr)
                onFxDjfilterQMaxChange (getFxDjfilterQMax ());
        }
        else if (property == FxDjfilterQGainReductionPropertyId)
        {
            if (onFxDjfilterQGainReductionChange != nullptr)
                onFxDjfilterQGainReductionChange (getFxDjfilterQGainReduction ());
        }
        else if (property == FxDubEchoTminPropertyId)
        {
            if (onFxDubEchoTminChange != nullptr)
                onFxDubEchoTminChange (getFxDubEchoTmin ());
        }
        else if (property == FxDubEchoHpfPropertyId)
        {
            if (onFxDubEchoHpfChange != nullptr)
                onFxDubEchoHpfChange (getFxDubEchoHpf ());
        }
        else if (property == FxDubEchoLpfPropertyId)
        {
            if (onFxDubEchoLpfChange != nullptr)
                onFxDubEchoLpfChange (getFxDubEchoLpf ());
        }
        else if (property == FxDubEchoMixPropertyId)
        {
            if (onFxDubEchoMixChange != nullptr)
                onFxDubEchoMixChange (getFxDubEchoMix ());
        }
        else if (property == FxChorusCenterPropertyId)
        {
            if (onFxChorusCenterChange != nullptr)
                onFxChorusCenterChange (getFxChorusCenter ());
        }
        else if (property == FxChorusDepthPropertyId)
        {
            if (onFxChorusDepthChange != nullptr)
                onFxChorusDepthChange (getFxChorusDepth ());
        }
        else if (property == FxChorusMixPropertyId)
        {
            if (onFxChorusMixChange != nullptr)
                onFxChorusMixChange (getFxChorusMix ());
        }
        else if (property == FxChorusSpreadPropertyId)
        {
            if (onFxChorusSpreadChange != nullptr)
                onFxChorusSpreadChange (getFxChorusSpread ());
        }
        else if (property == FxChorusTapsPropertyId)
        {
            if (onFxChorusTapsChange != nullptr)
                onFxChorusTapsChange (getFxChorusTaps ());
        }
        else if (property == FxChorusLfoBPropertyId)
        {
            if (onFxChorusLfoBChange != nullptr)
                onFxChorusLfoBChange (getFxChorusLfoB ());
        }
        else if (property == FxChorusLfoTPropertyId)
        {
            if (onFxChorusLfoTChange != nullptr)
                onFxChorusLfoTChange (getFxChorusLfoT ());
        }
        else if (property == FxReverbLpfPropertyId)
        {
            if (onFxReverbLpfChange != nullptr)
                onFxReverbLpfChange (getFxReverbLpf ());
        }
        else if (property == FxReverbHpfPropertyId)
        {
            if (onFxReverbHpfChange != nullptr)
                onFxReverbHpfChange (getFxReverbHpf ());
        }
        else if (property == FxGlitchProbabilityMinPropertyId)
        {
            if (onFxGlitchProbabilityMinChange != nullptr)
                onFxGlitchProbabilityMinChange (getFxGlitchProbabilityMin ());
        }
        else if (property == FxGlitchProbabilityMaxPropertyId)
        {
            if (onFxGlitchProbabilityMaxChange != nullptr)
                onFxGlitchProbabilityMaxChange (getFxGlitchProbabilityMax ());
        }
        else if (property == FxGlitchWeightHoldLowPropertyId)
        {
            if (onFxGlitchWeightHoldLowChange != nullptr)
                onFxGlitchWeightHoldLowChange (getFxGlitchWeightHoldLow ());
        }
        else if (property == FxGlitchWeightStutterLowPropertyId)
        {
            if (onFxGlitchWeightStutterLowChange != nullptr)
                onFxGlitchWeightStutterLowChange (getFxGlitchWeightStutterLow ());
        }
        else if (property == FxGlitchWeightCrushLowPropertyId)
        {
            if (onFxGlitchWeightCrushLowChange != nullptr)
                onFxGlitchWeightCrushLowChange (getFxGlitchWeightCrushLow ());
        }
        else if (property == FxGlitchWeightDropLowPropertyId)
        {
            if (onFxGlitchWeightDropLowChange != nullptr)
                onFxGlitchWeightDropLowChange (getFxGlitchWeightDropLow ());
        }
        else if (property == FxGlitchWeightHoldHighPropertyId)
        {
            if (onFxGlitchWeightHoldHighChange != nullptr)
                onFxGlitchWeightHoldHighChange (getFxGlitchWeightHoldHigh ());
        }
        else if (property == FxGlitchWeightStutterHighPropertyId)
        {
            if (onFxGlitchWeightStutterHighChange != nullptr)
                onFxGlitchWeightStutterHighChange (getFxGlitchWeightStutterHigh ());
        }
        else if (property == FxGlitchWeightCrushHighPropertyId)
        {
            if (onFxGlitchWeightCrushHighChange != nullptr)
                onFxGlitchWeightCrushHighChange (getFxGlitchWeightCrushHigh ());
        }
        else if (property == FxGlitchWeightDropHighPropertyId)
        {
            if (onFxGlitchWeightDropHighChange != nullptr)
                onFxGlitchWeightDropHighChange (getFxGlitchWeightDropHigh ());
        }
        else if (property == FxGlitchDropKeepLevelMinPropertyId)
        {
            if (onFxGlitchDropKeepLevelMinChange != nullptr)
                onFxGlitchDropKeepLevelMinChange (getFxGlitchDropKeepLevelMin ());
        }
        else if (property == FxGlitchDropKeepLevelMaxPropertyId)
        {
            if (onFxGlitchDropKeepLevelMaxChange != nullptr)
                onFxGlitchDropKeepLevelMaxChange (getFxGlitchDropKeepLevelMax ());
        }
        else if (property == FxGlitchDropKeepTimeMinPropertyId)
        {
            if (onFxGlitchDropKeepTimeMinChange != nullptr)
                onFxGlitchDropKeepTimeMinChange (getFxGlitchDropKeepTimeMin ());
        }
        else if (property == FxGlitchDropKeepTimeMaxPropertyId)
        {
            if (onFxGlitchDropKeepTimeMaxChange != nullptr)
                onFxGlitchDropKeepTimeMaxChange (getFxGlitchDropKeepTimeMax ());
        }
        else if (property == FxGlitchCrushTimeMinPropertyId)
        {
            if (onFxGlitchCrushTimeMinChange != nullptr)
                onFxGlitchCrushTimeMinChange (getFxGlitchCrushTimeMin ());
        }
        else if (property == FxGlitchCrushTimeMaxPropertyId)
        {
            if (onFxGlitchCrushTimeMaxChange != nullptr)
                onFxGlitchCrushTimeMaxChange (getFxGlitchCrushTimeMax ());
        }
        else if (property == FxGlitchMicroloopSmplTMinPropertyId)
        {
            if (onFxGlitchMicroloopSmplTMinChange != nullptr)
                onFxGlitchMicroloopSmplTMinChange (getFxGlitchMicroloopSmplTMin ());
        }
        else if (property == FxGlitchMicroloopSmplTMaxPropertyId)
        {
            if (onFxGlitchMicroloopSmplTMaxChange != nullptr)
                onFxGlitchMicroloopSmplTMaxChange (getFxGlitchMicroloopSmplTMax ());
        }
        else if (property == FxGlitchMicroloopPlayTMinPropertyId)
        {
            if (onFxGlitchMicroloopPlayTMinChange != nullptr)
                onFxGlitchMicroloopPlayTMinChange (getFxGlitchMicroloopPlayTMin ());
        }
        else if (property == FxGlitchMicroloopPlayTMaxPropertyId)
        {
            if (onFxGlitchMicroloopPlayTMaxChange != nullptr)
                onFxGlitchMicroloopPlayTMaxChange (getFxGlitchMicroloopPlayTMax ());
        }
        else if (property == FxGlitchStutterSmplTMinPropertyId)
        {
            if (onFxGlitchStutterSmplTMinChange != nullptr)
                onFxGlitchStutterSmplTMinChange (getFxGlitchStutterSmplTMin ());
        }
        else if (property == FxGlitchStutterSmplTMaxPropertyId)
        {
            if (onFxGlitchStutterSmplTMaxChange != nullptr)
                onFxGlitchStutterSmplTMaxChange (getFxGlitchStutterSmplTMax ());
        }
        else if (property == FxGlitchStutterNumMinPropertyId)
        {
            if (onFxGlitchStutterNumMinChange != nullptr)
                onFxGlitchStutterNumMinChange (getFxGlitchStutterNumMin ());
        }
        else if (property == FxGlitchStutterNumMaxPropertyId)
        {
            if (onFxGlitchStutterNumMaxChange != nullptr)
                onFxGlitchStutterNumMaxChange (getFxGlitchStutterNumMax ());
        }
        else if (property == FxGlitchStutterWindowPropertyId)
        {
            if (onFxGlitchStutterWindowChange != nullptr)
                onFxGlitchStutterWindowChange (getFxGlitchStutterWindow ());
        }
    }
}

juce::String SettingsProperties::getPitchLowKey ()
{
    return "PITCH_LOW";
}

juce::String SettingsProperties::getPitchHighKey ()
{
    return "PITCH_HIGH";
}

juce::String SettingsProperties::getEnvelopeMaxReleaseKey ()
{
    return "ENVELOPE_MAX_RELEASE";
}

juce::String SettingsProperties::getChokeReleaseKey ()
{
    return "CHOKE_RELEASE";
}

juce::String SettingsProperties::getClsdReleaseModeKey ()
{
    return "CLSD_RELEASE_MODE";
}

juce::String SettingsProperties::getClsdRelOfstScaleKey ()
{
    return "CLSD_REL_OFST_SCALE";
}

juce::String SettingsProperties::getClsdMaxReleaseKey ()
{
    return "CLSD_MAX_RELEASE";
}

juce::String SettingsProperties::getAccClRelModKey ()
{
    return "ACC_CL_REL_MOD";
}

juce::String SettingsProperties::getAccOpRelModKey ()
{
    return "ACC_OP_REL_MOD";
}

juce::String SettingsProperties::getAccClAmpModKey ()
{
    return "ACC_CL_AMP_MOD";
}

juce::String SettingsProperties::getAccOpAmpModKey ()
{
    return "ACC_OP_AMP_MOD";
}

juce::String SettingsProperties::getFxCvUnipolarKey ()
{
    return "FX_CV_UNIPOLAR";
}

juce::String SettingsProperties::getVelocityUnipolarKey ()
{
    return "VELOCITY_UNIPOLAR";
}

juce::String SettingsProperties::getCvDisableVelocityKey ()
{
    return "CV_DISABLE_VELOCITY";
}

juce::String SettingsProperties::getCvDisableFxKey ()
{
    return "CV_DISABLE_FX";
}

juce::String SettingsProperties::getGateModeKey ()
{
    return "GATE_MODE";
}

juce::String SettingsProperties::getFeelAttackModKey ()
{
    return "FEEL_ATTACK_MOD";
}

juce::String SettingsProperties::getFeelReleaseModKey ()
{
    return "FEEL_RELEASE_MOD";
}

juce::String SettingsProperties::getFeelAmpModKey ()
{
    return "FEEL_AMP_MOD";
}

juce::String SettingsProperties::getKnobPosTakeupKey ()
{
    return "KNOB_POS_TAKEUP";
}

juce::String SettingsProperties::getFltrHpfMinFreqKey ()
{
    return "FLTR_HPF_MIN_FREQ";
}

juce::String SettingsProperties::getFltrHpfMaxFreqKey ()
{
    return "FLTR_HPF_MAX_FREQ";
}

juce::String SettingsProperties::getFltrLpfMinFreqKey ()
{
    return "FLTR_LPF_MIN_FREQ";
}

juce::String SettingsProperties::getFltrLpfMaxFreqKey ()
{
    return "FLTR_LPF_MAX_FREQ";
}

juce::String SettingsProperties::getFltrHpfQKey ()
{
    return "FLTR_HPF_Q";
}

juce::String SettingsProperties::getFltrLpfQKey ()
{
    return "FLTR_LPF_Q";
}

juce::String SettingsProperties::getFxDjfilterHpfMinKey ()
{
    return "FX_DJFILTER_HPF_MIN";
}

juce::String SettingsProperties::getFxDjfilterHpfMaxKey ()
{
    return "FX_DJFILTER_HPF_MAX";
}

juce::String SettingsProperties::getFxDjfilterLpfMinKey ()
{
    return "FX_DJFILTER_LPF_MIN";
}

juce::String SettingsProperties::getFxDjfilterLpfMaxKey ()
{
    return "FX_DJFILTER_LPF_MAX";
}

juce::String SettingsProperties::getFxDjfilterQMinKey ()
{
    return "FX_DJFILTER_Q_MIN";
}

juce::String SettingsProperties::getFxDjfilterQMaxKey ()
{
    return "FX_DJFILTER_Q_MAX";
}

juce::String SettingsProperties::getFxDjfilterQGainReductionKey ()
{
    return "FX_DJFILTER_Q_GAIN_REDUCTION";
}

juce::String SettingsProperties::getFxDubEchoTminKey ()
{
    return "FX_DUB_ECHO_TMIN";
}

juce::String SettingsProperties::getFxDubEchoHpfKey ()
{
    return "FX_DUB_ECHO_HPF";
}

juce::String SettingsProperties::getFxDubEchoLpfKey ()
{
    return "FX_DUB_ECHO_LPF";
}

juce::String SettingsProperties::getFxDubEchoMixKey ()
{
    return "FX_DUB_ECHO_MIX";
}

juce::String SettingsProperties::getFxChorusCenterKey ()
{
    return "FX_CHORUS_CENTER";
}

juce::String SettingsProperties::getFxChorusDepthKey ()
{
    return "FX_CHORUS_DEPTH";
}

juce::String SettingsProperties::getFxChorusMixKey ()
{
    return "FX_CHORUS_MIX";
}

juce::String SettingsProperties::getFxChorusSpreadKey ()
{
    return "FX_CHORUS_SPREAD";
}

juce::String SettingsProperties::getFxChorusTapsKey ()
{
    return "FX_CHORUS_TAPS";
}

juce::String SettingsProperties::getFxChorusLfoBKey ()
{
    return "FX_CHORUS_LFO_B";
}

juce::String SettingsProperties::getFxChorusLfoTKey ()
{
    return "FX_CHORUS_LFO_T";
}

juce::String SettingsProperties::getFxReverbLpfKey ()
{
    return "FX_REVERB_LPF";
}

juce::String SettingsProperties::getFxReverbHpfKey ()
{
    return "FX_REVERB_HPF";
}

juce::String SettingsProperties::getFxGlitchProbabilityMinKey ()
{
    return "FX_GLITCH_PROBABILITY_MIN";
}

juce::String SettingsProperties::getFxGlitchProbabilityMaxKey ()
{
    return "FX_GLITCH_PROBABILITY_MAX";
}

juce::String SettingsProperties::getFxGlitchWeightHoldLowKey ()
{
    return "FX_GLITCH_WEIGHT_HOLD_LOW";
}

juce::String SettingsProperties::getFxGlitchWeightStutterLowKey ()
{
    return "FX_GLITCH_WEIGHT_STUTTER_LOW";
}

juce::String SettingsProperties::getFxGlitchWeightCrushLowKey ()
{
    return "FX_GLITCH_WEIGHT_CRUSH_LOW";
}

juce::String SettingsProperties::getFxGlitchWeightDropLowKey ()
{
    return "FX_GLITCH_WEIGHT_DROP_LOW";
}

juce::String SettingsProperties::getFxGlitchWeightHoldHighKey ()
{
    return "FX_GLITCH_WEIGHT_HOLD_HIGH";
}

juce::String SettingsProperties::getFxGlitchWeightStutterHighKey ()
{
    return "FX_GLITCH_WEIGHT_STUTTER_HIGH";
}

juce::String SettingsProperties::getFxGlitchWeightCrushHighKey ()
{
    return "FX_GLITCH_WEIGHT_CRUSH_HIGH";
}

juce::String SettingsProperties::getFxGlitchWeightDropHighKey ()
{
    return "FX_GLITCH_WEIGHT_DROP_HIGH";
}

juce::String SettingsProperties::getFxGlitchDropKeepLevelMinKey ()
{
    return "FX_GLITCH_DROP_KEEP_LEVEL_MIN";
}

juce::String SettingsProperties::getFxGlitchDropKeepLevelMaxKey ()
{
    return "FX_GLITCH_DROP_KEEP_LEVEL_MAX";
}

juce::String SettingsProperties::getFxGlitchDropKeepTimeMinKey ()
{
    return "FX_GLITCH_DROP_KEEP_TIME_MIN";
}

juce::String SettingsProperties::getFxGlitchDropKeepTimeMaxKey ()
{
    return "FX_GLITCH_DROP_KEEP_TIME_MAX";
}

juce::String SettingsProperties::getFxGlitchCrushTimeMinKey ()
{
    return "FX_GLITCH_CRUSH_TIME_MIN";
}

juce::String SettingsProperties::getFxGlitchCrushTimeMaxKey ()
{
    return "FX_GLITCH_CRUSH_TIME_MAX";
}

juce::String SettingsProperties::getFxGlitchMicroloopSmplTMinKey ()
{
    return "FX_GLITCH_MICROLOOP_SMPL_T_MIN";
}

juce::String SettingsProperties::getFxGlitchMicroloopSmplTMaxKey ()
{
    return "FX_GLITCH_MICROLOOP_SMPL_T_MAX";
}

juce::String SettingsProperties::getFxGlitchMicroloopPlayTMinKey ()
{
    return "FX_GLITCH_MICROLOOP_PLAY_T_MIN";
}

juce::String SettingsProperties::getFxGlitchMicroloopPlayTMaxKey ()
{
    return "FX_GLITCH_MICROLOOP_PLAY_T_MAX";
}

juce::String SettingsProperties::getFxGlitchStutterSmplTMinKey ()
{
    return "FX_GLITCH_STUTTER_SMPL_T_MIN";
}

juce::String SettingsProperties::getFxGlitchStutterSmplTMaxKey ()
{
    return "FX_GLITCH_STUTTER_SMPL_T_MAX";
}

juce::String SettingsProperties::getFxGlitchStutterNumMinKey ()
{
    return "FX_GLITCH_STUTTER_NUM_MIN";
}

juce::String SettingsProperties::getFxGlitchStutterNumMaxKey ()
{
    return "FX_GLITCH_STUTTER_NUM_MAX";
}

juce::String SettingsProperties::getFxGlitchStutterWindowKey ()
{
    return "FX_GLITCH_STUTTER_WINDOW";
}
