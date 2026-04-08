#include "SettingsEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

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
constexpr int   kClsdReleaseModeDefault   { 1 };

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
constexpr float kFxChorusDepthMax         { 60.0f };
constexpr float kFxChorusDepthDefault     { 5.0f };
constexpr float kFxChorusMixMin           { 0.1f };
constexpr float kFxChorusMixMax           { 1.0f };
constexpr float kFxChorusMixDefault       { 1.0f };
constexpr float kFxChorusSpreadMin        { 0.001f };
constexpr float kFxChorusSpreadMax        { 0.1f };
constexpr float kFxChorusSpreadDefault    { 0.01f };
constexpr int   kFxChorusTapsDefault      { 4 };
constexpr float kFxChorusLfoBMin          { 0.0001f };
constexpr float kFxChorusLfoBMax          { 0.1f };
constexpr float kFxChorusLfoBDefault      { 0.002f };
constexpr float kFxChorusLfoTMin          { 0.1f };
constexpr float kFxChorusLfoTMax          { 20.0f };
constexpr float kFxChorusLfoTDefault      { 3.0f };

// Reverb
constexpr int   kFxReverbLpfMin           { 1000 };
constexpr int   kFxReverbLpfMax           { 20000 };
constexpr int   kFxReverbLpfDefault       { 9000 };
constexpr int   kFxReverbHpfMin           { 20 };
constexpr int   kFxReverbHpfMax           { 8000 };
constexpr int   kFxReverbHpfDefault       { 700 };

// Glitch Probability
constexpr float kFxGlitchProbabilityMinMin     { 0.0000001f };
constexpr float kFxGlitchProbabilityMinMax     { 0.001f };
constexpr float kFxGlitchProbabilityMinDefault { 0.00005f };
constexpr float kFxGlitchProbabilityMaxMin     { 0.000001f };
constexpr float kFxGlitchProbabilityMaxMax     { 0.1f };
constexpr float kFxGlitchProbabilityMaxDefault { 0.003f };

// Glitch Weights
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

// Glitch Drop Keep Level
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

// Glitch Stutter Num
constexpr int   kFxGlitchStutterNumMin         { 1 };
constexpr int   kFxGlitchStutterNumMax         { 40 };
constexpr int   kFxGlitchStutterNumMinDefault  { 2 };
constexpr int   kFxGlitchStutterNumMaxDefault  { 5 };

// Glitch Stutter Window
constexpr int   kFxGlitchStutterWindowMin      { 1 };
constexpr int   kFxGlitchStutterWindowMax      { 100 };
constexpr int   kFxGlitchStutterWindowDefault  { 20 };

juce::String getRoundedFloatString (float value, int decimalPlaces)
{
    return juce::String (value, decimalPlaces).trimCharactersAtEnd ("0").trimCharactersAtEnd (".");
}

