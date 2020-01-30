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

        setColour (Label::textColourId, COLOR_GREY_DARK);
        setColour (Label::textWhenEditingColourId, COLOR_BLACK);
        setColour (Label::backgroundWhenEditingColourId, COLOR_TRANSPARENT);

        setColour (TextEditor::textColourId, COLOR_GREY_DARK);
        setColour (TextEditor::highlightedTextColourId, COLOR_GREY_DARK);
        setColour (TextEditor::backgroundColourId, COLOR_WHITE);
        setColour (TextEditor::highlightColourId, COLOR_GREY_LIGHT);
        setColour (TextEditor::outlineColourId, COLOR_TRANSPARENT);
        setColour (TextEditor::focusedOutlineColourId, COLOR_TRANSPARENT);

        setColour (Slider::thumbColourId, COLOR_TRANSPARENT);
        setColour (Slider::rotarySliderFillColourId, COLOR_PURPLE);
        setColour (Slider::rotarySliderOutlineColourId, COLOR_WHITE);

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
    void drawTextEditorOutline (Graphics& inGraphics, int inWidth, int inHeight, TextEditor& textEditor) override
    {
        if (textEditor.isEnabled())
        {
            float cornerSize = inHeight * CORNER_SIZE_RATIO;
            juce::Rectangle<float> area (0.f, 0.f, (float) inWidth, (float) inHeight);

            if (textEditor.hasKeyboardFocus (true) && !textEditor.isReadOnly())
            {
                inGraphics.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
                inGraphics.drawRoundedRectangle (area.reduced (1.f), cornerSize, 2);
            }
            else
            {
                inGraphics.setColour (textEditor.findColour (TextEditor::outlineColourId));
                inGraphics.drawRoundedRectangle (area.reduced (1.f), cornerSize, 2);
            }
        }
    };

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

        inGraphics.setColour (COLOR_GREY_LIGHTER);
        inGraphics.fillPath (trianglePath);

        const float lineThickness = 1.f;
        inGraphics.setColour (COLOR_GREY_LIGHT);
        inGraphics.drawLine (0.5f, floatHeight, floatWidth, 0.5f, lineThickness);
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Widgets)
};
