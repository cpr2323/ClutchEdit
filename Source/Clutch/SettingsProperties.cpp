#include "SettingsProperties.h"
#include "HiHatIniValues.h"

void SettingsProperties::initValueTree ()
{
    // Core
    setPitchLow (kPitchLowDefault, false);
    setPitchHigh (kPitchHighDefault, false);
    setEnvelopeMaxRelease (kEnvelopeMaxReleaseDefault, false);
    setChokeRelease (kChokeReleaseDefault, false);
    setClsdRelOfstScale (kClsdRelOfstScaleDefault, false);
    setClsdMaxRelease (kClsdMaxReleaseDefault, false);
    setAccClRelMod (kAccClRelModDefault, false);
    setAccOpRelMod (kAccOpRelModDefault, false);
    setAccClAmpMod (kAccClAmpModDefault, false);
    setAccOpAmpMod (kAccOpAmpModDefault, false);
    setReleaseMode (kReleaseModeDefault, false);

    // CV / control
    setFxCvUnipolar (kFxCvUnipolarDefault, false);
    setVelocityUnipolar (kVelocityUnipolarDefault, false);
    setCvDisableVelocity (kCvDisableVelocityDefault, false);
    setCvDisableFx (kCvDisableFxDefault, false);
    setGateMode (kGateModeDefault, false);
    setFeelAttackMod (kFeelAttackModDefault, false);
    setFeelReleaseMod (kFeelReleaseModDefault, false);
    setFeelAmpMod (kFeelAmpModDefault, false);
    setKnobPosTakeup (kKnobPosTakeupDefault, false);

    // Filters
    setFltrHpfMinFreq (kFltrHpfMinFreqDefault, false);
    setFltrHpfMaxFreq (kFltrHpfMaxFreqDefault, false);
    setFltrLpfMinFreq (kFltrLpfMinFreqDefault, false);
    setFltrLpfMaxFreq (kFltrLpfMaxFreqDefault, false);
    setFltrHpfQ (kFltrHpfQDefault, false);
    setFltrLpfQ (kFltrLpfQDefault, false);

    // DJ Filter
    setFxDjfilterHpfMin (kFxDjfilterHpfMinDefault, false);
    setFxDjfilterHpfMax (kFxDjfilterHpfMaxDefault, false);
    setFxDjfilterLpfMin (kFxDjfilterLpfMinDefault, false);
    setFxDjfilterLpfMax (kFxDjfilterLpfMaxDefault, false);
    setFxDjfilterQMin (kFxDjfilterQMinDefault, false);
    setFxDjfilterQMax (kFxDjfilterQMaxDefault, false);
    setFxDjfilterQGainReduction (kFxDjfilterQGainReductionDefault, false);

    // Dub Echo
    setFxDubEchoTmin (kFxDubEchoTminDefault, false);
    setFxDubEchoHpf (kFxDubEchoHpfDefault, false);
    setFxDubEchoLpf (kFxDubEchoLpfDefault, false);
    setFxDubEchoMix (kFxDubEchoMixDefault, false);

    // Chorus
    setFxChorusCenter (kFxChorusCenterDefault, false);
    setFxChorusDepth (kFxChorusDepthDefault, false);
    setFxChorusMix (kFxChorusMixDefault, false);
    setFxChorusSpread (kFxChorusSpreadDefault, false);
    setFxChorusTaps (kFxChorusTapsDefault, false);
    setFxChorusLfoB (kFxChorusLfoBDefault, false);
    setFxChorusLfoT (kFxChorusLfoTDefault, false);
    setFxChorusType (kFxChorusTypeDefault, false);
    setFxChorusStagger (kFxChorusStaggerDefault, false);

    // Reverb
    setFxReverbLpf (kFxReverbLpfDefault, false);
    setFxReverbHpf (kFxReverbHpfDefault, false);
    setFxReverbType (kFxReverbTypeDefault, false);
    setFxReverbSizeMin (kFxReverbSizeMinDefault, false);
    setFxReverbSizeMax (kFxReverbSizeMaxDefault, false);
    setFxReverbPredelay (kFxReverbPredelayDefault, false);
    setFxReverbModDepth (kFxReverbModDepthDefault, false);
    setFxReverbModRate (kFxReverbModRateDefault, false);
    setFxReverbDiffusion (kFxReverbDiffusionDefault, false);
    setFxReverbMix (kFxReverbMixDefault, false);

    // Glitch – probability
    setFxGlitchProbabilityMin (kFxGlitchProbabilityMinDefault, false);
    setFxGlitchProbabilityMax (kFxGlitchProbabilityMaxDefault, false);

    // Glitch – weights (low)
    setFxGlitchWeightHoldLow (kFxGlitchWeightHoldLowDefault, false);
    setFxGlitchWeightStutterLow (kFxGlitchWeightStutterLowDefault, false);
    setFxGlitchWeightCrushLow (kFxGlitchWeightCrushLowDefault, false);
    setFxGlitchWeightDropLow (kFxGlitchWeightDropLowDefault, false);

    // Glitch – weights (high)
    setFxGlitchWeightHoldHigh (kFxGlitchWeightHoldHighDefault, false);
    setFxGlitchWeightStutterHigh (kFxGlitchWeightStutterHighDefault, false);
    setFxGlitchWeightCrushHigh (kFxGlitchWeightCrushHighDefault, false);
    setFxGlitchWeightDropHigh (kFxGlitchWeightDropHighDefault, false);

    // Glitch – drop
    setFxGlitchDropKeepLevelMin (kFxGlitchDropKeepLevelMinDefault, false);
    setFxGlitchDropKeepLevelMax (kFxGlitchDropKeepLevelMaxDefault, false);
    setFxGlitchDropKeepTimeMin (kFxGlitchDropKeepTimeMinDefault, false);
    setFxGlitchDropKeepTimeMax (kFxGlitchDropKeepTimeMaxDefault, false);

    // Glitch – crush
    setFxGlitchCrushTimeMin (kFxGlitchCrushTimeMinDefault, false);
    setFxGlitchCrushTimeMax (kFxGlitchCrushTimeMaxDefault, false);

    // Glitch – microloop
    setFxGlitchMicroloopSmplTMin (kFxGlitchMicroloopSmplTMinDefault, false);
    setFxGlitchMicroloopSmplTMax (kFxGlitchMicroloopSmplTMaxDefault, false);
    setFxGlitchMicroloopPlayTMin (kFxGlitchMicroloopPlayTMinDefault, false);
    setFxGlitchMicroloopPlayTMax (kFxGlitchMicroloopPlayTMaxDefault, false);

    // Glitch – stutter
    setFxGlitchStutterSmplTMin (kFxGlitchStutterSmplTMinDefault, false);
    setFxGlitchStutterSmplTMax (kFxGlitchStutterSmplTMaxDefault, false);
    setFxGlitchStutterNumMin (kFxGlitchStutterNumMinDefault, false);
    setFxGlitchStutterNumMax (kFxGlitchStutterNumMaxDefault, false);
    setFxGlitchStutterWindow (kFxGlitchStutterWindowDefault, false);
}

