#pragma once

#include "Pointers.h"
#include "IApplication.h"
#include "Application.h"

typedef SmartPointer<IApplication> ApplicationPtr;

namespace ApplicationMgr
{
	ApplicationPtr CreateApplication(int windowHeight, int windowWidth, const char* name)
	{
		return ApplicationPtr(new Application(windowHeight, windowWidth, name));
	}
}