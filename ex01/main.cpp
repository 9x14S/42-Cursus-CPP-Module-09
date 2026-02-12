#include <cstdlib>
#include <iostream>

#include "RPN.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "usage: " << argv[0] << " <expression>" << std::endl;
		return EXIT_FAILURE;
	}
	try
	{
		long result = RPN::eval(argv[1]);
		std::cout << result << std::endl;
		return EXIT_SUCCESS;
	}
	catch (...)
	{
		std::cerr << "Error" << std::endl;
		return EXIT_FAILURE;
	}
}
