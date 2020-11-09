#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Midi.h"

//==============================================================================
RipchordPluginProcessor::RipchordPluginProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
:   AudioProcessor (BusesProperties()
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
    auto playhead = getPlayHead();

    if (playhead != nullptr)
    {
        AudioPlayHead::CurrentPositionInfo info;

        if (playhead->getCurrentPosition(info))
        {
            const bool isPlaying = info.isPlaying || info.isRecording;
            mMainProcess.handleMidiBuffer (inMidiBuffer, inAudioBuffer.getNumSamples(), getSampleRate(), isPlaying);
        }
        else
        {
            mMainProcess.handleMidiBuffer (inMidiBuffer, inAudioBuffer.getNumSamples(), getSampleRate(), false);
        }
    }
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

//==============================================================================
int RipchordPluginProcessor::getLastEditorWidth() const
{
    if (mLastEditorWidth < 0) { return EDITOR_WIDTH; }
    return mLastEditorWidth;
}

int RipchordPluginProcessor::getLastEditorHeight() const
{
    if (mLastEditorWidth < 0) { return EDITOR_HEIGHT; }
    return mLastEditorHeight;
}

//==============================================================================
void RipchordPluginProcessor::setLastEditorWidth (int inEditorWidth)
{
    mLastEditorWidth = inEditorWidth;
}

void RipchordPluginProcessor::setLastEditorHeight (int inEditorHeight)
{
    mLastEditorHeight = inEditorHeight;
}

//==============================================================================
void RipchordPluginProcessor::getStateInformation (MemoryBlock& inMemory)
{
    XmlElement sessionXml (JucePlugin_Name);
    sessionXml.setAttribute ("t", String (Time::currentTimeMillis()));
    sessionXml.addChildElement (mMainProcess.exportSessionXml());
    copyXmlToBinary (sessionXml, inMemory);
}

void RipchordPluginProcessor::setStateInformation (const void* inData, int inSizeInBytes)
{
    std::unique_ptr<XmlElement> sessionXml (getXmlFromBinary (inData, inSizeInBytes));
    if (sessionXml == nullptr || !sessionXml->hasTagName (JucePlugin_Name)) { return; }

    mMainProcess.importSessionXml (sessionXml->getFirstChildElement());
}

//==============================================================================
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RipchordPluginProcessor();
}
