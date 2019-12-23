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
    void resized() override;

    //==============================================================================
    void handleMouseUp (const int noteNumber);
    void handleMouseDown (const int noteNumber);

private:
    //==============================================================================
    void initKeyboard();
    void bringBlackKeysToFront();
    juce::Rectangle<int> getKeyBounds (int& x, const int noteNumber);

    //==============================================================================
    const int mFirstKey = 21;
    const int mLastKey = 108;
    const int mWhiteKeyCount = 52;
    OwnedArray<KeyComponent> mKeyComponents;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
