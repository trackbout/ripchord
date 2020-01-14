#pragma once

//==============================================================================
const String PRESET_FILE_EXTENSION = ".rpc";

//==============================================================================
struct Chord
{
    String name;
    juce::Array<int> notes;
};

//==============================================================================
namespace Preset
{
    //==============================================================================
    static inline XmlElement getXmlFromPresetState (String inName, std::map<int, Chord> inChords)
    {
        XmlElement xml ("ripchord");
        XmlElement* preset = new XmlElement ("KeyboardMapping");
        preset->setAttribute ("name", inName);

        std::map<int, Chord>::iterator pair;

        for (pair = inChords.begin(); pair != inChords.end(); ++pair)
        {
            XmlElement* mapping = new XmlElement ("mapping");
            XmlElement* chord = new XmlElement ("chord");
            StringArray chordNotes;

            for (const int chordNote : pair->second.notes)
            {
                chordNotes.add (String (chordNote));
            }

            mapping->setAttribute ("note", String (pair->first));
            chord->setAttribute ("name", pair->second.name);
            chord->setAttribute ("notes", chordNotes.joinIntoString (";"));

            mapping->addChildElement (chord);
            preset->addChildElement (mapping);
        }

        xml.addChildElement (preset);
        return xml;
    }
}
