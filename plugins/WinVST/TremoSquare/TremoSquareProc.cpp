/* ========================================
 *  TremoSquare - TremoSquare.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __TremoSquare_H
#include "TremoSquare.h"
#endif

void TremoSquare::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double increment = pow(A,4) / (50.0*overallscale);
	double wet = B;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		osc += increment; if (osc > 1.0) osc = 0.0;
		//this is our little oscillator code
		
		if (inputSampleL < 0) {
			if (polarityL == true) muteL = (osc < 0.5);
			polarityL = false;
		} else {
			if (polarityL == false) muteL = (osc < 0.5);
			polarityL = true;
		}

		if (inputSampleR < 0) {
			if (polarityR == true) muteR = (osc < 0.5);
			polarityR = false;
		} else {
			if (polarityR == false) muteR = (osc < 0.5);
			polarityR = true;
		}
		
		if (muteL) inputSampleL = 0.0;
		if (muteR) inputSampleR = 0.0;
		
		if (wet !=1.0) {
			inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
			inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
		}
		

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

void TremoSquare::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double increment = pow(A,4) / (50.0*overallscale);
	double wet = B;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		osc += increment; if (osc > 1.0) osc = 0.0;
		//this is our little oscillator code
		
		if (inputSampleL < 0) {
			if (polarityL == true) muteL = (osc < 0.5);
			polarityL = false;
		} else {
			if (polarityL == false) muteL = (osc < 0.5);
			polarityL = true;
		}
		
		if (inputSampleR < 0) {
			if (polarityR == true) muteR = (osc < 0.5);
			polarityR = false;
		} else {
			if (polarityR == false) muteR = (osc < 0.5);
			polarityR = true;
		}
		
		if (muteL) inputSampleL = 0.0;
		if (muteR) inputSampleR = 0.0;
		
		if (wet !=1.0) {
			inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
			inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
		}
				
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		
		*out1 = inputSampleL;
		*out2 = inputSampleR;

		*in1++;
		*in2++;
		*out1++;
		*out2++;
    }
}
