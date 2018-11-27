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
					else if (word == "variable") {
						getVariables(line);
					}
					else {
						parseInstruction(line);
					}
				}
			}
		}
	}
	else {
		std::cout << "input file not found";
		EXIT_FAILURE;
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
	Instruction* instruct = NULL;
	instruct = new Instruction(reg, expression, variables);
	instructions.push_back(instruct);
}

bool Output::checkOutputs(std::string line) {

	for (Input* i : inputs) {
		//std::cout << i->getType();
		if (i->getType() == "output" || i->getType() == "variable") {
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
		if (i->getType() == "input" || i->getType() == "variable") {
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
		return;
	}

	_outputFile << "module structural(Clk, Rst, ";

	std::vector<std::string> variables = getInputsAndOutputs();

	for (int i = 0; i < variables.size(); i++) {
		if (i != (variables.size() - 1)) {
			_outputFile << variables[i] + ", ";
		}
		else {
			_outputFile << variables[i];
		}
	}

	_outputFile << ");\n";

	for (Input* i : inputs) {
		_outputFile << i->getType() + " " + i->getSize() + " ";
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
	for (Instruction* i : instructions) {
		if (i->getExpression() == "+") {
			nums[0]++;
			_outputFile << "ADD #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) add_" << nums[0] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "-") {
			nums[1]++;
			_outputFile << "SUB #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) sub_" << nums[1] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "==") {
			nums[2]++;
			_outputFile << "COMP #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) comp_" << nums[2] << "(" << "\"eq\", " << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "<") {
			nums[2]++;
			_outputFile << "COMP #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) comp_" << nums[2] << "(" << "\"lt\", " << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == ">") {
			nums[2]++;
			_outputFile << "COMP #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) comp_" << nums[2] << "(" << "\"gt\", " << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "<<") {
			nums[3]++;
			_outputFile << "SHL #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) shl_" << nums[3] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == ">>") {
			nums[4]++;
			_outputFile << "SHR #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) shr_" << nums[4] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "?") {
			nums[5]++;
			_outputFile << "MUX2x1 #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) mux2x1_" << nums[5] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "*") {
			nums[6]++;
			_outputFile << "MUL #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) mul_" << nums[6] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "<<") {
			nums[7]++;
			_outputFile << "REG #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) reg_" << nums[7] << "(Clk, Rst, " << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "/") {
			nums[8]++;
			_outputFile << "DIV #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) div_" << nums[8] << "(" << getVariables(i) << ");\n\n";
		}
		else if (i->getExpression() == "%") {
			nums[9]++;
			_outputFile << "MOD #(.DATAWIFTH(" << getDatawidth(i->getReg()) << ")) mod_" << nums[9] << "(" << getVariables(i) << ");\n\n";
		}

	}
	_outputFile << "end module";
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
		line = line + variables[j] + ", ";
	}
	line = line + i->getReg();
	return line;
}
