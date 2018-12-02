//
//  ifStatement.hpp
//  hlysn
//
//  Created by Alec Foster on Sunday12/2.
//

#ifndef ifStatement_hpp
#define ifStatement_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

class ifStatement {
private:
    std::string condition;
    bool elseStatement = false;
    std::string inIf;
    std::string inElse;
public:
    ifStatement() {};
    ifStatement(std::string word, std::string inIfState) : condition(word), inIf(inIfState) {};
    ifStatement(std::string word,std::string inIfState, bool elsestate, std::string inElseState) : condition(word), inIf(inIfState), elseStatement(elsestate), inElse(inIfState) {};
};


#endif /* ifStatement_hpp */
