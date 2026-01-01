#include "HiHatProperties.h"

void HiHatProperties::initValueTree ()
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

void HiHatProperties::setPitchLow (float value, bool includeSelfCallback)
{
    setValue (value, PitchLowPropertyId, includeSelfCallback);
}

void HiHatProperties::setPitchHigh (float value, bool includeSelfCallback)
{
    setValue (value, PitchHighPropertyId, includeSelfCallback);
}

void HiHatProperties::setEnvelopeMaxRelease (float value, bool includeSelfCallback)
{
    setValue (value, EnvelopeMaxReleasePropertyId, includeSelfCallback);
}

void HiHatProperties::setChokeRelease (float value, bool includeSelfCallback)
{
    setValue (value, ChokeReleasePropertyId, includeSelfCallback);
}

void HiHatProperties::setClsdReleaseMode (int value, bool includeSelfCallback)
{
    setValue (value, ClsdReleaseModePropertyId, includeSelfCallback);
}

void HiHatProperties::setClsdRelOfstScale (float value, bool includeSelfCallback)
{
    setValue (value, ClsdRelOfstScalePropertyId, includeSelfCallback);
}

void HiHatProperties::setClsdMaxRelease (float value, bool includeSelfCallback)
{
    setValue (value, ClsdMaxReleasePropertyId, includeSelfCallback);
}

void HiHatProperties::setAccClRelMod (float value, bool includeSelfCallback)
{
    setValue (value, AccClRelModPropertyId, includeSelfCallback);
}

void HiHatProperties::setAccOpRelMod (float value, bool includeSelfCallback)
{
    setValue (value, AccOpRelModPropertyId, includeSelfCallback);
}

void HiHatProperties::setAccClAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, AccClAmpModPropertyId, includeSelfCallback);
}

void HiHatProperties::setAccOpAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, AccOpAmpModPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxCvUnipolar (int value, bool includeSelfCallback)
{
    setValue (value, FxCvUnipolarPropertyId, includeSelfCallback);
}

void HiHatProperties::setVelocityUnipolar (int value, bool includeSelfCallback)
{
    setValue (value, VelocityUnipolarPropertyId, includeSelfCallback);
}

void HiHatProperties::setCvDisableVelocity (int value, bool includeSelfCallback)
{
    setValue (value, CvDisableVelocityPropertyId, includeSelfCallback);
}

void HiHatProperties::setCvDisableFx (int value, bool includeSelfCallback)
{
    setValue (value, CvDisableFxPropertyId, includeSelfCallback);
}

void HiHatProperties::setGateMode (int value, bool includeSelfCallback)
{
    setValue (value, GateModePropertyId, includeSelfCallback);
}

void HiHatProperties::setFeelAttackMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelAttackModPropertyId, includeSelfCallback);
}

void HiHatProperties::setFeelReleaseMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelReleaseModPropertyId, includeSelfCallback);
}

void HiHatProperties::setFeelAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelAmpModPropertyId, includeSelfCallback);
}

void HiHatProperties::setKnobPosTakeup (int value, bool includeSelfCallback)
{
    setValue (value, KnobPosTakeupPropertyId, includeSelfCallback);
}

void HiHatProperties::setFltrHpfMinFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrHpfMinFreqPropertyId, includeSelfCallback);
}

void HiHatProperties::setFltrHpfMaxFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrHpfMaxFreqPropertyId, includeSelfCallback);
}

void HiHatProperties::setFltrLpfMinFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrLpfMinFreqPropertyId, includeSelfCallback);
}

void HiHatProperties::setFltrLpfMaxFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrLpfMaxFreqPropertyId, includeSelfCallback);
}

void HiHatProperties::setFltrHpfQ (float value, bool includeSelfCallback)
{
    setValue (value, FltrHpfQPropertyId, includeSelfCallback);
}

