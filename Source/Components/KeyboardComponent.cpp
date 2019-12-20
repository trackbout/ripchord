#include "KeyboardComponent.h"

//==============================================================================
KeyboardComponent::KeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState())
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
void KeyboardComponent::initKeyboard()
{
    mKeyComponents.clear();

    int x = 0;

    for (int midiNoteNumber = mFirstKey; midiNoteNumber <= mLastKey; midiNoteNumber++)
    {
        auto keyBounds = getKeyBounds (x, midiNoteNumber);
        KeyComponent* keyComponent = new KeyComponent (mMainProcess, midiNoteNumber);

        keyComponent->setBounds (keyBounds);
        mKeyComponents.add (keyComponent);
        addAndMakeVisible (keyComponent);
    }

    bringBlackKeysToFront();
}

juce::Rectangle<int> KeyboardComponent::getKeyBounds (int& inX, int midiNoteNumber)
{
    int currentX = inX;
    const int whiteKeyWidth = getWidth() / mWhiteKeyCount;
    const int whiteKeyHeight = getHeight();
    const int blackKeyWidth = whiteKeyWidth * 0.78f;
    const int blackKeyHeight = whiteKeyHeight * 0.66f;

    if (Interface::isBlackKey (midiNoteNumber))
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
        if (Interface::isBlackKey (keyComponent->getMidiNoteNumber()))
        {
            keyComponent->toFront (false);
        }
    }
}
