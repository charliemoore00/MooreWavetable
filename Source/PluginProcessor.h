/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#define GAIN_ID "gain"
#define GAIN_NAME "Gain"
#define MIN_GAIN -60.0f
#define MAX_GAIN 0.0f
#define INIT_GAIN -15.0f

#define WAVE_SHAPE_ID "wave shape"
#define WAVE_SHAPE_NAME "Wave Shape"
#define INIT_SHAPE 0

using namespace juce;

//==============================================================================
/**
*/
class MooreWavetableAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    MooreWavetableAudioProcessor();
    ~MooreWavetableAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    
    void initializeVoices(int numVoices);
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    /*
    //one cycle of the sin function. hold these values in an array
    
    //use this array to access which value of the sin function we're at within the array
    juce::Array<float> waveTable;
    //how big the array is (how many samples make up one cycle)
    double frequency;
    double wtSize;
    double phase;
    double increment;
    double amplitude;
    double currentSampleRate;
     */
    
    //for plugin parameters for automation from DAW
    juce::AudioProcessorValueTreeState treeState;
    
    //for efficient parameter layout for APVTS constructor
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

private:
    
    Synthesiser synth;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MooreWavetableAudioProcessor)
};
