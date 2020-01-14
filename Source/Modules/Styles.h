#pragma once

#include "Constants.h"

//==============================================================================
namespace Styles
{
    //==============================================================================
    static inline Rectangle<int> getRelativeBounds (Rectangle<int> inBaselineBounds,
                                                    int inX, int inY, int inWidth, int inHeight)
    {
        Rectangle<float> proportions {
            inX / EDITOR_WIDTH,
            inY / EDITOR_HEIGHT,
            inWidth / EDITOR_WIDTH,
            inHeight / EDITOR_HEIGHT
        };

        return inBaselineBounds.getProportion (proportions);
    }

    //==============================================================================
    static inline bool isBlackKey (const int inNoteNumber)
    {
        div_t keyDiv = div (inNoteNumber, 12);
        int keyInOctave = keyDiv.rem;

        if ((keyInOctave == 1) ||
            (keyInOctave == 3) ||
            (keyInOctave == 6) ||
            (keyInOctave == 8) ||
            (keyInOctave == 10))
        {
            return true;
        }

        return false;
    }
}
