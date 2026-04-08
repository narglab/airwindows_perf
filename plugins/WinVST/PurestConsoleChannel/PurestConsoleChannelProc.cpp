/* ========================================
 *  PurestConsoleChannel - PurestConsoleChannel.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __PurestConsoleChannel_H
#include "PurestConsoleChannel.h"
#endif

void PurestConsoleChannel::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];


	double inputSampleL;
	double inputSampleR;

    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		inputSampleL = sin(inputSampleL);
		inputSampleR = sin(inputSampleR);
		//amplitude aspect

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

		*in1++;
		*in2++;
		*out1++;
		*out2++;
    }
}

void PurestConsoleChannel::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	
	double inputSampleL;
	double inputSampleR;

    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;

		inputSampleL = sin(inputSampleL);
		inputSampleR = sin(inputSampleR);
		//amplitude aspect
		
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

		*in1++;
		*in2++;
		*out1++;
		*out2++;
    }
}