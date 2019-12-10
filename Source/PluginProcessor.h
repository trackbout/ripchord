#pragma once

#include "JuceHeader.h"

//==============================================================================
class RipchordPluginProcessor : public AudioProcessor
{
public:
    //==============================================================================
    RipchordPluginProcessor();
    ~RipchordPluginProcessor();

    //==============================================================================
    const String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& name) override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    #ifndef JucePlugin_PreferredChannelConfigurations
        bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    void setLastEditorWidth (int width);
    void setLastEditorHeight (int height);
    int getLastEditorWidth (int defaultWidth) const;
    int getLastEditorHeight (int defaultHeight) const;

    //==============================================================================
    void getStateInformation (MemoryBlock& memory) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    int mLastEditorWidth = -1;
    int mLastEditorHeight = -1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RipchordPluginProcessor)
};
