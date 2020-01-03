#include "KeyComponent.h"

//==============================================================================
KeyComponent::KeyComponent (const int inNoteNumber)
:   mNoteNumber (inNoteNumber)
{
    Colour defaultColor = getDefaultColor (mNoteNumber);
    mNoteColor = defaultColor;
    mMarkerColor = defaultColor;
}

KeyComponent::~KeyComponent()
{
}

//==============================================================================
void KeyComponent::paint (Graphics& inGraphics)
{
    const int markerHeight = 4;
    auto keyArea = getLocalBounds().reduced (1);
    auto noteHeight = keyArea.getHeight() - markerHeight;

    inGraphics.setColour (COLOR_GREY_LIGHT);
    inGraphics.fillAll();

    inGraphics.setColour (mNoteColor);
    inGraphics.fillRect (keyArea.removeFromTop (noteHeight));

    inGraphics.setColour (mMarkerColor);
    inGraphics.fillRect (keyArea.removeFromTop (markerHeight));
}

//==============================================================================
void KeyComponent::mouseUp (const MouseEvent& inEvent)
{
    if (onMouseUp) { onMouseUp (mNoteNumber); }
}

void KeyComponent::mouseDown (const MouseEvent& inEvent)
{
    if (onMouseDown) { onMouseDown (mNoteNumber); }
}

//==============================================================================
void KeyComponent::setNoteColor (Colour inColor)
{
    mNoteColor = inColor;
    repaint();
}

void KeyComponent::setMarkerColor (Colour inColor)
{
    mMarkerColor = inColor;
    repaint();
}

void KeyComponent::setNoteAndMarkerColor (Colour inColor)
{
    mNoteColor = inColor;
    mMarkerColor = inColor;
    repaint();
}

//==============================================================================
const int KeyComponent::getNoteNumber()
{
    return mNoteNumber;
}

Colour KeyComponent::getDefaultColor (const int inNoteNumber)
{
    return Interface::isBlackKey (inNoteNumber) ? COLOR_GREY_DARK : COLOR_WHITE;
}
