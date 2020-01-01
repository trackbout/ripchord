#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

struct Chord
{
    String chordName;
    juce::Array<int> chordNotes;
};

//==============================================================================
class PresetState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    PresetState();
    ~PresetState();

    //==============================================================================
    void setEditModeInputNote (const int inputNote);
    void setEditModeOutputNote (const int outputNote);

private:
    //==============================================================================
    String mPresetName;
    std::map<int, Chord> mPresetChords;

    //==============================================================================
    Chord mEmptyChord;
    int mEditModeInputNote = 0;

    //==============================================================================
    Chord getPresetChord (const int inputNote);
    void setPresetChord (const int inputNote, Chord chord);
    void addPresetChord (const int inputNote);
    void removePresetChord (const int inputNote);
    bool containsPresetChord (const int inputNote);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
