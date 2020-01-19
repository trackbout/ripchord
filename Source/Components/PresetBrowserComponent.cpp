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

    refreshBrowser();
}

//==============================================================================
void PresetBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { refreshBrowser(); } break;
        case (MessageCode::kToggleFavorites): { refreshBrowser(); } break;
        case (MessageCode::kPresetFilterTextChanged): { refreshBrowser(); } break;
        case (MessageCode::kPresetsChanged): { refreshBrowser(); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetBrowserComponent::handleMouseClickOnDelete (const int inIndexValue)
{
    mBrowserState.handleMouseClickOnDelete (inIndexValue);
}

void PresetBrowserComponent::handleMouseClickOnFavorite (const int inIndexValue)
{
    mBrowserState.handleMouseClickOnFavorite (inIndexValue);
}

void PresetBrowserComponent::refreshBrowser()
{
    if (mGlobalState.isKeyboardView()) { return; }

    removeAllChildren();
    juce::Array<Preset> filteredPresets;
    bool isFavoritesOn = mBrowserState.getIsFavoritesOn();
    bool isFilterTextOn = !mBrowserState.getFilterText().isEmpty();

    if (!isFavoritesOn && !isFilterTextOn)
    {
        renderPresetComponents (mBrowserState.getPresets());
    }

    if (isFavoritesOn && !isFilterTextOn)
    {
        for (Preset& preset : mBrowserState.getPresets())
        {
            if (preset.isFavorite) { filteredPresets.add (preset); }
        }

        renderPresetComponents (filteredPresets);
    }

    if (!isFavoritesOn && isFilterTextOn)
    {
        String filterText = mBrowserState.getFilterText();

        for (Preset& preset : mBrowserState.getPresets())
        {
            if (preset.fileName.containsIgnoreCase (filterText)) { filteredPresets.add (preset); }
        }

        renderPresetComponents (filteredPresets);
    }

    if (isFavoritesOn && isFilterTextOn)
    {
        String filterText = mBrowserState.getFilterText();

        for (Preset& preset : mBrowserState.getPresets())
        {
            if (preset.isFavorite && preset.fileName.containsIgnoreCase (filterText))
            {
                filteredPresets.add (preset);
            }
        }

        renderPresetComponents (filteredPresets);
    }
}

void PresetBrowserComponent::renderPresetComponents (juce::Array<Preset> inPresets)
{
    for (int index = 0; index < inPresets.size(); index++)
    {
        Preset preset = inPresets[index];
        int x = (index % PRESETS_PER_ROW) * (mPresetWidth + mSpaceWidth) + mSpaceWidth;
        int y = (index / PRESETS_PER_ROW) * (mPresetHeight + mSpaceHeight) + mSpaceHeight;

        auto* presetComponent = new PresetComponent (preset);
        presetComponent->onDelete = [this](const int indexValue) { handleMouseClickOnDelete (indexValue); };
        presetComponent->onFavorite = [this](const int indexValue) { handleMouseClickOnFavorite (indexValue); };
        presetComponent->setBounds (x, y, mPresetWidth, mPresetHeight);
        addAndMakeVisible (presetComponent);

        // Delete pointers to prevent leaks
        mPresetsToDelete.add (presetComponent);
    }

    int rowCount = (int) std::ceil (inPresets.size() / (float) (PRESETS_PER_ROW));
    int viewportHeight = ((mPresetHeight + mSpaceHeight) * rowCount) + mSpaceHeight;
    setSize (getWidth(), viewportHeight);
}
