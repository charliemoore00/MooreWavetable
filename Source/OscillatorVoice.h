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



#pragma once

#include <JuceHeader.h>
#include "Scale.h"
#include "PluginEditor.h"
#include "PluginProcessor.h"


using namespace juce;
using namespace std;

#include <cmath>

class OscillatorVoice : public SynthesiserVoice
{
public:
    OscillatorVoice(MooreWavetableAudioProcessor& processor);
   ~OscillatorVoice();
    
    
    //======================================================================
    
    void pitchWheelMoved              (int                newPitchWheelValue)        override;
    void aftertouchChanged            (int                newAftertouchValue)        override;
    void channelPressureChanged       (int                newChannelPressureValue)   override;
    void setCurrentPlaybackSampleRate (double             newRate)                   override;
    void controllerMoved              (int                controllerNumber,
                                       int                newControllerValue)        override;
    void stopNote                     (float              velocity,
                                       bool               allowTailOff)              override;
    void startNote                    (int                midiNoteNumber,
                                       float              velocity,
                                       SynthesiserSound  *sound,
                                       int                currentPitchWheelPosition) override;
    bool canPlaySound                 (SynthesiserSound*)                            override;
    bool isVoiceActive                ()                  const                      override;
    bool isPlayingChannel             (int midiChannel)   const                      override;
    
    //======================================================================
    
    void renderNextBlock        (AudioBuffer<float>  &outputBuffer, int startSample, int numSamples) override;
    void renderNextBlock        (AudioBuffer<double> &outputBuffer, int startSample, int numSamples) override;
    
    //======================================================================
    
    void prepareNoiseWavetable ();
    
    //======================================================================
    
    void  setFrequency  (float frequency, float sampleRate);
    void  updateAngle   ();
    float getNextSample ();
    
    EqualTemperamentScale scale;
    
    void initializeEG();
    
    int waveShapeID = 1;
    
    
    
    
private:
    
    //
    //MooreWavetableAudioProcessorEditor& processorEditor;
    MooreWavetableAudioProcessor& audioProcessor;
    
    //create envelope
    ADSR EG;
    
    //initialize when attack, decay, sustain, release
    ADSR::Parameters EG_Parameters = {0.01, 0.1, 1.0, 0.2}; //TODO: variables for adsr
    
    
    /// A Random object to generate random numbers for the noise oscillator.
    Random noiseGenerator;
    
    /// ...
    vector<float> noiseWavetable;
    
    /// ...
    int WAVETABLE_SIZE = 512;
    
    //======================================================================
    
    /// ...
    int SAMPLERATE   = 44100;
    
    /// ...
    float phase      = 0.0f;
    
    /// ...
    float phaseDelta = 0.0f;
    
    
    
    //following from mclean's code:
    int mOscillatorMode = 1;
    double mTwoPi = 2.0 * MathConstants<double>::pi;                      // store 2*pi so we don't have to keep recalculating it
    double mFrequency = 0.0;                  // the frequency of our oscillator
    double mPhase = 0.0;                      // where we are in the oscillators cycle
    double mPhaseIncrement = 0.0;             // amount added to phase every sample
    double mSampleRate = 44100.0;                 // store the current sample rate
    double mLevel = 0.5;                      // store the current amplitude
};



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX


/*
  ==============================================================================

    OscillatorVoice.h
    Created: 30 Nov 2018 10:36:36am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

/*

#pragma once
#include "JuceHeader.h"
#include "OscillatorSound.h"
#include "Scale.h"
//#include "EnvelopeGenerator.h"

enum OscillatorMode{
    OSCILLATOR_MODE_SINE = 0,
    OSCILLATOR_MODE_SAW,
    OSCILLATOR_MODE_SQUARE,
    OSCILLATOR_MODE_TRIANGLE
};

class OscillatorVoice   :   public SynthesiserVoice{
    
public:
    OscillatorVoice();
    ~OscillatorVoice();
    
    bool canPlaySound (SynthesiserSound*) override;
    void startNote (int midiNoteNumber,
                        float velocity,
                        SynthesiserSound* sound,
                        int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void renderNextBlock (AudioBuffer<float>& outputBuffer,
                     int startSample,
                     int numSamples) override;
    
    
    void  setFrequency  (float frequency, float sampleRate);
    void  updateAngle   ();
    float getNextSample ();
    
    EqualTemperamentScale scale;
    
    void initializeEG();
    
private:
    OscillatorMode mOscillatorMode;     // the current waveform type our osc is set to
    double mTwoPi;                      // store 2*pi so we don't have to keep recalculating it
    double mFrequency;                  // the frequency of our oscillator
    double mPhase;                      // where we are in the oscillators cycle
    double mPhaseIncrement;             // amount added to phase every sample
    double mSampleRate;                 // store the current sample rate
    double mLevel;                      // store the current amplitude
    
    juce::ADSR EG;
    int SAMPLERATE   = 44100;
    
};


*/
