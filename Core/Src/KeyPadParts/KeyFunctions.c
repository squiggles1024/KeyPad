/*
 * KeyFunctions.c
 *
 *  Created on: May 18, 2022
 *      Author: evanl
 */

#include "KeyFunctions.h"

//modifier key masks
const ModifierKey KEY_MOD_NOMOD  = 0x00;
const ModifierKey KEY_MOD_LCTRL  = 0x01;
const ModifierKey KEY_MOD_LSHIFT = 0x02;
const ModifierKey KEY_MOD_LALT   = 0x04;
const ModifierKey KEY_MOD_LMETA  = 0x08;
const ModifierKey KEY_MOD_RCTRL  = 0x10;
const ModifierKey KEY_MOD_RSHIFT = 0x20;
const ModifierKey KEY_MOD_RALT   = 0x40;
const ModifierKey KEY_MOD_RMETA  = 0x80;

//mouse button masks
const MouseClick MOUSE_CLICK_NONE  = 0x00;
const MouseClick MOUSE_CLICK_LEFT  = 0x01;
const MouseClick MOUSE_CLICK_RIGHT = 0x02;
const MouseClick MOUSE_CLICK_3     = 0x04;
const MouseClick MOUSE_CLICK_4     = 0x08;
const MouseClick MOUSE_CLICK_5     = 0x10;

//mouse wheel values
const MouseWheel MOUSE_WHEEL_UP = 0x01;
const MouseWheel MOUSE_WHEEL_NO_MOVE = 0x00;
const MouseWheel MOUSE_WHEEL_DOWN = -0x01;

const KeyScanCode KEY_NONE = 0x00; // No key pressed
const KeyScanCode KEY_ERR_OVF = 0x01; //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
const KeyScanCode KEY_POST_FAIL = 0x02; //  Keyboard POST Fail
const KeyScanCode KEY_ERR_UNDF = 0x03; //  Keyboard Error Undefined
const KeyScanCode KEY_A = 0x04; // Keyboard a and A
const KeyScanCode KEY_B = 0x05; // Keyboard b and B
const KeyScanCode KEY_C = 0x06; // Keyboard c and C
const KeyScanCode KEY_D = 0x07; // Keyboard d and D
const KeyScanCode KEY_E = 0x08; // Keyboard e and E
const KeyScanCode KEY_F = 0x09; // Keyboard f and F
const KeyScanCode KEY_G = 0x0a; // Keyboard g and G
const KeyScanCode KEY_H = 0x0b; // Keyboard h and H
const KeyScanCode KEY_I = 0x0c; // Keyboard i and I
const KeyScanCode KEY_J = 0x0d; // Keyboard j and J
const KeyScanCode KEY_K = 0x0e; // Keyboard k and K
const KeyScanCode KEY_L = 0x0f; // Keyboard l and L
const KeyScanCode KEY_M = 0x10; // Keyboard m and M
const KeyScanCode KEY_N = 0x11; // Keyboard n and N
const KeyScanCode KEY_O = 0x12; // Keyboard o and O
const KeyScanCode KEY_P = 0x13; // Keyboard p and P
const KeyScanCode KEY_Q = 0x14; // Keyboard q and Q
const KeyScanCode KEY_R = 0x15; // Keyboard r and R
const KeyScanCode KEY_S = 0x16; // Keyboard s and S
const KeyScanCode KEY_T = 0x17; // Keyboard t and T
const KeyScanCode KEY_U = 0x18; // Keyboard u and U
const KeyScanCode KEY_V = 0x19; // Keyboard v and V
const KeyScanCode KEY_W = 0x1a; // Keyboard w and W
const KeyScanCode KEY_X = 0x1b; // Keyboard x and X
const KeyScanCode KEY_Y = 0x1c; // Keyboard y and Y
const KeyScanCode KEY_Z = 0x1d; // Keyboard z and Z

const KeyScanCode KEY_1 = 0x1e; // Keyboard 1 and !
const KeyScanCode KEY_2 = 0x1f; // Keyboard 2 and @
const KeyScanCode KEY_3 = 0x20; // Keyboard 3 and #
const KeyScanCode KEY_4 = 0x21; // Keyboard 4 and $
const KeyScanCode KEY_5 = 0x22; // Keyboard 5 and %
const KeyScanCode KEY_6 = 0x23; // Keyboard 6 and ^
const KeyScanCode KEY_7 = 0x24; // Keyboard 7 and &
const KeyScanCode KEY_8 = 0x25; // Keyboard 8 and *
const KeyScanCode KEY_9 = 0x26; // Keyboard 9 and (
const KeyScanCode KEY_0 = 0x27; // Keyboard 0 and )

