/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompAndExpAudioProcessor::CompAndExpAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else
	:	
#endif
parameters(*this,
	nullptr,
	juce::Identifier("CompAndExp"),
	{ std::make_unique<juce::AudioParameterFloat>(
		"Compress_Threshold",
		"Compress Threshold",
		juce::NormalisableRange{-60.f,
								0.f,
								0.1f,
								0.2f,
								false},
		0.f),
	std::make_unique<juce::AudioParameterFloat>(
		"Compress_Ratio",
		"Compress Ratio",
		juce::Range{0.f,1.f},
		0.0f),
	std::make_unique<juce::AudioParameterFloat>(
		"Expend_Treshold",
		"Expend Treshold",
		juce::NormalisableRange{-100.f,
								0.f,
								0.1f,
								0.2f,
								false},
		-30.f),
	std::make_unique<juce::AudioParameterFloat>(
		"Expend_Ratio",
		"Expend Ratio",
		juce::Range{-1.f,0.f},
		-1.f),
	std::make_unique<juce::AudioParameterFloat>(
		"Attack_Time",
		"Attack Time",
		juce::Range{0.f,1.f},
		0.8f),std::make_unique<juce::AudioParameterFloat>(
		"Release_Time",
		"Release Time",
		juce::Range{0.f,1.f},
		0.01f) })
{
	CompressThreshold	= parameters.getRawParameterValue("Compress_Threshold");
	CompressRatio		= parameters.getRawParameterValue("Compress_Ratio");
	ExpendTreshold		= parameters.getRawParameterValue("Expend_Treshold");
	ExpendRatio			= parameters.getRawParameterValue("Expend_Ratio");
	AttackTime			= parameters.getRawParameterValue("Attack_Time");
	ReleaseTime			= parameters.getRawParameterValue("Release_Time");
}

CompAndExpAudioProcessor::~CompAndExpAudioProcessor()
{
}

//==============================================================================
const juce::String CompAndExpAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompAndExpAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompAndExpAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompAndExpAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompAndExpAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompAndExpAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompAndExpAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompAndExpAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CompAndExpAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompAndExpAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CompAndExpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	allbuffer = juce::Array<CompAndExp>();
	for (int channel = 0; channel < getMainBusNumOutputChannels(); channel++)
	{
		allbuffer.add(CompAndExp());
	}
}

void CompAndExpAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompAndExpAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CompAndExpAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	
	const auto CT = CompressThreshold->load();
	const auto CR = CompressRatio->load();
	const auto ET = ExpendTreshold->load();
	const auto ER = ExpendRatio->load();
	const auto AT = AttackTime->load();
	const auto RT = ReleaseTime->load();

    for(int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

		CompAndExp* CompAndExpChan = &allbuffer.getReference(channel);
		CompAndExpChan->setATRT(AT, RT);
		CompAndExpChan->SetParaMeter(CT, CR, ET, ER);
		CompAndExpChan->processBlock(buffer, channelData); 
    }
}

//==============================================================================
bool CompAndExpAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompAndExpAudioProcessor::createEditor()
{
	return new CompAndExpAudioProcessorEditor(*this, parameters);
}

//==============================================================================
void CompAndExpAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompAndExpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompAndExpAudioProcessor();
}
