/* ========================================
 *  ElectroHat - ElectroHat.h
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __ElectroHat_H
#include "ElectroHat.h"
#endif

void ElectroHat::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) 
{
    float* in1  =  inputs[0];
    float* in2  =  inputs[1];
    float* out1 = outputs[0];
    float* out2 = outputs[1];
	
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	bool highSample = false;
	if (getSampleRate() > 64000) highSample = true;
	//we will go to another dither for 88 and 96K

	double drySampleL;
	double drySampleR;
	double tempSampleL;
	double tempSampleR;
	double inputSampleL;
	double inputSampleR;
	
	int deSyn = (VstInt32)( A * 5.999 )+1;
	double increment = B;
	double brighten = C;
	double outputlevel = D;
	double wet = E;
	
	if (deSyn == 4) {deSyn = 1; increment = 0.411; brighten = 0.87;}
	//606 preset
	if (deSyn == 5) {deSyn = 2; increment = 0.111; brighten = 1.0;}
	//808 preset
	if (deSyn == 6) {deSyn = 2; increment = 0.299; brighten = 0.359;}
	//909 preset
	int tok = deSyn + 1;
	increment *= 0.98;
	increment += 0.01;
	increment += (double)tok;
	double fosA = increment;
	double fosB = fosA * increment;
	double fosC = fosB * increment;
	double fosD = fosC * increment;
	double fosE = fosD * increment;
	double fosF = fosE * increment;
	int posA = fosA;
	int posB = fosB;
	int posC = fosC;
	int posD = fosD;
	int posE = fosE;
	int posF = fosF;
	int posG = posF*posE*posD*posC*posB; //factorial
    
    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		drySampleL = inputSampleL;
		drySampleR = inputSampleR;
		
		inputSampleL = fabs(inputSampleL)*outputlevel;
		inputSampleR = fabs(inputSampleR)*outputlevel;
		
		if (flip) { //will always be true unless we have high sample rate
			tik++;
			tik = tik % posG;		
			tok = tik * tik; tok = tok % posF;
			tok *= tok; tok = tok % posE;
			tok *= tok; tok = tok % posD;
			tok *= tok; tok = tok % posC;
			tok *= tok; tok = tok % posB;
			tok *= tok; tok = tok % posA;
			
			inputSampleL = tok*inputSampleL;
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 1)) {inputSampleL = -tok*inputSampleL;}		
			if ((abs(lok-tok)>abs(lok+tok))&&(deSyn == 2)) {inputSampleL = -tok*inputSampleL;}
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 3)) {inputSampleL = -tok*inputSampleL;}

			inputSampleR = tok*inputSampleR;
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 1)) {inputSampleR = -tok*inputSampleR;}		
			if ((abs(lok-tok)>abs(lok+tok))&&(deSyn == 2)) {inputSampleR = -tok*inputSampleR;}
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 3)) {inputSampleR = -tok*inputSampleR;}

			lok = tok;

			tempSampleL = inputSampleL;
			inputSampleL = inputSampleL - (lastSampleL*brighten);
			lastSampleL = tempSampleL;

			tempSampleR = inputSampleR;
			inputSampleR = inputSampleR - (lastSampleR*brighten);
			lastSampleR = tempSampleR;
		} else { //we have high sample rate and this is an interpolate sample
			inputSampleL = lastSampleL;
			inputSampleR = lastSampleR;
			//not really interpolating, just sample-and-hold
		}
		
		if (highSample) {
			flip = !flip;
		} else {
			flip = true;
		}
		
		tempSampleL = inputSampleL;
		inputSampleL += storedSampleL;
		storedSampleL = tempSampleL;

		tempSampleR = inputSampleR;
		inputSampleR += storedSampleR;
		storedSampleR = tempSampleR;
		
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

void ElectroHat::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames) 
{
    double* in1  =  inputs[0];
    double* in2  =  inputs[1];
    double* out1 = outputs[0];
    double* out2 = outputs[1];

	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= getSampleRate();
	bool highSample = false;
	if (getSampleRate() > 64000) highSample = true;
	//we will go to another dither for 88 and 96K
	
	double drySampleL;
	double drySampleR;
	double tempSampleL;
	double tempSampleR;
	double inputSampleL;
	double inputSampleR;
	
	int deSyn = (VstInt32)( A * 5.999 )+1;
	double increment = B;
	double brighten = C;
	double outputlevel = D;
	double wet = E;
	
	if (deSyn == 4) {deSyn = 1; increment = 0.411; brighten = 0.87;}
	//606 preset
	if (deSyn == 5) {deSyn = 2; increment = 0.111; brighten = 1.0;}
	//808 preset
	if (deSyn == 6) {deSyn = 2; increment = 0.299; brighten = 0.359;}
	//909 preset
	int tok = deSyn + 1;
	increment *= 0.98;
	increment += 0.01;
	increment += (double)tok;
	double fosA = increment;
	double fosB = fosA * increment;
	double fosC = fosB * increment;
	double fosD = fosC * increment;
	double fosE = fosD * increment;
	double fosF = fosE * increment;
	int posA = fosA;
	int posB = fosB;
	int posC = fosC;
	int posD = fosD;
	int posE = fosE;
	int posF = fosF;
	int posG = posF*posE*posD*posC*posB; //factorial
	
    while (--sampleFrames >= 0)
    {
		inputSampleL = *in1;
		inputSampleR = *in2;
		drySampleL = inputSampleL;
		drySampleR = inputSampleR;
		
		inputSampleL = fabs(inputSampleL)*outputlevel;
		inputSampleR = fabs(inputSampleR)*outputlevel;
		
		if (flip) { //will always be true unless we have high sample rate
			tik++;
			tik = tik % posG;		
			tok = tik * tik; tok = tok % posF;
			tok *= tok; tok = tok % posE;
			tok *= tok; tok = tok % posD;
			tok *= tok; tok = tok % posC;
			tok *= tok; tok = tok % posB;
			tok *= tok; tok = tok % posA;
			
			inputSampleL = tok*inputSampleL;
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 1)) {inputSampleL = -tok*inputSampleL;}		
			if ((abs(lok-tok)>abs(lok+tok))&&(deSyn == 2)) {inputSampleL = -tok*inputSampleL;}
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 3)) {inputSampleL = -tok*inputSampleL;}
			
			inputSampleR = tok*inputSampleR;
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 1)) {inputSampleR = -tok*inputSampleR;}		
			if ((abs(lok-tok)>abs(lok+tok))&&(deSyn == 2)) {inputSampleR = -tok*inputSampleR;}
			if ((abs(lok-tok)<abs(lok+tok))&&(deSyn == 3)) {inputSampleR = -tok*inputSampleR;}
			
			lok = tok;
			
			tempSampleL = inputSampleL;
			inputSampleL = inputSampleL - (lastSampleL*brighten);
			lastSampleL = tempSampleL;
			
			tempSampleR = inputSampleR;
			inputSampleR = inputSampleR - (lastSampleR*brighten);
			lastSampleR = tempSampleR;
		} else { //we have high sample rate and this is an interpolate sample
			inputSampleL = lastSampleL;
			inputSampleR = lastSampleR;
			//not really interpolating, just sample-and-hold
		}
		
		if (highSample) {
			flip = !flip;
		} else {
			flip = true;
		}
		
		tempSampleL = inputSampleL;
		inputSampleL += storedSampleL;
		storedSampleL = tempSampleL;
		
		tempSampleR = inputSampleR;
		inputSampleR += storedSampleR;
		storedSampleR = tempSampleR;
		
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