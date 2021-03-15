#pragma once

#include "JuceHeader.h"
#include "Styles.h"

using namespace juce;

//==============================================================================
class Widgets : public LookAndFeel_V4
{
public:
    //==============================================================================
    Widgets()
    {
        setDefaultSansSerifTypefaceName ("Arial");

        setColour (DrawableButton::backgroundColourId, COLOR_TRANSPARENT);
        setColour (DrawableButton::backgroundOnColourId, COLOR_TRANSPARENT);

        setColour (Label::textColourId, COLOR_GREY_DARKEST);
        setColour (Label::textWhenEditingColourId, COLOR_BLACK);
        setColour (Label::backgroundWhenEditingColourId, COLOR_TRANSPARENT);

        setColour (TextEditor::textColourId, COLOR_GREY_DARKEST);
        setColour (TextEditor::highlightedTextColourId, COLOR_GREY_DARKEST);
        setColour (TextEditor::backgroundColourId, COLOR_WHITE);
        setColour (TextEditor::highlightColourId, COLOR_GREY_LIGHT);
        setColour (TextEditor::outlineColourId, COLOR_TRANSPARENT);
        setColour (TextEditor::focusedOutlineColourId, COLOR_TRANSPARENT);

        setColour (Slider::thumbColourId, COLOR_TRANSPARENT);
        setColour (Slider::rotarySliderFillColourId, COLOR_PURPLE);
        setColour (Slider::rotarySliderOutlineColourId, COLOR_GREY_MEDIUM);

        setColour (ScrollBar::thumbColourId, COLOR_GREY_LIGHT);
        setColour (CaretComponent::caretColourId, COLOR_BLUE);
    };

    //==============================================================================
    void fillTextEditorBackground (Graphics& inGraphics, int inWidth, int inHeight, TextEditor& inTextEditor) override
    {
        inGraphics.setColour (inTextEditor.findColour (TextEditor::backgroundColourId));
        float cornerSize = inHeight * CORNER_SIZE_RATIO;
        inGraphics.fillRoundedRectangle ({ 0.f, 0.f, (float) inWidth, (float) inHeight }, cornerSize);
    }

    //==============================================================================
    void drawRotarySlider (Graphics& inGraphics, int inX, int inY, int inWidth, int inHeight, float inSliderPos,
                           const float inRotaryStartAngle, const float inRotaryEndAngle, Slider& inSlider) override
    {
        auto outline = inSlider.findColour (Slider::rotarySliderOutlineColourId);
        auto fill    = inSlider.findColour (Slider::rotarySliderFillColourId);

        auto bounds = Rectangle<int> (inX, inY, inWidth, inHeight).toFloat().reduced (10);

        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto toAngle = inRotaryStartAngle + inSliderPos * (inRotaryEndAngle - inRotaryStartAngle);
        auto lineW = jmin (8.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        Path backgroundArc;
        backgroundArc.addCentredArc (bounds.getCentreX(),
                                     bounds.getCentreY(),
                                     arcRadius,
                                     arcRadius,
                                     0.0f,
                                     inRotaryStartAngle,
                                     inRotaryEndAngle,
                                     true);

        inGraphics.setColour (outline);
        inGraphics.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

        if (inSlider.isEnabled())
        {
            Path valueArc;
            valueArc.addCentredArc (bounds.getCentreX(),
                                    bounds.getCentreY(),
                                    arcRadius,
                                    arcRadius,
                                    0.0f,
                                    inRotaryStartAngle,
                                    toAngle,
                                    true);

            inGraphics.setColour (fill);
            inGraphics.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
        }

        auto thumbWidth = lineW * 2.0f;
        Point<float> thumbPoint (bounds.getCentreX() + arcRadius * std::cos (toAngle - MathConstants<float>::halfPi),
                                 bounds.getCentreY() + arcRadius * std::sin (toAngle - MathConstants<float>::halfPi));

        inGraphics.setColour (inSlider.findColour (Slider::thumbColourId));
        inGraphics.fillEllipse (Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint));
    }

    //==============================================================================
    void drawScrollbar (Graphics& inGraphics, ScrollBar& inScrollbar, int inX, int inY, int inWidth, int inHeight,
                                      bool inIsScrollbarVertical, int inThumbStartPosition,
                                      int inThumbSize, bool inIsMouseOver, bool inIsMouseDown) override
    {
        inGraphics.fillAll (findColour (ScrollBar::backgroundColourId));

        Path thumbPath;

        if (inThumbSize > 0)
        {
            const float thumbIndent = (inIsScrollbarVertical ? inWidth : inHeight) * 0.25f;
            const float thumbIndentx2 = thumbIndent * 2.0f;

            if (inIsScrollbarVertical)
            {
                thumbPath.addRoundedRectangle (inX + thumbIndent, (float) inThumbStartPosition,
                                               inWidth - thumbIndentx2, (float) inThumbSize,
                                               (inWidth - thumbIndentx2) * 0.5f);
            }
            else
            {
                thumbPath.addRoundedRectangle ((float) inThumbStartPosition, inY + thumbIndent,
                                               (float) inThumbSize, inHeight - thumbIndentx2,
                                               (inHeight - thumbIndentx2) * 0.5f);
            }
        }

        Colour thumbCol (inScrollbar.findColour (ScrollBar::thumbColourId, true));

        if (inIsMouseOver || inIsMouseDown)
        {
            thumbCol = thumbCol.contrasting (0.2f);
        }

        inGraphics.setColour (thumbCol);
        inGraphics.fillPath (thumbPath);
    }

    //==============================================================================
    void drawCornerResizer (Graphics& inGraphics, int inWidth, int inHeight,
                            bool inIsMouseOver, bool inIsMouseDragging) override
    {
        const float floatWidth = (float) inWidth;
        const float floatHeight = (float) inHeight;
        Path trianglePath;
        trianglePath.addTriangle (floatWidth, 0.f, floatWidth, floatHeight, 0.f, floatHeight);

        inGraphics.setColour (COLOR_GREY_LIGHT);
        inGraphics.fillPath (trianglePath);

        const float lineThickness = 1.f;
        inGraphics.setColour (COLOR_GREY_MEDIUM);
        inGraphics.drawLine (0.5f, floatHeight, floatWidth, 0.5f, lineThickness);
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Widgets)
};
