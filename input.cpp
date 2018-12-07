#include "input.hpp"

Input::Input(std::string type, std::string size, std::vector<std::string> variables) {
	this->type = type;
	this->size = size;
	this->variables = variables;
}

std::string Input::getType() {
	return this->type;
}

std::vector<std::string> Input::getVariables() {
	return this->variables;
}

std::string Input::getSize() {
	return this->size;
}
//test