void HiHatProperties::setFltrLpfQ (float value, bool includeSelfCallback)
{
    setValue (value, FltrLpfQPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterHpfMin (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterHpfMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterHpfMax (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterHpfMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterLpfMin (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterLpfMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterLpfMax (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterLpfMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterQMin (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterQMax (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDjfilterQGainReduction (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQGainReductionPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDubEchoTmin (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoTminPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDubEchoHpf (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoHpfPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDubEchoLpf (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoLpfPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxDubEchoMix (float value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoMixPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusCenter (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusCenterPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusDepth (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusDepthPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusMix (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusMixPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusSpread (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusSpreadPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusTaps (int value, bool includeSelfCallback)
{
    setValue (value, FxChorusTapsPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusLfoB (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusLfoBPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxChorusLfoT (int value, bool includeSelfCallback)
{
    setValue (value, FxChorusLfoTPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxReverbLpf (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbLpfPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxReverbHpf (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbHpfPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchProbabilityMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchProbabilityMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchProbabilityMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchProbabilityMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightHoldLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightHoldLowPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightStutterLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightStutterLowPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightCrushLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightCrushLowPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightDropLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightDropLowPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightHoldHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightHoldHighPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightStutterHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightStutterHighPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightCrushHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightCrushHighPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchWeightDropHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightDropHighPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchDropKeepLevelMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepLevelMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchDropKeepLevelMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepLevelMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchDropKeepTimeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepTimeMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchDropKeepTimeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepTimeMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchCrushTimeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchCrushTimeMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchCrushTimeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchCrushTimeMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchMicroloopSmplTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopSmplTMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchMicroloopSmplTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopSmplTMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchMicroloopPlayTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopPlayTMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchMicroloopPlayTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopPlayTMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchStutterSmplTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterSmplTMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchStutterSmplTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterSmplTMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchStutterNumMin (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterNumMinPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchStutterNumMax (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterNumMaxPropertyId, includeSelfCallback);
}

void HiHatProperties::setFxGlitchStutterWindow (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterWindowPropertyId, includeSelfCallback);
}

float HiHatProperties::getPitchLow ()
{
    return getValue<float> (PitchLowPropertyId);
}

float HiHatProperties::getPitchHigh ()
{
    return getValue<float> (PitchHighPropertyId);
}

float HiHatProperties::getEnvelopeMaxRelease ()
{
    return getValue<float> (EnvelopeMaxReleasePropertyId);
}

float HiHatProperties::getChokeRelease ()
{
    return getValue<float> (ChokeReleasePropertyId);
}

int HiHatProperties::getClsdReleaseMode ()
{
    return getValue<int> (ClsdReleaseModePropertyId);
}

float HiHatProperties::getClsdRelOfstScale ()
{
    return getValue<float> (ClsdRelOfstScalePropertyId);
}

float HiHatProperties::getClsdMaxRelease ()
{
    return getValue<float> (ClsdMaxReleasePropertyId);
}

float HiHatProperties::getAccClRelMod ()
{
    return getValue<float> (AccClRelModPropertyId);
}

float HiHatProperties::getAccOpRelMod ()
{
    return getValue<float> (AccOpRelModPropertyId);
}

float HiHatProperties::getAccClAmpMod ()
{
    return getValue<float> (AccClAmpModPropertyId);
}

float HiHatProperties::getAccOpAmpMod ()
{
    return getValue<float> (AccOpAmpModPropertyId);
}

int HiHatProperties::getFxCvUnipolar ()
{
    return getValue<int> (FxCvUnipolarPropertyId);
}

int HiHatProperties::getVelocityUnipolar ()
{
    return getValue<int> (VelocityUnipolarPropertyId);
}

int HiHatProperties::getCvDisableVelocity ()
{
    return getValue<int> (CvDisableVelocityPropertyId);
}

int HiHatProperties::getCvDisableFx ()
{
    return getValue<int> (CvDisableFxPropertyId);
}

int HiHatProperties::getGateMode ()
{
    return getValue<int> (GateModePropertyId);
}

float HiHatProperties::getFeelAttackMod ()
{
    return getValue<float> (FeelAttackModPropertyId);
}

float HiHatProperties::getFeelReleaseMod ()
{
    return getValue<float> (FeelReleaseModPropertyId);
}

float HiHatProperties::getFeelAmpMod ()
{
    return getValue<float> (FeelAmpModPropertyId);
}

int HiHatProperties::getKnobPosTakeup ()
{
    return getValue<int> (KnobPosTakeupPropertyId);
}

int HiHatProperties::getFltrHpfMinFreq ()
{
    return getValue<int> (FltrHpfMinFreqPropertyId);
}

int HiHatProperties::getFltrHpfMaxFreq ()
{
    return getValue<int> (FltrHpfMaxFreqPropertyId);
}

int HiHatProperties::getFltrLpfMinFreq ()
{
    return getValue<int> (FltrLpfMinFreqPropertyId);
}

int HiHatProperties::getFltrLpfMaxFreq ()
{
    return getValue<int> (FltrLpfMaxFreqPropertyId);
}

float HiHatProperties::getFltrHpfQ ()
{
    return getValue<float> (FltrHpfQPropertyId);
}

float HiHatProperties::getFltrLpfQ ()
{
    return getValue<float> (FltrLpfQPropertyId);
}

int HiHatProperties::getFxDjfilterHpfMin ()
{
    return getValue<int> (FxDjfilterHpfMinPropertyId);
}

int HiHatProperties::getFxDjfilterHpfMax ()
{
    return getValue<int> (FxDjfilterHpfMaxPropertyId);
}

int HiHatProperties::getFxDjfilterLpfMin ()
{
    return getValue<int> (FxDjfilterLpfMinPropertyId);
}

int HiHatProperties::getFxDjfilterLpfMax ()
{
    return getValue<int> (FxDjfilterLpfMaxPropertyId);
}

float HiHatProperties::getFxDjfilterQMin ()
{
    return getValue<float> (FxDjfilterQMinPropertyId);
}

float HiHatProperties::getFxDjfilterQMax ()
{
    return getValue<float> (FxDjfilterQMaxPropertyId);
}

float HiHatProperties::getFxDjfilterQGainReduction ()
{
    return getValue<float> (FxDjfilterQGainReductionPropertyId);
}

int HiHatProperties::getFxDubEchoTmin ()
{
    return getValue<int> (FxDubEchoTminPropertyId);
}

int HiHatProperties::getFxDubEchoHpf ()
{
    return getValue<int> (FxDubEchoHpfPropertyId);
}

int HiHatProperties::getFxDubEchoLpf ()
{
    return getValue<int> (FxDubEchoLpfPropertyId);
}

float HiHatProperties::getFxDubEchoMix ()
{
    return getValue<float> (FxDubEchoMixPropertyId);
}

float HiHatProperties::getFxChorusCenter ()
{
    return getValue<float> (FxChorusCenterPropertyId);
}

float HiHatProperties::getFxChorusDepth ()
{
    return getValue<float> (FxChorusDepthPropertyId);
}

float HiHatProperties::getFxChorusMix ()
{
    return getValue<float> (FxChorusMixPropertyId);
}

float HiHatProperties::getFxChorusSpread ()
{
    return getValue<float> (FxChorusSpreadPropertyId);
}

int HiHatProperties::getFxChorusTaps ()
{
    return getValue<int> (FxChorusTapsPropertyId);
}

float HiHatProperties::getFxChorusLfoB ()
{
    return getValue<float> (FxChorusLfoBPropertyId);
}

int HiHatProperties::getFxChorusLfoT ()
{
    return getValue<int> (FxChorusLfoTPropertyId);
}

int HiHatProperties::getFxReverbLpf ()
{
    return getValue<int> (FxReverbLpfPropertyId);
}

int HiHatProperties::getFxReverbHpf ()
{
    return getValue<int> (FxReverbHpfPropertyId);
}

float HiHatProperties::getFxGlitchProbabilityMin ()
{
    return getValue<float> (FxGlitchProbabilityMinPropertyId);
}

float HiHatProperties::getFxGlitchProbabilityMax ()
{
    return getValue<float> (FxGlitchProbabilityMaxPropertyId);
}

float HiHatProperties::getFxGlitchWeightHoldLow ()
{
    return getValue<float> (FxGlitchWeightHoldLowPropertyId);
}

float HiHatProperties::getFxGlitchWeightStutterLow ()
{
    return getValue<float> (FxGlitchWeightStutterLowPropertyId);
}

float HiHatProperties::getFxGlitchWeightCrushLow ()
{
    return getValue<float> (FxGlitchWeightCrushLowPropertyId);
}

float HiHatProperties::getFxGlitchWeightDropLow ()
{
    return getValue<float> (FxGlitchWeightDropLowPropertyId);
}

float HiHatProperties::getFxGlitchWeightHoldHigh ()
{
    return getValue<float> (FxGlitchWeightHoldHighPropertyId);
}

float HiHatProperties::getFxGlitchWeightStutterHigh ()
{
    return getValue<float> (FxGlitchWeightStutterHighPropertyId);
}

float HiHatProperties::getFxGlitchWeightCrushHigh ()
{
    return getValue<float> (FxGlitchWeightCrushHighPropertyId);
}

float HiHatProperties::getFxGlitchWeightDropHigh ()
{
    return getValue<float> (FxGlitchWeightDropHighPropertyId);
}

float HiHatProperties::getFxGlitchDropKeepLevelMin ()
{
    return getValue<float> (FxGlitchDropKeepLevelMinPropertyId);
}

float HiHatProperties::getFxGlitchDropKeepLevelMax ()
{
    return getValue<float> (FxGlitchDropKeepLevelMaxPropertyId);
}

float HiHatProperties::getFxGlitchDropKeepTimeMin ()
{
    return getValue<float> (FxGlitchDropKeepTimeMinPropertyId);
}

float HiHatProperties::getFxGlitchDropKeepTimeMax ()
{
    return getValue<float> (FxGlitchDropKeepTimeMaxPropertyId);
}

float HiHatProperties::getFxGlitchCrushTimeMin ()
{
    return getValue<float> (FxGlitchCrushTimeMinPropertyId);
}

float HiHatProperties::getFxGlitchCrushTimeMax ()
{
    return getValue<float> (FxGlitchCrushTimeMaxPropertyId);
}

float HiHatProperties::getFxGlitchMicroloopSmplTMin ()
{
    return getValue<float> (FxGlitchMicroloopSmplTMinPropertyId);
}

float HiHatProperties::getFxGlitchMicroloopSmplTMax ()
{
    return getValue<float> (FxGlitchMicroloopSmplTMaxPropertyId);
}

float HiHatProperties::getFxGlitchMicroloopPlayTMin ()
{
    return getValue<float> (FxGlitchMicroloopPlayTMinPropertyId);
}

float HiHatProperties::getFxGlitchMicroloopPlayTMax ()
{
    return getValue<float> (FxGlitchMicroloopPlayTMaxPropertyId);
}

float HiHatProperties::getFxGlitchStutterSmplTMin ()
{
    return getValue<float> (FxGlitchStutterSmplTMinPropertyId);
}

float HiHatProperties::getFxGlitchStutterSmplTMax ()
{
    return getValue<float> (FxGlitchStutterSmplTMaxPropertyId);
}

int HiHatProperties::getFxGlitchStutterNumMin ()
{
    return getValue<int> (FxGlitchStutterNumMinPropertyId);
}

int HiHatProperties::getFxGlitchStutterNumMax ()
{
    return getValue<int> (FxGlitchStutterNumMaxPropertyId);
}

int HiHatProperties::getFxGlitchStutterWindow ()
{
    return getValue<int> (FxGlitchStutterWindowPropertyId);
}

void HiHatProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
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

juce::String HiHatProperties::getPitchLowKey ()
{
    return "PITCH_LOW";
}

juce::String HiHatProperties::getPitchHighKey ()
{
    return "PITCH_HIGH";
}

juce::String HiHatProperties::getEnvelopeMaxReleaseKey ()
{
    return "ENVELOPE_MAX_RELEASE";
}

juce::String HiHatProperties::getChokeReleaseKey ()
{
    return "CHOKE_RELEASE";
}

juce::String HiHatProperties::getClsdReleaseModeKey ()
{
    return "CLSD_RELEASE_MODE";
}

juce::String HiHatProperties::getClsdRelOfstScaleKey ()
{
    return "CLSD_REL_OFST_SCALE";
}

juce::String HiHatProperties::getClsdMaxReleaseKey ()
{
    return "CLSD_MAX_RELEASE";
}

juce::String HiHatProperties::getAccClRelModKey ()
{
    return "ACC_CL_REL_MOD";
}

juce::String HiHatProperties::getAccOpRelModKey ()
{
    return "ACC_OP_REL_MOD";
}

juce::String HiHatProperties::getAccClAmpModKey ()
{
    return "ACC_CL_AMP_MOD";
}

juce::String HiHatProperties::getAccOpAmpModKey ()
{
    return "ACC_OP_AMP_MOD";
}

juce::String HiHatProperties::getFxCvUnipolarKey ()
{
    return "FX_CV_UNIPOLAR";
}

juce::String HiHatProperties::getVelocityUnipolarKey ()
{
    return "VELOCITY_UNIPOLAR";
}

juce::String HiHatProperties::getCvDisableVelocityKey ()
{
    return "CV_DISABLE_VELOCITY";
}

juce::String HiHatProperties::getCvDisableFxKey ()
{
    return "CV_DISABLE_FX";
}

juce::String HiHatProperties::getGateModeKey ()
{
    return "GATE_MODE";
}

juce::String HiHatProperties::getFeelAttackModKey ()
{
    return "FEEL_ATTACK_MOD";
}

juce::String HiHatProperties::getFeelReleaseModKey ()
{
    return "FEEL_RELEASE_MOD";
}

juce::String HiHatProperties::getFeelAmpModKey ()
{
    return "FEEL_AMP_MOD";
}

juce::String HiHatProperties::getKnobPosTakeupKey ()
{
    return "KNOB_POS_TAKEUP";
}

juce::String HiHatProperties::getFltrHpfMinFreqKey ()
{
    return "FLTR_HPF_MIN_FREQ";
}

juce::String HiHatProperties::getFltrHpfMaxFreqKey ()
{
    return "FLTR_HPF_MAX_FREQ";
}

juce::String HiHatProperties::getFltrLpfMinFreqKey ()
{
    return "FLTR_LPF_MIN_FREQ";
}

juce::String HiHatProperties::getFltrLpfMaxFreqKey ()
{
    return "FLTR_LPF_MAX_FREQ";
}

juce::String HiHatProperties::getFltrHpfQKey ()
{
    return "FLTR_HPF_Q";
}

juce::String HiHatProperties::getFltrLpfQKey ()
{
    return "FLTR_LPF_Q";
}

juce::String HiHatProperties::getFxDjfilterHpfMinKey ()
{
    return "FX_DJFILTER_HPF_MIN";
}

juce::String HiHatProperties::getFxDjfilterHpfMaxKey ()
{
    return "FX_DJFILTER_HPF_MAX";
}

juce::String HiHatProperties::getFxDjfilterLpfMinKey ()
{
    return "FX_DJFILTER_LPF_MIN";
}

juce::String HiHatProperties::getFxDjfilterLpfMaxKey ()
{
    return "FX_DJFILTER_LPF_MAX";
}

juce::String HiHatProperties::getFxDjfilterQMinKey ()
{
    return "FX_DJFILTER_Q_MIN";
}

juce::String HiHatProperties::getFxDjfilterQMaxKey ()
{
    return "FX_DJFILTER_Q_MAX";
}

juce::String HiHatProperties::getFxDjfilterQGainReductionKey ()
{
    return "FX_DJFILTER_Q_GAIN_REDUCTION";
}

juce::String HiHatProperties::getFxDubEchoTminKey ()
{
    return "FX_DUB_ECHO_TMIN";
}

juce::String HiHatProperties::getFxDubEchoHpfKey ()
{
    return "FX_DUB_ECHO_HPF";
}

juce::String HiHatProperties::getFxDubEchoLpfKey ()
{
    return "FX_DUB_ECHO_LPF";
}

juce::String HiHatProperties::getFxDubEchoMixKey ()
{
    return "FX_DUB_ECHO_MIX";
}

juce::String HiHatProperties::getFxChorusCenterKey ()
{
    return "FX_CHORUS_CENTER";
}

juce::String HiHatProperties::getFxChorusDepthKey ()
{
    return "FX_CHORUS_DEPTH";
}

juce::String HiHatProperties::getFxChorusMixKey ()
{
    return "FX_CHORUS_MIX";
}

juce::String HiHatProperties::getFxChorusSpreadKey ()
{
    return "FX_CHORUS_SPREAD";
}

juce::String HiHatProperties::getFxChorusTapsKey ()
{
    return "FX_CHORUS_TAPS";
}

juce::String HiHatProperties::getFxChorusLfoBKey ()
{
    return "FX_CHORUS_LFO_B";
}

juce::String HiHatProperties::getFxChorusLfoTKey ()
{
    return "FX_CHORUS_LFO_T";
}

juce::String HiHatProperties::getFxReverbLpfKey ()
{
    return "FX_REVERB_LPF";
}

juce::String HiHatProperties::getFxReverbHpfKey ()
{
    return "FX_REVERB_HPF";
}

juce::String HiHatProperties::getFxGlitchProbabilityMinKey ()
{
    return "FX_GLITCH_PROBABILITY_MIN";
}

juce::String HiHatProperties::getFxGlitchProbabilityMaxKey ()
{
    return "FX_GLITCH_PROBABILITY_MAX";
}

juce::String HiHatProperties::getFxGlitchWeightHoldLowKey ()
{
    return "FX_GLITCH_WEIGHT_HOLD_LOW";
}

juce::String HiHatProperties::getFxGlitchWeightStutterLowKey ()
{
    return "FX_GLITCH_WEIGHT_STUTTER_LOW";
}

juce::String HiHatProperties::getFxGlitchWeightCrushLowKey ()
{
    return "FX_GLITCH_WEIGHT_CRUSH_LOW";
}

juce::String HiHatProperties::getFxGlitchWeightDropLowKey ()
{
    return "FX_GLITCH_WEIGHT_DROP_LOW";
}

juce::String HiHatProperties::getFxGlitchWeightHoldHighKey ()
{
    return "FX_GLITCH_WEIGHT_HOLD_HIGH";
}

juce::String HiHatProperties::getFxGlitchWeightStutterHighKey ()
{
    return "FX_GLITCH_WEIGHT_STUTTER_HIGH";
}

juce::String HiHatProperties::getFxGlitchWeightCrushHighKey ()
{
    return "FX_GLITCH_WEIGHT_CRUSH_HIGH";
}

juce::String HiHatProperties::getFxGlitchWeightDropHighKey ()
{
    return "FX_GLITCH_WEIGHT_DROP_HIGH";
}

juce::String HiHatProperties::getFxGlitchDropKeepLevelMinKey ()
{
    return "FX_GLITCH_DROP_KEEP_LEVEL_MIN";
}

juce::String HiHatProperties::getFxGlitchDropKeepLevelMaxKey ()
{
    return "FX_GLITCH_DROP_KEEP_LEVEL_MAX";
}

juce::String HiHatProperties::getFxGlitchDropKeepTimeMinKey ()
{
    return "FX_GLITCH_DROP_KEEP_TIME_MIN";
}

juce::String HiHatProperties::getFxGlitchDropKeepTimeMaxKey ()
{
    return "FX_GLITCH_DROP_KEEP_TIME_MAX";
}

juce::String HiHatProperties::getFxGlitchCrushTimeMinKey ()
{
    return "FX_GLITCH_CRUSH_TIME_MIN";
}

juce::String HiHatProperties::getFxGlitchCrushTimeMaxKey ()
{
    return "FX_GLITCH_CRUSH_TIME_MAX";
}

juce::String HiHatProperties::getFxGlitchMicroloopSmplTMinKey ()
{
    return "FX_GLITCH_MICROLOOP_SMPL_T_MIN";
}

juce::String HiHatProperties::getFxGlitchMicroloopSmplTMaxKey ()
{
    return "FX_GLITCH_MICROLOOP_SMPL_T_MAX";
}

juce::String HiHatProperties::getFxGlitchMicroloopPlayTMinKey ()
{
    return "FX_GLITCH_MICROLOOP_PLAY_T_MIN";
}

juce::String HiHatProperties::getFxGlitchMicroloopPlayTMaxKey ()
{
    return "FX_GLITCH_MICROLOOP_PLAY_T_MAX";
}

juce::String HiHatProperties::getFxGlitchStutterSmplTMinKey ()
{
    return "FX_GLITCH_STUTTER_SMPL_T_MIN";
}

juce::String HiHatProperties::getFxGlitchStutterSmplTMaxKey ()
{
    return "FX_GLITCH_STUTTER_SMPL_T_MAX";
}

juce::String HiHatProperties::getFxGlitchStutterNumMinKey ()
{
    return "FX_GLITCH_STUTTER_NUM_MIN";
}

juce::String HiHatProperties::getFxGlitchStutterNumMaxKey ()
{
    return "FX_GLITCH_STUTTER_NUM_MAX";
}

juce::String HiHatProperties::getFxGlitchStutterWindowKey ()
{
    return "FX_GLITCH_STUTTER_WINDOW";
}
