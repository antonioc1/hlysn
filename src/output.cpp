#include "output.hpp"
#include<algorithm>

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
                    else if (word == "if") {
                        createIfStatement(line); //Fix
                        
                        
                    }
                    else if (word == "else") {
                        createIfStatement(line); //Fix
                        
                        
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

void Output::createIfStatement(std::string line){
    std::size_t foundif = line.find("if");
    if (foundif!=std::string::npos) {
        
    
    ifStatement* ifState = new ifStatement();
    line.erase(std::remove(line.begin(), line.end(), '{'), line.end());
    ifState->setCondition(line);
    std::getline(_inputFile, line);
    while (1) {
        std::size_t foundif = line.find("if");
        std::size_t foundelse = line.find("else");
        std::size_t foundbracket = line.find("}");
        if (foundif!=std::string::npos){
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            std::cout << "nested if\n";
            createIfStatement(line);
            ifStatement* last = this->getLastifState();
            ifState->setNestedIf(last);
            std::getline(_inputFile, line);
        }
        else if (foundelse!=std::string::npos) {
            ifStatement* lastIf = this->getLastifState();
            std::getline(_inputFile, line);
            lastIf->setInElse(line);
            lastIf->setElseStatement();
            std::getline(_inputFile, line);
        }
        else if (foundbracket!=std::string::npos){
//            std::getline(_inputFile, line);
//            std::size_t foundelse = line.find("else");
//            if (foundelse!=std::string::npos) {
//                ifState->setInElse(line);
//            }
                break;
        }
        else{
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            ifState->setInIf(line);
            std::getline(_inputFile, line);
        }
    }
    ifStatements.push_back(ifState);
}
    else{
        while (1) {
        ifStatement* lastIf = this->getLastifState();
        std::getline(_inputFile, line);
            std::size_t foundbracket = line.find("}");
            if (foundbracket!=std::string::npos){
                break;
            }
        lastIf->setInElse(line);
        lastIf->setElseStatement();
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
//                    if (word == ">") {
//                        std::size_t found = line.find(">");
//                        if (found!=std::string::npos)
//                            std::cout << "create reg for > " << found << '\n';
//                    }
//                    else if (word == "<") {
//                        std::size_t found = line.find("<");
//                        if (found!=std::string::npos)
//                            std::cout << "create reg for < " << found << '\n';
//                    }
//                    else if (word == "=") {
//                        std::size_t found = line.find("=");
//                        if (found!=std::string::npos)
//                            std::cout << "create reg for = " << found << '\n';
//                    }
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

void Output::createEquations() {
	for (Instruction* i : instructions) {
		Equation* equation = NULL;
		std::vector<std::string> emp;
		equation = new Equation(0, 0, 0, 800, i->getReg(), i->getExpression(), i->getVariables(), emp, 0, false);
		equations.push_back(equation);
	}
	listRDone = listRSort(equations, _latency);
}

std::vector<Equation*> Output::listRSort(std::vector<Equation*> inputStuff, int globalLatency) {
	int i = 0;
	int j = 0;
	int k = 0;
	int t = 0;
	int m = 0;
	int cnt = 0;
	int flag = 0;
	int flagLat2 = 0;
	int flagLat3 = 0;
    bool testFlag = false;
	std::vector<int> opLat;
    std::vector<std::string> dumb;

	std::vector<Equation*> sortedEq;
	std::vector<Equation*> alapEqList;
	std::vector<Equation*> listREq;

	//clear all initiated vectors to prevent pointer issues 
	opLat.clear();
	sortedEq.clear();
	alapEqList.clear();
	listREq.clear();
    dumb.clear();

	sortedEq = inputStuff;

	//set node ID cause why not?
	for (i = 1; i < sortedEq.size(); i++) {
		sortedEq[i]->setID(i);
	}

	//sort through list and assign latency based on operator
	for (i = 0; i < sortedEq.size(); i++) {
		if (sortedEq[i]->getEqOperator() == "*") { //if given equation is multiplication 
			sortedEq[i]->setEqLatency(2);
		}
		else if (sortedEq[i]->getEqOperator() == "/" || sortedEq[i]->getEqOperator() == "%") {//if given equation is divider/modulo
			sortedEq[i]->setEqLatency(3);
		}
		else {//all other resources
			sortedEq[i]->setEqLatency(1);
		}
	}

	//set reliance
	/*
	for (i = sortedEq.size(); i > 0; i--) {
		for (j = 0; j < sortedEq.size(); j++) {//is this right? can't remember if it's < or <=
			for (k = 0; k < sortedEq[j]->getEqInput().size(); k++) {
				if (sortedEq[i]->getEqOutput() == sortedEq[j]->getEqInput().at(k)) {//does this work?
					sortedEq[i]->pushBackReliance(sortedEq[j]->getEqInput().at(k));
				}
			}
		}
	}
	*/

	for (Equation* i : sortedEq) {
		for (Equation* j : sortedEq) {
			for (std::string k : j->getEqInput()) {
				if (i->getEqOutput() == k) {
					j->pushBackReliance(k);
				}
			}
		}
	}

	//ALAP Sort ------------------------------------------------------------------------------------------------------------
	for (i = sortedEq.size(); i > 0; i--) {
    //for(i = 1; i <= sortedEq.size(); i++){
        if (i == sortedEq.size()) {//condition for first equation
			t = 1;
			sortedEq[i-1]->setALAP(t);
			alapEqList.push_back(sortedEq[i-1]);
		}
		else {
            /*m = alapEqList.size();
            for (j = (alapEqList.size()-1); j >= 0; j--){//for all items in the already sorted list
                for (k = 0; k < alapEqList[j]->getEqInput().size(); k++) { //for all inputs of those items
                    if (sortedEq[i-1]->getEqOutput() == alapEqList[j]->getEqInput().at(k)){//if the output of this eq is the input of that eq
                        t = alapEqList[j]->getALAP() + sortedEq[i-1]->getEqLatency();
                        sortedEq[i-1]->setALAP(t);
                        alapEqList.push_back(sortedEq[i-1]);
                    }
                }
            }
            if(m == alapEqList.size()){
                t = 1;
                sortedEq[i-1]->setALAP(t);
                alapEqList.push_back(sortedEq[i-1]);
            }
        }*/
            
            
			//if equation is in reliance array of already sorted equations update alap
			for (j = 0; j < alapEqList.size(); j++) {//go through already sorted equations
				for (k = 0; k < alapEqList[j]->getEqInput().size(); k++) { //check each equations inputs
					if (sortedEq[i-1]->getEqOutput() == alapEqList[j]->getEqInput().at(k)) { //if the output of the current eqation is an input of a lower equation
                        //if (testFlag == true){ //check if the flag was previously set
                        //}
						//else {
							flag = j; //otherwise mark the flag to reference for the new alap of the current eq
                            testFlag = true;
						//}
					}
				}
			}

			if (testFlag == false) { //if no reliance is found then put eq in lowest level
				t = 1;
				sortedEq[i-1]->setALAP(t);
				alapEqList.push_back(sortedEq[i-1]);
			}
			else {
				t = alapEqList[flag]->getALAP() + sortedEq[i-1]->getEqLatency(); //take the time of the reliant node and the latency of the current node to find it's time
				sortedEq[i-1]->setALAP(t);
				alapEqList.push_back(sortedEq[i-1]);
				if (t > cnt) {
					cnt = t; //updating the largest depth
				}
			}
		}
		flag = 0;
        testFlag = false;
}

	sortedEq = alapEqList;
	//then clear the alapEqList; 
    t = 0;
	for (i = 0; i < sortedEq.size(); i++) { //set alap in the right latency order
		t = sortedEq[i]->getALAP() - 1;
		sortedEq[i]->setALAP((cnt - t));
	}
	//alap portion of ListR completed------------------------------------------------------------------------------------------------------------

	//if global latency request < cnt, send error message about latency
	if (cnt > globalLatency) {
		std::cout << "Latency requested is not achievable with this netlist";
		exit(EXIT_FAILURE);
	}

	//Start ALAP to List-R------------------------------------------------------------------------------------------------------------
	if (cnt < globalLatency) { //check difference between required latency and global latency to shift down for List-R implementation 
		cnt = globalLatency - cnt;
	}

	for (i = 1; i <= globalLatency; i++) {
		//for each variable list, if reliance = null it's ready to go, remove reliance once something has been put on the list. 
		//remember latency (how long each takes) maybe on latency have a "when i = latency time required" remove from reliance lists 
		for (j = 0; j < sortedEq.size(); j++) {//set slack of remaining each time if they're ready
			if (sortedEq[j]->getEqReliance().size() == 0) {
				t = sortedEq[j]->getALAP() - i;
				sortedEq[j]->setSlack(t);
			}
		}
		t = 0;
		m = 0;
		//find the lowest slack
		for (j = 0; j < sortedEq.size(); j++) {
			if (j == 0) t = sortedEq[j]->getSlack();
			else {
				m = sortedEq[j]->getSlack();
				if (m < t) t = m;
			}
		}

		//implement
		flag = 0;
		for (j = 0; j < sortedEq.size(); j++) {
			if (sortedEq[j]->getSlack() == t) {    //if the slack is right
				for (k = 0; k < listREq.size(); k++) {
					if (listREq[k]->getALAP() == i) { //only check the items already sorted in this time scale
						if (sortedEq[j]->getEqLatency() == listREq[k]->getEqLatency()) {
							flag++;
						}
					}
				}
				if (flag == 0) {
					if (sortedEq[j]->getEqLatency() == 3) {
						if (flagLat3 <= 0) {
							sortedEq[j]->setALAP(i);
							listREq.push_back(sortedEq[j]);
							sortedEq[j]->setSortedFlag(true);
							flagLat3 = 3;
						}
					}
					else if (sortedEq[j]->getEqLatency() == 2) {
						if (flagLat2 <= 0) {
							sortedEq[j]->setALAP(i);
							listREq.push_back(sortedEq[j]);
							sortedEq[j]->setSortedFlag(true);
							flagLat2 = 2;
						}
					}
					else {
						sortedEq[j]->setALAP(i);
						listREq.push_back(sortedEq[j]);
						sortedEq[j]->setSortedFlag(true);
					}
				}
                flag = 0;
			}
		}

		for (j = 0; j < sortedEq.size(); j++) {
			for (k = 0; k < listREq.size(); k++) {
				for (m = 0; m < sortedEq[j]->getEqReliance().size(); m++) {
                    if(listREq[k]->getEqOutput() == sortedEq[j]->getEqReliance()[m]){
                        for(int n = 0; n < sortedEq[j]->getEqReliance().size(); n++){
                            if(listREq[k]->getEqOutput() != sortedEq[j]->getEqReliance()[n]){
                                dumb.push_back(sortedEq[j]->getEqReliance()[n]);
                            }
                        }
                        sortedEq[j]->setEqReliance(dumb);
                    }
                    dumb.clear();
				}
			}
		}
		//if this doesn't work, check antonio's code for finding in an object 

		for (j = 0; j < sortedEq.size(); j++) {
			if (sortedEq[j]->getSortedFlag() == true) {
				sortedEq.erase(sortedEq.begin() + j);
			}
		}
		flagLat3--;
		flagLat2--;
	}
    
    if(sortedEq.size() != 0){
        std::cout << "Latency requested is not achievable with this netlist";
        exit(EXIT_FAILURE);
    }
    
	return listREq;
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


