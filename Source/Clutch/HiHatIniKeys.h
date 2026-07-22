#pragma once

// Section and key names for HIHAT.INI

// Sections
constexpr auto kHiHatSection { "HIHAT" };
constexpr auto kPatternsSection { "PATTERNS" };
constexpr auto kEffectsSection { "EFFECTS" };

// [HIHAT] - Pitch
constexpr auto kPitchLowKey { "PITCH_LOW" };
constexpr auto kPitchHighKey { "PITCH_HIGH" };

// [HIHAT] - Envelope
constexpr auto kEnvelopeMaxReleaseKey { "ENVELOPE_MAX_RELEASE" };
constexpr auto kChokeReleaseKey { "CHOKE_RELEASE" };
constexpr auto kReleaseModeKey { "RELEASE_MODE" };
constexpr auto kClsdReleaseModeKey { "CLSD_RELEASE_MODE" }; // legacy name for RELEASE_MODE, still accepted
constexpr auto kClsdRelOfstScaleKey { "CLSD_REL_OFST_SCALE" };
constexpr auto kClsdMaxReleaseKey { "CLSD_MAX_RELEASE" };
constexpr auto kAccClRelModKey { "ACC_CL_REL_MOD" };
constexpr auto kAccOpRelModKey { "ACC_OP_REL_MOD" };
constexpr auto kAccClAmpModKey { "ACC_CL_AMP_MOD" };
constexpr auto kAccOpAmpModKey { "ACC_OP_AMP_MOD" };

// [HIHAT] - CV / control
constexpr auto kFxCvUnipolarKey { "FX_CV_UNIPOLAR" };
constexpr auto kVelocityUnipolarKey { "VELOCITY_UNIPOLAR" };
constexpr auto kCvDisableVelocityKey { "CV_DISABLE_VELOCITY" };
constexpr auto kCvDisableFxKey { "CV_DISABLE_FX" };
constexpr auto kGateModeKey { "GATE_MODE" };
constexpr auto kFeelAttackModKey { "FEEL_ATTACK_MOD" };
constexpr auto kFeelReleaseModKey { "FEEL_RELEASE_MOD" };
constexpr auto kFeelAmpModKey { "FEEL_AMP_MOD" };
constexpr auto kKnobPosTakeupKey { "KNOB_POS_TAKEUP" };

// [HIHAT] - Filters
constexpr auto kFltrHpfMinFreqKey { "FLTR_HPF_MIN_FREQ" };
constexpr auto kFltrHpfMaxFreqKey { "FLTR_HPF_MAX_FREQ" };
constexpr auto kFltrLpfMinFreqKey { "FLTR_LPF_MIN_FREQ" };
constexpr auto kFltrLpfMaxFreqKey { "FLTR_LPF_MAX_FREQ" };
constexpr auto kFltrHpfQKey { "FLTR_HPF_Q" };
constexpr auto kFltrLpfQKey { "FLTR_LPF_Q" };

// [HIHAT] - DJ Filter
constexpr auto kFxDjfilterHpfMinKey { "FX_DJFILTER_HPF_MIN" };
constexpr auto kFxDjfilterHpfMaxKey { "FX_DJFILTER_HPF_MAX" };
constexpr auto kFxDjfilterLpfMinKey { "FX_DJFILTER_LPF_MIN" };
constexpr auto kFxDjfilterLpfMaxKey { "FX_DJFILTER_LPF_MAX" };
constexpr auto kFxDjfilterQMinKey { "FX_DJFILTER_Q_MIN" };
constexpr auto kFxDjfilterQMaxKey { "FX_DJFILTER_Q_MAX" };
constexpr auto kFxDjfilterQGainReductionKey { "FX_DJFILTER_Q_GAIN_REDUCTION" };

// [HIHAT] - Dub Echo
constexpr auto kFxDubEchoTminKey { "FX_DUB_ECHO_TMIN" };
constexpr auto kFxDubEchoHpfKey { "FX_DUB_ECHO_HPF" };
constexpr auto kFxDubEchoLpfKey { "FX_DUB_ECHO_LPF" };
constexpr auto kFxDubEchoMixKey { "FX_DUB_ECHO_MIX" };

// [HIHAT] - Chorus
constexpr auto kFxChorusCenterKey { "FX_CHORUS_CENTER" };
constexpr auto kFxChorusDepthKey { "FX_CHORUS_DEPTH" };
constexpr auto kFxChorusMixKey { "FX_CHORUS_MIX" };
constexpr auto kFxChorusSpreadKey { "FX_CHORUS_SPREAD" };
constexpr auto kFxChorusTapsKey { "FX_CHORUS_TAPS" };
constexpr auto kFxChorusLfoBKey { "FX_CHORUS_LFO_B" };
constexpr auto kFxChorusLfoTKey { "FX_CHORUS_LFO_T" };
constexpr auto kFxChorusTypeKey { "FX_CHORUS_TYPE" };
constexpr auto kFxChorusStaggerKey { "FX_CHORUS_STAGGER" };

