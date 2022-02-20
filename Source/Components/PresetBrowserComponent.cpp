#include "JuceHeader.h"
#include "PresetBrowserComponent.h"

//==============================================================================
PresetBrowserComponent::PresetBrowserComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
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

    refreshBrowser();
}

//==============================================================================
void PresetBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { hardRefresh(); } break;
        case (MessageCode::kPresetFileSaved): { hardRefresh(); } break;
        case (MessageCode::kPresetFileLoaded): { hardRefresh(); } break;
        case (MessageCode::kPresetFileDeleted): { hardRefresh(); } break;
        case (MessageCode::kPresetFileFavorited): { refreshBrowser(); } break;
        case (MessageCode::kPresetFilterTextChanged): { refreshBrowser(); } break;
        case (MessageCode::kToggleFavorites): { refreshBrowser(); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetBrowserComponent::hardRefresh()
{
    mBrowserState.refreshPresetFiles();
    refreshBrowser();
}

void PresetBrowserComponent::refreshBrowser()
{
    mBrowserState.filterPresets();

    if (mGlobalState.isKeyboardView()) { return; }

    removeAllChildren();
    juce::Array<Preset> filteredPresets = mBrowserState.getFilteredPresets();

    for (int index = 0; index < filteredPresets.size(); index++)
    {
        Preset preset = filteredPresets[index];
        int x = (index % PRESETS_PER_ROW) * (mPresetWidth + mSpaceWidth) + mSpaceWidth;
        int y = (index / PRESETS_PER_ROW) * (mPresetHeight + mSpaceHeight) + mSpaceHeight;

        auto* presetComponent = new PresetComponent (preset);
        presetComponent->setBounds (x, y, mPresetWidth, mPresetHeight);

        presetComponent->onClick = [this](const int indexValue)
        {
            Array<File> allPresetFiles = mBrowserState.getAllPresetFiles();
            mPresetState.handleMouseDownOnPreset (allPresetFiles[indexValue]);
        };

        presetComponent->onDelete = [this](const int indexValue)
        {
            mBrowserState.handleMouseDownOnDelete (indexValue);
        };

        addAndMakeVisible (presetComponent);

        // Delete pointers to prevent leaks
        mPresetsToDelete.add (presetComponent);
    }

    int rowCount = (int) std::ceil (filteredPresets.size() / (float) (PRESETS_PER_ROW));
    int viewportHeight = ((mPresetHeight + mSpaceHeight) * rowCount) + mSpaceHeight;
    setSize (getWidth(), viewportHeight);
}
