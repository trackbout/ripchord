#pragma once

#include "JuceHeader.h"
#include "System.h"
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
    bool isPresetValid();
    bool isPresetCreated();
    bool isPresetNameModified();
    bool isPresetDataModified();

    //==============================================================================
    void resetEditModeInputNote();
    const int getEditModeInputNote();
    juce::Array<int> getMappedInputNotes();
    juce::Array<int> getEditModeInputNoteChordNotes();

    //==============================================================================
    bool containsChord (const int inputNote);
    String getChordName (const int inputNote);
    juce::Array<int> getChordNotes (const int inputNote);

    //==============================================================================
    void handleEditModeMouseDownOnInput (const int inputNote);
    void handleEditModeMouseDownOnOutput (const int outputNote);

    //==============================================================================
    void handleChordNameTextChanged (String chordName);
    void handlePresetNameTextChanged (String presetName);

    //==============================================================================
    void handleMouseClickOnSave();

private:
    //==============================================================================
    String mName;
    std::map<int, Chord> mChords;

    //==============================================================================
    bool mIsPresetCreated = false;
    bool mIsPresetNameModified = false;
    bool mIsPresetDataModified = false;

    //==============================================================================
    Chord mEmptyChord;
    int mEditModeInputNote = 0;

    //==============================================================================
    Chord getChord (const int inputNote);
    void setChord (const int inputNote, Chord chord);

    //==============================================================================
    const File mUserDataPath;
    const File mPresetFolder;

    //==============================================================================
    void createPresetFile();
    void renamePresetFile();
    void updatePresetFile();
    void deletePresetFile();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
