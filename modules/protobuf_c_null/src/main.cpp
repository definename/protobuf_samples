#include "pch.h"

int main(int argc, char *argv[])
{
	try
	{
		std::cout << "zlib version: " << zlib_version << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}

	return 0;
}