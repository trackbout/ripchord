#include "RightClickComponent.h"

//==============================================================================
RightClickComponent::RightClickComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mCutButton, "Cut.svg");
    mImages.setDrawableButtonImages (mCopyButton, "Copy.svg");
    mImages.setDrawableButtonImages (mPasteButton, "Paste.svg");

    mCutButton.setTriggeredOnMouseDown (true);
    mCopyButton.setTriggeredOnMouseDown (true);
    mPasteButton.setTriggeredOnMouseDown (true);

    mCutButton.onClick = [this]()
    {
        DBG ("CUT");
    };

    mCopyButton.onClick = [this]()
    {
        DBG ("COPY");
    };

    mPasteButton.onClick = [this]()
    {
        DBG ("PASTE");
    };

    addAndMakeVisible (mCutButton);
    addAndMakeVisible (mCopyButton);
    addAndMakeVisible (mPasteButton);
}

RightClickComponent::~RightClickComponent()
{
}

//==============================================================================
void RightClickComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_OVERLAY);
    inGraphics.fillRect (getLocalBounds());
}

void RightClickComponent::resized()
{
//    auto mainArea = getLocalBounds();
}

//==============================================================================
void RightClickComponent::mouseDown (const MouseEvent& inEvent)
{
    if (handleBackgroundClick) { handleBackgroundClick(); }
}

//==============================================================================
void RightClickComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMenu): { handleToggleMenu (inMessage); } break;
        default: { } break;
    };
}

void RightClickComponent::handleToggleMenu (const DataMessage* inMessage)
{

}