SettingsEditorComponent::SettingsEditorComponent ()
{
	struct EditorFloatData
	{
		CustomTextEditorFloat* editor;
		juce::Label& label;
		const juce::String& labelText;
		juce::String toolTip;
		juce::String menuHeader;
	};

	struct FloatDataRangeGetters
    {
        std::function<float ()> getMin;
        std::function<float ()> getMax;
    };

	struct FloatDragMultipliers
	{
		float slow;
		float medium;
		float fast;
	};

	auto setupFloatEditor = [this] (EditorFloatData editorData,
                                    FloatDataRangeGetters dataRangeGetters,
									FloatDragMultipliers dragMultipliers,
									std::function<juce::String (float value)> toStringCallback,
									std::function<void (float value)> updateDataCallback,
									std::function<void (float valueOffset)> updateFromDragCallback,
									std::function<float ()> getDefaultValue,
									std::function<float ()> getUneditedValue)
	{
		jassert (editorData.editor != nullptr);
		jassert (updateFromDragCallback != nullptr);
		jassert (toStringCallback != nullptr);
		jassert (updateDataCallback != nullptr);
		jassert (getDefaultValue != nullptr);
		jassert (getUneditedValue != nullptr);

		editorData.editor->setTooltip (editorData.toolTip);
		editorData.editor->getMinValueCallback = [getMin = dataRangeGetters.getMin] () { return getMin (); };
		editorData.editor->getMaxValueCallback = [getMax = dataRangeGetters.getMax] () { return getMax (); };
		editorData.editor->toStringCallback = [toStringCallback] (float value) { return toStringCallback (value); };
		editorData.editor->updateDataCallback = [updateDataCallback] (float value) { updateDataCallback (value); };
		editorData.editor->onDragCallback = [dragMultipliers, updateFromDragCallback] (DragSpeed dragSpeed, int direction)
        {
            const auto multiplier = [dragSpeed, dragMultipliers] ()
                {
                    if (dragSpeed == DragSpeed::slow)
                        return dragMultipliers.slow;
                    else if (dragSpeed == DragSpeed::medium)
                        return dragMultipliers.medium;
                    else
                        return dragMultipliers.fast;
                } ();

            updateFromDragCallback (multiplier * direction);
        };
		editorData.editor->onPopupMenuCallback = [this, editor = editorData.editor, getDefaultValue, getUneditedValue, menuHeader = editorData.menuHeader] ()
		{
            auto* popupMenuLnF { new juce::LookAndFeel_V4 };
            popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));

			juce::PopupMenu pm;
			pm.setLookAndFeel (popupMenuLnF);
			pm.addSectionHeader (menuHeader);
			pm.addSeparator ();
			pm.addItem ("Default", true, false, [editor, getDefaultValue] ()
			{
				editor->setValue (getDefaultValue ());
			});
			pm.addItem ("Revert", true, false, [editor, getUneditedValue] ()
			{
				editor->setValue (getUneditedValue ());
			});
            pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
        };

		editorData.label.setText (editorData.labelText, juce::dontSendNotification);
		addAndMakeVisible (editorData.label);
		editorData.editor->setColour (juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
		editorData.editor->setIndents (5, 2);
		addAndMakeVisible (editorData.editor);
	};

	struct EditorIntData
	{
		CustomTextEditorInt* editor;
		juce::Label& label;
		const juce::String& labelText;
		juce::String toolTip;
		juce::String menuHeader;
	};

	struct IntDataRange
	{
		int min;
		int max;
	};

	struct IntDragMultipliers
	{
		int slow;
		int medium;
		int fast;
	};

	auto setupIntEditor = [this] (EditorIntData editorData,
								  IntDataRange dataRange,
								  IntDragMultipliers dragMultipliers,
								  std::function<juce::String (int value)> toStringCallback,
								  std::function<void (int value)> updateDataCallback,
								  std::function<void (int valueOffset)> updateFromDragCallback,
								  std::function<int ()> getDefaultValue,
								  std::function<int ()> getUneditedValue)
	{
		jassert (editorData.editor != nullptr);
		jassert (updateFromDragCallback != nullptr);
		jassert (toStringCallback != nullptr);
		jassert (updateDataCallback != nullptr);
		jassert (getDefaultValue != nullptr);
		jassert (getUneditedValue != nullptr);

		editorData.editor->setTooltip (editorData.toolTip);
		editorData.editor->getMinValueCallback = [minValue = dataRange.min] () { return minValue; };
		editorData.editor->getMaxValueCallback = [maxValue = dataRange.max] () { return maxValue; };
		editorData.editor->toStringCallback = [toStringCallback] (int value) { return toStringCallback (value); };
		editorData.editor->updateDataCallback = [updateDataCallback] (int value) { updateDataCallback (value); };
		editorData.editor->onDragCallback = [dragMultipliers, updateFromDragCallback] (DragSpeed dragSpeed, int direction)
		{
			const auto multiplier = [dragSpeed, dragMultipliers] ()
			{
				if (dragSpeed == DragSpeed::slow)
					return dragMultipliers.slow;
				else if (dragSpeed == DragSpeed::medium)
					return dragMultipliers.medium;
				else
					return dragMultipliers.fast;
			} ();

			updateFromDragCallback (multiplier * direction);
		};
		editorData.editor->onPopupMenuCallback = [this, editor = editorData.editor, getDefaultValue, getUneditedValue, menuHeader = editorData.menuHeader] ()
		{
            auto* popupMenuLnF { new juce::LookAndFeel_V4 };
            popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));

			juce::PopupMenu pm;
			pm.setLookAndFeel (popupMenuLnF);
			pm.addSectionHeader (menuHeader);
			pm.addSeparator ();
			pm.addItem ("Default", true, false, [editor, getDefaultValue] ()
			{
				editor->setValue (getDefaultValue ());
			});
			pm.addItem ("Revert", true, false, [editor, getUneditedValue] ()
			{
				editor->setValue (getUneditedValue ());
			});
            pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
        };

		editorData.label.setText (editorData.labelText, juce::dontSendNotification);
		addAndMakeVisible (editorData.label);
		editorData.editor->setColour (juce::TextEditor::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
		editorData.editor->setIndents (5, 2);
		addAndMakeVisible (editorData.editor);
	};

	struct ComboBoxData
	{
		CustomComboBox& comboBox;
		juce::Label& label;
		const juce::String& labelText;
		juce::String toolTip;
		juce::String menuHeader;
	};

	struct ComboBoxMenuItemData
	{
		juce::String text;
		int value;
	};

	auto setupComboBox = [this] (ComboBoxData comboBoxData,
								 std::vector<ComboBoxMenuItemData> menuItems,
                                 std::function<void ()> onChangeCallback,
								 std::function<void (int valueOffset)> updateFromDragCallback,
								 std::function<int ()> getDefaultValue,
								 std::function<int ()> getUneditedValue)
	{
        jassert (onChangeCallback != nullptr);
        jassert (updateFromDragCallback != nullptr);
		jassert (getDefaultValue != nullptr);
		jassert (getUneditedValue != nullptr);

		comboBoxData.comboBox.setLookAndFeel (&noArrowComboBoxLnF);
		comboBoxData.comboBox.setTooltip (comboBoxData.toolTip);

		for (const auto& menuItem : menuItems)
			comboBoxData.comboBox.addItem (menuItem.text, menuItem.value);

		comboBoxData.comboBox.onDragCallback = [updateFromDragCallback] (DragSpeed dragSpeed, int direction)
		{
			const auto valueOffset { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
			updateFromDragCallback (valueOffset);
		};
		comboBoxData.comboBox.onPopupMenuCallback = [this, comboBox = &comboBoxData.comboBox, getDefaultValue, getUneditedValue, menuHeader = comboBoxData.menuHeader] ()
		{
            auto* popupMenuLnF { new juce::LookAndFeel_V4 };
            popupMenuLnF->setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));

			juce::PopupMenu pm;
			pm.setLookAndFeel (popupMenuLnF);
			pm.addSectionHeader (menuHeader);
			pm.addSeparator ();
			pm.addItem ("Default", true, false, [comboBox, getDefaultValue] ()
			{
				comboBox->setSelectedId (getDefaultValue (), juce::NotificationType::sendNotification);
			});
			pm.addItem ("Revert", true, false, [comboBox, getUneditedValue] ()
			{
				comboBox->setSelectedId (getUneditedValue (), juce::NotificationType::sendNotification);
			});
            pm.showMenuAsync ({}, [this, popupMenuLnF] (int) { delete popupMenuLnF; });
        };
        comboBoxData.label.setText (comboBoxData.labelText, juce::dontSendNotification);
        comboBoxData.comboBox.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
        comboBoxData.comboBox.onChange = onChangeCallback;
        addAndMakeVisible (comboBoxData.label);
        addAndMakeVisible (comboBoxData.comboBox);
	};

    setupFloatEditor ({ &accClAmpModEditor, accClAmpModLabel, "Amp Mod", "Amp Mod CLOSED ACC hit", "Acc Cl Amp Mod" },
                         { []() { return kAccClAmpModMin; }, []() { return kAccClAmpModMax; } },
                         { 0.01f, 0.3f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accClAmpModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccClAmpMod () + valueOffset };
                             accClAmpModEditor.setValue (newValue);
                         },
                         [this] () { return kAccClAmpModDefault; },
                         [this] () { return uneditedSettingsProperties.getAccClAmpMod (); });

    setupFloatEditor ({ &accClRelModEditor, accClRelModLabel, "Rel Mod", "Acc Cl Rel Mod", "Acc Cl Rel Mod" },
                         { []() { return kAccClRelModMin; }, []() { return kAccClRelModMax; } },
                         { 0.01f, 0.3f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accClRelModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccClRelMod () + valueOffset };
                             accClRelModEditor.setValue (newValue);
                         },
                         [this] () { return kAccClRelModDefault; },
                         [this] () { return uneditedSettingsProperties.getAccClRelMod (); });

    setupFloatEditor ({ &accOpAmpModEditor, accOpAmpModLabel, "Amp Mod", "Acc Op Amp Mod", "Acc Op Amp Mod" },
                         { []() { return kAccOpAmpModMin; }, []() { return kAccOpAmpModMax; } },
                         { 0.1f, 0.5f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accOpAmpModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccOpAmpMod () + valueOffset };
                             accOpAmpModEditor.setValue (newValue);
                         },
                         [this] () { return kAccOpAmpModDefault; },
                         [this] () { return uneditedSettingsProperties.getAccOpAmpMod (); });

    setupFloatEditor ({ &accOpRelModEditor, accOpRelModLabel, "Rel Mod", "Acc Op Rel Mod", "Acc Op Rel Mod" },
                         { []() { return kAccOpRelModMin; }, []() { return kAccOpRelModMax; } },
                         { 0.1f, 0.5f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accOpRelModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccOpRelMod () + valueOffset };
                             accOpRelModEditor.setValue (newValue);
                         },
                         [this] () { return kAccOpRelModDefault; },
                         [this] () { return uneditedSettingsProperties.getAccOpRelMod (); });

    setupFloatEditor ({ &chokeReleaseEditor, chokeReleaseLabel, "Choke Release", "Choke Release", "Choke Release" },
                         { []() { return kChokeReleaseMin; }, []() { return kChokeReleaseMax; } },
                         { 0.001f, 0.5f, 3.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { chokeReleaseUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getChokeRelease () + valueOffset };
                             chokeReleaseEditor.setValue (newValue);
                         },
                         [this] () { return kChokeReleaseDefault; },
                         [this] () { return uneditedSettingsProperties.getChokeRelease (); });

    setupFloatEditor ({ &clsdMaxReleaseEditor, clsdMaxReleaseLabel, "Max Release", "Choke Release", "Clsd Max Release" },
                         { []() { return kClsdMaxReleaseMin; }, []() { return kClsdMaxReleaseMax; } },
                         { 0.1f, 0.3f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { clsdMaxReleaseUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getClsdMaxRelease () + valueOffset };
                             clsdMaxReleaseEditor.setValue (newValue);
                         },
                         [this] () { return kClsdMaxReleaseDefault; },
                         [this] () { return uneditedSettingsProperties.getClsdMaxRelease (); });

    setupFloatEditor ({ &clsdRelOfstScaleEditor, clsdRelOfstScaleLabel, "Rel Ofst Scale", "Choke Release", "Clsd Rel Ofst Scale" },
                         { []() { return kClsdRelOfstScaleMin; }, []() { return kClsdRelOfstScaleMax; } },
                         { 0.1f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { clsdRelOfstScaleUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getClsdRelOfstScale () + valueOffset };
                             clsdRelOfstScaleEditor.setValue (newValue);
                         },
                         [this] () { return kClsdRelOfstScaleDefault; },
                         [this] () { return uneditedSettingsProperties.getClsdRelOfstScale (); });

    // 0: Independent Release for Closed
    // 1: Release Offset mode
    setupComboBox ({ clsdReleaseModeComboBox, clsdReleaseModeLabel, "Release Mode", "", "Clsd Release Mode" },
                      { { "Independent", 1 },
                        { "Offset", 2 } },
                      [this] ()
                      {
                          clsdReleaseModeUiChanged (clsdReleaseModeComboBox.getSelectedId () - 1);
                      },
                      [this] (int valueOffset)
                      {
                          const auto clsdReleaseMode { clsdReleaseModeComboBox.getSelectedId () - 1 };
                          settingsProperties.setClsdReleaseMode (std::clamp (clsdReleaseMode + valueOffset, 0, 1), true);
                      },
                      [this] () { return kClsdReleaseModeDefault; },
                      [this] () { return uneditedSettingsProperties.getClsdReleaseMode () + 1; });

    // 0: FX CV Always On
    // 1: CV Disable : Freeze FX CV
    setupComboBox ({ cvDisableFxComboBox, cvDisableFxLabel, "CV Disable FX", "", "CV Disable FX" },
                      { { "FX CV On", 1 },
                        { "FX CV Off", 2 } },
                      [this] ()
                      {
                          cvDisableFxUiChanged (cvDisableFxComboBox.getSelectedId () - 1);
                      },
                      [this] (int valueOffset)
                      {
                          const auto cvDisableFx { cvDisableFxComboBox.getSelectedId () - 1 };
                          settingsProperties.setCvDisableFx (std::clamp (cvDisableFx + valueOffset, 0, 1), true);
                      },
                      [this] () { return kCvDisableFxDefault; },
                      [this] () { return uneditedSettingsProperties.getCvDisableFx () + 1; });

    // 0: Velocity always enabled
    // 1: CV Off SW affects velocity
    setupComboBox ({ cvDisableVelocityComboBox, cvDisableVelocityLabel, "CV Disable Velocity", "", "CV Disable Velocity" },
                      { { "Always On", 1 },
                        { "CV Off", 2 } },
                      [this] ()
                      {
                          cvDisableVelocityUiChanged (cvDisableVelocityComboBox.getSelectedId () - 1);
                      },
                      [this] (int valueOffset)
                      {
                          const auto cvDisableVelocity { cvDisableVelocityComboBox.getSelectedId () - 1 };
                          settingsProperties.setCvDisableVelocity (std::clamp (cvDisableVelocity + valueOffset, 0, 1), true);
                      },
                      [this] () { return kCvDisableVelocityDefault; },
                      [this] () { return uneditedSettingsProperties.getCvDisableVelocity () + 1; });

    setupFloatEditor ({ &envelopeMaxReleaseEditor, envelopeMaxReleaseLabel, "Max Release", "Envelope Max Release", "Envelope Max Release" },
                         { []() { return kEnvelopeMaxReleaseMin; }, []() { return kEnvelopeMaxReleaseMax; } },
                         { 0.1f, 0.5f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { envelopeMaxReleaseUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getEnvelopeMaxRelease () + valueOffset };
                             envelopeMaxReleaseEditor.setValue (newValue);
                         },
                         [this] () { return kEnvelopeMaxReleaseDefault; },
                         [this] () { return uneditedSettingsProperties.getEnvelopeMaxRelease (); });

    setupFloatEditor ({ &feelAmpModEditor, feelAmpModLabel, "Amp Mod", "Feel Amp Mod", "Feel Amp Mod" },
                         { []() { return kFeelAmpModMin; }, []() { return kFeelAmpModMax; } },
                         { 0.1f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { feelAmpModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFeelAmpMod () + valueOffset };
                             feelAmpModEditor.setValue (newValue);
                         },
                         [this] () { return kFeelAmpModDefault; },
                         [this] () { return uneditedSettingsProperties.getFeelAmpMod (); });

    setupFloatEditor ({ &feelAttackModEditor, feelAttackModLabel, "Attack Mod", "Feel Attack Mod", "Feel Attack Mod" },
                         { []() { return kFeelAttackModMin; }, []() { return kFeelAttackModMax; } },
                         { 0.1f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { feelAttackModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFeelAttackMod () + valueOffset };
                             feelAttackModEditor.setValue (newValue);
                         },
                         [this] () { return kFeelAttackModDefault; },
                         [this] () { return uneditedSettingsProperties.getFeelAttackMod (); });

    setupFloatEditor ({ &feelReleaseModEditor, feelReleaseModLabel, "Release Mod", "Feel Release Mod", "Feel Release Mod" },
                         { []() { return kFeelReleaseModMin; }, []() { return kFeelReleaseModMax; } },
                         { 0.1f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { feelReleaseModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFeelReleaseMod () + valueOffset };
                             feelReleaseModEditor.setValue (newValue);
                         },
                         [this] () { return kFeelReleaseModDefault; },
                         [this] () { return uneditedSettingsProperties.getFeelReleaseMod (); });

    setupIntEditor ({ &fltrHpfMaxFreqEditor, fltrHpfMaxFreqLabel, "Max Freq", "Fltr HPF Max Freq", "Fltr HPF Max Freq" },
                       { kFltrHpfMaxFreqMin, kFltrHpfMaxFreqMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrHpfMaxFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrHpfMaxFreq () + valueOffset };
                           fltrHpfMaxFreqEditor.setValue (newValue);
                       },
                       [this] () { return kFltrHpfMaxFreqDefault; },
                       [this] () { return uneditedSettingsProperties.getFltrHpfMaxFreq (); });

    setupIntEditor ({ &fltrHpfMinFreqEditor, fltrHpfMinFreqLabel, "Min Freq", "Fltr HPF Min Freq", "Fltr HPF Min Freq" },
                       { kFltrHpfMinFreqMin, kFltrHpfMinFreqMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrHpfMinFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrHpfMinFreq () + valueOffset };
                           fltrHpfMinFreqEditor.setValue (newValue);
                       },
                       [this] () { return kFltrHpfMinFreqDefault; },
                       [this] () { return uneditedSettingsProperties.getFltrHpfMinFreq (); });

    setupFloatEditor ({ &fltrHpfQEditor, fltrHpfQLabel, "Q", "Fltr HPF Q", "Fltr HPF Q" },
                         { []() { return kFltrHpfQMin; }, []() { return kFltrHpfQMax; } },
                         { 0.001f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fltrHpfQUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFltrHpfQ () + valueOffset };
                             fltrHpfQEditor.setValue (newValue);
                         },
                         [this] () { return kFltrHpfQDefault; },
                         [this] () { return uneditedSettingsProperties.getFltrHpfQ (); });

    setupIntEditor ({ &fltrLpfMaxFreqEditor, fltrLpfMaxFreqLabel, "Max Freq", "Fltr LPF Max Freq", "Fltr LPF Max Freq" },
                       { kFltrLpfMaxFreqMin, kFltrLpfMaxFreqMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrLpfMaxFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrLpfMaxFreq () + valueOffset };
                           fltrLpfMaxFreqEditor.setValue (newValue);
                       },
                       [this] () { return kFltrLpfMaxFreqDefault; },
                       [this] () { return uneditedSettingsProperties.getFltrLpfMaxFreq (); });

    setupIntEditor ({ &fltrLpfMinFreqEditor, fltrLpfMinFreqLabel, "Min Freq", "Fltr LPF Min Freq", "Fltr LPF Min Freq" },
                       { kFltrLpfMinFreqMin, kFltrLpfMinFreqMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrLpfMinFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrLpfMinFreq () + valueOffset };
                           fltrLpfMinFreqEditor.setValue (newValue);
                       },
                       [this] () { return kFltrLpfMinFreqDefault; },
                       [this] () { return uneditedSettingsProperties.getFltrLpfMinFreq (); });

    setupFloatEditor ({ &fltrLpfQEditor, fltrLpfQLabel, "Q", "Fltr LPF Q", "Fltr LPF Q" },
                         { []() { return kFltrLpfQMin; }, []() { return kFltrLpfQMax; } },
                         { 0.001f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fltrLpfQUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFltrLpfQ () + valueOffset };
                             fltrLpfQEditor.setValue (newValue);
                         },
                         [this] () { return kFltrLpfQDefault; },
                         [this] () { return uneditedSettingsProperties.getFltrLpfQ (); });

    setupFloatEditor ({ &fxChorusCenterEditor, fxChorusCenterLabel, "Center", "FX Chorus Center", "FX Chorus Center" },
                         { []() { return kFxChorusCenterMin; }, []() { return kFxChorusCenterMax; } },
                         { 1.0f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusCenterUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusCenter () + valueOffset };
                             fxChorusCenterEditor.setValue (newValue);
                         },
                         [this] () { return kFxChorusCenterDefault; },
                         [this] () { return uneditedSettingsProperties.getFxChorusCenter (); });

    setupFloatEditor ({ &fxChorusDepthEditor, fxChorusDepthLabel, "Depth", "FX Chorus Depth", "FX Chorus Depth" },
                         { []() { return kFxChorusDepthMin; }, [this]() { return settingsProperties.getFxChorusCenter () / 2.0f; } },
                         { 1.0f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusDepthUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusDepth () + valueOffset };
                             fxChorusDepthEditor.setValue (newValue);
                         },
                         [this] () { return kFxChorusDepthDefault; },
                         [this] () { return uneditedSettingsProperties.getFxChorusDepth (); });

    setupFloatEditor ({ &fxChorusLfoBEditor, fxChorusLfoBLabel, "LFO B", "FX Chorus LFO B", "FX Chorus LFO B" },
                         { []() { return kFxChorusLfoBMin; }, []() { return kFxChorusLfoBMax; } },
                         { 0.001f, 0.1f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusLfoBUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusLfoB () + valueOffset };
                             fxChorusLfoBEditor.setValue (newValue);
                         },
                         [this] () { return kFxChorusLfoBDefault; },
                         [this] () { return uneditedSettingsProperties.getFxChorusLfoB (); });

    setupFloatEditor ({ &fxChorusLfoTEditor, fxChorusLfoTLabel, "LFO T", "FX Chorus LFO T", "FX Chorus LFO T" },
                         { []() { return kFxChorusLfoTMin; }, []() { return kFxChorusLfoTMax; } },
                         { 0.001f, 0.1f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusLfoTUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusLfoT () + valueOffset };
                             fxChorusLfoTEditor.setValue (newValue);
                         },
                         [this] () { return kFxChorusLfoTDefault; },
                         [this] () { return uneditedSettingsProperties.getFxChorusLfoT (); });

    setupFloatEditor ({ &fxChorusMixEditor, fxChorusMixLabel, "Mix", "FX Chorus Mix", "FX Chorus Mix" },
                         { []() { return kFxChorusMixMin; }, []() { return kFxChorusMixMax; } },
                         { 0.1f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusMixUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusMix () + valueOffset };
                             fxChorusMixEditor.setValue (newValue);
                         },
                         [this] () { return kFxChorusMixDefault; },
                         [this] () { return uneditedSettingsProperties.getFxChorusMix (); });

    setupFloatEditor ({ &fxChorusSpreadEditor, fxChorusSpreadLabel, "Spread", "FX Chorus Spread", "FX Chorus Spread" },
                         { []() { return kFxChorusSpreadMin; }, []() { return kFxChorusSpreadMax; } },
                         { 0.01f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusSpreadUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusSpread () + valueOffset };
                             fxChorusSpreadEditor.setValue (newValue);
                         },
                         [this] () { return kFxChorusSpreadDefault; },
                         [this] () { return uneditedSettingsProperties.getFxChorusSpread (); });

    // Integer # of Taps (1–4)
    setupComboBox ({ fxChorusTapsComboBox, fxChorusTapsLabel, "Taps", "", "FX Chorus Taps" },
                      { { "1", 1 },
                        { "2", 2 },
                        { "3", 3 },
                        { "4", 4 } },
                      [this] ()
                      {
                          fxChorusTapsUiChanged (fxChorusTapsComboBox.getSelectedId ());
                      },
                      [this] (int valueOffset)
                      {
                          const auto fxChorusTaps { fxChorusTapsComboBox.getSelectedId () };
                          settingsProperties.setFxChorusTaps (std::clamp (fxChorusTaps + valueOffset, 1, 4), true);
                      },
                      [this] () { return kFxChorusTapsDefault; },
                      [this] () { return uneditedSettingsProperties.getFxChorusTaps () + 1; });

    // 0: -5 to 5V, 1: 0 to 5V 
    setupComboBox ({ fxCvUnipolarComboBox, fxCvUnipolarLabel, "FX CV Unipolar", "", "FX CV Unipolar" },
                      { { "-5v to 5v", 1 },
                        { "0v to 5v", 2 } },
                      [this] ()
                      {
                          fxCvUnipolarUiChanged (fxCvUnipolarComboBox.getSelectedId ());
                      },
                      [this] (int valueOffset)
                      {
                          const auto fxCvUnipolar { fxCvUnipolarComboBox.getSelectedId () - 1 };
                          settingsProperties.setFxCvUnipolar (std::clamp (fxCvUnipolar + valueOffset, 0, 1), true);
                      },
                      [this] () { return kFxCvUnipolarDefault; },
                      [this] () { return uneditedSettingsProperties.getFxCvUnipolar () + 1; });

    setupIntEditor ({ &fxDjfilterHpfMaxEditor, fxDjfilterHpfMaxLabel, "Max", "FX DJ Filter HPF Max", "FX DJ Filter HPF Max" },
                       { kFxDjfilterHpfMaxMin, kFxDjfilterHpfMaxMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterHpfMaxUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterHpfMax () + valueOffset };
                           fxDjfilterHpfMaxEditor.setValue (newValue);
                       },
                       [this] () { return kFxDjfilterHpfMaxDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterHpfMax (); });

    setupIntEditor ({ &fxDjfilterHpfMinEditor, fxDjfilterHpfMinLabel, "Min", "FX DJ Filter HPF Min", "FX DJ Filter HPF Min" },
                       { kFxDjfilterHpfMinMin, kFxDjfilterHpfMinMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterHpfMinUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterHpfMin () + valueOffset };
                           fxDjfilterHpfMinEditor.setValue (newValue);
                       },
                       [this] () { return kFxDjfilterHpfMinDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterHpfMin (); });

    setupIntEditor ({ &fxDjfilterLpfMaxEditor, fxDjfilterLpfMaxLabel, "Max", "FX DJ Filter LPF Max", "FX DJ Filter LPF Max" },
                       { kFxDjfilterLpfMaxMin, kFxDjfilterLpfMaxMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterLpfMaxUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterLpfMax () + valueOffset };
                           fxDjfilterLpfMaxEditor.setValue (newValue);
                       },
                       [this] () { return kFxDjfilterLpfMaxDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterLpfMax (); });

    setupIntEditor ({ &fxDjfilterLpfMinEditor, fxDjfilterLpfMinLabel, "Min", "FX DJ Filter LPF Min", "FX DJ Filter LPF Min" },
                       { kFxDjfilterLpfMinMin, kFxDjfilterLpfMinMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterLpfMinUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterLpfMin () + valueOffset };
                           fxDjfilterLpfMinEditor.setValue (newValue);
                       },
                       [this] () { return kFxDjfilterLpfMinDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterLpfMin (); });

    setupFloatEditor ({ &fxDjfilterQGainReductionEditor, fxDjfilterQGainReductionLabel, "Gain Reduction", "FX DJ Filter Q Gain Reduction", "FX DJ Filter Q Gain Reduction" },
                         { []() { return kFxDjfilterQGainReductionMin; }, []() { return kFxDjfilterQGainReductionMax; } },
                         { 0.01f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDjfilterQGainReductionUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDjfilterQGainReduction () + valueOffset };
                             fxDjfilterQGainReductionEditor.setValue (newValue);
                         },
                         [this] () { return kFxDjfilterQGainReductionDefault; },
                         [this] () { return uneditedSettingsProperties.getFxDjfilterQGainReduction (); });

    setupFloatEditor ({ &fxDjfilterQMaxEditor, fxDjfilterQMaxLabel, "Max", "FX DJ Filter Q Max", "FX DJ Filter Q Max" },
                         { []() { return kFxDjfilterQMaxMin; }, []() { return kFxDjfilterQMaxMax; } },
                         { 0.1f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDjfilterQMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDjfilterQMax () + valueOffset };
                             fxDjfilterQMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxDjfilterQMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxDjfilterQMax (); });

    setupFloatEditor ({ &fxDjfilterQMinEditor, fxDjfilterQMinLabel, "Min", "FX DJ Filter Q Min", "FX DJ Filter Q Min" },
                         { []() { return kFxDjfilterQMinMin; }, []() { return kFxDjfilterQMinMax; } },
                         { 0.1f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDjfilterQMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDjfilterQMin () + valueOffset };
                             fxDjfilterQMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxDjfilterQMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxDjfilterQMin (); });

    setupIntEditor ({ &fxDubEchoHpfEditor, fxDubEchoHpfLabel, "HPF", "FX Dub Echo HPF", "FX Dub Echo HPF" },
                       { kFxDubEchoHpfMin, kFxDubEchoHpfMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDubEchoHpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDubEchoHpf () + valueOffset };
                           fxDubEchoHpfEditor.setValue (newValue);
                       },
                       [this] () { return kFxDubEchoHpfDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDubEchoHpf (); });

    setupIntEditor ({ &fxDubEchoLpfEditor, fxDubEchoLpfLabel, "LPF", "FX Dub Echo LPF", "FX Dub Echo LPF" },
                       { kFxDubEchoLpfMin, kFxDubEchoLpfMax },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDubEchoLpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDubEchoLpf () + valueOffset };
                           fxDubEchoLpfEditor.setValue (newValue);
                       },
                       [this] () { return kFxDubEchoLpfDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDubEchoLpf (); });

    setupFloatEditor ({ &fxDubEchoMixEditor, fxDubEchoMixLabel, "Mix", "FX Dub Echo Mix", "FX Dub Echo Mix" },
                         { []() { return kFxDubEchoMixMin; }, []() { return kFxDubEchoMixMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDubEchoMixUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDubEchoMix () + valueOffset };
                             fxDubEchoMixEditor.setValue (newValue);
                         },
                         [this] () { return kFxDubEchoMixDefault; },
                         [this] () { return uneditedSettingsProperties.getFxDubEchoMix (); });

    setupIntEditor ({ &fxDubEchoTminEditor, fxDubEchoTminLabel, "Tmin", "FX Dub Echo Tmin", "FX Dub Echo Tmin" },
                       { kFxDubEchoTminMin, kFxDubEchoTminMax },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDubEchoTminUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDubEchoTmin () + valueOffset };
                           fxDubEchoTminEditor.setValue (newValue);
                       },
                       [this] () { return kFxDubEchoTminDefault; },
                       [this] () { return uneditedSettingsProperties.getFxDubEchoTmin (); });

    setupFloatEditor ({ &fxGlitchCrushTimeMaxEditor, fxGlitchCrushTimeMaxLabel, "Time Max", "FX Glitch Crush Time Max", "FX Glitch Crush Time Max" },
                         { [this]() { return settingsProperties.getFxGlitchCrushTimeMin (); }, []() { return kFxGlitchCrushTimeMaxMax; } },
                         { 0.1f, 5.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchCrushTimeMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchCrushTimeMax () + valueOffset };
                             fxGlitchCrushTimeMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchCrushTimeMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchCrushTimeMax (); });
    fxGlitchCrushTimeMaxEditor.getMinValueCallback = [this] () { return settingsProperties.getFxGlitchCrushTimeMin (); };

    setupFloatEditor ({ &fxGlitchCrushTimeMinEditor, fxGlitchCrushTimeMinLabel, "Time Min", "FX Glitch Crush Time Min", "FX Glitch Crush Time Min" },
                         { []() { return kFxGlitchCrushTimeMinMin; }, []() { return kFxGlitchCrushTimeMinMax; } },
                         { 0.1f, 5.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchCrushTimeMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchCrushTimeMin () + valueOffset };
                             fxGlitchCrushTimeMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchCrushTimeMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchCrushTimeMin (); });

    setupFloatEditor ({ &fxGlitchDropKeepLevelMaxEditor, fxGlitchDropKeepLevelMaxLabel, "Level Max", "FX Glitch Drop Keep Level Max", "FX Glitch Drop Keep Level Max" },
                         { []() { return kFxGlitchDropKeepLevelMin; }, []() { return kFxGlitchDropKeepLevelMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepLevelMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepLevelMax () + valueOffset };
                             fxGlitchDropKeepLevelMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchDropKeepLevelMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepLevelMax (); });

    setupFloatEditor ({ &fxGlitchDropKeepLevelMinEditor, fxGlitchDropKeepLevelMinLabel, "Level Min", "FX Glitch Drop Keep Level Min", "FX Glitch Drop Keep Level Min" },
                         { []() { return kFxGlitchDropKeepLevelMin; }, []() { return kFxGlitchDropKeepLevelMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepLevelMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepLevelMin () + valueOffset };
                             fxGlitchDropKeepLevelMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchDropKeepLevelMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepLevelMin (); });

    setupFloatEditor ({ &fxGlitchDropKeepTimeMaxEditor, fxGlitchDropKeepTimeMaxLabel, "Time Max", "FX Glitch Drop Keep Time Max", "FX Glitch Drop Keep Time Max" },
                         { [this]() { return settingsProperties.getFxGlitchDropKeepTimeMin (); }, []() { return kFxGlitchDropKeepTimeMaxMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepTimeMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepTimeMax () + valueOffset };
                             fxGlitchDropKeepTimeMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchDropKeepTimeMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepTimeMax (); });

    setupFloatEditor ({ &fxGlitchDropKeepTimeMinEditor, fxGlitchDropKeepTimeMinLabel, "Time Min", "FX Glitch Drop Keep Time Min", "FX Glitch Drop Keep Time Min" },
                         { []() { return kFxGlitchDropKeepTimeMinMin; }, []() { return kFxGlitchDropKeepTimeMinMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepTimeMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepTimeMin () + valueOffset };
                             fxGlitchDropKeepTimeMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchDropKeepTimeMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepTimeMin (); });

    setupFloatEditor ({ &fxGlitchMicroloopPlayTMaxEditor, fxGlitchMicroloopPlayTMaxLabel, "Play T Max", "FX Glitch Microloop Play T Max", "FX Glitch Microloop Play T Max" },
                         { [this]() { return settingsProperties.getFxGlitchMicroloopPlayTMin (); }, []() { return kFxGlitchMicroloopPlayTMaxMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopPlayTMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopPlayTMax () + valueOffset };
                             fxGlitchMicroloopPlayTMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchMicroloopPlayTMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopPlayTMax (); });

    setupFloatEditor ({ &fxGlitchMicroloopPlayTMinEditor, fxGlitchMicroloopPlayTMinLabel, "Play T Min", "FX Glitch Microloop Play T Min", "FX Glitch Microloop Play T Min" },
                         { []() { return kFxGlitchMicroloopPlayTMinMin; }, []() { return kFxGlitchMicroloopPlayTMinMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopPlayTMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopPlayTMin () + valueOffset };
                             fxGlitchMicroloopPlayTMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchMicroloopPlayTMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopPlayTMin (); });

    setupFloatEditor ({ &fxGlitchMicroloopSmplTMaxEditor, fxGlitchMicroloopSmplTMaxLabel, "Smpl T Max", "FX Glitch Microloop Smpl T Max", "FX Glitch Microloop Smpl T Max" },
                         { [this]() { return settingsProperties.getFxGlitchMicroloopSmplTMin (); }, []() { return kFxGlitchMicroloopSmplTMaxMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopSmplTMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopSmplTMax () + valueOffset };
                             fxGlitchMicroloopSmplTMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchMicroloopSmplTMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopSmplTMax (); });

    setupFloatEditor ({ &fxGlitchMicroloopSmplTMinEditor, fxGlitchMicroloopSmplTMinLabel, "Smpl T Min", "FX Glitch Microloop Smpl T Min", "FX Glitch Microloop Smpl T Min" },
                         { []() { return kFxGlitchMicroloopSmplTMinMin; }, []() { return kFxGlitchMicroloopSmplTMinMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopSmplTMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopSmplTMin () + valueOffset };
                             fxGlitchMicroloopSmplTMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchMicroloopSmplTMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopSmplTMin (); });

    setupFloatEditor ({ &fxGlitchProbabilityMaxEditor, fxGlitchProbabilityMaxLabel, "Max", "FX Glitch Probability Max", "FX Glitch Probability Max" },
                         { []() { return kFxGlitchProbabilityMaxMin; }, []() { return kFxGlitchProbabilityMaxMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchProbabilityMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchProbabilityMax () + valueOffset };
                             fxGlitchProbabilityMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchProbabilityMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchProbabilityMax (); });

    setupFloatEditor ({ &fxGlitchProbabilityMinEditor, fxGlitchProbabilityMinLabel, "Min", "FX Glitch Probability Min", "FX Glitch Probability Min" },
                         { []() { return kFxGlitchProbabilityMinMin; }, []() { return kFxGlitchProbabilityMinMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 5); },
                         [this] (float value) { fxGlitchProbabilityMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchProbabilityMin () + valueOffset };
                             fxGlitchProbabilityMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchProbabilityMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchProbabilityMin (); });

    setupIntEditor ({ &fxGlitchStutterNumMaxEditor, fxGlitchStutterNumMaxLabel, "Num Max", "FX Glitch Stutter Num Max", "FX Glitch Stutter Num Max" },
                       { kFxGlitchStutterNumMin, kFxGlitchStutterNumMax },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxGlitchStutterNumMaxUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxGlitchStutterNumMax () + valueOffset };
                           fxGlitchStutterNumMaxEditor.setValue (newValue);
                       },
                       [this] () { return kFxGlitchStutterNumMaxDefault; },
                       [this] () { return uneditedSettingsProperties.getFxGlitchStutterNumMax (); });

    setupIntEditor ({ &fxGlitchStutterNumMinEditor, fxGlitchStutterNumMinLabel, "Num Min", "FX Glitch Stutter Num Min", "FX Glitch Stutter Num Min" },
                       { kFxGlitchStutterNumMin, kFxGlitchStutterNumMax },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxGlitchStutterNumMinUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxGlitchStutterNumMin () + valueOffset };
                           fxGlitchStutterNumMinEditor.setValue (newValue);
                       },
                       [this] () { return kFxGlitchStutterNumMinDefault; },
                       [this] () { return uneditedSettingsProperties.getFxGlitchStutterNumMin (); });

    setupFloatEditor ({ &fxGlitchStutterSmplTMaxEditor, fxGlitchStutterSmplTMaxLabel, "Smpl T Max", "FX Glitch Stutter Smpl T Max", "FX Glitch Stutter Smpl T Max" },
                         { [this]() { return settingsProperties.getFxGlitchStutterSmplTMin (); }, []() { return kFxGlitchStutterSmplTMaxMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchStutterSmplTMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchStutterSmplTMax () + valueOffset };
                             fxGlitchStutterSmplTMaxEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchStutterSmplTMaxDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchStutterSmplTMax (); });

    setupFloatEditor ({ &fxGlitchStutterSmplTMinEditor, fxGlitchStutterSmplTMinLabel, "Smpl T Min", "FX Glitch Stutter Smpl T Min", "FX Glitch Stutter Smpl T Min" },
                         { []() { return kFxGlitchStutterSmplTMinMin; }, []() { return kFxGlitchStutterSmplTMinMax; } },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchStutterSmplTMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchStutterSmplTMin () + valueOffset };
                             fxGlitchStutterSmplTMinEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchStutterSmplTMinDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchStutterSmplTMin (); });

    setupIntEditor ({ &fxGlitchStutterWindowEditor, fxGlitchStutterWindowLabel, "Window", "FX Glitch Stutter Window", "FX Glitch Stutter Window" },
                       { kFxGlitchStutterWindowMin, kFxGlitchStutterWindowMax },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxGlitchStutterWindowUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxGlitchStutterWindow () + valueOffset };
                           fxGlitchStutterWindowEditor.setValue (newValue);
                       },
                       [this] () { return kFxGlitchStutterWindowDefault; },
                       [this] () { return uneditedSettingsProperties.getFxGlitchStutterWindow (); });

    setupFloatEditor ({ &fxGlitchWeightCrushHighEditor, fxGlitchWeightCrushHighLabel, "Crush High", "FX Glitch Weight Crush High", "FX Glitch Weight Crush High" },
                      { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                      { 0.1f, 0.3f, 0.5f },
                      [this] (float value) { return getRoundedFloatString (value, 4); },
                      [this] (float value) { fxGlitchWeightCrushHighUiChanged (value); },
                      [this] (float valueOffset)
                      {
                          const auto newValue { settingsProperties.getFxGlitchWeightCrushHigh () + valueOffset };
                          fxGlitchWeightCrushHighEditor.setValue (newValue);
                      },
                      [this] () { return kFxGlitchWeightCrushHighDefault; },
                      [this] () { return uneditedSettingsProperties.getFxGlitchWeightCrushHigh (); });

    setupFloatEditor ({ &fxGlitchWeightCrushLowEditor, fxGlitchWeightCrushLowLabel, "Crush Low", "FX Glitch Weight Crush Low", "FX Glitch Weight Crush Low" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightCrushLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightCrushLow () + valueOffset };
                             fxGlitchWeightCrushLowEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightCrushLowDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightCrushLow (); });

    setupFloatEditor ({ &fxGlitchWeightDropHighEditor, fxGlitchWeightDropHighLabel, "Drop High", "FX Glitch Weight Drop High", "FX Glitch Weight Drop High" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightDropHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightDropHigh () + valueOffset };
                             fxGlitchWeightDropHighEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightDropHighDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightDropHigh (); });

    setupFloatEditor ({ &fxGlitchWeightDropLowEditor, fxGlitchWeightDropLowLabel, "Drop Low", "FX Glitch Weight Drop Low", "FX Glitch Weight Drop Low" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightDropLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightDropLow () + valueOffset };
                             fxGlitchWeightDropLowEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightDropLowDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightDropLow (); });

    setupFloatEditor ({ &fxGlitchWeightHoldHighEditor, fxGlitchWeightHoldHighLabel, "Hold High", "FX Glitch Weight Hold High", "FX Glitch Weight Hold High" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightHoldHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightHoldHigh () + valueOffset };
                             fxGlitchWeightHoldHighEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightHoldHighDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightHoldHigh (); });

    setupFloatEditor ({ &fxGlitchWeightHoldLowEditor, fxGlitchWeightHoldLowLabel, "Hold Low", "FX Glitch Weight Hold Low", "FX Glitch Weight Hold Low" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightHoldLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightHoldLow () + valueOffset };
                             fxGlitchWeightHoldLowEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightHoldLowDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightHoldLow (); });

    setupFloatEditor ({ &fxGlitchWeightStutterHighEditor, fxGlitchWeightStutterHighLabel, "Stutter High", "FX Glitch Weight Stutter High", "FX Glitch Weight Stutter High" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightStutterHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightStutterHigh () + valueOffset };
                             fxGlitchWeightStutterHighEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightStutterHighDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightStutterHigh (); });

    setupFloatEditor ({ &fxGlitchWeightStutterLowEditor, fxGlitchWeightStutterLowLabel, "Stutter Low", "FX Glitch Weight Stutter Low", "FX Glitch Weight Stutter Low" },
                         { []() { return kFxGlitchWeightMin; }, []() { return kFxGlitchWeightMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightStutterLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightStutterLow () + valueOffset };
                             fxGlitchWeightStutterLowEditor.setValue (newValue);
                         },
                         [this] () { return kFxGlitchWeightStutterLowDefault; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightStutterLow (); });

    setupIntEditor ({ &fxReverbHpfEditor, fxReverbHpfLabel, "HPF", "FX Reverb HPF", "FX Reverb HPF" },
                       { kFxReverbHpfMin, kFxReverbHpfMax },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxReverbHpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxReverbHpf () + valueOffset };
                           fxReverbHpfEditor.setValue (newValue);
                       },
                       [this] () { return kFxReverbHpfDefault; },
                       [this] () { return uneditedSettingsProperties.getFxReverbHpf (); });

    setupIntEditor ({ &fxReverbLpfEditor, fxReverbLpfLabel, "LPF", "FX Reverb LPF", "FX Reverb LPF" },
                       { kFxReverbLpfMin, kFxReverbLpfMax },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxReverbLpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxReverbLpf () + valueOffset };
                           fxReverbLpfEditor.setValue (newValue);
                       },
                       [this] () { return kFxReverbLpfDefault; },
                       [this] () { return uneditedSettingsProperties.getFxReverbLpf (); });

    // 0: 0V = 100 % -5 = 0 % +5 = 200 %
    // 1: 0V = 10 % +5 = 100 %
    setupComboBox ({ gateModeComboBox, gateModeLabel, "Gate Mode", "", "Gate Mode" },
                      { { "Immediate", 1 },
                        { "After Gate Falls", 2 } },
                      [this] ()
                      {
                          gateModeUiChanged (gateModeComboBox.getSelectedId () - 1);
                      },
                      [this] (int valueOffset)
                      {
                          const auto gateMode { gateModeComboBox.getSelectedId () - 1 };
                          settingsProperties.setGateMode (std::clamp (gateMode + valueOffset, 0, 1), true);
                      },
                      [this] () { return kGateModeDefault; },
                      [this] () { return uneditedSettingsProperties.getGateMode () + 1; });

    // 0 to sense small movement (wiggle)
    // 1 to require passing old value
    setupComboBox ({ knobPosTakeupComboBox, knobPosTakeupLabel, "Knob Pos Takeup", "", "Knob Pos Takeup" },
                      { { "Small Movement", 1 },
                        { "Pass Old Value", 2 } },
                      [this] ()
                      {
                          knobPosTakeupUiChanged (knobPosTakeupComboBox.getSelectedId () - 1);
                      },
                      [this] (int valueOffset)
                      {
                          const auto knobsPosTakeUp { knobPosTakeupComboBox.getSelectedId () - 1 };
                          settingsProperties.setKnobPosTakeup (std::clamp (knobsPosTakeUp + valueOffset, 0, 1), true);
                      },
                      [this] () { return kKnobPosTakeupDefault; },
                      [this] () { return uneditedSettingsProperties.getKnobPosTakeup () + 1; });

    setupFloatEditor ({ &pitchHighEditor, pitchHighLabel, "Pitch High", "Pitch High", "Pitch High" },
                         { []() { return kPitchHighMin; }, []() { return kPitchHighMax; } },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { pitchHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getPitchHigh () + valueOffset };
                             pitchHighEditor.setValue (newValue);
                         },
                         [this] () { return kPitchHighDefault; },
                         [this] () { return uneditedSettingsProperties.getPitchHigh (); });

    setupFloatEditor ({ &pitchLowEditor, pitchLowLabel, "Pitch Low", "Pitch Low", "Pitch Low" },
                         { []() { return kPitchLowMin; }, []() { return kPitchLowMax; } },
                         { 0.001f, 0.01f, 0.1f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { pitchLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getPitchLow () + valueOffset };
                             pitchLowEditor.setValue (newValue);
                         },
                         [this] () { return kPitchLowDefault; },
                         [this] () { return uneditedSettingsProperties.getPitchLow (); });

    // 0: 0V = 100 % -5 = 0 % +5 = 200 %
    // 1: 0V = 10 % +5 = 100 %
    setupComboBox ({ velocityUnipolarComboBox, velocityUnipolarLabel, "Velocity Unipolar", "", "Velocity Unipolar" },
                      { { "0%-100%-200%", 1 },
                        { "0%-100%", 2 } },
                      [this] ()
                      {
                          velocityUnipolarUiChanged (velocityUnipolarComboBox.getSelectedId () - 1);
                      },
                      [this] (int valueOffset)
                      {
                          const auto velocityUnipolar { velocityUnipolarComboBox.getSelectedId () - 1 };
                          settingsProperties.setVelocityUnipolar (std::clamp (velocityUnipolar + valueOffset, 0, 1), true);
                      },
                      [this] () { return kVelocityUnipolarDefault; },
                      [this] () { return uneditedSettingsProperties.getVelocityUnipolar () + 1; });

    auto setupHeaderLabel = [this] (juce::Label& label, const juce::String& text, float fontHeight)
        {
            label.setText (text, juce::dontSendNotification);
            label.setJustificationType (juce::Justification::centredLeft);
            label.setColour (juce::Label::textColourId, juce::Colours::white.withAlpha (0.92f));
            label.setFont (juce::Font (fontHeight, juce::Font::bold));
            addAndMakeVisible (label);
        };

    setupHeaderLabel (accentHeaderLabel, "Accent", 16.0f);
    setupHeaderLabel (accentOpenedHeaderLabel, "Opened", 14.0f);
    setupHeaderLabel (accentClosedHeaderLabel, "Closed", 14.0f);

    setupHeaderLabel (closedHeaderLabel, "Closed", 16.0f);

    setupHeaderLabel (cvHeaderLabel, "CV", 16.0f);

    setupHeaderLabel (envelopeHeaderLabel, "Envelope", 16.0f);
    setupHeaderLabel (feelHeaderLabel, "Feel", 16.0f);

    setupHeaderLabel (filterHeaderLabel, "Filter", 16.0f);
    setupHeaderLabel (filterHpfHeaderLabel, "HPF", 14.0f);
    setupHeaderLabel (filterLpfHeaderLabel, "LPF", 14.0f);

    setupHeaderLabel (pitchHeaderLabel, "Pitch", 16.0f);
    setupHeaderLabel (utilityHeaderLabel, "Utility", 16.0f);

    setupHeaderLabel (chorusHeaderLabel, "FX Chorus", 16.0f);

    setupHeaderLabel (djFilterHeaderLabel, "FX DJ Filter", 16.0f);
    setupHeaderLabel (djFilterHpfHeaderLabel, "HPF", 14.0f);
    setupHeaderLabel (djFilterLpfHeaderLabel, "LPF", 14.0f);
    setupHeaderLabel (djFilterQHeaderLabel, "Q", 14.0f);

    setupHeaderLabel (dubEchoHeaderLabel, "FX Dub Echo", 16.0f);

    setupHeaderLabel (reverbHeaderLabel, "FX Reverb", 16.0f);

    setupHeaderLabel (glitchHeaderLabel, "FX Glitch", 16.0f);
    setupHeaderLabel (glitchCrushHeaderLabel, "Crush", 14.0f);
    setupHeaderLabel (glitchDropHeaderLabel, "Drop", 14.0f);
    setupHeaderLabel (glitchMicroloopHeaderLabel, "Microloop", 14.0f);
    setupHeaderLabel (glitchProbabilityHeaderLabel, "Probability", 14.0f);
    setupHeaderLabel (glitchStutterHeaderLabel, "Stutter", 14.0f);
    setupHeaderLabel (glitchWeightsHeaderLabel, "Weights", 14.0f);
}

