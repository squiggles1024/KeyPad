/*
 * KeyFunctions.h
 *
 *  Created on: May 18, 2022
 *      Author: evanl
 */

#ifndef INC_KEYFUNCTIONS_H_
#define INC_KEYFUNCTIONS_H_
#include <stdint.h>

typedef uint8_t KeyScanCode;
typedef uint8_t ModifierKey;
typedef uint8_t MouseClick;
typedef int8_t MouseWheel;

//modifier key masks
extern const ModifierKey KEY_MOD_NOMOD;
extern const ModifierKey KEY_MOD_LCTRL;
extern const ModifierKey KEY_MOD_LSHIFT;
extern const ModifierKey KEY_MOD_LALT;
extern const ModifierKey KEY_MOD_LMETA;
extern const ModifierKey KEY_MOD_RCTRL;
extern const ModifierKey KEY_MOD_RSHIFT;
extern const ModifierKey KEY_MOD_RALT;
extern const ModifierKey KEY_MOD_RMETA;

//mouse button masks
extern const MouseClick MOUSE_CLICK_NONE;
extern const MouseClick MOUSE_CLICK_LEFT;
extern const MouseClick MOUSE_CLICK_RIGHT;
extern const MouseClick MOUSE_CLICK_3;
extern const MouseClick MOUSE_CLICK_4;
extern const MouseClick MOUSE_CLICK_5;

//mouse wheel values
extern const MouseWheel MOUSE_WHEEL_UP;
extern const MouseWheel MOUSE_WHEEL_NO_MOVE;
extern const MouseWheel MOUSE_WHEEL_DOWN;

/**
 * Scan codes - last N slots in the HID report (usually 6).
 *;0 if no key pressed.
 *
 * If more than N keys are pressed, the HID reports
 * KEY_ERR_OVF in all slots to indicate this condition.
 */

extern const KeyScanCode KEY_NONE; // No key pressed
extern const KeyScanCode KEY_ERR_OVF; //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
extern const KeyScanCode KEY_POST_FAIL; //  Keyboard POST Fail
extern const KeyScanCode KEY_ERR_UNDF; //  Keyboard Error Undefined
extern const KeyScanCode KEY_A; // Keyboard a and A
extern const KeyScanCode KEY_B; // Keyboard b and B
extern const KeyScanCode KEY_C; // Keyboard c and C
extern const KeyScanCode KEY_D; // Keyboard d and D
extern const KeyScanCode KEY_E; // Keyboard e and E
extern const KeyScanCode KEY_F; // Keyboard f and F
extern const KeyScanCode KEY_G; // Keyboard g and G
extern const KeyScanCode KEY_H; // Keyboard h and H
extern const KeyScanCode KEY_I; // Keyboard i and I
extern const KeyScanCode KEY_J; // Keyboard j and J
extern const KeyScanCode KEY_K; // Keyboard k and K
extern const KeyScanCode KEY_L; // Keyboard l and L
extern const KeyScanCode KEY_M; // Keyboard m and M
extern const KeyScanCode KEY_N; // Keyboard n and N
extern const KeyScanCode KEY_O; // Keyboard o and O
extern const KeyScanCode KEY_P; // Keyboard p and P
extern const KeyScanCode KEY_Q; // Keyboard q and Q
extern const KeyScanCode KEY_R; // Keyboard r and R
extern const KeyScanCode KEY_S; // Keyboard s and S
extern const KeyScanCode KEY_T; // Keyboard t and T
extern const KeyScanCode KEY_U; // Keyboard u and U
extern const KeyScanCode KEY_V; // Keyboard v and V
extern const KeyScanCode KEY_W; // Keyboard w and W
extern const KeyScanCode KEY_X; // Keyboard x and X
extern const KeyScanCode KEY_Y; // Keyboard y and Y
extern const KeyScanCode KEY_Z; // Keyboard z and Z

extern const KeyScanCode KEY_1; // Keyboard 1 and !
extern const KeyScanCode KEY_2; // Keyboard 2 and @
extern const KeyScanCode KEY_3; // Keyboard 3 and #
extern const KeyScanCode KEY_4; // Keyboard 4 and $
extern const KeyScanCode KEY_5; // Keyboard 5 and %
extern const KeyScanCode KEY_6; // Keyboard 6 and ^
extern const KeyScanCode KEY_7; // Keyboard 7 and &
extern const KeyScanCode KEY_8; // Keyboard 8 and *
extern const KeyScanCode KEY_9; // Keyboard 9 and (
extern const KeyScanCode KEY_0; // Keyboard 0 and )

