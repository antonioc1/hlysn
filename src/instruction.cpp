#include "instruction.hpp"

Instruction::Instruction(std::string reg, std::string expression, std::vector<std::string> variables) {
	this->reg = reg;
	this->expression = expression;
	this->variables = variables;
}

std::string Instruction::getReg() {
	return this->reg;
}

std::string Instruction::getExpression() {
	return this->expression;
}

std::vector<std::string> Instruction::getVariables(){
	return this->variables;
}
