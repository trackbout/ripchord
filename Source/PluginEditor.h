#pragma once

#include "JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
class RipchordPluginEditor : public AudioProcessorEditor
{
public:
    //==============================================================================
    RipchordPluginEditor (RipchordPluginProcessor&);
    ~RipchordPluginEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RipchordPluginProcessor& mPluginProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RipchordPluginEditor)
};
