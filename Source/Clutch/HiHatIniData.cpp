#include "HiHatIniData.h"
#include "HiHatIniKeys.h"
#include "EffectProperties.h"
#include "EffectListProperties.h"
#include "SettingsProperties.h"
#include "PatternProperties.h"
#include "PatternListProperties.h"

constexpr auto kKeyColumn { 0 };
constexpr auto kValueColumn { 34 };
constexpr auto kCommentColumn { 53 };
constexpr auto kDefaultValueColumn { 111 };

void HiHatIniData::FillInDataFromProperties (const juce::ValueTree clutchVT)
{
    SettingsProperties settingsProperties (clutchVT, ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::no);
    PatternListProperties patternListProperties (clutchVT, ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::no);
    EffectListProperties effectListProperties (clutchVT, ValueTreeWrapper<EffectListProperties>::WrapperType::client, ValueTreeWrapper<EffectListProperties>::EnableCallbacks::no);

    const auto setFloatValue = [this] (const juce::String& section, const juce::String& key, float value)
    {
        setValue (section, key, juce::String (value, 5).trimCharactersAtEnd ("0").trimCharactersAtEnd ("."));
    };
    const auto setIntValue = [this] (const juce::String& section, const juce::String& key, int value)
    {
        setValue (section, key, juce::String (value));
    };

    // Core
    setFloatValue (kHiHatSection, kPitchLowKey, settingsProperties.getPitchLow ());
    setFloatValue (kHiHatSection, kPitchHighKey, settingsProperties.getPitchHigh ());
    setFloatValue (kHiHatSection, kEnvelopeMaxReleaseKey, settingsProperties.getEnvelopeMaxRelease ());
    setFloatValue (kHiHatSection, kChokeReleaseKey, settingsProperties.getChokeRelease ());
    //setIntValue (kHiHatSection, kClsdReleaseModeKey, settingsProperties.getClsdReleaseMode ());
    setIntValue (kHiHatSection, kReleaseModeKey, settingsProperties.getReleaseMode ());
    setFloatValue (kHiHatSection, kClsdRelOfstScaleKey, settingsProperties.getClsdRelOfstScale ());
    setFloatValue (kHiHatSection, kClsdMaxReleaseKey, settingsProperties.getClsdMaxRelease ());
    setFloatValue (kHiHatSection, kAccClRelModKey, settingsProperties.getAccClRelMod ());
    setFloatValue (kHiHatSection, kAccOpRelModKey, settingsProperties.getAccOpRelMod ());
    setFloatValue (kHiHatSection, kAccClAmpModKey, settingsProperties.getAccClAmpMod ());
    setFloatValue (kHiHatSection, kAccOpAmpModKey, settingsProperties.getAccOpAmpMod ());

    // CV / control
    setIntValue (kHiHatSection, kFxCvUnipolarKey, settingsProperties.getFxCvUnipolar ());
    setIntValue (kHiHatSection, kVelocityUnipolarKey, settingsProperties.getVelocityUnipolar ());
    setIntValue (kHiHatSection, kCvDisableVelocityKey, settingsProperties.getCvDisableVelocity ());
    setIntValue (kHiHatSection, kCvDisableFxKey, settingsProperties.getCvDisableFx ());
    setIntValue (kHiHatSection, kGateModeKey, settingsProperties.getGateMode ());
    setFloatValue (kHiHatSection, kFeelAttackModKey, settingsProperties.getFeelAttackMod ());
    setFloatValue (kHiHatSection, kFeelReleaseModKey, settingsProperties.getFeelReleaseMod ());
    setFloatValue (kHiHatSection, kFeelAmpModKey, settingsProperties.getFeelAmpMod ());
    setIntValue (kHiHatSection, kKnobPosTakeupKey, settingsProperties.getKnobPosTakeup ());

    // Filters
    setIntValue (kHiHatSection, kFltrHpfMinFreqKey, settingsProperties.getFltrHpfMinFreq ());
    setIntValue (kHiHatSection, kFltrHpfMaxFreqKey, settingsProperties.getFltrHpfMaxFreq ());
    setIntValue (kHiHatSection, kFltrLpfMinFreqKey, settingsProperties.getFltrLpfMinFreq ());
    setIntValue (kHiHatSection, kFltrLpfMaxFreqKey, settingsProperties.getFltrLpfMaxFreq ());
    setFloatValue (kHiHatSection, kFltrHpfQKey, settingsProperties.getFltrHpfQ ());
    setFloatValue (kHiHatSection, kFltrLpfQKey, settingsProperties.getFltrLpfQ ());

    // DJ Filter
    setIntValue (kHiHatSection, kFxDjfilterHpfMinKey, settingsProperties.getFxDjfilterHpfMin ());
    setIntValue (kHiHatSection, kFxDjfilterHpfMaxKey, settingsProperties.getFxDjfilterHpfMax ());
    setIntValue (kHiHatSection, kFxDjfilterLpfMinKey, settingsProperties.getFxDjfilterLpfMin ());
    setIntValue (kHiHatSection, kFxDjfilterLpfMaxKey, settingsProperties.getFxDjfilterLpfMax ());
    setFloatValue (kHiHatSection, kFxDjfilterQMinKey, settingsProperties.getFxDjfilterQMin ());
    setFloatValue (kHiHatSection, kFxDjfilterQMaxKey, settingsProperties.getFxDjfilterQMax ());
    setFloatValue (kHiHatSection, kFxDjfilterQGainReductionKey, settingsProperties.getFxDjfilterQGainReduction ());

    // Dub Echo
    setIntValue (kHiHatSection, kFxDubEchoTminKey, settingsProperties.getFxDubEchoTmin ());
    setIntValue (kHiHatSection, kFxDubEchoHpfKey, settingsProperties.getFxDubEchoHpf ());
    setIntValue (kHiHatSection, kFxDubEchoLpfKey, settingsProperties.getFxDubEchoLpf ());
    setFloatValue (kHiHatSection, kFxDubEchoMixKey, settingsProperties.getFxDubEchoMix ());

    // Chorus
    setFloatValue (kHiHatSection, kFxChorusCenterKey, settingsProperties.getFxChorusCenter ());
    setFloatValue (kHiHatSection, kFxChorusDepthKey, settingsProperties.getFxChorusDepth ());
    setFloatValue (kHiHatSection, kFxChorusMixKey, settingsProperties.getFxChorusMix ());
    setFloatValue (kHiHatSection, kFxChorusSpreadKey, settingsProperties.getFxChorusSpread ());
    setIntValue (kHiHatSection, kFxChorusTapsKey, settingsProperties.getFxChorusTaps ());
    setFloatValue (kHiHatSection, kFxChorusLfoBKey, settingsProperties.getFxChorusLfoB ());
    setFloatValue (kHiHatSection, kFxChorusLfoTKey, settingsProperties.getFxChorusLfoT ());
    setIntValue (kHiHatSection, kFxChorusTypeKey, settingsProperties.getFxChorusType ());
    setFloatValue (kHiHatSection, kFxChorusStaggerKey, settingsProperties.getFxChorusStagger ());

    // Reverb
    setIntValue (kHiHatSection, kFxReverbLpfKey, settingsProperties.getFxReverbLpf ());
    setIntValue (kHiHatSection, kFxReverbHpfKey, settingsProperties.getFxReverbHpf ());
    setIntValue (kHiHatSection, kFxReverbTypeKey, settingsProperties.getFxReverbType ());
    setFloatValue (kHiHatSection, kFxReverbSizeMinKey, settingsProperties.getFxReverbSizeMin ());
    setFloatValue (kHiHatSection, kFxReverbSizeMaxKey, settingsProperties.getFxReverbSizeMax ());
    setIntValue (kHiHatSection, kFxReverbPredelayKey, settingsProperties.getFxReverbPredelay ());
    setFloatValue (kHiHatSection, kFxReverbModDepthKey, settingsProperties.getFxReverbModDepth ());
    setFloatValue (kHiHatSection, kFxReverbModRateKey, settingsProperties.getFxReverbModRate ());
    setFloatValue (kHiHatSection, kFxReverbDiffusionKey, settingsProperties.getFxReverbDiffusion ());
    setFloatValue (kHiHatSection, kFxReverbMixKey, settingsProperties.getFxReverbMix ());

    // Glitch � probability
    setFloatValue (kHiHatSection, kFxGlitchProbabilityMinKey, settingsProperties.getFxGlitchProbabilityMin ());
    setFloatValue (kHiHatSection, kFxGlitchProbabilityMaxKey, settingsProperties.getFxGlitchProbabilityMax ());

    // Glitch � weights (low)
    setFloatValue (kHiHatSection, kFxGlitchWeightHoldLowKey, settingsProperties.getFxGlitchWeightHoldLow ());
    setFloatValue (kHiHatSection, kFxGlitchWeightStutterLowKey, settingsProperties.getFxGlitchWeightStutterLow ());
    setFloatValue (kHiHatSection, kFxGlitchWeightCrushLowKey, settingsProperties.getFxGlitchWeightCrushLow ());
    setFloatValue (kHiHatSection, kFxGlitchWeightDropLowKey, settingsProperties.getFxGlitchWeightDropLow ());

    // Glitch � weights (high)
    setFloatValue (kHiHatSection, kFxGlitchWeightHoldHighKey, settingsProperties.getFxGlitchWeightHoldHigh ());
    setFloatValue (kHiHatSection, kFxGlitchWeightStutterHighKey, settingsProperties.getFxGlitchWeightStutterHigh ());
    setFloatValue (kHiHatSection, kFxGlitchWeightCrushHighKey, settingsProperties.getFxGlitchWeightCrushHigh ());
    setFloatValue (kHiHatSection, kFxGlitchWeightDropHighKey, settingsProperties.getFxGlitchWeightDropHigh ());

    // Glitch � drop
    setFloatValue (kHiHatSection, kFxGlitchDropKeepLevelMinKey, settingsProperties.getFxGlitchDropKeepLevelMin ());
    setFloatValue (kHiHatSection, kFxGlitchDropKeepLevelMaxKey, settingsProperties.getFxGlitchDropKeepLevelMax ());
    setFloatValue (kHiHatSection, kFxGlitchDropKeepTimeMinKey, settingsProperties.getFxGlitchDropKeepTimeMin ());
    setFloatValue (kHiHatSection, kFxGlitchDropKeepTimeMaxKey, settingsProperties.getFxGlitchDropKeepTimeMax ());

    // Glitch � crush
    setFloatValue (kHiHatSection, kFxGlitchCrushTimeMinKey, settingsProperties.getFxGlitchCrushTimeMin ());
    setFloatValue (kHiHatSection, kFxGlitchCrushTimeMaxKey, settingsProperties.getFxGlitchCrushTimeMax ());

    // Glitch � microloop
    setFloatValue (kHiHatSection, kFxGlitchMicroloopSmplTMinKey, settingsProperties.getFxGlitchMicroloopSmplTMin ());
    setFloatValue (kHiHatSection, kFxGlitchMicroloopSmplTMaxKey, settingsProperties.getFxGlitchMicroloopSmplTMax ());
    setFloatValue (kHiHatSection, kFxGlitchMicroloopPlayTMinKey, settingsProperties.getFxGlitchMicroloopPlayTMin ());
    setFloatValue (kHiHatSection, kFxGlitchMicroloopPlayTMaxKey, settingsProperties.getFxGlitchMicroloopPlayTMax ());

    // Glitch � stutter
    setFloatValue (kHiHatSection, kFxGlitchStutterSmplTMinKey, settingsProperties.getFxGlitchStutterSmplTMin ());
    setFloatValue (kHiHatSection, kFxGlitchStutterSmplTMaxKey, settingsProperties.getFxGlitchStutterSmplTMax ());
    setIntValue (kHiHatSection, kFxGlitchStutterNumMinKey, settingsProperties.getFxGlitchStutterNumMin ());
    setIntValue (kHiHatSection, kFxGlitchStutterNumMaxKey, settingsProperties.getFxGlitchStutterNumMax ());
    setIntValue (kHiHatSection, kFxGlitchStutterWindowKey, settingsProperties.getFxGlitchStutterWindow ());

    patternListProperties.forEachPattern ([this] (juce::ValueTree patternVT, [[maybe_unused]] int patternIndex)
    {
        PatternProperties patternProperties (patternVT, ValueTreeWrapper<PatternProperties>::WrapperType::client, ValueTreeWrapper<PatternProperties>::EnableCallbacks::no);
        setValue (kPatternsSection, patternProperties.getId (), patternProperties.getPattern ());
        return true;
    });
    effectListProperties.forEachEffect ([this] (juce::ValueTree effectVT, [[maybe_unused]] int effectIndex)
    {
        EffectProperties effectProperties (effectVT, ValueTreeWrapper<EffectProperties>::WrapperType::client, ValueTreeWrapper<EffectProperties>::EnableCallbacks::no);
        setValue (kEffectsSection, effectProperties.getId (), effectProperties.getEffect ());
        return true;
    });
}

