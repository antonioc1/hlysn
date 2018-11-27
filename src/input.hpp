#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>

class Input {
private:
	std::string type;
	std::string size;
	std::vector<std::string> variables;
public:
	Input(std::string type, std::string size, std::vector<std::string> variables);
	std::string getType();
	std::vector<std::string> getVariables();
	std::string getSize();
};

#endif