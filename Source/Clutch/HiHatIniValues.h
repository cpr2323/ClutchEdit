#pragma once

// Min/max ranges and default values for HIHAT.INI parameters, shared between the
// settings editor (which uses the ranges for its sliders) and the INI data parser
// (which uses the defaults when a key is absent). Not every parameter has a range.

// Pitch
constexpr float kPitchLowMin              { 0.001f };
constexpr float kPitchLowMax              { 0.5f };
constexpr float kPitchLowDefault          { 0.125f };
constexpr float kPitchHighMin             { 1.5f };
constexpr float kPitchHighMax             { 3.7f };
constexpr float kPitchHighDefault         { 2.5f };

// Envelope
constexpr float kEnvelopeMaxReleaseMin    { 0.6f };
constexpr float kEnvelopeMaxReleaseMax    { 20.0f };
constexpr float kEnvelopeMaxReleaseDefault { 4.0f };
constexpr float kChokeReleaseMin          { 0.002f };
constexpr float kChokeReleaseMax          { 0.400f };
constexpr float kChokeReleaseDefault      { 0.080f };

// Closed Hit Release
constexpr float kClsdRelOfstScaleMin      { 0.1f };
constexpr float kClsdRelOfstScaleMax      { 0.9f };
constexpr float kClsdRelOfstScaleDefault  { 0.5f };
constexpr float kClsdMaxReleaseMin        { 0.3f };
constexpr float kClsdMaxReleaseMax        { 2.0f };
constexpr float kClsdMaxReleaseDefault    { 0.8f };
constexpr int   kReleaseModeDefault       { 1 };

// Accent
constexpr float kAccClAmpModMin           { 0.5f };
constexpr float kAccClAmpModMax           { 3.0f };
constexpr float kAccClAmpModDefault       { 1.3f };
constexpr float kAccClRelModMin           { 0.5f };
constexpr float kAccClRelModMax           { 3.0f };
constexpr float kAccClRelModDefault       { 1.18f };
constexpr float kAccOpAmpModMin           { 0.5f };
constexpr float kAccOpAmpModMax           { 3.0f };
constexpr float kAccOpAmpModDefault       { 1.25f };
constexpr float kAccOpRelModMin           { 0.5f };
constexpr float kAccOpRelModMax           { 3.0f };
constexpr float kAccOpRelModDefault       { 1.25f };

// CV
constexpr int   kFxCvUnipolarDefault      { 1 };
constexpr int   kVelocityUnipolarDefault  { 0 };
constexpr int   kCvDisableVelocityDefault { 0 };
constexpr int   kCvDisableFxDefault       { 0 };

// Gate
constexpr int   kGateModeDefault          { 0 };

// Feel
constexpr float kFeelAttackModMin         { 0.0f };
constexpr float kFeelAttackModMax         { 5.0f };
constexpr float kFeelAttackModDefault     { 1.0f };
constexpr float kFeelReleaseModMin        { 0.0f };
constexpr float kFeelReleaseModMax        { 5.0f };
constexpr float kFeelReleaseModDefault    { 1.0f };
constexpr float kFeelAmpModMin            { 0.0f };
constexpr float kFeelAmpModMax            { 2.0f };
constexpr float kFeelAmpModDefault        { 1.0f };

// Utility
constexpr int   kKnobPosTakeupDefault     { 1 };

// Filter HPF
constexpr int   kFltrHpfMinFreqMin        { 20 };
constexpr int   kFltrHpfMinFreqMax        { 1000 };
constexpr int   kFltrHpfMinFreqDefault    { 100 };
constexpr int   kFltrHpfMaxFreqMin        { 8000 };
constexpr int   kFltrHpfMaxFreqMax        { 20000 };
constexpr int   kFltrHpfMaxFreqDefault    { 14000 };
constexpr float kFltrHpfQMin              { 0.25f };
constexpr float kFltrHpfQMax              { 4.0f };
constexpr float kFltrHpfQDefault          { 1.0f };

// Filter LPF
constexpr int   kFltrLpfMinFreqMin        { 20 };
constexpr int   kFltrLpfMinFreqMax        { 1000 };
constexpr int   kFltrLpfMinFreqDefault    { 200 };
constexpr int   kFltrLpfMaxFreqMin        { 12000 };
constexpr int   kFltrLpfMaxFreqMax        { 20000 };
constexpr int   kFltrLpfMaxFreqDefault    { 20000 };
constexpr float kFltrLpfQMin              { 0.25f };
constexpr float kFltrLpfQMax              { 4.0f };
constexpr float kFltrLpfQDefault          { 0.707f };

