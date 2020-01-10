#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent()
{
}

KeyboardComponent::~KeyboardComponent()
{
}

//==============================================================================
void KeyboardComponent::initKeyboard()
{
    mKeyComponents.clear();

    int x = 0;

    for (int noteNumber = mFirstKey; noteNumber <= mLastKey; noteNumber++)
    {
        // create and make visible
        KeyComponent* keyComponent = new KeyComponent (noteNumber);
        auto keyBounds = getKeyBounds (x, noteNumber);
        keyComponent->setBounds (keyBounds);
        addAndMakeVisible (keyComponent);

        // add to map
        mKeyComponents[noteNumber] = keyComponent;

        // add to owned array
        mKeys.add(keyComponent);
    }

    bringBlackKeysToFront();
}

//==============================================================================
juce::Rectangle<int> KeyboardComponent::getKeyBounds (int& inX, const int inNoteNumber)
{
    int currentX = inX;
    const int whiteKeyWidth = getWidth() / mWhiteKeyCount;
    const int whiteKeyHeight = getHeight();
    const int blackKeyWidth = whiteKeyWidth * 0.78f;
    const int blackKeyHeight = whiteKeyHeight * 0.66f;

    if (Interface::isBlackKey (inNoteNumber))
    {
        auto previousKey = mKeyComponents.at (inNoteNumber - 1);
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
    for (int noteNumber = mFirstKey; noteNumber <= mLastKey; noteNumber++)
    {
        if (Interface::isBlackKey (noteNumber))
        {
            auto keyComponent = mKeyComponents.at (noteNumber);
            keyComponent->toFront (false);
        }
    }
}
