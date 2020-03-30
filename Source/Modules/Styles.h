#pragma once

const Colour COLOR_BLUE_DARK = Colour (0,117,168);
const Colour COLOR_BLUE = Colour (0,168,232);
const Colour COLOR_GREEN = Colour (87,186,123);
const Colour COLOR_PURPLE = Colour (121,87,186);
const Colour COLOR_RED = Colour (239,71,111);
const Colour COLOR_WHITE = Colour (255,255,255);
const Colour COLOR_BLACK = Colour (0,0,0);
const Colour COLOR_GREY_DARK = Colour (60,60,60);
const Colour COLOR_GREY_MEDIUM = Colour (140,140,140);
const Colour COLOR_GREY_LIGHT = Colour (192,192,192);
const Colour COLOR_GREY_LIGHTER = Colour (220,220,220);
const Colour COLOR_GREY_LIGHTEST = Colour (235,235,235);
const Colour COLOR_TRANSPARENT = COLOR_WHITE.withAlpha (0.0f);
const Colour COLOR_OVERLAY = COLOR_BLACK.withAlpha (0.7f);

const float EDITOR_WIDTH = 1000.f;
const float SPACE = 20.f;
const float DOUBLE_SPACE = SPACE * 2;
const float HALF_SPACE = SPACE / 2;
const float HEADER_Y = SPACE;

const float ITEM_HEIGHT = 34.f;
const float BUTTON_WIDTH = 120.f;
const float CORNER_SIZE_RATIO = 0.15f;
const float TEXT_INPUT_FONT_HEIGHT_RATIO = 0.6f;

const float SLIDER_Y = 1.f;
const float SLIDER_SIZE = 72.f;
const float SLIDER_X_OFFSET = 19.f;

const float KEYBOARD_BG_HEIGHT = 120.f;
const float KEYBOARD_BG_WIDTH = EDITOR_WIDTH - DOUBLE_SPACE;
const float OUTPUT_KEYBOARD_BG_Y = ITEM_HEIGHT + DOUBLE_SPACE;
const float INPUT_KEYBOARD_BG_Y = OUTPUT_KEYBOARD_BG_Y + KEYBOARD_BG_HEIGHT + DOUBLE_SPACE + ITEM_HEIGHT;

const float CONTROLS_HEIGHT = DOUBLE_SPACE + ITEM_HEIGHT;
const float CONTROLS_WIDTH = KEYBOARD_BG_WIDTH;
const float CONTROLS_Y = OUTPUT_KEYBOARD_BG_Y + KEYBOARD_BG_HEIGHT;
const float CONTROLS_OUTER_SPACE = SPACE * 6.f;

const float VELOCITY_DIRECTION_X = CONTROLS_OUTER_SPACE;
const float VELOCITY_DEPTH_X = VELOCITY_DIRECTION_X + ITEM_HEIGHT + SPACE;
const float VELOCITY_VARIANCE_X = VELOCITY_DEPTH_X + ITEM_HEIGHT + SPACE + 9.f;

const float TRANSPOSE_BUTTON_X = (KEYBOARD_BG_WIDTH * 0.5f) - (ITEM_HEIGHT * 0.5f);
const float SHIFT_LEFT_BUTTON_X = TRANSPOSE_BUTTON_X - ITEM_HEIGHT - SPACE;
const float SHIFT_RIGHT_BUTTON_X = TRANSPOSE_BUTTON_X + ITEM_HEIGHT + SPACE;

const float SAVE_BUTTON_X = TRANSPOSE_BUTTON_X;
const float EDIT_LEFT_BUTTON_X = SHIFT_LEFT_BUTTON_X;
const float EDIT_RIGHT_BUTTON_X = SHIFT_RIGHT_BUTTON_X;
const float ALL_WHITE_BUTTON_X = EDIT_LEFT_BUTTON_X - ITEM_HEIGHT - SPACE;
const float ALL_BLACK_BUTTON_X = EDIT_RIGHT_BUTTON_X + ITEM_HEIGHT + SPACE;

const float DELAY_DIRECTION_X = KEYBOARD_BG_WIDTH - ITEM_HEIGHT - CONTROLS_OUTER_SPACE;
const float DELAY_DEPTH_X = DELAY_DIRECTION_X - ITEM_HEIGHT - SPACE;
const float DELAY_VARIANCE_X = DELAY_DEPTH_X - ITEM_HEIGHT - SPACE - 9.f;

const float KEYBOARD_LABEL_HEIGHT = 18.f;
const float KEYBOARD_LABEL_WIDTH = 200.f;
const float KEYBOARD_LABEL_X = SPACE + HALF_SPACE - 3;
const float OUTPUT_LABEL_Y = OUTPUT_KEYBOARD_BG_Y + HALF_SPACE;
const float INPUT_LABEL_Y = INPUT_KEYBOARD_BG_Y + HALF_SPACE;

