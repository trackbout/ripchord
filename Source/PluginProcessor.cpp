#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordPluginProcessor::RipchordPluginProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
    #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
            .withInput ("Input", AudioChannelSet::stereo(), true)
        #endif
        .withOutput ("Output", AudioChannelSet::stereo(), true)
    #endif
)
#endif
{
}

RipchordPluginProcessor::~RipchordPluginProcessor()
{
}

//==============================================================================
const String RipchordPluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RipchordPluginProcessor::acceptsMidi() const
{
    #if JucePlugin_WantsMidiInput
        return true;
    #else
        return false;
    #endif
}

bool RipchordPluginProcessor::producesMidi() const
{
    #if JucePlugin_ProducesMidiOutput
        return true;
    #else
        return false;
    #endif
}

bool RipchordPluginProcessor::isMidiEffect() const
{
    #if JucePlugin_IsMidiEffect
        return true;
    #else
        return false;
    #endif
}

double RipchordPluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RipchordPluginProcessor::getNumPrograms()
{
    return 1;
}

int RipchordPluginProcessor::getCurrentProgram()
{
    return 0;
}

void RipchordPluginProcessor::setCurrentProgram (int inIndex)
{
}

const String RipchordPluginProcessor::getProgramName (int inIndex)
{
    return {};
}

void RipchordPluginProcessor::changeProgramName (int inIndex, const String& inName)
{
}

//==============================================================================
void RipchordPluginProcessor::prepareToPlay (double inSampleRate, int inSamplesPerBlock)
{
}

void RipchordPluginProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RipchordPluginProcessor::isBusesLayoutSupported (const BusesLayout& inLayouts) const
{
    #if JucePlugin_IsMidiEffect
        ignoreUnused (inLayouts);
        return true;
    #else
        if (inLayouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && inLayouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    #if ! JucePlugin_IsSynth
        if (inLayouts.getMainOutputChannelSet() != inLayouts.getMainInputChannelSet())
        return false;
    #endif
        return true;
    #endif
}
#endif

void RipchordPluginProcessor::processBlock (AudioBuffer<float>& inAudioBuffer, MidiBuffer& inMidiBuffer)
{
}

//==============================================================================
AudioProcessorEditor* RipchordPluginProcessor::createEditor()
{
    return new RipchordPluginEditor (*this);
}

bool RipchordPluginProcessor::hasEditor() const
{
    return true;
}

void RipchordPluginProcessor::setLastEditorWidth (int inWidth)
{
    mLastEditorWidth = inWidth;
}

void RipchordPluginProcessor::setLastEditorHeight (int inHeight)
{
    mLastEditorHeight = inHeight;
}

int RipchordPluginProcessor::getLastEditorWidth (int inDefaultWidth) const
{
    if (mLastEditorWidth > 0)
    {
        return mLastEditorWidth;
    }

    return inDefaultWidth;
}

int RipchordPluginProcessor::getLastEditorHeight (int inDefaultHeight) const
{
    if (mLastEditorHeight > 0)
    {
        return mLastEditorHeight;
    }

    return inDefaultHeight;
}

//==============================================================================
void RipchordPluginProcessor::getStateInformation (MemoryBlock& inMemory)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RipchordPluginProcessor::setStateInformation (const void* inData, int inSizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RipchordPluginProcessor();
}
