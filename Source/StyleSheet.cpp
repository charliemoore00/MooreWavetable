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
    Point<float> thumbPoint (bounds.getCentreX() + (arcRadius - 8) * std::cos (toAngle - MathConstants<float>::halfPi),
                             bounds.getCentreY() + (arcRadius - 8) * std::sin (toAngle - MathConstants<float>::halfPi));
    g.setColour (slider.findColour (Slider::thumbColourId));
    /* making our own line to go from center of dial to thumb */
    float startX = backgroundArc.getBounds().getCentreX();
    float startY = backgroundArc.getBounds().getCentreY();
    float endX = thumbPoint.getX();
    float endY = thumbPoint.getY();
    g.drawLine(startX, startY, endX, endY, lineW); //actual drawing command
    
}

//==============================================================================
void CustomLNF::drawComboBox (Graphics& g, int width, int height, bool,
                                   int, int, int, int, ComboBox& box)
{
    auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : 3.0f;
    Rectangle<int> boxBounds (0, 0, width, height);

    g.setColour (box.findColour (ComboBox::backgroundColourId));
    g.fillRoundedRectangle (boxBounds.toFloat(), cornerSize);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.toFloat().reduced (0.5f, 0.5f), cornerSize, 1.0f);

    Rectangle<int> arrowZone (width - 30, 0, 20, height);
    Path path;
    path.startNewSubPath ((float) arrowZone.getX() + 3.0f, (float) arrowZone.getCentreY() - 2.0f);
    path.lineTo ((float) arrowZone.getCentreX(), (float) arrowZone.getCentreY() + 3.0f);
    path.lineTo ((float) arrowZone.getRight() - 3.0f, (float) arrowZone.getCentreY() - 2.0f);

    g.setColour (box.findColour (ComboBox::arrowColourId).withAlpha ((box.isEnabled() ? 0.9f : 0.2f)));
    g.strokePath (path, PathStrokeType (2.0f));
}

juce::String CustomLNF::getTextFromValue(double value)
{
    // return the value formatted to one decimal place
    return juce::String(value, 1);
}
