/*
*	File:		ZAcidLowpass.cpp
*	
*	Version:	1.0
* 
*	Created:	2/10/26
*	
*	Copyright:  Copyright © 2026 Airwindows, Airwindows uses the MIT license
* 
*	Disclaimer:	IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc. ("Apple") in 
*				consideration of your agreement to the following terms, and your use, installation, modification 
*				or redistribution of this Apple software constitutes acceptance of these terms.  If you do 
*				not agree with these terms, please do not use, install, modify or redistribute this Apple 
*				software.
*
*				In consideration of your agreement to abide by the following terms, and subject to these terms, 
*				Apple grants you a personal, non-exclusive license, under Apple's copyrights in this 
*				original Apple software (the "Apple Software"), to use, reproduce, modify and redistribute the 
*				Apple Software, with or without modifications, in source and/or binary forms; provided that if you 
*				redistribute the Apple Software in its entirety and without modifications, you must retain this 
*				notice and the following text and disclaimers in all such redistributions of the Apple Software. 
*				Neither the name, trademarks, service marks or logos of Apple Computer, Inc. may be used to 
*				endorse or promote products derived from the Apple Software without specific prior written 
*				permission from Apple.  Except as expressly stated in this notice, no other rights or 
*				licenses, express or implied, are granted by Apple herein, including but not limited to any 
*				patent rights that may be infringed by your derivative works or by other works in which the 
*				Apple Software may be incorporated.
*
*				The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO WARRANTIES, EXPRESS OR 
*				IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY 
*				AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE 
*				OR IN COMBINATION WITH YOUR PRODUCTS.
*
*				IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL 
*				DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS 
*				OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
*				REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER 
*				UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN 
*				IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
/*=============================================================================
	ZAcidLowpass.cpp
	
=============================================================================*/
#include "ZAcidLowpass.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

