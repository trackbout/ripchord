#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "KeyComponent.h"

//==============================================================================
class KeyboardComponent : public Component
{
public:
    //==============================================================================
    KeyboardComponent (MainProcess&);
    ~KeyboardComponent();

    //==============================================================================
    void resized() override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    //==============================================================================
    void initKeyboard();
    void bringBlackKeysToFront();
    juce::Rectangle<int> getKeyBounds (int& x, int midiNoteNumber);

    //==============================================================================
    const int mFirstKey = 21;
    const int mLastKey = 108;
    const int mWhiteKeyCount = 52;
    OwnedArray<KeyComponent> mKeyComponents;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};
