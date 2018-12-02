//
//  hlsmCreation.hpp
//  hlysn
//
//  Created by Alec Foster on Saturday12/1.
//

#ifndef hlsmCreation_hpp
#define hlsmCreation_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;

class HLSM{
private:
    int latCon = 0;
    char *_filename, *_filename2;
    std::ifstream _inputFile;
    std::ofstream _outputFile;
    
public:
    HLSM(char *filename, char *filename2,int latency) : latCon(latency), _filename(filename), _filename2(filename2){};
    void printStates();
    
};

class State{
private:
    string name;
    
public:
    
};



#endif /* hlsmCreation_hpp */
