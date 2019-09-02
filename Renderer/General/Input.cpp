#include "Input.h"

#include "IInputMap.h"

#include <Directx11/DX11InputMap.h>

bool k_keyStates[Input::Keys::SIZE];
IInputMap* k_inputMap = nullptr;

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

void Input::Shutdown()
{
	delete k_inputMap;
	k_inputMap = nullptr;
}
