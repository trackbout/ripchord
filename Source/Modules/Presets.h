#pragma once

#include "Midi.h"
#include "System.h"
#include "Keyboard.h"

//==============================================================================
const String PRESET_EXTENSION = ".rpc";

//==============================================================================
struct Preset
{
    int indexValue;
    String fileName;
    bool isFavorite;
};

//==============================================================================
struct Chord
{
    String name;
    juce::Array<int> notes;
};

//==============================================================================
namespace Presets
{
    //==============================================================================
    static inline Array<File> getSortedPresetFiles()
    {
        Array<File> files = PRESET_FOLDER.findChildFiles (File::findFiles, false, "*" + PRESET_EXTENSION);
        files.sort();
        return files;
    }

    static inline String generateNameFromNotes (juce::Array<int> inNotes)
    {
        String chordName = "";

        for (int index = 0; index < inNotes.size(); index++)
        {
            if ((index + 1) == inNotes.size())
            {
                chordName << Keyboard::getNoteNameFromNumber (inNotes[index]);
            }
            else
            {
                chordName << Keyboard::getNoteNameFromNumber (inNotes[index]) << " ";
            }
        }

        return chordName;
    }

    static inline XmlElement* getPresetXmlFromChords (std::map<int, Chord> inChords)
    {
        XmlElement* presetXml = new XmlElement ("preset");

        for (const auto& pair : inChords)
        {
            StringArray chordNotes;
            juce::Array<int> sortedNotes = pair.second.notes;
            sortedNotes.sort();

            for (const int chordNote : sortedNotes)
            {
                chordNotes.add (String (chordNote));
            }

            XmlElement* inputXml = new XmlElement ("input");
            XmlElement* chordXml = new XmlElement ("chord");

            inputXml->setAttribute ("note", String (pair.first));
            chordXml->setAttribute ("name", pair.second.name);
            chordXml->setAttribute ("notes", chordNotes.joinIntoString (";"));

            inputXml->addChildElement (chordXml);
            presetXml->addChildElement (inputXml);
        }

        return presetXml;
    }

    static inline MidiMessageSequence getMidiSequenceFromChords (std::map<int, Chord> inChords)
    {
        float ticks = 0.0f;
        MidiMessageSequence sequence;

        for (const auto& pair : inChords)
        {
            juce::Array<int> notes = pair.second.notes;

            for (const int chordNote : notes)
            {
                const auto& noteOn = MidiMessage::noteOn (1, chordNote, 0.8f);
                const auto& noteOff = MidiMessage::noteOff (1, chordNote);
                sequence.addEvent (noteOn, ticks);
                sequence.addEvent (noteOff, ticks + TICKS_PER_QUARTER_NOTE / 2);
            }

            ticks = ticks + TICKS_PER_QUARTER_NOTE;
        }

        return sequence;
    }

    static inline std::map<int, Chord> getChordsFromPresetXml (XmlElement* inPresetXml)
    {
        std::map<int, Chord> chords;

        for (XmlElement* inputXml : inPresetXml->getChildWithTagNameIterator ("input"))
        {
            Chord chord;
            juce::Array<int> notes;
            int note = inputXml->getIntAttribute ("note");
            XmlElement* chordXml = inputXml->getChildByName ("chord");
            String notesString = chordXml->getStringAttribute ("notes");
            StringArray notesSA = StringArray::fromTokens (notesString, ";", "");

            String name = chordXml->getStringAttribute ("name");
            for (String& note : notesSA) { notes.add (note.getIntValue()); }

            if (notes.size() > 0)
            {
                notes.sort();
                chord.name = name;
                chord.notes = notes;
                chords[note] = chord;
            }
        }

        return chords;
    }

    static inline std::map<int, Chord> getChordsFromMidiFile (File inMidiFile)
    {
        int noteNumber = 60;
        juce::Array<int> currentNotes;
        juce::Array<String> chordNames;
        std::map<int, Chord> chords;

        MidiFile midiFile;
        MidiMessageSequence events;
        FileInputStream midiFileStream (inMidiFile);
        midiFile.readFrom (midiFileStream);

        const int largeNumberOfEvents = 160;
        const int numberOfTracks = midiFile.getNumTracks();

        for (int index = 0; index < numberOfTracks; index++)
        {
            const MidiMessageSequence* midiTrack = midiFile.getTrack (index);

            for (MidiMessageSequence::MidiEventHolder* event : *midiTrack)
            {
                if (event->message.isNoteOnOrOff())
                {
                    events.addEvent (event->message);
                }
            }
        }

        if (events.getNumEvents() > largeNumberOfEvents)
        {
            noteNumber = 21;
        }

        for (MidiMessageSequence::MidiEventHolder* event : events)
        {
            if (noteNumber > 108) { return chords; }

            const MidiMessage message = event->message;

            if (message.isNoteOn())
            {
                currentNotes.add (message.getNoteNumber());
            }

            if (message.isNoteOff() && !currentNotes.isEmpty())
            {
                currentNotes.sort();
                const String chordName = generateNameFromNotes (currentNotes);

                if (!chordNames.contains (chordName))
                {
                    Chord chord;
                    chord.name = chordName;
                    chord.notes = currentNotes;
                    chordNames.add (chordName);
                    chords[noteNumber] = chord;
                    noteNumber = noteNumber + 1;
                }

                currentNotes.clear();
            }
        }

        return chords;
    }
}
