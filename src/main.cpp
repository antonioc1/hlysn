#include <stdio.h>
#include <iostream>
#include "output.hpp"
#include "hlsmCreation.hpp"

int main(int argc, char *argv[]) {

	if (argc != 4) {
		std::cout << "Usage: dpgen netlistFile verilogFile";
	}
    
    int latency = std::stoi(argv[2]);
    HLSM highlevel(argv[1], argv[3], latency);
    Output dpgen(argv[1], argv[3], latency);
    dpgen.ReadFromFile();
//    dpgen.printInstructionsToFile();
    highlevel.printStates();
    

    return 0;
}