void HiHatIniData::FillInPropertiesFromData (juce::ValueTree clutchVt)
{
    SettingsProperties settingsProperties (clutchVt, ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::no);
    PatternListProperties patternListProperties (clutchVt, ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::no);
    EffectListProperties effectListProperties (clutchVt, ValueTreeWrapper<EffectListProperties>::WrapperType::client, ValueTreeWrapper<EffectListProperties>::EnableCallbacks::no);
    const auto getFloatValue = [this] (const juce::String& section, const juce::String& key, float defaultValue) -> float
    {
        const auto valueString = getValue (section, key);
        if (valueString.isNotEmpty ())
            return valueString.getFloatValue ();
        return defaultValue;
    };
    const auto getIntValue = [this] (const juce::String& section, const juce::String& key, int defaultValue) -> int
    {
        const auto valueString = getValue (section, key);
        if (valueString.isNotEmpty ())
            return valueString.getIntValue ();
        return defaultValue;
    };
        // Core
    settingsProperties.setPitchLow (getFloatValue (kHiHatSection, kPitchLowKey, 0.125f), false);
    settingsProperties.setPitchHigh (getFloatValue (kHiHatSection, kPitchHighKey, 2.5f), false);
    settingsProperties.setEnvelopeMaxRelease (getFloatValue (kHiHatSection, kEnvelopeMaxReleaseKey, 4.0f), false);
    settingsProperties.setChokeRelease (getFloatValue (kHiHatSection, kChokeReleaseKey, 0.08f), false);
    // RELEASE_MODE replaced CLSD_RELEASE_MODE, but the old key name is still accepted
    if (getValue (kHiHatSection, kReleaseModeKey).isNotEmpty ())
        settingsProperties.setReleaseMode (getIntValue (kHiHatSection, kReleaseModeKey, 1), false);
    else
        settingsProperties.setReleaseMode (getIntValue (kHiHatSection, kClsdReleaseModeKey, 1), false);
    settingsProperties.setClsdRelOfstScale (getFloatValue (kHiHatSection, kClsdRelOfstScaleKey, 0.5f), false);
    settingsProperties.setClsdMaxRelease (getFloatValue (kHiHatSection, kClsdMaxReleaseKey, 0.8f), false);
    settingsProperties.setAccClRelMod (getFloatValue (kHiHatSection, kAccClRelModKey, 1.18f), false);
    settingsProperties.setAccOpRelMod (getFloatValue (kHiHatSection, kAccOpRelModKey, 1.25f), false);
    settingsProperties.setAccClAmpMod (getFloatValue (kHiHatSection, kAccClAmpModKey, 1.3f), false);
    settingsProperties.setAccOpAmpMod (getFloatValue (kHiHatSection, kAccOpAmpModKey, 1.25f), false);

    // CV / control
    settingsProperties.setFxCvUnipolar (getIntValue (kHiHatSection, kFxCvUnipolarKey, 1), false);
    settingsProperties.setVelocityUnipolar (getIntValue (kHiHatSection, kVelocityUnipolarKey, 0), false);
    settingsProperties.setCvDisableVelocity (getIntValue (kHiHatSection, kCvDisableVelocityKey, 0), false);
    settingsProperties.setCvDisableFx (getIntValue (kHiHatSection, kCvDisableFxKey, 0), false);
    settingsProperties.setGateMode (getIntValue (kHiHatSection, kGateModeKey, 0), false);
    settingsProperties.setFeelAttackMod (getFloatValue (kHiHatSection, kFeelAttackModKey, 1.0f), false);
    settingsProperties.setFeelReleaseMod (getFloatValue (kHiHatSection, kFeelReleaseModKey, 1.0f), false);
    settingsProperties.setFeelAmpMod (getFloatValue (kHiHatSection, kFeelAmpModKey, 1.0f), false);
    settingsProperties.setKnobPosTakeup (getIntValue (kHiHatSection, kKnobPosTakeupKey, 1), false);

    // Filters
    settingsProperties.setFltrHpfMinFreq (getIntValue (kHiHatSection, kFltrHpfMinFreqKey, 100), false);
    settingsProperties.setFltrHpfMaxFreq (getIntValue (kHiHatSection, kFltrHpfMaxFreqKey, 14000), false);
    settingsProperties.setFltrLpfMinFreq (getIntValue (kHiHatSection, kFltrLpfMinFreqKey, 200), false);
    settingsProperties.setFltrLpfMaxFreq (getIntValue (kHiHatSection, kFltrLpfMaxFreqKey, 20000), false);
    settingsProperties.setFltrHpfQ (getFloatValue (kHiHatSection, kFltrHpfQKey, 1.0f), false);
    settingsProperties.setFltrLpfQ (getFloatValue (kHiHatSection, kFltrLpfQKey, 0.707f), false);

    // DJ Filter
    settingsProperties.setFxDjfilterHpfMin (getIntValue (kHiHatSection, kFxDjfilterHpfMinKey, 100), false);
    settingsProperties.setFxDjfilterHpfMax (getIntValue (kHiHatSection, kFxDjfilterHpfMaxKey, 14000), false);
    settingsProperties.setFxDjfilterLpfMin (getIntValue (kHiHatSection, kFxDjfilterLpfMinKey, 200), false);
    settingsProperties.setFxDjfilterLpfMax (getIntValue (kHiHatSection, kFxDjfilterLpfMaxKey, 20000), false);
    settingsProperties.setFxDjfilterQMin (getFloatValue (kHiHatSection, kFxDjfilterQMinKey, 0.5f), false);
    settingsProperties.setFxDjfilterQMax (getFloatValue (kHiHatSection, kFxDjfilterQMaxKey, 4.0f), false);
    settingsProperties.setFxDjfilterQGainReduction (getFloatValue (kHiHatSection, kFxDjfilterQGainReductionKey, 0.12f), false);

    // Dub Echo
    settingsProperties.setFxDubEchoTmin (getIntValue (kHiHatSection, kFxDubEchoTminKey, 30), false);
    settingsProperties.setFxDubEchoHpf (getIntValue (kHiHatSection, kFxDubEchoHpfKey, 400), false);
    settingsProperties.setFxDubEchoLpf (getIntValue (kHiHatSection, kFxDubEchoLpfKey, 8400), false);
    settingsProperties.setFxDubEchoMix (getFloatValue (kHiHatSection, kFxDubEchoMixKey, 0.38f), false);

    // Chorus
    settingsProperties.setFxChorusCenter (getFloatValue (kHiHatSection, kFxChorusCenterKey, 12.0f), false);
    settingsProperties.setFxChorusDepth (getFloatValue (kHiHatSection, kFxChorusDepthKey, 5.0f), false);
    settingsProperties.setFxChorusMix (getFloatValue (kHiHatSection, kFxChorusMixKey, 1.0f), false);
    settingsProperties.setFxChorusSpread (getFloatValue (kHiHatSection, kFxChorusSpreadKey, 0.01f), false);
    settingsProperties.setFxChorusTaps (getIntValue (kHiHatSection, kFxChorusTapsKey, 4), false);
    settingsProperties.setFxChorusLfoB (getFloatValue (kHiHatSection, kFxChorusLfoBKey, 0.002f), false);
    settingsProperties.setFxChorusLfoT (getFloatValue (kHiHatSection, kFxChorusLfoTKey, 3.0f), false);
    settingsProperties.setFxChorusType (getIntValue (kHiHatSection, kFxChorusTypeKey, 1), false);
    settingsProperties.setFxChorusStagger (getFloatValue (kHiHatSection, kFxChorusStaggerKey, 0.5f), false);

    // Reverb
    settingsProperties.setFxReverbLpf (getIntValue (kHiHatSection, kFxReverbLpfKey, 9000), false);
    settingsProperties.setFxReverbHpf (getIntValue (kHiHatSection, kFxReverbHpfKey, 700), false);
    settingsProperties.setFxReverbType (getIntValue (kHiHatSection, kFxReverbTypeKey, 1), false);
    settingsProperties.setFxReverbSizeMin (getFloatValue (kHiHatSection, kFxReverbSizeMinKey, 0.6f), false);
    settingsProperties.setFxReverbSizeMax (getFloatValue (kHiHatSection, kFxReverbSizeMaxKey, 0.9f), false);
    settingsProperties.setFxReverbPredelay (getIntValue (kHiHatSection, kFxReverbPredelayKey, 21), false);
    settingsProperties.setFxReverbModDepth (getFloatValue (kHiHatSection, kFxReverbModDepthKey, 0.6f), false);
    settingsProperties.setFxReverbModRate (getFloatValue (kHiHatSection, kFxReverbModRateKey, 1.0f), false);
    settingsProperties.setFxReverbDiffusion (getFloatValue (kHiHatSection, kFxReverbDiffusionKey, 0.75f), false);
    settingsProperties.setFxReverbMix (getFloatValue (kHiHatSection, kFxReverbMixKey, 0.6f), false);

    // Glitch � probability
    settingsProperties.setFxGlitchProbabilityMin (getFloatValue (kHiHatSection, kFxGlitchProbabilityMinKey, 0.00005f), false);
    settingsProperties.setFxGlitchProbabilityMax (getFloatValue (kHiHatSection, kFxGlitchProbabilityMaxKey, 0.003f), false);

    // Glitch � weights (low)
    settingsProperties.setFxGlitchWeightHoldLow (getFloatValue (kHiHatSection, kFxGlitchWeightHoldLowKey, 0.15f), false);
    settingsProperties.setFxGlitchWeightStutterLow (getFloatValue (kHiHatSection, kFxGlitchWeightStutterLowKey, 0.05f), false);
    settingsProperties.setFxGlitchWeightCrushLow (getFloatValue (kHiHatSection, kFxGlitchWeightCrushLowKey, 0.30f), false);
    settingsProperties.setFxGlitchWeightDropLow (getFloatValue (kHiHatSection, kFxGlitchWeightDropLowKey, 0.02f), false);

    // Glitch � weights (high)
    settingsProperties.setFxGlitchWeightHoldHigh (getFloatValue (kHiHatSection, kFxGlitchWeightHoldHighKey, 0.30f), false);
    settingsProperties.setFxGlitchWeightStutterHigh (getFloatValue (kHiHatSection, kFxGlitchWeightStutterHighKey, 0.20f), false);
    settingsProperties.setFxGlitchWeightCrushHigh (getFloatValue (kHiHatSection, kFxGlitchWeightCrushHighKey, 0.20f), false);
    settingsProperties.setFxGlitchWeightDropHigh (getFloatValue (kHiHatSection, kFxGlitchWeightDropHighKey, 0.07f), false);

    // Glitch � drop
    settingsProperties.setFxGlitchDropKeepLevelMin (getFloatValue (kHiHatSection, kFxGlitchDropKeepLevelMinKey, 0.0f), false);
    settingsProperties.setFxGlitchDropKeepLevelMax (getFloatValue (kHiHatSection, kFxGlitchDropKeepLevelMaxKey, 0.75f), false);
    settingsProperties.setFxGlitchDropKeepTimeMin (getFloatValue (kHiHatSection, kFxGlitchDropKeepTimeMinKey, 4.0f), false);
    settingsProperties.setFxGlitchDropKeepTimeMax (getFloatValue (kHiHatSection, kFxGlitchDropKeepTimeMaxKey, 40.0f), false);

    // Glitch � crush
    settingsProperties.setFxGlitchCrushTimeMin (getFloatValue (kHiHatSection, kFxGlitchCrushTimeMinKey, 10.0f), false);
    settingsProperties.setFxGlitchCrushTimeMax (getFloatValue (kHiHatSection, kFxGlitchCrushTimeMaxKey, 50.0f), false);

    // Glitch � microloop
    settingsProperties.setFxGlitchMicroloopSmplTMin (getFloatValue (kHiHatSection, kFxGlitchMicroloopSmplTMinKey, 0.2f), false);
    settingsProperties.setFxGlitchMicroloopSmplTMax (getFloatValue (kHiHatSection, kFxGlitchMicroloopSmplTMaxKey, 3.0f), false);
    settingsProperties.setFxGlitchMicroloopPlayTMin (getFloatValue (kHiHatSection, kFxGlitchMicroloopPlayTMinKey, 5.0f), false);
    settingsProperties.setFxGlitchMicroloopPlayTMax (getFloatValue (kHiHatSection, kFxGlitchMicroloopPlayTMaxKey, 15.0f), false);

    // Glitch � stutter
    settingsProperties.setFxGlitchStutterSmplTMin (getFloatValue (kHiHatSection, kFxGlitchStutterSmplTMinKey, 3.0f), false);
    settingsProperties.setFxGlitchStutterSmplTMax (getFloatValue (kHiHatSection, kFxGlitchStutterSmplTMaxKey, 10.0f), false);
    settingsProperties.setFxGlitchStutterNumMin (getIntValue (kHiHatSection, kFxGlitchStutterNumMinKey, 2), false);
    settingsProperties.setFxGlitchStutterNumMax (getIntValue (kHiHatSection, kFxGlitchStutterNumMaxKey, 5), false);
    settingsProperties.setFxGlitchStutterWindow (getIntValue (kHiHatSection, kFxGlitchStutterWindowKey, 20), false);

    patternListProperties.forEachPattern ([this] (juce::ValueTree patternVT, [[maybe_unused]] int patternIndex)
    {
        PatternProperties patternProperties (patternVT, ValueTreeWrapper<PatternProperties>::WrapperType::client, ValueTreeWrapper<PatternProperties>::EnableCallbacks::no);
        patternProperties.setPattern (getValue (kPatternsSection, patternProperties.getId ()), false);
        return true;
    });
    effectListProperties.forEachEffect ([this] (juce::ValueTree effectVT, [[maybe_unused]] int effectIndex)
    {
        EffectProperties effectProperties (effectVT, ValueTreeWrapper<EffectProperties>::WrapperType::client, ValueTreeWrapper<EffectProperties>::EnableCallbacks::no);
        effectProperties.setEffect (getValue (kEffectsSection, effectProperties.getId ()), false);
        return true;
    });
}

