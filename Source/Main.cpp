#include <JuceHeader.h>
#include "AppProperties.h"
#include "SystemServices.h"
#include "Clutch/ClutchProperties.h"
#include "Clutch/EffectListProperties.h"
#include "Clutch/HiHatIniData.h"
#include "Clutch/SettingsProperties.h"
#include "Clutch/PatternListProperties.h"
#include "Clutch/Audio/AudioPlayer.h"
#include "GUI/GuiControlProperties.h"
#include "GUI/GuiProperties.h"
#include "GUI/MainComponent.h"
#include "Utility/DebugLog.h"
#include "Utility/PersistentRootProperties.h"
#include "Utility/RootProperties.h"
#include "Utility/RuntimeRootProperties.h"
#include "Utility/ValueTreeFile.h"
#include "Utility/ValueTreeMonitor.h"

// used to add things like TEST, or ALPHA, or BETA, etc to the version number when displayed
constexpr char* kVersionDecorator { "" };

// this requires the third party Melatonin Inspector be installed and added to the project
// https://github.com/sudara/melatonin_inspector
#define ENABLE_MELATONIN_INSPECTOR 0

const juce::String PropertiesFileExtension { ".properties" };

void crashHandler (void* /*data*/)
{
    FlushDebugLog ();
    juce::Logger::writeToLog (juce::SystemStats::getStackBacktrace ());
    FlushDebugLog ();
}

HiHatIniData gHiHatIniData;

