#pragma once

//Class which creates a single global static instance of itself, states are set by the window classes (still to be determined)
//Custom key and mouse mappings for DX and GL platforms will reside in the specific implementations
namespace Input
{
	enum Keys : uint8_t
	{
		//Special characters
		KEY_TILDE,
		KEY_HYPHEN,
		KEY_EQUAL,
		KEY_BACKSPACE,
		KEY_OPEN_SQUARE_BRACKETS,
		KEY_CLOSE_SQUARE_BRACKETS,
		KEY_BACKSLASH,
		KEY_FORWARDSLASH,
		KEY_SEMICOLON,
		KEY_APOSTROPHE,
		KEY_COMMA,
		KEY_PERIOD,

		//Misc keys
		KEY_ESC,
		KEY_PRNTSCR,
		KEY_PAUSE_BREAK,
		KEY_INSERT,
		KEY_HOME,
		KEY_PAGE_UP,
		KEY_DELETE,
		KEY_END,
		KEY_PAGE_DOWN,
		KEY_LSHIFT,
		KEY_RSHIFT,
		KEY_LCTRL,
		KEY_RCTRL,
		KEY_LALT,
		KEY_RALT,
		KEY_TAB,
		KEY_SPACEBAR,
		KEY_ENTER,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,

		//Locks
		KEY_CAPS_LOCK,
		KEY_NUM_LOCK,
		KEY_SCROLL_LOCK,

		//F-Keys
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		
		//Alphanumeric
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,

		//Numpad keys
		KEY_NUM_DIVIDE,
		KEY_NUM_MUL,
		KEY_NUM_SUB,
		KEY_NUM_DECIMAL,
		KEY_NUM_ADD,
		KEY_NUM_ENTER,
		KEY_NUM_0,
		KEY_NUM_1,
		KEY_NUM_2,
		KEY_NUM_3,
		KEY_NUM_4,
		KEY_NUM_5,
		KEY_NUM_6,
		KEY_NUM_7,
		KEY_NUM_8,
		KEY_NUM_9,

		SIZE
	};

	enum class MouseButtonType
	{
		kNone,
		kLeft,
		kRight
	};

	bool GetKeyDown(unsigned int keyCode);
	void SetKeyDown(unsigned int keyCode);
	void SetKeyUp(unsigned int keyCode);

	void SetMouseButtonDown(bool isDown, MouseButtonType buttonType);
	bool GetMouseButtonDown(MouseButtonType button);
	void SetMousePosition(int x, int y);
	void GetMousePosition(int& x, int& y);

	void Shutdown();
};