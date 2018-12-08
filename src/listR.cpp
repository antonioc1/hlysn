//Colter Ogden
//jcogden

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "listR.hpp"

Equation::Equation(int iD, int latency, int lap, int lack, std::string out, std::string operate, std::vector<std::string> input, std::vector<std::string> reliance, int relianceSize, bool sortedFlag) {
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
int Equation::getID() {
	return this->iD;
}

int Equation::getEqLatency() {
	return this->eqLatency;
}

int Equation::getALAP() {
	return this->aLAP;
}

int Equation::getSlack() {
	return this->slack;
}

std::string Equation::getEqOutput() {
	return this->eqOutput;
}

std::string Equation::getEqOperator() {
	return this->eqOperator;
}

std::vector<std::string> Equation::getEqInput() {
	return this->eqInput;
}

std::vector<std::string> Equation::getEqReliance() {
	return this->eqReliance;
}

int Equation::getEqRelianceSize() {
	return this->eqRelianceSize;
}

bool Equation::getSortedFlag() {
	return this->sortedFlag;
}

//setters
void Equation::setID(int newID) {
	this->iD = newID;
}

void Equation::setEqLatency(int newLatency) {
	this->eqLatency = newLatency;
}

void Equation::setALAP(int lap) {
	this->aLAP = lap;
}

void Equation::setSlack(int lap) {
	this->slack = lap;
}

void Equation::setEqOutput(std::string newOutput) {
	this->eqOutput = newOutput;
}

void Equation::setEqOperator(std::string newOp) {
	this->eqOperator = newOp;
}

void Equation::setEqInput(std::vector<std::string> newInput) {
	this->eqInput = newInput;
}

void Equation::setEqReliance(std::vector<std::string> newReliance) {
	this->eqReliance = newReliance;
}

void Equation::pushBackReliance(std::string r) {
	this->eqReliance.push_back(r);
}

void Equation::setEqRelianceSize(int newRSize) {
	this->eqRelianceSize = newRSize;
}

void Equation::clearReliance()
{
	this->eqReliance.clear();
}

void Equation::setSortedFlag(bool sflag) {
	this->sortedFlag = sflag;
}

