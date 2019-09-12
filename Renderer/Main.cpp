#include "stdafx.h"
#include <General/ApplicationMgr.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

static const int kApplicationWindowWidth = 800;
static const int kApplicationWindowHeight = 600;
static const char* kApplicationName = "Renderer";

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ApplicationPtr app = ApplicationMgr::CreateApplication(hInstance, kApplicationWindowWidth, kApplicationWindowHeight, kApplicationName);
	if (app->IsReady())
	{
		app->Run();
	}
	return 0;
}