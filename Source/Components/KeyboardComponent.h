#pragma once

#include "JuceHeader.h"
#include "KeyComponent.h"

//==============================================================================
class KeyboardComponent : public Component
{
public:
    //==============================================================================
    KeyboardComponent();
    ~KeyboardComponent();

    //==============================================================================
    void initKeyboard();
    OwnedArray<KeyComponent> mKeyComponents;

private:
    //==============================================================================
    juce::Rectangle<int> getKeyBounds (int& x, const int noteNumber);
    void bringBlackKeysToFront();

    //==============================================================================
    const int mFirstKey = 21;
    const int mLastKey = 108;
    const int mWhiteKeyCount = 52;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
