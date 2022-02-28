#pragma once

//==============================================================================
namespace System
{
    //==============================================================================
    static inline bool isValidFileName (String inFileName)
    {
        const String valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 #_-()";

        if (inFileName.length() < 1) { return false; }

        for (int index = 0; index < inFileName.length(); index++)
        {
            if (valid.indexOfChar (inFileName[index]) < 0) { return false; }
        }

        return true;
    }

    static inline File getUserDataPath (StringRef inCompanyName, StringRef inAppName)
    {
        #if JUCE_MAC || JUCE_IOS
            File directory ("~/Library/");
            directory = directory.getChildFile ("Application Support");
        #elif JUCE_LINUX || JUCE_ANDROID
            const File directory ("~");
        #elif JUCE_WINDOWS
            File directory (File::getSpecialLocation (File::userApplicationDataDirectory));
        #endif

        return directory.getChildFile (inCompanyName).getChildFile (inAppName);
    }

    static inline PropertiesFile::Options createPluginPropertiesOptions (const String& inFilenameSuffix)
    {
        PropertiesFile::Options pluginPropertiesOptions;
        pluginPropertiesOptions.applicationName = JucePlugin_Name;
        pluginPropertiesOptions.folderName = File::addTrailingSeparator (JucePlugin_Manufacturer) + JucePlugin_Name;
        pluginPropertiesOptions.filenameSuffix = inFilenameSuffix;
        pluginPropertiesOptions.osxLibrarySubFolder = "Application Support";
        pluginPropertiesOptions.commonToAllUsers = false;
        pluginPropertiesOptions.ignoreCaseOfKeyNames = true;
        pluginPropertiesOptions.doNotSave = false;
        pluginPropertiesOptions.millisecondsBeforeSaving = 10;
        pluginPropertiesOptions.storageFormat = PropertiesFile::storeAsXML;
        return pluginPropertiesOptions;
    }
}

const String TEMP_FILE_NAME = "Ripchord.mid";
const File TEMP_FOLDER = File::getSpecialLocation (File::SpecialLocationType::tempDirectory);
const File DESKTOP_FOLDER = File::getSpecialLocation (File::userDesktopDirectory);
const File RIPCHORD_FOLDER = System::getUserDataPath (ProjectInfo::companyName, ProjectInfo::projectName);
const File PRESET_FOLDER = RIPCHORD_FOLDER.getChildFile ("Presets");
