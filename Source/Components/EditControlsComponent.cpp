#include "EditControlsComponent.h"

//==============================================================================
EditControlsComponent::EditControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mMidiState (mMainProcess.getMidiState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mAllWhiteButton, "AllWhite.svg", "", "AllWhiteON.svg", "");
    mImages.setDrawableButtonImages (mAllBlackButton, "AllBlack.svg", "", "AllBlackON.svg", "");
    mImages.setDrawableButtonImages (mEditRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");
    mImages.setDrawableButtonImages (mEditLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
    mImages.setDrawableButtonImages (mSuccess, "Success.svg");

    mAllWhiteButton.setTriggeredOnMouseDown (true);
    mAllWhiteButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mPresetState.handleClickAllWhite();
    };

    mEditLeftButton.setTriggeredOnMouseDown (true);
    mEditLeftButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mPresetState.handleClickEditLeft();
    };

    mSaveButton.setTriggeredOnMouseDown (true);
    mSaveButton.onClick = [this]() { mPresetState.handleClickSave(); };

    mEditRightButton.setTriggeredOnMouseDown (true);
    mEditRightButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mPresetState.handleClickEditRight();
    };

    mAllBlackButton.setTriggeredOnMouseDown (true);
    mAllBlackButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mPresetState.handleClickAllBlack();
    };

    addAndMakeVisible (mAllWhiteButton);
    addAndMakeVisible (mAllBlackButton);
    addAndMakeVisible (mEditRightButton);
    addAndMakeVisible (mEditLeftButton);
    addAndMakeVisible (mSaveButton);
    addChildComponent (mSuccess);
}

EditControlsComponent::~EditControlsComponent()
{
}

//==============================================================================
void EditControlsComponent::resized()
{
    mAllWhiteButton.setBounds (ALL_WHITE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mEditLeftButton.setBounds (EDIT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mSaveButton.setBounds (SAVE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mSuccess.setBounds (SAVE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mEditRightButton.setBounds (EDIT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mAllBlackButton.setBounds (ALL_BLACK_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
}

//==============================================================================
void EditControlsComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetModified): { handlePresetModified (inMessage); } break;
        case (MessageCode::kPresetFileSaved): { handlePresetFileSaved (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handlePresetModified (inMessage); } break;
        case (MessageCode::kPresetNameTextChanged): { handlePresetModified (inMessage); } break;
        case (MessageCode::kChordNameTextChanged): { handlePresetModified (inMessage); } break;
        case (MessageCode::kEditModeShiftArrow): { handlePresetModified (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void EditControlsComponent::handleToggleMode (const DataMessage* inMessage)
{
    if (mGlobalState.isPlayMode()) { setVisible (false); }

    if (mGlobalState.isEditMode())
    {
        setVisible (true);
        mSuccess.setVisible (false);
        bool isPresetSaveable = mPresetState.isPresetModified() && mPresetState.isPresetValid();
        mImages.setDrawableButtonImages (mSaveButton, isPresetSaveable ? "SaveON.svg" : "Save.svg");
    }
}

void EditControlsComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
}

void EditControlsComponent::handlePresetModified (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mImages.setDrawableButtonImages (mSaveButton, mPresetState.isPresetValid() ? "SaveON.svg" : "Save.svg");
}

void EditControlsComponent::handlePresetFileSaved (const DataMessage* inMessage)
{
    mSuccess.setVisible (true);
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
}

void EditControlsComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
}
