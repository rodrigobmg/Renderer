#include "Input.h"

#include "IInputMap.h"

#ifdef DIRECTX11
#include <Directx11/DX11InputMap.h>
#elif OPENGL
#include <OpenGL/GLInputMap.h>
#endif // DIRECTX

bool k_keyStates[Input::Keys::SIZE];
IInputMap* k_inputMap = nullptr;

void InitializeKeyMap()
{
#ifdef DIRECTX11
	k_inputMap = new DXInputMap();
#elif OPENGL
	k_inputMap = new GLInputMap();
#endif // DIRECTX
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