COMPONENT_ENTRY(ZAcidLowpass)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::ZAcidLowpass
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ZAcidLowpass::ZAcidLowpass(AudioUnit component)
	: AUEffectBase(component)
{
	CreateElements();
	Globals()->UseIndexedParameters(kNumberOfParameters);
	SetParameter(kParam_A, kDefaultValue_ParamA );
	SetParameter(kParam_B, kDefaultValue_ParamB );
	SetParameter(kParam_C, kDefaultValue_ParamC );
	SetParameter(kParam_D, kDefaultValue_ParamD );
	SetParameter(kParam_E, kDefaultValue_ParamE );
	SetParameter(kParam_F, kDefaultValue_ParamF );
         
#if AU_DEBUG_DISPATCHER
	mDebugDispatcher = new AUDebugDispatcher (this);
#endif
	
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::GetParameterValueStrings
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			ZAcidLowpass::GetParameterValueStrings(AudioUnitScope		inScope,
                                                                AudioUnitParameterID	inParameterID,
                                                                CFArrayRef *		outStrings)
{
        
    return kAudioUnitErr_InvalidProperty;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::GetParameterInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			ZAcidLowpass::GetParameterInfo(AudioUnitScope		inScope,
                                                        AudioUnitParameterID	inParameterID,
                                                        AudioUnitParameterInfo	&outParameterInfo )
{
	ComponentResult result = noErr;

	outParameterInfo.flags = 	kAudioUnitParameterFlag_IsWritable
						|		kAudioUnitParameterFlag_IsReadable;
    
    if (inScope == kAudioUnitScope_Global) {
        switch(inParameterID)
        {
            case kParam_A:
                AUBase::FillInParameterName (outParameterInfo, kParameterAName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamA;
                break;
            case kParam_B:
                AUBase::FillInParameterName (outParameterInfo, kParameterBName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamB;
                break;
            case kParam_C:
                AUBase::FillInParameterName (outParameterInfo, kParameterCName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamC;
                break;
            case kParam_D:
                AUBase::FillInParameterName (outParameterInfo, kParameterDName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamD;
                break;
            case kParam_E:
                AUBase::FillInParameterName (outParameterInfo, kParameterEName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamE;
                break;
            case kParam_F:
                AUBase::FillInParameterName (outParameterInfo, kParameterFName, false);
                outParameterInfo.unit = kAudioUnitParameterUnit_Generic;
                outParameterInfo.minValue = 0.0;
                outParameterInfo.maxValue = 1.0;
                outParameterInfo.defaultValue = kDefaultValue_ParamF;
                break;
           default:
                result = kAudioUnitErr_InvalidParameter;
                break;
            }
	} else {
        result = kAudioUnitErr_InvalidParameter;
    }
    


	return result;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::GetPropertyInfo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			ZAcidLowpass::GetPropertyInfo (AudioUnitPropertyID	inID,
                                                        AudioUnitScope		inScope,
                                                        AudioUnitElement	inElement,
                                                        UInt32 &		outDataSize,
                                                        Boolean &		outWritable)
{
	return AUEffectBase::GetPropertyInfo (inID, inScope, inElement, outDataSize, outWritable);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::GetProperty
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult			ZAcidLowpass::GetProperty(	AudioUnitPropertyID inID,
                                                        AudioUnitScope 		inScope,
                                                        AudioUnitElement 	inElement,
                                                        void *			outData )
{
	return AUEffectBase::GetProperty (inID, inScope, inElement, outData);
}

//	ZAcidLowpass::Initialize
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ComponentResult ZAcidLowpass::Initialize()
{
    ComponentResult result = AUEffectBase::Initialize();
    if (result == noErr)
        Reset(kAudioUnitScope_Global, 0);
    return result;
}

#pragma mark ____ZAcidLowpassEffectKernel



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::ZAcidLowpassKernel::Reset()
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		ZAcidLowpass::ZAcidLowpassKernel::Reset()
{
	for (int x = 0; x < bez_total; x++) {bezA[x] = 0.0;}
	bezA[bez_cycle] = 1.0;
	for (int x = 0; x < 11; x++) {biquadE[x] = 0.0; biquadF[x] = 0.0;}
	iirSampleA = 0.0;
	cutoffA = 0.5; cutoffB = 0.5;
	overA = 0.0; overB = 0.0;
	underA = 1.0; underB = 1.0;
	meltdownA = 0.0; meltdownB = 0.0;
	inTrimA = 0.1; inTrimB = 0.1;
	outTrimA = 1.0; outTrimB = 1.0;
	
	fpd = 1.0; while (fpd < 16386) fpd = rand()*UINT32_MAX;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	ZAcidLowpass::ZAcidLowpassKernel::Process
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void		ZAcidLowpass::ZAcidLowpassKernel::Process(	const Float32 	*inSourceP,
                                                    Float32		 	*inDestP,
                                                    UInt32 			inFramesToProcess,
                                                    UInt32			inNumChannels, 
                                                    bool			&ioSilence )
{
	UInt32 nSampleFrames = inFramesToProcess;
	const Float32 *sourceP = inSourceP;
	Float32 *destP = inDestP;
	double overallscale = 1.0;
	overallscale /= 44100.0;
	overallscale *= GetSampleRate();
	
	cutoffA = cutoffB;
	cutoffB = pow(GetParameter( kParam_A ),3.0)/overallscale;
	cutoffB /= (2.0/pow(overallscale,0.5-((overallscale-1.0)*0.0375)));
	if (cutoffB < 0.0001) cutoffB = 0.0001; if (cutoffB > 1.0) cutoffB = 1.0;
	overA = overB;
	overB = GetParameter( kParam_B );
	underA = underB;
	underB = GetParameter( kParam_C );
	meltdownA = meltdownB;
	meltdownB = GetParameter( kParam_D );
	
	//opamp stuff
	inTrimA = inTrimB;
	inTrimB = GetParameter( kParam_E )*10.0;
	inTrimB *= inTrimB; inTrimB *= inTrimB;
	outTrimA = outTrimB;
	outTrimB = GetParameter( kParam_F );
	
	double iirAmountA = 0.00069/overallscale;
	biquadF[0] = biquadE[0] = 15500.0 / GetSampleRate();
    biquadF[1] = biquadE[1] = 0.935;
	double K = tan(M_PI * biquadE[0]); //lowpass
	double norm = 1.0 / (1.0 + K / biquadE[1] + K * K);
	biquadE[2] = K * K * norm;
	biquadE[3] = 2.0 * biquadE[2];
	biquadE[4] = biquadE[2];
	biquadE[5] = 2.0 * (K * K - 1.0) * norm;
	biquadE[6] = (1.0 - K / biquadE[1] + K * K) * norm;
	for (int x = 0; x < 7; x++) biquadF[x] = biquadE[x];
	//end opamp stuff	
	
	while (nSampleFrames-- > 0) {
		double inputSampleL = *sourceP;
		if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpd * 1.18e-17;
		
		double temp = (double)nSampleFrames/inFramesToProcess;
		double cutoff = (cutoffA*temp)+(cutoffB*(1.0-temp));
		double over = (overA*temp)+(overB*(1.0-temp));
		double under = (underA*temp)+(underB*(1.0-temp));
		double meltdown = (meltdownA*temp)+(meltdownB*(1.0-temp));
		double inTrim = (inTrimA*temp)+(inTrimB*(1.0-temp));
		double outTrim = (outTrimA*temp)+(outTrimB*(1.0-temp));
		double acidTrim = 1.0-pow(cutoff*0.5,1.0/(cutoff*0.5));
		
		bezA[bez_cycle] += cutoff;
		bezA[bez_SampL] += (inputSampleL * cutoff);
		
		if (bezA[bez_cycle] > 1.0) { //hit the end point and we do a reverb sample
			bezA[bez_cycle] -= 1.0;
			bezA[bez_DL] = bezA[bez_CL];
			bezA[bez_CL] = bezA[bez_BL];
			bezA[bez_BL] = bezA[bez_AL];
			bezA[bez_AL] = (bezA[bez_SampL]*(1.0-meltdown))+(inputSampleL*meltdown);
			bezA[bez_SampL] = 0.0;
		}
		
		double X = bezA[bez_cycle]*acidTrim;
		double midL = bezA[bez_DL] * pow(1.0-X,3.0);
		midL += bezA[bez_CL] * 3.0 * pow(1.0-X,2.0) * X;
		midL += bezA[bez_BL] * 3.0 * (1.0-X) * X * X;
		midL += bezA[bez_AL] * pow(X,3.0);
		
		inputSampleL = (midL*under) + ((inputSampleL - midL)*over);
		
		if (inTrim != 1.0) inputSampleL *= inTrim;
		
		//opamp stage
		if (fabs(iirSampleA)<1.18e-37) iirSampleA = 0.0;
		iirSampleA = (iirSampleA * (1.0 - iirAmountA)) + (inputSampleL * iirAmountA);
		inputSampleL -= iirSampleA;
		
		double outSample = biquadE[2]*inputSampleL+biquadE[3]*biquadE[7]+biquadE[4]*biquadE[8]-biquadE[5]*biquadE[9]-biquadE[6]*biquadE[10];
		biquadE[8] = biquadE[7]; biquadE[7] = inputSampleL; inputSampleL = outSample; biquadE[10] = biquadE[9]; biquadE[9] = inputSampleL; //DF1		
		
		if (inputSampleL > 1.0) inputSampleL = 1.0; if (inputSampleL < -1.0) inputSampleL = -1.0;
		inputSampleL -= (inputSampleL*inputSampleL*inputSampleL*inputSampleL*inputSampleL*0.1768);
		
		outSample = biquadF[2]*inputSampleL+biquadF[3]*biquadF[7]+biquadF[4]*biquadF[8]-biquadF[5]*biquadF[9]-biquadF[6]*biquadF[10];
		biquadF[8] = biquadF[7]; biquadF[7] = inputSampleL; inputSampleL = outSample; biquadF[10] = biquadF[9]; biquadF[9] = inputSampleL; //DF1
		
		if (outTrim != 1.0) inputSampleL *= outTrim;		
		//end opamp stage
		
		//begin 32 bit floating point dither
		int expon; frexpf((float)inputSampleL, &expon);
		fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
		inputSampleL += ((double(fpd)-uint32_t(0x7fffffff)) * 5.5e-36l * pow(2,expon+62));
		//end 32 bit floating point dither
		
		*destP = inputSampleL;
		
		sourceP += inNumChannels; destP += inNumChannels;
	}
}

