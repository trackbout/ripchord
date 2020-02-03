#pragma once

#include "System.h"

//==============================================================================
const String PRESET_EXTENSION = ".rpc";
const File PRESET_FOLDER = System::getUserDataPath (ProjectInfo::companyName,
                                                    ProjectInfo::projectName).getChildFile ("Presets");

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

    static inline std::map<int, Chord> getChordsFromPresetXml (XmlElement* inPresetXml)
    {
        std::map<int, Chord> chords;
        String inputTagName = inPresetXml->getTagName() == "preset" ? "input" : "mapping";

        forEachXmlChildElementWithTagName (*inPresetXml, inputXml, inputTagName)
        {
            Chord chord;
            juce::Array<int> notes;
            int note = inputXml->getIntAttribute("note");
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

    static inline bool isValidFileName (String inFileName)
    {
        const String valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 _-";

        for (int index = 0; index < inFileName.length(); index++)
        {
            if (valid.indexOfChar (inFileName[index]) < 0) { return false; }
        }

        return true;
    }

    static inline Array<File> getSortedPresetFiles()
    {
        Array<File> files = PRESET_FOLDER.findChildFiles (File::findFiles, false, "*" + PRESET_EXTENSION);
        files.sort();
        return files;
    }
}
