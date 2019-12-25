#include "KeyComponent.h"

//==============================================================================
KeyComponent::KeyComponent (const int inNoteNumber)
:   mNoteNumber (inNoteNumber)
{
}

KeyComponent::~KeyComponent()
{
}

//==============================================================================
void KeyComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY_LIGHT);
    inGraphics.fillAll();

    Colour defaultColor = getDefaultColor();

    const int markerHeight = 4;
    auto keyArea = getLocalBounds().reduced (1);
    auto noteHeight = keyArea.getHeight() - markerHeight;

    inGraphics.setColour (defaultColor);
    inGraphics.fillRect (keyArea.removeFromTop (noteHeight));

    inGraphics.setColour (defaultColor);
    inGraphics.fillRect (keyArea.removeFromTop (markerHeight));
}

//==============================================================================
const int KeyComponent::getNoteNumber()
{
    return mNoteNumber;
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
Colour KeyComponent::getDefaultColor()
{
    return Interface::isBlackKey (mNoteNumber) ? COLOR_GREY_DARK : COLOR_WHITE;
}
