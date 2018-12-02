#include "output.hpp"

void Output::ReadFromFile(){
	std::string line;
	std::string word;
	if (_filename != NULL) {
		_inputFile.open(_filename);
		if (_inputFile.is_open()) {
			while (std::getline(_inputFile, line)) {
				if (!(line == "")) {
					std::istringstream iss(line);
					iss >> word;
					if (word == "input") {
						getInputs(line);
					}
					else if (word == "output") {
						getOutputs(line);
					}
					else if (word == "wire") {
						getVariables(line);
					}
					else if (word == "register") {
						getVariablesReg(line);
					}
					else if (word == "variable") {
						getVariablesVar(line);
					}
					else {
						parseInstruction(line);
					}
				}
			}
		}
        else {
            std::cout << _filename << "\n";
            std::cout << "input file not found";
            exit(EXIT_FAILURE);
        }
	}
	
}

void Output::getInputs(std::string line) {
	std::string word;
	line.erase(std::remove(line.begin(), line.end(), ','), line.end());
	std::istringstream iss(line);
	int counter = 0;
	std::string size;
	std::vector<std::string> variables;

	while (iss >> word) {
		if (counter >= 2) {
			variables.push_back(word);
		}
		else if (counter == 1) {
			size = word;
		}
		counter++;
	}
	Input* input = NULL;
	input = new Input("input", size, variables);
	inputs.push_back(input);
}

void Output::getOutputs(std::string line) {
	std::string word;
	line.erase(std::remove(line.begin(), line.end(), ','), line.end());
	std::istringstream iss(line);
	int counter = 0;
	std::string size;
	std::vector<std::string> variables;

	while (iss >> word) {
		if (counter >= 2) {
			variables.push_back(word);
		}
		else if (counter == 1) {
			size = word;
		}
		counter++;
	}
	Input* input = NULL;
	input = new Input("output", size, variables);
	inputs.push_back(input);
}

void Output::getVariables(std::string line) {
	std::string word;
	line.erase(std::remove(line.begin(), line.end(), ','), line.end());
	std::istringstream iss(line);
	int counter = 0;
	std::string size;
	std::vector<std::string> variables;

	while (iss >> word) {
		if (counter >= 2) {
			variables.push_back(word);
		}
		else if (counter == 1) {
			size = word;
		}
		counter++;
	}
	Input* input = NULL;
	input = new Input("wire", size, variables);
	inputs.push_back(input);
}

void Output::getVariablesReg(std::string line) {
	std::string word;
	line.erase(std::remove(line.begin(), line.end(), ','), line.end());
	std::istringstream iss(line);
	int counter = 0;
	std::string size;
	std::vector<std::string> variables;

	while (iss >> word) {
		if (counter >= 2) {
			variables.push_back(word);
		}
		else if (counter == 1) {
			size = word;
		}
		counter++;
	}
	Input* input = NULL;
	input = new Input("reg", size, variables);
	inputs.push_back(input);
}

void Output::getVariablesVar(std::string line) {
	std::string word;
	line.erase(std::remove(line.begin(), line.end(), ','), line.end());
	std::istringstream iss(line);
	int counter = 0;
	std::string size;
	std::vector<std::string> variables;

	while (iss >> word) {
		if (counter >= 2) {
			variables.push_back(word);
		}
		else if (counter == 1) {
			size = word;
		}
		counter++;
	}
	Input* input = NULL;
	input = new Input("variable", size, variables);
	inputs.push_back(input);
}

void Output::parseInstruction(std::string line) {
	std::string word;
	std::istringstream iss(line);
	int counter = 0;
	std::string reg;
	std::string expression;
	std::vector<std::string> variables;

	while (iss >> word) {
		if (counter == 0) {
			if (checkOutputs(word) != false) {
				reg = word;
			}
			else {
				// error: reg not found
				std::cout << "Error: register " << word << " not found\n";
				exit(EXIT_FAILURE);
			}
		}
		else if (counter >= 2) {
			if (counter == 2) {
				if (checkInputsAndRegs(word) != false) {
					variables.push_back(word);
				}
				else {
					// error: input/reg not found
					std::cout << "Error: register/input " << word << " not found\n";
					exit(EXIT_FAILURE);
				}
			}
			else if (counter == 3) {
				if (checkExpression(word) != false) {
					expression = word;
				}
				else {
					//error: expression not found
					std::cout << "Error: expression " << word << " not found\n";
					exit(EXIT_FAILURE);
				}
			}
			else if (counter == 4) {
				if (checkInputsAndRegs(word) != false) {
					variables.push_back(word);
				}
				else {
					//error: input/reg not found
					std::cout << "Error: input/register " << word << " not found\n";
					exit(EXIT_FAILURE);
				}
			}
			// for ?
			else if (counter == 6) {
				if (checkInputsAndRegs(word) != false) {
					variables.push_back(word);
				}
				else {
					//error: input/reg not found
					std::cout << "Error: input/register " << word << " not found\n";
					exit(EXIT_FAILURE);
				}
			}
		}
		counter++;
	}
	if (expression == "") {
		expression = "=";
	}
	Instruction* instruct = NULL;
	instruct = new Instruction(reg, expression, variables);
	instructions.push_back(instruct);
}

