#include <stdio.h>
#include <iostream>
#include "output.hpp"
#include "hlsmCreation.hpp"

int main(int argc, char *argv[]) {

	if (argc != 4) {
		std::cout << "Usage: hlsyn cFile latency verilogFile";
	}
    
    HLSM highlevel(argv[1], argv[3], argv[2]);
	Output hlysn (argv[1], argv[3], argv[2]);
    hlysn.ReadFromFile();
   // dpgen.printInstructionsToFile();
    // create States here
    // list r here
    
    highlevel.printStates(&hlysn);
    

    return 0;
}

