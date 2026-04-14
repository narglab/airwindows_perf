/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DitherBoxAudioProcessorEditor::DitherBoxAudioProcessorEditor(DitherBoxAudioProcessor &p)
	: AudioProcessorEditor(&p), audioProcessor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 100);

	AKnob.setSliderStyle(juce::Slider::LinearHorizontal);
	AKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 380, 20);
	addAndMakeVisible(AKnob);

	paramAAttachment = std::make_unique<
		juce::AudioProcessorValueTreeState::SliderAttachment>(
			audioProcessor.apvts,
			"mA",
			AKnob);

	AKnob.textFromValueFunction = [](double value)
	{
		switch (static_cast<int>(value * 24.999)) //0 to almost edge of # of params
		{
			case 0: return juce::String("Trunc 16");
			case 1: return juce::String("Flat 16");
			case 2: return juce::String("TPDF 16");
			case 3: return juce::String("Paul 16");
			case 4: return juce::String("DbPaul 16");
			case 5: return juce::String("Tape 16");
			case 6: return juce::String("HiGloss 16");
			case 7: return juce::String("Vinyl 16");
			case 8: return juce::String("Spatial 16");
			case 9: return juce::String("Natural 16");
			case 10: return juce::String("NJAD 16");
			case 11: return juce::String("Trunc 24");
			case 12: return juce::String("Flat 24");
			case 13: return juce::String("TPDF 24");
			case 14: return juce::String("Paul 24");
			case 15: return juce::String("DbPaul 24");
			case 16: return juce::String("Tape 24");
			case 17: return juce::String("HiGloss 24");
			case 18: return juce::String("Vinyl 24");
			case 19: return juce::String("Spatial 24");
			case 20: return juce::String("Natural 24");
			case 21: return juce::String("NJAD 24");
			case 22: return juce::String("SlewOnly");
			case 23: return juce::String("SubsOnly");
			case 24: return juce::String("Silhouette");
		}
	};
	AKnob.updateText();

}

DitherBoxAudioProcessorEditor::~DitherBoxAudioProcessorEditor()
{
}

//==============================================================================
void DitherBoxAudioProcessorEditor::paint(juce::Graphics &g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.setColour(juce::Colours::white);

	AKnob.setBounds(10, 10, 380, 80);
}

void DitherBoxAudioProcessorEditor::resized()
{
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor..
}
