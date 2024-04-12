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
    
    
    gainSliderAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState, GAIN_ID, gainSlider);
    
    //set LookAndFeel to our own
    juce::LookAndFeel::setDefaultLookAndFeel(&myCustomLNF);
    
    
    // Load the background image
    background = juce::ImageCache::getFromMemory(BinaryData::rainbow_cloud_png, BinaryData::rainbow_cloud_pngSize);

    /*
    juce::File backgroundImageFile('');
    background = juce::ImageFileFormat::loadFrom(backgroundImageFile);
     */
    
    setSize (800, 600);
    
    gainSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainSlider.setRange(MIN_GAIN, MAX_GAIN);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
    
    /*

    freqLabel.setText("Frequency", juce::dontSendNotification);
    freqLabel.attachToComponent(&freqSlider, true);
    
    //______________________
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setRange(0.0, 1.0, 0.01);
    gainSlider.addListener(this);
    gainSlider.setValue(0.2);
    addAndMakeVisible(gainSlider);
    
    gainLabel.setText("Amplitude", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, true);
    
    
    //add ComboBox components
    addAndMakeVisible(textLabelShape);
    textLabelShape.setFont(textFont);
    addAndMakeVisible(waveShapeMenu);
    waveShapeMenu.addItem("Sine", 1);
    
    //why use .onChange function rather than listener?
    waveShapeMenu.onChange = [this] { waveShapeMenuChanged(); };
    waveShapeMenu.setSelectedId(1);
     
     */
}

MooreWavetableAudioProcessorEditor::~MooreWavetableAudioProcessorEditor()
{
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void MooreWavetableAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Draw the background image
    if (!background.isNull()) {
        g.drawImageAt(background, 0, 0);
    }
}

void MooreWavetableAudioProcessorEditor::resized()
{
    const int labelSpace = 100;
    const int gainSliderWidth = 200;
    //put dial in the middle of the screen
    gainSlider.setBounds(getWidth()/2 - 100, getHeight()/2 - 100, 200, 200);
    /*
    const int labelSpace = 100;
    freqSlider.setBounds(labelSpace, 80, getWidth()-100, 20);
    ampSlider.setBounds(labelSpace, 110, getWidth()-100, 50);
    
    textLabelShape.setBounds(10, 10, getWidth()-400, 20);
    waveShapeMenu.setBounds(10, 40, 80, 20);
     */
}

void MooreWavetableAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
}

/*
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
 */
