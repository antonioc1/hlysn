#include <iostream>
#include <cstring>
#include <vector>
#include "listR.hpp"

using namespace std;

Equation::Equation(int iD, int latency, int lap, std::string operate, std::vector<std::string> input, std::vector<std::string> reliance, int relianceSize){
    this->iD = iD;
    this->eqLatency = latency;
    this->aLAP = lap;
    this->eqOperator = operate;
    this->eqInput = input;
    this->eqReliance = reliance;
    this->eqRelianceSize = relianceSize;
}

//getters
int Equation::getID(){
    return this->iD;
}

int Equation::getEqLatency(){
    return this->eqLatency;
}

int Equation::getALAP(){
    return this->aLAP;
}

std::string Equation::getEqOutput(){
    return this->eqOutput;
}

std::string Equation::getEqOperator(){
    return this->eqOperator;
}

std::vector<std::string> Equation::getEqInput(){
    return this->eqInput;
}

std::vector<std::string> Equation::getEqReliance(){
    return this->eqReliance;
}

int Equation::getEqRelianceSize(){
    return this->eqRelianceSize;
}

//setters
void Equation::setID(int newID){
    this->iD = newID;
}

void Equation::setEqLatency(int newLatency){
    this->eqLatency = newLatency;
}

void Equation::setALAP(int lap){
    this->aLAP = lap;
}

void Equation::setEqOutput(std::string newOutput){
    this->eqOutput = newOutput;
}

void Equation::setEqOperator(std::string newOp){
    this->eqOperator = newOp;
}

void Equation::setEqInput(std::vector<std::string> newInput){
    this->eqInput = newInput;
}

void Equation::setEqReliance(std::vector<std::string> newReliance){
    this->eqReliance = newReliance;
}

void Equation::setEqRelianceSize(int newRSize){
    this->eqRelianceSize = newRSize;
}

std::vector<Equation::Equation> listRSort(vector<Equation> inputStuff){
    vector<Equation::Equation> sortedEq;


    //sort through list and assign latency based on operator
    //ALAP



    return sortedEq;
}








