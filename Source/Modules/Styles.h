#pragma once

const Colour COLOR_THEME_DARK = Colour (46,47,51);
const Colour COLOR_THEME_LIGHT = Colour (215,216,217);

const Colour COLOR_BLACK = Colour (32,33,36);
const Colour COLOR_GREY = Colour (128,132,138);
const Colour COLOR_WHITE = Colour (255,255,255);

const Colour COLOR_RED = Colour (212,68,85);
const Colour COLOR_BLUE = Colour (20,151,202);
const Colour COLOR_GREEN = Colour (87,186,123);
const Colour COLOR_PURPLE = Colour (121,87,186);
const Colour COLOR_BLUE_DARK = Colour (12,114,153);

const Colour COLOR_BORDER = Colour (69,72,76);
const Colour COLOR_OVERLAY = Colour (0,0,0).withAlpha (0.8f);
const Colour COLOR_TRANSPARENT = Colour (0,0,0).withAlpha (0.0f);

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
const float CONTROLS_OUTER_SPACE = SPACE * 7.f;

const float RECORD_BUTTON_X = 0;

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

const float RECORDED_BUTTON_X = CONTROLS_WIDTH - ITEM_HEIGHT;

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
const float POWER_BUTTON_X = SPACE + KEYBOARD_BG_WIDTH - ITEM_HEIGHT;
const float MENU_BUTTON_X = POWER_BUTTON_X - ITEM_HEIGHT - HALF_SPACE;
const float FAV_BUTTON_X = MENU_BUTTON_X - ITEM_HEIGHT - HALF_SPACE;

const float PRESET_VIEWPORT_Y = OUTPUT_KEYBOARD_BG_Y + ITEM_HEIGHT + SPACE;
const float PRESET_VIEWPORT_HEIGHT = (2 * KEYBOARD_BG_HEIGHT) + SPACE;
const float PRESET_VIEWPORT_WIDTH = KEYBOARD_BG_WIDTH + SPACE;
const float NEW_TAG_X = SPACE;
const float ACTIVE_TAGS_X = NEW_TAG_X + ITEM_HEIGHT + HALF_SPACE;
const float TAG_BG_X = ACTIVE_TAGS_X + ITEM_HEIGHT + HALF_SPACE;
const float TAG_BG_WIDTH = KEYBOARD_BG_WIDTH - SPACE - (2 * ITEM_HEIGHT);
const float PRESET_LIST_HEIGHT = PRESET_VIEWPORT_HEIGHT;
const float PRESET_LIST_WIDTH = KEYBOARD_BG_WIDTH;

const int PRESETS_PER_ROW = 3;
const float PRESET_WIDTH = (PRESET_LIST_WIDTH - ((PRESETS_PER_ROW + 1) * HALF_SPACE)) / PRESETS_PER_ROW;

const float PRESET_PAD_X = 8.f;
const float PRESET_PAD_Y = 7.f;

const float GEAR_WIDTH = 20.f;
const float GEAR_HEIGHT = 20.f;
const float TRASH_WIDTH = 16.f;
const float TRASH_HEIGHT = 20.f;
const float GEAR_X = PRESET_PAD_X;
const float GEAR_Y = PRESET_PAD_Y;
const float TRASH_X = PRESET_WIDTH - TRASH_WIDTH - PRESET_PAD_X;
const float TRASH_Y = PRESET_PAD_Y;

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

const float MENU_WIDTH = 496.f;
const float MENU_HEIGHT = 310.f;
const float MENU_ITEM_HEIGHT = 30.f;
const float MENU_ACTION_WIDTH = 220.f;
const float MENU_TOGGLE_WIDTH = 120.f;
const float MENU_X = EDITOR_WIDTH * 0.5f - MENU_WIDTH * 0.5f;
const float MENU_Y = EDITOR_HEIGHT * 0.5f - MENU_HEIGHT * 0.5f;
const float MENU_ACTION_X = EDITOR_WIDTH * 0.5f + HALF_SPACE;
const float MENU_ACTION_Y_01 = MENU_Y + SPACE;
const float MENU_ACTION_Y_02 = MENU_ACTION_Y_01 + MENU_ITEM_HEIGHT + HALF_SPACE;
const float MENU_ACTION_Y_03 = MENU_ACTION_Y_02 + MENU_ITEM_HEIGHT + HALF_SPACE;
const float MENU_ACTION_Y_04 = MENU_ACTION_Y_03 + MENU_ITEM_HEIGHT + HALF_SPACE;
const float MENU_ACTION_Y_05 = MENU_ACTION_Y_04 + MENU_ITEM_HEIGHT + HALF_SPACE;
const float MENU_ACTION_Y_06 = MENU_ACTION_Y_05 + MENU_ITEM_HEIGHT + HALF_SPACE;
const float MENU_ACTION_Y_07 = MENU_ACTION_Y_06 + MENU_ITEM_HEIGHT + HALF_SPACE;

const float RIGHT_CLICK_ITEM_HEIGHT = 24.f;
const float RIGHT_CLICK_ITEM_WIDTH = 80.f;
const float RIGHT_CLICK_MENU_HEIGHT = 102.f;
const float RIGHT_CLICK_MENU_WIDTH = 100.f;

//==============================================================================
namespace Styles
{
    //==============================================================================
    static inline Rectangle<int> getRelativeBounds (Rectangle<int> inBaselineBounds, int inX, int inY, int inWidth, int inHeight)
    {
        Rectangle<float> proportions { inX / EDITOR_WIDTH, inY / EDITOR_HEIGHT, inWidth / EDITOR_WIDTH, inHeight / EDITOR_HEIGHT };
        return inBaselineBounds.getProportion (proportions);
    }
}
