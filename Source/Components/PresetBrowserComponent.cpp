#include "JuceHeader.h"
#include "PresetBrowserComponent.h"

//==============================================================================
PresetBrowserComponent::PresetBrowserComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

PresetBrowserComponent::~PresetBrowserComponent()
{
}

//==============================================================================
void PresetBrowserComponent::setDimensions (int inWidth, int inHeight)
{
    mPresetWidth = int (inWidth * (PRESET_WIDTH / PRESET_LIST_WIDTH));
    mSpaceWidth = (inWidth - (PRESETS_PER_ROW * mPresetWidth)) / (PRESETS_PER_ROW + 1);

    mPresetHeight = int (inHeight * (ITEM_HEIGHT / PRESET_LIST_HEIGHT));
    mSpaceHeight = mPresetHeight * (HALF_SPACE / ITEM_HEIGHT);

    refreshBrowser (mBrowserState.getPresetNames());
}

//==============================================================================
void PresetBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kViewUpdated): { handleViewUpdated (inMessage); } break;
        case (MessageCode::kPresetNamesUpdated): { handlePresetNamesUpdated (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetBrowserComponent::handleViewUpdated (const DataMessage* inMessage)
{
    refreshBrowser (mBrowserState.getPresetNames());
}

void PresetBrowserComponent::handlePresetNamesUpdated (const DataMessage* inMessage)
{
    refreshBrowser (mBrowserState.getPresetNames());
}

void PresetBrowserComponent::handleMouseClickOnDelete (const int inIndexValue)
{
    mBrowserState.handleMouseClickOnDelete (inIndexValue);
}

void PresetBrowserComponent::handleMouseClickOnFavorite (const int inIndexValue)
{
    mBrowserState.handleMouseClickOnFavorite (inIndexValue);
}

void PresetBrowserComponent::refreshBrowser (juce::Array<juce::Array<String>> inPresetNames)
{
    if (mGlobalState.isKeyboardView()) { return; }

    removeAllChildren();

    for (int index = 0; index < inPresetNames.size(); index++)
    {
        juce::Array<String> presetName = inPresetNames[index];
        int x = (index % PRESETS_PER_ROW) * (mPresetWidth + mSpaceWidth) + mSpaceWidth;
        int y = (index / PRESETS_PER_ROW) * (mPresetHeight + mSpaceHeight) + mSpaceHeight;

        auto* presetComponent = new PresetComponent (index, presetName[0], presetName[1] == "true");
        presetComponent->onDelete = [this](const int index) { handleMouseClickOnDelete (index); };
        presetComponent->onFavorite = [this](const int index) { handleMouseClickOnFavorite (index); };
        presetComponent->setBounds (x, y, mPresetWidth, mPresetHeight);
        addAndMakeVisible (presetComponent);

        // Delete pointers to prevent leaks
        mPresetsToDelete.add (presetComponent);
    }

    int rowCount = (int) std::ceil (inPresetNames.size() / (float) (PRESETS_PER_ROW));
    int viewportHeight = ((mPresetHeight + mSpaceHeight) * rowCount) + mSpaceHeight;
    setSize (getWidth(), viewportHeight);
}
