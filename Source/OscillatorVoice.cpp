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
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include <iostream>



OscillatorVoice::OscillatorVoice(MooreWavetableAudioProcessor& processor)
: audioProcessor(processor)
{
    
    
    //waveShapeID = processorEditor;
    //waveShapeMenu.getSelectedItemIndex();
    initializeEG();
    prepareNoiseWavetable();
    setFrequency(scale.midiNoteArray[48], SAMPLERATE);
    
    //mTwoPi(),
    //mFrequency(0.0),
    //mPhase(0.0),
    //mPhaseIncrement(0.0),
    //mSampleRate(44100.0),
    //mLevel(0.5) //changed from 0.0 to 0.5 to test
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
    if (allowTailOff)
    {
        // Only trigger the note-off if it hasn't already been called
        if (!EG.isActive() || EG.isActive())
        {
            EG.noteOff();
        }
    }
    else
    {
        // Immediate stop
        clearCurrentNote();
    }
}

void OscillatorVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) 
{
    
    /*
    //first attempt
    EG.noteOn();
    float frequency = scale.midiNoteArray[midiNoteNumber];
    setFrequency(frequency, SAMPLERATE);
    
    //DEBUG PRINT
    std::cout << "startNote; frequency: " << frequency << "\n";
    */
    
    // reset variables based on the midi note number and velocity
    //mPhase = 0.0;
    mLevel = velocity;
    
    // calculate cycles per sample based on incoming midi note
    double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    double cyclesPerSample = cyclesPerSecond / mSampleRate;
    
    // set our phase increment which controlls the actual frequency of the oscillator
    mPhaseIncrement = cyclesPerSample * mTwoPi;
    
    
    EG.noteOn();
    mFrequency = scale.midiNoteArray[midiNoteNumber];

}

bool OscillatorVoice::canPlaySound (SynthesiserSound*) { return true; }

bool OscillatorVoice::isVoiceActive () const { return true; }

bool OscillatorVoice::isPlayingChannel (int midiChannel) const { return true; }

//==========================================================================

void OscillatorVoice::renderNextBlock (AudioBuffer<float>  &outputBuffer, int startSample, int numSamples)
{
    float waveShape = 0.0f;  // Default value

    // Assuming WAVE_SHAPE_ID is defined correctly and corresponds to the ID used in creating the parameter
    auto waveShapeParam = audioProcessor.treeState.getRawParameterValue(WAVE_SHAPE_ID);
    if (waveShapeParam != nullptr) {
        waveShape = waveShapeParam->load();  // Load the value from the std::atomic<float>
    }
    
    waveShape = static_cast<int>(waveShape);
    mOscillatorMode = waveShape + 1;
    
    /*
    
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
     
     */
    switch (mOscillatorMode) {
            
        case 1: //SINE
            for (int i = 0; i < numSamples; i++)
            {
                float EG_currentSample = EG.getNextSample();
                const float currentSample = (float) (sin(mPhase) * EG_currentSample * mLevel);
                
                for (int channel = outputBuffer.getNumChannels(); --channel >=0;) 
                {
                    outputBuffer.addSample(channel, startSample, currentSample);
                }
                mPhase += mPhaseIncrement;
                ++startSample;
                while (mPhase >= mTwoPi) {
                    mPhase -= mTwoPi;
                }
            }
            break;
            
        case 2: //SAW
            /*
             - mPhase goes from 0 upwards, and jumps back to 0 when it reaches mTwoPi.
             - Thus (mPhase / mTwoPi) goes from 0 upwards and jumps back to 0 when it reaches 1.
             - This means that (2.0 * mPhase / mTwoPi) goes from 0 up and jumps back at 2
             - When mPhase is 0, the expression 1.0 - (2.0 * mPhase / mTwoPi) is 1. While mPhase goes upwards, the expression goes downwards and jumps back to 1 when it reaches -1.
             - So! We have a downward saw wave
             */
            for (int i = 0; i < numSamples; i++)
            {
                float EG_currentSample = EG.getNextSample();
                const float currentSample = (float) (1.0 - (2.0 * (mPhase/mTwoPi))) * EG_currentSample * mLevel;
                
                for (int channel = outputBuffer.getNumChannels(); --channel>=0;)
                {
                    outputBuffer.addSample(channel, startSample, currentSample);
                }
                mPhase += mPhaseIncrement;
                ++startSample;
                while (mPhase >= mTwoPi) 
                {
                    mPhase -= mTwoPi;
                }
            }
            break;
            
        case 3: //SQUARE
            for (int i = 0; i < numSamples; i++)
            {
                
                float EG_currentSample = EG.getNextSample();
                
                // For half duty-cycle (pi) set high (1.0)
                // and for the other half set low (-1.0)
                float currentSample;
                if (mPhase <= MathConstants<float>::pi) {
                    currentSample = 1.0 * EG_currentSample * mLevel;
                }else{
                    currentSample = -1.0 * EG_currentSample * mLevel;
                }
                
                for (int channel = outputBuffer.getNumChannels(); --channel>=0;)
                {
                    outputBuffer.addSample(channel, startSample, currentSample);
                }
                mPhase += mPhaseIncrement;
                ++startSample;
                while (mPhase >= mTwoPi) {
                    mPhase -= mTwoPi;
                }
            }
            break;
            
            /*
             - -1.0 + (2.0 * mPhase/mTwoPi) is the inverse of the saw above -- It's an upwards saw wave
             - Taking the absolute value of theupwards saw means that all values belo 0 will be inverted (flipped around the x axis)
             - This means that the values will go up and then down
             - Subtracting 0.5 centers the waveform around 0
             - Multiplying by 2.0 makes the values go from 01 to +1. We have a traingle wave.
             */

        case 4: //TRIANGLE
            for (int i = 0; i < numSamples; i++)
            {
                float EG_currentSample = EG.getNextSample();
                const float currentSample = (float) (2.0 * fabs((-1.0 +(2.0 * mPhase/mTwoPi))) - 0.5) * EG_currentSample * mLevel;
                
                for (int channel = outputBuffer.getNumChannels(); --channel>=0;)
                {
                    outputBuffer.addSample(channel, startSample, currentSample);
                }
                mPhase += mPhaseIncrement;
                ++startSample;
                while (mPhase >= mTwoPi) {
                    mPhase -= mTwoPi;
                }
            }
            break;
            
        default:
            break;
    }
    
    
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
