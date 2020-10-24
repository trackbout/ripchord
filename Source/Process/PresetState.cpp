#include "PresetState.h"

//==============================================================================
PresetState::PresetState()
{
}

PresetState::~PresetState()
{
}

//==============================================================================
String PresetState::getName()
{
    return mName;
}

bool PresetState::isPresetValid()
{
    if (mName.isEmpty()) { return false; }

    juce::Array<int> chordNotes;

    for (int inputNote : getPresetInputNotes())
    {
        for (int chordNote : getChordNotes (inputNote))
        {
            chordNotes.add (chordNote);
        }
    }

    return chordNotes.size() > 0;
}

bool PresetState::isPresetModified()
{
    return mIsPresetModified;
}

void PresetState::resetEditModeInputNote()
{
    mEditModeInputNote = 0;
}

const int PresetState::getEditModeInputNote()
{
    return mEditModeInputNote;
}

juce::Array<int> PresetState::getPresetInputNotes()
{
    juce::Array<int> presetInputNotes;

    for (const auto& pair : mChords)
    {
      presetInputNotes.add (pair.first);
    }

    return presetInputNotes;
}

//==============================================================================
bool PresetState::containsChord (const int inInputNote)
{
    return mChords.count (inInputNote) > 0;
}

String PresetState::getChordName (const int inInputNote)
{
    return getChord (inInputNote).name;
}

juce::Array<int> PresetState::getChordNotes (const int inInputNote)
{
    return getChord (inInputNote).notes;
}

