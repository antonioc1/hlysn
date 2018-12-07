#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdio.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

#include "instruction.hpp"
#include "input.hpp"
#include "ifStatement.hpp"

class Output {
private:
	std::vector<Input*> inputs;
	std::vector<Instruction*> instructions;
	int nums[10] = { 0 };
	char *_filename, *_filename2;
	std::ifstream _inputFile;
	std::ofstream _outputFile;
	char *_latency;
    std::vector<ifStatement*> ifStatements;
    
    
public:
	Output() {};
    Output(char *filename, char *filename2, char *latency) : _filename(filename), _filename2(filename2), _latency(latency) {};
	void ReadFromFile();
	void getInputs(std::string line);
	void getOutputs(std::string line);
	void getVariables(std::string line);
	void getVariablesReg(std::string line);
	void parseInstruction(std::string line);
	bool checkOutputs(std::string line);
	bool checkInputsAndRegs(std::string line);
	bool checkExpression(std::string line);
	void printInstructionsToFile();
	std::vector<std::string> getInputsAndOutputs();
	std::string getDatawidth(std::string line);
	std::string getVariables(Instruction* i);
	void getVariablesVar(std::string line);
	std::string getMuxVariables(Instruction* i);
	std::string getSizes();
    std::vector<Input*> getinputs(){return inputs;}
    void createIfStatement(std::string line);
    ifStatement* getLastifState(){return ifStatements.back();}
    
};



#endif
