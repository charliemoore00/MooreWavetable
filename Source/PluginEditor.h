/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "StyleSheet.h"

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
    
    
    //quick way for the editor to access the processor object that created it.
    //MooreWavetableAudioProcessor& audioProcessor;
    /*
    void waveShapeMenuChanged();
     */
    juce::Slider gainSlider; //create gain slider
    

private:
    
    CustomLNF myCustomLNF;
    juce::Image background;
    
    
    /*
    
    
    juce::Label freqLabel, ampLabel;
    
    //create ComboBox components for choosing a wavetype
    juce::Label textLabelShape { {}, "Wave Shape"};
    std::string waveShape;
    juce::Font textFont { 12.0f};
    juce::ComboBox waveShapeMenu;
     */
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MooreWavetableAudioProcessor& audioProcessor;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MooreWavetableAudioProcessorEditor)
};
