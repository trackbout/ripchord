#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RipchordPluginEditor::RipchordPluginEditor (RipchordPluginProcessor& inRipchordPluginProcessor)
:   AudioProcessorEditor (&inRipchordPluginProcessor),
    mPluginProcessor (inRipchordPluginProcessor),
    mMainComponent { mPluginProcessor.getMainProcess() }
{
    if (auto* boundsConstrainer = getConstrainer())
    {
        boundsConstrainer->setFixedAspectRatio (EDITOR_WIDTH / (float) EDITOR_HEIGHT);
        boundsConstrainer->setMinimumSize (EDITOR_WIDTH * 0.5f, EDITOR_HEIGHT * 0.5f);
        boundsConstrainer->setMaximumSize (EDITOR_WIDTH * 2.0f, EDITOR_HEIGHT * 2.0f);
    }

    setResizable (true, true);
    setSize (mPluginProcessor.getLastEditorWidth(), mPluginProcessor.getLastEditorHeight());

    addAndMakeVisible (mMainComponent);
}

RipchordPluginEditor::~RipchordPluginEditor()
{
}

//==============================================================================
void RipchordPluginEditor::resized()
{
    auto area = getLocalBounds();
    mMainComponent.setBounds (area);
    mPluginProcessor.setLastEditorWidth (getWidth());
    mPluginProcessor.setLastEditorHeight (getHeight());
}
