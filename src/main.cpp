#include <stdio.h>
#include <iostream>
#include "output.hpp"
#include "hlsmCreation.hpp"

int main(int argc, char *argv[]) {

	if (argc != 4) {
		std::cout << "Usage: hlsyn cFile latency verilogFile";
	}
    
	int x = atoi(argv[2]);

    HLSM highlevel(argv[1], argv[3], x);
	Output hlysn (argv[1], argv[3], x);
    hlysn.ReadFromFile();
   // dpgen.printInstructionsToFile();
    // create States here
    // list r here
    
    highlevel.printStates(&hlysn);
    

    return 0;
}

