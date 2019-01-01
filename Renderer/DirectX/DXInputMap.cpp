#include "DXInputMap.h"

#include <General/Input.h>

#include <windows.h>

DXInputMap::DXInputMap()
{
	//Special characters
	m_keyMap[VK_OEM_3] = Input::KEY_TILDE;
	m_keyMap[VK_OEM_MINUS] = Input::KEY_HYPHEN;
	m_keyMap[VK_OEM_PLUS] = Input::KEY_EQUAL;
	m_keyMap[VK_BACK] = Input::KEY_BACKSPACE;
	m_keyMap[VK_OEM_4] = Input::KEY_OPEN_SQUARE_BRACKETS;
	m_keyMap[VK_OEM_6] = Input::KEY_CLOSE_SQUARE_BRACKETS;
	m_keyMap[VK_OEM_5] = Input::KEY_BACKSLASH;
	m_keyMap[VK_OEM_2] = Input::KEY_FORWARDSLASH;
	m_keyMap[VK_OEM_1] = Input::KEY_SEMICOLON;
	m_keyMap[VK_OEM_7] = Input::KEY_APOSTROPHE;
	m_keyMap[VK_OEM_COMMA] = Input::KEY_COMMA;
	m_keyMap[VK_OEM_PERIOD] = Input::KEY_PERIOD;

	//Misc keys
	m_keyMap[VK_ESCAPE] = Input::KEY_ESC;
	m_keyMap[VK_SNAPSHOT] = Input::KEY_PRNTSCR;
	m_keyMap[VK_PAUSE] = Input::KEY_PAUSE_BREAK;
	m_keyMap[VK_INSERT] = Input::KEY_INSERT;
	m_keyMap[VK_HOME] = Input::KEY_HOME;
	m_keyMap[VK_PRIOR] = Input::KEY_PAGE_UP;
	m_keyMap[VK_DELETE] = Input::KEY_DELETE;
	m_keyMap[VK_END] = Input::KEY_END;
	m_keyMap[VK_NEXT] = Input::KEY_PAGE_DOWN;
	m_keyMap[VK_LSHIFT] = Input::KEY_LSHIFT;
	m_keyMap[VK_SHIFT] = Input::KEY_RSHIFT;
	m_keyMap[VK_LCONTROL] = Input::KEY_LCTRL;
	m_keyMap[VK_CONTROL] = Input::KEY_RCTRL;
	m_keyMap[VK_LMENU] = Input::KEY_LALT;
	m_keyMap[VK_MENU] = Input::KEY_RALT;
	m_keyMap[VK_TAB] = Input::KEY_TAB;
	m_keyMap[VK_SPACE] = Input::KEY_SPACEBAR;
	m_keyMap[VK_RETURN] = Input::KEY_ENTER;
	m_keyMap[VK_UP] = Input::KEY_UP;
	m_keyMap[VK_DOWN] = Input::KEY_DOWN;
	m_keyMap[VK_LEFT] = Input::KEY_LEFT;
	m_keyMap[VK_RIGHT] = Input::KEY_RIGHT;

	//Locks
	m_keyMap[VK_CAPITAL] = Input::KEY_CAPS_LOCK;
	m_keyMap[VK_NUMLOCK] = Input::KEY_NUM_LOCK;
	m_keyMap[VK_SCROLL] = Input::KEY_SCROLL_LOCK;

	//F-Keys
	m_keyMap[VK_F1] = Input::KEY_F1;
	m_keyMap[VK_F2] = Input::KEY_F2;
	m_keyMap[VK_F3] = Input::KEY_F3;
	m_keyMap[VK_F4] = Input::KEY_F4;
	m_keyMap[VK_F5] = Input::KEY_F5;
	m_keyMap[VK_F6] = Input::KEY_F6;
	m_keyMap[VK_F7] = Input::KEY_F7;
	m_keyMap[VK_F8] = Input::KEY_F8;
	m_keyMap[VK_F9] = Input::KEY_F9;
	m_keyMap[VK_F10] = Input::KEY_F10;
	m_keyMap[VK_F11] = Input::KEY_F11;
	m_keyMap[VK_F12] = Input::KEY_F12;

	//Alphanumeric
	m_keyMap[0x30] = Input::KEY_0;
	m_keyMap[0x31] = Input::KEY_1;
	m_keyMap[0x32] = Input::KEY_2;
	m_keyMap[0x33] = Input::KEY_3;
	m_keyMap[0x34] = Input::KEY_4;
	m_keyMap[0x35] = Input::KEY_5;
	m_keyMap[0x36] = Input::KEY_6;
	m_keyMap[0x37] = Input::KEY_7;
	m_keyMap[0x38] = Input::KEY_8;
	m_keyMap[0x39] = Input::KEY_9;
	m_keyMap[0x41] = Input::KEY_A;
	m_keyMap[0x42] = Input::KEY_B;
	m_keyMap[0x43] = Input::KEY_C;
	m_keyMap[0x44] = Input::KEY_D;
	m_keyMap[0x45] = Input::KEY_E;
	m_keyMap[0x46] = Input::KEY_F;
	m_keyMap[0x47] = Input::KEY_G;
	m_keyMap[0x48] = Input::KEY_H;
	m_keyMap[0x49] = Input::KEY_I;
	m_keyMap[0x4A] = Input::KEY_J;
	m_keyMap[0x4B] = Input::KEY_K;
	m_keyMap[0x4C] = Input::KEY_L;
	m_keyMap[0x4D] = Input::KEY_M;
	m_keyMap[0x4E] = Input::KEY_N;
	m_keyMap[0x4F] = Input::KEY_O;
	m_keyMap[0x50] = Input::KEY_P;
	m_keyMap[0x51] = Input::KEY_Q;
	m_keyMap[0x52] = Input::KEY_R;
	m_keyMap[0x53] = Input::KEY_S;
	m_keyMap[0x54] = Input::KEY_T;
	m_keyMap[0x55] = Input::KEY_U;
	m_keyMap[0x56] = Input::KEY_V;
	m_keyMap[0x57] = Input::KEY_W;
	m_keyMap[0x58] = Input::KEY_X;
	m_keyMap[0x59] = Input::KEY_Y;
	m_keyMap[0x5A] = Input::KEY_Z;

	//Numpad keys
	m_keyMap[VK_DIVIDE] = Input::KEY_NUM_DIVIDE;
	m_keyMap[VK_MULTIPLY] = Input::KEY_NUM_MUL;
	m_keyMap[VK_SUBTRACT] = Input::KEY_NUM_SUB;
	m_keyMap[VK_DECIMAL] = Input::KEY_NUM_DECIMAL;
	m_keyMap[VK_ADD] = Input::KEY_NUM_ADD;
	m_keyMap[VK_NUMPAD0] = Input::KEY_NUM_0;
	m_keyMap[VK_NUMPAD1] = Input::KEY_NUM_1;
	m_keyMap[VK_NUMPAD2] = Input::KEY_NUM_2;
	m_keyMap[VK_NUMPAD3] = Input::KEY_NUM_3;
	m_keyMap[VK_NUMPAD4] = Input::KEY_NUM_4;
	m_keyMap[VK_NUMPAD5] = Input::KEY_NUM_5;
	m_keyMap[VK_NUMPAD6] = Input::KEY_NUM_6;
	m_keyMap[VK_NUMPAD7] = Input::KEY_NUM_7;
	m_keyMap[VK_NUMPAD8] = Input::KEY_NUM_8;
	m_keyMap[VK_NUMPAD9] = Input::KEY_NUM_9;
}
