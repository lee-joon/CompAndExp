/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompAndExpAudioProcessorEditor::CompAndExpAudioProcessorEditor (CompAndExpAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	///////////////////////////////////////////////////////////////////////////////////////

	addAndMakeVisible(CompressThresholdSlider);
	CompressThresholdSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	CompressThresholdAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Compress_Threshold", CompressThresholdSlider));

	addAndMakeVisible(CompressThresholdLabel);
	CompressThresholdLabel.setText("Compress Threshold",
		juce::dontSendNotification);
	///////////////////////////////////////////////////////////////////////////////////////

	addAndMakeVisible(CompressRatioSlider);
	CompressRatioSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	CompressRatioAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Compress_Ratio", CompressRatioSlider));

	addAndMakeVisible(CompressRatioLabel);
	CompressRatioLabel.setText("Compress Ratio",
		juce::dontSendNotification);
	///////////////////////////////////////////////////////////////////////////////////////

	addAndMakeVisible(ExpendTresholdSlider);
	ExpendTresholdSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	ExpendTresholdAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Expend_Treshold", ExpendTresholdSlider));

	addAndMakeVisible(ExpendTresholdLabel);
	ExpendTresholdLabel.setText("Expend Treshold",
		juce::dontSendNotification);
	///////////////////////////////////////////////////////////////////////////////////////

	addAndMakeVisible(ExpendRatioSlider);
	ExpendRatioSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	ExpendRatioAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Expend_Ratio", ExpendRatioSlider));

	addAndMakeVisible(ExpendRatioLabel);
	ExpendRatioLabel.setText("Expend Ratio",
		juce::dontSendNotification);
	///////////////////////////////////////////////////////////////////////////////////////

	addAndMakeVisible(AttackTimeSlider);
	AttackTimeSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	AttackTimeAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Attack_Time", AttackTimeSlider));

	addAndMakeVisible(AttackTimeLabel);
	AttackTimeLabel.setText("Attack Time",
		juce::dontSendNotification);
	///////////////////////////////////////////////////////////////////////////////////////

	addAndMakeVisible(ReleaseTimeSlider);
	ReleaseTimeSlider.setSliderStyle(
		juce::Slider::SliderStyle::LinearVertical);
	ReleaseTimeAttachment.reset(
		new juce::AudioProcessorValueTreeState::SliderAttachment(
			vts, "Release_Time", ReleaseTimeSlider));

	addAndMakeVisible(ReleaseTimeLabel);
	ReleaseTimeLabel.setText("Release Time",
		juce::dontSendNotification);
	///////////////////////////////////////////////////////////////////////////////////////


    setSize (1400, 600);
}

CompAndExpAudioProcessorEditor::~CompAndExpAudioProcessorEditor()
{
}

//==============================================================================
void CompAndExpAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void CompAndExpAudioProcessorEditor::resized()
{
	///////////////////////////////////////////////////////////////////////////////////////

	CompressThresholdSlider.setBounds({ 15, 35, 300, 300 });
	CompressThresholdLabel.setBounds({ CompressThresholdSlider.getX() + 30,
									CompressThresholdSlider.getY() - 30,
									200, 50 });
	///////////////////////////////////////////////////////////////////////////////////////

	CompressRatioSlider.setBounds({ 215, 35, 300, 300 });
	CompressRatioLabel.setBounds({ CompressRatioSlider.getX() + 30,
									CompressRatioSlider.getY() - 30,
									200, 50 });
	///////////////////////////////////////////////////////////////////////////////////////

	ExpendTresholdSlider.setBounds({ 415, 35, 300, 300 });
	ExpendTresholdLabel.setBounds({ ExpendTresholdSlider.getX() + 30,
									ExpendTresholdSlider.getY() - 30,
									200, 50 });
	///////////////////////////////////////////////////////////////////////////////////////

	ExpendRatioSlider.setBounds({ 615, 35, 300, 300 });
	ExpendRatioLabel.setBounds({ ExpendRatioSlider.getX() + 30,
									ExpendRatioSlider.getY() - 30,
									200, 50 });
	///////////////////////////////////////////////////////////////////////////////////////

	AttackTimeSlider.setBounds({ 815, 35, 300, 300 });
	AttackTimeLabel.setBounds({ AttackTimeSlider.getX() + 30,
									AttackTimeSlider.getY() - 30,
									200, 50 });
	///////////////////////////////////////////////////////////////////////////////////////

	ReleaseTimeSlider.setBounds({ 1015, 35, 300, 300 });
	ReleaseTimeLabel.setBounds({ ReleaseTimeSlider.getX() + 30,
									ReleaseTimeSlider.getY() - 30,
									200, 50 });

}
