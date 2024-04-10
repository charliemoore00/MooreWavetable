/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MooreWavetableAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    MooreWavetableAudioProcessorEditor (MooreWavetableAudioProcessor&);
    ~MooreWavetableAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged(juce::Slider* slider) override;
    void waveShapeMenuChanged();
    

private:
    
    juce::Slider freqSlider, ampSlider;
    
    juce::Label freqLabel, ampLabel;
    
    //create ComboBox components for choosing a wavetype
    juce::Label textLabelShape { {}, "Wave Shape"};
    std::string waveShape;
    juce::Font textFont { 12.0f};
    juce::ComboBox waveShapeMenu;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MooreWavetableAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MooreWavetableAudioProcessorEditor)
};
