#include "Rule.h"

Rule::Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies) {
    this->name = name;
    this->cmd = cmd;
    this->dependencies = dependencies;
}

void Rule::printRule() {
    // Name
    std::cout << "Name = " << this->name << std::endl;
    // Dependencies
    std::cout << "Dependencies : " << std::endl;
    for(std::vector<int>::size_type i = 0; i != dependencies.size(); i++) {
        std::cout << dependencies.at(i) << std::endl;
    }
    // Commands
    std::cout << "Commands : " << std::endl;
    for(std::vector<int>::size_type i = 0; i != cmd.size(); i++) {
        std::cout << cmd.at(i) << std::endl;
    }
}

std::string Rule::getName() {
    return this->name;
}

std::vector<std::string> Rule::getCmd() {
    return this->cmd;
}

std::vector<std::string> Rule::getDependencies() {
    return this->dependencies;
}