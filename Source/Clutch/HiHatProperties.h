#pragma once

#include <JuceHeader.h>
#include "../Utility/ValueTreeWrapper.h"

struct HiHatSettings
{
    juce::String key;
    juce::String value;
    juce::String defaultValue;
};

const HiHatSettings hiHatSettings []
{
    {"PITCH_LOW", "0.125", "0.125"},
    {"PITCH_HIGH", "2.5", "2.5"},
    {"ENVELOPE_MAX_RELEASE", "4.000", "4.000"},
    {"CHOKE_RELEASE", "0.080", "0.080"},
    {"CLSD_RELEASE_MODE", "1", "1"},
    {"CLSD_REL_OFST_SCALE", "0.5", "0.5"},
    {"CLSD_MAX_RELEASE", "0.8", "0.8"},
    {"ACC_CL_REL_MOD", "1.18", "1.18"},
    {"ACC_OP_REL_MOD", "1.25", "1.25"},
    {"ACC_CL_AMP_MOD", "1.3", "1.3"},
    {"ACC_OP_AMP_MOD", "1.25", "1.25"},
    {"FX_CV_UNIPOLAR", "1", "1"},
    {"VELOCITY_UNIPOLAR", "0", "0"},
    {"CV_DISABLE_VELOCITY", "0", "0"},
    {"CV_DISABLE_FX", "0", "0"},
    {"GATE_MODE", "0", "0"},
    {"FEEL_ATTACK_MOD", "1.0", "1.0"},
    {"FEEL_RELEASE_MOD", "1.0", "1.0"},
    {"FEEL_AMP_MOD", "1.0", "1.0"},
    {"KNOB_POS_TAKEUP", "1", "1"},
    {"FLTR_HPF_MIN_FREQ", "100", "100"},
    {"FLTR_HPF_MAX_FREQ", "14000", "14000"},
    {"FLTR_LPF_MIN_FREQ", "200", "200"},
    {"FLTR_LPF_MAX_FREQ", "20000", "20000"},
    {"FLTR_HPF_Q", "1.0", "1.0"},
    {"FLTR_LPF_Q", "0.707", "0.707"},
    {"FX_DJFILTER_HPF_MIN", "100", "100"},
    {"FX_DJFILTER_HPF_MAX", "14000", "14000"},
    {"FX_DJFILTER_LPF_MIN", "200", "200"},
    {"FX_DJFILTER_LPF_MAX", "20000", "20000"},
    {"FX_DJFILTER_Q_MIN", "0.5", "0.5"},
    {"FX_DJFILTER_Q_MAX", "4.0", "4.0"},
    {"FX_DJFILTER_Q_GAIN_REDUCTION", "0.12", "0.12"},
    {"FX_DUB_ECHO_TMIN", "30", "30"},
    {"FX_DUB_ECHO_HPF", "400", "400"},
    {"FX_DUB_ECHO_LPF", "8400", "8400"},
    {"FX_DUB_ECHO_MIX", "0.38", "0.38"},
    {"FX_CHORUS_CENTER", "12.0", "12.0"},
    {"FX_CHORUS_DEPTH", "5.0", "5.0"},
    {"FX_CHORUS_MIX", "1.0", "1.0"},
    {"FX_CHORUS_SPREAD", "0.01", "0.01"},
    {"FX_CHORUS_TAPS", "4", "4"},
    {"FX_CHORUS_LFO_B", "0.002", "0.002"},
    {"FX_CHORUS_LFO_T", "3", "3"},
    {"FX_REVERB_LPF", "9000", "9000"},
    {"FX_REVERB_HPF", "700", "700"},
    {"FX_GLITCH_PROBABILITY_MIN", "0.00005", "0.00005"},
    {"FX_GLITCH_PROBABILITY_MAX", "0.003", "0.003"},
    {"FX_GLITCH_WEIGHT_HOLD_LOW", "0.15", "0.15"},
    {"FX_GLITCH_WEIGHT_STUTTER_LOW", "0.05", "0.05"},
    {"FX_GLITCH_WEIGHT_CRUSH_LOW", "0.30", "0.30"},
    {"FX_GLITCH_WEIGHT_DROP_LOW", "0.02", "0.02"},
    {"FX_GLITCH_WEIGHT_HOLD_HIGH", "0.30", "0.30"},
    {"FX_GLITCH_WEIGHT_STUTTER_HIGH", "0.20", "0.20"},
    {"FX_GLITCH_WEIGHT_CRUSH_HIGH", "0.20", "0.20"},
    {"FX_GLITCH_WEIGHT_DROP_HIGH", "0.07", "0.07"},
    {"FX_GLITCH_DROP_KEEP_LEVEL_MIN", "0.0", "0.0"},
    {"FX_GLITCH_DROP_KEEP_LEVEL_MAX", "0.75", "0.75"},
    {"FX_GLITCH_DROP_KEEP_TIME_MIN", "4.0", "4.0"},
    {"FX_GLITCH_DROP_KEEP_TIME_MAX", "40.0", "40.0"},
    {"FX_GLITCH_CRUSH_TIME_MIN", "10.0", "10.0"},
    {"FX_GLITCH_CRUSH_TIME_MAX", "50.0", "50.0"},
    {"FX_GLITCH_MICROLOOP_SMPL_T_MIN", "0.2", "0.2"},
    {"FX_GLITCH_MICROLOOP_SMPL_T_MAX", "3.0", "3.0"},
    {"FX_GLITCH_MICROLOOP_PLAY_T_MIN", "5.0", "5.0"},
    {"FX_GLITCH_MICROLOOP_PLAY_T_MAX", "15.0", "15.0"},
    {"FX_GLITCH_STUTTER_SMPL_T_MIN", "3.0", "3.0"},
    {"FX_GLITCH_STUTTER_SMPL_T_MAX", "10.0", "10.0"},
    {"FX_GLITCH_STUTTER_NUM_MIN", "2", "2"},
    {"FX_GLITCH_STUTTER_NUM_MAX", "5", "5"},
    {"FX_GLITCH_STUTTER_WINDOW", "20", "20"},
};

