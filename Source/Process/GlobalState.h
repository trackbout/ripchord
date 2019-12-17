#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class GlobalState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    GlobalState();
    ~GlobalState();

    //==============================================================================
    enum Mode { Play, Edit };

    void toggleMode();
    bool isInPlayMode();
    bool isInEditMode();

private:
    //==============================================================================
    Mode mMode = Mode::Play;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalState)
};
