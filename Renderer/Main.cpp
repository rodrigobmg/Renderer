#include <General/ApplicationMgr.h>

#ifdef DIRECTX11
#define PLATFORM_DIR "DirectX"
#else
#error Platform not supported
#endif // DIRECTX

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

static const int kApplicationWindowWidth = 800;
static const int kApplicationWindowHeight = 600;
static const char* kApplicationName = "Renderer";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	DEBUG_LOG("Testing testing %d %d %d", 1, 2, 3);
	ApplicationPtr app = ApplicationMgr::CreateApplication(hInstance, kApplicationWindowWidth, kApplicationWindowHeight, kApplicationName);
	if (app->IsReady())
	{
		app->Run();
	}
	return 0;
}