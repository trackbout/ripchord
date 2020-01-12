#pragma once

#include "JuceHeader.h"
#include "FileManager.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

struct Chord
{
    String name;
    juce::Array<int> notes;
};

//==============================================================================
class PresetState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    PresetState();
    ~PresetState();

    //==============================================================================
    void resetEditModeInputNote();
    const int getEditModeInputNote();
    juce::Array<int> getMappedInputNotes();
    juce::Array<int> getEditModeInputNoteChordNotes();

    //==============================================================================
    bool isPresetSaveable();
    bool containsChord (const int inputNote);
    String getChordName (const int inputNote);
    juce::Array<int> getChordNotes (const int inputNote);

    //==============================================================================
    void handleEditModeMouseDownOnInput (const int inputNote);
    void handleEditModeMouseDownOnOutput (const int outputNote);

    //==============================================================================
    void handleChordNameTextChanged (String chordName);
    void handlePresetNameTextChanged (String presetName);

private:
    //==============================================================================
    String mName;
    std::map<int, Chord> mChords;

    //==============================================================================
    FileManager mFileManager;
    bool mIsPresetNew = true;
    bool mIsPresetModified = false;

    //==============================================================================
    Chord mEmptyChord;
    int mEditModeInputNote = 0;

    //==============================================================================
    Chord getChord (const int inputNote);
    void setChord (const int inputNote, Chord chord);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
