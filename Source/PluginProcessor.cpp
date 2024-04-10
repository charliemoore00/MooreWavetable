/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MooreWavetableAudioProcessor::MooreWavetableAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    
    //______________________
    frequency = 440;
    phase = 0;
    wtSize = 1024;
    amplitude = 0.2;
    
    
    //one cycle of a sin wave
    for(int i = 0; i < wtSize; i++)
    {
        waveTable.insert(i, sin(2.0 * juce::MathConstants<double>::pi * i / wtSize));
    }
    
}

MooreWavetableAudioProcessor::~MooreWavetableAudioProcessor()
{
}

//==============================================================================
const juce::String MooreWavetableAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MooreWavetableAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MooreWavetableAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MooreWavetableAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MooreWavetableAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MooreWavetableAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MooreWavetableAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MooreWavetableAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MooreWavetableAudioProcessor::getProgramName (int index)
{
    return {};
}

void MooreWavetableAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MooreWavetableAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
}

void MooreWavetableAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MooreWavetableAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MooreWavetableAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    //auto totalNumInputChannels  = getTotalNumInputChannels();
    //auto totalNumOutputChannels = getTotalNumOutputChannels();
    //
    
    buffer.clear();
    
    //setting up buffers for stereo channels
    float* const leftSpeaker = buffer.getWritePointer(0, buffer.getSample(0, 0));
    float* const rightSpeaker = buffer.getWritePointer(1, buffer.getSample(1, 0));
    
    for(int sample = 0; sample < buffer.getNumSamples(); sample++)
    {
        leftSpeaker[sample] = waveTable[(int)phase] * amplitude;
        rightSpeaker[sample] = waveTable[(int)phase] * amplitude;
        updateFrequency();
    }
}

//==============================================================================
bool MooreWavetableAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MooreWavetableAudioProcessor::createEditor()
{
    return new MooreWavetableAudioProcessorEditor (*this);
}

//==============================================================================
void MooreWavetableAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MooreWavetableAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MooreWavetableAudioProcessor();
}
void MooreWavetableAudioProcessor::updateFrequency()
{
    increment = frequency * wtSize / currentSampleRate;
    phase = fmod(phase + increment, wtSize);
    
}
