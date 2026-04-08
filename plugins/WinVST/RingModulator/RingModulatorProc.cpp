/* ========================================
 *  RingModulator - RingModulator.h
 *  Copyright (c) airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __RingModulator_H
#include "RingModulator.h"
#endif

void RingModulator::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	VstInt32 inFramesToProcess = sampleFrames; //vst doesn't give us this as a separate variable so we'll make it
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	incLA = incLB; incLB = pow(A,5)/overallscale;
	incRA = incRB; incRB = pow(B,5)/overallscale;
	double soar = 0.3-(C*0.3);
	double wet = pow(D,2);
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		double temp = (double)sampleFrames/inFramesToProcess;
		double incL = (incLA*temp)+(incLB*(1.0-temp));
		double incR = (incRA*temp)+(incRB*(1.0-temp));
		
		sinePosL += incL;
		if (sinePosL > 6.283185307179586) sinePosL -= 6.283185307179586;
		double sinResultL = sin(sinePosL);
		sinePosR += incR;
		if (sinePosR > 6.283185307179586) sinePosR -= 6.283185307179586;
		double sinResultR = sin(sinePosR);
		
		double out = 0.0;
		double snM = fabs(sinResultL)+(soar*soar);
		double inM = fabs(inputSampleL);
		if (inM < snM) {
			inM = fabs(sinResultL);
			snM = fabs(inputSampleL)+(soar*soar);
		}
		
		if (inputSampleL > 0.0 && sinResultL > 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		if (inputSampleL < 0.0 && sinResultL > 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleL > 0.0 && sinResultL < 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleL < 0.0 && sinResultL < 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		inputSampleL = out;
		
		out = 0.0;
		snM = fabs(sinResultR)+(soar*soar);
		inM = fabs(inputSampleR);
		if (inM < snM) {
			inM = fabs(sinResultR);
			snM = fabs(inputSampleR)+(soar*soar);
		}
		
		if (inputSampleR > 0.0 && sinResultR > 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		if (inputSampleR < 0.0 && sinResultR > 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleR > 0.0 && sinResultR < 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleR < 0.0 && sinResultR < 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		inputSampleR = out;
		
		if (wet != 1.0) {
			inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
			inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
		}
		//Dry/Wet control, defaults to the last slider
		

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

void RingModulator::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	VstInt32 inFramesToProcess = sampleFrames; //vst doesn't give us this as a separate variable so we'll make it
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	incLA = incLB; incLB = pow(A,5)/overallscale;
	incRA = incRB; incRB = pow(B,5)/overallscale;
	double soar = 0.3-(C*0.3);
	double wet = pow(D,2);
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		double temp = (double)sampleFrames/inFramesToProcess;
		double incL = (incLA*temp)+(incLB*(1.0-temp));
		double incR = (incRA*temp)+(incRB*(1.0-temp));
		
		sinePosL += incL;
		if (sinePosL > 6.283185307179586) sinePosL -= 6.283185307179586;
		double sinResultL = sin(sinePosL);
		sinePosR += incR;
		if (sinePosR > 6.283185307179586) sinePosR -= 6.283185307179586;
		double sinResultR = sin(sinePosR);
		
		double out = 0.0;
		double snM = fabs(sinResultL)+(soar*soar);
		double inM = fabs(inputSampleL);
		if (inM < snM) {
			inM = fabs(sinResultL);
			snM = fabs(inputSampleL)+(soar*soar);
		}
		
		if (inputSampleL > 0.0 && sinResultL > 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		if (inputSampleL < 0.0 && sinResultL > 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleL > 0.0 && sinResultL < 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleL < 0.0 && sinResultL < 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		inputSampleL = out;
		
		out = 0.0;
		snM = fabs(sinResultR)+(soar*soar);
		inM = fabs(inputSampleR);
		if (inM < snM) {
			inM = fabs(sinResultR);
			snM = fabs(inputSampleR)+(soar*soar);
		}
		
		if (inputSampleR > 0.0 && sinResultR > 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		if (inputSampleR < 0.0 && sinResultR > 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleR > 0.0 && sinResultR < 0.0) out = fmin((-sqrt(inM/snM)*snM)+soar,0.0);
		if (inputSampleR < 0.0 && sinResultR < 0.0) out = fmax((sqrt(inM/snM)*snM)-soar,0.0);
		inputSampleR = out;
		
		if (wet != 1.0) {
			inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
			inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
		}
		//Dry/Wet control, defaults to the last slider
		
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
