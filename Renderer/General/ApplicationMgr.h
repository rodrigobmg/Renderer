#pragma once

#include "Pointers.h"
#include "IApplication.h"
#include <Opengl/GLApplication.h>

typedef SmartPointer<IApplication> ApplicationPtr;

namespace ApplicationMgr
{
	ApplicationPtr CreateApplication(int windowHeight, int windowWidth, const char* name)
	{
#ifdef DIRECTX
		return ApplicationPtr(new GLApplication(windowHeight, windowWidth, name));
#elif OPENGL
		return ApplicationPtr(new GLApplication(windowHeight, windowWidth, name));
#else
#error Unrecognised platform
#endif // _M_AMD64

	}
}