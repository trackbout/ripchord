#include "KeyComponent.h"

//==============================================================================
KeyComponent::KeyComponent (MainProcess& inMainProcess, int inMidiNoteNumber)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mCurrentPresetState (mMainProcess.getCurrentPresetState()),
    mMidiNoteNumber (inMidiNoteNumber)
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
int KeyComponent::getMidiNoteNumber()
{
    return mMidiNoteNumber;
}

//==============================================================================
Colour KeyComponent::getDefaultColor()
{
    const bool isBlackKey = Interface::isBlackKey (mMidiNoteNumber);
    if (isBlackKey) { return COLOR_GREY_DARK; }
    return COLOR_WHITE;
}
