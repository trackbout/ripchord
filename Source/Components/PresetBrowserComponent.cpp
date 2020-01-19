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
        case (MessageCode::kToggleView): { handleToggleView (inMessage); } break;
        case (MessageCode::kToggleFavorites): { handleToggleFavorites (inMessage); } break;
        case (MessageCode::kPresetFilterTextChanged): { handlePresetFilterTextChanged (inMessage); } break;
        case (MessageCode::kPresetsChanged): { handlePresetsChanged (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetBrowserComponent::handleToggleView (const DataMessage* inMessage)
{
    refreshBrowser();
}

void PresetBrowserComponent::handleToggleFavorites (const DataMessage* inMessage)
{
    refreshBrowser();
}

void PresetBrowserComponent::handlePresetFilterTextChanged (const DataMessage* inMessage)
{
    refreshBrowser();
}

void PresetBrowserComponent::handlePresetsChanged (const DataMessage* inMessage)
{
    refreshBrowser();
}

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
    juce::Array<juce::Array<var>> filteredPresets;
    bool isFavoritesOn = mBrowserState.getIsFavoritesOn();
    bool isFilterTextOn = !mBrowserState.getFilterText().isEmpty();

    if (!isFavoritesOn && !isFilterTextOn)
    {
        renderPresetComponents (mBrowserState.getPresets());
    }

    if (isFavoritesOn && !isFilterTextOn)
    {
        for (juce::Array<var>& preset : mBrowserState.getPresets())
        {
            bool isFavorite = preset[2];
            if (isFavorite) { filteredPresets.add (preset); }
        }

        renderPresetComponents (filteredPresets);
    }

    if (!isFavoritesOn && isFilterTextOn)
    {
        String filterText = mBrowserState.getFilterText();

        for (juce::Array<var>& preset : mBrowserState.getPresets())
        {
            String fileName = preset[1];
            if (fileName.containsIgnoreCase (filterText)) { filteredPresets.add (preset); }
        }

        renderPresetComponents (filteredPresets);
    }

    if (isFavoritesOn && isFilterTextOn)
    {
        String filterText = mBrowserState.getFilterText();

        for (juce::Array<var>& preset : mBrowserState.getPresets())
        {
            bool isFavorite = preset[2];
            String fileName = preset[1];
            if (isFavorite && fileName.containsIgnoreCase (filterText))
            {
                filteredPresets.add (preset);
            }
        }

        renderPresetComponents (filteredPresets);
    }
}

void PresetBrowserComponent::renderPresetComponents (juce::Array<juce::Array<var>> inPresets)
{
    for (int index = 0; index < inPresets.size(); index++)
    {
        juce::Array<var> preset = inPresets[index];
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
