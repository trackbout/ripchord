#pragma once

const int DOUBLE_TRIGGER_WEIGHT = 1000;

//==============================================================================
struct Origin
{
    int transposition;
    juce::Array<int> triggers;
};