SettingsEditorComponent::~SettingsEditorComponent ()
{
}

void SettingsEditorComponent::init (juce::ValueTree rootPropertiesVT)
{
    RuntimeRootProperties runtimeRootProperties (rootPropertiesVT, ValueTreeWrapper<RuntimeRootProperties>::WrapperType::client, ValueTreeWrapper<RuntimeRootProperties>::EnableCallbacks::no);
    ClutchProperties uneditedClutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "unedited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    uneditedSettingsProperties.wrap (uneditedClutchProperties.getValueTree ().getChildWithName ("HiHat"), ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::yes);
    ClutchProperties clutchProperties (runtimeRootProperties.getValueTree ().getChildWithProperty (ClutchProperties::NamePropertyId, "edited"), ValueTreeWrapper<ClutchProperties>::WrapperType::client, ValueTreeWrapper<ClutchProperties>::EnableCallbacks::no);
    settingsProperties.wrap (clutchProperties.getValueTree ().getChildWithName ("HiHat"), ValueTreeWrapper<SettingsProperties>::WrapperType::client, ValueTreeWrapper<SettingsProperties>::EnableCallbacks::yes);

    // initialize fields when data first attached
    pitchLowDataChanged (settingsProperties.getPitchLow ());
    pitchHighDataChanged (settingsProperties.getPitchHigh ());
    envelopeMaxReleaseDataChanged (settingsProperties.getEnvelopeMaxRelease ());
    chokeReleaseDataChanged (settingsProperties.getChokeRelease ());
    clsdReleaseModeDataChanged (settingsProperties.getClsdReleaseMode ());
    clsdRelOfstScaleDataChanged (settingsProperties.getClsdRelOfstScale ());
    clsdMaxReleaseDataChanged (settingsProperties.getClsdMaxRelease ());
    accClRelModDataChanged (settingsProperties.getAccClRelMod ());
    accOpRelModDataChanged (settingsProperties.getAccOpRelMod ());
    accClAmpModDataChanged (settingsProperties.getAccClAmpMod ());
    accOpAmpModDataChanged (settingsProperties.getAccOpAmpMod ());
    fxCvUnipolarDataChanged (settingsProperties.getFxCvUnipolar ());
    velocityUnipolarDataChanged (settingsProperties.getVelocityUnipolar ());
    cvDisableVelocityDataChanged (settingsProperties.getCvDisableVelocity ());
    cvDisableFxDataChanged (settingsProperties.getCvDisableFx ());
    gateModeDataChanged (settingsProperties.getGateMode ());
    feelAttackModDataChanged (settingsProperties.getFeelAttackMod ());
    feelReleaseModDataChanged (settingsProperties.getFeelReleaseMod ());
    feelAmpModDataChanged (settingsProperties.getFeelAmpMod ());
    knobPosTakeupDataChanged (settingsProperties.getKnobPosTakeup ());
    fltrHpfMinFreqDataChanged (settingsProperties.getFltrHpfMinFreq ());
    fltrHpfMaxFreqDataChanged (settingsProperties.getFltrHpfMaxFreq ());
    fltrLpfMinFreqDataChanged (settingsProperties.getFltrLpfMinFreq ());
    fltrLpfMaxFreqDataChanged (settingsProperties.getFltrLpfMaxFreq ());
    fltrHpfQDataChanged (settingsProperties.getFltrHpfQ ());
    fltrLpfQDataChanged (settingsProperties.getFltrLpfQ ());
    fxDjfilterHpfMinDataChanged (settingsProperties.getFxDjfilterHpfMin ());
    fxDjfilterHpfMaxDataChanged (settingsProperties.getFxDjfilterHpfMax ());
    fxDjfilterLpfMinDataChanged (settingsProperties.getFxDjfilterLpfMin ());
    fxDjfilterLpfMaxDataChanged (settingsProperties.getFxDjfilterLpfMax ());
    fxDjfilterQMinDataChanged (settingsProperties.getFxDjfilterQMin ());
    fxDjfilterQMaxDataChanged (settingsProperties.getFxDjfilterQMax ());
    fxDjfilterQGainReductionDataChanged (settingsProperties.getFxDjfilterQGainReduction ());
    fxDubEchoTminDataChanged (settingsProperties.getFxDubEchoTmin ());
    fxDubEchoHpfDataChanged (settingsProperties.getFxDubEchoHpf ());
    fxDubEchoLpfDataChanged (settingsProperties.getFxDubEchoLpf ());
    fxDubEchoMixDataChanged (settingsProperties.getFxDubEchoMix ());
    fxChorusCenterDataChanged (settingsProperties.getFxChorusCenter ());
    fxChorusDepthDataChanged (settingsProperties.getFxChorusDepth ());
    fxChorusMixDataChanged (settingsProperties.getFxChorusMix ());
    fxChorusSpreadDataChanged (settingsProperties.getFxChorusSpread ());
    fxChorusTapsDataChanged (settingsProperties.getFxChorusTaps ());
    fxChorusLfoBDataChanged (settingsProperties.getFxChorusLfoB ());
    fxChorusLfoTDataChanged (settingsProperties.getFxChorusLfoT ());
    fxReverbLpfDataChanged (settingsProperties.getFxReverbLpf ());
    fxReverbHpfDataChanged (settingsProperties.getFxReverbHpf ());
    fxGlitchProbabilityMinDataChanged (settingsProperties.getFxGlitchProbabilityMin ());
    fxGlitchProbabilityMaxDataChanged (settingsProperties.getFxGlitchProbabilityMax ());
    fxGlitchWeightHoldLowDataChanged (settingsProperties.getFxGlitchWeightHoldLow ());
    fxGlitchWeightStutterLowDataChanged (settingsProperties.getFxGlitchWeightStutterLow ());
    fxGlitchWeightCrushLowDataChanged (settingsProperties.getFxGlitchWeightCrushLow ());
    fxGlitchWeightDropLowDataChanged (settingsProperties.getFxGlitchWeightDropLow ());
    fxGlitchWeightHoldHighDataChanged (settingsProperties.getFxGlitchWeightHoldHigh ());
    fxGlitchWeightStutterHighDataChanged (settingsProperties.getFxGlitchWeightStutterHigh ());
    fxGlitchWeightCrushHighDataChanged (settingsProperties.getFxGlitchWeightCrushHigh ());
    fxGlitchWeightDropHighDataChanged (settingsProperties.getFxGlitchWeightDropHigh ());
    fxGlitchDropKeepLevelMinDataChanged (settingsProperties.getFxGlitchDropKeepLevelMin ());
    fxGlitchDropKeepLevelMaxDataChanged (settingsProperties.getFxGlitchDropKeepLevelMax ());
    fxGlitchDropKeepTimeMinDataChanged (settingsProperties.getFxGlitchDropKeepTimeMin ());
    fxGlitchDropKeepTimeMaxDataChanged (settingsProperties.getFxGlitchDropKeepTimeMax ());
    fxGlitchCrushTimeMinDataChanged (settingsProperties.getFxGlitchCrushTimeMin ());
    fxGlitchCrushTimeMaxDataChanged (settingsProperties.getFxGlitchCrushTimeMax ());
    fxGlitchMicroloopSmplTMinDataChanged (settingsProperties.getFxGlitchMicroloopSmplTMin ());
    fxGlitchMicroloopSmplTMaxDataChanged (settingsProperties.getFxGlitchMicroloopSmplTMax ());
    fxGlitchMicroloopPlayTMinDataChanged (settingsProperties.getFxGlitchMicroloopPlayTMin ());
    fxGlitchMicroloopPlayTMaxDataChanged (settingsProperties.getFxGlitchMicroloopPlayTMax ());
    fxGlitchStutterSmplTMinDataChanged (settingsProperties.getFxGlitchStutterSmplTMin ());
    fxGlitchStutterSmplTMaxDataChanged (settingsProperties.getFxGlitchStutterSmplTMax ());
    fxGlitchStutterNumMinDataChanged (settingsProperties.getFxGlitchStutterNumMin ());
    fxGlitchStutterNumMaxDataChanged (settingsProperties.getFxGlitchStutterNumMax ());
    fxGlitchStutterWindowDataChanged (settingsProperties.getFxGlitchStutterWindow ());

    initializeCallbacks ();
}

