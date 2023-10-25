/*
  ==============================================================================

    CircularBuffer.h
    Created: 18 Jun 2023 12:03:26am
    Author:  JUNLEE

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class CircularBuffer {

public:
	CircularBuffer();

	CircularBuffer(int bufferSize, int delayLength);

	float getData();

	void setData(float data);

	void nextSample();

private:
	juce::AudioSampleBuffer buffer;

	int writeIndex;

	int readIndex;

	int delayLength;
};