// [HIHAT] - Reverb
constexpr auto kFxReverbLpfKey { "FX_REVERB_LPF" };
constexpr auto kFxReverbHpfKey { "FX_REVERB_HPF" };
constexpr auto kFxReverbTypeKey { "FX_REVERB_TYPE" };
constexpr auto kFxReverbSizeMinKey { "FX_REVERB_SIZE_MIN" };
constexpr auto kFxReverbSizeMaxKey { "FX_REVERB_SIZE_MAX" };
constexpr auto kFxReverbPredelayKey { "FX_REVERB_PREDELAY" };
constexpr auto kFxReverbModDepthKey { "FX_REVERB_MOD_DEPTH" };
constexpr auto kFxReverbModRateKey { "FX_REVERB_MOD_RATE" };
constexpr auto kFxReverbDiffusionKey { "FX_REVERB_DIFFUSION" };
constexpr auto kFxReverbMixKey { "FX_REVERB_MIX" };

// [HIHAT] - Glitch
constexpr auto kFxGlitchProbabilityMinKey { "FX_GLITCH_PROBABILITY_MIN" };
constexpr auto kFxGlitchProbabilityMaxKey { "FX_GLITCH_PROBABILITY_MAX" };
constexpr auto kFxGlitchWeightHoldLowKey { "FX_GLITCH_WEIGHT_HOLD_LOW" };
constexpr auto kFxGlitchWeightStutterLowKey { "FX_GLITCH_WEIGHT_STUTTER_LOW" };
constexpr auto kFxGlitchWeightCrushLowKey { "FX_GLITCH_WEIGHT_CRUSH_LOW" };
constexpr auto kFxGlitchWeightDropLowKey { "FX_GLITCH_WEIGHT_DROP_LOW" };
constexpr auto kFxGlitchWeightHoldHighKey { "FX_GLITCH_WEIGHT_HOLD_HIGH" };
constexpr auto kFxGlitchWeightStutterHighKey { "FX_GLITCH_WEIGHT_STUTTER_HIGH" };
constexpr auto kFxGlitchWeightCrushHighKey { "FX_GLITCH_WEIGHT_CRUSH_HIGH" };
constexpr auto kFxGlitchWeightDropHighKey { "FX_GLITCH_WEIGHT_DROP_HIGH" };
constexpr auto kFxGlitchDropKeepLevelMinKey { "FX_GLITCH_DROP_KEEP_LEVEL_MIN" };
constexpr auto kFxGlitchDropKeepLevelMaxKey { "FX_GLITCH_DROP_KEEP_LEVEL_MAX" };
constexpr auto kFxGlitchDropKeepTimeMinKey { "FX_GLITCH_DROP_KEEP_TIME_MIN" };
constexpr auto kFxGlitchDropKeepTimeMaxKey { "FX_GLITCH_DROP_KEEP_TIME_MAX" };
constexpr auto kFxGlitchCrushTimeMinKey { "FX_GLITCH_CRUSH_TIME_MIN" };
constexpr auto kFxGlitchCrushTimeMaxKey { "FX_GLITCH_CRUSH_TIME_MAX" };
constexpr auto kFxGlitchMicroloopSmplTMinKey { "FX_GLITCH_MICROLOOP_SMPL_T_MIN" };
constexpr auto kFxGlitchMicroloopSmplTMaxKey { "FX_GLITCH_MICROLOOP_SMPL_T_MAX" };
constexpr auto kFxGlitchMicroloopPlayTMinKey { "FX_GLITCH_MICROLOOP_PLAY_T_MIN" };
constexpr auto kFxGlitchMicroloopPlayTMaxKey { "FX_GLITCH_MICROLOOP_PLAY_T_MAX" };
constexpr auto kFxGlitchStutterSmplTMinKey { "FX_GLITCH_STUTTER_SMPL_T_MIN" };
constexpr auto kFxGlitchStutterSmplTMaxKey { "FX_GLITCH_STUTTER_SMPL_T_MAX" };
constexpr auto kFxGlitchStutterNumMinKey { "FX_GLITCH_STUTTER_NUM_MIN" };
constexpr auto kFxGlitchStutterNumMaxKey { "FX_GLITCH_STUTTER_NUM_MAX" };
constexpr auto kFxGlitchStutterWindowKey { "FX_GLITCH_STUTTER_WINDOW" };

// [PATTERNS]
constexpr auto kPtnWhiteKey { "PTN_WHITE" };
constexpr auto kPtnRedKey { "PTN_RED" };
constexpr auto kPtnOrangeKey { "PTN_ORANGE" };
constexpr auto kPtnYellowKey { "PTN_YELLOW" };
constexpr auto kPtnGreenKey { "PTN_GREEN" };
constexpr auto kPtnBlueKey { "PTN_BLUE" };
constexpr auto kPtnCyanKey { "PTN_CYAN" };
constexpr auto kPtnVioletKey { "PTN_VIOLET" };

// [EFFECTS]
constexpr auto kFxWhiteKey { "FX_WHITE" };
constexpr auto kFxRedKey { "FX_RED" };
constexpr auto kFxOrangeKey { "FX_ORANGE" };
constexpr auto kFxYellowKey { "FX_YELLOW" };
constexpr auto kFxGreenKey { "FX_GREEN" };
constexpr auto kFxBlueKey { "FX_BLUE" };
constexpr auto kFxCyanKey { "FX_CYAN" };
constexpr auto kFxVioletKey { "FX_VIOLET" };
