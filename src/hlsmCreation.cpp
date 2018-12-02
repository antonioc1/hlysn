//
//  hlsmCreation.cpp
//  hlysn
//
//  Created by Alec Foster on Saturday12/1.
//

#include "hlsmCreation.hpp"

void HLSM::printStates(){
    if (_filename2 != NULL) {
        _outputFile.open(_filename2);
    }
    else {
        std::cout << "Output file not found";
        
        exit(EXIT_FAILURE);
    }
    int bitNumforState = int(log2(latCon)+1);;
    
    _outputFile << "reg ["<< bitNumforState << ":0] state ;\n";
    _outputFile << "parameter stateStart = 0;\n";
    
    for (int i = 1; i <= latCon; i++) {
        _outputFile << "parameter state_"<< i << "= " << i << ";\n";
    }
    _outputFile << "parameter stateFinish = "<< latCon+1 <<";\n\n";

    
    
    _outputFile << "always@ (posedge Clk) begin \n";
    _outputFile << "if (Rst == 1) begin\n";
    _outputFile << "state <= stateStart;\n";
    _outputFile << "end\n\n";
    
    _outputFile << "else begin\n";
    _outputFile << "case( state )\n";
    _outputFile << "stateStart : begin\n";
    _outputFile << "state <= state_1 ;\n";
    _outputFile << "Done <= 0 ;\n";
    _outputFile << "end\n";
    _outputFile << "else begin\n";
    _outputFile << "state <= stateStart ;\n";
    _outputFile << "end\n";
    _outputFile << "end\n";
    
    // write generic case creation here
    
    
    _outputFile << "Final : begin\n";
    _outputFile << "Done <= 1 ;\n";
    _outputFile << "state <= stateStart ;\n";
    _outputFile << "end\n";
    _outputFile << "endcase\n";
    _outputFile << "end\n";
    
    _outputFile << "\n\nend\n";

}