// DJ Filter
constexpr int   kFxDjfilterHpfMinMin      { 20 };
constexpr int   kFxDjfilterHpfMinMax      { 2000 };
constexpr int   kFxDjfilterHpfMinDefault  { 100 };
constexpr int   kFxDjfilterHpfMaxMin      { 8000 };
constexpr int   kFxDjfilterHpfMaxMax      { 20000 };
constexpr int   kFxDjfilterHpfMaxDefault  { 14000 };
constexpr int   kFxDjfilterLpfMinMin      { 20 };
constexpr int   kFxDjfilterLpfMinMax      { 2000 };
constexpr int   kFxDjfilterLpfMinDefault  { 200 };
constexpr int   kFxDjfilterLpfMaxMin      { 12000 };
constexpr int   kFxDjfilterLpfMaxMax      { 20000 };
constexpr int   kFxDjfilterLpfMaxDefault  { 20000 };
constexpr float kFxDjfilterQMinMin        { 0.25f };
constexpr float kFxDjfilterQMinMax        { 12.0f };
constexpr float kFxDjfilterQMinDefault    { 0.5f };
constexpr float kFxDjfilterQMaxMin        { 0.25f };
constexpr float kFxDjfilterQMaxMax        { 12.0f };
constexpr float kFxDjfilterQMaxDefault    { 4.0f };
constexpr float kFxDjfilterQGainReductionMin     { 0.0f };
constexpr float kFxDjfilterQGainReductionMax     { 0.5f };
constexpr float kFxDjfilterQGainReductionDefault { 0.12f };

// Dub Echo
constexpr int   kFxDubEchoTminMin         { 5 };
constexpr int   kFxDubEchoTminMax         { 80 };
constexpr int   kFxDubEchoTminDefault     { 30 };
constexpr int   kFxDubEchoHpfMin          { 20 };
constexpr int   kFxDubEchoHpfMax          { 2000 };
constexpr int   kFxDubEchoHpfDefault      { 400 };
constexpr int   kFxDubEchoLpfMin          { 2000 };
constexpr int   kFxDubEchoLpfMax          { 20000 };
constexpr int   kFxDubEchoLpfDefault      { 8400 };
constexpr float kFxDubEchoMixMin          { 0.01f };
constexpr float kFxDubEchoMixMax          { 0.80f };
constexpr float kFxDubEchoMixDefault      { 0.38f };

// Chorus
constexpr float kFxChorusCenterMin        { 1.0f };
constexpr float kFxChorusCenterMax        { 120.0f };
constexpr float kFxChorusCenterDefault    { 12.0f };
constexpr float kFxChorusDepthMin         { 1.0f };
constexpr float kFxChorusDepthDefault     { 5.0f };
constexpr float kFxChorusMixMin           { 0.1f };
constexpr float kFxChorusMixMax           { 1.0f };
constexpr float kFxChorusMixDefault       { 1.0f };
constexpr float kFxChorusSpreadMin        { 0.001f };
constexpr float kFxChorusSpreadMax        { 0.1f };
constexpr float kFxChorusSpreadDefault    { 0.01f };
constexpr int   kFxChorusTapsDefault      { 6 };
constexpr float kFxChorusLfoBMin          { 0.0001f };
constexpr float kFxChorusLfoBMax          { 0.1f };
constexpr float kFxChorusLfoBDefault      { 0.002f };
constexpr float kFxChorusLfoTMin          { 0.1f };
constexpr float kFxChorusLfoTMax          { 20.0f };
constexpr float kFxChorusLfoTDefault      { 3.0f };
// 0: Vintage (thin), 1: Thick (multi-voice)
constexpr int   kFxChorusTypeDefault      { 1 };
constexpr float kFxChorusStaggerMin       { 0.0f };
constexpr float kFxChorusStaggerMax       { 1.0f };
constexpr float kFxChorusStaggerDefault   { 0.5f };
// Voices: 1 to 4 for Vintage, 1 to 6 for Thick
constexpr int   kFxChorusVoicesMin        { 1 };
constexpr int   kFxChorusVoicesMax        { 6 };

// Reverb
constexpr int   kFxReverbLpfMin           { 1000 };
constexpr int   kFxReverbLpfMax           { 20000 };
constexpr int   kFxReverbLpfDefault       { 9000 };
constexpr int   kFxReverbHpfMin           { 20 };
constexpr int   kFxReverbHpfMax           { 8000 };
constexpr int   kFxReverbHpfDefault       { 700 };
// 0: Vintage (echoey), 1: Plate (smooth)
constexpr int   kFxReverbTypeDefault      { 1 };
// Plate size at PARAM CCW; SizeMax min is derived from the current SizeMin.
constexpr float kFxReverbSizeMinMin       { 0.10f };
constexpr float kFxReverbSizeMinMax       { 1.1f };
constexpr float kFxReverbSizeMinDefault   { 0.6f };
constexpr float kFxReverbSizeMaxMax       { 1.1f };
constexpr float kFxReverbSizeMaxDefault   { 0.9f };
constexpr int   kFxReverbPredelayMin      { 0 };
constexpr int   kFxReverbPredelayMax      { 80 };
constexpr int   kFxReverbPredelayDefault  { 21 };
constexpr float kFxReverbModDepthMin      { 0.0f };
constexpr float kFxReverbModDepthMax      { 2.0f };
constexpr float kFxReverbModDepthDefault  { 0.6f };
constexpr float kFxReverbModRateMin       { 0.05f };
constexpr float kFxReverbModRateMax       { 5.0f };
constexpr float kFxReverbModRateDefault   { 1.0f };
constexpr float kFxReverbDiffusionMin     { 0.10f };
constexpr float kFxReverbDiffusionMax     { 0.99f };
constexpr float kFxReverbDiffusionDefault { 0.75f };
constexpr float kFxReverbMixMin           { 0.05f };
constexpr float kFxReverbMixMax           { 1.0f };
constexpr float kFxReverbMixDefault       { 0.6f };

