/* ========================================
 *  LRConvolve - LRConvolve.h
 *  Copyright (c) airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __LRConvolve_H
#include "LRConvolve.h"
#endif

void LRConvolve::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
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
		
		//blame Jannik Asfaig (BoyXx76) for this (and me) :D
		double out = 0.0;		
		if (inputSampleL > 0.0 && inputSampleR > 0.0) out = sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		if (inputSampleL < 0.0 && inputSampleR > 0.0) out = -sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		if (inputSampleL > 0.0 && inputSampleR < 0.0) out = -sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		if (inputSampleL < 0.0 && inputSampleR < 0.0) out = sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		inputSampleL = inputSampleR = out;
		

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

void LRConvolve::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
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
		
		//blame Jannik Asfaig (BoyXx76) for this (and me) :D
		double out = 0.0;		
		if (inputSampleL > 0.0 && inputSampleR > 0.0) out = sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		if (inputSampleL < 0.0 && inputSampleR > 0.0) out = -sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		if (inputSampleL > 0.0 && inputSampleR < 0.0) out = -sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		if (inputSampleL < 0.0 && inputSampleR < 0.0) out = sqrt(fabs(inputSampleL)*fabs(inputSampleR));
		inputSampleL = inputSampleR = out;
		
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
