#pragma once

#include "JuceHeader.h"
#include "System.h"
#include "Presets.h"
#include "Constants.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class PresetState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    PresetState();
    ~PresetState();

    //==============================================================================
    bool isPresetSaveable();
    void resetEditModeInputNote();
    const int getEditModeInputNote();
    juce::Array<int> getPresetInputNotes();

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
    std::map<int, Presets::Chord> mChords;

    //==============================================================================
    Presets::Chord mEmptyChord;
    int mEditModeInputNote = 0;

    //==============================================================================
    Presets::Chord getChord (const int inputNote);
    void setChord (const int inputNote, Presets::Chord chord);

    //==============================================================================
    const File mUserDataPath;
    const File mPresetFolder;

    //==============================================================================
    String mPresetFileName;
    bool mIsPresetModified = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
