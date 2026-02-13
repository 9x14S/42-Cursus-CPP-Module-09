#include "PmergeMe.hpp"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Error: Usage ./PmergeMe <positive integer sequence>" << std::endl;
		return 1;
	}

	PmergeMe sorter;
	
	// The class handles validation and parsing internally to keep main clean
	sorter.parse(argc, argv);
	sorter.execute();

	return 0;
}
