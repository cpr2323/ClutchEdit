#pragma once

#include <JuceHeader.h>
#include "HiHatIniKeys.h"
#include "../Utility/ValueTreeWrapper.h"

class SettingsProperties : public ValueTreeWrapper<SettingsProperties>
{
public:
    SettingsProperties () noexcept : ValueTreeWrapper<SettingsProperties> (SettingsTypeId)
    {
    }
    SettingsProperties (juce::ValueTree vt, WrapperType wrapperType, EnableCallbacks shouldEnableCallbacks) noexcept
        : ValueTreeWrapper<SettingsProperties> (SettingsTypeId, vt, wrapperType, shouldEnableCallbacks)
    {
    }

    void setAccClAmpMod (float value, bool includeSelfCallback);
    void setAccClRelMod (float value, bool includeSelfCallback);
    void setAccOpAmpMod (float value, bool includeSelfCallback);
    void setAccOpRelMod (float value, bool includeSelfCallback);
    void setChokeRelease (float value, bool includeSelfCallback);
    void setClsdMaxRelease (float value, bool includeSelfCallback);
    //void setClsdReleaseMode (int value, bool includeSelfCallback);
    void setClsdRelOfstScale (float value, bool includeSelfCallback);
    void setCvDisableFx (int value, bool includeSelfCallback);
    void setCvDisableVelocity (int value, bool includeSelfCallback);
    void setEnvelopeMaxRelease (float value, bool includeSelfCallback);
    void setFeelAmpMod (float value, bool includeSelfCallback);
    void setFeelAttackMod (float value, bool includeSelfCallback);
    void setFeelReleaseMod (float value, bool includeSelfCallback);
    void setFltrHpfMaxFreq (int value, bool includeSelfCallback);
    void setFltrHpfMinFreq (int value, bool includeSelfCallback);
    void setFltrHpfQ (float value, bool includeSelfCallback);
    void setFltrLpfMaxFreq (int value, bool includeSelfCallback);
    void setFltrLpfMinFreq (int value, bool includeSelfCallback);
    void setFltrLpfQ (float value, bool includeSelfCallback);
    void setFxChorusCenter (float value, bool includeSelfCallback);
    void setFxChorusDepth (float value, bool includeSelfCallback);
    void setFxChorusLfoB (float value, bool includeSelfCallback);
    void setFxChorusLfoT (float value, bool includeSelfCallback);
    void setFxChorusMix (float value, bool includeSelfCallback);
    void setFxChorusSpread (float value, bool includeSelfCallback);
    void setFxChorusStagger (float value, bool includeSelfCallback);
    void setFxChorusTaps (int value, bool includeSelfCallback);
    void setFxChorusType (int value, bool includeSelfCallback);
    void setFxCvUnipolar (int value, bool includeSelfCallback);
    void setFxDjfilterHpfMax (int value, bool includeSelfCallback);
    void setFxDjfilterHpfMin (int value, bool includeSelfCallback);
    void setFxDjfilterLpfMax (int value, bool includeSelfCallback);
    void setFxDjfilterLpfMin (int value, bool includeSelfCallback);
    void setFxDjfilterQGainReduction (float value, bool includeSelfCallback);
    void setFxDjfilterQMax (float value, bool includeSelfCallback);
    void setFxDjfilterQMin (float value, bool includeSelfCallback);
    void setFxDubEchoHpf (int value, bool includeSelfCallback);
    void setFxDubEchoLpf (int value, bool includeSelfCallback);
    void setFxDubEchoMix (float value, bool includeSelfCallback);
    void setFxDubEchoTmin (int value, bool includeSelfCallback);
    void setFxGlitchCrushTimeMax (float value, bool includeSelfCallback);
    void setFxGlitchCrushTimeMin (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepLevelMax (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepLevelMin (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepTimeMax (float value, bool includeSelfCallback);
    void setFxGlitchDropKeepTimeMin (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopPlayTMax (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopPlayTMin (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopSmplTMax (float value, bool includeSelfCallback);
    void setFxGlitchMicroloopSmplTMin (float value, bool includeSelfCallback);
    void setFxGlitchProbabilityMax (float value, bool includeSelfCallback);
    void setFxGlitchProbabilityMin (float value, bool includeSelfCallback);
    void setFxGlitchStutterNumMax (int value, bool includeSelfCallback);
    void setFxGlitchStutterNumMin (int value, bool includeSelfCallback);
    void setFxGlitchStutterSmplTMax (float value, bool includeSelfCallback);
    void setFxGlitchStutterSmplTMin (float value, bool includeSelfCallback);
    void setFxGlitchStutterWindow (int value, bool includeSelfCallback);
    void setFxGlitchWeightCrushHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightCrushLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightDropHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightDropLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightHoldHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightHoldLow (float value, bool includeSelfCallback);
    void setFxGlitchWeightStutterHigh (float value, bool includeSelfCallback);
    void setFxGlitchWeightStutterLow (float value, bool includeSelfCallback);
    void setFxReverbDiffusion (float value, bool includeSelfCallback);
    void setFxReverbHpf (int value, bool includeSelfCallback);
    void setFxReverbLpf (int value, bool includeSelfCallback);
    void setFxReverbMix (float value, bool includeSelfCallback);
    void setFxReverbModDepth (float value, bool includeSelfCallback);
    void setFxReverbModRate (float value, bool includeSelfCallback);
    void setFxReverbPredelay (int value, bool includeSelfCallback);
    void setFxReverbSizeMax (float value, bool includeSelfCallback);
    void setFxReverbSizeMin (float value, bool includeSelfCallback);
    void setFxReverbType (int value, bool includeSelfCallback);
    void setGateMode (int value, bool includeSelfCallback);
    void setKnobPosTakeup (int value, bool includeSelfCallback);
    void setPitchHigh (float value, bool includeSelfCallback);
    void setPitchLow (float value, bool includeSelfCallback);
    void setReleaseMode (int value, bool includeSelfCallback);
    void setVelocityUnipolar (int value, bool includeSelfCallback);

    float getAccClAmpMod ();
    float getAccClRelMod ();
    float getAccOpAmpMod ();
    float getAccOpRelMod ();
    float getChokeRelease ();
    float getClsdMaxRelease ();
    //int getClsdReleaseMode ();
    float getClsdRelOfstScale ();
    int getCvDisableFx ();
    int getCvDisableVelocity ();
    float getEnvelopeMaxRelease ();
    float getFeelAmpMod ();
    float getFeelAttackMod ();
    float getFeelReleaseMod ();
    int getFltrHpfMaxFreq ();
    int getFltrHpfMinFreq ();
    float getFltrHpfQ ();
    int getFltrLpfMaxFreq ();
    int getFltrLpfMinFreq ();
    float getFltrLpfQ ();
    float getFxChorusCenter ();
    float getFxChorusDepth ();
    float getFxChorusLfoB ();
    float getFxChorusLfoT ();
    float getFxChorusMix ();
    float getFxChorusSpread ();
    float getFxChorusStagger ();
    int getFxChorusTaps ();
    int getFxChorusType ();
    int getFxCvUnipolar ();
    int getFxDjfilterHpfMax ();
    int getFxDjfilterHpfMin ();
    int getFxDjfilterLpfMax ();
    int getFxDjfilterLpfMin ();
    float getFxDjfilterQGainReduction ();
    float getFxDjfilterQMax ();
    float getFxDjfilterQMin ();
    int getFxDubEchoHpf ();
    int getFxDubEchoLpf ();
    float getFxDubEchoMix ();
    int getFxDubEchoTmin ();
    float getFxGlitchCrushTimeMax ();
    float getFxGlitchCrushTimeMin ();
    float getFxGlitchDropKeepLevelMax ();
    float getFxGlitchDropKeepLevelMin ();
    float getFxGlitchDropKeepTimeMax ();
    float getFxGlitchDropKeepTimeMin ();
    float getFxGlitchMicroloopPlayTMax ();
    float getFxGlitchMicroloopPlayTMin ();
    float getFxGlitchMicroloopSmplTMax ();
    float getFxGlitchMicroloopSmplTMin ();
    float getFxGlitchProbabilityMax ();
    float getFxGlitchProbabilityMin ();
    int getFxGlitchStutterNumMax ();
    int getFxGlitchStutterNumMin ();
    float getFxGlitchStutterSmplTMax ();
    float getFxGlitchStutterSmplTMin ();
    int getFxGlitchStutterWindow ();
    float getFxGlitchWeightCrushHigh ();
    float getFxGlitchWeightCrushLow ();
    float getFxGlitchWeightDropHigh ();
    float getFxGlitchWeightDropLow ();
    float getFxGlitchWeightHoldHigh ();
    float getFxGlitchWeightHoldLow ();
    float getFxGlitchWeightStutterHigh ();
    float getFxGlitchWeightStutterLow ();
    float getFxReverbDiffusion ();
    int getFxReverbHpf ();
    int getFxReverbLpf ();
    float getFxReverbMix ();
    float getFxReverbModDepth ();
    float getFxReverbModRate ();
    int getFxReverbPredelay ();
    float getFxReverbSizeMax ();
    float getFxReverbSizeMin ();
    int getFxReverbType ();
    int getGateMode ();
    int getKnobPosTakeup ();
    float getPitchHigh ();
    float getPitchLow ();
    int getReleaseMode ();
    int getVelocityUnipolar ();

    juce::String getAccClAmpModKey ();
    juce::String getAccClRelModKey ();
    juce::String getAccOpAmpModKey ();
    juce::String getAccOpRelModKey ();
    juce::String getChokeReleaseKey ();
    juce::String getClsdMaxReleaseKey ();
    //juce::String getClsdReleaseModeKey ();
    juce::String getClsdRelOfstScaleKey ();
    juce::String getCvDisableFxKey ();
    juce::String getCvDisableVelocityKey ();
    juce::String getEnvelopeMaxReleaseKey ();
    juce::String getFeelAmpModKey ();
    juce::String getFeelAttackModKey ();
    juce::String getFeelReleaseModKey ();
    juce::String getFltrHpfMaxFreqKey ();
    juce::String getFltrHpfMinFreqKey ();
    juce::String getFltrHpfQKey ();
    juce::String getFltrLpfMaxFreqKey ();
    juce::String getFltrLpfMinFreqKey ();
    juce::String getFltrLpfQKey ();
    juce::String getFxChorusCenterKey ();
    juce::String getFxChorusDepthKey ();
    juce::String getFxChorusLfoBKey ();
    juce::String getFxChorusLfoTKey ();
    juce::String getFxChorusMixKey ();
    juce::String getFxChorusSpreadKey ();
    juce::String getFxChorusStaggerKey ();
    juce::String getFxChorusTapsKey ();
    juce::String getFxChorusTypeKey ();
    juce::String getFxCvUnipolarKey ();
    juce::String getFxDjfilterHpfMaxKey ();
    juce::String getFxDjfilterHpfMinKey ();
    juce::String getFxDjfilterLpfMaxKey ();
    juce::String getFxDjfilterLpfMinKey ();
    juce::String getFxDjfilterQGainReductionKey ();
    juce::String getFxDjfilterQMaxKey ();
    juce::String getFxDjfilterQMinKey ();
    juce::String getFxDubEchoHpfKey ();
    juce::String getFxDubEchoLpfKey ();
    juce::String getFxDubEchoMixKey ();
    juce::String getFxDubEchoTminKey ();
    juce::String getFxGlitchCrushTimeMaxKey ();
    juce::String getFxGlitchCrushTimeMinKey ();
    juce::String getFxGlitchDropKeepLevelMaxKey ();
    juce::String getFxGlitchDropKeepLevelMinKey ();
    juce::String getFxGlitchDropKeepTimeMaxKey ();
    juce::String getFxGlitchDropKeepTimeMinKey ();
    juce::String getFxGlitchMicroloopPlayTMaxKey ();
    juce::String getFxGlitchMicroloopPlayTMinKey ();
    juce::String getFxGlitchMicroloopSmplTMaxKey ();
    juce::String getFxGlitchMicroloopSmplTMinKey ();
    juce::String getFxGlitchProbabilityMaxKey ();
    juce::String getFxGlitchProbabilityMinKey ();
    juce::String getFxGlitchStutterNumMaxKey ();
    juce::String getFxGlitchStutterNumMinKey ();
    juce::String getFxGlitchStutterSmplTMaxKey ();
    juce::String getFxGlitchStutterSmplTMinKey ();
    juce::String getFxGlitchStutterWindowKey ();
    juce::String getFxGlitchWeightCrushHighKey ();
    juce::String getFxGlitchWeightCrushLowKey ();
    juce::String getFxGlitchWeightDropHighKey ();
    juce::String getFxGlitchWeightDropLowKey ();
    juce::String getFxGlitchWeightHoldHighKey ();
    juce::String getFxGlitchWeightHoldLowKey ();
    juce::String getFxGlitchWeightStutterHighKey ();
    juce::String getFxGlitchWeightStutterLowKey ();
    juce::String getFxReverbDiffusionKey ();
    juce::String getFxReverbHpfKey ();
    juce::String getFxReverbLpfKey ();
    juce::String getFxReverbMixKey ();
    juce::String getFxReverbModDepthKey ();
    juce::String getFxReverbModRateKey ();
    juce::String getFxReverbPredelayKey ();
    juce::String getFxReverbSizeMaxKey ();
    juce::String getFxReverbSizeMinKey ();
    juce::String getFxReverbTypeKey ();
    juce::String getGateModeKey ();
    juce::String getKnobPosTakeupKey ();
    juce::String getPitchHighKey ();
    juce::String getPitchLowKey ();
    juce::String getReleaseModeKey ();
    juce::String getVelocityUnipolarKey ();

    std::function<void (float value)> onAccClAmpModChange;
    std::function<void (float value)> onAccClRelModChange;
    std::function<void (float value)> onAccOpAmpModChange;
    std::function<void (float value)> onAccOpRelModChange;
    std::function<void (float value)> onChokeReleaseChange;
    std::function<void (float value)> onClsdMaxReleaseChange;
    std::function<void (float value)> onClsdRelOfstScaleChange;
    std::function<void (int value)> onCvDisableFxChange;
    std::function<void (int value)> onCvDisableVelocityChange;
    std::function<void (float value)> onEnvelopeMaxReleaseChange;
    std::function<void (float value)> onFeelAmpModChange;
    std::function<void (float value)> onFeelAttackModChange;
    std::function<void (float value)> onFeelReleaseModChange;
    std::function<void (int value)> onFltrHpfMaxFreqChange;
    std::function<void (int value)> onFltrHpfMinFreqChange;
    std::function<void (float value)> onFltrHpfQChange;
    std::function<void (int value)> onFltrLpfMaxFreqChange;
    std::function<void (int value)> onFltrLpfMinFreqChange;
    std::function<void (float value)> onFltrLpfQChange;
    std::function<void (float value)> onFxChorusCenterChange;
    std::function<void (float value)> onFxChorusDepthChange;
    std::function<void (float value)> onFxChorusLfoBChange;
    std::function<void (float value)> onFxChorusLfoTChange;
    std::function<void (float value)> onFxChorusMixChange;
    std::function<void (float value)> onFxChorusSpreadChange;
    std::function<void (float value)> onFxChorusStaggerChange;
    std::function<void (int value)> onFxChorusTapsChange;
    std::function<void (int value)> onFxChorusTypeChange;
    std::function<void (int value)> onFxCvUnipolarChange;
    std::function<void (int value)> onFxDjfilterHpfMaxChange;
    std::function<void (int value)> onFxDjfilterHpfMinChange;
    std::function<void (int value)> onFxDjfilterLpfMaxChange;
    std::function<void (int value)> onFxDjfilterLpfMinChange;
    std::function<void (float value)> onFxDjfilterQGainReductionChange;
    std::function<void (float value)> onFxDjfilterQMaxChange;
    std::function<void (float value)> onFxDjfilterQMinChange;
    std::function<void (int value)> onFxDubEchoHpfChange;
    std::function<void (int value)> onFxDubEchoLpfChange;
    std::function<void (float value)> onFxDubEchoMixChange;
    std::function<void (int value)> onFxDubEchoTminChange;
    std::function<void (float value)> onFxGlitchCrushTimeMaxChange;
    std::function<void (float value)> onFxGlitchCrushTimeMinChange;
    std::function<void (float value)> onFxGlitchDropKeepLevelMaxChange;
    std::function<void (float value)> onFxGlitchDropKeepLevelMinChange;
    std::function<void (float value)> onFxGlitchDropKeepTimeMaxChange;
    std::function<void (float value)> onFxGlitchDropKeepTimeMinChange;
    std::function<void (float value)> onFxGlitchMicroloopPlayTMaxChange;
    std::function<void (float value)> onFxGlitchMicroloopPlayTMinChange;
    std::function<void (float value)> onFxGlitchMicroloopSmplTMaxChange;
    std::function<void (float value)> onFxGlitchMicroloopSmplTMinChange;
    std::function<void (float value)> onFxGlitchProbabilityMaxChange;
    std::function<void (float value)> onFxGlitchProbabilityMinChange;
    std::function<void (int value)> onFxGlitchStutterNumMaxChange;
    std::function<void (int value)> onFxGlitchStutterNumMinChange;
    std::function<void (float value)> onFxGlitchStutterSmplTMaxChange;
    std::function<void (float value)> onFxGlitchStutterSmplTMinChange;
    std::function<void (int value)> onFxGlitchStutterWindowChange;
    std::function<void (float value)> onFxGlitchWeightCrushHighChange;
    std::function<void (float value)> onFxGlitchWeightCrushLowChange;
    std::function<void (float value)> onFxGlitchWeightDropHighChange;
    std::function<void (float value)> onFxGlitchWeightDropLowChange;
    std::function<void (float value)> onFxGlitchWeightHoldHighChange;
    std::function<void (float value)> onFxGlitchWeightHoldLowChange;
    std::function<void (float value)> onFxGlitchWeightStutterHighChange;
    std::function<void (float value)> onFxGlitchWeightStutterLowChange;
    std::function<void (float value)> onFxReverbDiffusionChange;
    std::function<void (int value)> onFxReverbHpfChange;
    std::function<void (int value)> onFxReverbLpfChange;
    std::function<void (float value)> onFxReverbMixChange;
    std::function<void (float value)> onFxReverbModDepthChange;
    std::function<void (float value)> onFxReverbModRateChange;
    std::function<void (int value)> onFxReverbPredelayChange;
    std::function<void (float value)> onFxReverbSizeMaxChange;
    std::function<void (float value)> onFxReverbSizeMinChange;
    std::function<void (int value)> onFxReverbTypeChange;
    std::function<void (int value)> onGateModeChange;
    std::function<void (int value)> onKnobPosTakeupChange;
    std::function<void (float value)> onPitchHighChange;
    std::function<void (float value)> onPitchLowChange;
    std::function<void (int value)> onReleaseModeChange;
    std::function<void (int value)> onVelocityUnipolarChange;

    static inline const juce::Identifier SettingsTypeId { "HiHat" };
    static inline const juce::Identifier AccClAmpModPropertyId { "accClAmpMod" };
    static inline const juce::Identifier AccClRelModPropertyId { "accClRelMod" };
    static inline const juce::Identifier AccOpAmpModPropertyId { "accOpAmpMod" };
    static inline const juce::Identifier AccOpRelModPropertyId { "accOpRelMod" };
    static inline const juce::Identifier ChokeReleasePropertyId { "chokeRelease" };
    static inline const juce::Identifier ClsdMaxReleasePropertyId { "clsdMaxRelease" };
    static inline const juce::Identifier ClsdRelOfstScalePropertyId { "clsdRelOfstScale" };
    static inline const juce::Identifier CvDisableFxPropertyId { "cvDisableFx" };
    static inline const juce::Identifier CvDisableVelocityPropertyId { "cvDisableVelocity" };
    static inline const juce::Identifier EnvelopeMaxReleasePropertyId { "envelopeMaxRelease" };
    static inline const juce::Identifier FeelAmpModPropertyId { "feelAmpMod" };
    static inline const juce::Identifier FeelAttackModPropertyId { "feelAttackMod" };
    static inline const juce::Identifier FeelReleaseModPropertyId { "feelReleaseMod" };
    static inline const juce::Identifier FltrHpfMaxFreqPropertyId { "fltrHpfMaxFreq" };
    static inline const juce::Identifier FltrHpfMinFreqPropertyId { "fltrHpfMinFreq" };
    static inline const juce::Identifier FltrHpfQPropertyId { "fltrHpfQ" };
    static inline const juce::Identifier FltrLpfMaxFreqPropertyId { "fltrLpfMaxFreq" };
    static inline const juce::Identifier FltrLpfMinFreqPropertyId { "fltrLpfMinFreq" };
    static inline const juce::Identifier FltrLpfQPropertyId { "fltrLpfQ" };
    static inline const juce::Identifier FxChorusCenterPropertyId { "fxChorusCenter" };
    static inline const juce::Identifier FxChorusDepthPropertyId { "fxChorusDepth" };
    static inline const juce::Identifier FxChorusLfoBPropertyId { "fxChorusLfoB" };
    static inline const juce::Identifier FxChorusLfoTPropertyId { "fxChorusLfoT" };
    static inline const juce::Identifier FxChorusMixPropertyId { "fxChorusMix" };
    static inline const juce::Identifier FxChorusSpreadPropertyId { "fxChorusSpread" };
    static inline const juce::Identifier FxChorusStaggerPropertyId { "fxChorusStagger" };
    static inline const juce::Identifier FxChorusTapsPropertyId { "fxChorusTaps" };
    static inline const juce::Identifier FxChorusTypePropertyId { "fxChorusType" };
    static inline const juce::Identifier FxCvUnipolarPropertyId { "fxCvUnipolar" };
    static inline const juce::Identifier FxDjfilterHpfMaxPropertyId { "fxDjfilterHpfMax" };
    static inline const juce::Identifier FxDjfilterHpfMinPropertyId { "fxDjfilterHpfMin" };
    static inline const juce::Identifier FxDjfilterLpfMaxPropertyId { "fxDjfilterLpfMax" };
    static inline const juce::Identifier FxDjfilterLpfMinPropertyId { "fxDjfilterLpfMin" };
    static inline const juce::Identifier FxDjfilterQGainReductionPropertyId { "fxDjfilterQGainReduction" };
    static inline const juce::Identifier FxDjfilterQMaxPropertyId { "fxDjfilterQMax" };
    static inline const juce::Identifier FxDjfilterQMinPropertyId { "fxDjfilterQMin" };
    static inline const juce::Identifier FxDubEchoHpfPropertyId { "fxDubEchoHpf" };
    static inline const juce::Identifier FxDubEchoLpfPropertyId { "fxDubEchoLpf" };
    static inline const juce::Identifier FxDubEchoMixPropertyId { "fxDubEchoMix" };
    static inline const juce::Identifier FxDubEchoTminPropertyId { "fxDubEchoTmin" };
    static inline const juce::Identifier FxGlitchCrushTimeMaxPropertyId { "fxGlitchCrushTimeMax" };
    static inline const juce::Identifier FxGlitchCrushTimeMinPropertyId { "fxGlitchCrushTimeMin" };
    static inline const juce::Identifier FxGlitchDropKeepLevelMaxPropertyId { "fxGlitchDropKeepLevelMax" };
    static inline const juce::Identifier FxGlitchDropKeepLevelMinPropertyId { "fxGlitchDropKeepLevelMin" };
    static inline const juce::Identifier FxGlitchDropKeepTimeMaxPropertyId { "fxGlitchDropKeepTimeMax" };
    static inline const juce::Identifier FxGlitchDropKeepTimeMinPropertyId { "fxGlitchDropKeepTimeMin" };
    static inline const juce::Identifier FxGlitchMicroloopPlayTMaxPropertyId { "fxGlitchMicroloopPlayTMax" };
    static inline const juce::Identifier FxGlitchMicroloopPlayTMinPropertyId { "fxGlitchMicroloopPlayTMin" };
    static inline const juce::Identifier FxGlitchMicroloopSmplTMaxPropertyId { "fxGlitchMicroloopSmplTMax" };
    static inline const juce::Identifier FxGlitchMicroloopSmplTMinPropertyId { "fxGlitchMicroloopSmplTMin" };
    static inline const juce::Identifier FxGlitchProbabilityMaxPropertyId { "fxGlitchProbabilityMax" };
    static inline const juce::Identifier FxGlitchProbabilityMinPropertyId { "fxGlitchProbabilityMin" };
    static inline const juce::Identifier FxGlitchStutterNumMaxPropertyId { "fxGlitchStutterNumMax" };
    static inline const juce::Identifier FxGlitchStutterNumMinPropertyId { "fxGlitchStutterNumMin" };
    static inline const juce::Identifier FxGlitchStutterSmplTMaxPropertyId { "fxGlitchStutterSmplTMax" };
    static inline const juce::Identifier FxGlitchStutterSmplTMinPropertyId { "fxGlitchStutterSmplTMin" };
    static inline const juce::Identifier FxGlitchStutterWindowPropertyId { "fxGlitchStutterWindow" };
    static inline const juce::Identifier FxGlitchWeightCrushHighPropertyId { "fxGlitchWeightCrushHigh" };
    static inline const juce::Identifier FxGlitchWeightCrushLowPropertyId { "fxGlitchWeightCrushLow" };
    static inline const juce::Identifier FxGlitchWeightDropHighPropertyId { "fxGlitchWeightDropHigh" };
    static inline const juce::Identifier FxGlitchWeightDropLowPropertyId { "fxGlitchWeightDropLow" };
    static inline const juce::Identifier FxGlitchWeightHoldHighPropertyId { "fxGlitchWeightHoldHigh" };
    static inline const juce::Identifier FxGlitchWeightHoldLowPropertyId { "fxGlitchWeightHoldLow" };
    static inline const juce::Identifier FxGlitchWeightStutterHighPropertyId { "fxGlitchWeightStutterHigh" };
    static inline const juce::Identifier FxGlitchWeightStutterLowPropertyId { "fxGlitchWeightStutterLow" };
    static inline const juce::Identifier FxReverbDiffusionPropertyId { "fxReverbDiffusion" };
    static inline const juce::Identifier FxReverbHpfPropertyId { "fxReverbHpf" };
    static inline const juce::Identifier FxReverbLpfPropertyId { "fxReverbLpf" };
    static inline const juce::Identifier FxReverbMixPropertyId { "fxReverbMix" };
    static inline const juce::Identifier FxReverbModDepthPropertyId { "fxReverbModDepth" };
    static inline const juce::Identifier FxReverbModRatePropertyId { "fxReverbModRate" };
    static inline const juce::Identifier FxReverbPredelayPropertyId { "fxReverbPredelay" };
    static inline const juce::Identifier FxReverbSizeMaxPropertyId { "fxReverbSizeMax" };
    static inline const juce::Identifier FxReverbSizeMinPropertyId { "fxReverbSizeMin" };
    static inline const juce::Identifier FxReverbTypePropertyId { "fxReverbType" };
    static inline const juce::Identifier GateModePropertyId { "gateMode" };
    static inline const juce::Identifier KnobPosTakeupPropertyId { "knobPosTakeup" };
    static inline const juce::Identifier PitchHighPropertyId { "pitchHigh" };
    static inline const juce::Identifier PitchLowPropertyId { "pitchLow" };
    static inline const juce::Identifier ReleaseModePropertyId { "releaseMode" };
    static inline const juce::Identifier VelocityUnipolarPropertyId { "velocityUnipolar" };

    void initValueTree ();
    void processValueTree () {}

private:

    void valueTreePropertyChanged (juce::ValueTree& vt, const juce::Identifier& property) override;
};

/*
* This is the format from v1.1 firmware
; =======================================================================================================================
; HIHAT.INI
; WMD CLUTCH — User adjustable parameters and FEEL Patterns
;
; This file uses standard INI format with [section] headers and key=value pairs.
; Comments start with semicolon (;). Defaults are marked with "d:".
; Ranges are in parenthesis ( )
; =======================================================================================================================

[HIHAT]
; Pitch control multiplier (both Surface A and Surface B)
PITCH_LOW                         = 0.125            ; Min pitch (0.001 to 0.5)                                d: 0.125
PITCH_HIGH                        = 2.5              ; Max pitch (1.5 to 3.7)                                  d: 2.5

; Envelope Release Parameters in seconds
ENVELOPE_MAX_RELEASE              = 4.000            ; Max release seconds at CW (0.6 to 20)                   d: 4.0
CHOKE_RELEASE                     = 0.080            ; Choke release time seconds (0.002 to 0.400)             d: 0.080

; Release behavior for CLOSED and OPEN hits (formerly CLSD_RELEASE_MODE) the old key name is still accepted)
RELEASE_MODE                      = 1                ; 0: RELEASE OFFSET sets a fixed CLOSED release time,     d: 1
                                                     ;    RELEASE control/CV sets the OPEN release
                                                     ; 1: Release Offset mode
                                                     ; 2: RELEASE OFFSET sets a fixed OPEN release time,
                                                     ;    RELEASE control/CV sets the CLOSED release

; Scale of envelope for closed hits (multiply ENV_MAX_RELEASE for Closed Hits)
; Only applies if RELEASE_MODE = 1
CLSD_REL_OFST_SCALE               = 0.5              ; Range (0.1 to 0.9)                                      d: 0.5

; CLOSED Hit Max Release, applies if RELEASE_MODE = 0 or 2
CLSD_MAX_RELEASE                  = 0.8              ; Max release time (0.3 to 2.0)                           d: 0.8

; Envelope Release Multipliers for Accented hits, > 1 extends release, < 1 shortens release (FEEL OFF)
ACC_CL_REL_MOD                    = 1.18             ; Release Mod CLOSED ACC hit (0.5 to 3.0)                 d: 1.18
ACC_OP_REL_MOD                    = 1.25             ; Release Mod OPEN ACC hit   (0.5 to 3.0)                 d: 1.25
; Amplitude Multipliers for Accented hits, > 1 increases amplitude, < 1 reduces amplitude (FEEL OFF)
ACC_CL_AMP_MOD                    = 1.3              ; Amp Mod CLOSED ACC hit     (0.5 to 3.0)                 d: 1.3
ACC_OP_AMP_MOD                    = 1.25             ; Amp Mod OPEN ACC hit       (0.5 to 3.0)                 d: 1.25

; CV Bipolar or Unipolar options
FX_CV_UNIPOLAR                    = 1                ; 0: -5 to 5V, 1: 0 to 5V                                 d: 1
VELOCITY_UNIPOLAR                 = 0                ; 0: 0V=100%  -5=0%  +5=200%                              d: 0
                                                     ; 1: 0V=10%         +5=100%

; CV OFF/ON Switch Options
CV_DISABLE_VELOCITY               = 0                ; 0: Velocity always enabled                              d: 0
                                                     ; 1: CV Off SW affects velocity
CV_DISABLE_FX                     = 0                ; 0: FX CV Always On                                      d: 0
                                                     ; 1: CV Disable : Freeze FX CV

; Gate behavior
GATE_MODE                         = 0                ; 0: Release immediately (TRIGGER MODE)                   d: 0
                                                     ; 1: Release after gate falls

; Feel behavior - modulation multipliers for feel params
FEEL_ATTACK_MOD                   = 1.0              ; 0.000 (none) to 5.000 (5x)                              d: 1.0
FEEL_RELEASE_MOD                  = 1.0              ; 0.000 (none) to 5.000 (5x)                              d: 1.0
FEEL_AMP_MOD                      = 1.0              ; 0.000 (none) to 2.000 (2x)                              d: 1.0

; Multipurpose Knobs - Wiggle or Positional Takeup
KNOB_POS_TAKEUP                   = 1                ; 0 to sense small movement (wiggle)                      d: 0
                                                     ; 1 to require passing old value

; Filter Frequency Ranges
FLTR_HPF_MIN_FREQ                 = 100              ; HPF minimum frequency (Hz)  (20 to 1000)                d: 100
FLTR_HPF_MAX_FREQ                 = 14000            ; HPF maximum frequency (Hz)  (8000 - 20000)              d: 14000
FLTR_LPF_MIN_FREQ                 = 200              ; LPF minimum frequency (Hz)  (20 to 1000)                d: 200
FLTR_LPF_MAX_FREQ                 = 20000            ; LPF maximum frequency (Hz)  (12000 - 20000)             d: 20000
FLTR_HPF_Q                        = 1.0              ; HPF resonance (Q factor) (0.25 - 4.0)                   d: 1.0
FLTR_LPF_Q                        = 0.707            ; LPF resonance (Q factor) (0.25 - 4.0)                   d: 0.707

; DJ Filter Frequency Ranges
FX_DJFILTER_HPF_MIN               = 100              ; DJ HPF minimum frequency (Hz) (20 to 2000)              d: 100
FX_DJFILTER_HPF_MAX               = 14000            ; DJ HPF maximum frequency (Hz) (8000 to 20000)           d: 14000
FX_DJFILTER_LPF_MIN               = 200              ; DJ LPF minimum frequency (Hz) (20 to 2000)              d: 200
FX_DJFILTER_LPF_MAX               = 20000            ; DJ LPF maximum frequency (Hz) (12000 to 20000)          d: 20000
FX_DJFILTER_Q_MIN                 = 0.5              ; DJ Filter minimum Q (resonance) (0.25 to 12.0)          d: 0.5
FX_DJFILTER_Q_MAX                 = 4.0              ; DJ Filter maximum Q (resonance) (0.25 to 12.0)          d: 4.0
FX_DJFILTER_Q_GAIN_REDUCTION      = 0.12             ; Gain reduction factor for high Q (0.0 to 0.5)           d: 0.12

; FX Parameters — voicing for specific effects
FX_DUB_ECHO_TMIN                  = 30               ; Minimum Time at PARAM CCW in ms (5 to 80)               d: 30
FX_DUB_ECHO_HPF                   = 400              ; HPF Cutoff Frequency (Hz) (20 to 2000)                  d: 400
FX_DUB_ECHO_LPF                   = 8400             ; LPF Cutoff Frequency (Hz) (2000 to 20000)               d: 8400
FX_DUB_ECHO_MIX                   = 0.38             ; MIX level for DUB ECHO    (0.01 to 0.80)                d: 0.38

FX_CHORUS_CENTER                  = 12.0             ; Center Delay in ms (1 to 120)                           d: 12.0
FX_CHORUS_DEPTH                   = 5.0              ; Depth in ms (1 to FX_CHORUS_CENTER / 2)                 d: 5.0
FX_CHORUS_MIX                     = 1.0              ; Mix level (0.1 to 1.0)                                  d: 1.0
FX_CHORUS_SPREAD                  = 0.01             ; LFO Freq Spread % per tap (0.001 to 0.1)                d: 0.01
FX_CHORUS_TAPS                    = 6                ; Integer # of Voices (1 to 4 Vintage, 1 to 6 Thick)      d: 6
FX_CHORUS_LFO_B                   = 0.002            ; LFO at slowest in Hz  (0.0001 to 0.1)  (Thick only)     d: 0.002
FX_CHORUS_LFO_T                   = 3                ; LFO at fastest in Hz  (0.1 to 20)      (Thick only)     d: 3
FX_CHORUS_TYPE                    = 1                ; 0: Vintage (thin), 1: Thick (multi-voice)               d: 1
FX_CHORUS_STAGGER                 = 0.5              ; Voice center spread for Thick (0 to 1)                  d: 0.5

FX_REVERB_LPF                     = 9000             ; LPF for FB in Hz  (1000 - 20000)                        d: 9000
FX_REVERB_HPF                     = 700              ; HPF for FB in Hz  (20 - 8000)                           d: 700
FX_REVERB_TYPE                    = 1                ; 0: Vintage (echoey), 1: Plate (smooth)                  d: 1
; The following only apply to the Plate reverb (FX_REVERB_TYPE = 1)
; The PARAM knob/CV sweeps plate size and decay together, from SIZE_MIN (CCW,
; small + tight) to SIZE_MAX (CW, huge + near-freeze). Set MIN = MAX for a
; fixed size (knob then only controls decay).
FX_REVERB_SIZE_MIN                = 0.6              ; Plate size at PARAM CCW (0.10 to 1.1)                   d: 0.6
FX_REVERB_SIZE_MAX                = 0.9              ; Plate size at PARAM CW  (^ MIN to 1.1)                  d: 0.9
FX_REVERB_PREDELAY                = 21               ; Pre-delay in ms (0 to 80)                               d: 21
FX_REVERB_MOD_DEPTH               = 0.6              ; Tank modulation depth in ms (0 to 2.0)                  d: 0.6
FX_REVERB_MOD_RATE                = 1.0              ; Tank modulation rate in Hz (0.05 to 5.0)                d: 1.0
FX_REVERB_DIFFUSION               = 0.75             ; Diffusion amount (0.10 to 0.99)                         d: 0.75
FX_REVERB_MIX                     = 0.6              ; Wet level scale for the Plate (0.05 to 1.0)             d: 0.6

; ----- Glitch Engine (probabilities, weights, and per-mode timing/levels) -----
FX_GLITCH_PROBABILITY_MIN         = 0.00005          ; Master probability PARAM 0% (0.0000001 to 0.001)        d: 0.00005
FX_GLITCH_PROBABILITY_MAX         = 0.003            ; Master probability at PARAM 100% (0.000001 to 0.1)      d: 0.003

FX_GLITCH_WEIGHT_HOLD_LOW         = 0.15             ; Weighted chance of hold at PARAM 0%       (0 to 1)      d: 0.15
FX_GLITCH_WEIGHT_STUTTER_LOW      = 0.05             ; Weighted chance of stutter at PARAM 0%    (0 to 1)      d: 0.05
FX_GLITCH_WEIGHT_CRUSH_LOW        = 0.30             ; Weighted chance of bit crush at PARAM 0%  (0 to 1)      d: 0.30
FX_GLITCH_WEIGHT_DROP_LOW         = 0.02             ; Weighted chance of dropout at PARAM 0%    (0 to 1)      d: 0.02

FX_GLITCH_WEIGHT_HOLD_HIGH        = 0.30             ; Weighted chance of hold at PARAM 100%      (0 to 1)     d: 0.30
FX_GLITCH_WEIGHT_STUTTER_HIGH     = 0.20             ; Weighted chance of stutter at PARAM 100%   (0 to 1)     d: 0.20
FX_GLITCH_WEIGHT_CRUSH_HIGH       = 0.20             ; Weighted chance of bit crush at PARAM 100% (0 to 1)     d: 0.20
FX_GLITCH_WEIGHT_DROP_HIGH        = 0.07             ; Weighted chance of dropout at PARAM 100%   (0 to 1)     d: 0.07

; DROP (ghost/attenuation)
FX_GLITCH_DROP_KEEP_LEVEL_MIN     = 0.00             ; Dropout minimum level (0 = mute, 1 = no drop) (0 to 1)  d: 0.0
FX_GLITCH_DROP_KEEP_LEVEL_MAX     = 0.75             ; Dropout maximum level (0 = mute, 1 = no drop) (0 to 1)  d: 0.75
FX_GLITCH_DROP_KEEP_TIME_MIN      = 4.0              ; Dropout duration minimum (ms)       (1 to 100)          d: 4.0
FX_GLITCH_DROP_KEEP_TIME_MAX      = 40.0             ; Dropout duration maximum (ms)       (^ MIN to 1000)     d: 40.0

; CRUSH (sample-rate reduction)
FX_GLITCH_CRUSH_TIME_MIN          = 10.0             ; Bit crush duration minimum (ms)     (1 to 100)          d: 10.0
FX_GLITCH_CRUSH_TIME_MAX          = 50.0             ; Bit crush duration maximum (ms)     (^ MIN to 1000)     d: 50.0

; MICRO LOOP
FX_GLITCH_MICROLOOP_SMPL_T_MIN     = 0.2             ; Hold micro loop time minimum (ms)   (0.01 to 20)        d: 0.2
FX_GLITCH_MICROLOOP_SMPL_T_MAX     = 3.0             ; Hold micro loop time maximum (ms)   (^ MIN to 100)      d: 3.0
FX_GLITCH_MICROLOOP_PLAY_T_MIN     = 5.0             ; Hold micro loop play time minimum (ms) (0.5 to 200)     d: 5.0
FX_GLITCH_MICROLOOP_PLAY_T_MAX     = 15.0            ; Hold micro loop play time maximum (ms) (^ MIN to 1000)  d: 15.0

; REPEAT (onset stutter)
FX_GLITCH_STUTTER_SMPL_T_MIN       = 3.0             ; Stutter sample time minimum (ms)        (0.5 to 50)     d: 3.0
FX_GLITCH_STUTTER_SMPL_T_MAX       = 10.0            ; Stutter sample time maximum (ms)        (^ MIN to 100)  d: 10.0
FX_GLITCH_STUTTER_NUM_MIN          = 2               ; Stutter repeat quantity minimum (integer) (1 to 40)     d: 2
FX_GLITCH_STUTTER_NUM_MAX          = 5               ; Stutter repeat quantity maximum (integer) (1 to 40)     d: 5
FX_GLITCH_STUTTER_WINDOW           = 20              ; Stutter window after trigger (ms) (1 to 100)            d: 20


; =======================================================================================================================
[PATTERNS]
; User-customizable patterns for the FEEL option
; 8× patterns of numbers 1–9. A 0 ends the pattern.
; 1:10%, 2:30%, 3:60%, 4:80%, 5:100%, 6:110%, 7:125%, 8:150%, 9:200%
; MAX STEPS is 32 + a trailing 0 to denote pattern end.
; Example: PTN_WHITE = 6,5,7,5,0  (four-step pattern)
; =======================================================================================================================

;             1|2|3|4|5|6|7|8|1|2|3|4|5|6|7|8|1|2|3|4|5|6|7|8|1|2|3|4|5|6|7|8|END
PTN_WHITE   = 6,5,7,5,0
PTN_RED     = 6,5,5,7,5,6,5,6,4,0
PTN_ORANGE  = 3,2,8,5,2,6,2,2,0
PTN_YELLOW  = 7,3,5,7,3,5,2,5,7,3,5,3,2,8,3,2,0
PTN_GREEN   = 4,3,6,3,4,7,1,2,6,4,3,6,3,6,4,5,0
PTN_BLUE    = 5,2,3,5,1,5,1,0
PTN_CYAN    = 5,5,5,7,0
PTN_VIOLET  = 5,4,5,5,9,5,5,4,5,5,7,4,6,4,5,3,0
;             1|2|3|4|5|6|7|8|1|2|3|4|5|6|7|8|1|2|3|4|5|6|7|8|1|2|3|4|5|6|7|8|END

; =======================================================================================================================
[EFFECTS]
; Color-to-Effect Mapping
; Maps each LED color to an effect. Set to "NONE" to bypass.
; Available effects: SPUTTER, BITCRUSH, COMBFILTER, WAVEFOLD, DUBECHO, CHORUS, REVERB, GLITCH, DJFILTER, NONE
; =======================================================================================================================

FX_WHITE   = SPUTTER           ; d: SPUTTER
FX_RED     = BITCRUSH          ; d: BITCRUSH
FX_GREEN   = COMBFILTER        ; d: COMBFILTER
FX_BLUE    = DJFILTER          ; d: DJFILTER
FX_ORANGE  = DUBECHO           ; d: DUBECHO
FX_CYAN    = CHORUS            ; d: CHORUS
FX_VIOLET  = REVERB            ; d: REVERB
FX_YELLOW  = GLITCH            ; d: GLITCH

; =======================================================================================================================
; End of HIHAT.INI
; =======================================================================================================================
*/