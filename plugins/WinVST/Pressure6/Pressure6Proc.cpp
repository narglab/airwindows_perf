/* ========================================
 *  Pressure6 - Pressure6.h
 *  Copyright (c) airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __Pressure6_H
#include "Pressure6.h"
#endif

void Pressure6::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double threshold = 1.0-pow(A*0.9,3.0);
	double adjSpd = ((A*92.0)+92.0)*overallscale;
	double wet = B*0.9;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		double inputSample = fabs(inputSampleL);
		if (fabs(inputSampleR) > inputSample) inputSample = fabs(inputSampleR);
		
		inputSample *= (muComp/threshold);
		inputSampleL *= (muComp/threshold);
		inputSampleR *= (muComp/threshold);
		if (fabs(inputSample) > threshold)
		{
			muComp *= muSpd;
			if (threshold/fabs(inputSample) < threshold) muComp += threshold*fabs(inputSample);
			else muComp -= threshold/fabs(inputSample);
			muComp /= muSpd;
		} else {
			muComp *= (muSpd*muSpd);
			muComp += ((1.1+threshold)-fabs(inputSample));
			muComp /= (muSpd*muSpd);
		}
		muComp = fmax(fmin(muComp,1.0),threshold);
		inputSample *= (muComp*muComp);
		inputSampleL *= (muComp*muComp);
		inputSampleR *= (muComp*muComp);
		muSpd = fmax(fmin(((muSpd*(muSpd-1.0))+(fabs(inputSample*adjSpd)))/muSpd,adjSpd*2.0),adjSpd);
		
		inputSampleL = (drySampleL*(1.0-(wet*1.1)))+(sin(fmax(fmin(inputSampleL*wet,M_PI_2),-M_PI_2))*wet);
		inputSampleR = (drySampleR*(1.0-(wet*1.1)))+(sin(fmax(fmin(inputSampleR*wet,M_PI_2),-M_PI_2))*wet);
		

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

void Pressure6::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double threshold = 1.0-pow(A*0.9,3.0);
	double adjSpd = ((A*92.0)+92.0)*overallscale;
	double wet = B*0.9;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		double inputSample = fabs(inputSampleL);
		if (fabs(inputSampleR) > inputSample) inputSample = fabs(inputSampleR);
		
		inputSample *= (muComp/threshold);
		inputSampleL *= (muComp/threshold);
		inputSampleR *= (muComp/threshold);
		if (fabs(inputSample) > threshold)
		{
			muComp *= muSpd;
			if (threshold/fabs(inputSample) < threshold) muComp += threshold*fabs(inputSample);
			else muComp -= threshold/fabs(inputSample);
			muComp /= muSpd;
		} else {
			muComp *= (muSpd*muSpd);
			muComp += ((1.1+threshold)-fabs(inputSample));
			muComp /= (muSpd*muSpd);
		}
		muComp = fmax(fmin(muComp,1.0),threshold);
		inputSample *= (muComp*muComp);
		inputSampleL *= (muComp*muComp);
		inputSampleR *= (muComp*muComp);
		muSpd = fmax(fmin(((muSpd*(muSpd-1.0))+(fabs(inputSample*adjSpd)))/muSpd,adjSpd*2.0),adjSpd);
		
		inputSampleL = (drySampleL*(1.0-(wet*1.1)))+(sin(fmax(fmin(inputSampleL*wet,M_PI_2),-M_PI_2))*wet);
		inputSampleR = (drySampleR*(1.0-(wet*1.1)))+(sin(fmax(fmin(inputSampleR*wet,M_PI_2),-M_PI_2))*wet);
		
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
