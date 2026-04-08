/* ========================================
 *  C5RawBuss - C5RawBuss.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __C5RawBuss_H
#include "C5RawBuss.h"
#endif

void C5RawBuss::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	
	double centering = A * 0.5;
	centering = 1.0 - pow(centering,5);
	//we can set our centering force from zero to rather high, but
	//there's a really intense taper on it forcing it to mostly be almost 1.0.
	//If it's literally 1.0, we don't even apply it, and you get the original
	//Xmas Morning bugged-out Console5, which is the default setting for Raw Console5.
	double differenceL;
	double differenceR;
	
	double inputSampleL;
	double inputSampleR;
    
    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		if (inputSampleL > 1.0) inputSampleL = 1.0;
		if (inputSampleL < -1.0) inputSampleL = -1.0;
		inputSampleL = asin(inputSampleL);
		//amplitude aspect
		if (inputSampleR > 1.0) inputSampleR = 1.0;
		if (inputSampleR < -1.0) inputSampleR = -1.0;
		inputSampleR = asin(inputSampleR);
		//amplitude aspect
		
		differenceL = lastSampleBussL - inputSampleL;
		lastSampleBussL = inputSampleL;
		//derive slew part off direct sample measurement + from last time
		differenceR = lastSampleBussR - inputSampleR;
		lastSampleBussR = inputSampleR;
		//derive slew part off direct sample measurement + from last time

		if (differenceL > 1.57079633) differenceL = 1.57079633;
		if (differenceL < -1.57079633) differenceL = -1.57079633;
		if (differenceR > 1.57079633) differenceR = 1.57079633;
		if (differenceR < -1.57079633) differenceR = -1.57079633;

		inputSampleL = lastFXBussL + sin(differenceL);
		lastFXBussL = inputSampleL;
		if (centering < 1.0) lastFXBussL *= centering;
		//if we're using the crude centering force, it's applied here
		inputSampleR = lastFXBussR + sin(differenceR);
		lastFXBussR = inputSampleR;
		if (centering < 1.0) lastFXBussR *= centering;
		//if we're using the crude centering force, it's applied here

		if (lastFXBussL > 1.0) lastFXBussL = 1.0;
		if (lastFXBussL < -1.0) lastFXBussL = -1.0;
		//build new signal off what was present in output last time
		if (lastFXBussR > 1.0) lastFXBussR = 1.0;
		if (lastFXBussR < -1.0) lastFXBussR = -1.0;
		//build new signal off what was present in output last time
		//slew aspect
		

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

void C5RawBuss::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	
	double centering = A * 0.5;
	centering = 1.0 - pow(centering,5);
	//we can set our centering force from zero to rather high, but
	//there's a really intense taper on it forcing it to mostly be almost 1.0.
	//If it's literally 1.0, we don't even apply it, and you get the original
	//Xmas Morning bugged-out Console5, which is the default setting for Raw Console5.
	double differenceL;
	double differenceR;
	
	double inputSampleL;
	double inputSampleR;

    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		if (inputSampleL > 1.0) inputSampleL = 1.0;
		if (inputSampleL < -1.0) inputSampleL = -1.0;
		inputSampleL = asin(inputSampleL);
		//amplitude aspect
		if (inputSampleR > 1.0) inputSampleR = 1.0;
		if (inputSampleR < -1.0) inputSampleR = -1.0;
		inputSampleR = asin(inputSampleR);
		//amplitude aspect
		
		differenceL = lastSampleBussL - inputSampleL;
		lastSampleBussL = inputSampleL;
		//derive slew part off direct sample measurement + from last time
		differenceR = lastSampleBussR - inputSampleR;
		lastSampleBussR = inputSampleR;
		//derive slew part off direct sample measurement + from last time
		
		if (differenceL > 1.57079633) differenceL = 1.57079633;
		if (differenceL < -1.57079633) differenceL = -1.57079633;
		if (differenceR > 1.57079633) differenceR = 1.57079633;
		if (differenceR < -1.57079633) differenceR = -1.57079633;
		
		inputSampleL = lastFXBussL + sin(differenceL);
		lastFXBussL = inputSampleL;
		if (centering < 1.0) lastFXBussL *= centering;
		//if we're using the crude centering force, it's applied here
		inputSampleR = lastFXBussR + sin(differenceR);
		lastFXBussR = inputSampleR;
		if (centering < 1.0) lastFXBussR *= centering;
		//if we're using the crude centering force, it's applied here
		
		if (lastFXBussL > 1.0) lastFXBussL = 1.0;
		if (lastFXBussL < -1.0) lastFXBussL = -1.0;
		//build new signal off what was present in output last time
		if (lastFXBussR > 1.0) lastFXBussR = 1.0;
		if (lastFXBussR < -1.0) lastFXBussR = -1.0;
		//build new signal off what was present in output last time
		//slew aspect
		
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