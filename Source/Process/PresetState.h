#pragma once

#include "JuceHeader.h"
#include "Presets.h"
#include "Keyboard.h"
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
    String getName();
    bool isPresetValid();
    bool isPresetModified();
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
    void handleClickCut (const int inputNote);
    void handleClickCopy (const int inputNote);
    void handleClickPaste (const int inputNote);

    //==============================================================================
    void handleClickNew();
    void handleClickSave();
    void handleClickImportMidi();
    void handleClickExportMidi();
    void handleClickImportPreset();
    void handleClickExportPreset();
    void handleClickImportMPC();
    void handleClickDuplicate();
    void handleClickEditLeft();
    void handleClickEditRight();
    void handleClickAllWhite();
    void handleClickAllBlack();
    void handleClickPreset (File presetFile);

    //==============================================================================
    XmlElement* exportPresetStateXml();
    void importPresetStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    String mName;
    std::map<int, Chord> mChords;

    Chord mEmptyChord;
    Chord mClipboardChord;
    int mEditModeInputNote = 0;

    String mPresetFileName;
    bool mIsPresetModified = false;

    Chord getChord (const int inputNote);
    void setChord (const int inputNote, Chord chord);
    void resetPresetState (bool keepChords);

    void loadPresetFile (File presetFile);
    void loadMidiFile (File midiFile);
    void loadMPCFile (File mpcFile);

    std::map<int, Chord> savePresetFile (File presetFile);
    std::map<int, Chord> saveMidiFile (File midiFile);
    std::map<int, Chord> saveMPCFile (File mpcFile);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetState)
};