void FillInDataFromVt (HiHatIniData& data, const juce::ValueTree clutchVT)
{
    SettingsProperties settingsProperties (clutchVT, ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::no);
    PatternListProperties patternListProperties (clutchVT, ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::no);
    EffectListProperties effectListProperties (clutchVT, ValueTreeWrapper<EffectListProperties>::WrapperType::client, ValueTreeWrapper<EffectListProperties>::EnableCallbacks::no);

    const auto setFloatValue = [&data] (const juce::String& section, const juce::String& key, float value)
    {
        data.setValue (section, key, juce::String (value, 5).trimCharactersAtEnd ("0").trimCharactersAtEnd ("."));
    };
    const auto setIntValue = [&data] (const juce::String& section, const juce::String& key, int value)
    {
        data.setValue (section, key, juce::String (value));
    };

    // Core
    setFloatValue ("HIHAT", "PITCH_LOW", settingsProperties.getPitchLow ());
    setFloatValue ("HIHAT", "PITCH_HIGH", settingsProperties.getPitchHigh ());
    setFloatValue ("HIHAT", "ENVELOPE_MAX_RELEASE", settingsProperties.getEnvelopeMaxRelease ());
    setFloatValue ("HIHAT", "CHOKE_RELEASE", settingsProperties.getChokeRelease ());
    setIntValue ("HIHAT", "CLSD_RELEASE_MODE", settingsProperties.getClsdReleaseMode ());
    setFloatValue ("HIHAT", "CLSD_REL_OFST_SCALE", settingsProperties.getClsdRelOfstScale ());
    setFloatValue ("HIHAT", "CLSD_MAX_RELEASE", settingsProperties.getClsdMaxRelease ());
    setFloatValue ("HIHAT", "ACC_CL_REL_MOD", settingsProperties.getAccClRelMod ());
    setFloatValue ("HIHAT", "ACC_OP_REL_MOD", settingsProperties.getAccOpRelMod ());
    setFloatValue ("HIHAT", "ACC_CL_AMP_MOD", settingsProperties.getAccClAmpMod ());
    setFloatValue ("HIHAT", "ACC_OP_AMP_MOD", settingsProperties.getAccOpAmpMod ());

    // CV / control
    setIntValue ("HIHAT", "FX_CV_UNIPOLAR", settingsProperties.getFxCvUnipolar ());
    setIntValue ("HIHAT", "VELOCITY_UNIPOLAR", settingsProperties.getVelocityUnipolar ());
    setIntValue ("HIHAT", "CV_DISABLE_VELOCITY", settingsProperties.getCvDisableVelocity ());
    setIntValue ("HIHAT", "CV_DISABLE_FX", settingsProperties.getCvDisableFx ());
    setIntValue ("HIHAT", "GATE_MODE", settingsProperties.getGateMode ());
    setFloatValue ("HIHAT", "FEEL_ATTACK_MOD", settingsProperties.getFeelAttackMod ());
    setFloatValue ("HIHAT", "FEEL_RELEASE_MOD", settingsProperties.getFeelReleaseMod ());
    setFloatValue ("HIHAT", "FEEL_AMP_MOD", settingsProperties.getFeelAmpMod ());
    setIntValue ("HIHAT", "KNOB_POS_TAKEUP", settingsProperties.getKnobPosTakeup ());

    // Filters
    setIntValue ("HIHAT", "FLTR_HPF_MIN_FREQ", settingsProperties.getFltrHpfMinFreq ());
    setIntValue ("HIHAT", "FLTR_HPF_MAX_FREQ", settingsProperties.getFltrHpfMaxFreq ());
    setIntValue ("HIHAT", "FLTR_LPF_MIN_FREQ", settingsProperties.getFltrLpfMinFreq ());
    setIntValue ("HIHAT", "FLTR_LPF_MAX_FREQ", settingsProperties.getFltrLpfMaxFreq ());
    setFloatValue ("HIHAT", "FLTR_HPF_Q", settingsProperties.getFltrHpfQ ());
    setFloatValue ("HIHAT", "FLTR_LPF_Q", settingsProperties.getFltrLpfQ ());

    // DJ Filter
    setIntValue ("HIHAT", "FX_DJFILTER_HPF_MIN", settingsProperties.getFxDjfilterHpfMin ());
    setIntValue ("HIHAT", "FX_DJFILTER_HPF_MAX", settingsProperties.getFxDjfilterHpfMax ());
    setIntValue ("HIHAT", "FX_DJFILTER_LPF_MIN", settingsProperties.getFxDjfilterLpfMin ());
    setIntValue ("HIHAT", "FX_DJFILTER_LPF_MAX", settingsProperties.getFxDjfilterLpfMax ());
    setFloatValue ("HIHAT", "FX_DJFILTER_Q_MIN", settingsProperties.getFxDjfilterQMin ());
    setFloatValue ("HIHAT", "FX_DJFILTER_Q_MAX", settingsProperties.getFxDjfilterQMax ());
    setFloatValue ("HIHAT", "FX_DJFILTER_Q_GAIN_REDUCTION", settingsProperties.getFxDjfilterQGainReduction ());

    // Dub Echo
    setIntValue ("HIHAT", "FX_DUB_ECHO_TMIN", settingsProperties.getFxDubEchoTmin ());
    setIntValue ("HIHAT", "FX_DUB_ECHO_HPF", settingsProperties.getFxDubEchoHpf ());
    setIntValue ("HIHAT", "FX_DUB_ECHO_LPF", settingsProperties.getFxDubEchoLpf ());
    setFloatValue ("HIHAT", "FX_DUB_ECHO_MIX", settingsProperties.getFxDubEchoMix ());

    // Chorus
    setFloatValue ("HIHAT", "FX_CHORUS_CENTER", settingsProperties.getFxChorusCenter ());
    setFloatValue ("HIHAT", "FX_CHORUS_DEPTH", settingsProperties.getFxChorusDepth ());
    setFloatValue ("HIHAT", "FX_CHORUS_MIX", settingsProperties.getFxChorusMix ());
    setFloatValue ("HIHAT", "FX_CHORUS_SPREAD", settingsProperties.getFxChorusSpread ());
    setIntValue ("HIHAT", "FX_CHORUS_TAPS", settingsProperties.getFxChorusTaps ());
    setFloatValue ("HIHAT", "FX_CHORUS_LFO_B", settingsProperties.getFxChorusLfoB ());
    setIntValue ("HIHAT", "FX_CHORUS_LFO_T", settingsProperties.getFxChorusLfoT ());

    // Reverb
    setIntValue ("HIHAT", "FX_REVERB_LPF", settingsProperties.getFxReverbLpf ());
    setIntValue ("HIHAT", "FX_REVERB_HPF", settingsProperties.getFxReverbHpf ());

    // Glitch – probability
    setFloatValue ("HIHAT", "FX_GLITCH_PROBABILITY_MIN", settingsProperties.getFxGlitchProbabilityMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_PROBABILITY_MAX", settingsProperties.getFxGlitchProbabilityMax ());

    // Glitch – weights (low)
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_HOLD_LOW", settingsProperties.getFxGlitchWeightHoldLow ());
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_STUTTER_LOW", settingsProperties.getFxGlitchWeightStutterLow ());
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_CRUSH_LOW", settingsProperties.getFxGlitchWeightCrushLow ());
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_DROP_LOW", settingsProperties.getFxGlitchWeightDropLow ());

    // Glitch – weights (high)
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_HOLD_HIGH", settingsProperties.getFxGlitchWeightHoldHigh ());
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_STUTTER_HIGH", settingsProperties.getFxGlitchWeightStutterHigh ());
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_CRUSH_HIGH", settingsProperties.getFxGlitchWeightCrushHigh ());
    setFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_DROP_HIGH", settingsProperties.getFxGlitchWeightDropHigh ());

    // Glitch – drop
    setFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_LEVEL_MIN", settingsProperties.getFxGlitchDropKeepLevelMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_LEVEL_MAX", settingsProperties.getFxGlitchDropKeepLevelMax ());
    setFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_TIME_MIN", settingsProperties.getFxGlitchDropKeepTimeMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_TIME_MAX", settingsProperties.getFxGlitchDropKeepTimeMax ());

    // Glitch – crush
    setFloatValue ("HIHAT", "FX_GLITCH_CRUSH_TIME_MIN", settingsProperties.getFxGlitchCrushTimeMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_CRUSH_TIME_MAX", settingsProperties.getFxGlitchCrushTimeMax ());

    // Glitch – microloop
    setFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_SMPL_T_MIN", settingsProperties.getFxGlitchMicroloopSmplTMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_SMPL_T_MAX", settingsProperties.getFxGlitchMicroloopSmplTMax ());
    setFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_PLAY_T_MIN", settingsProperties.getFxGlitchMicroloopPlayTMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_PLAY_T_MAX", settingsProperties.getFxGlitchMicroloopPlayTMax ());

    // Glitch – stutter
    setFloatValue ("HIHAT", "FX_GLITCH_STUTTER_SMPL_T_MIN", settingsProperties.getFxGlitchStutterSmplTMin ());
    setFloatValue ("HIHAT", "FX_GLITCH_STUTTER_SMPL_T_MAX", settingsProperties.getFxGlitchStutterSmplTMax ());
    setIntValue ("HIHAT", "FX_GLITCH_STUTTER_NUM_MIN", settingsProperties.getFxGlitchStutterNumMin ());
    setIntValue ("HIHAT", "FX_GLITCH_STUTTER_NUM_MAX", settingsProperties.getFxGlitchStutterNumMax ());
    setIntValue ("HIHAT", "FX_GLITCH_STUTTER_WINDOW", settingsProperties.getFxGlitchStutterWindow ());

    patternListProperties.forEachPattern ([&data] (juce::ValueTree patternVT, int patternIndex)
    {
        PatternProperties patternProperties (patternVT, ValueTreeWrapper<PatternProperties>::WrapperType::client, ValueTreeWrapper<PatternProperties>::EnableCallbacks::no);
        data.setValue ("PATTERNS", patternProperties.getId (), patternProperties.getPattern ());
        return true;
    });
    effectListProperties.forEachEffect ([&data] (juce::ValueTree effectVT, int effectIndex)
    {
        EffectProperties effectProperties (effectVT, ValueTreeWrapper<EffectProperties>::WrapperType::client, ValueTreeWrapper<EffectProperties>::EnableCallbacks::no);
        data.setValue ("EFFECTS", effectProperties.getId (), effectProperties.getEffect ());
        return true;
    });
}

