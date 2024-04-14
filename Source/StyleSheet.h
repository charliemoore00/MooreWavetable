/*
  ==============================================================================

    StyleSheet.h
    Created: 12 Apr 2024 3:22:02pm
    Author:  Charlie Moore

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using namespace juce;

class StyleSheet : public LookAndFeel_V4
{
public:
    void drawRotarySlider (Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider &);
};
