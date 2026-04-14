/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class DitherBoxAudioProcessor : public juce::AudioProcessor
{
public:
	//==============================================================================
	DitherBoxAudioProcessor();
	~DitherBoxAudioProcessor() override;

	//==============================================================================
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void releaseResources() override;

	#ifndef JucePlugin_PreferredChannelConfigurations
	bool isBusesLayoutSupported(const BusesLayout &layouts) const override;
	#endif

	void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;
	void processBlock(juce::AudioBuffer<double> &, juce::MidiBuffer &) override;

	//==============================================================================
	juce::AudioProcessorEditor *createEditor() override;
	bool hasEditor() const override;

	//==============================================================================
	const juce::String getName() const override;

	bool acceptsMidi() const override;
	bool producesMidi() const override;
	bool isMidiEffect() const override;
	double getTailLengthSeconds() const override;
	bool supportsDoublePrecisionProcessing() const;

	//==============================================================================
	int getNumPrograms() override;
	int getCurrentProgram() override;
	void setCurrentProgram(int index) override;
	const juce::String getProgramName(int index) override;
	void changeProgramName(int index, const juce::String &newName) override;

	//==============================================================================
	void getStateInformation(juce::MemoryBlock &destData) override;
	void setStateInformation(const void *data, int sizeInBytes) override;

	juce::AudioProcessorValueTreeState apvts;

	juce::AudioProcessorValueTreeState::ParameterLayout createParameters()
	{
		std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

		params.push_back(std::make_unique<juce::AudioParameterFloat>(
			"mA",
			"A",
			juce::NormalisableRange<float>(0.0f, 1.00f, 0.0f, 0.5f),
			0.5f));

		return { params.begin(), params.end() };
	}

private:
	template <typename SampleType>
	void processBlockTemplate(juce::AudioBuffer<SampleType> &, juce::MidiBuffer &);

	double bynL[13];
	double bynR[13];
	double noiseShapingL;
	double noiseShapingR;
	double contingentErrL;
	double contingentErrR;
	double currentDitherL;
	double currentDitherR;
	int Position;
	bool flip;
	double NSOddL;
	double prevL;
	double nsL[16];
	double NSOddR;
	double prevR;
	double nsR[16];
	double lastSampleL;
	double outSampleL;
	double lastSampleR;
	double outSampleR;

	double iirSampleAL;
	double iirSampleBL;
	double iirSampleCL;
	double iirSampleDL;
	double iirSampleEL;
	double iirSampleFL;
	double iirSampleGL;
	double iirSampleHL;
	double iirSampleIL;
	double iirSampleJL;
	double iirSampleKL;
	double iirSampleLL;
	double iirSampleML;
	double iirSampleNL;
	double iirSampleOL;
	double iirSamplePL;
	double iirSampleQL;
	double iirSampleRL;
	double iirSampleSL;
	double iirSampleTL;
	double iirSampleUL;
	double iirSampleVL;
	double iirSampleWL;
	double iirSampleXL;
	double iirSampleYL;
	double iirSampleZL;

	double iirSampleAR;
	double iirSampleBR;
	double iirSampleCR;
	double iirSampleDR;
	double iirSampleER;
	double iirSampleFR;
	double iirSampleGR;
	double iirSampleHR;
	double iirSampleIR;
	double iirSampleJR;
	double iirSampleKR;
	double iirSampleLR;
	double iirSampleMR;
	double iirSampleNR;
	double iirSampleOR;
	double iirSamplePR;
	double iirSampleQR;
	double iirSampleRR;
	double iirSampleSR;
	double iirSampleTR;
	double iirSampleUR;
	double iirSampleVR;
	double iirSampleWR;
	double iirSampleXR;
	double iirSampleYR;
	double iirSampleZR;

	uint32_t fpdL;
	uint32_t fpdR;

	float A;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DitherBoxAudioProcessor)
};

