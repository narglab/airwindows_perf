/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DitherBoxAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	DitherBoxAudioProcessorEditor(DitherBoxAudioProcessor &);
	~DitherBoxAudioProcessorEditor() override;

	//==============================================================================
	void paint(juce::Graphics &) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	DitherBoxAudioProcessor &audioProcessor;

	juce::Slider AKnob;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> paramAAttachment;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DitherBoxAudioProcessorEditor)
};
