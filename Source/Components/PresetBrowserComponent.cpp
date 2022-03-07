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
    mPresetWidth = float (inWidth * (PRESET_WIDTH / PRESET_BROWSER_WIDTH));
    mSpaceWidth = (inWidth - (PRESETS_PER_ROW * mPresetWidth)) / (PRESETS_PER_ROW + 1);

    mPresetHeight = float (inHeight * (ITEM_HEIGHT / PRESET_VIEWPORT_HEIGHT));
    mSpaceHeight = mPresetHeight * ((HALF_SPACE + 1) / ITEM_HEIGHT);

    refreshBrowser();
}

//==============================================================================
void PresetBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { refreshBrowser(); } break;
        case (MessageCode::kPresetFileSaved): { hardRefresh(); } break;
        case (MessageCode::kPresetFileLoaded): { hardRefresh(); } break;
        case (MessageCode::kPresetFileDeleted): { hardRefresh(); } break;
        case (MessageCode::kToggleTagSelector): { refreshBrowser(); } break;
        case (MessageCode::kClickPresetTagger): { refreshBrowser(); } break;
        case (MessageCode::kClickSelectableTag): { refreshBrowser(); } break;
        case (MessageCode::kClickAssignableTag): { refreshBrowser(); } break;
        case (MessageCode::kPresetFileFavorited): { refreshBrowser(); } break;
        case (MessageCode::kPresetFilterTextChanged): { refreshBrowser(); } break;
        case (MessageCode::kToggleFavorites): { refreshBrowser(); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetBrowserComponent::hardRefresh()
{
    mBrowserState.refreshData();
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
        float x = (index % PRESETS_PER_ROW) * (mPresetWidth + mSpaceWidth) + mSpaceWidth;
        float y = (index / PRESETS_PER_ROW) * (mPresetHeight + mSpaceHeight) + mSpaceHeight;

        if (mBrowserState.isTagSelectorOn())
        {
            bool isInAssignableTag = mBrowserState.isInAssignableTag (preset.fileName);
            auto* presetTaggerComponent = new PresetTaggerComponent (preset, isInAssignableTag);
            presetTaggerComponent->setBounds (x, y, mPresetWidth, mPresetHeight);

            presetTaggerComponent->onClick = [this](const int indexValue)
            {
                mBrowserState.handleClickPresetTagger (indexValue);
            };

            addAndMakeVisible (presetTaggerComponent);

            // Delete pointers to prevent leaks
            mPresetTaggersToDelete.add (presetTaggerComponent);
        }
        else
        {
            auto* presetComponent = new PresetComponent (preset);
            presetComponent->setBounds (x, y, mPresetWidth, mPresetHeight);

            presetComponent->onClick = [this](const int indexValue)
            {
                Array<File> allPresetFiles = mBrowserState.getAllPresetFiles();
                mPresetState.handleClickPreset (allPresetFiles[indexValue]);
            };

            presetComponent->onDelete = [this](const int indexValue)
            {
                mBrowserState.handleClickDeletePreset (indexValue);
            };

            presetComponent->onFavorite = [this](const int indexValue)
            {
                mBrowserState.handleClickFavorite (indexValue);
            };

            addAndMakeVisible (presetComponent);

            // Delete pointers to prevent leaks
            mPresetsToDelete.add (presetComponent);
        }
    }

    int rowCount = (int) std::ceil (filteredPresets.size() / (float) (PRESETS_PER_ROW));
    float viewportHeight = ((mPresetHeight + mSpaceHeight) * rowCount) + mSpaceHeight;
    setSize (getWidth(), viewportHeight);
}
