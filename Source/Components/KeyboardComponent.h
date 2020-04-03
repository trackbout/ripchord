#pragma once

#include "JuceHeader.h"
#include "KeyComponent.h"
#include "Keyboard.h"

//==============================================================================
class KeyboardComponent : public Component
{
public:
    //==============================================================================
    KeyboardComponent();
    ~KeyboardComponent();

    //==============================================================================
    void initKeyboard();
    void resetKeyColors();

    //==============================================================================
    std::map<int, KeyComponent*> mKeyComponents;

    //==============================================================================
    const int mFirstKey = 21;
    const int mLastKey = 108;

private:
    //==============================================================================
    const int mWhiteKeyCount = 52;
    juce::Rectangle<int> getKeyBounds (int& x, const int noteNumber);
    void bringBlackKeysToFront();

    juce::OwnedArray<KeyComponent> mKeysToDelete;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
