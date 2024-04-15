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
    juce::LookAndFeel::setDefaultLookAndFeel(&LNF);
    //Label* gainTextBox = juce::Slider::LookAndFeelMethods::createSliderTextBox(gainSlider);
    
    gainSlider.setTitle("Gain");
    gainLabel.setText(GAIN_NAME, juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(gainLabel);
    
    // Load the background image
    background = juce::ImageCache::getFromMemory(BinaryData::WavetableBackground_png, BinaryData::WavetableBackground_pngSize);
    
    setSize (800, 600);
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
        g.drawImage(background, 0, 0, 800, 600, 0, 0, 1280, 819);
    }
    else
    {
        std::cout << "background image is null" << "\n";
    }
}

void MooreWavetableAudioProcessorEditor::resized()
{
    // put dial in the middle of the screen
    int gainWidth = 180;
    int gainHeight = 180;
    gainSlider.setBounds(getWidth()/2 - 100, getHeight()/2 - 250, gainWidth, gainHeight);
    // draw the label right under the dial
    float gainCenterX = gainSlider.getX() + gainWidth/2;
    float gainCenterY = gainSlider.getY() + gainHeight/2;
    gainLabel.setBounds(gainCenterX - 20, gainCenterY + 40, 50, 20);
    
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
