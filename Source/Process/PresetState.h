#pragma once

#include "JuceHeader.h"
#include "System.h"
#include "Constants.h"
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
    std::map<int, Chord> mChords;

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
    bool mIsPresetCreated = false;
    bool mIsPresetModified = false;

    //==============================================================================
    void createPresetFile();
    void updatePresetFile();
    void deletePresetFile();

    //==============================================================================
    String mPresetFileName;
    XmlElement getXmlFromPresetState();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
