#include "GLInputMap.h"

#include <General/Input.h>
#include <Externals/GLFW/Includes.h>

GLInputMap::GLInputMap()
{
	//Special characters
	m_keyMap[GLFW_KEY_GRAVE_ACCENT] = Input::KEY_TILDE;
	m_keyMap[GLFW_KEY_MINUS] = Input::KEY_HYPHEN;
	m_keyMap[GLFW_KEY_EQUAL] = Input::KEY_EQUAL;
	m_keyMap[GLFW_KEY_BACKSPACE] = Input::KEY_BACKSPACE;
	m_keyMap[GLFW_KEY_LEFT_BRACKET] = Input::KEY_OPEN_SQUARE_BRACKETS;
	m_keyMap[GLFW_KEY_RIGHT_BRACKET] = Input::KEY_CLOSE_SQUARE_BRACKETS;
	m_keyMap[GLFW_KEY_BACKSLASH] = Input::KEY_BACKSLASH;
	m_keyMap[GLFW_KEY_SLASH] = Input::KEY_FORWARDSLASH;
	m_keyMap[GLFW_KEY_SEMICOLON] = Input::KEY_SEMICOLON;
	m_keyMap[GLFW_KEY_APOSTROPHE] = Input::KEY_APOSTROPHE;
	m_keyMap[GLFW_KEY_COMMA] = Input::KEY_COMMA;
	m_keyMap[GLFW_KEY_PERIOD] = Input::KEY_PERIOD;

	//Misc keys
	m_keyMap[GLFW_KEY_ESCAPE] = Input::KEY_ESC;
	m_keyMap[GLFW_KEY_PRINT_SCREEN] = Input::KEY_PRNTSCR;
	m_keyMap[GLFW_KEY_PAUSE] = Input::KEY_PAUSE_BREAK;
	m_keyMap[GLFW_KEY_INSERT] = Input::KEY_INSERT;
	m_keyMap[GLFW_KEY_HOME] = Input::KEY_HOME;
	m_keyMap[GLFW_KEY_PAGE_UP] = Input::KEY_PAGE_UP;
	m_keyMap[GLFW_KEY_DELETE] = Input::KEY_DELETE;
	m_keyMap[GLFW_KEY_END] = Input::KEY_END;
	m_keyMap[GLFW_KEY_PAGE_DOWN] = Input::KEY_PAGE_DOWN;
	m_keyMap[GLFW_KEY_LEFT_SHIFT] = Input::KEY_LSHIFT;
	m_keyMap[GLFW_KEY_RIGHT_SHIFT] = Input::KEY_RSHIFT;
	m_keyMap[GLFW_KEY_LEFT_CONTROL] = Input::KEY_LCTRL;
	m_keyMap[GLFW_KEY_RIGHT_CONTROL] = Input::KEY_RCTRL;
	m_keyMap[GLFW_KEY_LEFT_ALT] = Input::KEY_LALT;
	m_keyMap[GLFW_KEY_RIGHT_ALT] = Input::KEY_RALT;
	m_keyMap[GLFW_KEY_TAB] = Input::KEY_TAB;
	m_keyMap[GLFW_KEY_SPACE] = Input::KEY_SPACEBAR;
	m_keyMap[GLFW_KEY_ENTER] = Input::KEY_ENTER;
	m_keyMap[GLFW_KEY_UP] = Input::KEY_UP;
	m_keyMap[GLFW_KEY_DOWN] = Input::KEY_DOWN;
	m_keyMap[GLFW_KEY_LEFT] = Input::KEY_LEFT;
	m_keyMap[GLFW_KEY_RIGHT] = Input::KEY_RIGHT;

	//Locks
	m_keyMap[GLFW_KEY_CAPS_LOCK] = Input::KEY_CAPS_LOCK;
	m_keyMap[GLFW_KEY_NUM_LOCK] = Input::KEY_NUM_LOCK;
	m_keyMap[GLFW_KEY_SCROLL_LOCK] = Input::KEY_SCROLL_LOCK;

	//F-Keys
	m_keyMap[GLFW_KEY_F1] = Input::KEY_F1;
	m_keyMap[GLFW_KEY_F2] = Input::KEY_F2;
	m_keyMap[GLFW_KEY_F3] = Input::KEY_F3;
	m_keyMap[GLFW_KEY_F4] = Input::KEY_F4;
	m_keyMap[GLFW_KEY_F5] = Input::KEY_F5;
	m_keyMap[GLFW_KEY_F6] = Input::KEY_F6;
	m_keyMap[GLFW_KEY_F7] = Input::KEY_F7;
	m_keyMap[GLFW_KEY_F8] = Input::KEY_F8;
	m_keyMap[GLFW_KEY_F9] = Input::KEY_F9;
	m_keyMap[GLFW_KEY_F10] = Input::KEY_F10;
	m_keyMap[GLFW_KEY_F11] = Input::KEY_F11;
	m_keyMap[GLFW_KEY_F12] = Input::KEY_F12;

	//Alphanumeric
	m_keyMap[GLFW_KEY_0] = Input::KEY_0;
	m_keyMap[GLFW_KEY_1] = Input::KEY_1;
	m_keyMap[GLFW_KEY_2] = Input::KEY_2;
	m_keyMap[GLFW_KEY_3] = Input::KEY_3;
	m_keyMap[GLFW_KEY_4] = Input::KEY_4;
	m_keyMap[GLFW_KEY_5] = Input::KEY_5;
	m_keyMap[GLFW_KEY_6] = Input::KEY_6;
	m_keyMap[GLFW_KEY_7] = Input::KEY_7;
	m_keyMap[GLFW_KEY_8] = Input::KEY_8;
	m_keyMap[GLFW_KEY_9] = Input::KEY_9;
	m_keyMap[GLFW_KEY_A] = Input::KEY_A;
	m_keyMap[GLFW_KEY_B] = Input::KEY_B;
	m_keyMap[GLFW_KEY_C] = Input::KEY_C;
	m_keyMap[GLFW_KEY_D] = Input::KEY_D;
	m_keyMap[GLFW_KEY_E] = Input::KEY_E;
	m_keyMap[GLFW_KEY_F] = Input::KEY_F;
	m_keyMap[GLFW_KEY_G] = Input::KEY_G;
	m_keyMap[GLFW_KEY_H] = Input::KEY_H;
	m_keyMap[GLFW_KEY_I] = Input::KEY_I;
	m_keyMap[GLFW_KEY_J] = Input::KEY_J;
	m_keyMap[GLFW_KEY_K] = Input::KEY_K;
	m_keyMap[GLFW_KEY_L] = Input::KEY_L;
	m_keyMap[GLFW_KEY_M] = Input::KEY_M;
	m_keyMap[GLFW_KEY_N] = Input::KEY_N;
	m_keyMap[GLFW_KEY_O] = Input::KEY_O;
	m_keyMap[GLFW_KEY_P] = Input::KEY_P;
	m_keyMap[GLFW_KEY_Q] = Input::KEY_Q;
	m_keyMap[GLFW_KEY_R] = Input::KEY_R;
	m_keyMap[GLFW_KEY_S] = Input::KEY_S;
	m_keyMap[GLFW_KEY_T] = Input::KEY_T;
	m_keyMap[GLFW_KEY_U] = Input::KEY_U;
	m_keyMap[GLFW_KEY_V] = Input::KEY_V;
	m_keyMap[GLFW_KEY_W] = Input::KEY_W;
	m_keyMap[GLFW_KEY_X] = Input::KEY_X;
	m_keyMap[GLFW_KEY_Y] = Input::KEY_Y;
	m_keyMap[GLFW_KEY_Z] = Input::KEY_Z;

	//Numpad keys
	m_keyMap[GLFW_KEY_KP_DIVIDE] = Input::KEY_NUM_DIVIDE;
	m_keyMap[GLFW_KEY_KP_MULTIPLY] = Input::KEY_NUM_MUL;
	m_keyMap[GLFW_KEY_KP_SUBTRACT] = Input::KEY_NUM_SUB;
	m_keyMap[GLFW_KEY_KP_DECIMAL] = Input::KEY_NUM_DECIMAL;
	m_keyMap[GLFW_KEY_KP_ADD] = Input::KEY_NUM_ADD;
	m_keyMap[GLFW_KEY_KP_ENTER] = Input::KEY_NUM_ENTER;
	m_keyMap[GLFW_KEY_KP_0] = Input::KEY_NUM_0;
	m_keyMap[GLFW_KEY_KP_1] = Input::KEY_NUM_1;
	m_keyMap[GLFW_KEY_KP_2] = Input::KEY_NUM_2;
	m_keyMap[GLFW_KEY_KP_3] = Input::KEY_NUM_3;
	m_keyMap[GLFW_KEY_KP_4] = Input::KEY_NUM_4;
	m_keyMap[GLFW_KEY_KP_5] = Input::KEY_NUM_5;
	m_keyMap[GLFW_KEY_KP_6] = Input::KEY_NUM_6;
	m_keyMap[GLFW_KEY_KP_7] = Input::KEY_NUM_7;
	m_keyMap[GLFW_KEY_KP_8] = Input::KEY_NUM_8;
	m_keyMap[GLFW_KEY_KP_9] = Input::KEY_NUM_9;
}