void SettingsProperties::setAccClAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, AccClAmpModPropertyId, includeSelfCallback);
}

void SettingsProperties::setAccClRelMod (float value, bool includeSelfCallback)
{
    setValue (value, AccClRelModPropertyId, includeSelfCallback);
}

void SettingsProperties::setAccOpAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, AccOpAmpModPropertyId, includeSelfCallback);
}

void SettingsProperties::setAccOpRelMod (float value, bool includeSelfCallback)
{
    setValue (value, AccOpRelModPropertyId, includeSelfCallback);
}

void SettingsProperties::setChokeRelease (float value, bool includeSelfCallback)
{
    setValue (value, ChokeReleasePropertyId, includeSelfCallback);
}

void SettingsProperties::setClsdMaxRelease (float value, bool includeSelfCallback)
{
    setValue (value, ClsdMaxReleasePropertyId, includeSelfCallback);
}

void SettingsProperties::setClsdRelOfstScale (float value, bool includeSelfCallback)
{
    setValue (value, ClsdRelOfstScalePropertyId, includeSelfCallback);
}

void SettingsProperties::setCvDisableFx (int value, bool includeSelfCallback)
{
    setValue (value, CvDisableFxPropertyId, includeSelfCallback);
}

void SettingsProperties::setCvDisableVelocity (int value, bool includeSelfCallback)
{
    setValue (value, CvDisableVelocityPropertyId, includeSelfCallback);
}

void SettingsProperties::setEnvelopeMaxRelease (float value, bool includeSelfCallback)
{
    setValue (value, EnvelopeMaxReleasePropertyId, includeSelfCallback);
}

void SettingsProperties::setFeelAmpMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelAmpModPropertyId, includeSelfCallback);
}

void SettingsProperties::setFeelAttackMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelAttackModPropertyId, includeSelfCallback);
}

