//
//  hlsmCreation.cpp
//  hlysn
//
//  Created by Alec Foster on Saturday12/1.
//

#include "hlsmCreation.hpp"


void HLSM::printStates(Output *dpgen){
    if (_filename2 != NULL) {
        _outputFile.open(_filename2);
    }
    else {
        std::cout << "Output file not found";
        
        exit(EXIT_FAILURE);
    }
    int bitNumforState = int(log2(latCon)+1);;
    
    _outputFile << "`timescale 1ns / 1ps \n\n\n\n";
    _outputFile << "module HLSM (Clk, Rst, Start, Done, ";
    
    std::vector<std::string> variables = dpgen->getInputsAndOutputs();
    
    for (int i = 0; i < variables.size(); i++) {
        if (i != (variables.size() - 1)) {
            _outputFile << variables[i] + ", ";
        }
        else {
            _outputFile << variables[i];
        }
    }
    
    _outputFile << ");\n\n";
	_outputFile << dpgen->getSizes();
    
    _outputFile << "input Clk, Rst, Start;\n";
    _outputFile << "output reg Done;\n";
    
    for (Input* i : dpgen->getinputs()) {
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
    
    
    
    _outputFile << "reg ["<< bitNumforState << ":0] State, NextState;\n";
    _outputFile << "parameter Wait = 0;\n";
    
    for (int i = 1; i <= latCon; i++) {
        _outputFile << "parameter state_"<< i << "= " << i << ";\n";
    }
    _outputFile << "parameter Final = "<< latCon+1 <<";\n\n";

	_outputFile << "always @(State) begin\n";
	_outputFile << "case(State)\n";
	_outputFile << "Wait: begin\n";
	_outputFile << "if(Start == 1)\n";
	_outputFile << "NextState <= state_1;\n";
	_outputFile << "else if(Start == 0)\n";
	_outputFile << "NextState <= Wait;\n";
	_outputFile << "end\n";
    /*
    _outputFile << "always@ (posedge Clk) begin \n";
    _outputFile << "if (Rst == 1) begin\n";
    for (Input* i : dpgen->getinputs()) {
        std::string size = i->getSize();
    std::vector<std::string> variables = i->getVariables();
    for (int i = 0; i < variables.size(); i++) {
        _outputFile << variables[i] << " <= 0 ;\n";
    }
    }
    _outputFile << "state <= stateStart;\n";
    _outputFile << "end\n\n";
    
    _outputFile << "else begin\n";
    _outputFile << "case( state )\n";
    _outputFile << "stateStart : begin\n";
    _outputFile << "state <= state_1 ;\n";
    _outputFile << "Done <= 0 ;\n";
    _outputFile << "end\n";
    
    // write generic case creation here
    */
    for (int i = 1; i <= latCon; i++) {
        _outputFile << "state_" << i <<" : begin\n";
        // create function to find which thing to print here
		for (int j = 0; j < dpgen->getListRDone().size(); j++) {
			if (i == dpgen->getListRDone().at(j)->getALAP()) {
				_outputFile << dpgen->getListRDone().at(j)->getEqOutput();
				_outputFile << " <= ";
				if (dpgen->getListRDone().at(j)->getEqOperator() != "?") {
					for (int k = 0; k < dpgen->getListRDone().at(j)->getEqInput().size(); k++) {
						if (k == 0) {
							_outputFile << dpgen->getListRDone().at(j)->getEqInput().at(k);
							_outputFile << " ";
							_outputFile << dpgen->getListRDone().at(j)->getEqOperator();
						
						}
						else {
							_outputFile << " " << dpgen->getListRDone().at(j)->getEqInput().at(k);
							_outputFile << ";\n";
						}
					}
				}
				else {
					for (int k = 0; k < dpgen->getListRDone().at(j)->getEqInput().size(); k++) {
						if (k == 0) {
							_outputFile << dpgen->getListRDone().at(j)->getEqInput().at(k);
							_outputFile << " ";
							_outputFile << dpgen->getListRDone().at(j)->getEqOperator();

						}
						else if (k == 1){
							_outputFile << " " << dpgen->getListRDone().at(j)->getEqInput().at(k);
							_outputFile << " :";
						}
						else {
							_outputFile << " " << dpgen->getListRDone().at(j)->getEqInput().at(k);
							_outputFile << ";\n";
						}
					}
				}
			}
		}
        if (i+1 > latCon) {
            _outputFile << "NextState <= Final;\n";
        }
        else{
            _outputFile << "NextState <= state_" << i+1 <<" ;\n";
        }
        _outputFile << "end\n";
    }
    
    
    _outputFile << "Final : begin\n";
    _outputFile << "Done <= 1;\n";
    _outputFile << "state <= Wait;\n";
    _outputFile << "end\n";
    _outputFile << "endcase\n";
    _outputFile << "end\n";

	_outputFile << "always @(posedge Clk) begin\n";
	_outputFile << "if(Rst == 1) begin\n";

	for (Input* i : dpgen->getinputs()) {
		std::vector<std::string> variables = i->getVariables();
		if (i->getType() == "output" || i->getType() == "reg") {
			for (int i = 0; i < variables.size(); i++) {
				_outputFile << variables[i] << " <= 0;\n";
			}
		}
	}
	_outputFile << "Done <= 0;\n";
	_outputFile << "State <= Wait;\n";
	_outputFile << "end\n";
	_outputFile << "else\n";
	_outputFile << "State <= NextState;\n";
	_outputFile << "end\n";
    
    _outputFile << "\n\nendmodule\n";

}
