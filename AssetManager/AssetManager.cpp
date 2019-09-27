#include "pch.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#ifdef _DEBUG
	//Setup logger
	spdlog::set_default_logger(std::make_shared<spdlog::logger>("msvc_logger", std::make_shared<spdlog::sinks::msvc_sink_mt>()));
#endif // _DEBUG

	using namespace std;
	using namespace filesystem;
	if (argc == 3)
	{
		path inputPath(argv[1]);
		path outputPath(argv[2]);
		try
		{
			if (exists(outputPath))
			{
				remove_all(outputPath);
			}
			copy(inputPath, outputPath, copy_options::recursive | copy_options::overwrite_existing);
			return 0;
		}
		catch (const exception& ex)
		{
			ERROR_LOG("Error processing files %s", ex.what());
			return -1;
		}
	}
	else
	{
		ERROR_LOG("Incorrect number of arguments");
	}
	return -1;
}