const KeyScanCode KEY_ENTER = 0x28; // Keyboard Return (ENTER)
const KeyScanCode KEY_ESC = 0x29; // Keyboard ESCAPE
const KeyScanCode KEY_BACKSPACE = 0x2a; // Keyboard DELETE (Backspace)
const KeyScanCode KEY_TAB = 0x2b; // Keyboard Tab
const KeyScanCode KEY_SPACE = 0x2c; // Keyboard Spacebar
const KeyScanCode KEY_MINUS = 0x2d; // Keyboard - and _
const KeyScanCode KEY_EQUAL = 0x2e; // Keyboard = and +
const KeyScanCode KEY_LEFTBRACE = 0x2f; // Keyboard [ and {
const KeyScanCode KEY_RIGHTBRACE = 0x30; // Keyboard ] and }
const KeyScanCode KEY_BACKSLASH = 0x31; // Keyboard \ and |
const KeyScanCode KEY_HASHTILDE = 0x32; // Keyboard Non-US # and ~
const KeyScanCode KEY_SEMICOLON = 0x33; // Keyboard ; and :
const KeyScanCode KEY_APOSTROPHE = 0x34; // Keyboard ' and "
const KeyScanCode KEY_GRAVE = 0x35; // Keyboard ` and ~
const KeyScanCode KEY_COMMA = 0x36; // Keyboard , and <
const KeyScanCode KEY_DOT = 0x37; // Keyboard . and >
const KeyScanCode KEY_SLASH = 0x38; // Keyboard / and ?
const KeyScanCode KEY_CAPSLOCK = 0x39; // Keyboard Caps Lock

const KeyScanCode KEY_F1 = 0x3a; // Keyboard F1
const KeyScanCode KEY_F2 = 0x3b; // Keyboard F2
const KeyScanCode KEY_F3 = 0x3c; // Keyboard F3
const KeyScanCode KEY_F4 = 0x3d; // Keyboard F4
const KeyScanCode KEY_F5 = 0x3e; // Keyboard F5
const KeyScanCode KEY_F6 = 0x3f; // Keyboard F6
const KeyScanCode KEY_F7 = 0x40; // Keyboard F7
const KeyScanCode KEY_F8 = 0x41; // Keyboard F8
const KeyScanCode KEY_F9 = 0x42; // Keyboard F9
const KeyScanCode KEY_F10 = 0x43; // Keyboard F10
const KeyScanCode KEY_F11 = 0x44; // Keyboard F11
const KeyScanCode KEY_F12 = 0x45; // Keyboard F12

const KeyScanCode KEY_SYSRQ = 0x46; // Keyboard Print Screen
const KeyScanCode KEY_SCROLLLOCK = 0x47; // Keyboard Scroll Lock
const KeyScanCode KEY_PAUSE = 0x48; // Keyboard Pause
const KeyScanCode KEY_INSERT = 0x49; // Keyboard Insert
const KeyScanCode KEY_HOME = 0x4a; // Keyboard Home
const KeyScanCode KEY_PAGEUP = 0x4b; // Keyboard Page Up
const KeyScanCode KEY_DELETE = 0x4c; // Keyboard Delete Forward
const KeyScanCode KEY_END = 0x4d; // Keyboard End
const KeyScanCode KEY_PAGEDOWN = 0x4e; // Keyboard Page Down
const KeyScanCode KEY_RIGHT = 0x4f; // Keyboard Right Arrow
const KeyScanCode KEY_LEFT = 0x50; // Keyboard Left Arrow
const KeyScanCode KEY_DOWN = 0x51; // Keyboard Down Arrow
const KeyScanCode KEY_UP = 0x52; // Keyboard Up Arrow

const KeyScanCode KEY_NUMLOCK = 0x53; // Keyboard Num Lock and Clear
const KeyScanCode KEY_KPSLASH = 0x54; // Keypad /
const KeyScanCode KEY_KPASTERISK = 0x55; // Keypad *
const KeyScanCode KEY_KPMINUS = 0x56; // Keypad -
const KeyScanCode KEY_KPPLUS = 0x57; // Keypad +
const KeyScanCode KEY_KPENTER = 0x58; // Keypad ENTER
const KeyScanCode KEY_KP1 = 0x59; // Keypad 1 and End
const KeyScanCode KEY_KP2 = 0x5a; // Keypad 2 and Down Arrow
const KeyScanCode KEY_KP3 = 0x5b; // Keypad 3 and PageDn
const KeyScanCode KEY_KP4 = 0x5c; // Keypad 4 and Left Arrow
const KeyScanCode KEY_KP5 = 0x5d; // Keypad 5
const KeyScanCode KEY_KP6 = 0x5e; // Keypad 6 and Right Arrow
const KeyScanCode KEY_KP7 = 0x5f; // Keyp ad 7 and Home
const KeyScanCode KEY_KP8 = 0x60; // Keypad 8 and Up Arrow
const KeyScanCode KEY_KP9 = 0x61; // Keypad 9 and Page Up
const KeyScanCode KEY_KP0 = 0x62; // Keypad 0 and Insert
const KeyScanCode KEY_KPDOT = 0x63; // Keypad . and Delete
