#pragma once

#include "JuceHeader.h"

//==============================================================================
// A simple label whose editor is taking the same justification as the label.
struct TextLabel : public Label
{
    using Label::Label;

    TextEditor* createEditorComponent() override
    {
        auto* editor = Label::createEditorComponent();
        editor->setJustification (getJustificationType());
        return editor;
    }
};
