/* ========================================
 *  LRConvolve3 - LRConvolve3.h
 *  Copyright (c) airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __LRConvolve3_H
#include "LRConvolve3.h"
#endif

void LRConvolve3::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double smooth = pow(A,4)*(0.5/overallscale);
	double channel = B;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		double carrier = inputSampleL;
		double modulate = fabs(inputSampleR);
		if (channel > 0.5) {
			carrier = inputSampleR;
			modulate = fabs(inputSampleL);
		}
		if (iirSample < modulate) iirSample = modulate;
		modulate = (iirSample*smooth)+(modulate*(1.0-smooth));
		if (carrier > 0.0) carrier = sqrt(carrier/modulate)*modulate;
		if (carrier < 0.0) carrier = -sqrt(carrier/modulate)*modulate;
		inputSampleL = inputSampleR = carrier;
		

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

void LRConvolve3::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double smooth = pow(A,4)*(0.5/overallscale);
	double channel = B;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		double carrier = inputSampleL;
		double modulate = fabs(inputSampleR);
		if (channel > 0.5) {
			carrier = inputSampleR;
			modulate = fabs(inputSampleL);
		}
		if (iirSample < modulate) iirSample = modulate;
		modulate = (iirSample*smooth)+(modulate*(1.0-smooth));
		if (carrier > 0.0) carrier = sqrt(carrier/modulate)*modulate;
		if (carrier < 0.0) carrier = -sqrt(carrier/modulate)*modulate;
		inputSampleL = inputSampleR = carrier;
		
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