void SettingsProperties::setFeelReleaseMod (float value, bool includeSelfCallback)
{
    setValue (value, FeelReleaseModPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrHpfMaxFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrHpfMaxFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrHpfMinFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrHpfMinFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrHpfQ (float value, bool includeSelfCallback)
{
    setValue (value, FltrHpfQPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrLpfMaxFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrLpfMaxFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrLpfMinFreq (int value, bool includeSelfCallback)
{
    setValue (value, FltrLpfMinFreqPropertyId, includeSelfCallback);
}

void SettingsProperties::setFltrLpfQ (float value, bool includeSelfCallback)
{
    setValue (value, FltrLpfQPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusCenter (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusCenterPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusDepth (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusDepthPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusLfoB (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusLfoBPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusLfoT (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusLfoTPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusMix (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusMixPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusSpread (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusSpreadPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusStagger (float value, bool includeSelfCallback)
{
    setValue (value, FxChorusStaggerPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusTaps (int value, bool includeSelfCallback)
{
    setValue (value, FxChorusTapsPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxChorusType (int value, bool includeSelfCallback)
{
    setValue (value, FxChorusTypePropertyId, includeSelfCallback);
}

void SettingsProperties::setFxCvUnipolar (int value, bool includeSelfCallback)
{
    setValue (value, FxCvUnipolarPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterHpfMax (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterHpfMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterHpfMin (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterHpfMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterLpfMax (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterLpfMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterLpfMin (int value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterLpfMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterQGainReduction (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQGainReductionPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterQMax (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxDjfilterQMin (float value, bool includeSelfCallback)
{
    setValue (value, FxDjfilterQMinPropertyId, includeSelfCallback);
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

void SettingsProperties::setFxDubEchoTmin (int value, bool includeSelfCallback)
{
    setValue (value, FxDubEchoTminPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchCrushTimeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchCrushTimeMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchCrushTimeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchCrushTimeMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepLevelMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepLevelMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepLevelMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepLevelMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepTimeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepTimeMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchDropKeepTimeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchDropKeepTimeMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopPlayTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopPlayTMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopPlayTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopPlayTMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopSmplTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopSmplTMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchMicroloopSmplTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchMicroloopSmplTMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchProbabilityMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchProbabilityMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchProbabilityMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchProbabilityMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterNumMax (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterNumMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterNumMin (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterNumMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterSmplTMax (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterSmplTMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterSmplTMin (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterSmplTMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchStutterWindow (int value, bool includeSelfCallback)
{
    setValue (value, FxGlitchStutterWindowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightCrushHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightCrushHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightCrushLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightCrushLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightDropHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightDropHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightDropLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightDropLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightHoldHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightHoldHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightHoldLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightHoldLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightStutterHigh (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightStutterHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxGlitchWeightStutterLow (float value, bool includeSelfCallback)
{
    setValue (value, FxGlitchWeightStutterLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbDiffusion (float value, bool includeSelfCallback)
{
    setValue (value, FxReverbDiffusionPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbHpf (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbHpfPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbLpf (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbLpfPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbMix (float value, bool includeSelfCallback)
{
    setValue (value, FxReverbMixPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbModDepth (float value, bool includeSelfCallback)
{
    setValue (value, FxReverbModDepthPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbModRate (float value, bool includeSelfCallback)
{
    setValue (value, FxReverbModRatePropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbPredelay (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbPredelayPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbSizeMax (float value, bool includeSelfCallback)
{
    setValue (value, FxReverbSizeMaxPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbSizeMin (float value, bool includeSelfCallback)
{
    setValue (value, FxReverbSizeMinPropertyId, includeSelfCallback);
}

void SettingsProperties::setFxReverbType (int value, bool includeSelfCallback)
{
    setValue (value, FxReverbTypePropertyId, includeSelfCallback);
}

void SettingsProperties::setGateMode (int value, bool includeSelfCallback)
{
    setValue (value, GateModePropertyId, includeSelfCallback);
}

void SettingsProperties::setKnobPosTakeup (int value, bool includeSelfCallback)
{
    setValue (value, KnobPosTakeupPropertyId, includeSelfCallback);
}

void SettingsProperties::setPitchHigh (float value, bool includeSelfCallback)
{
    setValue (value, PitchHighPropertyId, includeSelfCallback);
}

void SettingsProperties::setPitchLow (float value, bool includeSelfCallback)
{
    setValue (value, PitchLowPropertyId, includeSelfCallback);
}

void SettingsProperties::setReleaseMode (int value, bool includeSelfCallback)
{
    setValue (value, ReleaseModePropertyId, includeSelfCallback);
}

void SettingsProperties::setVelocityUnipolar (int value, bool includeSelfCallback)
{
    setValue (value, VelocityUnipolarPropertyId, includeSelfCallback);
}

float SettingsProperties::getAccClAmpMod ()
{
    return getValue<float> (AccClAmpModPropertyId);
}

float SettingsProperties::getAccClRelMod ()
{
    return getValue<float> (AccClRelModPropertyId);
}

float SettingsProperties::getAccOpAmpMod ()
{
    return getValue<float> (AccOpAmpModPropertyId);
}

float SettingsProperties::getAccOpRelMod ()
{
    return getValue<float> (AccOpRelModPropertyId);
}

float SettingsProperties::getChokeRelease ()
{
    return getValue<float> (ChokeReleasePropertyId);
}

float SettingsProperties::getClsdMaxRelease ()
{
    return getValue<float> (ClsdMaxReleasePropertyId);
}

float SettingsProperties::getClsdRelOfstScale ()
{
    return getValue<float> (ClsdRelOfstScalePropertyId);
}

int SettingsProperties::getCvDisableFx ()
{
    return getValue<int> (CvDisableFxPropertyId);
}

int SettingsProperties::getCvDisableVelocity ()
{
    return getValue<int> (CvDisableVelocityPropertyId);
}

float SettingsProperties::getEnvelopeMaxRelease ()
{
    return getValue<float> (EnvelopeMaxReleasePropertyId);
}

float SettingsProperties::getFeelAmpMod ()
{
    return getValue<float> (FeelAmpModPropertyId);
}

float SettingsProperties::getFeelAttackMod ()
{
    return getValue<float> (FeelAttackModPropertyId);
}

float SettingsProperties::getFeelReleaseMod ()
{
    return getValue<float> (FeelReleaseModPropertyId);
}

int SettingsProperties::getFltrHpfMaxFreq ()
{
    return getValue<int> (FltrHpfMaxFreqPropertyId);
}

int SettingsProperties::getFltrHpfMinFreq ()
{
    return getValue<int> (FltrHpfMinFreqPropertyId);
}

float SettingsProperties::getFltrHpfQ ()
{
    return getValue<float> (FltrHpfQPropertyId);
}

int SettingsProperties::getFltrLpfMaxFreq ()
{
    return getValue<int> (FltrLpfMaxFreqPropertyId);
}

int SettingsProperties::getFltrLpfMinFreq ()
{
    return getValue<int> (FltrLpfMinFreqPropertyId);
}

float SettingsProperties::getFltrLpfQ ()
{
    return getValue<float> (FltrLpfQPropertyId);
}

float SettingsProperties::getFxChorusCenter ()
{
    return getValue<float> (FxChorusCenterPropertyId);
}

float SettingsProperties::getFxChorusDepth ()
{
    return getValue<float> (FxChorusDepthPropertyId);
}

float SettingsProperties::getFxChorusLfoB ()
{
    return getValue<float> (FxChorusLfoBPropertyId);
}

float SettingsProperties::getFxChorusLfoT ()
{
    return getValue<float> (FxChorusLfoTPropertyId);
}

float SettingsProperties::getFxChorusMix ()
{
    return getValue<float> (FxChorusMixPropertyId);
}

float SettingsProperties::getFxChorusSpread ()
{
    return getValue<float> (FxChorusSpreadPropertyId);
}

float SettingsProperties::getFxChorusStagger ()
{
    return getValue<float> (FxChorusStaggerPropertyId);
}

int SettingsProperties::getFxChorusTaps ()
{
    return getValue<int> (FxChorusTapsPropertyId);
}

int SettingsProperties::getFxChorusType ()
{
    return getValue<int> (FxChorusTypePropertyId);
}

int SettingsProperties::getFxCvUnipolar ()
{
    return getValue<int> (FxCvUnipolarPropertyId);
}

int SettingsProperties::getFxDjfilterHpfMax ()
{
    return getValue<int> (FxDjfilterHpfMaxPropertyId);
}

int SettingsProperties::getFxDjfilterHpfMin ()
{
    return getValue<int> (FxDjfilterHpfMinPropertyId);
}

int SettingsProperties::getFxDjfilterLpfMax ()
{
    return getValue<int> (FxDjfilterLpfMaxPropertyId);
}

int SettingsProperties::getFxDjfilterLpfMin ()
{
    return getValue<int> (FxDjfilterLpfMinPropertyId);
}

float SettingsProperties::getFxDjfilterQGainReduction ()
{
    return getValue<float> (FxDjfilterQGainReductionPropertyId);
}

float SettingsProperties::getFxDjfilterQMax ()
{
    return getValue<float> (FxDjfilterQMaxPropertyId);
}

float SettingsProperties::getFxDjfilterQMin ()
{
    return getValue<float> (FxDjfilterQMinPropertyId);
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

int SettingsProperties::getFxDubEchoTmin ()
{
    return getValue<int> (FxDubEchoTminPropertyId);
}

float SettingsProperties::getFxGlitchCrushTimeMax ()
{
    return getValue<float> (FxGlitchCrushTimeMaxPropertyId);
}

float SettingsProperties::getFxGlitchCrushTimeMin ()
{
    return getValue<float> (FxGlitchCrushTimeMinPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepLevelMax ()
{
    return getValue<float> (FxGlitchDropKeepLevelMaxPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepLevelMin ()
{
    return getValue<float> (FxGlitchDropKeepLevelMinPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepTimeMax ()
{
    return getValue<float> (FxGlitchDropKeepTimeMaxPropertyId);
}

float SettingsProperties::getFxGlitchDropKeepTimeMin ()
{
    return getValue<float> (FxGlitchDropKeepTimeMinPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopPlayTMax ()
{
    return getValue<float> (FxGlitchMicroloopPlayTMaxPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopPlayTMin ()
{
    return getValue<float> (FxGlitchMicroloopPlayTMinPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopSmplTMax ()
{
    return getValue<float> (FxGlitchMicroloopSmplTMaxPropertyId);
}

float SettingsProperties::getFxGlitchMicroloopSmplTMin ()
{
    return getValue<float> (FxGlitchMicroloopSmplTMinPropertyId);
}

float SettingsProperties::getFxGlitchProbabilityMax ()
{
    return getValue<float> (FxGlitchProbabilityMaxPropertyId);
}

float SettingsProperties::getFxGlitchProbabilityMin ()
{
    return getValue<float> (FxGlitchProbabilityMinPropertyId);
}

int SettingsProperties::getFxGlitchStutterNumMax ()
{
    return getValue<int> (FxGlitchStutterNumMaxPropertyId);
}

int SettingsProperties::getFxGlitchStutterNumMin ()
{
    return getValue<int> (FxGlitchStutterNumMinPropertyId);
}

float SettingsProperties::getFxGlitchStutterSmplTMax ()
{
    return getValue<float> (FxGlitchStutterSmplTMaxPropertyId);
}

float SettingsProperties::getFxGlitchStutterSmplTMin ()
{
    return getValue<float> (FxGlitchStutterSmplTMinPropertyId);
}

int SettingsProperties::getFxGlitchStutterWindow ()
{
    return getValue<int> (FxGlitchStutterWindowPropertyId);
}

float SettingsProperties::getFxGlitchWeightCrushHigh ()
{
    return getValue<float> (FxGlitchWeightCrushHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightCrushLow ()
{
    return getValue<float> (FxGlitchWeightCrushLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightDropHigh ()
{
    return getValue<float> (FxGlitchWeightDropHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightDropLow ()
{
    return getValue<float> (FxGlitchWeightDropLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightHoldHigh ()
{
    return getValue<float> (FxGlitchWeightHoldHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightHoldLow ()
{
    return getValue<float> (FxGlitchWeightHoldLowPropertyId);
}

float SettingsProperties::getFxGlitchWeightStutterHigh ()
{
    return getValue<float> (FxGlitchWeightStutterHighPropertyId);
}

float SettingsProperties::getFxGlitchWeightStutterLow ()
{
    return getValue<float> (FxGlitchWeightStutterLowPropertyId);
}

float SettingsProperties::getFxReverbDiffusion ()
{
    return getValue<float> (FxReverbDiffusionPropertyId);
}

int SettingsProperties::getFxReverbHpf ()
{
    return getValue<int> (FxReverbHpfPropertyId);
}

int SettingsProperties::getFxReverbLpf ()
{
    return getValue<int> (FxReverbLpfPropertyId);
}

float SettingsProperties::getFxReverbMix ()
{
    return getValue<float> (FxReverbMixPropertyId);
}

float SettingsProperties::getFxReverbModDepth ()
{
    return getValue<float> (FxReverbModDepthPropertyId);
}

float SettingsProperties::getFxReverbModRate ()
{
    return getValue<float> (FxReverbModRatePropertyId);
}

int SettingsProperties::getFxReverbPredelay ()
{
    return getValue<int> (FxReverbPredelayPropertyId);
}

float SettingsProperties::getFxReverbSizeMax ()
{
    return getValue<float> (FxReverbSizeMaxPropertyId);
}

float SettingsProperties::getFxReverbSizeMin ()
{
    return getValue<float> (FxReverbSizeMinPropertyId);
}

int SettingsProperties::getFxReverbType ()
{
    return getValue<int> (FxReverbTypePropertyId);
}

int SettingsProperties::getGateMode ()
{
    return getValue<int> (GateModePropertyId);
}

int SettingsProperties::getKnobPosTakeup ()
{
    return getValue<int> (KnobPosTakeupPropertyId);
}

float SettingsProperties::getPitchHigh ()
{
    return getValue<float> (PitchHighPropertyId);
}

float SettingsProperties::getPitchLow ()
{
    return getValue<float> (PitchLowPropertyId);
}

int SettingsProperties::getReleaseMode ()
{
    return getValue<int> (ReleaseModePropertyId);
}

int SettingsProperties::getVelocityUnipolar ()
{
    return getValue<int> (VelocityUnipolarPropertyId);
}

void SettingsProperties::valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property)
{
    if (data == vt)
    {
        if (property == AccClAmpModPropertyId)
        {
            if (onAccClAmpModChange != nullptr)
                onAccClAmpModChange (getAccClAmpMod ());
        }
        else if (property == AccClRelModPropertyId)
        {
            if (onAccClRelModChange != nullptr)
                onAccClRelModChange (getAccClRelMod ());
        }
        else if (property == AccOpAmpModPropertyId)
        {
            if (onAccOpAmpModChange != nullptr)
                onAccOpAmpModChange (getAccOpAmpMod ());
        }
        else if (property == AccOpRelModPropertyId)
        {
            if (onAccOpRelModChange != nullptr)
                onAccOpRelModChange (getAccOpRelMod ());
        }
        else if (property == ChokeReleasePropertyId)
        {
            if (onChokeReleaseChange != nullptr)
                onChokeReleaseChange (getChokeRelease ());
        }
        else if (property == ClsdMaxReleasePropertyId)
        {
            if (onClsdMaxReleaseChange != nullptr)
                onClsdMaxReleaseChange (getClsdMaxRelease ());
        }
        else if (property == ClsdRelOfstScalePropertyId)
        {
            if (onClsdRelOfstScaleChange != nullptr)
                onClsdRelOfstScaleChange (getClsdRelOfstScale ());
        }
        else if (property == CvDisableFxPropertyId)
        {
            if (onCvDisableFxChange != nullptr)
                onCvDisableFxChange (getCvDisableFx ());
        }
        else if (property == CvDisableVelocityPropertyId)
        {
            if (onCvDisableVelocityChange != nullptr)
                onCvDisableVelocityChange (getCvDisableVelocity ());
        }
        else if (property == EnvelopeMaxReleasePropertyId)
        {
            if (onEnvelopeMaxReleaseChange != nullptr)
                onEnvelopeMaxReleaseChange (getEnvelopeMaxRelease ());
        }
        else if (property == FeelAmpModPropertyId)
        {
            if (onFeelAmpModChange != nullptr)
                onFeelAmpModChange (getFeelAmpMod ());
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
        else if (property == FltrHpfMaxFreqPropertyId)
        {
            if (onFltrHpfMaxFreqChange != nullptr)
                onFltrHpfMaxFreqChange (getFltrHpfMaxFreq ());
        }
        else if (property == FltrHpfMinFreqPropertyId)
        {
            if (onFltrHpfMinFreqChange != nullptr)
                onFltrHpfMinFreqChange (getFltrHpfMinFreq ());
        }
        else if (property == FltrHpfQPropertyId)
        {
            if (onFltrHpfQChange != nullptr)
                onFltrHpfQChange (getFltrHpfQ ());
        }
        else if (property == FltrLpfMaxFreqPropertyId)
        {
            if (onFltrLpfMaxFreqChange != nullptr)
                onFltrLpfMaxFreqChange (getFltrLpfMaxFreq ());
        }
        else if (property == FltrLpfMinFreqPropertyId)
        {
            if (onFltrLpfMinFreqChange != nullptr)
                onFltrLpfMinFreqChange (getFltrLpfMinFreq ());
        }
        else if (property == FltrLpfQPropertyId)
        {
            if (onFltrLpfQChange != nullptr)
                onFltrLpfQChange (getFltrLpfQ ());
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
        else if (property == FxChorusStaggerPropertyId)
        {
            if (onFxChorusStaggerChange != nullptr)
                onFxChorusStaggerChange (getFxChorusStagger ());
        }
        else if (property == FxChorusTapsPropertyId)
        {
            if (onFxChorusTapsChange != nullptr)
                onFxChorusTapsChange (getFxChorusTaps ());
        }
        else if (property == FxChorusTypePropertyId)
        {
            if (onFxChorusTypeChange != nullptr)
                onFxChorusTypeChange (getFxChorusType ());
        }
        else if (property == FxCvUnipolarPropertyId)
        {
            if (onFxCvUnipolarChange != nullptr)
                onFxCvUnipolarChange (getFxCvUnipolar ());
        }
        else if (property == FxDjfilterHpfMaxPropertyId)
        {
            if (onFxDjfilterHpfMaxChange != nullptr)
                onFxDjfilterHpfMaxChange (getFxDjfilterHpfMax ());
        }
        else if (property == FxDjfilterHpfMinPropertyId)
        {
            if (onFxDjfilterHpfMinChange != nullptr)
                onFxDjfilterHpfMinChange (getFxDjfilterHpfMin ());
        }
        else if (property == FxDjfilterLpfMaxPropertyId)
        {
            if (onFxDjfilterLpfMaxChange != nullptr)
                onFxDjfilterLpfMaxChange (getFxDjfilterLpfMax ());
        }
        else if (property == FxDjfilterLpfMinPropertyId)
        {
            if (onFxDjfilterLpfMinChange != nullptr)
                onFxDjfilterLpfMinChange (getFxDjfilterLpfMin ());
        }
        else if (property == FxDjfilterQGainReductionPropertyId)
        {
            if (onFxDjfilterQGainReductionChange != nullptr)
                onFxDjfilterQGainReductionChange (getFxDjfilterQGainReduction ());
        }
        else if (property == FxDjfilterQMaxPropertyId)
        {
            if (onFxDjfilterQMaxChange != nullptr)
                onFxDjfilterQMaxChange (getFxDjfilterQMax ());
        }
        else if (property == FxDjfilterQMinPropertyId)
        {
            if (onFxDjfilterQMinChange != nullptr)
                onFxDjfilterQMinChange (getFxDjfilterQMin ());
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
        else if (property == FxDubEchoTminPropertyId)
        {
            if (onFxDubEchoTminChange != nullptr)
                onFxDubEchoTminChange (getFxDubEchoTmin ());
        }
        else if (property == FxGlitchCrushTimeMaxPropertyId)
        {
            if (onFxGlitchCrushTimeMaxChange != nullptr)
                onFxGlitchCrushTimeMaxChange (getFxGlitchCrushTimeMax ());
        }
        else if (property == FxGlitchCrushTimeMinPropertyId)
        {
            if (onFxGlitchCrushTimeMinChange != nullptr)
                onFxGlitchCrushTimeMinChange (getFxGlitchCrushTimeMin ());
        }
        else if (property == FxGlitchDropKeepLevelMaxPropertyId)
        {
            if (onFxGlitchDropKeepLevelMaxChange != nullptr)
                onFxGlitchDropKeepLevelMaxChange (getFxGlitchDropKeepLevelMax ());
        }
        else if (property == FxGlitchDropKeepLevelMinPropertyId)
        {
            if (onFxGlitchDropKeepLevelMinChange != nullptr)
                onFxGlitchDropKeepLevelMinChange (getFxGlitchDropKeepLevelMin ());
        }
        else if (property == FxGlitchDropKeepTimeMaxPropertyId)
        {
            if (onFxGlitchDropKeepTimeMaxChange != nullptr)
                onFxGlitchDropKeepTimeMaxChange (getFxGlitchDropKeepTimeMax ());
        }
        else if (property == FxGlitchDropKeepTimeMinPropertyId)
        {
            if (onFxGlitchDropKeepTimeMinChange != nullptr)
                onFxGlitchDropKeepTimeMinChange (getFxGlitchDropKeepTimeMin ());
        }
        else if (property == FxGlitchMicroloopPlayTMaxPropertyId)
        {
            if (onFxGlitchMicroloopPlayTMaxChange != nullptr)
                onFxGlitchMicroloopPlayTMaxChange (getFxGlitchMicroloopPlayTMax ());
        }
        else if (property == FxGlitchMicroloopPlayTMinPropertyId)
        {
            if (onFxGlitchMicroloopPlayTMinChange != nullptr)
                onFxGlitchMicroloopPlayTMinChange (getFxGlitchMicroloopPlayTMin ());
        }
        else if (property == FxGlitchMicroloopSmplTMaxPropertyId)
        {
            if (onFxGlitchMicroloopSmplTMaxChange != nullptr)
                onFxGlitchMicroloopSmplTMaxChange (getFxGlitchMicroloopSmplTMax ());
        }
        else if (property == FxGlitchMicroloopSmplTMinPropertyId)
        {
            if (onFxGlitchMicroloopSmplTMinChange != nullptr)
                onFxGlitchMicroloopSmplTMinChange (getFxGlitchMicroloopSmplTMin ());
        }
        else if (property == FxGlitchProbabilityMaxPropertyId)
        {
            if (onFxGlitchProbabilityMaxChange != nullptr)
                onFxGlitchProbabilityMaxChange (getFxGlitchProbabilityMax ());
        }
        else if (property == FxGlitchProbabilityMinPropertyId)
        {
            if (onFxGlitchProbabilityMinChange != nullptr)
                onFxGlitchProbabilityMinChange (getFxGlitchProbabilityMin ());
        }
        else if (property == FxGlitchStutterNumMaxPropertyId)
        {
            if (onFxGlitchStutterNumMaxChange != nullptr)
                onFxGlitchStutterNumMaxChange (getFxGlitchStutterNumMax ());
        }
        else if (property == FxGlitchStutterNumMinPropertyId)
        {
            if (onFxGlitchStutterNumMinChange != nullptr)
                onFxGlitchStutterNumMinChange (getFxGlitchStutterNumMin ());
        }
        else if (property == FxGlitchStutterSmplTMaxPropertyId)
        {
            if (onFxGlitchStutterSmplTMaxChange != nullptr)
                onFxGlitchStutterSmplTMaxChange (getFxGlitchStutterSmplTMax ());
        }
        else if (property == FxGlitchStutterSmplTMinPropertyId)
        {
            if (onFxGlitchStutterSmplTMinChange != nullptr)
                onFxGlitchStutterSmplTMinChange (getFxGlitchStutterSmplTMin ());
        }
        else if (property == FxGlitchStutterWindowPropertyId)
        {
            if (onFxGlitchStutterWindowChange != nullptr)
                onFxGlitchStutterWindowChange (getFxGlitchStutterWindow ());
        }
        else if (property == FxGlitchWeightCrushHighPropertyId)
        {
            if (onFxGlitchWeightCrushHighChange != nullptr)
                onFxGlitchWeightCrushHighChange (getFxGlitchWeightCrushHigh ());
        }
        else if (property == FxGlitchWeightCrushLowPropertyId)
        {
            if (onFxGlitchWeightCrushLowChange != nullptr)
                onFxGlitchWeightCrushLowChange (getFxGlitchWeightCrushLow ());
        }
        else if (property == FxGlitchWeightDropHighPropertyId)
        {
            if (onFxGlitchWeightDropHighChange != nullptr)
                onFxGlitchWeightDropHighChange (getFxGlitchWeightDropHigh ());
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
        else if (property == FxGlitchWeightHoldLowPropertyId)
        {
            if (onFxGlitchWeightHoldLowChange != nullptr)
                onFxGlitchWeightHoldLowChange (getFxGlitchWeightHoldLow ());
        }
        else if (property == FxGlitchWeightStutterHighPropertyId)
        {
            if (onFxGlitchWeightStutterHighChange != nullptr)
                onFxGlitchWeightStutterHighChange (getFxGlitchWeightStutterHigh ());
        }
        else if (property == FxGlitchWeightStutterLowPropertyId)
        {
            if (onFxGlitchWeightStutterLowChange != nullptr)
                onFxGlitchWeightStutterLowChange (getFxGlitchWeightStutterLow ());
        }
        else if (property == FxReverbDiffusionPropertyId)
        {
            if (onFxReverbDiffusionChange != nullptr)
                onFxReverbDiffusionChange (getFxReverbDiffusion ());
        }
        else if (property == FxReverbHpfPropertyId)
        {
            if (onFxReverbHpfChange != nullptr)
                onFxReverbHpfChange (getFxReverbHpf ());
        }
        else if (property == FxReverbLpfPropertyId)
        {
            if (onFxReverbLpfChange != nullptr)
                onFxReverbLpfChange (getFxReverbLpf ());
        }
        else if (property == FxReverbMixPropertyId)
        {
            if (onFxReverbMixChange != nullptr)
                onFxReverbMixChange (getFxReverbMix ());
        }
        else if (property == FxReverbModDepthPropertyId)
        {
            if (onFxReverbModDepthChange != nullptr)
                onFxReverbModDepthChange (getFxReverbModDepth ());
        }
        else if (property == FxReverbModRatePropertyId)
        {
            if (onFxReverbModRateChange != nullptr)
                onFxReverbModRateChange (getFxReverbModRate ());
        }
        else if (property == FxReverbPredelayPropertyId)
        {
            if (onFxReverbPredelayChange != nullptr)
                onFxReverbPredelayChange (getFxReverbPredelay ());
        }
        else if (property == FxReverbSizeMaxPropertyId)
        {
            if (onFxReverbSizeMaxChange != nullptr)
                onFxReverbSizeMaxChange (getFxReverbSizeMax ());
        }
        else if (property == FxReverbSizeMinPropertyId)
        {
            if (onFxReverbSizeMinChange != nullptr)
                onFxReverbSizeMinChange (getFxReverbSizeMin ());
        }
        else if (property == FxReverbTypePropertyId)
        {
            if (onFxReverbTypeChange != nullptr)
                onFxReverbTypeChange (getFxReverbType ());
        }
        else if (property == GateModePropertyId)
        {
            if (onGateModeChange != nullptr)
                onGateModeChange (getGateMode ());
        }
        else if (property == KnobPosTakeupPropertyId)
        {
            if (onKnobPosTakeupChange != nullptr)
                onKnobPosTakeupChange (getKnobPosTakeup ());
        }
        else if (property == PitchHighPropertyId)
        {
            if (onPitchHighChange != nullptr)
                onPitchHighChange (getPitchHigh ());
        }
        else if (property == PitchLowPropertyId)
        {
            if (onPitchLowChange != nullptr)
                onPitchLowChange (getPitchLow ());
        }
        else if (property == ReleaseModePropertyId)
        {
            if (onReleaseModeChange != nullptr)
                onReleaseModeChange (getReleaseMode ());
        }
        else if (property == VelocityUnipolarPropertyId)
        {
            if (onVelocityUnipolarChange != nullptr)
                onVelocityUnipolarChange (getVelocityUnipolar ());
        }
    }
}

juce::String SettingsProperties::getAccClAmpModKey ()
{
    return kAccClAmpModKey;
}

juce::String SettingsProperties::getAccClRelModKey ()
{
    return kAccClRelModKey;
}

juce::String SettingsProperties::getAccOpAmpModKey ()
{
    return kAccOpAmpModKey;
}

juce::String SettingsProperties::getAccOpRelModKey ()
{
    return kAccOpRelModKey;
}

juce::String SettingsProperties::getChokeReleaseKey ()
{
    return kChokeReleaseKey;
}

juce::String SettingsProperties::getClsdMaxReleaseKey ()
{
    return kClsdMaxReleaseKey;
}

juce::String SettingsProperties::getClsdRelOfstScaleKey ()
{
    return kClsdRelOfstScaleKey;
}

juce::String SettingsProperties::getCvDisableFxKey ()
{
    return kCvDisableFxKey;
}

juce::String SettingsProperties::getCvDisableVelocityKey ()
{
    return kCvDisableVelocityKey;
}

juce::String SettingsProperties::getEnvelopeMaxReleaseKey ()
{
    return kEnvelopeMaxReleaseKey;
}

juce::String SettingsProperties::getFeelAmpModKey ()
{
    return kFeelAmpModKey;
}

juce::String SettingsProperties::getFeelAttackModKey ()
{
    return kFeelAttackModKey;
}

juce::String SettingsProperties::getFeelReleaseModKey ()
{
    return kFeelReleaseModKey;
}

juce::String SettingsProperties::getFltrHpfMaxFreqKey ()
{
    return kFltrHpfMaxFreqKey;
}

juce::String SettingsProperties::getFltrHpfMinFreqKey ()
{
    return kFltrHpfMinFreqKey;
}

juce::String SettingsProperties::getFltrHpfQKey ()
{
    return kFltrHpfQKey;
}

juce::String SettingsProperties::getFltrLpfMaxFreqKey ()
{
    return kFltrLpfMaxFreqKey;
}

juce::String SettingsProperties::getFltrLpfMinFreqKey ()
{
    return kFltrLpfMinFreqKey;
}

juce::String SettingsProperties::getFltrLpfQKey ()
{
    return kFltrLpfQKey;
}

juce::String SettingsProperties::getFxChorusCenterKey ()
{
    return kFxChorusCenterKey;
}

juce::String SettingsProperties::getFxChorusDepthKey ()
{
    return kFxChorusDepthKey;
}

juce::String SettingsProperties::getFxChorusLfoBKey ()
{
    return kFxChorusLfoBKey;
}

juce::String SettingsProperties::getFxChorusLfoTKey ()
{
    return kFxChorusLfoTKey;
}

juce::String SettingsProperties::getFxChorusMixKey ()
{
    return kFxChorusMixKey;
}

juce::String SettingsProperties::getFxChorusSpreadKey ()
{
    return kFxChorusSpreadKey;
}

juce::String SettingsProperties::getFxChorusStaggerKey ()
{
    return kFxChorusStaggerKey;
}

juce::String SettingsProperties::getFxChorusTapsKey ()
{
    return kFxChorusTapsKey;
}

juce::String SettingsProperties::getFxChorusTypeKey ()
{
    return kFxChorusTypeKey;
}

juce::String SettingsProperties::getFxCvUnipolarKey ()
{
    return kFxCvUnipolarKey;
}

juce::String SettingsProperties::getFxDjfilterHpfMaxKey ()
{
    return kFxDjfilterHpfMaxKey;
}

juce::String SettingsProperties::getFxDjfilterHpfMinKey ()
{
    return kFxDjfilterHpfMinKey;
}

juce::String SettingsProperties::getFxDjfilterLpfMaxKey ()
{
    return kFxDjfilterLpfMaxKey;
}

juce::String SettingsProperties::getFxDjfilterLpfMinKey ()
{
    return kFxDjfilterLpfMinKey;
}

juce::String SettingsProperties::getFxDjfilterQGainReductionKey ()
{
    return kFxDjfilterQGainReductionKey;
}

juce::String SettingsProperties::getFxDjfilterQMaxKey ()
{
    return kFxDjfilterQMaxKey;
}

juce::String SettingsProperties::getFxDjfilterQMinKey ()
{
    return kFxDjfilterQMinKey;
}

juce::String SettingsProperties::getFxDubEchoHpfKey ()
{
    return kFxDubEchoHpfKey;
}

juce::String SettingsProperties::getFxDubEchoLpfKey ()
{
    return kFxDubEchoLpfKey;
}

juce::String SettingsProperties::getFxDubEchoMixKey ()
{
    return kFxDubEchoMixKey;
}

juce::String SettingsProperties::getFxDubEchoTminKey ()
{
    return kFxDubEchoTminKey;
}

juce::String SettingsProperties::getFxGlitchCrushTimeMaxKey ()
{
    return kFxGlitchCrushTimeMaxKey;
}

juce::String SettingsProperties::getFxGlitchCrushTimeMinKey ()
{
    return kFxGlitchCrushTimeMinKey;
}

juce::String SettingsProperties::getFxGlitchDropKeepLevelMaxKey ()
{
    return kFxGlitchDropKeepLevelMaxKey;
}

juce::String SettingsProperties::getFxGlitchDropKeepLevelMinKey ()
{
    return kFxGlitchDropKeepLevelMinKey;
}

juce::String SettingsProperties::getFxGlitchDropKeepTimeMaxKey ()
{
    return kFxGlitchDropKeepTimeMaxKey;
}

juce::String SettingsProperties::getFxGlitchDropKeepTimeMinKey ()
{
    return kFxGlitchDropKeepTimeMinKey;
}

juce::String SettingsProperties::getFxGlitchMicroloopPlayTMaxKey ()
{
    return kFxGlitchMicroloopPlayTMaxKey;
}

juce::String SettingsProperties::getFxGlitchMicroloopPlayTMinKey ()
{
    return kFxGlitchMicroloopPlayTMinKey;
}

juce::String SettingsProperties::getFxGlitchMicroloopSmplTMaxKey ()
{
    return kFxGlitchMicroloopSmplTMaxKey;
}

juce::String SettingsProperties::getFxGlitchMicroloopSmplTMinKey ()
{
    return kFxGlitchMicroloopSmplTMinKey;
}

juce::String SettingsProperties::getFxGlitchProbabilityMaxKey ()
{
    return kFxGlitchProbabilityMaxKey;
}

juce::String SettingsProperties::getFxGlitchProbabilityMinKey ()
{
    return kFxGlitchProbabilityMinKey;
}

juce::String SettingsProperties::getFxGlitchStutterNumMaxKey ()
{
    return kFxGlitchStutterNumMaxKey;
}

juce::String SettingsProperties::getFxGlitchStutterNumMinKey ()
{
    return kFxGlitchStutterNumMinKey;
}

juce::String SettingsProperties::getFxGlitchStutterSmplTMaxKey ()
{
    return kFxGlitchStutterSmplTMaxKey;
}

juce::String SettingsProperties::getFxGlitchStutterSmplTMinKey ()
{
    return kFxGlitchStutterSmplTMinKey;
}

juce::String SettingsProperties::getFxGlitchStutterWindowKey ()
{
    return kFxGlitchStutterWindowKey;
}

juce::String SettingsProperties::getFxGlitchWeightCrushHighKey ()
{
    return kFxGlitchWeightCrushHighKey;
}

juce::String SettingsProperties::getFxGlitchWeightCrushLowKey ()
{
    return kFxGlitchWeightCrushLowKey;
}

juce::String SettingsProperties::getFxGlitchWeightDropHighKey ()
{
    return kFxGlitchWeightDropHighKey;
}

juce::String SettingsProperties::getFxGlitchWeightDropLowKey ()
{
    return kFxGlitchWeightDropLowKey;
}

juce::String SettingsProperties::getFxGlitchWeightHoldHighKey ()
{
    return kFxGlitchWeightHoldHighKey;
}

juce::String SettingsProperties::getFxGlitchWeightHoldLowKey ()
{
    return kFxGlitchWeightHoldLowKey;
}

juce::String SettingsProperties::getFxGlitchWeightStutterHighKey ()
{
    return kFxGlitchWeightStutterHighKey;
}

juce::String SettingsProperties::getFxGlitchWeightStutterLowKey ()
{
    return kFxGlitchWeightStutterLowKey;
}

juce::String SettingsProperties::getFxReverbDiffusionKey ()
{
    return kFxReverbDiffusionKey;
}

juce::String SettingsProperties::getFxReverbHpfKey ()
{
    return kFxReverbHpfKey;
}

juce::String SettingsProperties::getFxReverbLpfKey ()
{
    return kFxReverbLpfKey;
}

juce::String SettingsProperties::getFxReverbMixKey ()
{
    return kFxReverbMixKey;
}

juce::String SettingsProperties::getFxReverbModDepthKey ()
{
    return kFxReverbModDepthKey;
}

juce::String SettingsProperties::getFxReverbModRateKey ()
{
    return kFxReverbModRateKey;
}

juce::String SettingsProperties::getFxReverbPredelayKey ()
{
    return kFxReverbPredelayKey;
}

juce::String SettingsProperties::getFxReverbSizeMaxKey ()
{
    return kFxReverbSizeMaxKey;
}

juce::String SettingsProperties::getFxReverbSizeMinKey ()
{
    return kFxReverbSizeMinKey;
}

juce::String SettingsProperties::getFxReverbTypeKey ()
{
    return kFxReverbTypeKey;
}

juce::String SettingsProperties::getGateModeKey ()
{
    return kGateModeKey;
}

juce::String SettingsProperties::getKnobPosTakeupKey ()
{
    return kKnobPosTakeupKey;
}

juce::String SettingsProperties::getPitchHighKey ()
{
    return kPitchHighKey;
}

juce::String SettingsProperties::getPitchLowKey ()
{
    return kPitchLowKey;
}

juce::String SettingsProperties::getReleaseModeKey ()
{
    return kReleaseModeKey;
}

juce::String SettingsProperties::getVelocityUnipolarKey ()
{
    return kVelocityUnipolarKey;
}
