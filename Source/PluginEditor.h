#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
class RipchordAudioProcessorEditor : public AudioProcessorEditor
{
public:
    //==============================================================================
    RipchordAudioProcessorEditor (RipchordAudioProcessor&);
    ~RipchordAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RipchordAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RipchordAudioProcessorEditor)
};
