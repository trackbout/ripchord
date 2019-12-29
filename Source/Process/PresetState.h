#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

struct Chord
{
    String chordName;
    Array<int> chordNotes;
};

//==============================================================================
class PresetState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    PresetState();
    ~PresetState();

    //==============================================================================
    String getPresetName();
    void setPresetName (String name);

    //==============================================================================
    Chord getPresetChord (const int inputNote);
    void setPresetChord (const int inputNote, Chord chord);

    //==============================================================================
    void resetPresetName();
    void resetPresetChords();

    //==============================================================================
    void addPresetChord (const int inputNote);
    void removePresetChord (const int inputNote);
    bool containsPresetChord (const int inputNote);

    //==============================================================================
    void addPresetChordNote (const int inputNote, const int outputNote);
    void removePresetChordNote (const int inputNote, const int *outputNote);
    bool containsPresetChordNote (const int inputNote, const int outputNote);

    //==============================================================================
    int getEditModeInputNote();
    void setEditModeInputNote (int inputNote);

private:
    //==============================================================================
    String mPresetName;
    std::map<int, Chord> mPresetChords;

    //==============================================================================
    Chord mEmptyChord;
    int mEditModeInputNote = 0;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
