/*
  ==============================================================================

    OscillatorSound.cpp
    Created: 27 Mar 2024 2:40:36pm
    Author:  Charlie Moore

  ==============================================================================
*/

#include "OscillatorSound.h"

OscillatorSound::OscillatorSound()
{
    
}
OscillatorSound::~OscillatorSound()
{
    
}


bool OscillatorSound::appliesToNote(int midiNoteNumber)
{
    return true;
}
bool OscillatorSound::appliesToChannel(int midiChannel)
{
    return true;
}
