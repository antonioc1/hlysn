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
    std::vector<std::string> inIf;
    std::vector<std::string> inElse;
    ifStatement* nested = NULL;
public:
    ifStatement() {};
    void setCondition(std::string word){condition = word;}
    void setInIf(std::string word){inIf.push_back(word);}
    void setInElse(std::string word){inElse.push_back(word);}
    void setElseStatement(){elseStatement = true;}
    void setNestedIf(ifStatement* nestedpointer){nested = nestedpointer;}

};
//test2

//test
#endif /* ifStatement_hpp */
