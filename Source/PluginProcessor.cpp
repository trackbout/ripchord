#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordPluginProcessor::RipchordPluginProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
    #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
            .withInput  ("Input",  AudioChannelSet::stereo(), true)
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
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto index = totalNumInputChannels; index < totalNumOutputChannels; ++index)
    {
        inAudioBuffer.clear (index, 0, inAudioBuffer.getNumSamples());
    }

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
    // auto* channelData = buffer.getWritePointer (channel);
    // ..do something to the data...
    }
}

//==============================================================================
bool RipchordPluginProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* RipchordPluginProcessor::createEditor()
{
    return new RipchordPluginEditor (*this);
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
