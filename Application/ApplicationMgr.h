#pragma once

#include <General/Application/IApplication.h>
#include "Application.h"

typedef SharedPtr<IApplication> ApplicationPtr;

namespace ApplicationMgr
{
	ApplicationPtr CreateApplication(HINSTANCE hInstance, int windowHeight, int windowWidth, const char* name)
	{
		return ApplicationPtr(new Application(hInstance, windowHeight, windowWidth, name));
	}
}