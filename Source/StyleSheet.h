/*
  ==============================================================================

    StyleSheet.h
    Created: 12 Apr 2024 3:22:02pm
    Author:  Charlie Moore

  ==============================================================================
*/

#pragma once

//#include "PluginEditor.h"
#include <JuceHeader.h>
#include "PluginProcessor.h"

#define PI juce::MathConstants<float>::pi
//#define MIN_GAIN -60.0f
//#define MAX_GAIN 0.0f

using namespace juce;

class CustomLNF : public LookAndFeel_V4
{
public:
    void drawRotarySlider (Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &) override;
    
    void drawComboBox (Graphics&, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       ComboBox&) override;
    
    String getTextFromValue(double value);

};

class GainDial : public Slider
{
public:
    GainDial()
    {
        auto gainRotaryParams = getRotaryParameters();
        // customize gainSlider's paramaters
        gainRotaryParams.startAngleRadians = 1.25 * PI;
        gainRotaryParams.endAngleRadians = 2.75 * PI;
        setRotaryParameters(gainRotaryParams);
        
        // custom gainSlider colours
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::white);
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
        
        setSliderStyle(juce::Slider::RotaryVerticalDrag);
        setRange(MIN_GAIN, MAX_GAIN, 0.1f);
        setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 25);
        setTextBoxIsEditable(true);
        showTextBox();
        setNumDecimalPlacesToDisplay(1);
        //make value box transparent
        setColour(juce::Slider::ColourIds::textBoxOutlineColourId, juce::Colours::transparentBlack);
        
    }
};

