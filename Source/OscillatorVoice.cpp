/**
  ==============================================================================

    NAME: MooreWavetable
    AUTHOR: Charlie Moore & McLean Macionis
    DATE: April 3, 2024
    COMMENTS: Pitter patter!
 
    ----------------------------------------------------------------------------
 
    This file contains the basic framework code for a JUCE plugin processor.
    
    To open this project as a plugin in Ableton Live, do the following:
    1. Navigate to "Product" in the menu bar
    2. Select "Scheme" followed by "Edit Scheme" (Command Shift <)
    3. Select "Release" under "Build Configuration"
    4. Select "Ableton Live 11 Suite.app" under "Executable"

  ==============================================================================
*/

#include "OscillatorVoice.h"
#include <iostream>


OscillatorVoice::OscillatorVoice ()
{
    initializeEG();
    prepareNoiseWavetable();
    setFrequency(scale.midiNoteArray[48], SAMPLERATE);
}

OscillatorVoice::~OscillatorVoice() {}

//==========================================================================

void OscillatorVoice::pitchWheelMoved (int newPitchWheelValue) {}

void OscillatorVoice::aftertouchChanged (int newAftertouchValue) {}

void OscillatorVoice::channelPressureChanged (int newChannelPressureValue) {}

void OscillatorVoice::setCurrentPlaybackSampleRate (double newRate) {}

void OscillatorVoice::controllerMoved (int controllerNumber, int newControllerValue) 
{
}

void OscillatorVoice::stopNote (float  velocity, bool allowTailOff)
{
    allowTailOff = false;
    //DEBUG PRINT
    std::cout << "stopNote\n";
    EG.noteOff();
}

void OscillatorVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) 
{
    EG.noteOn();
    float frequency = scale.midiNoteArray[midiNoteNumber];
    setFrequency(frequency, SAMPLERATE);
    
    //DEBUG PRINT
    std::cout << "startNote; frequency: " << frequency << "\n";
}

bool OscillatorVoice::canPlaySound (SynthesiserSound*) { return true; }

bool OscillatorVoice::isVoiceActive () const { return true; }

bool OscillatorVoice::isPlayingChannel (int midiChannel) const { return true; }

//==========================================================================

void OscillatorVoice::renderNextBlock (AudioBuffer<float>  &outputBuffer, int startSample, int numSamples)
{
    //DEBUG PRINT
    //std::cout << "renderNextBlock";
    
    /// Clear the output buffer.
    outputBuffer.clear();
    
    /// Dirty sinewave Generator
    //while (--numSamples >= 0)
    for (int i = 0; i < numSamples; i++)
    {
        float currentSample = getNextSample();
        
        float EG_currentSample = EG.getNextSample();
        currentSample *= EG_currentSample;
        
        /// We then load our random sample into the audio buffer, which is passed along to the PluginProcessor.
        for (int channel = outputBuffer.getNumChannels(); --channel >= 0;) 
        {
            outputBuffer.addSample(channel, startSample, currentSample);
        }
        
        /// Increment the current sample by 1.
        ++startSample;
    }
    
    /*
    /// White noise generator.
    while (--numSamples >= 0)
    {
        /// To create white noise, we need a random value between -1.0 and 1.0. We obtain these values by using the Random class, scaling the value by 2.0, and then subtracting 1.0.
        float randomSample = (noiseGenerator.nextFloat() * 2.0f) - 1.0f;
        
        /// We then load our random sample into the audio buffer, which is passed along to the PluginProcessor.
        for (int channel = outputBuffer.getNumChannels(); --channel >= 0;) { outputBuffer.addSample(channel, startSample, randomSample); }
        
        /// Increment the current sample by 1.
        ++startSample;
    }
    */
}

void OscillatorVoice::renderNextBlock (AudioBuffer<double>  &outputBuffer, int startSample, int numSamples) {}

//==========================================================================

void OscillatorVoice::prepareNoiseWavetable()
{
    /// Reserve the noiseWavetable size before initializing the program.
    noiseWavetable.reserve(WAVETABLE_SIZE);
    
    /// Fill noiseWavetable with samples.
    for (int index = 0; ++index < noiseWavetable.capacity();)
    {
        /// To create white noise, we need a random value between -1.0 and 1.0.
        /// We obtain these values by using the Random class, scaling the value by 2.0, and then subtracting 1.0.
        float randomSample = (noiseGenerator.nextFloat() * 2.0f) - 1.0f;
        
        /// Insert a random value into noiseWavetable.
        noiseWavetable.push_back(randomSample);
    }
}

//==========================================================================

void OscillatorVoice::initializeEG()
{
    EG.setSampleRate(SAMPLERATE);
    EG.setParameters(EG_Parameters);
    EG.reset();
}

void OscillatorVoice::setFrequency (float frequency, float sampleRate)
{
    auto cyclesPerSample = frequency / sampleRate;
    phaseDelta = cyclesPerSample * static_cast<float>(M_2_PI);
}

float OscillatorVoice::getNextSample()
{
    auto currentSample = sin(phase);
    updateAngle();
    return currentSample;
}

void OscillatorVoice::updateAngle()
{
    phase += phaseDelta;
    if (phase >= static_cast<float>(M_2_PI)) phase -= static_cast<float>(M_2_PI);
}