// Glitch Probability
constexpr float kFxGlitchProbabilityMinMin     { 0.0000001f };
constexpr float kFxGlitchProbabilityMinMax     { 0.001f };
constexpr float kFxGlitchProbabilityMinDefault { 0.00005f };
constexpr float kFxGlitchProbabilityMaxMin     { 0.000001f };
constexpr float kFxGlitchProbabilityMaxMax     { 0.1f };
constexpr float kFxGlitchProbabilityMaxDefault { 0.003f };

// Glitch Weights (shared min/max range)
constexpr float kFxGlitchWeightMin             { 0.0f };
constexpr float kFxGlitchWeightMax             { 1.0f };
constexpr float kFxGlitchWeightHoldLowDefault       { 0.15f };
constexpr float kFxGlitchWeightStutterLowDefault    { 0.05f };
constexpr float kFxGlitchWeightCrushLowDefault      { 0.30f };
constexpr float kFxGlitchWeightDropLowDefault       { 0.02f };
constexpr float kFxGlitchWeightHoldHighDefault      { 0.30f };
constexpr float kFxGlitchWeightStutterHighDefault   { 0.20f };
constexpr float kFxGlitchWeightCrushHighDefault     { 0.20f };
constexpr float kFxGlitchWeightDropHighDefault      { 0.07f };

// Glitch Drop Keep Level (shared min/max range)
constexpr float kFxGlitchDropKeepLevelMin      { 0.0f };
constexpr float kFxGlitchDropKeepLevelMax      { 1.0f };
constexpr float kFxGlitchDropKeepLevelMinDefault { 0.0f };
constexpr float kFxGlitchDropKeepLevelMaxDefault { 0.75f };

// Glitch Drop Keep Time
constexpr float kFxGlitchDropKeepTimeMinMin    { 1.0f };
constexpr float kFxGlitchDropKeepTimeMinMax    { 100.0f };
constexpr float kFxGlitchDropKeepTimeMinDefault { 4.0f };
constexpr float kFxGlitchDropKeepTimeMaxMax    { 1000.0f };
constexpr float kFxGlitchDropKeepTimeMaxDefault { 40.0f };

// Glitch Crush Time
constexpr float kFxGlitchCrushTimeMinMin       { 1.0f };
constexpr float kFxGlitchCrushTimeMinMax       { 100.0f };
constexpr float kFxGlitchCrushTimeMinDefault   { 10.0f };
constexpr float kFxGlitchCrushTimeMaxMax       { 1000.0f };
constexpr float kFxGlitchCrushTimeMaxDefault   { 50.0f };

// Glitch Microloop Smpl T
constexpr float kFxGlitchMicroloopSmplTMinMin  { 0.01f };
constexpr float kFxGlitchMicroloopSmplTMinMax  { 20.0f };
constexpr float kFxGlitchMicroloopSmplTMinDefault { 0.2f };
constexpr float kFxGlitchMicroloopSmplTMaxMax  { 100.0f };
constexpr float kFxGlitchMicroloopSmplTMaxDefault { 3.0f };

// Glitch Microloop Play T
constexpr float kFxGlitchMicroloopPlayTMinMin  { 0.5f };
constexpr float kFxGlitchMicroloopPlayTMinMax  { 200.0f };
constexpr float kFxGlitchMicroloopPlayTMinDefault { 5.0f };
constexpr float kFxGlitchMicroloopPlayTMaxMax  { 1000.0f };
constexpr float kFxGlitchMicroloopPlayTMaxDefault { 15.0f };

// Glitch Stutter Smpl T
constexpr float kFxGlitchStutterSmplTMinMin    { 0.5f };
constexpr float kFxGlitchStutterSmplTMinMax    { 50.0f };
constexpr float kFxGlitchStutterSmplTMinDefault { 3.0f };
constexpr float kFxGlitchStutterSmplTMaxMax    { 100.0f };
constexpr float kFxGlitchStutterSmplTMaxDefault { 10.0f };

// Glitch Stutter Num (shared min/max range)
constexpr int   kFxGlitchStutterNumMin         { 1 };
constexpr int   kFxGlitchStutterNumMax         { 40 };
constexpr int   kFxGlitchStutterNumMinDefault  { 2 };
constexpr int   kFxGlitchStutterNumMaxDefault  { 5 };

// Glitch Stutter Window
constexpr int   kFxGlitchStutterWindowMin      { 1 };
constexpr int   kFxGlitchStutterWindowMax      { 100 };
constexpr int   kFxGlitchStutterWindowDefault  { 20 };
