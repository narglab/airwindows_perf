/* ========================================
 *  PurestConsole3Channel - PurestConsole3Channel.h
 *  Copyright (c) airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __PurestConsole3Channel_H
#include "PurestConsole3Channel.h"
#endif

void PurestConsole3Channel::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];
    
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		inputSampleL += ((pow(inputSampleL,5)/128.0) + (pow(inputSampleL,9)/262144.0)) - ((pow(inputSampleL,3)/8.0) + (pow(inputSampleL,7)/4096.0));
		inputSampleR += ((pow(inputSampleR,5)/128.0) + (pow(inputSampleR,9)/262144.0)) - ((pow(inputSampleR,3)/8.0) + (pow(inputSampleR,7)/4096.0));
		//crude sine. Note that because modern processors love math more than extra variables, this is optimized


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

void PurestConsole3Channel::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;

		inputSampleL += ((pow(inputSampleL,5)/128.0) + (pow(inputSampleL,9)/262144.0)) - ((pow(inputSampleL,3)/8.0) + (pow(inputSampleL,7)/4096.0));
		inputSampleR += ((pow(inputSampleR,5)/128.0) + (pow(inputSampleR,9)/262144.0)) - ((pow(inputSampleR,3)/8.0) + (pow(inputSampleR,7)/4096.0));
		//crude sine. Note that because modern processors love math more than extra variables, this is optimized
		
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		
		*out1 = inputSampleL;
		*out2 = inputSampleR;

		in1++;
		in2++;
		out1++;
		out2++;
    }
}
