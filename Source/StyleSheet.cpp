/*
  ==============================================================================

    StyleSheet.cpp
    Created: 12 Apr 2024 3:22:02pm
    Author:  Charlie Moore

  ==============================================================================
*/

#include "StyleSheet.h"

using namespace juce;

void CustomLNF::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)

{
    auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (8.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;
    

    //Dial background path
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
    //draw path
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

    
    if (slider.isEnabled())
    {
        //dial FILLED background path
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
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }
    

    //the point of the slider (thumb)
    auto thumbWidth = lineW * 2.0f;
    Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));

    g.setColour (slider.findColour (Slider::thumbColourId));
    g.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
    
}
