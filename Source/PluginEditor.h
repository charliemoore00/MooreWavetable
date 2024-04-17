/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include "StyleSheet.h"
#include <JuceHeader.h>

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
    
    //==============================================================================
    
    void waveShapeMenuChanged();
     
    GainDial gainSlider; //create custom gain dial
    
    //create ComboBox components for choosing a wavetype
    juce::Label textLabelShape { {}, "Wave Shape"};
    std::string waveShape;
    juce::Font textFont { 12.0f};
    juce::ComboBox waveShapeMenu;
    

private:
    
    CustomLNF LNF;
    juce::Image background;
    
    juce::Label gainLabel;
    
    
    
    
    
    
    
    
     
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MooreWavetableAudioProcessor& audioProcessor;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MooreWavetableAudioProcessorEditor)
};