void FillInVtFromData (juce::ValueTree clutchVt, const HiHatIniData& data)
{
    SettingsProperties settingsProperties (clutchVt, ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::no);
    PatternListProperties patternListProperties (clutchVt, ValueTreeWrapper<PatternListProperties>::WrapperType::client, ValueTreeWrapper<PatternListProperties>::EnableCallbacks::no);
    EffectListProperties effectListProperties (clutchVt, ValueTreeWrapper<EffectListProperties>::WrapperType::client, ValueTreeWrapper<EffectListProperties>::EnableCallbacks::no);
    const auto getFloatValue = [&data](const juce::String& section, const juce::String& key, float defaultValue) -> float
    {
        const auto valueString = data.getValue (section, key);
        if (valueString.isNotEmpty ())
            return valueString.getFloatValue ();
        return defaultValue;
    };
    const auto getIntValue = [&data] (const juce::String& section, const juce::String& key, int defaultValue) -> int
    {
        const auto valueString = data.getValue (section, key);
        if (valueString.isNotEmpty ())
            return valueString.getIntValue ();
        return defaultValue;
    };
    // Core
    settingsProperties.setPitchLow (getFloatValue ("HIHAT", "PITCH_LOW", 0.125f), false);
    settingsProperties.setPitchHigh (getFloatValue ("HIHAT", "PITCH_HIGH", 2.5f), false);
    settingsProperties.setEnvelopeMaxRelease (getFloatValue ("HIHAT", "ENVELOPE_MAX_RELEASE", 4.0f), false);
    settingsProperties.setChokeRelease (getFloatValue ("HIHAT", "CHOKE_RELEASE", 0.08f), false);
    settingsProperties.setClsdReleaseMode (getIntValue ("HIHAT", "CLSD_RELEASE_MODE", 1), false);
    settingsProperties.setClsdRelOfstScale (getFloatValue ("HIHAT", "CLSD_REL_OFST_SCALE", 0.5f), false);
    settingsProperties.setClsdMaxRelease (getFloatValue ("HIHAT", "CLSD_MAX_RELEASE", 0.8f), false);
    settingsProperties.setAccClRelMod (getFloatValue ("HIHAT", "ACC_CL_REL_MOD", 1.18f), false);
    settingsProperties.setAccOpRelMod (getFloatValue ("HIHAT", "ACC_OP_REL_MOD", 1.25f), false);
    settingsProperties.setAccClAmpMod (getFloatValue ("HIHAT", "ACC_CL_AMP_MOD", 1.3f), false);
    settingsProperties.setAccOpAmpMod (getFloatValue ("HIHAT", "ACC_OP_AMP_MOD", 1.25f), false);

    // CV / control
    settingsProperties.setFxCvUnipolar (getIntValue ("HIHAT", "FX_CV_UNIPOLAR", 1), false);
    settingsProperties.setVelocityUnipolar (getIntValue ("HIHAT", "VELOCITY_UNIPOLAR", 0), false);
    settingsProperties.setCvDisableVelocity (getIntValue ("HIHAT", "CV_DISABLE_VELOCITY", 0), false);
    settingsProperties.setCvDisableFx (getIntValue ("HIHAT", "CV_DISABLE_FX", 0), false);
    settingsProperties.setGateMode (getIntValue ("HIHAT", "GATE_MODE", 0), false);
    settingsProperties.setFeelAttackMod (getFloatValue ("HIHAT", "FEEL_ATTACK_MOD", 1.0f), false);
    settingsProperties.setFeelReleaseMod (getFloatValue ("HIHAT", "FEEL_RELEASE_MOD", 1.0f), false);
    settingsProperties.setFeelAmpMod (getFloatValue ("HIHAT", "FEEL_AMP_MOD", 1.0f), false);
    settingsProperties.setKnobPosTakeup (getIntValue ("HIHAT", "KNOB_POS_TAKEUP", 1), false);

    // Filters
    settingsProperties.setFltrHpfMinFreq (getIntValue ("HIHAT", "FLTR_HPF_MIN_FREQ", 100), false);
    settingsProperties.setFltrHpfMaxFreq (getIntValue ("HIHAT", "FLTR_HPF_MAX_FREQ", 14000), false);
    settingsProperties.setFltrLpfMinFreq (getIntValue ("HIHAT", "FLTR_LPF_MIN_FREQ", 200), false);
    settingsProperties.setFltrLpfMaxFreq (getIntValue ("HIHAT", "FLTR_LPF_MAX_FREQ", 20000), false);
    settingsProperties.setFltrHpfQ (getFloatValue ("HIHAT", "FLTR_HPF_Q", 1.0f), false);
    settingsProperties.setFltrLpfQ (getFloatValue ("HIHAT", "FLTR_LPF_Q", 0.707f), false);

    // DJ Filter
    settingsProperties.setFxDjfilterHpfMin (getIntValue ("HIHAT", "FX_DJFILTER_HPF_MIN", 100), false);
    settingsProperties.setFxDjfilterHpfMax (getIntValue ("HIHAT", "FX_DJFILTER_HPF_MAX", 14000), false);
    settingsProperties.setFxDjfilterLpfMin (getIntValue ("HIHAT", "FX_DJFILTER_LPF_MIN", 200), false);
    settingsProperties.setFxDjfilterLpfMax (getIntValue ("HIHAT", "FX_DJFILTER_LPF_MAX", 20000), false);
    settingsProperties.setFxDjfilterQMin (getFloatValue ("HIHAT", "FX_DJFILTER_Q_MIN", 0.5f), false);
    settingsProperties.setFxDjfilterQMax (getFloatValue ("HIHAT", "FX_DJFILTER_Q_MAX", 4.0f), false);
    settingsProperties.setFxDjfilterQGainReduction (getFloatValue ("HIHAT", "FX_DJFILTER_Q_GAIN_REDUCTION", 0.12f), false);

    // Dub Echo
    settingsProperties.setFxDubEchoTmin (getIntValue ("HIHAT", "FX_DUB_ECHO_TMIN", 30), false);
    settingsProperties.setFxDubEchoHpf (getIntValue ("HIHAT", "FX_DUB_ECHO_HPF", 400), false);
    settingsProperties.setFxDubEchoLpf (getIntValue ("HIHAT", "FX_DUB_ECHO_LPF", 8400), false);
    settingsProperties.setFxDubEchoMix (getFloatValue ("HIHAT", "FX_DUB_ECHO_MIX", 0.38f), false);

    // Chorus
    settingsProperties.setFxChorusCenter (getFloatValue ("HIHAT", "FX_CHORUS_CENTER", 12.0f), false);
    settingsProperties.setFxChorusDepth (getFloatValue ("HIHAT", "FX_CHORUS_DEPTH", 5.0f), false);
    settingsProperties.setFxChorusMix (getFloatValue ("HIHAT", "FX_CHORUS_MIX", 1.0f), false);
    settingsProperties.setFxChorusSpread (getFloatValue ("HIHAT", "FX_CHORUS_SPREAD", 0.01f), false);
    settingsProperties.setFxChorusTaps (getIntValue ("HIHAT", "FX_CHORUS_TAPS", 4), false);
    settingsProperties.setFxChorusLfoB (getFloatValue ("HIHAT", "FX_CHORUS_LFO_B", 0.002f), false);
    settingsProperties.setFxChorusLfoT (getIntValue ("HIHAT", "FX_CHORUS_LFO_T", 3), false);

    // Reverb
    settingsProperties.setFxReverbLpf (getIntValue ("HIHAT", "FX_REVERB_LPF", 9000), false);
    settingsProperties.setFxReverbHpf (getIntValue ("HIHAT", "FX_REVERB_HPF", 700), false);

    // Glitch – probability
    settingsProperties.setFxGlitchProbabilityMin (getFloatValue ("HIHAT", "FX_GLITCH_PROBABILITY_MIN", 0.00005f), false);
    settingsProperties.setFxGlitchProbabilityMax (getFloatValue ("HIHAT", "FX_GLITCH_PROBABILITY_MAX", 0.003f), false);

    // Glitch – weights (low)
    settingsProperties.setFxGlitchWeightHoldLow (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_HOLD_LOW", 0.15f), false);
    settingsProperties.setFxGlitchWeightStutterLow (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_STUTTER_LOW", 0.05f), false);
    settingsProperties.setFxGlitchWeightCrushLow (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_CRUSH_LOW", 0.30f), false);
    settingsProperties.setFxGlitchWeightDropLow (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_DROP_LOW", 0.02f), false);

    // Glitch – weights (high)
    settingsProperties.setFxGlitchWeightHoldHigh (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_HOLD_HIGH", 0.30f), false);
    settingsProperties.setFxGlitchWeightStutterHigh (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_STUTTER_HIGH", 0.20f), false);
    settingsProperties.setFxGlitchWeightCrushHigh (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_CRUSH_HIGH", 0.20f), false);
    settingsProperties.setFxGlitchWeightDropHigh (getFloatValue ("HIHAT", "FX_GLITCH_WEIGHT_DROP_HIGH", 0.07f), false);

    // Glitch – drop
    settingsProperties.setFxGlitchDropKeepLevelMin (getFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_LEVEL_MIN", 0.0f), false);
    settingsProperties.setFxGlitchDropKeepLevelMax (getFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_LEVEL_MAX", 0.75f), false);
    settingsProperties.setFxGlitchDropKeepTimeMin (getFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_TIME_MIN", 4.0f), false);
    settingsProperties.setFxGlitchDropKeepTimeMax (getFloatValue ("HIHAT", "FX_GLITCH_DROP_KEEP_TIME_MAX", 40.0f), false);

    // Glitch – crush
    settingsProperties.setFxGlitchCrushTimeMin (getFloatValue ("HIHAT", "FX_GLITCH_CRUSH_TIME_MIN", 10.0f), false);
    settingsProperties.setFxGlitchCrushTimeMax (getFloatValue ("HIHAT", "FX_GLITCH_CRUSH_TIME_MAX", 50.0f), false);

    // Glitch – microloop
    settingsProperties.setFxGlitchMicroloopSmplTMin (getFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_SMPL_T_MIN", 0.2f), false);
    settingsProperties.setFxGlitchMicroloopSmplTMax (getFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_SMPL_T_MAX", 3.0f), false);
    settingsProperties.setFxGlitchMicroloopPlayTMin (getFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_PLAY_T_MIN", 5.0f), false);
    settingsProperties.setFxGlitchMicroloopPlayTMax (getFloatValue ("HIHAT", "FX_GLITCH_MICROLOOP_PLAY_T_MAX", 15.0f), false);

    // Glitch – stutter
    settingsProperties.setFxGlitchStutterSmplTMin (getFloatValue ("HIHAT", "FX_GLITCH_STUTTER_SMPL_T_MIN", 3.0f), false);
    settingsProperties.setFxGlitchStutterSmplTMax (getFloatValue ("HIHAT", "FX_GLITCH_STUTTER_SMPL_T_MAX", 10.0f), false);
    settingsProperties.setFxGlitchStutterNumMin (getIntValue ("HIHAT", "FX_GLITCH_STUTTER_NUM_MIN", 2), false);
    settingsProperties.setFxGlitchStutterNumMax (getIntValue ("HIHAT", "FX_GLITCH_STUTTER_NUM_MAX", 5), false);
    settingsProperties.setFxGlitchStutterWindow (getIntValue ("HIHAT", "FX_GLITCH_STUTTER_WINDOW", 20), false);

    patternListProperties.forEachPattern ([&data] (juce::ValueTree patternVT, int patternIndex)
    {
        PatternProperties patternProperties (patternVT, ValueTreeWrapper<PatternProperties>::WrapperType::client, ValueTreeWrapper<PatternProperties>::EnableCallbacks::no);
        patternProperties.setPattern (data.getValue ("PATTERNS", patternProperties.getId ()), false);
        return true;
    });
    effectListProperties.forEachEffect ([&data] (juce::ValueTree effectVT, int effectIndex)
    {
        EffectProperties effectProperties (effectVT, ValueTreeWrapper<EffectProperties>::WrapperType::client, ValueTreeWrapper<EffectProperties>::EnableCallbacks::no);
        effectProperties.setEffect (data.getValue ("EFFECTS", effectProperties.getId ()), false);
        return true;
    });
}

class ClutchEditApplication : public juce::JUCEApplication, public juce::Timer
{
public:
    ClutchEditApplication () {}
    const juce::String getApplicationName () override { return ProjectInfo::projectName; }
    const juce::String getApplicationVersion () override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed () override { return true; }

    void initialise ([[maybe_unused]] const juce::String& commandLine) override
    {
        initAppDirectory ();
        initLogger ();
        initCrashHandler ();
        initPropertyRoots ();
        initSystemServices ();
        initClutch();
        initAudio ();
        initUi ();

        //ValueTreeHelpers::dumpValueTreeContent (runtimeRootProperties.getValueTree (), false, [this] (juce::String line) { DebugLog ("", line); });

        // async quit timer
        startTimer (125);
    }

    void shutdown () override
    {
        audioPlayer.shutdownAudio ();
        persitentPropertiesFile.save ();
        mainWindow = nullptr; // (deletes our window)
        juce::Logger::setCurrentLogger (nullptr);
    }

    void anotherInstanceStarted ([[maybe_unused]] const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    void suspended () override
    {
        runtimeRootProperties.triggerAppSuspended (false);
    }

    void resumed () override
    {
        runtimeRootProperties.triggerAppResumed (false);
    }

    void systemRequestedQuit () override
    {
        // reset preferred quit state
        runtimeRootProperties.setPreferredQuitState (RuntimeRootProperties::QuitState::now, false);
        // listeners for 'onSystemRequestedQuit' can do runtimeRootProperties.setPreferredQuitState (RuntimeRootProperties::QuitState::idle);
        // if they need to do something, which also makes them responsible for calling runtimeRootProperties.setQuitState (RuntimeRootProperties::QuitState::now); when they are done...
        runtimeRootProperties.triggerSystemRequestedQuit (false);
        localQuitState.store (runtimeRootProperties.getPreferredQuitState ());
    }

    void timerCallback () override
    {
        if (localQuitState.load () == RuntimeRootProperties::QuitState::now)
            quit ();
    }

    void initClutch ()
    {
        SettingsProperties settingsProperties;
        PatternListProperties patternListProperties;
        EffectListProperties effectListProperties;
        ClutchProperties clutchProperties (runtimeRootProperties.getValueTree (), ClutchProperties::WrapperType::owner, ClutchProperties::EnableCallbacks::no);
        clutchProperties.getValueTree ().addChild (settingsProperties.getValueTree (), -1, nullptr);
        clutchProperties.getValueTree ().addChild (patternListProperties.getValueTree (), -1, nullptr);
        clutchProperties.getValueTree ().addChild (effectListProperties.getValueTree (), -1, nullptr);

        auto hiHatIniFile { juce::File (appProperties.getRecentlyUsedFile (0))};
        if (hiHatIniFile.existsAsFile ())
        {
            gHiHatIniData.readFromFile (hiHatIniFile);
            FillInVtFromData (clutchProperties.getValueTree (), gHiHatIniData);
        }
    }

    void initUi ()
    {
        guiControlProperties.wrap (runtimeRootProperties.getValueTree (), GuiControlProperties::WrapperType::owner, GuiControlProperties::EnableCallbacks::no);
        guiProperties.wrap (persistentRootProperties.getValueTree (), GuiProperties::WrapperType::owner, GuiProperties::EnableCallbacks::no);
        mainWindow.reset (new MainWindow (getApplicationName () + " - " + getVersionDisplayString (), rootProperties.getValueTree ()));
    }

    void initPropertyRoots ()
    {
        persistentRootProperties.wrap (rootProperties.getValueTree (), PersistentRootProperties::WrapperType::owner, PersistentRootProperties::EnableCallbacks::no);
        // connect the Properties file and the AppProperties ValueTree with the propertiesFile (ValueTreeFile with auto-save)
        persitentPropertiesFile.init (persistentRootProperties.getValueTree (), appDirectory.getChildFile ("app" + PropertiesFileExtension), true);
        appProperties.wrap (persistentRootProperties.getValueTree (), AppProperties::WrapperType::owner, AppProperties::EnableCallbacks::yes);
        appProperties.setMaxMruEntries (1);
        runtimeRootProperties.wrap (rootProperties.getValueTree (), RuntimeRootProperties::WrapperType::owner, RuntimeRootProperties::EnableCallbacks::yes);
        runtimeRootProperties.setAppVersion (getApplicationVersion (), false);
        runtimeRootProperties.setAppDataPath (appDirectory.getFullPathName (), false);
        runtimeRootProperties.onQuitStateChanged = [this] (RuntimeRootProperties::QuitState quitState) { localQuitState.store (quitState); };

        if (appProperties.getMostRecentFolder ().isEmpty ())
        {
            appProperties.setMostRecentFolder (appDirectory.getFullPathName ());
            appProperties.addRecentlyUsedFile (juce::File (appDirectory.getFullPathName ()).getChildFile ("HIHAT.INI").getFullPathName ());
        }
    }

    void initAudio ()
    {
        audioPlayer.init (rootProperties.getValueTree ());
    }

    void initSystemServices ()
    {
        // connect services to the SystemServices VTW
        SystemServices systemServices (runtimeRootProperties.getValueTree (), SystemServices::WrapperType::owner, SystemServices::EnableCallbacks::no);

        //audioManager.init (rootProperties.getValueTree ());
        //systemServices.setAudioManager (&audioManager);

        //systemServices.setEditManager (&editManager);
    }

    void initAppDirectory ()
    {
        // locate the appProperties file in the User Application Data Directory

        const juce::String propertiesFilePath { juce::File::getSpecialLocation (juce::File::userApplicationDataDirectory).getFullPathName () };
        appDirectory = juce::File (propertiesFilePath).getChildFile (ProjectInfo::companyName).getChildFile (getApplicationName ());
        if (! appDirectory.exists ())
        {
            const auto result { appDirectory.createDirectory () };
            if (! result.wasOk ())
            {
                juce::AlertWindow::showMessageBoxAsync (juce::AlertWindow::WarningIcon, "Application Startup Error",
                    "Unable to create " + getApplicationName () + " preferences directory, '" + appDirectory.getFullPathName () + "'", {}, nullptr,
                    juce::ModalCallbackFunction::create ([this] (int) { quit (); }));
                return;
            }
        }
    }

    juce::String getVersionDisplayString ()
    {
        return "v" + getApplicationVersion () + juce::String (kVersionDecorator);
    }

    void initLogger ()
    {
        auto getSessionTextForLogFile = [this] ()
        {
            auto resultOrNa = [] (juce::String result)
            {
                if (result.isEmpty ())
                    return juce::String ("n/a");
                else
                    return result;
            };
            const auto nl { juce::String ("\n") };
            auto welcomeText { juce::String (getApplicationName () + " - v" + getVersionDisplayString () + " Log File" + nl) };
            welcomeText += " OS: " + resultOrNa (juce::SystemStats::getOperatingSystemName ()) + nl;
            welcomeText += " Device Description: " + resultOrNa (juce::SystemStats::getDeviceDescription ()) + nl;
            welcomeText += " Device Manufacturer: " + resultOrNa (juce::SystemStats::getDeviceManufacturer ()) + nl;
            welcomeText += " CPU Vendor: " + resultOrNa (juce::SystemStats::getCpuVendor ()) + nl;
            welcomeText += " CPU Model: " + resultOrNa (juce::SystemStats::getCpuModel ()) + nl;
            welcomeText += " CPU Speed: " + resultOrNa (juce::String (juce::SystemStats::getCpuSpeedInMegahertz ())) + nl;
            welcomeText += " Logical/Physicals CPUs: " + resultOrNa (juce::String (juce::SystemStats::getNumCpus ())) + "/" + resultOrNa (juce::String (juce::SystemStats::getNumPhysicalCpus ())) + nl;
            welcomeText += " Memory: " + resultOrNa (juce::String (juce::SystemStats::getMemorySizeInMegabytes ())) + "mb" + nl;
            return welcomeText;
        };
        fileLogger = std::make_unique<juce::FileLogger> (appDirectory.getChildFile ("DebugLog"), getSessionTextForLogFile ());
        juce::Logger::setCurrentLogger (fileLogger.get ());
    }

    void initCrashHandler ()
    {
        juce::SystemStats::setApplicationCrashHandler (crashHandler);
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainComponent class.
    */
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name, juce::ValueTree rootPropertiesVT)
            : DocumentWindow (name,
                              juce::Desktop::getInstance ().getDefaultLookAndFeel ().findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent (rootPropertiesVT), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
           #endif

            PersistentRootProperties prp (rootPropertiesVT, PersistentRootProperties::WrapperType::client, PersistentRootProperties::EnableCallbacks::no);
            guiProperties.wrap (prp.getValueTree (), GuiProperties::WrapperType::client, GuiProperties::EnableCallbacks::no);
            auto [width, height] { guiProperties.getSize () };
            auto [x, y] { guiProperties.getPosition () };
            if (x == -1 || y == -1)
                centreWithSize (width, height);
            else
                setBounds (x, y, width, height);

            setVisible (true);

#if ENABLE_MELATONIN_INSPECTOR
            inspector.setVisible (true);
#endif
        }

#if (! JUCE_IOS) && (! JUCE_ANDROID)
        void moved () override
        {
            guiProperties.setPosition (getBounds ().getX (), getBounds ().getY (), false);
            DocumentWindow::moved ();
        }

        void resized () override
        {
            guiProperties.setSize (getBounds ().getWidth (), getBounds ().getHeight (), false);
            DocumentWindow::resized ();
        }
#endif // ! JUCE_IOS && ! JUCE_ANDROID

        void closeButtonPressed () override
        {
            JUCEApplication::getInstance ()->systemRequestedQuit ();
        }

    private:
        GuiProperties guiProperties;
#if ENABLE_MELATONIN_INSPECTOR
        melatonin::Inspector inspector { *this, false };
#endif
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    juce::File appDirectory;
    RootProperties rootProperties;
    ValueTreeFile persitentPropertiesFile;
    PersistentRootProperties persistentRootProperties;
    AppProperties appProperties;
    GuiControlProperties guiControlProperties;
    GuiProperties guiProperties;
    RuntimeRootProperties runtimeRootProperties;
    //SampleManager sampleManager;
    //Assimil8orValidator assimil8orValidator;
    //PresetProperties presetProperties;
    //DirectoryValueTree directoryValueTree;
    //DirectoryDataProperties directoryDataProperties;
    std::unique_ptr<juce::FileLogger> fileLogger;
    std::atomic<RuntimeRootProperties::QuitState> localQuitState { RuntimeRootProperties::QuitState::idle };
    std::unique_ptr<MainWindow> mainWindow;
    AudioPlayer audioPlayer;
    //AudioManager audioManager;
    //EditManager editManager;

    ValueTreeMonitor audioConfigPropertiesMonitor;
    ValueTreeMonitor directoryDataMonitor;
    ValueTreeMonitor presetPropertiesMonitor;
};

// This macro generates the main () routine that launches the app.
START_JUCE_APPLICATION (ClutchEditApplication)
