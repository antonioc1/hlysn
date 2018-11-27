#include <stdio.h>
#include <iostream>
#include "output.hpp"

int main(int argc, char *argv[]) {

	if (argc != 3) {
		std::cout << "Usage: hlysn inputFile outputFile";
	}

	Output HLSM(argv[1], argv[2]);
	HLSM.ReadFromFile();
	HLSM.printInstructionsToFile();
	return 0;
}