bool Output::checkOutputs(std::string line) {

	for (Input* i : inputs) {
		//std::cout << i->getType();
		if (i->getType() == "output" || i->getType() == "wire" || i->getType() == "reg" || i->getType() == "variable") {
			for (std::string j : i->getVariables()) {
				//std::cout << j;
				if (j == line) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Output::checkInputsAndRegs(std::string line) {
	for (Input* i : inputs) {
		//std::cout << i->getType();
		if (i->getType() == "input" || i->getType() == "wire" || i->getType() == "reg" || i->getType() == "variable") {
			for (std::string j : i->getVariables()) {
				//std::cout << j;
				if (j == line) {
					return true;
				}
			}
		}
	}
	return false;
}

bool Output::checkExpression(std::string line) {
	if ((line == "+") || (line == "-") || (line == "*") || (line == ">") || (line == "<") || (line == "==") || (line == "?") || (line == ">>") || (line == "<<") || (line == "/") || (line == "%")) {
		return true;
	}
	return false;
}

void Output::printInstructionsToFile() {
	if (_filename2 != NULL) {
		_outputFile.open(_filename2);
	}
	else {
		std::cout << "Output file not found";
		
		exit(EXIT_FAILURE);
	}
	
	_outputFile << "`timescale 1ns / 1ps \n";
	_outputFile << "module HLSM (Clk, Rst, Start, Done, ";

	std::vector<std::string> variables = getInputsAndOutputs();

	for (int i = 0; i < variables.size(); i++) {
		if (i != (variables.size() - 1)) {
			_outputFile << variables[i] + ", ";
		}
		else {
			_outputFile << variables[i];
		}
	}

	_outputFile << ");\n\n";

	_outputFile << getSizes();

	_outputFile << "\n";
	_outputFile << "input Clk, Rst, Start;\n";
    _outputFile << "output reg Done;\n";

	for (Input* i : inputs) {
		std::string size = i->getSize();
		size.erase(remove_if(size.begin(), size.end(), [](char c) { return !isalpha(c); }), size.end());
		if (size == "UInt") {
			_outputFile << i->getType() + " [" + i->getSize() + "-1:0] ";
		}
		else {
			_outputFile << i->getType() + " signed [" + i->getSize() + "-1:0] ";
		}
		std::vector<std::string> variables = i->getVariables();
		for (int i = 0; i < variables.size(); i++) {
			if (i != (variables.size() - 1)) {
				_outputFile << variables[i] + ", ";
			}
			else {
				_outputFile << variables[i] + ";\n";
			}
		}
	}

	_outputFile << "\n";

	int counter = 0;
	std::string line;
	for (Instruction* i : instructions) {
		std::string sign = getDatawidth(i->getReg());
		sign.erase(remove_if(sign.begin(), sign.end(), [](char c) { return !isalpha(c); }), sign.end());

		if (sign == "Int") {
			line = "S";
		}
		else {
			line = "";
		}

		if (i->getExpression() == "+") {
			nums[0]++;
			_outputFile << line << "ADD #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) add_" << nums[0] << "(" << getVariables(i) << i->getReg() << ");\n\n";
		}
		else if (i->getExpression() == "-") {
			nums[1]++;
			_outputFile << line << "SUB #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) sub_" << nums[1] << "(" << getVariables(i) << i->getReg() << ");\n\n";
		}
		else if (i->getExpression() == "==") {
			nums[2]++;
			_outputFile << line << "COMP #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) comp_" << nums[2] << "(" << getVariables(i) << "0, 0, " <<  i->getReg() << ");\n\n";
		}
		else if (i->getExpression() == "<") {
			nums[2]++;
			_outputFile << line << "COMP #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) comp_" << nums[2] << "(" << getVariables(i) << "0, " << i->getReg() << ", 0);\n\n";
		}
		else if (i->getExpression() == ">") {
			nums[2]++;
			_outputFile << line << "COMP #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) comp_" << nums[2] << "(" << getVariables(i) << i->getReg() <<", 0, 0);\n\n";
		}
		else if (i->getExpression() == "<<") {
			nums[3]++;
			_outputFile << line << "SHL #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) shl_" << nums[3] << "(" << getVariables(i) << i->getReg() << ");\n\n";
		}
		else if (i->getExpression() == ">>") {
			nums[4]++;
			_outputFile << line << "SHR #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) shr_" << nums[4] << "(" << getVariables(i) << i->getReg() << ");\n\n";
		}

		// FIX ME : MUX

		else if (i->getExpression() == "?") {
			nums[5]++;
			_outputFile << line << "MUX2x1 #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) mux2x1_" << nums[5] << "(" << getMuxVariables(i) << i->getReg() << ");\n\n";
		}
		else if (i->getExpression() == "*") {
			nums[6]++;
			_outputFile << line << "MUL #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) mul_" << nums[6] << "(" << getVariables(i) << i->getReg() << ");\n\n";
		}
		else if (i->getExpression() == "=") {
			nums[7]++;
			_outputFile << line << "REG #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) reg_" << nums[7] << "(" << getVariables(i) << "Clk, Rst, " << i->getReg() <<");\n\n";
		}
		else if (i->getExpression() == "/") {
			nums[8]++;
			_outputFile << line << "DIV #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) div_" << nums[8] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "%") {
			nums[9]++;
			_outputFile << line << "MOD #(.DATAWIDTH(" << getDatawidth(i->getReg()) << ")) mod_" << nums[9] << "(" << getVariables(i) << ");\n\n";
		}

	}
	_outputFile << "endmodule";
}

std::vector<std::string> Output::getInputsAndOutputs() {
	std::vector<std::string> variables;
	for (Input* i : inputs) {
		//std::cout << i->getType();
		if (i->getType() == "output" || i->getType() == "input") {
			for (std::string j : i->getVariables()) {
				//std::cout << j;
				variables.push_back(j);
			}
		}
	}
	return variables;
}

std::string Output::getDatawidth(std::string line) {
	for (Input* i : inputs) {
		for (std::string j : i->getVariables()) {
			if (j == line) {
				return i->getSize();
			}
		}
		
	}
	return 0;
}

std::string Output::getVariables(Instruction * i) {
	std::string line = "";
	std::vector<std::string> variables = i->getVariables();
	
	for (int j = 0; j < variables.size(); j++) {
		/*
		if (j != (variables.size() - 1)) {
			line = line + variables[j] + ", ";
		}
		else {
			line = line + variables[j];
		}
		*/
		line = line + variables[j] + ", ";
	}

	return line;
}

std::string Output::getMuxVariables(Instruction* i) {
	std::string line = "";
	std::vector<std::string> variables = i->getVariables();
	std::string selector;

	for (int j = 0; j < variables.size(); j++) {
		/*
		if (j != (variables.size() - 1)) {
			line = line + variables[j] + ", ";
		}
		else {
			line = line + variables[j];
		}
		*/
		if (j == 0) {
			selector = variables[j];
		}
		else {
			line = line + variables[j] + ", ";
		}
	}
	line = line + selector + ", ";
	return line;
}

std::string Output::getSizes() {
	bool flag;
	std::vector<std::string> currentSizes;
	std::string line;
	std::string size;
	std::string output = "";

	for (Input* i : inputs) {
		if (currentSizes.size() == 0) {
			currentSizes.push_back(i->getSize());
		}
		else {
			for (int j = 0; j < currentSizes.size(); j++) {
				if (currentSizes[j] == i->getSize()) {
					flag = false;
					break;
				}
				else {
					flag = true;
				}
			}
			if (flag != false) {
				currentSizes.push_back(i->getSize());
			}
		}
	}
	for (int i = 0; i < currentSizes.size(); i++) {
		line = currentSizes[i];
		size = currentSizes[i];
		line.erase(remove_if(line.begin(), line.end(), [](char c) { return !isalpha(c); }), line.end());
		if (line == "Int") {
			size.erase(0, 3);
			output = output + "parameter " + currentSizes[i] + " = " + size + ";\n";
		}
		else if(line == "UInt") {
			size.erase(0, 4);
			output = output + "parameter " + currentSizes[i] + " = " + size + ";\n";
		}
	}
	return output;
}

