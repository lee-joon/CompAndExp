/*
  ==============================================================================

    CompAndExp.cpp
    Created: 18 Jun 2023 12:03:42am
    Author:  JUNLEE

  ==============================================================================
*/

#include "CompAndExp.h"



CompAndExp::CompAndExp()  : DelayBuffer(Delay *2, Delay)
{

}

void CompAndExp::processBlock(juce::AudioBuffer<float>& buffer, float* WritePointer)
{

	for (int i = 0; i < buffer.getNumSamples(); i++)
	{
		const float InputSample = WritePointer[i];

		RMS = (1 - RMSTimeAverage) * RMS + RMSTimeAverage * InputSample * InputSample;

		float X = 10.f * log10(RMS); 

		//float G = std::min({ 0.0f, CompressRatio*(CompressThreshold - X), ExpendRatio*(ExpendTreshold - X)});
		float G = CEFunc( CompressRatio*(CompressThreshold - X), ExpendRatio*(ExpendTreshold - X));

		float f = pow(10.f, G / 20.f);///////ÀÌ°Å ¹ø°æ

		float Coeff = f < Gain ? AttackTime : ReleaseTime;

		Gain = (1.0f - Coeff) * Gain + (Coeff * f);

		WritePointer[i] = DelayBuffer.getData() * Gain;

		DelayBuffer.setData(InputSample);
		DelayBuffer.nextSample();
	}

}

void CompAndExp::SetParaMeter(float CT, float CR, float ET, float ER)
{
	this->CompressThreshold = CT;
	this->CompressRatio		= CR;
	this->ExpendTreshold	= ET;
	this->ExpendRatio		= ER;
}

void CompAndExp::setATRT(float AT, float RT)
{
	this->AttackTime = AT;
	this->ReleaseTime = RT;
}
