/*
 *  Acceleration - AccelerationProc.cpp
 *  Copyright (c) 2016 airwindows, Airwindows uses the MIT license
 *  Copyright (c) 2026 narglab
*/

#ifndef __Acceleration_H
#include "Acceleration.h"
#endif

void Acceleration::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames)
{
	float *in1 = inputs[0];
	float *in2 = inputs[1];
	float *out1 = outputs[0];
	float *out2 = outputs[1];

	double overallscale = 1.0;
	overallscale *= inv_reference_samplerate;
	overallscale *= getSampleRate();

	const double intensity = A * A * A * (32 / overallscale);
	const double intensity_sq = intensity * intensity;
	double wet = B;

	double senseL;
	double smoothL;
	double senseR;
	double smoothR;
	double accumulatorSample;
	double drySampleL;
	double drySampleR;
	double inputSampleL;
	double inputSampleR;

	while (--sampleFrames >= 0)
	{
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (std::abs(inputSampleL) < 1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (std::abs(inputSampleR) < 1.18e-23) inputSampleR = fpdR * 1.18e-17;
		drySampleL = inputSampleL;
		drySampleR = inputSampleR;

		s3L = s2L;
		s2L = s1L;
		s1L = inputSampleL;
		smoothL = (s3L + s2L + s1L) * inv_3;
		const double diff_s1L_s2L = s1L - s2L;
		m1L = diff_s1L_s2L * (diff_s1L_s2L * inv_one_point_three);
		m2L = (s2L - s3L) * (diff_s1L_s2L * inv_one_point_three);
		senseL = std::abs(m1L - m2L);
		senseL = intensity_sq * senseL;
		o3L = o2L;
		o2L = o1L;
		o1L = senseL;
		senseL = o2L > senseL ? o2L : senseL;
		senseL = o3L > senseL ? o3L : senseL;
		//sense on the most intense

		s3R = s2R;
		s2R = s1R;
		s1R = inputSampleR;
		smoothR = (s3R + s2R + s1R) * inv_3;
		const double diff_s1R_s2R = s1R - s2R;
		m1R = diff_s1R_s2R * (diff_s1R_s2R * inv_one_point_three);
		m2R = (s2R - s3R) * (diff_s1R_s2R * inv_one_point_three);
		senseR = std::abs(m1R - m2R);
		senseR = intensity_sq * senseR;
		o3R = o2R;
		o2R = o1R;
		o1R = senseR;
		senseR = o2R > senseR ? o2R : senseR;
		senseR = o3R > senseR ? o3R : senseR;
		//sense on the most intense

		senseL = senseL > 1.0 ? 1.0 : senseL;
		senseR = senseR > 1.0 ? 1.0 : senseR;

		inputSampleL *= (1.0 - senseL);
		inputSampleR *= (1.0 - senseR);

		inputSampleL += (smoothL * senseL);
		inputSampleR += (smoothR * senseR);

		senseL *= 0.5;
		senseR *= 0.5;

		accumulatorSample = (ataLastOutL * senseL) + (inputSampleL * (1.0 - senseL));
		ataLastOutL = inputSampleL;
		inputSampleL = accumulatorSample;

		accumulatorSample = (ataLastOutR * senseR) + (inputSampleR * (1.0 - senseR));
		ataLastOutR = inputSampleR;
		inputSampleR = accumulatorSample;

		if (wet != 1.0)
		{
			const double om_wet = 1.0 - wet;
			inputSampleL = (inputSampleL * wet) + (drySampleL * om_wet);
			inputSampleR = (inputSampleR * wet) + (drySampleR * om_wet);
		}

		//begin 32 bit stereo floating point dither
		int expon;
		constexpr uint32_t magic_number_dither = uint32_t(0x7fffffff);
		constexpr uint64_t two_pow_62 = 1ULL << 62;
		std::frexp((float) inputSampleL, &expon);
		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
		uint64_t power_of_twoL = two_pow_62 << expon;
		double dither_factorL = 5.5e-36l * power_of_twoL;
		inputSampleL += ((double(fpdL) - magic_number_dither) * dither_factorL);
		std::frexp((float) inputSampleR, &expon);
		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
		uint64_t power_of_twoR = two_pow_62 << expon;
		double dither_factorR = 5.5e-36l * power_of_twoR;
		inputSampleR += ((double(fpdR) - magic_number_dither) * dither_factorR);
		//end 32 bit stereo floating point dither

		*out1 = static_cast<float>(inputSampleL);
		*out2 = static_cast<float>(inputSampleR);

		*in1++;
		*in2++;
		*out1++;
		*out2++;
	}
}

void Acceleration::processDoubleReplacing(double **inputs, double **outputs, VstInt32 sampleFrames)
{
	double *in1 = inputs[0];
	double *in2 = inputs[1];
	double *out1 = outputs[0];
	double *out2 = outputs[1];

	double overallscale = 1.0;
	overallscale *= inv_reference_samplerate;
	overallscale *= getSampleRate();

	const double intensity = A * A * A * (32 / overallscale);
	const double intensity_sq = intensity * intensity;
	const double wet = B;

	double senseL;
	double smoothL;
	double senseR;
	double smoothR;
	double accumulatorSample;
	double drySampleL;
	double drySampleR;
	double inputSampleL;
	double inputSampleR;

	while (--sampleFrames >= 0)
	{
		inputSampleL = *in1;
		inputSampleR = *in2;
		if (std::abs(inputSampleL) < 1.18e-23) inputSampleL = fpdL * 1.18e-17;
		if (std::abs(inputSampleR) < 1.18e-23) inputSampleR = fpdR * 1.18e-17;
		drySampleL = inputSampleL;
		drySampleR = inputSampleR;

		s3L = s2L;
		s2L = s1L;
		s1L = inputSampleL;
		smoothL = (s3L + s2L + s1L) * inv_3;
		const double diff_s1L_s2L = s1L - s2L;
		m1L = diff_s1L_s2L * (diff_s1L_s2L * inv_one_point_three);
		m2L = (s2L - s3L) * (diff_s1L_s2L * inv_one_point_three);
		senseL = std::abs(m1L - m2L);
		senseL = intensity_sq * senseL;
		o3L = o2L;
		o2L = o1L;
		o1L = senseL;
		senseL = o2L > senseL ? o2L : senseL;
		senseL = o3L > senseL ? o3L : senseL;
		//sense on the most intense

		s3R = s2R;
		s2R = s1R;
		s1R = inputSampleR;
		smoothR = (s3R + s2R + s1R) * inv_3;
		const double diff_s1R_s2R = s1R - s2R;
		m1R = diff_s1R_s2R * (diff_s1R_s2R * inv_one_point_three);
		m2R = (s2R - s3R) * (diff_s1R_s2R * inv_one_point_three);
		senseR = std::abs(m1R - m2R);
		senseR = intensity_sq * senseR;
		o3R = o2R;
		o2R = o1R;
		o1R = senseR;
		senseR = o2R > senseR ? o2R : senseR;
		senseR = o3R > senseR ? o3R : senseR;
		//sense on the most intense

		senseL = senseL > 1.0 ? 1.0 : senseL;
		senseR = senseR > 1.0 ? 1.0 : senseR;

		inputSampleL *= (1.0 - senseL);
		inputSampleR *= (1.0 - senseR);

		inputSampleL += (smoothL * senseL);
		inputSampleR += (smoothR * senseR);

		senseL *= 0.5;
		senseR *= 0.5;

		accumulatorSample = (ataLastOutL * senseL) + (inputSampleL * (1.0 - senseL));
		ataLastOutL = inputSampleL;
		inputSampleL = accumulatorSample;

		accumulatorSample = (ataLastOutR * senseR) + (inputSampleR * (1.0 - senseR));
		ataLastOutR = inputSampleR;
		inputSampleR = accumulatorSample;

		if (wet != 1.0)
		{
			const double om_wet = 1.0 - wet;
			inputSampleL = (inputSampleL * wet) + (drySampleL * om_wet);
			inputSampleR = (inputSampleR * wet) + (drySampleR * om_wet);
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