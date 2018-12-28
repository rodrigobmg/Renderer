#include <General/Logger.h>
#include <General/ApplicationMgr.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main(int argc, char** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ApplicationPtr app = ApplicationMgr::CreateApplication(800, 600, "Test");
	app->Start();
	return 0;
}