const float KEYBOARD_WIDTH = 936.f;
const float KEYBOARD_HEIGHT = KEYBOARD_BG_HEIGHT - KEYBOARD_LABEL_HEIGHT - (3 * HALF_SPACE);
const float KEYBOARD_X = EDITOR_WIDTH * 0.5f - KEYBOARD_WIDTH * 0.5f;
const float OUTPUT_KEYBOARD_Y = OUTPUT_KEYBOARD_BG_Y + KEYBOARD_LABEL_HEIGHT + SPACE;
const float INPUT_KEYBOARD_Y = INPUT_KEYBOARD_BG_Y + KEYBOARD_LABEL_HEIGHT + SPACE;

const float THROUGH_X = EDITOR_WIDTH * 0.5f - ITEM_HEIGHT * 0.5f;
const float THROUGH_Y = OUTPUT_KEYBOARD_BG_Y + KEYBOARD_BG_HEIGHT + SPACE;

const float ARROW_WIDTH = 22.f;
const float TEXT_INPUT_WIDTH = KEYBOARD_BG_WIDTH - (4 * BUTTON_WIDTH);
const float TEXT_INPUT_X = EDITOR_WIDTH * 0.5f - TEXT_INPUT_WIDTH * 0.5f;
const float LEFT_BUTTON_X = SPACE;
const float RIGHT_BUTTON_X = SPACE + KEYBOARD_BG_WIDTH - BUTTON_WIDTH;
const float MENU_X = SPACE + KEYBOARD_BG_WIDTH - ITEM_HEIGHT;

const float PRESET_VIEWPORT_Y = OUTPUT_KEYBOARD_BG_Y + ITEM_HEIGHT + SPACE;
const float PRESET_VIEWPORT_HEIGHT = (2 * KEYBOARD_BG_HEIGHT) + SPACE;
const float PRESET_VIEWPORT_WIDTH = KEYBOARD_BG_WIDTH + SPACE;
const float PRESET_LIST_HEIGHT = PRESET_VIEWPORT_HEIGHT;
const float PRESET_LIST_WIDTH = KEYBOARD_BG_WIDTH;

const int PRESETS_PER_ROW = 3;
const float PRESET_WIDTH = (PRESET_LIST_WIDTH - ((PRESETS_PER_ROW + 1) * HALF_SPACE)) / PRESETS_PER_ROW;

const float STAR_WIDTH = 21.f;
const float STAR_HEIGHT = 20.f;
const float TRASH_WIDTH = 16.f;
const float TRASH_HEIGHT = 20.f;
const float STAR_X = 8.f;
const float STAR_Y = 6.f;
const float TRASH_X = PRESET_WIDTH - TRASH_WIDTH - STAR_X;
const float TRASH_Y = 7.f;

const float CANCEL_WIDTH = 120.f;
const float CANCEL_HEIGHT = 24.f;
const float DELETE_WIDTH = CANCEL_WIDTH;
const float DELETE_HEIGHT = CANCEL_HEIGHT;
const float CANCEL_X = 28.f;
const float CANCEL_Y = 5.f;
const float DELETE_X = PRESET_WIDTH - DELETE_WIDTH - CANCEL_X;
const float DELETE_Y = CANCEL_Y;

const float FOOTER_Y = INPUT_KEYBOARD_BG_Y + KEYBOARD_BG_HEIGHT + SPACE;
const float EDITOR_HEIGHT = FOOTER_Y + ITEM_HEIGHT + SPACE;

const int ACTIONS_MENU_BUTTON_COUNT = 5;
const float ACTIONS_MENU_BUTTON_HEIGHT = 50.f;
const float ACTIONS_MENU_BUTTON_WIDTH = 300.f;
const float ACTIONS_MENU_WIDTH = ACTIONS_MENU_BUTTON_WIDTH;
const float ACTIONS_MENU_HEIGHT = ACTIONS_MENU_BUTTON_HEIGHT * ACTIONS_MENU_BUTTON_COUNT;
const float ACTIONS_MENU_X = EDITOR_WIDTH * 0.5f - ACTIONS_MENU_WIDTH * 0.5f;
const float ACTIONS_MENU_Y = EDITOR_HEIGHT * 0.5f - ACTIONS_MENU_HEIGHT * 0.5f;

const int RIGHT_CLICK_ITEM_COUNT = 3;
const float RIGHT_CLICK_ITEM_HEIGHT = 24.f;
const float RIGHT_CLICK_ITEM_WIDTH = 80.f;
const float RIGHT_CLICK_MENU_HEIGHT = RIGHT_CLICK_ITEM_HEIGHT * RIGHT_CLICK_ITEM_COUNT;
const float RIGHT_CLICK_MENU_WIDTH = RIGHT_CLICK_ITEM_WIDTH;
const float RIGHT_CLICK_MENU_Y = EDITOR_HEIGHT - 200;
const float RIGHT_CLICK_MENU_X = 200;

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
