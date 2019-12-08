#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordAudioProcessor::RipchordAudioProcessor()
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

RipchordAudioProcessor::~RipchordAudioProcessor()
{
}

//==============================================================================
const String RipchordAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RipchordAudioProcessor::acceptsMidi() const
{
    #if JucePlugin_WantsMidiInput
        return true;
    #else
        return false;
    #endif
}

bool RipchordAudioProcessor::producesMidi() const
{
    #if JucePlugin_ProducesMidiOutput
        return true;
    #else
        return false;
    #endif
}

bool RipchordAudioProcessor::isMidiEffect() const
{
    #if JucePlugin_IsMidiEffect
        return true;
    #else
        return false;
    #endif
}

double RipchordAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RipchordAudioProcessor::getNumPrograms()
{
    return 1;
}

int RipchordAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RipchordAudioProcessor::setCurrentProgram (int index)
{
}

const String RipchordAudioProcessor::getProgramName (int index)
{
    return {};
}

void RipchordAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void RipchordAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void RipchordAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RipchordAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    #if JucePlugin_IsMidiEffect
        ignoreUnused (layouts);
        return true;
    #else
        if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    #if ! JucePlugin_IsSynth
        if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
    #endif
        return true;
    #endif
}
#endif

void RipchordAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    {
        buffer.clear (i, 0, buffer.getNumSamples());
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
bool RipchordAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* RipchordAudioProcessor::createEditor()
{
    return new RipchordAudioProcessorEditor (*this);
}

//==============================================================================
void RipchordAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void RipchordAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RipchordAudioProcessor();
}
