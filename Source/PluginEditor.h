/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CompAndExpAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CompAndExpAudioProcessorEditor (CompAndExpAudioProcessor&, juce::AudioProcessorValueTreeState& vts);
    ~CompAndExpAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CompAndExpAudioProcessor& audioProcessor;

	juce::Slider CompressThresholdSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> CompressThresholdAttachment;
	juce::Label CompressThresholdLabel;

	juce::Slider CompressRatioSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> CompressRatioAttachment;
	juce::Label CompressRatioLabel;

	juce::Slider ExpendTresholdSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ExpendTresholdAttachment;
	juce::Label ExpendTresholdLabel;

	juce::Slider ExpendRatioSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ExpendRatioAttachment;
	juce::Label ExpendRatioLabel;

	juce::Slider AttackTimeSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> AttackTimeAttachment;
	juce::Label AttackTimeLabel;

	juce::Slider ReleaseTimeSlider;
	std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ReleaseTimeAttachment;
	juce::Label ReleaseTimeLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompAndExpAudioProcessorEditor)
};
