/*
  ==============================================================================

    CompAndExp.h
    Created: 18 Jun 2023 12:03:42am
    Author:  JUNLEE

  ==============================================================================
*/

#pragma once														
#include "JuceHeader.h"
#include "CircularBuffer.h"
#include "ComExpFunctor.h"


class CompAndExp {

public :
	CompAndExp();
	
	void processBlock(juce::AudioBuffer<float>&, float* WritePointer);
	void SetParaMeter(float CT, float CR, float ET, float ER);
	void setATRT(float AT, float RT);
	

private:
	float CompressThreshold = 0.0f;
	float CompressRatio = 0.0f; // CR<0
	float ExpendTreshold = 0.0f;
	float ExpendRatio = 0.0f;

	float AttackTime = 0.03f;
	float ReleaseTime = 0.003f;
	float RMSTimeAverage = 0.01f;
	

	int Delay = 20;

	float RMS = 0.0f;
	float Gain = 1;

	CircularBuffer DelayBuffer;
	CompExpFunctor CEFunc;
};