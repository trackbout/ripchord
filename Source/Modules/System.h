#pragma once

//==============================================================================
namespace System
{
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

    //==============================================================================
    // To sort files by modification date (with last modified files first).
    struct FileModificationTimeSorter
    {
        static int compareElements (const File& inFile1, const File& inFile2)
        {
            auto time1 = inFile1.getLastModificationTime();
            auto time2 = inFile2.getLastModificationTime();

            if (time1 == time2)
            {
                return 0;
            }

            return time1 > time2 ? -1 : 1;
        }
    };

    //==============================================================================
    static inline PropertiesFile::Options createPluginPropertiesOptions (const String& inFilenameSuffix)
    {
        PropertiesFile::Options pluginPropertiesOptions;
        pluginPropertiesOptions.applicationName         = JucePlugin_Name;
        pluginPropertiesOptions.folderName              = File::addTrailingSeparator (JucePlugin_Manufacturer) + JucePlugin_Name;
        pluginPropertiesOptions.filenameSuffix          = inFilenameSuffix;
        pluginPropertiesOptions.osxLibrarySubFolder     = "Application Support";
        pluginPropertiesOptions.commonToAllUsers        = false;
        pluginPropertiesOptions.ignoreCaseOfKeyNames    = true;
        pluginPropertiesOptions.doNotSave               = false;
        pluginPropertiesOptions.millisecondsBeforeSaving = 10;
        pluginPropertiesOptions.storageFormat           = PropertiesFile::storeAsXML;
        return pluginPropertiesOptions;
    }
}
