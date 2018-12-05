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

void Equation::pushBackReliance(std::string r){
    this->eqReliance.push_back(r);
}

void Equation::setEqRelianceSize(int newRSize){
    this->eqRelianceSize = newRSize;
}

std::vector<Equation::Equation> listRSort(vector<Equation> inputStuff){
    int i = 0;
    int j = 0;
    int k = 0; 
    int t = 0;
    int cnt = 0;
    int flag = 0; 

    vector<Equation::Equation> sortedEq;
    vector<Equation::Equation> alapEqList;
    //clear both sortedEq and alapEqList to prevent pointer issues 

    //sort through list and assign latency based on operator
    for(i ; i<= sortedEq.size(); i++){
        if(sortedEq[i].getEqOperator() == "*"){ //if given equation is multiplication 
            sortedEq[i].setEqLatency(2);
        }
        else if(sortedEq[i].getEqOperator() == "/" || sortedEq[i].getEqOperator() == "%"){//if given equation is divider/modulo
            sortedEq[i].setEqLatency(3);
        }
        else{//all other resources
            sortedEq[i].setEqLatency(1);
        }
    }

    //set reliance 
    for(i = sortedEq.size(); i > 0; i--){
        for(j = 0; j < sortedEq.size(); j++){//is this right? can't remember if it's < or <=
            for(k = 0; k < sortedEq[j].getEqInput().size ; k++){
                if(sortedEq[i].getEqOutput() == sortedEq[j].getEqInput()[k]){//does this work?
                    sortedEq[i].pushBackReliance(sortedEq[j].getEqInput()[k]);
                }        
            }
        }
    }    

    //ALAP (but the times locations will be backwards)
    for(i = sortedEq.size(); i > 0; i--){
        if(i == sortedEq.size()){//condition for first equation 
            t = 1;
            sortedEq[i].setALAP(t);
            alapEqList.push_back(sortedEq[i]);
        }
        else{
            //if equation is in reliance array of already sorted equations update alap
            for(j = 0; j < alapEqList.size(); j++){//go through already sorted equations
                for(k = 0; k < alapEqList[j].getEqInput().size(); k++){ //check each equations inputs
                    if(sortedEq[i].getEqOutput() == alapEqList[j].getEqInput()[k]){ //if the output of the current eqation is an input of a lower equation
                        if(flag > 0); //check if the flag was previously set
                        else{
                            flag = j; //otherwise mark the flag to reference for the new alap of the current eq
                        }
                    }
                }
            }
            if(flag == 0){ //if no reliance is found then put eq in lowest level
                t = 1;
                sortedEq[i].setALAP(t);
                alapEqList.push_back(sortedEq[i]);
            }
            else{
                t = alapEqList[j].getALAP() + sortedEq[i].getEqLatency(); //take the time of the reliant node and the latency of the current node to find it's time
                sortedEq[i].setEqLatency(t);
                alapEqList.push_back(sortedEq[i]);
                if(t > cnt){
                    cnt = t; //updating the largest depth
                }
            }
        }
        flag = 0;
    }

    sortedEq = alapEqList;
    //then clear the alapEqList; 

    for(i = 0; i < sortedEq.size(); i++){ //set alap in the right latency order
        t = sortedEq[i].getALAP() - 1;
        sortedEq[i].setALAP((cnt - t));
    }
    //alap portion of ListR completed

    

    return sortedEq;
}