class HiHatProperties : public ValueTreeWrapper<HiHatProperties>
{
public:
    HiHatProperties () noexcept : ValueTreeWrapper<HiHatProperties> (HiHatTypeId)
    {
    }
    HiHatProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<HiHatProperties> (HiHatTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setPitchLow (float value, bool includeSelfCallback);
    void setPitchHigh (float value, bool includeSelfCallback);
    void setEnvelopeMaxRelease (float value, bool includeSelfCallback);
    void setChokeRelease (float value, bool includeSelfCallback);
    void setClsdReleaseMode (int value, bool includeSelfCallback);
    void setClsdRelOfstScale (float value, bool includeSelfCallback);
    void setClsdMaxRelease (float value, bool includeSelfCallback);
    void setAccClRelMod (float value, bool includeSelfCallback);
    void setAccOpRelMod (float value, bool includeSelfCallback);
    void setAccClAmpMod (float value, bool includeSelfCallback);
    void setAccOpAmpMod (float value, bool includeSelfCallback);
    void setFxCvUnipolar (int value, bool includeSelfCallback);
    void setVelocityUnipolar (int value, bool includeSelfCallback);
    void setCvDisableVelocity (int value, bool includeSelfCallback);
    void setCvDisableFx (int value, bool includeSelfCallback);
    void setGateMode (int value, bool includeSelfCallback);
    void setFeelAttackMod (float value, bool includeSelfCallback);
    void setFeelReleaseMod (float value, bool includeSelfCallback);
    void setFeelAmpMod (float value, bool includeSelfCallback);
    void setKnobPosTakeup (int value, bool includeSelfCallback);
    void setFltrHpfMinFreq (int value, bool includeSelfCallback);
    void setFltrHpfMaxFreq (int value, bool includeSelfCallback);
    void setFltrLpfMinFreq (int value, bool includeSelfCallback);
    void setFltrLpfMaxFreq (int value, bool includeSelfCallback);
    void setFltrHpfQ (float value, bool includeSelfCallback);
    void setFltrLpfQ (float value, bool includeSelfCallback);
    void setFxDjfilterHpfMin (int value, bool includeSelfCallback);
    void setFxDjfilterHpfMax (int value, bool includeSelfCallback);
    void setFxDjfilterLpfMin (int value, bool includeSelfCallback);
    void setFxDjfilterLpfMax (int value, bool includeSelfCallback);
    void setFxDjfilterQMin (float value, bool includeSelfCallback);
    void setFxDjfilterQMax (float value, bool includeSelfCallback);
    void setFxDjfilterQGainReduction (float value, bool includeSelfCallback);
    void setFxDubEchoTmin (int value, bool includeSelfCallback);
    void setFxDubEchoHpf (int value, bool includeSelfCallback);
    void setFxDubEchoLpf (int value, bool includeSelfCallback);
    void setFxDubEchoMix (float value, bool includeSelfCallback);
    void setFxChorusCenter (float value, bool includeSelfCallback);
    void setFxChorusDepth (float value, bool includeSelfCallback);
    void setFxChorusMix (float value, bool includeSelfCallback);
    void setFxChorusSpread (float value, bool includeSelfCallback);
    void setFxChorusTaps (int value, bool includeSelfCallback);
    void setFxChorusLfoB (float value, bool includeSelfCallback);
    void setFxChorusLfoT (int value, bool includeSelfCallback);
    void setFxReverbLpf (int value, bool includeSelfCallback);
    void setFxReverbHpf (int value, bool includeSelfCallback);
    void setFxGlitchProbabilityMin (float value, bool includeSelfCallback);
    void setFxGlitchProbabilityMax (float value, bool includeSelfCallback);
    void setFxGlitchWeightHoldLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightStutterLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightCrushLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightDropLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightHoldHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightStutterHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightCrushHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightDropHigh (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepLevelMin (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepLevelMax (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepTimeMin (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepTimeMax (float value, bool includeSelfCallback);
    void setFxGlitchCrushTimeMin (float value, bool includeSelfCallback);
    void setFxGlitchCrushTimeMax (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopSmplTMin (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopSmplTMax (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopPlayTMin (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopPlayTMax (float value, bool includeSelfCallback);
    void setFxGlitchStutterSmplTMin (float value, bool includeSelfCallback);
    void setFxGlitchStutterSmplTMax (float value, bool includeSelfCallback);
    void setFxGlitchStutterNumMin (int value, bool includeSelfCallback);
    void setFxGlitchStutterNumMax (int value, bool includeSelfCallback);
    void setFxGlitchStutterWindow (int value, bool includeSelfCallback);

    float getPitchLow ();
    float getPitchHigh ();
    float getEnvelopeMaxRelease ();
    float getChokeRelease ();
    int getClsdReleaseMode ();
    float getClsdRelOfstScale ();
    float getClsdMaxRelease ();
    float getAccClRelMod ();
    float getAccOpRelMod ();
    float getAccClAmpMod ();
    float getAccOpAmpMod ();
    int getFxCvUnipolar ();
    int getVelocityUnipolar ();
    int getCvDisableVelocity ();
    int getCvDisableFx ();
    int getGateMode ();
    float getFeelAttackMod ();
    float getFeelReleaseMod ();
    float getFeelAmpMod ();
    int getKnobPosTakeup ();
    int getFltrHpfMinFreq ();
    int getFltrHpfMaxFreq ();
    int getFltrLpfMinFreq ();
    int getFltrLpfMaxFreq ();
    float getFltrHpfQ ();
    float getFltrLpfQ ();
    int getFxDjfilterHpfMin ();
    int getFxDjfilterHpfMax ();
    int getFxDjfilterLpfMin ();
    int getFxDjfilterLpfMax ();
    float getFxDjfilterQMin ();
    float getFxDjfilterQMax ();
    float getFxDjfilterQGainReduction ();
    int getFxDubEchoTmin ();
    int getFxDubEchoHpf ();
    int getFxDubEchoLpf ();
    float getFxDubEchoMix ();
    float getFxChorusCenter ();
    float getFxChorusDepth ();
    float getFxChorusMix ();
    float getFxChorusSpread ();
    int getFxChorusTaps ();
    float getFxChorusLfoB ();
    int getFxChorusLfoT ();
    int getFxReverbLpf ();
    int getFxReverbHpf ();
    float getFxGlitchProbabilityMin ();
    float getFxGlitchProbabilityMax ();
    float getFxGlitchWeightHoldLow ();
    float getFxGlitchWeightStutterLow ();
    float getFxGlitchWeightCrushLow ();
    float getFxGlitchWeightDropLow ();
    float getFxGlitchWeightHoldHigh ();
    float getFxGlitchWeightStutterHigh ();
    float getFxGlitchWeightCrushHigh ();
    float getFxGlitchWeightDropHigh ();
    float getFxGlitchDropKeepLevelMin ();
    float getFxGlitchDropKeepLevelMax ();
    float getFxGlitchDropKeepTimeMin ();
    float getFxGlitchDropKeepTimeMax ();
    float getFxGlitchCrushTimeMin ();
    float getFxGlitchCrushTimeMax ();
    float getFxGlitchMicroloopSmplTMin ();
    float getFxGlitchMicroloopSmplTMax ();
    float getFxGlitchMicroloopPlayTMin ();
    float getFxGlitchMicroloopPlayTMax ();
    float getFxGlitchStutterSmplTMin ();
    float getFxGlitchStutterSmplTMax ();
    int getFxGlitchStutterNumMin ();
    int getFxGlitchStutterNumMax ();
    int getFxGlitchStutterWindow ();

    juce::String getPitchLowKey ();
    juce::String getPitchHighKey ();
    juce::String getEnvelopeMaxReleaseKey ();
    juce::String getChokeReleaseKey ();
    juce::String getClsdReleaseModeKey ();
    juce::String getClsdRelOfstScaleKey ();
    juce::String getClsdMaxReleaseKey ();
    juce::String getAccClRelModKey ();
    juce::String getAccOpRelModKey ();
    juce::String getAccClAmpModKey ();
    juce::String getAccOpAmpModKey ();
    juce::String getFxCvUnipolarKey ();
    juce::String getVelocityUnipolarKey ();
    juce::String getCvDisableVelocityKey ();
    juce::String getCvDisableFxKey ();
    juce::String getGateModeKey ();
    juce::String getFeelAttackModKey ();
    juce::String getFeelReleaseModKey ();
    juce::String getFeelAmpModKey ();
    juce::String getKnobPosTakeupKey ();
    juce::String getFltrHpfMinFreqKey ();
    juce::String getFltrHpfMaxFreqKey ();
    juce::String getFltrLpfMinFreqKey ();
    juce::String getFltrLpfMaxFreqKey ();
    juce::String getFltrHpfQKey ();
    juce::String getFltrLpfQKey ();
    juce::String getFxDjfilterHpfMinKey ();
    juce::String getFxDjfilterHpfMaxKey ();
    juce::String getFxDjfilterLpfMinKey ();
    juce::String getFxDjfilterLpfMaxKey ();
    juce::String getFxDjfilterQMinKey ();
    juce::String getFxDjfilterQMaxKey ();
    juce::String getFxDjfilterQGainReductionKey ();
    juce::String getFxDubEchoTminKey ();
    juce::String getFxDubEchoHpfKey ();
    juce::String getFxDubEchoLpfKey ();
    juce::String getFxDubEchoMixKey ();
    juce::String getFxChorusCenterKey ();
    juce::String getFxChorusDepthKey ();
    juce::String getFxChorusMixKey ();
    juce::String getFxChorusSpreadKey ();
    juce::String getFxChorusTapsKey ();
    juce::String getFxChorusLfoBKey ();
    juce::String getFxChorusLfoTKey ();
    juce::String getFxReverbLpfKey ();
    juce::String getFxReverbHpfKey ();
    juce::String getFxGlitchProbabilityMinKey ();
    juce::String getFxGlitchProbabilityMaxKey ();
    juce::String getFxGlitchWeightHoldLowKey ();
    juce::String getFxGlitchWeightStutterLowKey ();
    juce::String getFxGlitchWeightCrushLowKey ();
    juce::String getFxGlitchWeightDropLowKey ();
    juce::String getFxGlitchWeightHoldHighKey ();
    juce::String getFxGlitchWeightStutterHighKey ();
    juce::String getFxGlitchWeightCrushHighKey ();
    juce::String getFxGlitchWeightDropHighKey ();
    juce::String getFxGlitchDropKeepLevelMinKey ();
    juce::String getFxGlitchDropKeepLevelMaxKey ();
    juce::String getFxGlitchDropKeepTimeMinKey ();
    juce::String getFxGlitchDropKeepTimeMaxKey ();
    juce::String getFxGlitchCrushTimeMinKey ();
    juce::String getFxGlitchCrushTimeMaxKey ();
    juce::String getFxGlitchMicroloopSmplTMinKey ();
    juce::String getFxGlitchMicroloopSmplTMaxKey ();
    juce::String getFxGlitchMicroloopPlayTMinKey ();
    juce::String getFxGlitchMicroloopPlayTMaxKey ();
    juce::String getFxGlitchStutterSmplTMinKey ();
    juce::String getFxGlitchStutterSmplTMaxKey ();
    juce::String getFxGlitchStutterNumMinKey ();
    juce::String getFxGlitchStutterNumMaxKey ();
    juce::String getFxGlitchStutterWindowKey ();

    std::function<void (float value)> onPitchLowChange;
    std::function<void (float value)> onPitchHighChange;
    std::function<void (float value)> onEnvelopeMaxReleaseChange;
    std::function<void (float value)> onChokeReleaseChange;
    std::function<void (int value)> onClsdReleaseModeChange;
    std::function<void (float value)> onClsdRelOfstScaleChange;
    std::function<void (float value)> onClsdMaxReleaseChange;
    std::function<void (float value)> onAccClRelModChange;
    std::function<void (float value)> onAccOpRelModChange;
    std::function<void (float value)> onAccClAmpModChange;
    std::function<void (float value)> onAccOpAmpModChange;
    std::function<void (int value)> onFxCvUnipolarChange;
    std::function<void (int value)> onVelocityUnipolarChange;
    std::function<void (int value)> onCvDisableVelocityChange;
    std::function<void (int value)> onCvDisableFxChange;
    std::function<void (int value)> onGateModeChange;
    std::function<void (float value)> onFeelAttackModChange;
    std::function<void (float value)> onFeelReleaseModChange;
    std::function<void (float value)> onFeelAmpModChange;
    std::function<void (int value)> onKnobPosTakeupChange;
    std::function<void (int value)> onFltrHpfMinFreqChange;
    std::function<void (int value)> onFltrHpfMaxFreqChange;
    std::function<void (int value)> onFltrLpfMinFreqChange;
    std::function<void (int value)> onFltrLpfMaxFreqChange;
    std::function<void (float value)> onFltrHpfQChange;
    std::function<void (float value)> onFltrLpfQChange;
    std::function<void (int value)> onFxDjfilterHpfMinChange;
    std::function<void (int value)> onFxDjfilterHpfMaxChange;
    std::function<void (int value)> onFxDjfilterLpfMinChange;
    std::function<void (int value)> onFxDjfilterLpfMaxChange;
    std::function<void (float value)> onFxDjfilterQMinChange;
    std::function<void (float value)> onFxDjfilterQMaxChange;
    std::function<void (float value)> onFxDjfilterQGainReductionChange;
    std::function<void (int value)> onFxDubEchoTminChange;
    std::function<void (int value)> onFxDubEchoHpfChange;
    std::function<void (int value)> onFxDubEchoLpfChange;
    std::function<void (float value)> onFxDubEchoMixChange;
    std::function<void (float value)> onFxChorusCenterChange;
    std::function<void (float value)> onFxChorusDepthChange;
    std::function<void (float value)> onFxChorusMixChange;
    std::function<void (float value)> onFxChorusSpreadChange;
    std::function<void (int value)> onFxChorusTapsChange;
    std::function<void (float value)> onFxChorusLfoBChange;
    std::function<void (int value)> onFxChorusLfoTChange;
    std::function<void (int value)> onFxReverbLpfChange;
    std::function<void (int value)> onFxReverbHpfChange;
    std::function<void (float value)> onFxGlitchProbabilityMinChange;
    std::function<void (float value)> onFxGlitchProbabilityMaxChange;
    std::function<void (float value)> onFxGlitchWeightHoldLowChange;
    std::function<void (float value)> onFxGlitchWeightStutterLowChange;
    std::function<void (float value)> onFxGlitchWeightCrushLowChange;
    std::function<void (float value)> onFxGlitchWeightDropLowChange;
    std::function<void (float value)> onFxGlitchWeightHoldHighChange;
    std::function<void (float value)> onFxGlitchWeightStutterHighChange;
    std::function<void (float value)> onFxGlitchWeightCrushHighChange;
    std::function<void (float value)> onFxGlitchWeightDropHighChange;
    std::function<void (float value)> onFxGlitchDropKeepLevelMinChange;
    std::function<void (float value)> onFxGlitchDropKeepLevelMaxChange;
    std::function<void (float value)> onFxGlitchDropKeepTimeMinChange;
    std::function<void (float value)> onFxGlitchDropKeepTimeMaxChange;
    std::function<void (float value)> onFxGlitchCrushTimeMinChange;
    std::function<void (float value)> onFxGlitchCrushTimeMaxChange;
    std::function<void (float value)> onFxGlitchMicroloopSmplTMinChange;
    std::function<void (float value)> onFxGlitchMicroloopSmplTMaxChange;
    std::function<void (float value)> onFxGlitchMicroloopPlayTMinChange;
    std::function<void (float value)> onFxGlitchMicroloopPlayTMaxChange;
    std::function<void (float value)> onFxGlitchStutterSmplTMinChange;
    std::function<void (float value)> onFxGlitchStutterSmplTMaxChange;
    std::function<void (int value)> onFxGlitchStutterNumMinChange;
    std::function<void (int value)> onFxGlitchStutterNumMaxChange;
    std::function<void (int value)> onFxGlitchStutterWindowChange;

    //void copyFrom (juce::ValueTree sourceVT, bool settingsOnly);
    //static juce::ValueTree create (int id);

    static inline const juce::Identifier HiHatTypeId { "HiHat" };
    static inline const juce::Identifier PitchLowPropertyId { "pitchLow" };
    static inline const juce::Identifier PitchHighPropertyId { "pitchHigh" };
    static inline const juce::Identifier EnvelopeMaxReleasePropertyId { "envelopeMaxRelease" };
    static inline const juce::Identifier ChokeReleasePropertyId { "chokeRelease" };
    static inline const juce::Identifier ClsdReleaseModePropertyId { "clsdReleaseMode" };
    static inline const juce::Identifier ClsdRelOfstScalePropertyId { "clsdRelOfstScale" };
    static inline const juce::Identifier ClsdMaxReleasePropertyId { "clsdMaxRelease" };
    static inline const juce::Identifier AccClRelModPropertyId { "accClRelMod" };
    static inline const juce::Identifier AccOpRelModPropertyId { "accOpRelMod" };
    static inline const juce::Identifier AccClAmpModPropertyId { "accClAmpMod" };
    static inline const juce::Identifier AccOpAmpModPropertyId { "accOpAmpMod" };
    static inline const juce::Identifier FxCvUnipolarPropertyId { "fxCvUnipolar" };
    static inline const juce::Identifier VelocityUnipolarPropertyId { "velocityUnipolar" };
    static inline const juce::Identifier CvDisableVelocityPropertyId { "cvDisableVelocity" };
    static inline const juce::Identifier CvDisableFxPropertyId { "cvDisableFx" };
    static inline const juce::Identifier GateModePropertyId { "gateMode" };
    static inline const juce::Identifier FeelAttackModPropertyId { "feelAttackMod" };
    static inline const juce::Identifier FeelReleaseModPropertyId { "feelReleaseMod" };
    static inline const juce::Identifier FeelAmpModPropertyId { "feelAmpMod" };
    static inline const juce::Identifier KnobPosTakeupPropertyId { "knobPosTakeup" };
    static inline const juce::Identifier FltrHpfMinFreqPropertyId { "fltrHpfMinFreq" };
    static inline const juce::Identifier FltrHpfMaxFreqPropertyId { "fltrHpfMaxFreq" };
    static inline const juce::Identifier FltrLpfMinFreqPropertyId { "fltrLpfMinFreq" };
    static inline const juce::Identifier FltrLpfMaxFreqPropertyId { "fltrLpfMaxFreq" };
    static inline const juce::Identifier FltrHpfQPropertyId { "fltrHpfQ" };
    static inline const juce::Identifier FltrLpfQPropertyId { "fltrLpfQ" };
    static inline const juce::Identifier FxDjfilterHpfMinPropertyId { "fxDjfilterHpfMin" };
    static inline const juce::Identifier FxDjfilterHpfMaxPropertyId { "fxDjfilterHpfMax" };
    static inline const juce::Identifier FxDjfilterLpfMinPropertyId { "fxDjfilterLpfMin" };
    static inline const juce::Identifier FxDjfilterLpfMaxPropertyId { "fxDjfilterLpfMax" };
    static inline const juce::Identifier FxDjfilterQMinPropertyId { "fxDjfilterQMin" };
    static inline const juce::Identifier FxDjfilterQMaxPropertyId { "fxDjfilterQMax" };
    static inline const juce::Identifier FxDjfilterQGainReductionPropertyId { "fxDjfilterQGainReduction" };
    static inline const juce::Identifier FxDubEchoTminPropertyId { "fxDubEchoTmin" };
    static inline const juce::Identifier FxDubEchoHpfPropertyId { "fxDubEchoHpf" };
    static inline const juce::Identifier FxDubEchoLpfPropertyId { "fxDubEchoLpf" };
    static inline const juce::Identifier FxDubEchoMixPropertyId { "fxDubEchoMix" };
    static inline const juce::Identifier FxChorusCenterPropertyId { "fxChorusCenter" };
    static inline const juce::Identifier FxChorusDepthPropertyId { "fxChorusDepth" };
    static inline const juce::Identifier FxChorusMixPropertyId { "fxChorusMix" };
    static inline const juce::Identifier FxChorusSpreadPropertyId { "fxChorusSpread" };
    static inline const juce::Identifier FxChorusTapsPropertyId { "fxChorusTaps" };
    static inline const juce::Identifier FxChorusLfoBPropertyId { "fxChorusLfoB" };
    static inline const juce::Identifier FxChorusLfoTPropertyId { "fxChorusLfoT" };
    static inline const juce::Identifier FxReverbLpfPropertyId { "fxReverbLpf" };
    static inline const juce::Identifier FxReverbHpfPropertyId { "fxReverbHpf" };
    static inline const juce::Identifier FxGlitchProbabilityMinPropertyId { "fxGlitchProbabilityMin" };
    static inline const juce::Identifier FxGlitchProbabilityMaxPropertyId { "fxGlitchProbabilityMax" };
    static inline const juce::Identifier FxGlitchWeightHoldLowPropertyId { "fxGlitchWeightHoldLow" };
    static inline const juce::Identifier FxGlitchWeightStutterLowPropertyId { "fxGlitchWeightStutterLow" };
    static inline const juce::Identifier FxGlitchWeightCrushLowPropertyId { "fxGlitchWeightCrushLow" };
    static inline const juce::Identifier FxGlitchWeightDropLowPropertyId { "fxGlitchWeightDropLow" };
    static inline const juce::Identifier FxGlitchWeightHoldHighPropertyId { "fxGlitchWeightHoldHigh" };
    static inline const juce::Identifier FxGlitchWeightStutterHighPropertyId { "fxGlitchWeightStutterHigh" };
    static inline const juce::Identifier FxGlitchWeightCrushHighPropertyId { "fxGlitchWeightCrushHigh" };
    static inline const juce::Identifier FxGlitchWeightDropHighPropertyId { "fxGlitchWeightDropHigh" };
    static inline const juce::Identifier FxGlitchDropKeepLevelMinPropertyId { "fxGlitchDropKeepLevelMin" };
    static inline const juce::Identifier FxGlitchDropKeepLevelMaxPropertyId { "fxGlitchDropKeepLevelMax" };
    static inline const juce::Identifier FxGlitchDropKeepTimeMinPropertyId { "fxGlitchDropKeepTimeMin" };
    static inline const juce::Identifier FxGlitchDropKeepTimeMaxPropertyId { "fxGlitchDropKeepTimeMax" };
    static inline const juce::Identifier FxGlitchCrushTimeMinPropertyId { "fxGlitchCrushTimeMin" };
    static inline const juce::Identifier FxGlitchCrushTimeMaxPropertyId { "fxGlitchCrushTimeMax" };
    static inline const juce::Identifier FxGlitchMicroloopSmplTMinPropertyId { "fxGlitchMicroloopSmplTMin" };
    static inline const juce::Identifier FxGlitchMicroloopSmplTMaxPropertyId { "fxGlitchMicroloopSmplTMax" };
    static inline const juce::Identifier FxGlitchMicroloopPlayTMinPropertyId { "fxGlitchMicroloopPlayTMin" };
    static inline const juce::Identifier FxGlitchMicroloopPlayTMaxPropertyId { "fxGlitchMicroloopPlayTMax" };
    static inline const juce::Identifier FxGlitchStutterSmplTMinPropertyId { "fxGlitchStutterSmplTMin" };
    static inline const juce::Identifier FxGlitchStutterSmplTMaxPropertyId { "fxGlitchStutterSmplTMax" };
    static inline const juce::Identifier FxGlitchStutterNumMinPropertyId { "fxGlitchStutterNumMin" };
    static inline const juce::Identifier FxGlitchStutterNumMaxPropertyId { "fxGlitchStutterNumMax" };
    static inline const juce::Identifier FxGlitchStutterWindowPropertyId { "fxGlitchStutterWindow" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};

/*
[HIHAT]
; Pitch control multiplier (both Surface A and Surface B)
PITCH_LOW = 0.125; Min pitch 0.001 to 0.5                                  d: 0.125
PITCH_HIGH = 2.5; Max pitch 1.5 to 3.7                                    d: 2.5
; Envelope Release Parameters in seconds
ENVELOPE_MAX_RELEASE = 4.000; Max release 0.6 to 20 s                                 d : 4.0
CHOKE_RELEASE = 0.080; Choke release time                                      d : 0.080
; CLOSED Hit Release scale options and modifiers
CLSD_RELEASE_MODE = 1; 1: Release Offset mode                                  d : 1
; 0: Independent Release for Closed
; Scale of envelope for closed hits (multiply ENV_MAX_RELEASE for Closed Hits)
; Only applies if CLSD_RELEASE_MODE = 1
CLSD_REL_OFST_SCALE = 0.5; Range 0.1 to 0.9                                        d: 0.5
; CLOSED Hit Max Release, only applies if CLSD_RELEASE_MODE = 0
CLSD_MAX_RELEASE = 0.8; Max release time 0.3 to 2.0                             d: 0.8
; Envelope Release Modifiers for Accented hits, extends release (FEEL OFF)
ACC_CL_REL_MOD = 1.18; Release Mod CLOSED ACC hit                              d : 1.18
ACC_OP_REL_MOD = 1.25; Release Mod OPEN ACC hit                                d : 1.25
ACC_CL_AMP_MOD = 1.3; Amp Mod CLOSED ACC hit                                  d : 1.3
ACC_OP_AMP_MOD = 1.25; Amp Mod OPEN ACC hit                                    d : 1.25
; CV Bipolar or Unipolar options
FX_CV_UNIPOLAR = 1; 0: -5 to 5V, 1 : 0 to 5V                                 d : 1
VELOCITY_UNIPOLAR = 0; 0: 0V = 100 % -5 = 0 % +5 = 200 % d : 0, 1: 0V = 10 % +5 = 100 %
; CV OFF / ON Switch Options
CV_DISABLE_VELOCITY = 0; 0: Velocity always enabled, 1: CV Off SW affects velocity                              d : 0
;
CV_DISABLE_FX = 0; 0: FX CV Always On                                      d : 0
; 1: CV Disable : Freeze FX CV
; Gate behavior
GATE_MODE = 0; 0: Release immediately (TRIGGER MODE)                   d : 0
; 1: Release after gate falls
; Feel behavior - modulation multipliers for feel params
FEEL_ATTACK_MOD = 1.0; 0.000 (none) to 5.000 (5x)                              d: 1.0
FEEL_RELEASE_MOD = 1.0; 0.000 (none) to 5.000 (5x)                              d: 1.0
FEEL_AMP_MOD = 1.0; 0.000 (none) to 2.000 (2x)                              d: 1.0
; Multipurpose Knobs - Wiggle or Positional Takeup
KNOB_POS_TAKEUP = 1; 0 to sense small movement (wiggle)                      d: 0
; 1 to require passing old value
; Filter Frequency Ranges
FLTR_HPF_MIN_FREQ = 100; HPF minimum frequency (Hz)                              d: 100
FLTR_HPF_MAX_FREQ = 14000; HPF maximum frequency (Hz)                              d: 14000
FLTR_LPF_MIN_FREQ = 200; LPF minimum frequency (Hz)                              d: 200
FLTR_LPF_MAX_FREQ = 20000; LPF maximum frequency (Hz)                              d: 20000
FLTR_HPF_Q = 1.0; HPF resonance (Q factor) 0.25 - 4.0                     d: 1.0
FLTR_LPF_Q = 0.707; LPF resonance (Q factor) 0.25 - 4.0                     d: 0.707
; DJ Filter Frequency Ranges
FX_DJFILTER_HPF_MIN = 100; DJ HPF minimum frequency (Hz)                           d: 100
FX_DJFILTER_HPF_MAX = 14000; DJ HPF maximum frequency (Hz)                           d: 14000
FX_DJFILTER_LPF_MIN = 200; DJ LPF minimum frequency (Hz)                           d: 200
FX_DJFILTER_LPF_MAX = 20000; DJ LPF maximum frequency (Hz)                           d: 20000
FX_DJFILTER_Q_MIN = 0.5; DJ Filter minimum Q (resonance)                         d: 0.5
FX_DJFILTER_Q_MAX = 4.0; DJ Filter maximum Q (resonance)                         d: 4.0
FX_DJFILTER_Q_GAIN_REDUCTION = 0.12; Gain reduction factor for high Q                        d : 0.12
; FX Parameters — voicing for specific effects
FX_DUB_ECHO_TMIN = 30; Minimum Time at PARAM CCW                               d : 30
FX_DUB_ECHO_HPF = 400; HPF Cutoff Frequency (Hz)                               d: 400
FX_DUB_ECHO_LPF = 8400; LPF Cutoff Frequency (Hz)                               d: 8400
FX_DUB_ECHO_MIX = 0.38; MIX level for DUB ECHO                                  d : 0.38
FX_CHORUS_CENTER = 12.0; Center Delay in ms (1–120)                              d: 12.0
FX_CHORUS_DEPTH = 5.0; Depth in ms (1–CENTER)                                  d: 5.0
FX_CHORUS_MIX = 1.0; Mix level (0.1–1)                                       d: 1.0
FX_CHORUS_SPREAD = 0.01; LFO Freq Spread% per tap                               d : 0.01
FX_CHORUS_TAPS = 4; Integer # of Taps (1–4)                                 d: 4
FX_CHORUS_LFO_B = 0.002; LFO at slowest in Hz                                    d : 0.002
FX_CHORUS_LFO_T = 3; LFO at fastest in Hz                                    d : 3
FX_REVERB_LPF = 9000; LPF for FB in Hz                                        d : 9000
FX_REVERB_HPF = 700; HPF for FB in Hz                                        d : 700
; ---- - Glitch Engine (probabilities, weights, and per - mode timing / levels) ---- -
FX_GLITCH_PROBABILITY_MIN = 0.00005; Master probability to glitch at PARAM 0 % d: 0.00005
FX_GLITCH_PROBABILITY_MAX = 0.003; Master probability to glitch at PARAM 100 % d: 0.003
FX_GLITCH_WEIGHT_HOLD_LOW = 0.15; Weighted chance of hold at PARAM 0 % d: 0.15
FX_GLITCH_WEIGHT_STUTTER_LOW = 0.05; Weighted chance of stutter at PARAM 0 % d: 0.05
FX_GLITCH_WEIGHT_CRUSH_LOW = 0.30; Weighted chance of bit crush at PARAM 0 % d: 0.30
FX_GLITCH_WEIGHT_DROP_LOW = 0.02; Weighted chance of dropout at PARAM 0 % d: 0.02
FX_GLITCH_WEIGHT_HOLD_HIGH = 0.30; Weighted chance of hold at PARAM 100 % d: 0.30
FX_GLITCH_WEIGHT_STUTTER_HIGH = 0.20; Weighted chance of stutter at PARAM 100 % d: 0.20
FX_GLITCH_WEIGHT_CRUSH_HIGH = 0.20; Weighted chance of bit crush at PARAM 100 % d: 0.20
FX_GLITCH_WEIGHT_DROP_HIGH = 0.07; Weighted chance of dropout at PARAM 100 % d: 0.07
; DROP (ghost / attenuation)
FX_GLITCH_DROP_KEEP_LEVEL_MIN = 0.00; Dropout minimum level (0 = mute, 1 = no drop)           d: 0.0
FX_GLITCH_DROP_KEEP_LEVEL_MAX = 0.75; Dropout maximum level (0 = mute, 1 = no drop)           d: 0.75
FX_GLITCH_DROP_KEEP_TIME_MIN = 4.0; Dropout duration minimum (ms)                           d: 4.0
FX_GLITCH_DROP_KEEP_TIME_MAX = 40.0; Dropout duration maximum (ms)                           d: 40.0
; CRUSH (sample - rate reduction)
FX_GLITCH_CRUSH_TIME_MIN = 10.0; Bit crush duration minimum (ms)                         d: 10.0
FX_GLITCH_CRUSH_TIME_MAX = 50.0; Bit crush duration maximum (ms)                         d: 50.0
; MICRO LOOP
FX_GLITCH_MICROLOOP_SMPL_T_MIN = 0.2; Hold micro loop time minimum (ms)                       d: 0.2
FX_GLITCH_MICROLOOP_SMPL_T_MAX = 3.0; Hold micro loop time maximum (ms)                       d: 3.0
FX_GLITCH_MICROLOOP_PLAY_T_MIN = 5.0; Hold micro loop play time minimum (ms)                  d: 5.0
FX_GLITCH_MICROLOOP_PLAY_T_MAX = 15.0; Hold micro loop play time maximum (ms)                  d: 15.0
; REPEAT (onset stutter)
FX_GLITCH_STUTTER_SMPL_T_MIN = 3.0; Stutter sample time minimum (ms)                        d: 3.0
FX_GLITCH_STUTTER_SMPL_T_MAX = 10.0; Stutter sample time maximum (ms)                        d: 10.0
FX_GLITCH_STUTTER_NUM_MIN = 2; Stutter repeat quantity minimum (integer)               d: 2
FX_GLITCH_STUTTER_NUM_MAX = 5; Stutter repeat quantity maximum (integer)               d: 5
FX_GLITCH_STUTTER_WINDOW = 20; Stutter can happen within x ms of sample trigger        d : 20
*/