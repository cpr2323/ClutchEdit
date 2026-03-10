#include "SettingsEditorComponent.h"
#include "../../Clutch/ClutchProperties.h"
#include "../../Utility/RuntimeRootProperties.h"

juce::String getRoundedFloatString (float value, int decimalPlaces)
{
    return juce::String (value, decimalPlaces).trimCharactersAtEnd ("0").trimCharactersAtEnd (".");
}

SettingsEditorComponent::SettingsEditorComponent ()
{
    popupMenuLnF.setColour (juce::PopupMenu::ColourIds::headerTextColourId, juce::Colours::white.withAlpha (0.3f));

	struct EditorFloatData
	{
		CustomTextEditorFloat* editor;
		juce::Label& label;
		const juce::String& labelText;
		juce::String toolTip;
		juce::String menuHeader;
	};

	struct FloatDataRange
	{
		float min;
		float max;
	};

	struct FloatDragMultipliers
	{
		float slow;
		float medium;
		float fast;
	};

	auto setupFloatEditor = [this] (EditorFloatData editorData,
									   FloatDataRange dataRange,
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
			editorData.editor->getMinValueCallback = [minValue = dataRange.min] () { return minValue; };
			editorData.editor->getMaxValueCallback = [maxValue = dataRange.max] () { return maxValue; };
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
				juce::PopupMenu pm;
				pm.setLookAndFeel (&popupMenuLnF);
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
                pm.showMenuAsync ({}, [this, &pm] (int) { pm.setLookAndFeel (nullptr); });
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
				juce::PopupMenu pm;
				pm.setLookAndFeel (&popupMenuLnF);
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
				pm.showMenuAsync ({}, [this, &pm] (int) { pm.setLookAndFeel (nullptr); });
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
									std::function<void (int valueOffset)> updateFromDragCallback,
									std::function<int ()> getDefaultValue,
									std::function<int ()> getUneditedValue)
		{
			jassert (updateFromDragCallback != nullptr);
			jassert (getDefaultValue != nullptr);
			jassert (getUneditedValue != nullptr);

			comboBoxData.comboBox.setLookAndFeel (&noArrowComboBoxLnF);
			comboBoxData.comboBox.setTooltip (comboBoxData.toolTip);
			comboBoxData.comboBox.clear (juce::dontSendNotification);

			for (const auto& menuItem : menuItems)
				comboBoxData.comboBox.addItem (menuItem.text, menuItem.value);

			comboBoxData.comboBox.onDragCallback = [updateFromDragCallback] (DragSpeed dragSpeed, int direction)
			{
				const auto valueOffset { (dragSpeed == DragSpeed::fast ? 2 : 1) * direction };
				updateFromDragCallback (valueOffset);
			};
			comboBoxData.comboBox.onPopupMenuCallback = [this, comboBox = &comboBoxData.comboBox, getDefaultValue, getUneditedValue, menuHeader = comboBoxData.menuHeader] ()
			{
				juce::PopupMenu pm;
				pm.setLookAndFeel (&popupMenuLnF);
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
				pm.showMenuAsync ({}, [this, &pm] (int) { pm.setLookAndFeel (nullptr); });
			};
            comboBoxData.label.setText (comboBoxData.labelText, juce::dontSendNotification);
            comboBoxData.comboBox.setColour (juce::ComboBox::backgroundColourId, juce::Colours::darkgrey.darker (0.5f));
            addAndMakeVisible (comboBoxData.label);
            addAndMakeVisible (comboBoxData.comboBox);
		};

    // THIS IS THE ORIGINAL SETUP CODE
    setupFloatEditor ({ &accClAmpModEditor, accClAmpModLabel, "Acc Cl Amp Mod", "Amp Mod CLOSED ACC hit", "Acc Cl Amp Mod" },
                         { 0.1f, 10.0f },
                         { 0.01f, 0.3f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accClAmpModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccClAmpMod () + valueOffset };
                             accClAmpModEditor.setValue (newValue);
                         },
                         [this] () { return 1.3f; },
                         [this] () { return uneditedSettingsProperties.getAccClAmpMod (); });

    setupFloatEditor ({ &accClRelModEditor, accClRelModLabel, "Acc Cl Rel Mod", "Acc Cl Rel Mod", "Acc Cl Rel Mod" },
                         { 0.1f, 10.0f },
                         { 0.01f, 0.3f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accClRelModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccClRelMod () + valueOffset };
                             accClRelModEditor.setValue (newValue);
                         },
                         [this] () { return 1.18f; },
                         [this] () { return uneditedSettingsProperties.getAccClRelMod (); });

    setupFloatEditor ({ &accOpAmpModEditor, accOpAmpModLabel, "Acc Op Amp Mod", "Acc Op Amp Mod", "Acc Op Amp Mod" },
                         { 0.1f, 10.0f },
                         { 0.1f, 0.5f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accOpAmpModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccOpAmpMod () + valueOffset };
                             accOpAmpModEditor.setValue (newValue);
                         },
                         [this] () { return 1.25f; },
                         [this] () { return uneditedSettingsProperties.getAccOpAmpMod (); });

    setupFloatEditor ({ &accOpRelModEditor, accOpRelModLabel, "Acc Op Rel Mod", "Acc Op Rel Mod", "Acc Op Rel Mod" },
                         { 0.1f, 10.0f },
                         { 0.1f, 0.5f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { accOpRelModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getAccOpRelMod () + valueOffset };
                             accOpRelModEditor.setValue (newValue);
                         },
                         [this] () { return 1.25f; },
                         [this] () { return uneditedSettingsProperties.getAccOpRelMod (); });

    setupFloatEditor ({ &chokeReleaseEditor, chokeReleaseLabel, "Choke Release", "Choke Release", "Choke Release" },
                         { 0.001f, 10.0f },
                         { 0.001f, 0.5f, 3.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { chokeReleaseUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getChokeRelease () + valueOffset };
                             chokeReleaseEditor.setValue (newValue);
                         },
                         [this] () { return 0.08f; },
                         [this] () { return uneditedSettingsProperties.getChokeRelease (); });

    setupFloatEditor ({ &clsdMaxReleaseEditor, clsdMaxReleaseLabel, "Clsd Max Release", "Choke Release", "Clsd Max Release" },
                         { 0.3f, 2.0f },
                         { 0.1f, 0.3f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { clsdMaxReleaseUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getClsdMaxRelease () + valueOffset };
                             clsdMaxReleaseEditor.setValue (newValue);
                         },
                         [this] () { return 0.8f; },
                         [this] () { return uneditedSettingsProperties.getClsdMaxRelease (); });

    setupFloatEditor ({ &clsdRelOfstScaleEditor, clsdRelOfstScaleLabel, "Clsd Rel Ofst Scale", "Choke Release", "Clsd Rel Ofst Scale" },
                         { 0.1f, 0.9f },
                         { 0.1f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { clsdRelOfstScaleUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getClsdRelOfstScale () + valueOffset };
                             clsdRelOfstScaleEditor.setValue (newValue);
                         },
                         [this] () { return 0.5f; },
                         [this] () { return uneditedSettingsProperties.getClsdRelOfstScale (); });

    // 0: Independent Release for Closed
    // 1: Release Offset mode
    setupComboBox ({ clsdReleaseModeComboBox, clsdReleaseModeLabel, "Clsd Release Mode", "", "Clsd Release Mode" },
                      { { "Independent", 1 },
                        { "Offset", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto clsdReleaseMode { clsdReleaseModeComboBox.getSelectedId () - 1 };
                          settingsProperties.setClsdReleaseMode (std::clamp (clsdReleaseMode + valueOffset, 0, 1), true);
                      },
                      [this] () { return 2; },
                      [this] () { return uneditedSettingsProperties.getClsdReleaseMode () + 1; });

    // 0: FX CV Always On
    // 1: CV Disable : Freeze FX CV
    setupComboBox ({ cvDisableFxComboBox, cvDisableFxLabel, "CV Disable FX", "", "CV Disable FX" },
                      { { "FX CV On", 1 },
                        { "FX CV Off", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto cvDisableFx { cvDisableFxComboBox.getSelectedId () - 1 };
                          settingsProperties.setCvDisableFx (std::clamp (cvDisableFx + valueOffset, 0, 1), true);
                      },
                      [this] () { return 1; },
                      [this] () { return uneditedSettingsProperties.getCvDisableFx () + 1; });

    // 0: Velocity always enabled
    // 1: CV Off SW affects velocity
    setupComboBox ({ cvDisableVelocityComboBox, cvDisableVelocityLabel, "CV Disable Velocity", "", "CV Disable Velocity" },
                      { { "Always On", 1 },
                        { "CV Off", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto cvDisableVelocity { cvDisableVelocityComboBox.getSelectedId () - 1 };
                          settingsProperties.setCvDisableVelocity (std::clamp (cvDisableVelocity + valueOffset, 0, 1), true);
                      },
                      [this] () { return 1; },
                      [this] () { return uneditedSettingsProperties.getCvDisableVelocity () + 1; });

    setupFloatEditor ({ &envelopeMaxReleaseEditor, envelopeMaxReleaseLabel, "Envelope Max Release", "Envelope Max Release", "Envelope Max Release" },
                         { 0.6f, 20.0f },
                         { 0.1f, 0.5f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { envelopeMaxReleaseUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getEnvelopeMaxRelease () + valueOffset };
                             envelopeMaxReleaseEditor.setValue (newValue);
                         },
                         [this] () { return 4.0f; },
                         [this] () { return uneditedSettingsProperties.getEnvelopeMaxRelease (); });

    setupFloatEditor ({ &feelAmpModEditor, feelAmpModLabel, "Feel Amp Mod", "Feel Amp Mod", "Feel Amp Mod" },
                         { 0.0f, 2.0f },
                         { 0.1f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { feelAmpModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFeelAmpMod () + valueOffset };
                             feelAmpModEditor.setValue (newValue);
                         },
                         [this] () { return 1.0f; },
                         [this] () { return uneditedSettingsProperties.getFeelAmpMod (); });

    setupFloatEditor ({ &feelAttackModEditor, feelAttackModLabel, "Feel Attack Mod", "Feel Attack Mod", "Feel Attack Mod" },
                         { 0.0f, 5.0f },
                         { 0.1f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { feelAttackModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFeelAttackMod () + valueOffset };
                             feelAttackModEditor.setValue (newValue);
                         },
                         [this] () { return 1.0f; },
                         [this] () { return uneditedSettingsProperties.getFeelAttackMod (); });

    setupFloatEditor ({ &feelReleaseModEditor, feelReleaseModLabel, "Feel Release Mod", "Feel Release Mod", "Feel Release Mod" },
                         { 0.0f, 5.0f },
                         { 0.1f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { feelReleaseModUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFeelReleaseMod () + valueOffset };
                             feelReleaseModEditor.setValue (newValue);
                         },
                         [this] () { return 1.0f; },
                         [this] () { return uneditedSettingsProperties.getFeelReleaseMod (); });

    setupIntEditor ({ &fltrHpfMaxFreqEditor, fltrHpfMaxFreqLabel, "Fltr HPF Max Freq", "Fltr HPF Max Freq", "Fltr HPF Max Freq" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrHpfMaxFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrHpfMaxFreq () + valueOffset };
                           fltrHpfMaxFreqEditor.setValue (newValue);
                       },
                       [this] () { return 14000; },
                       [this] () { return uneditedSettingsProperties.getFltrHpfMaxFreq (); });

    setupIntEditor ({ &fltrHpfMinFreqEditor, fltrHpfMinFreqLabel, "Fltr HPF Min Freq", "Fltr HPF Min Freq", "Fltr HPF Min Freq" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrHpfMinFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrHpfMinFreq () + valueOffset };
                           fltrHpfMinFreqEditor.setValue (newValue);
                       },
                       [this] () { return 100; },
                       [this] () { return uneditedSettingsProperties.getFltrHpfMinFreq (); });

    setupFloatEditor ({ &fltrHpfQEditor, fltrHpfQLabel, "Fltr HPF Q", "Fltr HPF Q", "Fltr HPF Q" },
                         { 0.25f, 4.0f },
                         { 0.001f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fltrHpfQUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFltrHpfQ () + valueOffset };
                             fltrHpfQEditor.setValue (newValue);
                         },
                         [this] () { return 1.0f; },
                         [this] () { return uneditedSettingsProperties.getFltrHpfQ (); });

    setupIntEditor ({ &fltrLpfMaxFreqEditor, fltrLpfMaxFreqLabel, "Fltr LPF Max Freq", "Fltr LPF Max Freq", "Fltr LPF Max Freq" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrLpfMaxFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrLpfMaxFreq () + valueOffset };
                           fltrLpfMaxFreqEditor.setValue (newValue);
                       },
                       [this] () { return 20000; },
                       [this] () { return uneditedSettingsProperties.getFltrLpfMaxFreq (); });

    setupIntEditor ({ &fltrLpfMinFreqEditor, fltrLpfMinFreqLabel, "Fltr LPF Min Freq", "Fltr LPF Min Freq", "Fltr LPF Min Freq" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fltrLpfMinFreqUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFltrLpfMinFreq () + valueOffset };
                           fltrLpfMinFreqEditor.setValue (newValue);
                       },
                       [this] () { return 200; },
                       [this] () { return uneditedSettingsProperties.getFltrLpfMinFreq (); });

    setupFloatEditor ({ &fltrLpfQEditor, fltrLpfQLabel, "Fltr LPF Q", "Fltr LPF Q", "Fltr LPF Q" },
                         { 0.25f, 4.0f },
                         { 0.001f, 0.1f, 1.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fltrLpfQUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFltrLpfQ () + valueOffset };
                             fltrLpfQEditor.setValue (newValue);
                         },
                         [this] () { return 0.707f; },
                         [this] () { return uneditedSettingsProperties.getFltrLpfQ (); });

    setupFloatEditor ({ &fxChorusCenterEditor, fxChorusCenterLabel, "FX Chorus Center", "FX Chorus Center", "FX Chorus Center" },
                         { 1.0f, 20.0f },
                         { 1.0f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusCenterUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusCenter () + valueOffset };
                             fxChorusCenterEditor.setValue (newValue);
                         },
                         [this] () { return 12.0f; },
                         [this] () { return uneditedSettingsProperties.getFxChorusCenter (); });

    setupFloatEditor ({ &fxChorusDepthEditor, fxChorusDepthLabel, "FX Chorus Depth", "FX Chorus Depth", "FX Chorus Depth" },
                         { 1.0f, 5.0f },
                         { 1.0f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusDepthUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusDepth () + valueOffset };
                             fxChorusDepthEditor.setValue (newValue);
                         },
                         [this] () { return settingsProperties.getFxChorusCenter (); },
                         [this] () { return uneditedSettingsProperties.getFxChorusDepth (); });

    setupFloatEditor ({ &fxChorusLfoBEditor, fxChorusLfoBLabel, "FX Chorus LFO B", "FX Chorus LFO B", "FX Chorus LFO B" },
                         { 0.002f, 3.0f },
                         { 0.001f, 0.1f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusLfoBUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusLfoB () + valueOffset };
                             fxChorusLfoBEditor.setValue (newValue);
                         },
                         [this] () { return 0.002f; },
                         [this] () { return uneditedSettingsProperties.getFxChorusLfoB (); });

    setupFloatEditor ({ &fxChorusLfoTEditor, fxChorusLfoTLabel, "FX Chorus LFO T", "FX Chorus LFO T", "FX Chorus LFO T" },
                         { 0.002f, 3.0f },
                         { 0.001f, 0.1f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusLfoTUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusLfoT () + valueOffset };
                             fxChorusLfoTEditor.setValue (newValue);
                         },
                         [this] () { return 3.0f; },
                         [this] () { return uneditedSettingsProperties.getFxChorusLfoT (); });

    setupFloatEditor ({ &fxChorusMixEditor, fxChorusMixLabel, "FX Chorus Mix", "FX Chorus Mix", "FX Chorus Mix" },
                         { 0.1f, 1.0f },
                         { 0.1f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusMixUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusMix () + valueOffset };
                             fxChorusMixEditor.setValue (newValue);
                         },
                         [this] () { return 1.0f; },
                         [this] () { return uneditedSettingsProperties.getFxChorusMix (); });

    setupFloatEditor ({ &fxChorusSpreadEditor, fxChorusSpreadLabel, "FX Chorus Spread", "FX Chorus Spread", "FX Chorus Spread" },
                         { 0.01f, 1.0f },
                         { 0.01f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxChorusSpreadUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxChorusSpread () + valueOffset };
                             fxChorusSpreadEditor.setValue (newValue);
                         },
                         [this] () { return 0.01f; },
                         [this] () { return uneditedSettingsProperties.getFxChorusSpread (); });

    // Integer # of Taps (1–4)
    setupComboBox ({ fxChorusTapsComboBox, fxChorusTapsLabel, "FX Chorus Taps", "", "FX Chorus Taps" },
                      { { "1", 1 },
                        { "2", 2 },
                        { "3", 3 },
                        { "4", 4 } },
                      [this] (int valueOffset)
                      {
                          const auto fxChorusTaps { fxChorusTapsComboBox.getSelectedId () };
                          settingsProperties.setFxChorusTaps (std::clamp (fxChorusTaps + valueOffset, 1, 4), true);
                      },
                      [this] () { return 4; },
                      [this] () { return uneditedSettingsProperties.getFxChorusTaps () + 1; });

    // 0: -5 to 5V, 1: 0 to 5V 
    setupComboBox ({ fxCvUnipolarComboBox, fxCvUnipolarLabel, "FX CV Unipolar", "", "FX CV Unipolar" },
                      { { "-5v to 5v", 1 },
                        { "0v to 5v", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto fxCvUnipolar { fxCvUnipolarComboBox.getSelectedId () - 1 };
                          settingsProperties.setFxCvUnipolar (std::clamp (fxCvUnipolar + valueOffset, 0, 1), true);
                      },
                      [this] () { return 2; },
                      [this] () { return uneditedSettingsProperties.getFxCvUnipolar () + 1; });

    setupIntEditor ({ &fxDjfilterHpfMaxEditor, fxDjfilterHpfMaxLabel, "FX DJ Filter HPF Max", "FX DJ Filter HPF Max", "FX DJ Filter HPF Max" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterHpfMaxUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterHpfMax () + valueOffset };
                           fxDjfilterHpfMaxEditor.setValue (newValue);
                       },
                       [this] () { return 14000; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterHpfMax (); });

    setupIntEditor ({ &fxDjfilterHpfMinEditor, fxDjfilterHpfMinLabel, "FX DJ Filter HPF Min", "FX DJ Filter HPF Min", "FX DJ Filter HPF Min" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterHpfMinUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterHpfMin () + valueOffset };
                           fxDjfilterHpfMinEditor.setValue (newValue);
                       },
                       [this] () { return 100; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterHpfMin (); });

    setupIntEditor ({ &fxDjfilterLpfMaxEditor, fxDjfilterLpfMaxLabel, "FX DJ Filter LPF Max", "FX DJ Filter LPF Max", "FX DJ Filter LPF Max" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterLpfMaxUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterLpfMax () + valueOffset };
                           fxDjfilterLpfMaxEditor.setValue (newValue);
                       },
                       [this] () { return 20000; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterLpfMax (); });

    setupIntEditor ({ &fxDjfilterLpfMinEditor, fxDjfilterLpfMinLabel, "FX DJ Filter LPF Min", "FX DJ Filter LPF Min", "FX DJ Filter LPF Min" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDjfilterLpfMinUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDjfilterLpfMin () + valueOffset };
                           fxDjfilterLpfMinEditor.setValue (newValue);
                       },
                       [this] () { return 200; },
                       [this] () { return uneditedSettingsProperties.getFxDjfilterLpfMin (); });

    setupFloatEditor ({ &fxDjfilterQGainReductionEditor, fxDjfilterQGainReductionLabel, "FX DJ Filter Q Gain Reduction", "FX DJ Filter Q Gain Reduction", "FX DJ Filter Q Gain Reduction" },
                         { 0.01f, 1.0f },
                         { 0.01f, 0.1f, 0.3f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDjfilterQGainReductionUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDjfilterQGainReduction () + valueOffset };
                             fxDjfilterQGainReductionEditor.setValue (newValue);
                         },
                         [this] () { return 0.12f; },
                         [this] () { return uneditedSettingsProperties.getFxDjfilterQGainReduction (); });

    setupFloatEditor ({ &fxDjfilterQMaxEditor, fxDjfilterQMaxLabel, "FX DJ Filter Q Max", "FX DJ Filter Q Max", "FX DJ Filter Q Max" },
                         { 0.0f, 20.0f },
                         { 0.1f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDjfilterQMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDjfilterQMax () + valueOffset };
                             fxDjfilterQMaxEditor.setValue (newValue);
                         },
                         [this] () { return 4.0f; },
                         [this] () { return uneditedSettingsProperties.getFxDjfilterQMax (); });

    setupFloatEditor ({ &fxDjfilterQMinEditor, fxDjfilterQMinLabel, "FX DJ Filter Q Min", "FX DJ Filter Q Min", "FX DJ Filter Q Min" },
                         { 0.0f, 20.0f },
                         { 0.1f, 3.0f, 10.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDjfilterQMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDjfilterQMin () + valueOffset };
                             fxDjfilterQMinEditor.setValue (newValue);
                         },
                         [this] () { return 0.5f; },
                         [this] () { return uneditedSettingsProperties.getFxDjfilterQMin (); });

    setupIntEditor ({ &fxDubEchoHpfEditor, fxDubEchoHpfLabel, "FX Dub Echo HPF", "FX Dub Echo HPF", "FX Dub Echo HPF" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDubEchoHpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDubEchoHpf () + valueOffset };
                           fxDubEchoHpfEditor.setValue (newValue);
                       },
                       [this] () { return 400; },
                       [this] () { return uneditedSettingsProperties.getFxDubEchoHpf (); });

    setupIntEditor ({ &fxDubEchoLpfEditor, fxDubEchoLpfLabel, "FX Dub Echo LPF", "FX Dub Echo LPF", "FX Dub Echo LPF" },
                       { 20, 20000 },
                       { 1, 25, 100 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDubEchoLpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDubEchoLpf () + valueOffset };
                           fxDubEchoLpfEditor.setValue (newValue);
                       },
                       [this] () { return 8400; },
                       [this] () { return uneditedSettingsProperties.getFxDubEchoLpf (); });

    setupFloatEditor ({ &fxDubEchoMixEditor, fxDubEchoMixLabel, "FX Dub Echo Mix", "FX Dub Echo Mix", "FX Dub Echo Mix" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxDubEchoMixUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxDubEchoMix () + valueOffset };
                             fxDubEchoMixEditor.setValue (newValue);
                         },
                         [this] () { return 0.38f; },
                         [this] () { return uneditedSettingsProperties.getFxDubEchoMix (); });

    setupIntEditor ({ &fxDubEchoTminEditor, fxDubEchoTminLabel, "FX Dub Echo Tmin", "FX Dub Echo Tmin", "FX Dub Echo Tmin" },
                       { 0, 100 },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxDubEchoTminUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxDubEchoTmin () + valueOffset };
                           fxDubEchoTminEditor.setValue (newValue);
                       },
                       [this] () { return 30; },
                       [this] () { return uneditedSettingsProperties.getFxDubEchoTmin (); });

    setupFloatEditor ({ &fxGlitchCrushTimeMaxEditor, fxGlitchCrushTimeMaxLabel, "FX Glitch Crush Time Max", "FX Glitch Crush Time Max", "FX Glitch Crush Time Max" },
                         { 0.0f, 100.0f },
                         { 0.1f, 5.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchCrushTimeMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchCrushTimeMax () + valueOffset };
                             fxGlitchCrushTimeMaxEditor.setValue (newValue);
                         },
                         [this] () { return 50.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchCrushTimeMax (); });

    setupFloatEditor ({ &fxGlitchCrushTimeMinEditor, fxGlitchCrushTimeMinLabel, "FX Glitch Crush Time Min", "FX Glitch Crush Time Min", "FX Glitch Crush Time Min" },
                         { 0.0f, 100.0f },
                         { 0.1f, 5.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchCrushTimeMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchCrushTimeMin () + valueOffset };
                             fxGlitchCrushTimeMinEditor.setValue (newValue);
                         },
                         [this] () { return 10.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchCrushTimeMin (); });

    setupFloatEditor ({ &fxGlitchDropKeepLevelMaxEditor, fxGlitchDropKeepLevelMaxLabel, "FX Glitch Drop Keep Level Max", "FX Glitch Drop Keep Level Max", "FX Glitch Drop Keep Level Max" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepLevelMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepLevelMax () + valueOffset };
                             fxGlitchDropKeepLevelMaxEditor.setValue (newValue);
                         },
                         [this] () { return 0.75f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepLevelMax (); });

    setupFloatEditor ({ &fxGlitchDropKeepLevelMinEditor, fxGlitchDropKeepLevelMinLabel, "FX Glitch Drop Keep Level Min", "FX Glitch Drop Keep Level Min", "FX Glitch Drop Keep Level Min" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepLevelMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepLevelMin () + valueOffset };
                             fxGlitchDropKeepLevelMinEditor.setValue (newValue);
                         },
                         [this] () { return 0.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepLevelMin (); });

    setupFloatEditor ({ &fxGlitchDropKeepTimeMaxEditor, fxGlitchDropKeepTimeMaxLabel, "FX Glitch Drop Keep Time Max", "FX Glitch Drop Keep Time Max", "FX Glitch Drop Keep Time Max" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepTimeMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepTimeMax () + valueOffset };
                             fxGlitchDropKeepTimeMaxEditor.setValue (newValue);
                         },
                         [this] () { return 40.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepTimeMax (); });

    setupFloatEditor ({ &fxGlitchDropKeepTimeMinEditor, fxGlitchDropKeepTimeMinLabel, "FX Glitch Drop Keep Time Min", "FX Glitch Drop Keep Time Min", "FX Glitch Drop Keep Time Min" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchDropKeepTimeMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchDropKeepTimeMin () + valueOffset };
                             fxGlitchDropKeepTimeMinEditor.setValue (newValue);
                         },
                         [this] () { return 4.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchDropKeepTimeMin (); });

    setupFloatEditor ({ &fxGlitchMicroloopPlayTMaxEditor, fxGlitchMicroloopPlayTMaxLabel, "FX Glitch Microloop Play T Max", "FX Glitch Microloop Play T Max", "FX Glitch Microloop Play T Max" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopPlayTMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopPlayTMax () + valueOffset };
                             fxGlitchMicroloopPlayTMaxEditor.setValue (newValue);
                         },
                         [this] () { return 15.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopPlayTMax (); });

    setupFloatEditor ({ &fxGlitchMicroloopPlayTMinEditor, fxGlitchMicroloopPlayTMinLabel, "FX Glitch Microloop Play T Min", "FX Glitch Microloop Play T Min", "FX Glitch Microloop Play T Min" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopPlayTMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopPlayTMin () + valueOffset };
                             fxGlitchMicroloopPlayTMinEditor.setValue (newValue);
                         },
                         [this] () { return 5.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopPlayTMin (); });

    setupFloatEditor ({ &fxGlitchMicroloopSmplTMaxEditor, fxGlitchMicroloopSmplTMaxLabel, "FX Glitch Microloop Smpl T Max", "FX Glitch Microloop Smpl T Max", "FX Glitch Microloop Smpl T Max" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopSmplTMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopSmplTMax () + valueOffset };
                             fxGlitchMicroloopSmplTMaxEditor.setValue (newValue);
                         },
                         [this] () { return 3.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopSmplTMax (); });

    setupFloatEditor ({ &fxGlitchMicroloopSmplTMinEditor, fxGlitchMicroloopSmplTMinLabel, "FX Glitch Microloop Smpl T Min", "FX Glitch Microloop Smpl T Min", "FX Glitch Microloop Smpl T Min" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchMicroloopSmplTMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchMicroloopSmplTMin () + valueOffset };
                             fxGlitchMicroloopSmplTMinEditor.setValue (newValue);
                         },
                         [this] () { return 0.2f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchMicroloopSmplTMin (); });

    setupFloatEditor ({ &fxGlitchProbabilityMaxEditor, fxGlitchProbabilityMaxLabel, "FX Glitch Probability Max", "FX Glitch Probability Max", "FX Glitch Probability Max" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchProbabilityMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchProbabilityMax () + valueOffset };
                             fxGlitchProbabilityMaxEditor.setValue (newValue);
                         },
                         [this] () { return 0.003f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchProbabilityMax (); });

    setupFloatEditor ({ &fxGlitchProbabilityMinEditor, fxGlitchProbabilityMinLabel, "FX Glitch Probability Min", "FX Glitch Probability Min", "FX Glitch Probability Min" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 5); },
                         [this] (float value) { fxGlitchProbabilityMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchProbabilityMin () + valueOffset };
                             fxGlitchProbabilityMinEditor.setValue (newValue);
                         },
                         [this] () { return 0.00005f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchProbabilityMin (); });

    setupIntEditor ({ &fxGlitchStutterNumMaxEditor, fxGlitchStutterNumMaxLabel, "FX Glitch Stutter Num Max", "FX Glitch Stutter Num Max", "FX Glitch Stutter Num Max" },
                       { 0, 100 },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxGlitchStutterNumMaxUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxGlitchStutterNumMax () + valueOffset };
                           fxGlitchStutterNumMaxEditor.setValue (newValue);
                       },
                       [this] () { return 5; },
                       [this] () { return uneditedSettingsProperties.getFxGlitchStutterNumMax (); });

    setupIntEditor ({ &fxGlitchStutterNumMinEditor, fxGlitchStutterNumMinLabel, "FX Glitch Stutter Num Min", "FX Glitch Stutter Num Min", "FX Glitch Stutter Num Min" },
                       { 0, 100 },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxGlitchStutterNumMinUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxGlitchStutterNumMin () + valueOffset };
                           fxGlitchStutterNumMinEditor.setValue (newValue);
                       },
                       [this] () { return 2; },
                       [this] () { return uneditedSettingsProperties.getFxGlitchStutterNumMin (); });

    setupFloatEditor ({ &fxGlitchStutterSmplTMaxEditor, fxGlitchStutterSmplTMaxLabel, "FX Glitch Stutter Smpl T Max", "FX Glitch Stutter Smpl T Max", "FX Glitch Stutter Smpl T Max" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchStutterSmplTMaxUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchStutterSmplTMax () + valueOffset };
                             fxGlitchStutterSmplTMaxEditor.setValue (newValue);
                         },
                         [this] () { return 10.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchStutterSmplTMax (); });

    setupFloatEditor ({ &fxGlitchStutterSmplTMinEditor, fxGlitchStutterSmplTMinLabel, "FX Glitch Stutter Smpl T Min", "FX Glitch Stutter Smpl T Min", "FX Glitch Stutter Smpl T Min" },
                         { 0.0f, 100.0f },
                         { 0.1f, 10.0f, 25.0f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchStutterSmplTMinUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchStutterSmplTMin () + valueOffset };
                             fxGlitchStutterSmplTMinEditor.setValue (newValue);
                         },
                         [this] () { return 3.0f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchStutterSmplTMin (); });

    setupIntEditor ({ &fxGlitchStutterWindowEditor, fxGlitchStutterWindowLabel, "FX Glitch Stutter Window", "FX Glitch Stutter Window", "FX Glitch Stutter Window" },
                       { 0, 100 },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxGlitchStutterWindowUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxGlitchStutterWindow () + valueOffset };
                           fxGlitchStutterWindowEditor.setValue (newValue);
                       },
                       [this] () { return 20; },
                       [this] () { return uneditedSettingsProperties.getFxGlitchStutterWindow (); });

    setupFloatEditor ({ &fxGlitchWeightCrushLowEditor, fxGlitchWeightCrushLowLabel, "FX Glitch Weight Crush Low", "FX Glitch Weight Crush Low", "FX Glitch Weight Crush Low" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightCrushLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightCrushLow () + valueOffset };
                             fxGlitchWeightCrushLowEditor.setValue (newValue);
                         },
                         [this] () { return 0.30f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightCrushLow (); });

    setupFloatEditor ({ &fxGlitchWeightDropHighEditor, fxGlitchWeightDropHighLabel, "FX Glitch Weight Drop High", "FX Glitch Weight Drop High", "FX Glitch Weight Drop High" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightDropHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightDropHigh () + valueOffset };
                             fxGlitchWeightDropHighEditor.setValue (newValue);
                         },
                         [this] () { return 0.07f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightDropHigh (); });

    setupFloatEditor ({ &fxGlitchWeightDropLowEditor, fxGlitchWeightDropLowLabel, "FX Glitch Weight Drop Low", "FX Glitch Weight Drop Low", "FX Glitch Weight Drop Low" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightDropLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightDropLow () + valueOffset };
                             fxGlitchWeightDropLowEditor.setValue (newValue);
                         },
                         [this] () { return 0.02f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightDropLow (); });

    setupFloatEditor ({ &fxGlitchWeightHoldHighEditor, fxGlitchWeightHoldHighLabel, "FX Glitch Weight Hold High", "FX Glitch Weight Hold High", "FX Glitch Weight Hold High" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightHoldHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightHoldHigh () + valueOffset };
                             fxGlitchWeightHoldHighEditor.setValue (newValue);
                         },
                         [this] () { return 0.30f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightHoldHigh (); });

    setupFloatEditor ({ &fxGlitchWeightHoldLowEditor, fxGlitchWeightHoldLowLabel, "FX Glitch Weight Hold Low", "FX Glitch Weight Hold Low", "FX Glitch Weight Hold Low" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightHoldLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightHoldLow () + valueOffset };
                             fxGlitchWeightHoldLowEditor.setValue (newValue);
                         },
                         [this] () { return 0.15f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightHoldLow (); });

    setupFloatEditor ({ &fxGlitchWeightStutterHighEditor, fxGlitchWeightStutterHighLabel, "FX Glitch Weight Stutter High", "FX Glitch Weight Stutter High", "FX Glitch Weight Stutter High" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightStutterHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightStutterHigh () + valueOffset };
                             fxGlitchWeightStutterHighEditor.setValue (newValue);
                         },
                         [this] () { return 0.20f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightStutterHigh (); });

    setupFloatEditor ({ &fxGlitchWeightStutterLowEditor, fxGlitchWeightStutterLowLabel, "FX Glitch Weight Stutter Low", "FX Glitch Weight Stutter Low", "FX Glitch Weight Stutter Low" },
                         { 0.0f, 1.0f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { fxGlitchWeightStutterLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getFxGlitchWeightStutterLow () + valueOffset };
                             fxGlitchWeightStutterLowEditor.setValue (newValue);
                         },
                         [this] () { return 0.05f; },
                         [this] () { return uneditedSettingsProperties.getFxGlitchWeightStutterLow (); });

    setupIntEditor ({ &fxReverbHpfEditor, fxReverbHpfLabel, "FX Reverb HPF", "FX Reverb HPF", "FX Reverb HPF" },
                       { 20, 20000 },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxReverbHpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxReverbHpf () + valueOffset };
                           fxReverbHpfEditor.setValue (newValue);
                       },
                       [this] () { return 700; },
                       [this] () { return uneditedSettingsProperties.getFxReverbHpf (); });

    setupIntEditor ({ &fxReverbLpfEditor, fxReverbLpfLabel, "FX Reverb LPF", "FX Reverb LPF", "FX Reverb LPF" },
                       { 20, 20000 },
                       { 1, 10, 25 },
                       [this] (int value) { return juce::String (value); },
                       [this] (int value) { fxReverbLpfUiChanged (value); },
                       [this] (int valueOffset)
                       {
                           const auto newValue { settingsProperties.getFxReverbLpf () + valueOffset };
                           fxReverbLpfEditor.setValue (newValue);
                       },
                       [this] () { return 9000; },
                       [this] () { return uneditedSettingsProperties.getFxReverbLpf (); });

    // 0: 0V = 100 % -5 = 0 % +5 = 200 %
    // 1: 0V = 10 % +5 = 100 %
    setupComboBox ({ gateModeComboBox, gateModeLabel, "Gate Mode", "", "Gate Mode" },
                      { { "Immediate", 1 },
                        { "After Gate Falls", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto gateMode { gateModeComboBox.getSelectedId () - 1 };
                          settingsProperties.setGateMode (std::clamp (gateMode + valueOffset, 0, 1), true);
                      },
                      [this] () { return 1; },
                      [this] () { return uneditedSettingsProperties.getGateMode () + 1; });

    // 0 to sense small movement (wiggle)
    // 1 to require passing old value
    setupComboBox ({ knobPosTakeupComboBox, knobPosTakeupLabel, "Knob Pos Takeup", "", "Knob Pos Takeup" },
                      { { "Small Movement", 1 },
                        { "Pass Old Value", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto fxCvUnipolar { knobPosTakeupComboBox.getSelectedId () - 1 };
                          settingsProperties.setKnobPosTakeup (std::clamp (fxCvUnipolar + valueOffset, 0, 1), true);
                      },
                      [this] () { return 2; },
                      [this] () { return uneditedSettingsProperties.getKnobPosTakeup () + 1; });

    setupFloatEditor ({ &pitchHighEditor, pitchHighLabel, "Pitch High", "Pitch High", "Pitch High" },
                         { 1.5f, 3.7f },
                         { 0.1f, 0.3f, 0.5f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { pitchHighUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getPitchHigh () + valueOffset };
                             pitchHighEditor.setValue (newValue);
                         },
                         [this] () { return 2.5f; },
                         [this] () { return uneditedSettingsProperties.getPitchHigh (); });

    setupFloatEditor ({ &pitchLowEditor, pitchLowLabel, "Pitch Low", "Pitch Low", "Pitch Low" },
                         { 0.001f, 0.5f },
                         { 0.001f, 0.01f, 0.1f },
                         [this] (float value) { return getRoundedFloatString (value, 4); },
                         [this] (float value) { pitchLowUiChanged (value); },
                         [this] (float valueOffset)
                         {
                             const auto newValue { settingsProperties.getPitchLow () + valueOffset };
                             pitchLowEditor.setValue (newValue);
                         },
                         [this] () { return 0.125f; },
                         [this] () { return uneditedSettingsProperties.getPitchLow (); });

    // 0: 0V = 100 % -5 = 0 % +5 = 200 %
    // 1: 0V = 10 % +5 = 100 %
    setupComboBox ({ velocityUnipolarComboBox, velocityUnipolarLabel, "Velocity Unipolar", "", "Velocity Unipolar" },
                      { { "0%-100%-200%", 1 },
                        { "0%-100%", 2 } },
                      [this] (int valueOffset)
                      {
                          const auto velocityUnipolar { velocityUnipolarComboBox.getSelectedId () - 1 };
                          settingsProperties.setVelocityUnipolar (std::clamp (velocityUnipolar + valueOffset, 0, 1), true);
                      },
                      [this] () { return 1; },
                      [this] () { return uneditedSettingsProperties.getVelocityUnipolar () + 1; });
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
    clsdReleaseModeComboBox.setSelectedId (value + 1);
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
    fxCvUnipolarComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::fxCvUnipolarUiChanged (int value)
{
    settingsProperties.setFxCvUnipolar (value, false);
}

void SettingsEditorComponent::velocityUnipolarDataChanged (int value)
{
    velocityUnipolarComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::velocityUnipolarUiChanged (int value)
{
    settingsProperties.setVelocityUnipolar (value, false);
}

void SettingsEditorComponent::cvDisableVelocityDataChanged (int value)
{
    cvDisableVelocityComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::cvDisableVelocityUiChanged (int value)
{
    settingsProperties.setCvDisableVelocity (value, false);
}

void SettingsEditorComponent::cvDisableFxDataChanged (int value)
{
    cvDisableFxComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::cvDisableFxUiChanged (int value)
{
    settingsProperties.setCvDisableFx (value, false);
}

void SettingsEditorComponent::gateModeDataChanged (int value)
{
    gateModeComboBox.setSelectedId (value + 1);
}

void SettingsEditorComponent::gateModeUiChanged (int value)
{
    settingsProperties.setGateMode (value, false);
}

void SettingsEditorComponent::knobPosTakeupDataChanged (int value)
{
    knobPosTakeupComboBox.setSelectedId (value + 1);
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
    fxChorusTapsComboBox.setSelectedId (value);
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
    g.fillAll (juce::Colours::darkgrey);
}

void SettingsEditorComponent::resized ()
{
    struct CompLabelPair
    {
        juce::Component* comp;
        juce::Label* label;
    };

    CompLabelPair pairs [] =
    {
        { &accClAmpModEditor, &accClAmpModLabel },
        { &accClRelModEditor, &accClRelModLabel },
        { &accOpAmpModEditor, &accOpAmpModLabel },
        { &accOpRelModEditor, &accOpRelModLabel },
        { &chokeReleaseEditor, &chokeReleaseLabel },
        { &clsdMaxReleaseEditor, &clsdMaxReleaseLabel },
        { &clsdRelOfstScaleEditor, &clsdRelOfstScaleLabel },
        { &clsdReleaseModeComboBox, &clsdReleaseModeLabel },
        { &cvDisableFxComboBox, &cvDisableFxLabel },
        { &cvDisableVelocityComboBox, &cvDisableVelocityLabel },
        { &envelopeMaxReleaseEditor, &envelopeMaxReleaseLabel },
        { &feelAmpModEditor, &feelAmpModLabel },
        { &feelAttackModEditor, &feelAttackModLabel },
        { &feelReleaseModEditor, &feelReleaseModLabel },
        { &fltrHpfMaxFreqEditor, &fltrHpfMaxFreqLabel },
        { &fltrHpfMinFreqEditor, &fltrHpfMinFreqLabel },
        { &fltrHpfQEditor, &fltrHpfQLabel },
        { &fltrLpfMaxFreqEditor, &fltrLpfMaxFreqLabel },
        { &fltrLpfMinFreqEditor, &fltrLpfMinFreqLabel },
        { &fltrLpfQEditor, &fltrLpfQLabel },
        { &fxChorusCenterEditor, &fxChorusCenterLabel },
        { &fxChorusDepthEditor, &fxChorusDepthLabel },
        { &fxChorusLfoBEditor, &fxChorusLfoBLabel },
        { &fxChorusLfoTEditor, &fxChorusLfoTLabel },
        { &fxChorusMixEditor, &fxChorusMixLabel },
        { &fxChorusSpreadEditor, &fxChorusSpreadLabel },
        { &fxChorusTapsComboBox, &fxChorusTapsLabel },
        { &fxCvUnipolarComboBox, &fxCvUnipolarLabel },
        { &fxDjfilterHpfMaxEditor, &fxDjfilterHpfMaxLabel },
        { &fxDjfilterHpfMinEditor, &fxDjfilterHpfMinLabel },
        { &fxDjfilterLpfMaxEditor, &fxDjfilterLpfMaxLabel },
        { &fxDjfilterLpfMinEditor, &fxDjfilterLpfMinLabel },
        { &fxDjfilterQGainReductionEditor, &fxDjfilterQGainReductionLabel },
        { &fxDjfilterQMaxEditor, &fxDjfilterQMaxLabel },
        { &fxDjfilterQMinEditor, &fxDjfilterQMinLabel },
        { &fxDubEchoHpfEditor, &fxDubEchoHpfLabel },
        { &fxDubEchoLpfEditor, &fxDubEchoLpfLabel },
        { &fxDubEchoMixEditor, &fxDubEchoMixLabel },
        { &fxDubEchoTminEditor, &fxDubEchoTminLabel },
        { &fxGlitchCrushTimeMaxEditor, &fxGlitchCrushTimeMaxLabel },
        { &fxGlitchCrushTimeMinEditor, &fxGlitchCrushTimeMinLabel },
        { &fxGlitchDropKeepLevelMaxEditor, &fxGlitchDropKeepLevelMaxLabel },
        { &fxGlitchDropKeepLevelMinEditor, &fxGlitchDropKeepLevelMinLabel },
        { &fxGlitchDropKeepTimeMaxEditor, &fxGlitchDropKeepTimeMaxLabel },
        { &fxGlitchDropKeepTimeMinEditor, &fxGlitchDropKeepTimeMinLabel },
        { &fxGlitchMicroloopPlayTMaxEditor, &fxGlitchMicroloopPlayTMaxLabel },
        { &fxGlitchMicroloopPlayTMinEditor, &fxGlitchMicroloopPlayTMinLabel },
        { &fxGlitchMicroloopSmplTMaxEditor, &fxGlitchMicroloopSmplTMaxLabel },
        { &fxGlitchMicroloopSmplTMinEditor, &fxGlitchMicroloopSmplTMinLabel },
        { &fxGlitchProbabilityMaxEditor, &fxGlitchProbabilityMaxLabel },
        { &fxGlitchProbabilityMinEditor, &fxGlitchProbabilityMinLabel },
        { &fxGlitchStutterNumMaxEditor, &fxGlitchStutterNumMaxLabel },
        { &fxGlitchStutterNumMinEditor, &fxGlitchStutterNumMinLabel },
        { &fxGlitchStutterSmplTMaxEditor, &fxGlitchStutterSmplTMaxLabel },
        { &fxGlitchStutterSmplTMinEditor, &fxGlitchStutterSmplTMinLabel },
        { &fxGlitchStutterWindowEditor, &fxGlitchStutterWindowLabel },
        { &fxGlitchWeightCrushLowEditor, &fxGlitchWeightCrushLowLabel },
        { &fxGlitchWeightDropHighEditor, &fxGlitchWeightDropHighLabel },
        { &fxGlitchWeightDropLowEditor, &fxGlitchWeightDropLowLabel },
        { &fxGlitchWeightHoldHighEditor, &fxGlitchWeightHoldHighLabel },
        { &fxGlitchWeightHoldLowEditor, &fxGlitchWeightHoldLowLabel },
        { &fxGlitchWeightStutterHighEditor, &fxGlitchWeightStutterHighLabel },
        { &fxGlitchWeightStutterLowEditor, &fxGlitchWeightStutterLowLabel },
        { &fxReverbHpfEditor, &fxReverbHpfLabel },
        { &fxReverbLpfEditor, &fxReverbLpfLabel },
        { &gateModeComboBox, &gateModeLabel },
        { &knobPosTakeupComboBox, &knobPosTakeupLabel },
        { &pitchHighEditor, &pitchHighLabel },
        { &pitchLowEditor, &pitchLowLabel },
        { &velocityUnipolarComboBox, &velocityUnipolarLabel }
    };


    auto curX { 10 };
    auto curY { 10 };
    constexpr auto kLabelWidth { 160 };
    constexpr auto kCompWidth { 100 };
    constexpr auto kLineHeight { 20 };
    constexpr auto kLinePerColumn { 20 };
    for (const auto& p : pairs)
    {
        p.label->setBounds (curX, curY, kLabelWidth, kLineHeight);
        p.comp->setBounds (curX + kLabelWidth + 2, curY, kCompWidth, kLineHeight);
        curY += kLineHeight + 2;
        if (curY + kLineHeight + 2 > kLinePerColumn * (kLineHeight + 2))
        {
            curY = 10;
            curX += kLabelWidth + kCompWidth + 10;
        }
    }
}
