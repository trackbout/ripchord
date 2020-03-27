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
void PresetState::handleMouseClickOnNew()
{
    resetPresetState();
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileNew;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleMouseClickOnMidi()
{
    FileChooser chooser ("Select a MIDI file...", PRESET_FOLDER, "*.mid");

    if (chooser.browseForFileToOpen())
    {
        File chosenFile = chooser.getResult();

        if (chosenFile.existsAsFile())
        {
            loadMidiFile (chosenFile);
        }
    }
}

void PresetState::handleMouseClickOnSave()
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

void PresetState::handleMouseClickOnImport()
{
    FileChooser chooser ("Select a preset file...", PRESET_FOLDER, "*" + PRESET_EXTENSION);

    if (chooser.browseForFileToOpen())
    {
        File chosenFile = chooser.getResult();

        if (chosenFile.existsAsFile())
        {
            loadPresetFile (chosenFile);
        }
    }
}

void PresetState::handleMouseClickOnExport()
{
    if (!isPresetValid()) { return; }

    FileChooser chooser ("Copy preset to...", PRESET_FOLDER, "*" + PRESET_EXTENSION);

    if (chooser.browseForFileToSave (true))
    {
        XmlElement rootXml ("ripchord");
        rootXml.addChildElement (Presets::getPresetXmlFromChords (mChords));
        rootXml.writeTo (chooser.getResult());
    }
}

void PresetState::handleMouseClickOnPreset (File inPresetFile)
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

void PresetState::loadMidiFile (File inMidiFile)
{
    MidiFile midiFile;
    FileInputStream midiFileStream (inMidiFile);
    midiFile.readFrom (midiFileStream);
    const MidiMessageSequence* midiTrack = midiFile.getTrack(0);

    for (MidiMessageSequence::MidiEventHolder* event : *midiTrack) {
        DBG (event->message.getDescription());
    }
}

void PresetState::loadPresetFile (File inPresetFile)
{
    resetPresetState();
    mPresetFileName = inPresetFile.getFileName();
    mName = inPresetFile.getFileNameWithoutExtension();

    std::unique_ptr<XmlElement> inRootXml = parseXML (inPresetFile);
    XmlElement* presetXml = inRootXml->getFirstChildElement();
    mChords = Presets::getChordsFromPresetXml (presetXml);

    File prevPresetFile = PRESET_FOLDER.getChildFile (mPresetFileName);
    if (prevPresetFile.existsAsFile()) { prevPresetFile.deleteFile(); }

    XmlElement rootXml ("ripchord");
    rootXml.addChildElement (Presets::getPresetXmlFromChords (mChords));
    rootXml.writeTo (PRESET_FOLDER.getChildFile (mPresetFileName));

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileLoaded;
    message->messageVar1 = mName;
    message->messageArray1 = getPresetInputNotes();
    sendMessage (message, ListenerType::kSync);
}

void PresetState::resetPresetState()
{
    mName.clear();
    mChords.clear();
    mPresetFileName.clear();
    mIsPresetModified = false;
    mEditModeInputNote = 0;
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
