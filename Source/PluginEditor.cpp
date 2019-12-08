#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordAudioProcessorEditor::RipchordAudioProcessorEditor (RipchordAudioProcessor& p)
:   AudioProcessorEditor (&p),
    processor (p)
{
    setSize (400, 300);
}

RipchordAudioProcessorEditor::~RipchordAudioProcessorEditor()
{
}

//==============================================================================
void RipchordAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void RipchordAudioProcessorEditor::resized()
{

}
