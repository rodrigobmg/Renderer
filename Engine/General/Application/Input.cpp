#include "pch.h"
#include "Input.h"

#include "IInputMap.h"

#include <Directx11/Application/DX11InputMap.h>


//Global variables
bool k_keyStates[Input::Keys::SIZE];
IInputMap* k_inputMap = nullptr;
struct MouseButtonState
{
	bool isDown;
	Input::MouseButtonType type;
};

MouseButtonState leftMBState = { false, Input::MouseButtonType::kLeft };
MouseButtonState rightMBState = { false, Input::MouseButtonType::kRight };

int mouseX = 0;
int mouseY = 0;


void InitializeKeyMap()
{
	k_inputMap = new DX11InputMap();
}

bool Input::GetKeyDown(unsigned int keyCode)
{
	assert(keyCode < SIZE);
	return k_keyStates[keyCode];
}

void Input::SetKeyDown(unsigned int keyCode)
{
	if (!k_inputMap)
	{
		InitializeKeyMap();
	}
	keyCode = k_inputMap->GetMappedValue(keyCode);
	assert(keyCode < SIZE);
	k_keyStates[keyCode] = true;
}

void Input::SetKeyUp(unsigned int keyCode)
{
	if (!k_inputMap)
	{
		InitializeKeyMap();
	}
	keyCode = k_inputMap->GetMappedValue(keyCode);
	assert(keyCode < SIZE);
	k_keyStates[keyCode] = false;
}

void Input::SetMouseButtonDown(bool isDown, MouseButtonType buttonType)
{
	if (buttonType == MouseButtonType::kLeft)
	{
		leftMBState.isDown = isDown;
	}
	else if (buttonType == MouseButtonType::kRight)
	{
		rightMBState.isDown = isDown;
	}
}

bool Input::GetMouseButtonDown(MouseButtonType buttonType)
{
	if (buttonType == MouseButtonType::kLeft)
	{
		return leftMBState.isDown;
	}
	else if (buttonType == MouseButtonType::kRight)
	{
		return rightMBState.isDown;
	}
	return false;
}

void Input::SetMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Input::GetMousePosition(int& x, int& y)
{
	x = mouseX;
	y = mouseY;
}

void Input::Shutdown()
{
	delete k_inputMap;
	k_inputMap = nullptr;
}
