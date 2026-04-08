/* ========================================
 *  ClipSoftly - ClipSoftly.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __ClipSoftly_H
#include "ClipSoftly.h"
#endif

void ClipSoftly::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	int spacing = floor(overallscale); //should give us working basic scaling, usually 2 or 4
	if (spacing < 1) spacing = 1; if (spacing > 16) spacing = 16;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		double softSpeed = fabs(inputSampleL);
		if (softSpeed < 1.0) softSpeed = 1.0; else softSpeed = 1.0/softSpeed;
		if (inputSampleL > 1.57079633) inputSampleL = 1.57079633;
		if (inputSampleL < -1.57079633) inputSampleL = -1.57079633;
		inputSampleL = sin(inputSampleL)*0.9549925859; //scale to what cliponly uses
		inputSampleL = (inputSampleL*softSpeed)+(lastSampleL*(1.0-softSpeed));

		softSpeed = fabs(inputSampleR);
		if (softSpeed < 1.0) softSpeed = 1.0; else softSpeed = 1.0/softSpeed;
		if (inputSampleR > 1.57079633) inputSampleR = 1.57079633;
		if (inputSampleR < -1.57079633) inputSampleR = -1.57079633;
		inputSampleR = sin(inputSampleR)*0.9549925859; //scale to what cliponly uses
		inputSampleR = (inputSampleR*softSpeed)+(lastSampleR*(1.0-softSpeed));
		
		intermediateL[spacing] = inputSampleL;
        inputSampleL = lastSampleL; //Latency is however many samples equals one 44.1k sample
		for (int x = spacing; x > 0; x--) intermediateL[x-1] = intermediateL[x];
		lastSampleL = intermediateL[0]; //run a little buffer to handle this
		
		intermediateR[spacing] = inputSampleR;
        inputSampleR = lastSampleR; //Latency is however many samples equals one 44.1k sample
		for (int x = spacing; x > 0; x--) intermediateR[x-1] = intermediateR[x];
		lastSampleR = intermediateR[0]; //run a little buffer to handle this
		
		//begin 32 bit stereo floating point dither
		int expon;
		constexpr uint32_t magic_number_dither = uint32_t(0x7fffffff);
		constexpr uint64_t two_pow_62 = 1ULL << 62;
		std::frexp((float) inputSampleL, &expon);
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		uint64_t power_of_twoL = two_pow_62 << expon;
		double dither_factorL = 5.5e-36l * power_of_twoL;
		inputSampleL += ((double(fpdL) - magic_number_dither) * dither_factorL);
		std::frexp((float) inputSampleR, &expon);
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		uint64_t power_of_twoR = two_pow_62 << expon;
		double dither_factorR = 5.5e-36l * power_of_twoR;
		inputSampleR += ((double(fpdR) - magic_number_dither) * dither_factorR);
		//end 32 bit stereo floating point dither

		*out1 = static_cast<float>(inputSampleL);
		*out2 = static_cast<float>(inputSampleR);
		
		*out1 = inputSampleL;
		*out2 = inputSampleR;

		in1++;
		in2++;
		out1++;
		out2++;
    }
}

void ClipSoftly::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	int spacing = floor(overallscale); //should give us working basic scaling, usually 2 or 4
	if (spacing < 1) spacing = 1; if (spacing > 16) spacing = 16;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		double softSpeed = fabs(inputSampleL);
		if (softSpeed < 1.0) softSpeed = 1.0; else softSpeed = 1.0/softSpeed;
		if (inputSampleL > 1.57079633) inputSampleL = 1.57079633;
		if (inputSampleL < -1.57079633) inputSampleL = -1.57079633;
		inputSampleL = sin(inputSampleL)*0.9549925859; //scale to what cliponly uses
		inputSampleL = (inputSampleL*softSpeed)+(lastSampleL*(1.0-softSpeed));
		
		softSpeed = fabs(inputSampleR);
		if (softSpeed < 1.0) softSpeed = 1.0; else softSpeed = 1.0/softSpeed;
		if (inputSampleR > 1.57079633) inputSampleR = 1.57079633;
		if (inputSampleR < -1.57079633) inputSampleR = -1.57079633;
		inputSampleR = sin(inputSampleR)*0.9549925859; //scale to what cliponly uses
		inputSampleR = (inputSampleR*softSpeed)+(lastSampleR*(1.0-softSpeed));
		
		intermediateL[spacing] = inputSampleL;
        inputSampleL = lastSampleL; //Latency is however many samples equals one 44.1k sample
		for (int x = spacing; x > 0; x--) intermediateL[x-1] = intermediateL[x];
		lastSampleL = intermediateL[0]; //run a little buffer to handle this
		
		intermediateR[spacing] = inputSampleR;
        inputSampleR = lastSampleR; //Latency is however many samples equals one 44.1k sample
		for (int x = spacing; x > 0; x--) intermediateR[x-1] = intermediateR[x];
		lastSampleR = intermediateR[0]; //run a little buffer to handle this
		
		//begin 64 bit stereo floating point dither
		//int expon; frexp((double)inputSampleL, &expon);
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		//inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
		//frexp((double)inputSampleR, &expon);
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		//inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
		//end 64 bit stereo floating point dither
		
		*out1 = inputSampleL;
		*out2 = inputSampleR;

		in1++;
		in2++;
		out1++;
		out2++;
    }
}
