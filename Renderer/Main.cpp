#include <General/ApplicationMgr.h>

#ifdef DIRECTX
#define PLATFORM_DIR "DirectX"
#elif
#define PLATFORM_DIR "Opengl"
#else
#error Platform not supported
#endif // DIRECTX

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