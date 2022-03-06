#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"
#include "MainComponent.h"
#include "Widgets.h"

//==============================================================================
class RipchordPluginEditor : public AudioProcessorEditor
{
public:
    //==============================================================================
    RipchordPluginEditor (RipchordPluginProcessor&);
    ~RipchordPluginEditor();

    //==============================================================================
    void resized() override;

    //==============================================================================
    struct DefaultLookAndFeel : public Widgets
    {
        DefaultLookAndFeel() { LookAndFeel::setDefaultLookAndFeel (this); }
        ~DefaultLookAndFeel() { LookAndFeel::setDefaultLookAndFeel (nullptr); }
    };

    SharedResourcePointer<DefaultLookAndFeel> lookAndFeel;

private:
    //==============================================================================
    RipchordPluginProcessor& mPluginProcessor;
    MainComponent mMainComponent;

    PropertiesFile mConfigFile { System::createPluginPropertiesOptions ("config") };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RipchordPluginEditor)
};
