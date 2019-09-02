#include "pch.h"

int main(int argc, char *argv[])
{
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
			cout << "Error processing files " << ex.what();
			return -1;
		}
	}
	else
	{
		cout << "Incorrect number of arguments";
	}
	return -1;
}