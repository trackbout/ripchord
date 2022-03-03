#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "DeleteComponent.h"

//==============================================================================
class TagComponent : public Component
{
public:
    //==============================================================================
    TagComponent (String name, String type, bool isSelected, bool isAssignable);
    ~TagComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& event) override;

    //==============================================================================
    std::function<void (const String name)> onClick;
    std::function<void (const String name)> onDelete;

private:
    //==============================================================================
    String mName;
    String mType;

    bool mIsSelected;
    bool mIsAssignable;

    Images mImages;
    Label mTagLabel;
    DeleteComponent mDeleteComponent;

    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TagComponent)
};
