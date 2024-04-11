/*
  ==============================================================================

    OscillatorSound.h
    Created: 27 Mar 2024 2:40:36pm
    Author:  Charlie Moore

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;
using namespace std;

class OscillatorSound : public SynthesiserSound
{
public:
    OscillatorSound();
    ~OscillatorSound();
    
    
    bool appliesToNote(int midiNoteNumber) override;
    bool appliesToChannel(int midiChannel) override;
    
    
private:
    
};
