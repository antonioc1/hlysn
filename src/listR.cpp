//Colter Ogden
//jcogden

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "listR.hpp"

using namespace std;

Equation::Equation(int iD, int latency, int lap, int lack, std::string out, std::string operate, std::vector<std::string> input, std::vector<std::string> reliance, int relianceSize){
    this->iD = iD;
    this->eqLatency = latency;
    this->aLAP = lap;
    this->slack = lack;
    this->eqOutput = out; 
    this->eqOperator = operate;
    this->eqInput = input;
    this->eqReliance = reliance;
    this->eqRelianceSize = relianceSize;
    this->sortedFlag = false; 
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

int Equation::getSlack(){
    return this->slack;
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

int Equation::getSortedFlag(){
    return this->sortedFlag;
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

void Equation::setSlack(int lap){
    this->slack = lap;
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

void Equation::setSortedFlag(bool sflag){
    this->sortedFlag = sflag;
}

std::vector<Equation::Equation> listRSort(vector<Equation> inputStuff, int globalLatency){
    int i = 0;
    int j = 0;
    int k = 0; 
    int t = 0;
    int m = 0;
    int cnt = 0;
    int flag = 0; 
    vector<int> opLat;

    vector<Equation::Equation> sortedEq;
    vector<Equation> alapEqList;
    vector<Equation> listREq;

    //clear all initiated vectors to prevent pointer issues 
    opLat.clear();
    sortedEq.clear();
    alapEqList.clear();
    listREq.clear();

    //set node ID cause why not?
    for(i = 1; i <= sortedEq.size(); i++){
        sortedEq[i].setID(i);
    }

    //sort through list and assign latency based on operator
    for(i = 0; i < sortedEq.size(); i++){
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
            for(k = 0; k < sortedEq[j].getEqInput().size(); k++){
                if(sortedEq[i].getEqOutput() == sortedEq[j].getEqInput()[k]){//does this work?
                    sortedEq[i].pushBackReliance(sortedEq[j].getEqInput()[k]);
                }        
            }
        }
    }    

    //ALAP Sort ------------------------------------------------------------------------------------------------------------
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
    //alap portion of ListR completed------------------------------------------------------------------------------------------------------------

    //if global latency request < cnt, send error message about latency
    if(globalLatency > cnt){
        cout << "Latency requested is not achievable with this netlist";
        exit(EXIT_FAILURE);
    }

    //Start ALAP to List-R------------------------------------------------------------------------------------------------------------
    if(cnt < globalLatency){ //check difference between required latency and global latency to shift down for List-R implementation 
        cnt = globalLatency - cnt;
    }

    for(i = 1; i <= globalLatency; i++){
        //for each variable list, if reliance = null it's ready to go, remove reliance once something has been put on the list. 
        //remember latency (how long each takes) maybe on latency have a "when i = latency time required" remove from reliance lists 
        for(j = 0; j < sortedEq.size(); j++){//set slack of remaining each time if they're ready
            if(sortedEq[j].getEqReliance().empty()){
                t = sortedEq[j].getALAP() - i;
                sortedEq[j].setSlack(t);
            }
        }
        t = 0; 
        m = 0;
        //find the lowest slack
        for(j=0; j < sortedEq.size(); j++){
            if(j=0)t = sortedEq[j].getSlack();
            else{
                m = sortedEq[j].getSlack();
                if(m < t) t = m; 
            }
        }

        //implement
        flag = 0; 
        for(j = 0; j < sortedEq.size(); j++){
            if(sortedEq[j].getSlack() == t){    //if the slack is right
                if(opLat.empty()){//remember to clear each time
                    sortedEq[j].setALAP(i);
                    listREq.push_back(sortedEq[j]);
                    sortedEq[j].setSortedFlag(true);
                }
                else{
                    for(k = 0; k < listREq.size(); k++){
                        if(listREq[k].getALAP() == i){ //only check the items already sorted in this time scale
                            if(sortedEq[j].getEqLatency() == listREq[k].getEqLatency()){
                                flag++;
                            }
                        }
                    }
                    if(flag == 0){
                        sortedEq[j].setALAP(i);
                        listREq.push_back(sortedEq[j]);
                        sortedEq[j].setSortedFlag(true);
                    }
                }
            }
        }
        //figure out when to remove sorted thing 

        for(j = 0; j < sortedEq.size(); j++){
            for(k = 0; k < listREq.size(); k++){
                for(m = 0; m < sortedEq[j].getEqReliance().size(); m++){
                    auto position = find(sortedEq[j].getEqReliance().begin(), sortedEq[j].getEqReliance().end(), listREq[k].getEqOutput());
                    if(position != sortedEq[j].getEqReliance().end()){
                        sortedEq[j].getEqReliance().erase(position);
                    }
                }
            }
        }
        //if this doesn't work, check antonio's code for finding in an object 

        for(j = 0; j < sortedEq.size(); j++){
            if(sortedEq[j].getSortedFlag() == true){
                sortedEq.erase(sortedEq.begin() + j);
            }
        }
    }

    return listREq;
}