extern const KeyScanCode KEY_ENTER; // Keyboard Return (ENTER)
extern const KeyScanCode KEY_ESC; // Keyboard ESCAPE
extern const KeyScanCode KEY_BACKSPACE; // Keyboard DELETE (Backspace)
extern const KeyScanCode KEY_TAB; // Keyboard Tab
extern const KeyScanCode KEY_SPACE; // Keyboard Spacebar
extern const KeyScanCode KEY_MINUS; // Keyboard - and _
extern const KeyScanCode KEY_EQUAL; // Keyboard = and +
extern const KeyScanCode KEY_LEFTBRACE; // Keyboard [ and {
extern const KeyScanCode KEY_RIGHTBRACE; // Keyboard ] and }
extern const KeyScanCode KEY_BACKSLASH; // Keyboard \ and |
extern const KeyScanCode KEY_HASHTILDE; // Keyboard Non-US # and ~
extern const KeyScanCode KEY_SEMICOLON; // Keyboard ; and :
extern const KeyScanCode KEY_APOSTROPHE; // Keyboard ' and "
extern const KeyScanCode KEY_GRAVE; // Keyboard ` and ~
extern const KeyScanCode KEY_COMMA; // Keyboard , and <
extern const KeyScanCode KEY_DOT; // Keyboard . and >
extern const KeyScanCode KEY_SLASH; // Keyboard / and ?
extern const KeyScanCode KEY_CAPSLOCK; // Keyboard Caps Lock

extern const KeyScanCode KEY_F1; // Keyboard F1
extern const KeyScanCode KEY_F2; // Keyboard F2
extern const KeyScanCode KEY_F3; // Keyboard F3
extern const KeyScanCode KEY_F4; // Keyboard F4
extern const KeyScanCode KEY_F5; // Keyboard F5
extern const KeyScanCode KEY_F6; // Keyboard F6
extern const KeyScanCode KEY_F7; // Keyboard F7
extern const KeyScanCode KEY_F8; // Keyboard F8
extern const KeyScanCode KEY_F9; // Keyboard F9
extern const KeyScanCode KEY_F10; // Keyboard F10
extern const KeyScanCode KEY_F11; // Keyboard F11
extern const KeyScanCode KEY_F12; // Keyboard F12

extern const KeyScanCode KEY_SYSRQ; // Keyboard Print Screen
extern const KeyScanCode KEY_SCROLLLOCK; // Keyboard Scroll Lock
extern const KeyScanCode KEY_PAUSE; // Keyboard Pause
extern const KeyScanCode KEY_INSERT; // Keyboard Insert
extern const KeyScanCode KEY_HOME; // Keyboard Home
extern const KeyScanCode KEY_PAGEUP; // Keyboard Page Up
extern const KeyScanCode KEY_DELETE; // Keyboard Delete Forward
extern const KeyScanCode KEY_END; // Keyboard End
extern const KeyScanCode KEY_PAGEDOWN; // Keyboard Page Down
extern const KeyScanCode KEY_RIGHT; // Keyboard Right Arrow
extern const KeyScanCode KEY_LEFT; // Keyboard Left Arrow
extern const KeyScanCode KEY_DOWN; // Keyboard Down Arrow
extern const KeyScanCode KEY_UP; // Keyboard Up Arrow

extern const KeyScanCode KEY_NUMLOCK; // Keyboard Num Lock and Clear
extern const KeyScanCode KEY_KPSLASH; // Keypad /
extern const KeyScanCode KEY_KPASTERISK; // Keypad *
extern const KeyScanCode KEY_KPMINUS; // Keypad -
extern const KeyScanCode KEY_KPPLUS; // Keypad +
extern const KeyScanCode KEY_KPENTER; // Keypad ENTER
extern const KeyScanCode KEY_KP1; // Keypad 1 and End
extern const KeyScanCode KEY_KP2; // Keypad 2 and Down Arrow
extern const KeyScanCode KEY_KP3; // Keypad 3 and PageDn
extern const KeyScanCode KEY_KP4; // Keypad 4 and Left Arrow
extern const KeyScanCode KEY_KP5; // Keypad 5
extern const KeyScanCode KEY_KP6; // Keypad 6 and Right Arrow
extern const KeyScanCode KEY_KP7; // Keyp ad 7 and Home
extern const KeyScanCode KEY_KP8; // Keypad 8 and Up Arrow
extern const KeyScanCode KEY_KP9; // Keypad 9 and Page Up
extern const KeyScanCode KEY_KP0; // Keypad 0 and Insert
extern const KeyScanCode KEY_KPDOT; // Keypad . and Delete


#endif /* INC_KEYFUNCTIONS_H_ */
