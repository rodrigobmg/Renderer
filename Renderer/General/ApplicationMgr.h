#pragma once

#include "IApplication.h"
#include "Application.h"

typedef std::unique_ptr<IApplication> ApplicationPtr;

namespace ApplicationMgr
{
	ApplicationPtr CreateApplication(int windowHeight, int windowWidth, const char* name)
	{
		return ApplicationPtr(new Application(windowHeight, windowWidth, name));
	}
}