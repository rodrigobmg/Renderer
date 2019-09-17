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
	namespace fs = experimental::filesystem::v1;
	if (argc == 3)
	{
		fs::path inputPath(argv[1]);
		fs::path outputPath(argv[2]);
		try
		{
			fs::copy(inputPath, outputPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
			return 0;
		}
		catch (const exception& ex)
		{
			ERROR_LOG("Error processing files {}", ex.what());
			return -1;
		}
	}
	else
	{
		ERROR_LOG("Incorrect number of arguments");
	}
	return -1;
}