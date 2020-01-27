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
    static inline std::map<int, Chord> legacyGetChordsFromXml (const File& inFile)
    {
        std::map<int, Chord> chords;
        std::unique_ptr<XmlElement> presetXml = parseXML (inFile);
        XmlElement* mappingsXml = presetXml->getChildByName ("KeyboardMapping");

        forEachXmlChildElementWithTagName (*mappingsXml, mappingXml, "mapping")
        {
            Chord chord;
            juce::Array<int> notes;
            int note = mappingXml->getIntAttribute("note");
            XmlElement* chordXml = mappingXml->getChildByName ("chord");
            String notesString = chordXml->getStringAttribute ("notes");
            StringArray notesSA = StringArray::fromTokens (notesString, ";", "");

            String name = chordXml->getStringAttribute ("name");
            for (String& note : notesSA) { notes.add (note.getIntValue()); }

            if (notes.size() > 0)
            {
                chord.name = name;
                chord.notes = notes;
                chords[note] = chord;
            }
        }

        return chords;
    }

    static inline std::map<int, Chord> getChordsFromXml (const File& inFile)
    {
        std::unique_ptr<XmlElement> presetXml = parseXML (inFile);
        XmlElement* firstChildXml = presetXml->getFirstChildElement();
        String tagName = firstChildXml->getTagName();

        if (tagName == "KeyboardMapping") { return legacyGetChordsFromXml (inFile); }

        std::map<int, Chord> chords;

        forEachXmlChildElementWithTagName (*firstChildXml, inputXml, "input")
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
                chord.name = name;
                chord.notes = notes;
                chords[note] = chord;
            }
        }

        return chords;
    }

    static inline XmlElement* getInnerXmlPointerFromChords (std::map<int, Chord> inChords)
    {
        XmlElement* presetXml = new XmlElement ("preset");

        for (const auto& pair : inChords)
        {
            StringArray chordNotes;

            for (const int chordNote : pair.second.notes)
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

    static inline XmlElement getXmlFromChords (std::map<int, Chord> inChords)
    {
        XmlElement rootXml ("ripchord");
        XmlElement* presetXml = getInnerXmlPointerFromChords (inChords);
        rootXml.addChildElement (presetXml);
        return rootXml;
    }

    static inline bool isValidFileName (String inFileName)
    {
        const String valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ -_1234567890";

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
