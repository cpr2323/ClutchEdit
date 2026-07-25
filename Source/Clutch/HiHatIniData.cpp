#include "HiHatIniData.h"
#include "HiHatIniKeys.h"
#include "HiHatIniValues.h"
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
    settingsProperties.setPitchLow (getFloatValue (kHiHatSection, kPitchLowKey, kPitchLowDefault), false);
    settingsProperties.setPitchHigh (getFloatValue (kHiHatSection, kPitchHighKey, kPitchHighDefault), false);
    settingsProperties.setEnvelopeMaxRelease (getFloatValue (kHiHatSection, kEnvelopeMaxReleaseKey, kEnvelopeMaxReleaseDefault), false);
    settingsProperties.setChokeRelease (getFloatValue (kHiHatSection, kChokeReleaseKey, kChokeReleaseDefault), false);
    // RELEASE_MODE replaced CLSD_RELEASE_MODE, but the old key name is still accepted
    if (getValue (kHiHatSection, kReleaseModeKey).isNotEmpty ())
        settingsProperties.setReleaseMode (getIntValue (kHiHatSection, kReleaseModeKey, kReleaseModeDefault), false);
    else
        settingsProperties.setReleaseMode (getIntValue (kHiHatSection, k_DEPRECATED_ClsdReleaseModeKey, kReleaseModeDefault), false);
    settingsProperties.setClsdRelOfstScale (getFloatValue (kHiHatSection, kClsdRelOfstScaleKey, kClsdRelOfstScaleDefault), false);
    settingsProperties.setClsdMaxRelease (getFloatValue (kHiHatSection, kClsdMaxReleaseKey, kClsdMaxReleaseDefault), false);
    settingsProperties.setAccClRelMod (getFloatValue (kHiHatSection, kAccClRelModKey, kAccClRelModDefault), false);
    settingsProperties.setAccOpRelMod (getFloatValue (kHiHatSection, kAccOpRelModKey, kAccOpRelModDefault), false);
    settingsProperties.setAccClAmpMod (getFloatValue (kHiHatSection, kAccClAmpModKey, kAccClAmpModDefault), false);
    settingsProperties.setAccOpAmpMod (getFloatValue (kHiHatSection, kAccOpAmpModKey, kAccOpAmpModDefault), false);

    // CV / control
    settingsProperties.setFxCvUnipolar (getIntValue (kHiHatSection, kFxCvUnipolarKey, kFxCvUnipolarDefault), false);
    settingsProperties.setVelocityUnipolar (getIntValue (kHiHatSection, kVelocityUnipolarKey, kVelocityUnipolarDefault), false);
    settingsProperties.setCvDisableVelocity (getIntValue (kHiHatSection, kCvDisableVelocityKey, kCvDisableVelocityDefault), false);
    settingsProperties.setCvDisableFx (getIntValue (kHiHatSection, kCvDisableFxKey, kCvDisableFxDefault), false);
    settingsProperties.setGateMode (getIntValue (kHiHatSection, kGateModeKey, kGateModeDefault), false);
    settingsProperties.setFeelAttackMod (getFloatValue (kHiHatSection, kFeelAttackModKey, kFeelAttackModDefault), false);
    settingsProperties.setFeelReleaseMod (getFloatValue (kHiHatSection, kFeelReleaseModKey, kFeelReleaseModDefault), false);
    settingsProperties.setFeelAmpMod (getFloatValue (kHiHatSection, kFeelAmpModKey, kFeelAmpModDefault), false);
    settingsProperties.setKnobPosTakeup (getIntValue (kHiHatSection, kKnobPosTakeupKey, kKnobPosTakeupDefault), false);

    // Filters
    settingsProperties.setFltrHpfMinFreq (getIntValue (kHiHatSection, kFltrHpfMinFreqKey, kFltrHpfMinFreqDefault), false);
    settingsProperties.setFltrHpfMaxFreq (getIntValue (kHiHatSection, kFltrHpfMaxFreqKey, kFltrHpfMaxFreqDefault), false);
    settingsProperties.setFltrLpfMinFreq (getIntValue (kHiHatSection, kFltrLpfMinFreqKey, kFltrLpfMinFreqDefault), false);
    settingsProperties.setFltrLpfMaxFreq (getIntValue (kHiHatSection, kFltrLpfMaxFreqKey, kFltrLpfMaxFreqDefault), false);
    settingsProperties.setFltrHpfQ (getFloatValue (kHiHatSection, kFltrHpfQKey, kFltrHpfQDefault), false);
    settingsProperties.setFltrLpfQ (getFloatValue (kHiHatSection, kFltrLpfQKey, kFltrLpfQDefault), false);

    // DJ Filter
    settingsProperties.setFxDjfilterHpfMin (getIntValue (kHiHatSection, kFxDjfilterHpfMinKey, kFxDjfilterHpfMinDefault), false);
    settingsProperties.setFxDjfilterHpfMax (getIntValue (kHiHatSection, kFxDjfilterHpfMaxKey, kFxDjfilterHpfMaxDefault), false);
    settingsProperties.setFxDjfilterLpfMin (getIntValue (kHiHatSection, kFxDjfilterLpfMinKey, kFxDjfilterLpfMinDefault), false);
    settingsProperties.setFxDjfilterLpfMax (getIntValue (kHiHatSection, kFxDjfilterLpfMaxKey, kFxDjfilterLpfMaxDefault), false);
    settingsProperties.setFxDjfilterQMin (getFloatValue (kHiHatSection, kFxDjfilterQMinKey, kFxDjfilterQMinDefault), false);
    settingsProperties.setFxDjfilterQMax (getFloatValue (kHiHatSection, kFxDjfilterQMaxKey, kFxDjfilterQMaxDefault), false);
    settingsProperties.setFxDjfilterQGainReduction (getFloatValue (kHiHatSection, kFxDjfilterQGainReductionKey, kFxDjfilterQGainReductionDefault), false);

    // Dub Echo
    settingsProperties.setFxDubEchoTmin (getIntValue (kHiHatSection, kFxDubEchoTminKey, kFxDubEchoTminDefault), false);
    settingsProperties.setFxDubEchoHpf (getIntValue (kHiHatSection, kFxDubEchoHpfKey, kFxDubEchoHpfDefault), false);
    settingsProperties.setFxDubEchoLpf (getIntValue (kHiHatSection, kFxDubEchoLpfKey, kFxDubEchoLpfDefault), false);
    settingsProperties.setFxDubEchoMix (getFloatValue (kHiHatSection, kFxDubEchoMixKey, kFxDubEchoMixDefault), false);

    // Chorus
    settingsProperties.setFxChorusCenter (getFloatValue (kHiHatSection, kFxChorusCenterKey, kFxChorusCenterDefault), false);
    settingsProperties.setFxChorusDepth (getFloatValue (kHiHatSection, kFxChorusDepthKey, kFxChorusDepthDefault), false);
    settingsProperties.setFxChorusMix (getFloatValue (kHiHatSection, kFxChorusMixKey, kFxChorusMixDefault), false);
    settingsProperties.setFxChorusSpread (getFloatValue (kHiHatSection, kFxChorusSpreadKey, kFxChorusSpreadDefault), false);
    settingsProperties.setFxChorusTaps (getIntValue (kHiHatSection, kFxChorusTapsKey, kFxChorusTapsDefault), false);
    settingsProperties.setFxChorusLfoB (getFloatValue (kHiHatSection, kFxChorusLfoBKey, kFxChorusLfoBDefault), false);
    settingsProperties.setFxChorusLfoT (getFloatValue (kHiHatSection, kFxChorusLfoTKey, kFxChorusLfoTDefault), false);
    settingsProperties.setFxChorusType (getIntValue (kHiHatSection, kFxChorusTypeKey, kFxChorusTypeDefault), false);
    settingsProperties.setFxChorusStagger (getFloatValue (kHiHatSection, kFxChorusStaggerKey, kFxChorusStaggerDefault), false);

    // Reverb
    settingsProperties.setFxReverbLpf (getIntValue (kHiHatSection, kFxReverbLpfKey, kFxReverbLpfDefault), false);
    settingsProperties.setFxReverbHpf (getIntValue (kHiHatSection, kFxReverbHpfKey, kFxReverbHpfDefault), false);
    settingsProperties.setFxReverbType (getIntValue (kHiHatSection, kFxReverbTypeKey, kFxReverbTypeDefault), false);
    settingsProperties.setFxReverbSizeMin (getFloatValue (kHiHatSection, kFxReverbSizeMinKey, kFxReverbSizeMinDefault), false);
    settingsProperties.setFxReverbSizeMax (getFloatValue (kHiHatSection, kFxReverbSizeMaxKey, kFxReverbSizeMaxDefault), false);
    settingsProperties.setFxReverbPredelay (getIntValue (kHiHatSection, kFxReverbPredelayKey, kFxReverbPredelayDefault), false);
    settingsProperties.setFxReverbModDepth (getFloatValue (kHiHatSection, kFxReverbModDepthKey, kFxReverbModDepthDefault), false);
    settingsProperties.setFxReverbModRate (getFloatValue (kHiHatSection, kFxReverbModRateKey, kFxReverbModRateDefault), false);
    settingsProperties.setFxReverbDiffusion (getFloatValue (kHiHatSection, kFxReverbDiffusionKey, kFxReverbDiffusionDefault), false);
    settingsProperties.setFxReverbMix (getFloatValue (kHiHatSection, kFxReverbMixKey, kFxReverbMixDefault), false);

    // Glitch � probability
    settingsProperties.setFxGlitchProbabilityMin (getFloatValue (kHiHatSection, kFxGlitchProbabilityMinKey, kFxGlitchProbabilityMinDefault), false);
    settingsProperties.setFxGlitchProbabilityMax (getFloatValue (kHiHatSection, kFxGlitchProbabilityMaxKey, kFxGlitchProbabilityMaxDefault), false);

    // Glitch � weights (low)
    settingsProperties.setFxGlitchWeightHoldLow (getFloatValue (kHiHatSection, kFxGlitchWeightHoldLowKey, kFxGlitchWeightHoldLowDefault), false);
    settingsProperties.setFxGlitchWeightStutterLow (getFloatValue (kHiHatSection, kFxGlitchWeightStutterLowKey, kFxGlitchWeightStutterLowDefault), false);
    settingsProperties.setFxGlitchWeightCrushLow (getFloatValue (kHiHatSection, kFxGlitchWeightCrushLowKey, kFxGlitchWeightCrushLowDefault), false);
    settingsProperties.setFxGlitchWeightDropLow (getFloatValue (kHiHatSection, kFxGlitchWeightDropLowKey, kFxGlitchWeightDropLowDefault), false);

    // Glitch � weights (high)
    settingsProperties.setFxGlitchWeightHoldHigh (getFloatValue (kHiHatSection, kFxGlitchWeightHoldHighKey, kFxGlitchWeightHoldHighDefault), false);
    settingsProperties.setFxGlitchWeightStutterHigh (getFloatValue (kHiHatSection, kFxGlitchWeightStutterHighKey, kFxGlitchWeightStutterHighDefault), false);
    settingsProperties.setFxGlitchWeightCrushHigh (getFloatValue (kHiHatSection, kFxGlitchWeightCrushHighKey, kFxGlitchWeightCrushHighDefault), false);
    settingsProperties.setFxGlitchWeightDropHigh (getFloatValue (kHiHatSection, kFxGlitchWeightDropHighKey, kFxGlitchWeightDropHighDefault), false);

    // Glitch � drop
    settingsProperties.setFxGlitchDropKeepLevelMin (getFloatValue (kHiHatSection, kFxGlitchDropKeepLevelMinKey, kFxGlitchDropKeepLevelMinDefault), false);
    settingsProperties.setFxGlitchDropKeepLevelMax (getFloatValue (kHiHatSection, kFxGlitchDropKeepLevelMaxKey, kFxGlitchDropKeepLevelMaxDefault), false);
    settingsProperties.setFxGlitchDropKeepTimeMin (getFloatValue (kHiHatSection, kFxGlitchDropKeepTimeMinKey, kFxGlitchDropKeepTimeMinDefault), false);
    settingsProperties.setFxGlitchDropKeepTimeMax (getFloatValue (kHiHatSection, kFxGlitchDropKeepTimeMaxKey, kFxGlitchDropKeepTimeMaxDefault), false);

    // Glitch � crush
    settingsProperties.setFxGlitchCrushTimeMin (getFloatValue (kHiHatSection, kFxGlitchCrushTimeMinKey, kFxGlitchCrushTimeMinDefault), false);
    settingsProperties.setFxGlitchCrushTimeMax (getFloatValue (kHiHatSection, kFxGlitchCrushTimeMaxKey, kFxGlitchCrushTimeMaxDefault), false);

    // Glitch � microloop
    settingsProperties.setFxGlitchMicroloopSmplTMin (getFloatValue (kHiHatSection, kFxGlitchMicroloopSmplTMinKey, kFxGlitchMicroloopSmplTMinDefault), false);
    settingsProperties.setFxGlitchMicroloopSmplTMax (getFloatValue (kHiHatSection, kFxGlitchMicroloopSmplTMaxKey, kFxGlitchMicroloopSmplTMaxDefault), false);
    settingsProperties.setFxGlitchMicroloopPlayTMin (getFloatValue (kHiHatSection, kFxGlitchMicroloopPlayTMinKey, kFxGlitchMicroloopPlayTMinDefault), false);
    settingsProperties.setFxGlitchMicroloopPlayTMax (getFloatValue (kHiHatSection, kFxGlitchMicroloopPlayTMaxKey, kFxGlitchMicroloopPlayTMaxDefault), false);

    // Glitch � stutter
    settingsProperties.setFxGlitchStutterSmplTMin (getFloatValue (kHiHatSection, kFxGlitchStutterSmplTMinKey, kFxGlitchStutterSmplTMinDefault), false);
    settingsProperties.setFxGlitchStutterSmplTMax (getFloatValue (kHiHatSection, kFxGlitchStutterSmplTMaxKey, kFxGlitchStutterSmplTMaxDefault), false);
    settingsProperties.setFxGlitchStutterNumMin (getIntValue (kHiHatSection, kFxGlitchStutterNumMinKey, kFxGlitchStutterNumMinDefault), false);
    settingsProperties.setFxGlitchStutterNumMax (getIntValue (kHiHatSection, kFxGlitchStutterNumMaxKey, kFxGlitchStutterNumMaxDefault), false);
    settingsProperties.setFxGlitchStutterWindow (getIntValue (kHiHatSection, kFxGlitchStutterWindowKey, kFxGlitchStutterWindowDefault), false);

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