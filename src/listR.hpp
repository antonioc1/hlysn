//Colter Ogden
//jcogden

#ifndef LISTR_H
#define LISTR_H

#include <stdio.h>
#include <vector>
#include <fstream>
#include <istream>
#include <sstream>
#include <iostream>
#include <algorithm>

class Equation {
    private:
        int iD;
        int eqLatency; 
        int aLAP;
        int slack;
        std::string eqOutput;
        std::string eqOperator;
        std::vector<std::string> eqInput;
        std::vector<std::string> eqReliance;
        int eqRelianceSize; 
    public:
        Equation(int iD, int latency, int lap, int lack, std::string operate, std::vector<std::string> input, std::vector<std::string> reliance, int relianceSize);
        //getters
        int getID();
        int getEqLatency();
        int getALAP();
        int getSlack();
        std::string getEqOutput();
        std::string getEqOperator();
        std::vector<std::string> getEqInput();
        std::vector<std::string> getEqReliance();
        int getEqRelianceSize();
        //setters
        void setID(int newID);
        void setEqLatency(int newLatency);
        void setALAP(int lap);
        void setSlack(int lap);
        void setEqOutput(std::string newOutput);
        void setEqOperator(std::string newOp);
        void setEqInput(std::vector<std::string> newInput);
        void setEqReliance(std::vector<std::string> newReliance);
        void setEqRelianceSize(int newRSize);

        void Equation::pushBackReliance(std::string r);

        //listR
        std::vector<Equation> listRSort(std::vector<Equation> inputStuff, int globalLatency);

};       

#endif