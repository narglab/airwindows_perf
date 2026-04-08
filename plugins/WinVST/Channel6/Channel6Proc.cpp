/* ========================================
 *  Channel6 - Channel6.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __Channel6_H
#include "Channel6.h"
#endif

void Channel6::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();	
	const double localiirAmount = iirAmount / overallscale;
	const double localthreshold = threshold / overallscale;
	const double density = pow(drive,2); //this doesn't relate to the plugins Density and Drive much
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;

		
		if (flip)
		{
			iirSampleLA = (iirSampleLA * (1 - localiirAmount)) + (inputSampleL * localiirAmount);
			inputSampleL = inputSampleL - iirSampleLA;
			iirSampleRA = (iirSampleRA * (1 - localiirAmount)) + (inputSampleR * localiirAmount);
			inputSampleR = inputSampleR - iirSampleRA;
		}
		else
		{
			iirSampleLB = (iirSampleLB * (1 - localiirAmount)) + (inputSampleL * localiirAmount);
			inputSampleL = inputSampleL - iirSampleLB;
			iirSampleRB = (iirSampleRB * (1 - localiirAmount)) + (inputSampleR * localiirAmount);
			inputSampleR = inputSampleR - iirSampleRB;
		}
		//highpass section
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;

		
		if (inputSampleL > 1.0) inputSampleL = 1.0;
		if (inputSampleL < -1.0) inputSampleL = -1.0;
		inputSampleL *= 1.2533141373155;
		//clip to 1.2533141373155 to reach maximum output
		
		double distSampleL = sin(inputSampleL * fabs(inputSampleL)) / ((fabs(inputSampleL) == 0.0) ?1:fabs(inputSampleL));
		inputSampleL = (drySampleL*(1-density))+(distSampleL*density);
		//drive section
		
		if (inputSampleR > 1.0) inputSampleR = 1.0;
		if (inputSampleR < -1.0) inputSampleR = -1.0;
		inputSampleR *= 1.2533141373155;
		//clip to 1.2533141373155 to reach maximum output
		
		double distSampleR = sin(inputSampleR * fabs(inputSampleR)) / ((fabs(inputSampleR) == 0.0) ?1:fabs(inputSampleR));
		inputSampleR = (drySampleR*(1-density))+(distSampleR*density);
		//drive section
		
		double clamp = inputSampleL - lastSampleL;
		if (clamp > localthreshold)
			inputSampleL = lastSampleL + localthreshold;
		if (-clamp > localthreshold)
			inputSampleL = lastSampleL - localthreshold;
		lastSampleL = inputSampleL;
		
		clamp = inputSampleR - lastSampleR;
		if (clamp > localthreshold)
			inputSampleR = lastSampleR + localthreshold;
		if (-clamp > localthreshold)
			inputSampleR = lastSampleR - localthreshold;
		lastSampleR = inputSampleR;
		//slew section
		flip = !flip;
		
		if (output < 1.0) {
			inputSampleL *= output;
			inputSampleR *= output;
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

void Channel6::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();	
	const double localiirAmount = iirAmount / overallscale;
	const double localthreshold = threshold / overallscale;
	const double density = pow(drive,2); //this doesn't relate to the plugins Density and Drive much
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;

		
		if (flip)
		{
			iirSampleLA = (iirSampleLA * (1 - localiirAmount)) + (inputSampleL * localiirAmount);
			inputSampleL = inputSampleL - iirSampleLA;
			iirSampleRA = (iirSampleRA * (1 - localiirAmount)) + (inputSampleR * localiirAmount);
			inputSampleR = inputSampleR - iirSampleRA;
		}
		else
		{
			iirSampleLB = (iirSampleLB * (1 - localiirAmount)) + (inputSampleL * localiirAmount);
			inputSampleL = inputSampleL - iirSampleLB;
			iirSampleRB = (iirSampleRB * (1 - localiirAmount)) + (inputSampleR * localiirAmount);
			inputSampleR = inputSampleR - iirSampleRB;
		}
		//highpass section
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
		
		
		if (inputSampleL > 1.0) inputSampleL = 1.0;
		if (inputSampleL < -1.0) inputSampleL = -1.0;
		inputSampleL *= 1.2533141373155;
		//clip to 1.2533141373155 to reach maximum output
		
		double distSampleL = sin(inputSampleL * fabs(inputSampleL)) / ((fabs(inputSampleL) == 0.0) ?1:fabs(inputSampleL));
		inputSampleL = (drySampleL*(1-density))+(distSampleL*density);
		//drive section
		
		if (inputSampleR > 1.0) inputSampleR = 1.0;
		if (inputSampleR < -1.0) inputSampleR = -1.0;
		inputSampleR *= 1.2533141373155;
		//clip to 1.2533141373155 to reach maximum output
		
		double distSampleR = sin(inputSampleR * fabs(inputSampleR)) / ((fabs(inputSampleR) == 0.0) ?1:fabs(inputSampleR));
		inputSampleR = (drySampleR*(1-density))+(distSampleR*density);
		//drive section
		
		double clamp = inputSampleL - lastSampleL;
		if (clamp > localthreshold)
			inputSampleL = lastSampleL + localthreshold;
		if (-clamp > localthreshold)
			inputSampleL = lastSampleL - localthreshold;
		lastSampleL = inputSampleL;
		
		clamp = inputSampleR - lastSampleR;
		if (clamp > localthreshold)
			inputSampleR = lastSampleR + localthreshold;
		if (-clamp > localthreshold)
			inputSampleR = lastSampleR - localthreshold;
		lastSampleR = inputSampleR;
		//slew section
		flip = !flip;
		
		if (output < 1.0) {
			inputSampleL *= output;
			inputSampleR *= output;
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
