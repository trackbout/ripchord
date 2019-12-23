#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent()
{
}

KeyboardComponent::~KeyboardComponent()
{
}

//==============================================================================
void KeyboardComponent::resized()
{
    initKeyboard();
}

//==============================================================================
void KeyboardComponent::handleMouseUp (const int inNoteNumber)
{
    DBG("UP NOTE: " << inNoteNumber);
}

void KeyboardComponent::handleMouseDown (const int inNoteNumber)
{
    DBG("DOWN NOTE: " << inNoteNumber);
}

//==============================================================================
void KeyboardComponent::initKeyboard()
{
    mKeyComponents.clear();

    int x = 0;

    for (int noteNumber = mFirstKey; noteNumber <= mLastKey; noteNumber++)
    {
        auto keyBounds = getKeyBounds (x, noteNumber);
        KeyComponent* keyComponent = new KeyComponent (noteNumber);

        keyComponent->onMouseUp = [this](const int inNoteNumber) { handleMouseUp (inNoteNumber); };
        keyComponent->onMouseDown = [this](const int inNoteNumber) { handleMouseDown (inNoteNumber); };
        keyComponent->setBounds (keyBounds);
        mKeyComponents.add (keyComponent);
        addAndMakeVisible (keyComponent);
    }

    bringBlackKeysToFront();
}

juce::Rectangle<int> KeyboardComponent::getKeyBounds (int& inX, const int inNoteNumber)
{
    int currentX = inX;
    const int whiteKeyWidth = getWidth() / mWhiteKeyCount;
    const int whiteKeyHeight = getHeight();
    const int blackKeyWidth = whiteKeyWidth * 0.78f;
    const int blackKeyHeight = whiteKeyHeight * 0.66f;

    if (Interface::isBlackKey (inNoteNumber))
    {
        auto previousKey = mKeyComponents.getUnchecked (mKeyComponents.size() - 1);
        currentX = previousKey->getRight() - (blackKeyWidth * 0.5f);
        return juce::Rectangle<int> (currentX, 0, blackKeyWidth, blackKeyHeight);
    }

    else
    {
        inX = inX + whiteKeyWidth;
        return juce::Rectangle<int> (currentX, 0, whiteKeyWidth, whiteKeyHeight);
    }
}

void KeyboardComponent::bringBlackKeysToFront()
{
    for (auto& keyComponent : mKeyComponents)
    {
        if (Interface::isBlackKey (keyComponent->getNoteNumber()))
        {
            keyComponent->toFront (false);
        }
    }
}
