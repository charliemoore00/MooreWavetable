/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MooreWavetableAudioProcessorEditor::MooreWavetableAudioProcessorEditor (MooreWavetableAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (800, 600);
    
    //_______________________
    freqSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    freqSlider.setTextValueSuffix("Hz");
    freqSlider.setRange(110, 1500, 1);
    freqSlider.setValue(440);
    freqSlider.addListener(this);
    addAndMakeVisible(freqSlider);

    freqLabel.setText("Frequency", juce::dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, true);
    
    //______________________
    ampSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    ampSlider.setRange(0.0, 1.0, 0.01);
    ampSlider.addListener(this);
    ampSlider.setValue(0.2);
    addAndMakeVisible(ampSlider);
    
    ampLabel.setText("Amplitude", juce::dontSendNotification);
    ampLabel.attachToComponent(&ampSlider, true);
    
    
    //add ComboBox components
    addAndMakeVisible(textLabelShape);
    textLabelShape.setFont(textFont);
    addAndMakeVisible(waveShapeMenu);
    waveShapeMenu.addItem("Sine", 1);
    
    //why use .onChange function rather than listener?
    waveShapeMenu.onChange = [this] { waveShapeMenuChanged(); };
    waveShapeMenu.setSelectedId(1);
}

MooreWavetableAudioProcessorEditor::~MooreWavetableAudioProcessorEditor()
{
}

//==============================================================================
void MooreWavetableAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MooreWavetableAudioProcessorEditor::resized()
{
    const int labelSpace = 100;
    freqSlider.setBounds(labelSpace, 80, getWidth()-100, 20);
    ampSlider.setBounds(labelSpace, 110, getWidth()-100, 50);
    
    textLabelShape.setBounds(10, 10, getWidth()-400, 20);
    waveShapeMenu.setBounds(10, 40, 80, 20);
}
void MooreWavetableAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &freqSlider)
    {
        audioProcessor.frequency = freqSlider.getValue();
        std::cout << audioProcessor.increment << std::endl;
    } else if (slider == &ampSlider)
    {
        audioProcessor.amplitude = ampSlider.getValue();
    }
}

void MooreWavetableAudioProcessorEditor::waveShapeMenuChanged()
{
    switch (waveShapeMenu.getSelectedId()) {
        case 1:
            //set wave shape to sine
            waveShape = "sine";
            break;
            
        default:
            break;
    }
}