void HiHatIniData::readFromFile (const juce::File& file)
{
    readFromIniText (juce::StringArray::fromLines (file.loadFileAsString ()));
}

void HiHatIniData::readFromIniText (const juce::StringArray& hiHatIniLines)
{
    iniLines.clear ();
    juce::String currentSection;
    for (auto& line : hiHatIniLines)
    {
        HiHatIniFileLine iniLine;
        iniLine.section = currentSection;
        iniLine.rawLine = line;
        auto trimmedLine = line.trim ();
        if (trimmedLine.isEmpty ())
        {
            iniLine.lineType = LineType::unknown;
        }
        else if (trimmedLine.startsWithChar (';'))
        {
            iniLine.lineType = LineType::comment;
            iniLine.comment = trimmedLine.substring (1);
        }
        else if (trimmedLine.startsWithChar ('['))
        {
            iniLine.lineType = LineType::section;
            currentSection = trimmedLine.fromFirstOccurrenceOf ("[", false, false).upToLastOccurrenceOf ("]", false, false).trim ();
            iniLine.section = currentSection;
        }
        else
        {
            auto key { trimmedLine.upToFirstOccurrenceOf (" ", false, false).trim () };
            if (!key.isEmpty ())
            {
                auto afterKey = trimmedLine.fromFirstOccurrenceOf (" ", false, false).trim ();
                if (afterKey.startsWithChar ('='))
                {
                    auto valuePart = afterKey.fromFirstOccurrenceOf ("=", false, false).trim ();
                    if (!valuePart.isEmpty ())
                    {
                        iniLine.lineType = LineType::keyValuePair;
                        iniLine.key = key;
                        iniLine.value = valuePart.upToFirstOccurrenceOf (" ;", false, false).trim ();
                        auto comment = valuePart.fromFirstOccurrenceOf (" ;", true, false).trim ();
                        if (!comment.isEmpty ())
                        {
                            iniLine.comment = comment;
                            auto defaultValueIndex = comment.lastIndexOf ("d:");
                            if (defaultValueIndex != -1)
                                iniLine.defaultValue = comment.substring (defaultValueIndex + 2).trim ();
                        }
                    }
                }
            }
            else
            {
                iniLine.lineType = LineType::unknown;
            }
        }
        iniLines.push_back (iniLine);
    }
}
void HiHatIniData::writeToFile (juce::File outputFile)
{
    juce::FileOutputStream outputStream (outputFile);
    outputStream.setPosition (0);
    outputStream.truncate ();
    if (outputStream.openedOk ())
    {
        for (const auto& iniLine : iniLines)
        {
            switch (iniLine.lineType)
            {
                case LineType::section:
                    outputStream << "[" << iniLine.section << "]\n";
                break;

                case LineType::unknown:
                case LineType::comment:
                    outputStream << iniLine.rawLine << "\n";
                break;

                case LineType::keyValuePair:
                {
                    const auto valueColumn = [section = iniLine.section] ()
                    {
                        if (section == kHiHatSection)
                            return kValueColumn;
                        else if (section == kPatternsSection)
                            return 12;
                        else if (section == kEffectsSection)
                            return 11;
                        else
                            return 5;
                    } ();
                    outputStream << iniLine.key.paddedRight (' ', valueColumn) << "= " << iniLine.value.paddedRight (' ', kCommentColumn - kValueColumn - 2);
                    if (!iniLine.comment.isEmpty ())
                        outputStream << iniLine.comment.paddedRight (' ', kDefaultValueColumn - kCommentColumn);
                    outputStream << "\n";
                }
                break;

                default:
                break;
            }
        }
    }
}

juce::String HiHatIniData::getValue (const juce::String& section, const juce::String& key) const
{
    for (const auto& iniLine : iniLines)
    {
        if (iniLine.lineType == LineType::keyValuePair)
        {
            if (iniLine.section == section && iniLine.key == key)
                return iniLine.value;
        }
    }
    return {};
}

void HiHatIniData::setValue (const juce::String& section, const juce::String& key, const juce::String& value)
{
    for (auto& iniLine : iniLines)
    {
        if (iniLine.lineType == LineType::keyValuePair)
        {
            if (iniLine.section == section && iniLine.key == key)
                iniLine.value = value;
        }
    }
}