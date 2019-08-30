#include <General/ApplicationMgr.h>

#ifdef DIRECTX11
#define PLATFORM_DIR "DirectX"
#elif OPENGL
#define PLATFORM_DIR "Opengl"
#else
#error Platform not supported
#endif // DIRECTX

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ApplicationPtr app = ApplicationMgr::CreateApplication(800, 600, "Test");
	if (app->IsReady())
	{
		app->Run();
	}
	return 0;
}