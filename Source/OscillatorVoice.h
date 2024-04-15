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

using namespace juce;
using namespace std;

#include <cmath>

class OscillatorVoice : public SynthesiserVoice
{
public:
    OscillatorVoice();
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
    
    
private:
    
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
};

