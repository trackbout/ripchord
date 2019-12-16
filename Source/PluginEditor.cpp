#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordPluginEditor::RipchordPluginEditor (RipchordPluginProcessor& inRipchordPluginProcessor)
:   AudioProcessorEditor (&inRipchordPluginProcessor),
    mPluginProcessor (inRipchordPluginProcessor),
    mMainComponent { mPluginProcessor.getMainProcess() }
{
    addAndMakeVisible (mMainComponent);

    if (auto* boundsConstrainer = getConstrainer())
    {
        boundsConstrainer->setFixedAspectRatio (EDITOR_WIDTH / (float) EDITOR_HEIGHT);
    }

    setResizable (true, true);
    setResizeLimits(EDITOR_WIDTH * 0.5f, EDITOR_HEIGHT * 0.5f, EDITOR_WIDTH * 1.5f, EDITOR_HEIGHT * 1.5f);
    setSize (mPluginProcessor.getLastEditorWidth (EDITOR_WIDTH), mPluginProcessor.getLastEditorHeight (EDITOR_HEIGHT));
}

RipchordPluginEditor::~RipchordPluginEditor()
{
}

//==============================================================================
void RipchordPluginEditor::paint (Graphics& inGraphics)
{
}

void RipchordPluginEditor::resized()
{
    auto area = getLocalBounds();
    mMainComponent.setBounds (area);

    if (isMouseButtonDownAnywhere()) {
        mPluginProcessor.setLastEditorWidth (getWidth());
        mPluginProcessor.setLastEditorHeight (getHeight());
    }
}