//==============================================================================
void PresetState::handleEditModeMouseDownOnInput (const int inInputNote)
{
    const int prevEditModeInputNote = mEditModeInputNote;
    const int nextEditModeInputNote = inInputNote == mEditModeInputNote ? 0 : inInputNote;
    bool prevEditModeInputNoteContainsChord = containsChord (prevEditModeInputNote);
    juce::Array<int> prevEditModeOutputNotes = getChordNotes (prevEditModeInputNote);
    juce::Array<int> nextEditModeOutputNotes = getChordNotes (nextEditModeInputNote);

    mEditModeInputNote = nextEditModeInputNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeInputNote;
    message->messageVar1 = prevEditModeInputNote;
    message->messageVar2 = nextEditModeInputNote;
    message->messageVar3 = prevEditModeInputNoteContainsChord;
    message->messageArray1 = prevEditModeOutputNotes;
    message->messageArray2 = nextEditModeOutputNotes;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleEditModeMouseDownOnOutput (const int inOutputNote)
{
    if (mEditModeInputNote == 0) { return; }

    juce::Array<int> prevEditModeOutputNotes = getChordNotes (mEditModeInputNote);
    bool shouldAddNote = !prevEditModeOutputNotes.contains (inOutputNote);

    if (shouldAddNote)
    {
        Chord presetChord = getChord (mEditModeInputNote);
        presetChord.notes.addUsingDefaultSort (inOutputNote);
        setChord (mEditModeInputNote, presetChord);
    }
    else
    {
        if (prevEditModeOutputNotes.size() > 1)
        {
            Chord presetChord = getChord (mEditModeInputNote);
            presetChord.notes.removeFirstMatchingValue (inOutputNote);
            setChord (mEditModeInputNote, presetChord);
        }
        else
        {
            mChords.erase (mEditModeInputNote);
        }
    }

    juce::Array<int> nextEditModeOutputNotes = getChordNotes (mEditModeInputNote);

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeOutputNotes;
    message->messageArray1 = prevEditModeOutputNotes;
    message->messageArray2 = nextEditModeOutputNotes;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void PresetState::handleChordNameTextChanged (String inChordName)
{
    Chord presetChord = getChord (mEditModeInputNote);
    if (mEditModeInputNote == 0 || presetChord.name == inChordName) { return; }

    presetChord.name = inChordName;
    setChord (mEditModeInputNote, presetChord);

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kChordNameTextChanged;
    message->messageVar1 = inChordName;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handlePresetNameTextChanged (String inPresetName)
{
    if (mName == inPresetName) { return; }

    if (Presets::isValidFileName (inPresetName))
    {
        mName = inPresetName;
        mIsPresetModified = true;
    }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetNameTextChanged;
    message->messageVar1 = mName;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void PresetState::handleMouseDownOnCut (const int inInputNote)
{
    mClipboardChord = getChord (inInputNote);
    mChords.erase (inInputNote);
    mEditModeInputNote = 0;

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetModified;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnCopy (const int inInputNote)
{
    mClipboardChord = getChord (inInputNote);
}

void PresetState::handleMouseDownOnPaste (const int inInputNote)
{
    if (mClipboardChord.notes.isEmpty()) { return; }

    setChord (inInputNote, mClipboardChord);
    mEditModeInputNote = 0;

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetModified;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void PresetState::handleMouseDownOnNew()
{
    resetPresetState (false);
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileNew;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnSave()
{
    if (!isPresetValid() || !mIsPresetModified) { return; }

    File prevPresetFile = PRESET_FOLDER.getChildFile (mPresetFileName);
    if (prevPresetFile.existsAsFile()) { prevPresetFile.deleteFile(); }

    mPresetFileName = mName + PRESET_EXTENSION;
    mIsPresetModified = false;

    XmlElement rootXml ("ripchord");
    rootXml.addChildElement (Presets::getPresetXmlFromChords (mChords));
    rootXml.writeTo (PRESET_FOLDER.getChildFile (mPresetFileName));

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileSaved;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnImportMidi()
{
    FileChooser chooser ("Select a MIDI file(s)...", DESKTOP_FOLDER, "*.mid");

    if (chooser.browseForMultipleFilesToOpen())
    {
        juce::Array<File> chosenFiles = chooser.getResults();

        for (int index = 0; index < chosenFiles.size(); index++)
        {
            File chosenFile = chosenFiles.getUnchecked (index);

            if (index + 1 == chosenFiles.size())
            {
                loadMidiFile (chosenFile);
            }
            else
            {
                saveMidiFile (chosenFile);
            }
        }
    }
}

void PresetState::handleMouseDownOnExportMidi()
{
    if (!isPresetValid()) { return; }

    FileChooser chooser ("Copy preset to...", DESKTOP_FOLDER, "*" + PRESET_EXTENSION);

    if (chooser.browseForFileToSave (true))
    {
        XmlElement rootXml ("ripchord");
        rootXml.addChildElement (Presets::getPresetXmlFromChords (mChords));
        rootXml.writeTo (chooser.getResult());
    }
}

void PresetState::handleMouseDownOnImportPreset()
{
    FileChooser chooser ("Select a preset file(s)...", DESKTOP_FOLDER, "*" + PRESET_EXTENSION);

    if (chooser.browseForMultipleFilesToOpen())
    {
        juce::Array<File> chosenFiles = chooser.getResults();

        for (int index = 0; index < chosenFiles.size(); index++)
        {
            File chosenFile = chosenFiles.getUnchecked (index);

            if (index + 1 == chosenFiles.size())
            {
                loadPresetFile (chosenFile);
            }
            else
            {
                savePresetFile (chosenFile);
            }
        }
    }
}

void PresetState::handleMouseDownOnExportPreset()
{
    if (!isPresetValid()) { return; }

    FileChooser chooser ("Copy preset to...", DESKTOP_FOLDER, "*" + PRESET_EXTENSION);

    if (chooser.browseForFileToSave (true))
    {
        XmlElement rootXml ("ripchord");
        rootXml.addChildElement (Presets::getPresetXmlFromChords (mChords));
        rootXml.writeTo (chooser.getResult());
    }
}

void PresetState::handleMouseDownOnDuplicate()
{
    resetPresetState (true);
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileNew;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnEditLeft()
{
    juce::Array<int> inputNotes = getPresetInputNotes();
    if (inputNotes.isEmpty() || inputNotes.contains (21) || mEditModeInputNote == 21) { return; }

    std::map<int, Chord> nextChords;

    for (int inputNote : inputNotes)
    {
        nextChords[inputNote - 1] = getChord (inputNote);
    }

    const int prevEditModeInputNote = mEditModeInputNote;
    const int nextEditModeInputNote = mEditModeInputNote > 0 ? mEditModeInputNote - 1 : 0;

    mChords.clear();
    mChords = nextChords;
    mEditModeInputNote = nextEditModeInputNote;

    juce::Array<int> prevPresetInputNotes = inputNotes;
    juce::Array<int> nextPresetInputNotes = getPresetInputNotes();

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeShiftArrow;
    message->messageVar1 = prevEditModeInputNote;
    message->messageVar2 = nextEditModeInputNote;
    message->messageArray1 = prevPresetInputNotes;
    message->messageArray2 = nextPresetInputNotes;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnEditRight()
{
    juce::Array<int> inputNotes = getPresetInputNotes();
    if (inputNotes.isEmpty() || inputNotes.contains (108) || mEditModeInputNote == 108) { return; }

    std::map<int, Chord> nextChords;

    for (int inputNote : inputNotes)
    {
        nextChords[inputNote + 1] = getChord (inputNote);
    }

    const int prevEditModeInputNote = mEditModeInputNote;
    const int nextEditModeInputNote = mEditModeInputNote > 0 ? mEditModeInputNote + 1 : 0;

    mChords.clear();
    mChords = nextChords;
    mEditModeInputNote = nextEditModeInputNote;

    juce::Array<int> prevPresetInputNotes = inputNotes;
    juce::Array<int> nextPresetInputNotes = getPresetInputNotes();

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeShiftArrow;
    message->messageVar1 = prevEditModeInputNote;
    message->messageVar2 = nextEditModeInputNote;
    message->messageArray1 = prevPresetInputNotes;
    message->messageArray2 = nextPresetInputNotes;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnAllWhite()
{
    juce::Array<int> inputNotes = getPresetInputNotes();
    if (inputNotes.isEmpty()) { return; }

    inputNotes.sort();
    int lowestNote = inputNotes[0];
    while (Keyboard::isBlackKey(lowestNote)) { lowestNote++; }
    if (lowestNote > 108) { return; }

    int whiteNoteIndex = Keyboard::getWhiteNoteIndex (lowestNote);
    std::map<int, Chord> nextChords;

    for (int inputNote : inputNotes)
    {
        if (whiteNoteIndex > 51) { return; }
        int nextWhiteNote = Keyboard::getWhiteNoteNumber (whiteNoteIndex);
        nextChords[nextWhiteNote] = getChord (inputNote);
        whiteNoteIndex++;
    }

    mChords.clear();
    mChords = nextChords;
    mEditModeInputNote = 0;

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetModified;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnAllBlack()
{
    juce::Array<int> inputNotes = getPresetInputNotes();
    if (inputNotes.isEmpty()) { return; }

    inputNotes.sort();
    int lowestNote = inputNotes[0];
    while (!Keyboard::isBlackKey(lowestNote)) { lowestNote++; }
    if (lowestNote > 106) { return; }

    int blackNoteIndex = Keyboard::getBlackNoteIndex (lowestNote);
    std::map<int, Chord> nextChords;

    for (int inputNote : inputNotes)
    {
        if (blackNoteIndex > 35) { return; }
        int nextBlackNote = Keyboard::getBlackNoteNumber (blackNoteIndex);
        nextChords[nextBlackNote] = getChord (inputNote);
        blackNoteIndex++;
    }

    mChords.clear();
    mChords = nextChords;
    mEditModeInputNote = 0;

    mIsPresetModified = true;
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetModified;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseDownOnPreset (File inPresetFile)
{
    if (inPresetFile.existsAsFile())
    {
        loadPresetFile (inPresetFile);
    }
}

//==============================================================================
Chord PresetState::getChord (const int inInputNote)
{
    auto pair = mChords.find (inInputNote);
    if (pair == mChords.end()) { return mEmptyChord; }
    return pair->second;
}

void PresetState::setChord (const int inInputNote, Chord inChord)
{
    mChords[inInputNote] = inChord;
}

void PresetState::resetPresetState (bool inKeepChords)
{
    if (!inKeepChords) { mChords.clear(); }

    mName.clear();
    mPresetFileName.clear();
    mIsPresetModified = false;
    mEditModeInputNote = 0;
}

void PresetState::loadMidiFile (File inMidiFile)
{
    resetPresetState (false);
    mName = inMidiFile.getFileNameWithoutExtension();
    mPresetFileName = mName + PRESET_EXTENSION;
    mChords = saveMidiFile (inMidiFile);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileLoaded;
    message->messageVar1 = mName;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

void PresetState::loadPresetFile (File inPresetFile)
{
    resetPresetState (false);
    mName = inPresetFile.getFileNameWithoutExtension();
    mPresetFileName = mName + PRESET_EXTENSION;
    mChords = savePresetFile (inPresetFile);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileLoaded;
    message->messageVar1 = mName;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

std::map<int, Chord> PresetState::saveMidiFile (File inMidiFile)
{
    String presetFileName = inMidiFile.getFileNameWithoutExtension() + PRESET_EXTENSION;
    std::map<int, Chord> chords = Presets::getChordsFromMidiFile (inMidiFile);

    File prevPresetFile = PRESET_FOLDER.getChildFile (presetFileName);
    if (prevPresetFile.existsAsFile()) { prevPresetFile.deleteFile(); }

    XmlElement rootXml ("ripchord");
    rootXml.addChildElement (Presets::getPresetXmlFromChords (chords));
    rootXml.writeTo (PRESET_FOLDER.getChildFile (presetFileName));

    return chords;
}

std::map<int, Chord> PresetState::savePresetFile (File inPresetFile)
{
    String presetFileName = inPresetFile.getFileName();
    std::unique_ptr<XmlElement> inRootXml = parseXML (inPresetFile);
    XmlElement* presetXml = inRootXml->getFirstChildElement();
    std::map<int, Chord> chords = Presets::getChordsFromPresetXml (presetXml);

    File prevPresetFile = PRESET_FOLDER.getChildFile (presetFileName);
    if (prevPresetFile.existsAsFile()) { prevPresetFile.deleteFile(); }

    XmlElement rootXml ("ripchord");
    rootXml.addChildElement (Presets::getPresetXmlFromChords (chords));
    rootXml.writeTo (PRESET_FOLDER.getChildFile (presetFileName));

    return chords;
}

//==============================================================================
XmlElement* PresetState::exportPresetStateXml()
{
    XmlElement* presetStateXml = new XmlElement ("PresetState");
    presetStateXml->setAttribute ("name", mName);
    presetStateXml->setAttribute ("presetFileName", mPresetFileName);
    presetStateXml->setAttribute ("isPresetModified", mIsPresetModified);
    presetStateXml->addChildElement (Presets::getPresetXmlFromChords (mChords));
    return presetStateXml;
}

void PresetState::importPresetStateXml (XmlElement* inPresetStateXml)
{
    XmlElement* presetXml = inPresetStateXml->getFirstChildElement();
    mName = inPresetStateXml->getStringAttribute ("name");
    mPresetFileName = inPresetStateXml->getStringAttribute ("presetFileName");
    mIsPresetModified = inPresetStateXml->getBoolAttribute ("isPresetModified");
    mChords = Presets::getChordsFromPresetXml (presetXml);
}
