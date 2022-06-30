/*
 * KeyPadConfig.c
 *
 *  Created on: Jun 24, 2022
 *      Author: evanl
 */

#include "KeyFunctions.h"
#include "KeyPadConfig.h"

KeyFunction_t ButtonFunctionsDefault[NUMBER_OF_BUTTONS] = {

        //1 Up
        {.KeyScanCode = KEY_1,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //1 Right
        {.KeyScanCode = KEY_1,
        .ModifierKey = KEY_MOD_RSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //1 Down
        {.KeyScanCode = KEY_1,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //1
        {.KeyScanCode = KEY_1,
        .ModifierKey = KEY_MOD_LALT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //1 Left
        {.KeyScanCode = KEY_1,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Z
        {.KeyScanCode = KEY_Z,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //A
        {.KeyScanCode = KEY_A,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Q
        {.KeyScanCode = KEY_Q,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //` Up
        {.KeyScanCode = KEY_GRAVE,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //` Right
        {.KeyScanCode = KEY_GRAVE,
        .ModifierKey = KEY_MOD_RSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //` Down
        {.KeyScanCode = KEY_GRAVE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //` Left
        {.KeyScanCode = KEY_GRAVE,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //`
        {.KeyScanCode = KEY_GRAVE,
        .ModifierKey = KEY_MOD_LALT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Tab
        {.KeyScanCode = KEY_TAB,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Shift
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Ctrl
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_LCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //5
        {.KeyScanCode = KEY_5,
        .ModifierKey = KEY_MOD_LALT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //5 Left
        {.KeyScanCode = KEY_5,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //F5
        {.KeyScanCode = KEY_F5,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //F4
        {.KeyScanCode = KEY_F4,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //F3
        {.KeyScanCode = KEY_F3,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //F2
        {.KeyScanCode = KEY_F2,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //F1
        {.KeyScanCode = KEY_F1,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Esc
        {.KeyScanCode = KEY_ESC,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //5 Down
        {.KeyScanCode = KEY_5,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //5 Right
        {.KeyScanCode = KEY_5,
        .ModifierKey = KEY_MOD_RSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //5 Up
        {.KeyScanCode = KEY_5,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //None
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //None
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //None
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //None
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //None
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //X
        {.KeyScanCode = KEY_X,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //S
        {.KeyScanCode = KEY_S,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //W
        {.KeyScanCode = KEY_W,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //2
        {.KeyScanCode = KEY_2,
        .ModifierKey = KEY_MOD_LALT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //2 Left
        {.KeyScanCode = KEY_2,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //2 Down
        {.KeyScanCode = KEY_2,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //2 Right
        {.KeyScanCode = KEY_2,
        .ModifierKey = KEY_MOD_RSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //2 Up
        {.KeyScanCode = KEY_2,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //C
        {.KeyScanCode = KEY_C,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //D
        {.KeyScanCode = KEY_D,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //E
        {.KeyScanCode = KEY_E,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //3
        {.KeyScanCode = KEY_3,
        .ModifierKey = KEY_MOD_LALT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //3 Left
        {.KeyScanCode = KEY_3,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //3 Down
        {.KeyScanCode = KEY_3,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //3 Right
        {.KeyScanCode = KEY_3,
        .ModifierKey = KEY_MOD_RSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //3 Up
        {.KeyScanCode = KEY_3,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Stick
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_3,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //V
        {.KeyScanCode = KEY_V,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //B
        {.KeyScanCode = KEY_B,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //F
        {.KeyScanCode = KEY_F,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Thumb3
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_RIGHT,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Thumb2
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_LEFT,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Thumb1
        {.KeyScanCode = KEY_SPACE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Space
        {.KeyScanCode = KEY_SPACE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //R
        {.KeyScanCode = KEY_R,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //G
        {.KeyScanCode = KEY_G,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //T
        {.KeyScanCode = KEY_T,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

		//4
        {.KeyScanCode = KEY_4,
        .ModifierKey = KEY_MOD_LALT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

		//4 Left
        {.KeyScanCode = KEY_4,
        .ModifierKey = KEY_MOD_LSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

		//4 Down
        {.KeyScanCode = KEY_4,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

		//4 Right
        {.KeyScanCode = KEY_4,
        .ModifierKey = KEY_MOD_RSHIFT,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //4 Up
        {.KeyScanCode = KEY_4,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},


};

KeyFunction_t TouchButtonFunctionsDefault[NUMBER_OF_TOUCH_BUTTONS] = {
        //1 (Character)
        {.KeyScanCode = KEY_F1,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //2 (Bags)
        {.KeyScanCode = KEY_F2,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //3 (Collections)
        {.KeyScanCode = KEY_F3,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //4 (LFG)
        {.KeyScanCode = KEY_F4,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //5 (Spellbook)
        {.KeyScanCode = KEY_F5,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //6 (Talents)
        {.KeyScanCode = KEY_F6,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //7 (Social)
        {.KeyScanCode = KEY_F7,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //8 (Guild)
        {.KeyScanCode = KEY_F8,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //9 (Map)
        {.KeyScanCode = KEY_F9,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //10 (Achievements)
        {.KeyScanCode = KEY_F10,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //11 (Adventure Guide)
        {.KeyScanCode = KEY_F11,
        .ModifierKey = KEY_MOD_RCTRL,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //12 (Menu)
        {.KeyScanCode = KEY_ESC,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE}

};

KeyFunction_t JoystickFunctionsDefault[8] = {
        //Up
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_UP},

        //UpRight
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Right
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_4,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //DownRight
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Down
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_DOWN},

        //DownLeft
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //Left
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_5,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE},

        //UpLeft
        {.KeyScanCode = KEY_NONE,
        .ModifierKey = KEY_MOD_NOMOD,
        .MouseClick = MOUSE_CLICK_NONE,
        .MouseWheel = MOUSE_WHEEL_NO_MOVE}
};
