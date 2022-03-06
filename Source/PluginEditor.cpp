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

    int lastWidth = mPluginProcessor.getLastEditorWidth();
    int lastHeight = mPluginProcessor.getLastEditorHeight();

    int savedWidth = mConfigFile.getValue ("width").getIntValue();
    int savedHeight = mConfigFile.getValue ("height").getIntValue();

    int useWidth = savedWidth > 0 ? savedWidth : lastWidth;
    int useHeight = savedHeight > 0 ? savedHeight : lastHeight;

    setResizable (true, true);

    setSize (useWidth, useHeight);

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

    int width = getWidth();
    int height = getHeight();

    mConfigFile.setValue ("width", width);
    mConfigFile.setValue ("height", height);
    mConfigFile.saveIfNeeded();

    mPluginProcessor.setLastEditorWidth (width);
    mPluginProcessor.setLastEditorHeight (height);
}
