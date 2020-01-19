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
    static inline Array<File> getSortedPresetFiles()
    {
        Array<File> files = PRESET_FOLDER.findChildFiles (File::findFiles, false, "*.rpc");
        files.sort();
        return files;
    }

    static inline XmlElement getXmlFromPresetState (String inName, std::map<int, Chord> inChords)
    {
        XmlElement presetXml ("ripchord");
        XmlElement* mappingsXml = new XmlElement ("KeyboardMapping");
        mappingsXml->setAttribute ("name", inName);

        for (const auto& pair : inChords)
        {
            XmlElement* mappingXml = new XmlElement ("mapping");
            XmlElement* chordXml = new XmlElement ("chord");
            StringArray chordNotes;

            for (const int chordNote : pair.second.notes)
            {
                chordNotes.add (String (chordNote));
            }

            mappingXml->setAttribute ("note", String (pair.first));
            chordXml->setAttribute ("name", pair.second.name);
            chordXml->setAttribute ("notes", chordNotes.joinIntoString (";"));

            mappingXml->addChildElement (chordXml);
            mappingsXml->addChildElement (mappingXml);
        }

        presetXml.addChildElement (mappingsXml);
        return presetXml;
    }

    static inline String getPresetNameFromXml (const File& inFile)
    {
        std::unique_ptr<XmlElement> presetXml = parseXML (inFile);
        XmlElement* mappingsXml = presetXml->getChildByName ("KeyboardMapping");
        return mappingsXml->getStringAttribute ("name");
    }

    static inline std::map<int, Chord> getPresetChordsFromXml (const File& inFile)
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

            chord.name = name;
            chord.notes = notes;
            chords[note] = chord;
        }

        return chords;
    }
}