void SettingsEditorComponent::initializeCallbacks ()
{
    jassert (settingsProperties.isValid ());
    settingsProperties.onPitchLowChange = [this] (float value) { pitchLowDataChanged (value); };
    settingsProperties.onPitchHighChange = [this] (float value) { pitchHighDataChanged (value); };
    settingsProperties.onEnvelopeMaxReleaseChange = [this] (float value) { envelopeMaxReleaseDataChanged (value); };
    settingsProperties.onChokeReleaseChange = [this] (float value) { chokeReleaseDataChanged (value); };
    settingsProperties.onClsdReleaseModeChange = [this] (int value) { clsdReleaseModeDataChanged (value); };
    settingsProperties.onClsdRelOfstScaleChange = [this] (float value) { clsdRelOfstScaleDataChanged (value); };
    settingsProperties.onClsdMaxReleaseChange = [this] (float value) { clsdMaxReleaseDataChanged (value); };
    settingsProperties.onAccClRelModChange = [this] (float value) { accClRelModDataChanged (value); };
    settingsProperties.onAccOpRelModChange = [this] (float value) { accOpRelModDataChanged (value); };
    settingsProperties.onAccClAmpModChange = [this] (float value) { accClAmpModDataChanged (value); };
    settingsProperties.onAccOpAmpModChange = [this] (float value) { accOpAmpModDataChanged (value); };
    settingsProperties.onFeelAttackModChange = [this] (float value) { feelAttackModDataChanged (value); };
    settingsProperties.onFeelReleaseModChange = [this] (float value) { feelReleaseModDataChanged (value); };
    settingsProperties.onFeelAmpModChange = [this] (float value) { feelAmpModDataChanged (value); };
    settingsProperties.onFxCvUnipolarChange = [this] (int value) { fxCvUnipolarDataChanged (value); };
    settingsProperties.onVelocityUnipolarChange = [this] (int value) { velocityUnipolarDataChanged (value); };
    settingsProperties.onCvDisableVelocityChange = [this] (int value) { cvDisableVelocityDataChanged (value); };
    settingsProperties.onCvDisableFxChange = [this] (int value) { cvDisableFxDataChanged (value); };
    settingsProperties.onGateModeChange = [this] (int value) { gateModeDataChanged (value); };
    settingsProperties.onKnobPosTakeupChange = [this] (int value) { knobPosTakeupDataChanged (value); };
    settingsProperties.onFltrHpfMinFreqChange = [this] (int value) { fltrHpfMinFreqDataChanged (value); };
    settingsProperties.onFltrHpfMaxFreqChange = [this] (int value) { fltrHpfMaxFreqDataChanged (value); };
    settingsProperties.onFltrLpfMinFreqChange = [this] (int value) { fltrLpfMinFreqDataChanged (value); };
    settingsProperties.onFltrLpfMaxFreqChange = [this] (int value) { fltrLpfMaxFreqDataChanged (value); };
    settingsProperties.onFltrHpfQChange = [this] (float value) { fltrHpfQDataChanged (value); };
    settingsProperties.onFltrLpfQChange = [this] (float value) { fltrLpfQDataChanged (value); };
    settingsProperties.onFxDjfilterHpfMinChange = [this] (int value) { fxDjfilterHpfMinDataChanged (value); };
    settingsProperties.onFxDjfilterHpfMaxChange = [this] (int value) { fxDjfilterHpfMaxDataChanged (value); };
    settingsProperties.onFxDjfilterLpfMinChange = [this] (int value) { fxDjfilterLpfMinDataChanged (value); };
    settingsProperties.onFxDjfilterLpfMaxChange = [this] (int value) { fxDjfilterLpfMaxDataChanged (value); };
    settingsProperties.onFxDjfilterQMinChange = [this] (float value) { fxDjfilterQMinDataChanged (value); };
    settingsProperties.onFxDjfilterQMaxChange = [this] (float value) { fxDjfilterQMaxDataChanged (value); };
    settingsProperties.onFxDjfilterQGainReductionChange = [this] (float value) { fxDjfilterQGainReductionDataChanged (value); };
    settingsProperties.onFxDubEchoTminChange = [this] (int value) { fxDubEchoTminDataChanged (value); };
    settingsProperties.onFxDubEchoHpfChange = [this] (int value) { fxDubEchoHpfDataChanged (value); };
    settingsProperties.onFxDubEchoLpfChange = [this] (int value) { fxDubEchoLpfDataChanged (value); };
    settingsProperties.onFxDubEchoMixChange = [this] (float value) { fxDubEchoMixDataChanged (value); };
    settingsProperties.onFxChorusCenterChange = [this] (float value) { fxChorusCenterDataChanged (value); };
    settingsProperties.onFxChorusDepthChange = [this] (float value) { fxChorusDepthDataChanged (value); };
    settingsProperties.onFxChorusMixChange = [this] (float value) { fxChorusMixDataChanged (value); };
    settingsProperties.onFxChorusSpreadChange = [this] (float value) { fxChorusSpreadDataChanged (value); };
    settingsProperties.onFxChorusTapsChange = [this] (int value) { fxChorusTapsDataChanged (value); };
    settingsProperties.onFxChorusLfoBChange = [this] (float value) { fxChorusLfoBDataChanged (value); };
    settingsProperties.onFxChorusLfoTChange = [this] (float value) { fxChorusLfoTDataChanged (value); };
    settingsProperties.onFxReverbLpfChange = [this] (int value) { fxReverbLpfDataChanged (value); };
    settingsProperties.onFxReverbHpfChange = [this] (int value) { fxReverbHpfDataChanged (value); };
    settingsProperties.onFxGlitchProbabilityMinChange = [this] (float value) { fxGlitchProbabilityMinDataChanged (value); };
    settingsProperties.onFxGlitchProbabilityMaxChange = [this] (float value) { fxGlitchProbabilityMaxDataChanged (value); };
    settingsProperties.onFxGlitchWeightHoldLowChange = [this] (float value) { fxGlitchWeightHoldLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightStutterLowChange = [this] (float value) { fxGlitchWeightStutterLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightCrushLowChange = [this] (float value) { fxGlitchWeightCrushLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightDropLowChange = [this] (float value) { fxGlitchWeightDropLowDataChanged (value); };
    settingsProperties.onFxGlitchWeightHoldHighChange = [this] (float value) { fxGlitchWeightHoldHighDataChanged (value); };
    settingsProperties.onFxGlitchWeightStutterHighChange = [this] (float value) { fxGlitchWeightStutterHighDataChanged (value); };
    settingsProperties.onFxGlitchWeightCrushHighChange = [this] (float value) { fxGlitchWeightCrushHighDataChanged (value); };
    settingsProperties.onFxGlitchWeightDropHighChange = [this] (float value) { fxGlitchWeightDropHighDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepLevelMinChange = [this] (float value) { fxGlitchDropKeepLevelMinDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepLevelMaxChange = [this] (float value) { fxGlitchDropKeepLevelMaxDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepTimeMinChange = [this] (float value) { fxGlitchDropKeepTimeMinDataChanged (value); };
    settingsProperties.onFxGlitchDropKeepTimeMaxChange = [this] (float value) { fxGlitchDropKeepTimeMaxDataChanged (value); };
    settingsProperties.onFxGlitchCrushTimeMinChange = [this] (float value) { fxGlitchCrushTimeMinDataChanged (value); };
    settingsProperties.onFxGlitchCrushTimeMaxChange = [this] (float value) { fxGlitchCrushTimeMaxDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopSmplTMinChange = [this] (float value) { fxGlitchMicroloopSmplTMinDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopSmplTMaxChange = [this] (float value) { fxGlitchMicroloopSmplTMaxDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopPlayTMinChange = [this] (float value) { fxGlitchMicroloopPlayTMinDataChanged (value); };
    settingsProperties.onFxGlitchMicroloopPlayTMaxChange = [this] (float value) { fxGlitchMicroloopPlayTMaxDataChanged (value); };
    settingsProperties.onFxGlitchStutterSmplTMinChange = [this] (float value) { fxGlitchStutterSmplTMinDataChanged (value); };
    settingsProperties.onFxGlitchStutterSmplTMaxChange = [this] (float value) { fxGlitchStutterSmplTMaxDataChanged (value); };
    settingsProperties.onFxGlitchStutterNumMinChange = [this] (int value) { fxGlitchStutterNumMinDataChanged (value); };
    settingsProperties.onFxGlitchStutterNumMaxChange = [this] (int value) { fxGlitchStutterNumMaxDataChanged (value); };
    settingsProperties.onFxGlitchStutterWindowChange = [this] (int value) { fxGlitchStutterWindowDataChanged (value); };
}

void SettingsEditorComponent::pitchLowDataChanged (float value)
{
    pitchLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::pitchLowUiChanged (float value)
{
    settingsProperties.setPitchLow (value, false);
}

void SettingsEditorComponent::pitchHighDataChanged (float value)
{
    pitchHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::pitchHighUiChanged (float value)
{
    settingsProperties.setPitchHigh (value, false);
}

void SettingsEditorComponent::envelopeMaxReleaseDataChanged (float value)
{
    envelopeMaxReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::envelopeMaxReleaseUiChanged (float value)
{
    settingsProperties.setEnvelopeMaxRelease (value, false);
}

void SettingsEditorComponent::chokeReleaseDataChanged (float value)
{
    chokeReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::chokeReleaseUiChanged (float value)
{
    settingsProperties.setChokeRelease (value, false);
}

void SettingsEditorComponent::clsdReleaseModeDataChanged (int value)
{
    clsdReleaseModeComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::clsdReleaseModeUiChanged (int value)
{
    settingsProperties.setClsdReleaseMode (value, false);
}

void SettingsEditorComponent::clsdRelOfstScaleDataChanged (float value)
{
    clsdRelOfstScaleEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::clsdRelOfstScaleUiChanged (float value)
{
    settingsProperties.setClsdRelOfstScale (value, false);
}

void SettingsEditorComponent::clsdMaxReleaseDataChanged (float value)
{
    clsdMaxReleaseEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::clsdMaxReleaseUiChanged (float value)
{
    settingsProperties.setClsdMaxRelease (value, false);
}

void SettingsEditorComponent::accClRelModDataChanged (float value)
{
    accClRelModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accClRelModUiChanged (float value)
{
    settingsProperties.setAccClRelMod (value, false);
}

void SettingsEditorComponent::accOpRelModDataChanged (float value)
{
    accOpRelModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accOpRelModUiChanged (float value)
{
    settingsProperties.setAccOpRelMod (value, false);
}

void SettingsEditorComponent::accClAmpModDataChanged (float value)
{
    accClAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accClAmpModUiChanged (float value)
{
    settingsProperties.setAccClAmpMod (value, false);
}

void SettingsEditorComponent::accOpAmpModDataChanged (float value)
{
    accOpAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::accOpAmpModUiChanged (float value)
{
    settingsProperties.setAccOpAmpMod (value, false);
}

void SettingsEditorComponent::feelAttackModDataChanged (float value)
{
    feelAttackModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::feelAttackModUiChanged (float value)
{
    settingsProperties.setFeelAttackMod (value, false);
}

void SettingsEditorComponent::feelReleaseModDataChanged (float value)
{
    feelReleaseModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::feelReleaseModUiChanged (float value)
{
    settingsProperties.setFeelReleaseMod (value, false);
}

void SettingsEditorComponent::feelAmpModDataChanged (float value)
{
    feelAmpModEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::feelAmpModUiChanged (float value)
{
    settingsProperties.setFeelAmpMod (value, false);
}

void SettingsEditorComponent::fxCvUnipolarDataChanged (int value)
{
    fxCvUnipolarComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::fxCvUnipolarUiChanged (int value)
{
    settingsProperties.setFxCvUnipolar (value, false);
}

void SettingsEditorComponent::velocityUnipolarDataChanged (int value)
{
    velocityUnipolarComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::velocityUnipolarUiChanged (int value)
{
    settingsProperties.setVelocityUnipolar (value, false);
}

void SettingsEditorComponent::cvDisableVelocityDataChanged (int value)
{
    cvDisableVelocityComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::cvDisableVelocityUiChanged (int value)
{
    settingsProperties.setCvDisableVelocity (value, false);
}

void SettingsEditorComponent::cvDisableFxDataChanged (int value)
{
    cvDisableFxComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::cvDisableFxUiChanged (int value)
{
    settingsProperties.setCvDisableFx (value, false);
}

void SettingsEditorComponent::gateModeDataChanged (int value)
{
    gateModeComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::gateModeUiChanged (int value)
{
    settingsProperties.setGateMode (value, false);
}

void SettingsEditorComponent::knobPosTakeupDataChanged (int value)
{
    knobPosTakeupComboBox.setSelectedId (value + 1, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::knobPosTakeupUiChanged (int value)
{
    settingsProperties.setKnobPosTakeup (value, false);
}

void SettingsEditorComponent::fltrHpfMinFreqDataChanged (int value)
{
    fltrHpfMinFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrHpfMinFreqUiChanged (int value)
{
    settingsProperties.setFltrHpfMinFreq (value, false);
}

void SettingsEditorComponent::fltrHpfMaxFreqDataChanged (int value)
{
    fltrHpfMaxFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrHpfMaxFreqUiChanged (int value)
{
    settingsProperties.setFltrHpfMaxFreq (value, false);
}

void SettingsEditorComponent::fltrLpfMinFreqDataChanged (int value)
{
    fltrLpfMinFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrLpfMinFreqUiChanged (int value)
{
    settingsProperties.setFltrLpfMinFreq (value, false);
}

void SettingsEditorComponent::fltrLpfMaxFreqDataChanged (int value)
{
    fltrLpfMaxFreqEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrLpfMaxFreqUiChanged (int value)
{
    settingsProperties.setFltrLpfMaxFreq (value, false);
}

void SettingsEditorComponent::fltrHpfQDataChanged (float value)
{
    fltrHpfQEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrHpfQUiChanged (float value)
{
    settingsProperties.setFltrHpfQ (value, false);
}

void SettingsEditorComponent::fltrLpfQDataChanged (float value)
{
    fltrLpfQEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fltrLpfQUiChanged (float value)
{
    settingsProperties.setFltrLpfQ (value, false);
}

void SettingsEditorComponent::fxDjfilterHpfMinDataChanged (int value)
{
    fxDjfilterHpfMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterHpfMinUiChanged (int value)
{
    settingsProperties.setFxDjfilterHpfMin (value, false);
}

void SettingsEditorComponent::fxDjfilterHpfMaxDataChanged (int value)
{
    fxDjfilterHpfMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterHpfMaxUiChanged (int value)
{
    settingsProperties.setFxDjfilterHpfMax (value, false);
}

void SettingsEditorComponent::fxDjfilterLpfMinDataChanged (int value)
{
    fxDjfilterLpfMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterLpfMinUiChanged (int value)
{
    settingsProperties.setFxDjfilterLpfMin (value, false);
}

void SettingsEditorComponent::fxDjfilterLpfMaxDataChanged (int value)
{
    fxDjfilterLpfMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterLpfMaxUiChanged (int value)
{
    settingsProperties.setFxDjfilterLpfMax (value, false);
}

void SettingsEditorComponent::fxDjfilterQMinDataChanged (float value)
{
    fxDjfilterQMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterQMinUiChanged (float value)
{
    settingsProperties.setFxDjfilterQMin (value, false);
}

void SettingsEditorComponent::fxDjfilterQMaxDataChanged (float value)
{
    fxDjfilterQMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterQMaxUiChanged (float value)
{
    settingsProperties.setFxDjfilterQMax (value, false);
}

void SettingsEditorComponent::fxDjfilterQGainReductionDataChanged (float value)
{
    fxDjfilterQGainReductionEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDjfilterQGainReductionUiChanged (float value)
{
    settingsProperties.setFxDjfilterQGainReduction (value, false);
}

void SettingsEditorComponent::fxDubEchoTminDataChanged (int value)
{
    fxDubEchoTminEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoTminUiChanged (int value)
{
    settingsProperties.setFxDubEchoTmin (value, false);
}

void SettingsEditorComponent::fxDubEchoHpfDataChanged (int value)
{
    fxDubEchoHpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoHpfUiChanged (int value)
{
    settingsProperties.setFxDubEchoHpf (value, false);
}

void SettingsEditorComponent::fxDubEchoLpfDataChanged (int value)
{
    fxDubEchoLpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoLpfUiChanged (int value)
{
    settingsProperties.setFxDubEchoLpf (value, false);
}

void SettingsEditorComponent::fxDubEchoMixDataChanged (float value)
{
    fxDubEchoMixEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxDubEchoMixUiChanged (float value)
{
    settingsProperties.setFxDubEchoMix (value, false);
}

void SettingsEditorComponent::fxChorusCenterDataChanged (float value)
{
    fxChorusCenterEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusCenterUiChanged (float value)
{
    settingsProperties.setFxChorusCenter (value, false);
}

void SettingsEditorComponent::fxChorusDepthDataChanged (float value)
{
    fxChorusDepthEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusDepthUiChanged (float value)
{
    settingsProperties.setFxChorusDepth (value, false);
}

void SettingsEditorComponent::fxChorusMixDataChanged (float value)
{
    fxChorusMixEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusMixUiChanged (float value)
{
    settingsProperties.setFxChorusMix (value, false);
}

void SettingsEditorComponent::fxChorusSpreadDataChanged (float value)
{
    fxChorusSpreadEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusSpreadUiChanged (float value)
{
    settingsProperties.setFxChorusSpread (value, false);
}

void SettingsEditorComponent::fxChorusTapsDataChanged (int value)
{
    fxChorusTapsComboBox.setSelectedId (value, juce::NotificationType::dontSendNotification);
}

void SettingsEditorComponent::fxChorusTapsUiChanged (int value)
{
    settingsProperties.setFxChorusTaps (value, false);
}

void SettingsEditorComponent::fxChorusLfoBDataChanged (float value)
{
    fxChorusLfoBEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusLfoBUiChanged (float value)
{
    settingsProperties.setFxChorusLfoB (value, false);
}

void SettingsEditorComponent::fxChorusLfoTDataChanged (float value)
{
    fxChorusLfoTEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxChorusLfoTUiChanged (float value)
{
    settingsProperties.setFxChorusLfoT (value, false);
}

void SettingsEditorComponent::fxReverbLpfDataChanged (int value)
{
    fxReverbLpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxReverbLpfUiChanged (int value)
{
    settingsProperties.setFxReverbLpf (value, false);
}

void SettingsEditorComponent::fxReverbHpfDataChanged (int value)
{
    fxReverbHpfEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxReverbHpfUiChanged (int value)
{
    settingsProperties.setFxReverbHpf (value, false);
}

void SettingsEditorComponent::fxGlitchProbabilityMinDataChanged (float value)
{
    fxGlitchProbabilityMinEditor.setText (getRoundedFloatString (value, 5), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchProbabilityMinUiChanged (float value)
{
    settingsProperties.setFxGlitchProbabilityMin (value, false);
}

void SettingsEditorComponent::fxGlitchProbabilityMaxDataChanged (float value)
{
    fxGlitchProbabilityMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchProbabilityMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchProbabilityMax (value, false);
}

void SettingsEditorComponent::fxGlitchWeightHoldLowDataChanged (float value)
{
    fxGlitchWeightHoldLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightHoldLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightHoldLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightStutterLowDataChanged (float value)
{
    fxGlitchWeightStutterLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightStutterLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightStutterLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightCrushLowDataChanged (float value)
{
    fxGlitchWeightCrushLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightCrushLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightCrushLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightDropLowDataChanged (float value)
{
    fxGlitchWeightDropLowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightDropLowUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightDropLow (value, false);
}

void SettingsEditorComponent::fxGlitchWeightHoldHighDataChanged (float value)
{
    fxGlitchWeightHoldHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightHoldHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightHoldHigh (value, false);
}

void SettingsEditorComponent::fxGlitchWeightStutterHighDataChanged (float value)
{
    fxGlitchWeightStutterHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightStutterHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightStutterHigh (value, false);
}

void SettingsEditorComponent::fxGlitchWeightCrushHighDataChanged (float value)
{
    fxGlitchWeightCrushHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightCrushHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightCrushHigh (value, false);
}

void SettingsEditorComponent::fxGlitchWeightDropHighDataChanged (float value)
{
    fxGlitchWeightDropHighEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchWeightDropHighUiChanged (float value)
{
    settingsProperties.setFxGlitchWeightDropHigh (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMinDataChanged (float value)
{
    fxGlitchDropKeepLevelMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMinUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepLevelMin (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMaxDataChanged (float value)
{
    fxGlitchDropKeepLevelMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepLevelMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepLevelMax (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMinDataChanged (float value)
{
    fxGlitchDropKeepTimeMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMinUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepTimeMin (value, false);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMaxDataChanged (float value)
{
    fxGlitchDropKeepTimeMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchDropKeepTimeMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchDropKeepTimeMax (value, false);
}

void SettingsEditorComponent::fxGlitchCrushTimeMinDataChanged (float value)
{
    fxGlitchCrushTimeMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchCrushTimeMinUiChanged (float value)
{
    settingsProperties.setFxGlitchCrushTimeMin (value, false);
}

void SettingsEditorComponent::fxGlitchCrushTimeMaxDataChanged (float value)
{
    fxGlitchCrushTimeMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchCrushTimeMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchCrushTimeMax (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMinDataChanged (float value)
{
    fxGlitchMicroloopSmplTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMinUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopSmplTMin (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMaxDataChanged (float value)
{
    fxGlitchMicroloopSmplTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopSmplTMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopSmplTMax (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMinDataChanged (float value)
{
    fxGlitchMicroloopPlayTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMinUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopPlayTMin (value, false);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMaxDataChanged (float value)
{
    fxGlitchMicroloopPlayTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchMicroloopPlayTMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchMicroloopPlayTMax (value, false);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMinDataChanged (float value)
{
    fxGlitchStutterSmplTMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMinUiChanged (float value)
{
    settingsProperties.setFxGlitchStutterSmplTMin (value, false);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMaxDataChanged (float value)
{
    fxGlitchStutterSmplTMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterSmplTMaxUiChanged (float value)
{
    settingsProperties.setFxGlitchStutterSmplTMax (value, false);
}

void SettingsEditorComponent::fxGlitchStutterNumMinDataChanged (int value)
{
    fxGlitchStutterNumMinEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterNumMinUiChanged (int value)
{
    settingsProperties.setFxGlitchStutterNumMin (value, false);
}

void SettingsEditorComponent::fxGlitchStutterNumMaxDataChanged (int value)
{
    fxGlitchStutterNumMaxEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterNumMaxUiChanged (int value)
{
    settingsProperties.setFxGlitchStutterNumMax (value, false);
}

void SettingsEditorComponent::fxGlitchStutterWindowDataChanged (int value)
{
    fxGlitchStutterWindowEditor.setText (juce::String (value), juce::dontSendNotification);
}

void SettingsEditorComponent::fxGlitchStutterWindowUiChanged (int value)
{
    settingsProperties.setFxGlitchStutterWindow (value, false);
}

void SettingsEditorComponent::paint (juce::Graphics& g)
{
    const auto kBackgroundColour { juce::Colour (0xff4a4a4a) };
    const auto kSectionOutlineColour { juce::Colour (0xff6a6a6a) };

    constexpr auto kSectionCornerSize { 4.0f };
    constexpr auto kSectionOutlineThickness { 1.0f };

    constexpr auto kSeparatorInsetX { 0 };
    constexpr auto kSeparatorThickness { 1.0f };

    g.setColour (kSectionOutlineColour.brighter (0.4f));
    for (const auto& box : sectionBoxes)
    {
        g.drawRoundedRectangle (box.toFloat (), kSectionCornerSize, kSectionOutlineThickness);
    }

    auto drawMainHeaderSeparator =
        [&] (const juce::Label& header)
        {
            const auto bounds { header.getBounds () };
            const auto y { bounds.getBottom () };

            g.drawLine ((float) (bounds.getX () + kSeparatorInsetX),
                        (float) y,
                        (float) (bounds.getRight () + 8), // NOTE - hack to get things working. since the line is bring drawn relative to the label, it doesn't know how wide the actual section is
                        (float) y,
                        kSeparatorThickness);
        };

    drawMainHeaderSeparator (accentHeaderLabel);
    drawMainHeaderSeparator (closedHeaderLabel);
    drawMainHeaderSeparator (envelopeHeaderLabel);
    drawMainHeaderSeparator (feelHeaderLabel);
    drawMainHeaderSeparator (cvHeaderLabel);
    drawMainHeaderSeparator (filterHeaderLabel);
    drawMainHeaderSeparator (pitchHeaderLabel);
    drawMainHeaderSeparator (utilityHeaderLabel);
    drawMainHeaderSeparator (chorusHeaderLabel);
    drawMainHeaderSeparator (reverbHeaderLabel);
    drawMainHeaderSeparator (djFilterHeaderLabel);
    drawMainHeaderSeparator (dubEchoHeaderLabel);
    drawMainHeaderSeparator (glitchHeaderLabel);
}

void SettingsEditorComponent::resized ()
{
    struct CompLabelPair
    {
        juce::Component* comp;
        juce::Label* label;
    };

    //==========================================================================
    // Global layout
    //==========================================================================

    constexpr auto kOuterMargin { 10 };

    // (2) Space between each outer column.
    constexpr auto kColumnGap { 5 };

    // (3) Column width.
    // Set to -1 to auto-fit all columns evenly into the available width.
    constexpr auto kFixedColumnWidth { -1 };

    //==========================================================================
    // Section box / inner border controls
    //==========================================================================

    // (4) Inner column borders, left/right and top/bottom.
    // These control the padding between a section box and the content inside it.
    constexpr auto kSectionInnerPadLeft { 1 };
    constexpr auto kSectionInnerPadRight { 8 };
    constexpr auto kSectionInnerPadTop { 5 };
    constexpr auto kSectionInnerPadBottom { 5 };

    // (1) Space between each section.
    // This is the visible gap between section boxes in a column.
    constexpr auto kSectionGap { 5 };

    //==========================================================================
    // Row sizing
    //==========================================================================

    constexpr auto kRowHeight { 20 };
    constexpr auto kRowGap { 2 };
    constexpr auto kRowStride { kRowHeight + kRowGap };

    //==========================================================================
    // Heading sizing
    //==========================================================================

    constexpr auto kSectionHeaderHeight { 24 };
    constexpr auto kSubHeaderHeight { 18 };

    // (5) Space between main heading and subcontent.
    constexpr auto kMainHeaderToContentGap { 2 };

    constexpr auto kSubSectionGap { 5 };

    //==========================================================================
    // Content indents
    //==========================================================================

    constexpr auto kSectionContentIndent { 10 };
    constexpr auto kSubHeaderIndent { 10 };
    constexpr auto kSubsectionContentIndent { 20 };

    //==========================================================================
    // Standard control alignment inside a full column
    //==========================================================================

    constexpr auto kControlGap { 4 };
    constexpr auto kControlWidth { 90 };

    //==========================================================================
    // Glitch section internal layout
    //==========================================================================

    constexpr auto kGlitchColumnGap { 5 };
    constexpr auto kGlitchControlWidth { 60 };
    constexpr auto kGlitchSubHeaderIndent { 8 };
    constexpr auto kGlitchContentIndent { 12 };

    sectionBoxes.clear ();

    auto bounds { getLocalBounds ().reduced (kOuterMargin) };

    auto makeColumns =
        [&] (juce::Rectangle<int> area, int numColumns)
        {
            std::vector<juce::Rectangle<int>> columns;

            const auto totalGap { (numColumns - 1) * kColumnGap };

            int columnWidth { 0 };

            if (kFixedColumnWidth > 0)
            {
                columnWidth = kFixedColumnWidth;
            }
            else
            {
                columnWidth = (area.getWidth () - totalGap) / numColumns;
            }

            for (int i { 0 }; i < numColumns; ++i)
            {
                const auto x { area.getX () + i * (columnWidth + kColumnGap) };
                columns.emplace_back (x, area.getY (), columnWidth, area.getHeight ());
            }

            return columns;
        };

    auto allColumns { makeColumns (bounds, 4) };

    auto leftColumn0Bounds { allColumns [0] };
    auto leftColumn1Bounds { allColumns [1] };
    auto rightColumn0Bounds { allColumns [2] };
    auto rightColumn1Bounds { allColumns [3] };

    auto leftColumn0 { leftColumn0Bounds };
    auto leftColumn1 { leftColumn1Bounds };
    auto rightColumn0 { rightColumn0Bounds };
    auto rightColumn1 { rightColumn1Bounds };

    auto getSectionContentArea =
        [&] (const juce::Rectangle<int>& columnBounds, const juce::Rectangle<int>& runningColumn)
        {
            juce::Rectangle<int> area
            {
                columnBounds.getX () + kSectionInnerPadLeft,
                runningColumn.getY () + kSectionInnerPadTop,
                columnBounds.getWidth () - kSectionInnerPadLeft - kSectionInnerPadRight,
                juce::jmax (0, runningColumn.getBottom () - runningColumn.getY () - kSectionInnerPadTop)
            };

            return area;
        };

    auto positionHeader =
        [] (juce::Label& header, juce::Rectangle<int>& area, int height, int indent = 0)
        {
            header.setBounds (area.getX () + indent, area.getY () - 5, area.getWidth () - indent, height);
            area.removeFromTop (height);
        };

    auto addVerticalGap =
        [] (juce::Rectangle<int>& area, int amount)
        {
            area.removeFromTop (amount);
        };

    auto beginSection =
        [] (const juce::Rectangle<int>& runningColumn)
        {
            return runningColumn.getY ();
        };

    auto finishSection =
        [&] (const juce::Rectangle<int>& columnBounds, juce::Rectangle<int>& runningColumn, int startY, int contentEndY)
        {
            const auto sectionTop { startY };
            const auto sectionBottom { contentEndY + kSectionInnerPadBottom };

            sectionBoxes.emplace_back (
                columnBounds.getX (),
                sectionTop,
                columnBounds.getWidth (),
                juce::jmax (0, sectionBottom - sectionTop));

            runningColumn.setY (sectionBottom + kSectionGap);
            runningColumn.setHeight (juce::jmax (0, columnBounds.getBottom () - runningColumn.getY ()));
        };

    auto getColumnControlX =
        [&] (const juce::Rectangle<int>& contentBounds)
        {
            return contentBounds.getRight () - kControlWidth;
        };

    auto positionRows =
        [&] (juce::Rectangle<int>& area,
             std::initializer_list<CompLabelPair> pairs,
             int indent)
        {
            auto y { area.getY () };
            const auto controlX { getColumnControlX (area) };
            const auto labelX { area.getX () + indent };
            const auto labelWidth { juce::jmax (20, controlX - labelX - kControlGap) };

            for (const auto& pair : pairs)
            {
                pair.label->setBounds (labelX, y, labelWidth, kRowHeight);
                pair.comp->setBounds (controlX, y, kControlWidth, kRowHeight);
                y += kRowStride;
            }

            area.setY (y);
            area.setHeight (juce::jmax (0, area.getBottom () - y));
        };

    //==========================================================================
    // LEFT SIDE
    //==========================================================================

    // Accent
    {
        auto& runningColumn { leftColumn0 };
        const auto& columnBounds { leftColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (accentHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);

        positionHeader (accentOpenedHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &accOpAmpModEditor, &accOpAmpModLabel },
                          { &accOpRelModEditor, &accOpRelModLabel }
                      },
                      kSubsectionContentIndent);

        addVerticalGap (sectionArea, kSubSectionGap);

        positionHeader (accentClosedHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &accClAmpModEditor, &accClAmpModLabel },
                          { &accClRelModEditor, &accClRelModLabel }
                      },
                      kSubsectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Closed
    {
        auto& runningColumn { leftColumn0 };
        const auto& columnBounds { leftColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (closedHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &clsdMaxReleaseEditor, &clsdMaxReleaseLabel },
                          { &clsdRelOfstScaleEditor, &clsdRelOfstScaleLabel },
                          { &clsdReleaseModeComboBox, &clsdReleaseModeLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Envelope
    {
        auto& runningColumn { leftColumn0 };
        const auto& columnBounds { leftColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (envelopeHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &chokeReleaseEditor, &chokeReleaseLabel },
                          { &envelopeMaxReleaseEditor, &envelopeMaxReleaseLabel },
                          { &gateModeComboBox,& gateModeLabel },
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Feel
    {
        auto& runningColumn { leftColumn0 };
        const auto& columnBounds { leftColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (feelHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &feelAmpModEditor, &feelAmpModLabel },
                          { &feelAttackModEditor, &feelAttackModLabel },
                          { &feelReleaseModEditor, &feelReleaseModLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // CV
    {
        auto& runningColumn { leftColumn1 };
        const auto& columnBounds { leftColumn1Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (cvHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &cvDisableFxComboBox, &cvDisableFxLabel },
                          { &cvDisableVelocityComboBox, &cvDisableVelocityLabel },
                          { &fxCvUnipolarComboBox, &fxCvUnipolarLabel },
                          { &velocityUnipolarComboBox, &velocityUnipolarLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Filter
    {
        auto& runningColumn { leftColumn1 };
        const auto& columnBounds { leftColumn1Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (filterHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);

        positionHeader (filterHpfHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &fltrHpfMinFreqEditor, &fltrHpfMinFreqLabel },
                          { &fltrHpfMaxFreqEditor, &fltrHpfMaxFreqLabel },
                          { &fltrHpfQEditor, &fltrHpfQLabel }
                      },
                      kSubsectionContentIndent);

        addVerticalGap (sectionArea, kSubSectionGap);

        positionHeader (filterLpfHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &fltrLpfMinFreqEditor, &fltrLpfMinFreqLabel },
                          { &fltrLpfMaxFreqEditor, &fltrLpfMaxFreqLabel },
                          { &fltrLpfQEditor, &fltrLpfQLabel }
                      },
                      kSubsectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Pitch
    {
        auto& runningColumn { leftColumn1 };
        const auto& columnBounds { leftColumn1Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (pitchHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &pitchLowEditor, &pitchLowLabel },
                          { &pitchHighEditor, &pitchHighLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Utility
    {
        auto& runningColumn { leftColumn1 };
        const auto& columnBounds { leftColumn1Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (utilityHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &knobPosTakeupComboBox, &knobPosTakeupLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    //==========================================================================
    // RIGHT SIDE
    //==========================================================================

    // Chorus
    {
        auto& runningColumn { rightColumn0 };
        const auto& columnBounds { rightColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (chorusHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &fxChorusCenterEditor, &fxChorusCenterLabel },
                          { &fxChorusDepthEditor, &fxChorusDepthLabel },
                          { &fxChorusLfoBEditor, &fxChorusLfoBLabel },
                          { &fxChorusLfoTEditor, &fxChorusLfoTLabel },
                          { &fxChorusMixEditor, &fxChorusMixLabel },
                          { &fxChorusSpreadEditor, &fxChorusSpreadLabel },
                          { &fxChorusTapsComboBox, &fxChorusTapsLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Reverb
    {
        auto& runningColumn { rightColumn0 };
        const auto& columnBounds { rightColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (reverbHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &fxReverbHpfEditor, &fxReverbHpfLabel },
                          { &fxReverbLpfEditor, &fxReverbLpfLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // DJ Filter
    {
        auto& runningColumn { rightColumn0 };
        const auto& columnBounds { rightColumn0Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (djFilterHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);

        positionHeader (djFilterHpfHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &fxDjfilterHpfMinEditor, &fxDjfilterHpfMinLabel },
                          { &fxDjfilterHpfMaxEditor, &fxDjfilterHpfMaxLabel }
                      },
                      kSubsectionContentIndent);

        addVerticalGap (sectionArea, kSubSectionGap);

        positionHeader (djFilterLpfHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &fxDjfilterLpfMinEditor, &fxDjfilterLpfMinLabel },
                          { &fxDjfilterLpfMaxEditor, &fxDjfilterLpfMaxLabel }
                      },
                      kSubsectionContentIndent);

        addVerticalGap (sectionArea, kSubSectionGap);

        positionHeader (djFilterQHeaderLabel, sectionArea, kSubHeaderHeight, kSubHeaderIndent);
        positionRows (sectionArea,
                      {
                          { &fxDjfilterQMinEditor, &fxDjfilterQMinLabel },
                          { &fxDjfilterQMaxEditor, &fxDjfilterQMaxLabel },
                          { &fxDjfilterQGainReductionEditor, &fxDjfilterQGainReductionLabel }
                      },
                      kSubsectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Dub Echo
    {
        auto& runningColumn { rightColumn1 };
        const auto& columnBounds { rightColumn1Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        positionHeader (dubEchoHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);
        positionRows (sectionArea,
                      {
                          { &fxDubEchoHpfEditor, &fxDubEchoHpfLabel },
                          { &fxDubEchoLpfEditor, &fxDubEchoLpfLabel },
                          { &fxDubEchoMixEditor, &fxDubEchoMixLabel },
                          { &fxDubEchoTminEditor, &fxDubEchoTminLabel }
                      },
                      kSectionContentIndent);

        finishSection (columnBounds, runningColumn, startY, sectionArea.getY ());
    }

    // Glitch
    {
        auto& runningColumn { rightColumn1 };
        const auto& columnBounds { rightColumn1Bounds };
        const auto startY { beginSection (runningColumn) };
        auto sectionArea { getSectionContentArea (columnBounds, runningColumn) };

        auto makeGlitchColumns =
            [&] (juce::Rectangle<int> area)
            {
                std::vector<juce::Rectangle<int>> columns;
                const auto columnWidth { (area.getWidth () - kGlitchColumnGap) / 2 };

                columns.emplace_back (area.getX (), area.getY (), columnWidth, area.getHeight ());
                columns.emplace_back (area.getX () + columnWidth + kGlitchColumnGap, area.getY (), columnWidth, area.getHeight ());
                return columns;
            };

        auto positionGlitchRows =
            [&] (juce::Rectangle<int>& area,
                 const juce::Rectangle<int>& subColumnBounds,
                 std::initializer_list<CompLabelPair> pairs,
                 int indent)
            {
                auto y { area.getY () };
                const auto controlX { subColumnBounds.getRight () - kGlitchControlWidth };
                const auto labelX { subColumnBounds.getX () + indent };
                const auto labelWidth { juce::jmax (18, controlX - labelX) };

                for (const auto& pair : pairs)
                {
                    pair.label->setBounds (labelX, y, labelWidth, kRowHeight);
                    pair.comp->setBounds (controlX, y, kGlitchControlWidth, kRowHeight);
                    y += kRowStride;
                }

                area.setY (y);
                area.setHeight (juce::jmax (0, area.getBottom () - y));
            };

        positionHeader (glitchHeaderLabel, sectionArea, kSectionHeaderHeight);
        addVerticalGap (sectionArea, kMainHeaderToContentGap);

        auto glitchColumns { makeGlitchColumns (sectionArea) };
        auto glitchColumn0Bounds { glitchColumns [0] };
        auto glitchColumn1Bounds { glitchColumns [1] };
        auto glitchColumn0 { glitchColumn0Bounds };
        auto glitchColumn1 { glitchColumn1Bounds };

        positionHeader (glitchCrushHeaderLabel, glitchColumn0, kSubHeaderHeight, kGlitchSubHeaderIndent);
        positionGlitchRows (glitchColumn0,
                            glitchColumn0Bounds,
                            {
                                { &fxGlitchCrushTimeMinEditor, &fxGlitchCrushTimeMinLabel },
                                { &fxGlitchCrushTimeMaxEditor, &fxGlitchCrushTimeMaxLabel }
                            },
                            kGlitchContentIndent);

        addVerticalGap (glitchColumn0, kSubSectionGap);

        positionHeader (glitchDropHeaderLabel, glitchColumn0, kSubHeaderHeight, kGlitchSubHeaderIndent);
        positionGlitchRows (glitchColumn0,
                            glitchColumn0Bounds,
                            {
                                { &fxGlitchDropKeepLevelMinEditor, &fxGlitchDropKeepLevelMinLabel },
                                { &fxGlitchDropKeepLevelMaxEditor, &fxGlitchDropKeepLevelMaxLabel },
                                { &fxGlitchDropKeepTimeMinEditor, &fxGlitchDropKeepTimeMinLabel },
                                { &fxGlitchDropKeepTimeMaxEditor, &fxGlitchDropKeepTimeMaxLabel }
                            },
                            kGlitchContentIndent);

        addVerticalGap (glitchColumn0, kSubSectionGap);

        positionHeader (glitchMicroloopHeaderLabel, glitchColumn0, kSubHeaderHeight, kGlitchSubHeaderIndent);
        positionGlitchRows (glitchColumn0,
                            glitchColumn0Bounds,
                            {
                                { &fxGlitchMicroloopPlayTMinEditor, &fxGlitchMicroloopPlayTMinLabel },
                                { &fxGlitchMicroloopPlayTMaxEditor, &fxGlitchMicroloopPlayTMaxLabel },
                                { &fxGlitchMicroloopSmplTMinEditor, &fxGlitchMicroloopSmplTMinLabel },
                                { &fxGlitchMicroloopSmplTMaxEditor, &fxGlitchMicroloopSmplTMaxLabel }
                            },
                            kGlitchContentIndent);

        addVerticalGap (glitchColumn0, kSubSectionGap);

        positionHeader (glitchProbabilityHeaderLabel, glitchColumn0, kSubHeaderHeight, kGlitchSubHeaderIndent);
        positionGlitchRows (glitchColumn0,
                            glitchColumn0Bounds,
                            {
                                { &fxGlitchProbabilityMinEditor, &fxGlitchProbabilityMinLabel },
                                { &fxGlitchProbabilityMaxEditor, &fxGlitchProbabilityMaxLabel }
                            },
                            kGlitchContentIndent);

        positionHeader (glitchStutterHeaderLabel, glitchColumn1, kSubHeaderHeight, kGlitchSubHeaderIndent);
        positionGlitchRows (glitchColumn1,
                            glitchColumn1Bounds,
                            {
                                { &fxGlitchStutterNumMinEditor, &fxGlitchStutterNumMinLabel },
                                { &fxGlitchStutterNumMaxEditor, &fxGlitchStutterNumMaxLabel },
                                { &fxGlitchStutterSmplTMinEditor, &fxGlitchStutterSmplTMinLabel },
                                { &fxGlitchStutterSmplTMaxEditor, &fxGlitchStutterSmplTMaxLabel },
                                { &fxGlitchStutterWindowEditor, &fxGlitchStutterWindowLabel }
                            },
                            kGlitchContentIndent);

        addVerticalGap (glitchColumn1, kSubSectionGap);

        positionHeader (glitchWeightsHeaderLabel, glitchColumn1, kSubHeaderHeight, kGlitchSubHeaderIndent);
        positionGlitchRows (glitchColumn1,
                            glitchColumn1Bounds,
                            {
                                { &fxGlitchWeightCrushLowEditor, &fxGlitchWeightCrushLowLabel },
                                { &fxGlitchWeightCrushHighEditor, &fxGlitchWeightCrushHighLabel },
                                { &fxGlitchWeightDropLowEditor, &fxGlitchWeightDropLowLabel },
                                { &fxGlitchWeightDropHighEditor, &fxGlitchWeightDropHighLabel },
                                { &fxGlitchWeightHoldLowEditor, &fxGlitchWeightHoldLowLabel },
                                { &fxGlitchWeightHoldHighEditor, &fxGlitchWeightHoldHighLabel },
                                { &fxGlitchWeightStutterLowEditor, &fxGlitchWeightStutterLowLabel },
                                { &fxGlitchWeightStutterHighEditor, &fxGlitchWeightStutterHighLabel }
                            },
                            kGlitchContentIndent);

        const auto glitchEndY { juce::jmax (glitchColumn0.getY (), glitchColumn1.getY ()) };
        finishSection (columnBounds, runningColumn, startY, glitchEndY);
    }
}