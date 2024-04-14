/*
  ==============================================================================

    StyleSheet.cpp
    Created: 12 Apr 2024 3:22:02pm
    Author:  Charlie Moore

  ==============================================================================
*/

#include "StyleSheet.h"

using namespace juce;

void StyleSheet::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)

{
    /* color and geometry calculations */
    auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);
    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    /* arc drawing setup */
    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (8.0f, radius * 0.5f); //lineW = thickness of the arc
    auto arcRadius = radius - lineW * 0.5f;
    
    /* drawing the background arc */
    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);
    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded)); //actual drawing command
    
    /* drawing the value arc (filled arc) */
    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);
        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded)); //actual drawing command
    }
    
    /* drawing the thumb */
    Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));
    g.setColour (slider.findColour (Slider::thumbColourId));
    /* making our own line to go from center of dial to thumb */
    float startX = backgroundArc.getBounds().getCentreX();
    float startY = backgroundArc.getBounds().getCentreY();
    float endX = thumbPoint.getX();
    float endY = thumbPoint.getY();
    g.drawLine(startX, startY, endX, endY, lineW); //actual drawing command
    
}
