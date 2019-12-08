#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordPluginEditor::RipchordPluginEditor (RipchordPluginProcessor& inRipchordPluginProcessor)
:   AudioProcessorEditor (&inRipchordPluginProcessor),
    mPluginProcessor (inRipchordPluginProcessor)
{
    setSize (400, 300);
}

RipchordPluginEditor::~RipchordPluginEditor()
{
}

//==============================================================================
void RipchordPluginEditor::paint (Graphics& inGraphics)
{
    inGraphics.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    inGraphics.setColour (Colours::white);
    inGraphics.setFont (15.0f);
    inGraphics.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void RipchordPluginEditor::resized()
{
}
