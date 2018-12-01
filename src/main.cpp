#include <stdio.h>
#include <iostream>
#include "output.hpp"

int main(int argc, char *argv[]) {

	if (argc != 3) {
		std::cout << "Usage: dpgen netlistFile verilogFile";
	}

	Output dpgen(argv[1], argv[2]);
	dpgen.ReadFromFile();
	dpgen.printInstructionsToFile();
	return 0;
}

