/* ========================================
 *  DeRez - DeRez.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __DeRez_H
#include "DeRez.h"
#endif

void DeRez::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double targetA = pow(A,3)+0.0005;
	if (targetA > 1.0) targetA = 1.0;
	double soften = (1.0 + targetA)/2;
	double targetB = pow(1.0-B,3) / 3;
	targetA /= overallscale;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23 && (targetB == 0)) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23 && (targetB == 0)) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		incrementA = ((incrementA*999.0)+targetA)/1000.0;
		incrementB = ((incrementB*999.0)+targetB)/1000.0;
		//incrementA is the frequency derez
		//incrementB is the bit depth derez
		position += incrementA;
		
		double outputSampleL = heldSampleL;
		double outputSampleR = heldSampleR;
		if (position > 1.0)
		{
			position -= 1.0;
			heldSampleL = (lastSampleL * position) + (inputSampleL * (1.0-position));
			outputSampleL = (outputSampleL * (1.0-soften)) + (heldSampleL * soften);
			//softens the edge of the derez
			heldSampleR = (lastSampleR * position) + (inputSampleR * (1.0-position));
			outputSampleR = (outputSampleR * (1.0-soften)) + (heldSampleR * soften);
			//softens the edge of the derez
		}
		inputSampleL = outputSampleL;
		inputSampleR = outputSampleR;
		
		double offset;
		if (incrementB > 0.0005)
		{
			if (inputSampleL > 0)
			{
				offset = inputSampleL;
				while (offset > 0) {offset -= incrementB;}
				inputSampleL -= offset;
				//it's below 0 so subtracting adds the remainder
			}
			if (inputSampleR > 0)
			{
				offset = inputSampleR;
				while (offset > 0) {offset -= incrementB;}
				inputSampleR -= offset;
				//it's below 0 so subtracting adds the remainder
			}
			
			if (inputSampleL < 0)
			{
				offset = inputSampleL;
				while (offset < 0) {offset += incrementB;}
				inputSampleL -= offset;
				//it's above 0 so subtracting subtracts the remainder
			}
			if (inputSampleR < 0)
			{
				offset = inputSampleR;
				while (offset < 0) {offset += incrementB;}
				inputSampleR -= offset;
				//it's above 0 so subtracting subtracts the remainder
			}
			
			inputSampleL *= (1.0 - incrementB);
			inputSampleR *= (1.0 - incrementB);
		}
		
		lastSampleL = drySampleL;
		lastSampleR = drySampleR;
		

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

void DeRez::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	double targetA = pow(A,3)+0.0005;
	if (targetA > 1.0) targetA = 1.0;
	double soften = (1.0 + targetA)/2;
	double targetB = pow(1.0-B,3) / 3;
	targetA /= overallscale;

    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23 && (targetB == 0)) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23 && (targetB == 0)) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		incrementA = ((incrementA*999.0)+targetA)/1000.0;
		incrementB = ((incrementB*999.0)+targetB)/1000.0;
		//incrementA is the frequency derez
		//incrementB is the bit depth derez
		position += incrementA;
		
		double outputSampleL = heldSampleL;
		double outputSampleR = heldSampleR;
		if (position > 1.0)
		{
			position -= 1.0;
			heldSampleL = (lastSampleL * position) + (inputSampleL * (1.0-position));
			outputSampleL = (outputSampleL * (1.0-soften)) + (heldSampleL * soften);
			//softens the edge of the derez
			heldSampleR = (lastSampleR * position) + (inputSampleR * (1.0-position));
			outputSampleR = (outputSampleR * (1.0-soften)) + (heldSampleR * soften);
			//softens the edge of the derez
		}
		inputSampleL = outputSampleL;
		inputSampleR = outputSampleR;
		
		double offset;
		if (incrementB > 0.0005)
		{
			if (inputSampleL > 0)
			{
				offset = inputSampleL;
				while (offset > 0) {offset -= incrementB;}
				inputSampleL -= offset;
				//it's below 0 so subtracting adds the remainder
			}
			if (inputSampleR > 0)
			{
				offset = inputSampleR;
				while (offset > 0) {offset -= incrementB;}
				inputSampleR -= offset;
				//it's below 0 so subtracting adds the remainder
			}
			
			if (inputSampleL < 0)
			{
				offset = inputSampleL;
				while (offset < 0) {offset += incrementB;}
				inputSampleL -= offset;
				//it's above 0 so subtracting subtracts the remainder
			}
			if (inputSampleR < 0)
			{
				offset = inputSampleR;
				while (offset < 0) {offset += incrementB;}
				inputSampleR -= offset;
				//it's above 0 so subtracting subtracts the remainder
			}
			
			inputSampleL *= (1.0 - incrementB);
			inputSampleR *= (1.0 - incrementB);
		}
		
		lastSampleL = drySampleL;
		lastSampleR = drySampleR;
		
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