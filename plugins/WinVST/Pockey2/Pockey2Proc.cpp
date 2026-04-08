/* ========================================
 *  Pockey2 - Pockey2.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __Pockey2_H
#include "Pockey2.h"
#endif

void Pockey2::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	int freq = floor(pow(A,3)*32.0*overallscale);
	//dividing of derez must always be integer values now: no freq grinding
	
	double rez = 4+(B*12.0);
	//4 to 16, with 12 being the default.
	int rezFactor = (int)pow(2,rez); //256, 4096, 65536 or anything in between
	
	double wet = C;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
				
		if (inputSampleL > 1.0) inputSampleL = 1.0; if (inputSampleL < -1.0) inputSampleL = -1.0;
		if (inputSampleL > 0) inputSampleL = log(1.0+(255*fabs(inputSampleL)))/log(255);
		if (inputSampleL < 0) inputSampleL = -log(1.0+(255*fabs(inputSampleL)))/log(255);
		
		if (inputSampleR > 1.0) inputSampleR = 1.0; if (inputSampleR < -1.0) inputSampleR = -1.0;
		if (inputSampleR > 0) inputSampleR = log(1.0+(255*fabs(inputSampleR)))/log(255);
		if (inputSampleR < 0) inputSampleR = -log(1.0+(255*fabs(inputSampleR)))/log(255);
		//end uLaw encode		
		
		inputSampleL *= rezFactor;
		inputSampleR *= rezFactor;
		if (inputSampleL > 0) inputSampleL = floor(inputSampleL);
		if (inputSampleL < 0) inputSampleL = -floor(-inputSampleL);
		if (inputSampleR > 0) inputSampleR = floor(inputSampleR);
		if (inputSampleR < 0) inputSampleR = -floor(-inputSampleR);
		inputSampleL /= rezFactor;
		inputSampleR /= rezFactor;
		
		if (inputSampleL > 1.0) inputSampleL = 1.0; if (inputSampleL < -1.0) inputSampleL = -1.0;
		if (inputSampleL > 0) inputSampleL = (pow(256,fabs(inputSampleL))-1.0) / 255;
		if (inputSampleL < 0) inputSampleL = -(pow(256,fabs(inputSampleL))-1.0) / 255;
		
		if (inputSampleR > 1.0) inputSampleR = 1.0; if (inputSampleR < -1.0) inputSampleR = -1.0;
		if (inputSampleR > 0) inputSampleR = (pow(256,fabs(inputSampleR))-1.0) / 255;
		if (inputSampleR < 0) inputSampleR = -(pow(256,fabs(inputSampleR))-1.0) / 255;
		//end uLaw decode
		
		double blurL = 0.618033988749894848204586-(fabs(inputSampleL - lastSampleL)*overallscale);
		if (blurL < 0.0) blurL = 0.0;
		double blurR = 0.618033988749894848204586-(fabs(inputSampleR - lastSampleR)*overallscale);
		if (blurR < 0.0) blurR = 0.0; //reverse it. Mellow stuff gets blur, bright gets edge
		
		if (position < 1)
		{
			position = freq; //one to ? scaled by overallscale
			heldSampleL = inputSampleL;			
			heldSampleR = inputSampleR;			
		}
		inputSampleL = heldSampleL;
		inputSampleR = heldSampleR;
		lastSampleL = drySampleL;
		lastSampleR = drySampleR;
		position--;
				
		inputSampleL = (inputSampleL * blurL) + (previousHeldL * (1.0-blurL));
		inputSampleR = (inputSampleR * blurR) + (previousHeldR * (1.0-blurR));
		//conditional average: only if we actually have brightness
		previousHeldL = heldSampleL;
		previousHeldR = heldSampleR;
		//end Frequency Derez
		
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

void Pockey2::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	
	int freq = floor(pow(A,3)*32.0*overallscale);
	//dividing of derez must always be integer values now: no freq grinding
	
	double rez = 4+(B*12.0);
	//4 to 16, with 12 being the default.
	int rezFactor = (int)pow(2,rez); //256, 4096, 65536 or anything in between
	
	double wet = C;
	
    while (--sampleFrames >= 0)
    {
		double inputSampleL = *in1;
		double inputSampleR = *in2;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
		double drySampleL = inputSampleL;
		double drySampleR = inputSampleR;
				
		if (inputSampleL > 1.0) inputSampleL = 1.0; if (inputSampleL < -1.0) inputSampleL = -1.0;
		if (inputSampleL > 0) inputSampleL = log(1.0+(255*fabs(inputSampleL)))/log(255);
		if (inputSampleL < 0) inputSampleL = -log(1.0+(255*fabs(inputSampleL)))/log(255);
		
		if (inputSampleR > 1.0) inputSampleR = 1.0; if (inputSampleR < -1.0) inputSampleR = -1.0;
		if (inputSampleR > 0) inputSampleR = log(1.0+(255*fabs(inputSampleR)))/log(255);
		if (inputSampleR < 0) inputSampleR = -log(1.0+(255*fabs(inputSampleR)))/log(255);
		//end uLaw encode		
		
		inputSampleL *= rezFactor;
		inputSampleR *= rezFactor;
		if (inputSampleL > 0) inputSampleL = floor(inputSampleL);
		if (inputSampleL < 0) inputSampleL = -floor(-inputSampleL);
		if (inputSampleR > 0) inputSampleR = floor(inputSampleR);
		if (inputSampleR < 0) inputSampleR = -floor(-inputSampleR);
		inputSampleL /= rezFactor;
		inputSampleR /= rezFactor;
				
		if (inputSampleL > 1.0) inputSampleL = 1.0; if (inputSampleL < -1.0) inputSampleL = -1.0;
		if (inputSampleL > 0) inputSampleL = (pow(256,fabs(inputSampleL))-1.0) / 255;
		if (inputSampleL < 0) inputSampleL = -(pow(256,fabs(inputSampleL))-1.0) / 255;
		
		if (inputSampleR > 1.0) inputSampleR = 1.0; if (inputSampleR < -1.0) inputSampleR = -1.0;
		if (inputSampleR > 0) inputSampleR = (pow(256,fabs(inputSampleR))-1.0) / 255;
		if (inputSampleR < 0) inputSampleR = -(pow(256,fabs(inputSampleR))-1.0) / 255;
		//end uLaw decode
		
		double blurL = 0.618033988749894848204586-(fabs(inputSampleL - lastSampleL)*overallscale);
		if (blurL < 0.0) blurL = 0.0;
		double blurR = 0.618033988749894848204586-(fabs(inputSampleR - lastSampleR)*overallscale);
		if (blurR < 0.0) blurR = 0.0; //reverse it. Mellow stuff gets blur, bright gets edge
		
		if (position < 1)
		{
			position = freq; //one to ? scaled by overallscale
			heldSampleL = inputSampleL;			
			heldSampleR = inputSampleR;			
		}
		inputSampleL = heldSampleL;
		inputSampleR = heldSampleR;
		lastSampleL = drySampleL;
		lastSampleR = drySampleR;
		position--;
		
		inputSampleL = (inputSampleL * blurL) + (previousHeldL * (1.0-blurL));
		inputSampleR = (inputSampleR * blurR) + (previousHeldR * (1.0-blurR));
		//conditional average: only if we actually have brightness
		previousHeldL = heldSampleL;
		previousHeldR = heldSampleR;
		//end Frequency Derez
		
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
