#pragma once

const Colour COLOR_THEME_DARK = Colour (46,47,51);
const Colour COLOR_THEME_LIGHT = Colour (215,216,217);

const Colour COLOR_BLACK = Colour (32,33,36);
const Colour COLOR_DARK = Colour (64, 65, 69);
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

const float PRESET_BROWSER_X = SPACE;
const float PRESET_BROWSER_Y = OUTPUT_KEYBOARD_BG_Y + ITEM_HEIGHT + SPACE;
const float PRESET_BROWSER_WIDTH = KEYBOARD_BG_WIDTH;
const float PRESET_BROWSER_HEIGHT = (2 * KEYBOARD_BG_HEIGHT) + SPACE;

const float PRESET_VIEWPORT_X = PRESET_BROWSER_X + 1;
const float PRESET_VIEWPORT_Y = PRESET_BROWSER_Y + 1;
const float PRESET_VIEWPORT_WIDTH = PRESET_BROWSER_WIDTH + SPACE - 2;
const float PRESET_VIEWPORT_HEIGHT = PRESET_BROWSER_HEIGHT - 2;

const int PRESETS_PER_ROW = 3;
const float PRESET_WIDTH = (PRESET_BROWSER_WIDTH - ((PRESETS_PER_ROW + 1) * HALF_SPACE)) / PRESETS_PER_ROW;
const float PRESET_PAD_X = 8.f;
const float PRESET_PAD_Y = 7.f;

const float TAG_MANAGER_X = SPACE;
const float TAG_SELECTOR_X = TAG_MANAGER_X + ITEM_HEIGHT + HALF_SPACE;
const float TAGS_BG_X = TAG_SELECTOR_X + ITEM_HEIGHT + HALF_SPACE;
const float TAGS_BG_WIDTH = KEYBOARD_BG_WIDTH - SPACE - (2 * ITEM_HEIGHT);

const float STAR_WIDTH = 20.f;
const float STAR_HEIGHT = 20.f;
const float STAR_X = PRESET_PAD_X;
const float STAR_Y = PRESET_PAD_Y - 0.5;

const float TRASH_WIDTH = 16.f;
const float TRASH_HEIGHT = 20.f;
const float TRASH_X = PRESET_WIDTH - TRASH_WIDTH - PRESET_PAD_X;
const float TRASH_Y = PRESET_PAD_Y;

const float CHECK_WIDTH = 22.f;
const float CHECK_HEIGHT = 22.f;
const float CHECK_X = PRESET_PAD_X - 1;
const float CHECK_Y = PRESET_PAD_Y - 1;

const float FOOTER_Y = INPUT_KEYBOARD_BG_Y + KEYBOARD_BG_HEIGHT + SPACE;
const float EDITOR_HEIGHT = FOOTER_Y + ITEM_HEIGHT + SPACE;

const float MODAL_WIDTH = 496.f;
const float MODAL_HEIGHT = 310.f;
const float MODAL_X = EDITOR_WIDTH * 0.5f - MODAL_WIDTH * 0.5f;
const float MODAL_Y = EDITOR_HEIGHT * 0.5f - MODAL_HEIGHT * 0.5f;

const float TAG_INPUT_X = MODAL_X + SPACE;
const float TAG_INPUT_Y = MODAL_Y + SPACE;
const float TAG_INPUT_WIDTH = MODAL_WIDTH - BUTTON_WIDTH - (SPACE * 3);
const float CREATE_TAG_X = TAG_INPUT_X + TAG_INPUT_WIDTH + SPACE;

const float TAG_BROWSER_X = TAG_INPUT_X;
const float TAG_BROWSER_Y = TAG_INPUT_Y + ITEM_HEIGHT + SPACE;
const float TAG_BROWSER_WIDTH = MODAL_WIDTH - DOUBLE_SPACE;
const float TAG_BROWSER_HEIGHT = MODAL_HEIGHT - ITEM_HEIGHT - (SPACE * 3);

const float TAG_VIEWPORT_X = TAG_BROWSER_X + 1;
const float TAG_VIEWPORT_Y = TAG_BROWSER_Y + 1;
const float TAG_VIEWPORT_WIDTH = TAG_BROWSER_WIDTH + SPACE - 2;
const float TAG_VIEWPORT_HEIGHT = TAG_BROWSER_HEIGHT - 2;

const int TAGS_PER_ROW = 2;
const float TAG_WIDTH = (TAG_BROWSER_WIDTH - ((TAGS_PER_ROW + 1) * HALF_SPACE)) / TAGS_PER_ROW;
const float TAG_PAD_X = 6.f;
const float TAG_PAD_Y = 5.f;

const float CANCEL_WIDTH = 80.f;
const float CANCEL_HEIGHT = 24.f;
const float DELETE_WIDTH = CANCEL_WIDTH;
const float DELETE_HEIGHT = CANCEL_HEIGHT;
const float CANCEL_Y = 5.f;
const float DELETE_Y = CANCEL_Y;

const float CANCEL_PRESET_X = (PRESET_WIDTH / 2) - CANCEL_WIDTH - SPACE;
const float DELETE_PRESET_X = (PRESET_WIDTH / 2) + SPACE;
const float CANCEL_TAG_X = (TAG_WIDTH / 2) - CANCEL_WIDTH - HALF_SPACE;
const float DELETE_TAG_X = (TAG_WIDTH / 2) + HALF_SPACE;

const float MENU_ITEM_HEIGHT = 30.f;
const float MENU_ACTION_WIDTH = 220.f;
const float MENU_TOGGLE_WIDTH = 120.f;
const float MENU_ACTION_X = EDITOR_WIDTH * 0.5f + HALF_SPACE;
const float MENU_ACTION_Y_01 = MODAL_Y + SPACE;
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
