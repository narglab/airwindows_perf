/* ========================================
 *  Lowpass - Lowpass.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __Lowpass_H
#include "Lowpass.h"
#endif

void Lowpass::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	double iirAmount = (pow(A,2)+A)/2.0;
	iirAmount /= overallscale;
	double tight = (B*2.0)-1.0;
	double wet = C;
	//removed extra dry variable
	double offset;
	double inputSampleL;
	double inputSampleR;
	double outputSampleL;
	double outputSampleR;
	
	iirAmount += (iirAmount * tight * tight);
	if (tight > 0) tight /= 1.5;
	else tight /= 3.0;
	//we are setting it up so that to either extreme we can get an audible sound,
	//but sort of scaled so small adjustments don't shift the cutoff frequency yet.
	if (iirAmount <= 0.0) iirAmount = 0.0;
	if (iirAmount > 1.0) iirAmount = 1.0;
	//handle the change in cutoff frequency
    
    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		outputSampleL = inputSampleL;
		outputSampleR = inputSampleR;
		
		if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
		else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
		if (offset < 0) offset = 0;
		if (offset > 1) offset = 1;
		if (fpFlip)
		{
			iirSampleAL = (iirSampleAL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			outputSampleL = iirSampleAL;
		}
		else
		{
			iirSampleBL = (iirSampleBL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			outputSampleL = iirSampleBL;
		}

		
		if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
		else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
		if (offset < 0) offset = 0;
		if (offset > 1) offset = 1;
		if (fpFlip)
		{
			iirSampleAR = (iirSampleAR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			outputSampleR = iirSampleAR;
		}
		else
		{
			iirSampleBR = (iirSampleBR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			outputSampleR = iirSampleBR;
		}
		fpFlip = !fpFlip;

		
		
		if (wet < 1.0) outputSampleL = (outputSampleL * wet) + (inputSampleL * (1.0-wet));
		if (wet < 1.0) outputSampleR = (outputSampleR * wet) + (inputSampleR * (1.0-wet));


		*out1 = static_cast<float>(inputSampleL);
		*out2 = static_cast<float>(inputSampleR);

		*out1 = outputSampleL;
		*out2 = outputSampleR;

		*in1++;
		*in2++;
		*out1++;
		*out2++;
    }
}

void Lowpass::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	double iirAmount = (pow(A,2)+A)/2.0;
	iirAmount /= overallscale;
	double tight = (B*2.0)-1.0;
	double wet = C;
	//removed extra dry variable
	double offset;
	double inputSampleL;
	double inputSampleR;
	double outputSampleL;
	double outputSampleR;
	
	iirAmount += (iirAmount * tight * tight);
	if (tight > 0) tight /= 1.5;
	else tight /= 3.0;
	//we are setting it up so that to either extreme we can get an audible sound,
	//but sort of scaled so small adjustments don't shift the cutoff frequency yet.
	if (iirAmount <= 0.0) iirAmount = 0.0;
	if (iirAmount > 1.0) iirAmount = 1.0;
	//handle the change in cutoff frequency
	
    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		
		outputSampleL = inputSampleL;
		outputSampleR = inputSampleR;
		
		if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
		else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
		if (offset < 0) offset = 0;
		if (offset > 1) offset = 1;
		if (fpFlip)
		{
			iirSampleAL = (iirSampleAL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			outputSampleL = iirSampleAL;
		}
		else
		{
			iirSampleBL = (iirSampleBL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			outputSampleL = iirSampleBL;
		}
		
		
		if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
		else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
		if (offset < 0) offset = 0;
		if (offset > 1) offset = 1;
		if (fpFlip)
		{
			iirSampleAR = (iirSampleAR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			outputSampleR = iirSampleAR;
		}
		else
		{
			iirSampleBR = (iirSampleBR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			outputSampleR = iirSampleBR;
		}
		fpFlip = !fpFlip;
		
		
		
		if (wet < 1.0) outputSampleL = (outputSampleL * wet) + (inputSampleL * (1.0-wet));
		if (wet < 1.0) outputSampleR = (outputSampleR * wet) + (inputSampleR * (1.0-wet));
		
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		
		*out1 = outputSampleL;
		*out2 = outputSampleR;
		
		*in1++;
		*in2++;
		*out1++;
		*out2++;
    }
}