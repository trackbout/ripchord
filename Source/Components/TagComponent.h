#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"

//==============================================================================
class TagComponent : public Component
{
public:
    //==============================================================================
    TagComponent (String name);
    ~TagComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;
    void mouseDown (const MouseEvent& event) override;

    //==============================================================================
    std::function<void (const int indexValue)> onClick;
    std::function<void (const int indexValue)> onDelete;

private:
    //==============================================================================
    String mName;

    Images mImages;
    Label mPresetLabel;

    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TagComponent)
};
