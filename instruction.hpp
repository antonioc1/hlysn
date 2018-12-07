#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdio.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>

class Instruction{
private:
	std::string reg;
	std::string expression;
	std::vector<std::string> variables;

public:
	Instruction(std::string reg, std::string expression, std::vector<std::string> variables);
	std::string getReg();
	std::string getExpression();
	std::vector<std::string> getVariables();
};

#endif
