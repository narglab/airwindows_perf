/* ========================================
 *  ShortBuss - ShortBuss.h
 *  Copyright (c) airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __ShortBuss_H
#include "ShortBuss.h"
#endif

void ShortBuss::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();

	double sbScale = (pow((A*2.0)-1.0,3)*0.001)/sqrt(overallscale);
	double wet = B;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		inputSampleL += (2.0 * inputSampleL * inputSampleL) * sbSampleL;
		sbSampleL += ((inputSampleL - sin(inputSampleL))*sbScale);
		sbSampleL = sin(sbSampleL*0.015625)*64.0;
		
		inputSampleR += (2.0 * inputSampleR * inputSampleR) * sbSampleR;
		sbSampleR += ((inputSampleR - sin(inputSampleR))*sbScale);
		sbSampleR = sin(sbSampleR*0.015625)*64.0;
		
		if (wet !=1.0) {
			inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
			inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
		}
		

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

void ShortBuss::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double sbScale = (pow((A*2.0)-1.0,3)*0.001)/sqrt(overallscale);
	double wet = B;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		inputSampleL += (2.0 * inputSampleL * inputSampleL) * sbSampleL;
		sbSampleL += ((inputSampleL - sin(inputSampleL))*sbScale);
		sbSampleL = sin(sbSampleL*0.015625)*64.0;
		
		inputSampleR += (2.0 * inputSampleR * inputSampleR) * sbSampleR;
		sbSampleR += ((inputSampleR - sin(inputSampleR))*sbScale);
		sbSampleR = sin(sbSampleR*0.015625)*64.0;
		
		if (wet !=1.0) {
			inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
			inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
		}
				
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
