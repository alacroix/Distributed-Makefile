#include "Rule.h"

Rule::Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies) {
    this->name = name;
    this->cmd = cmd;
    this->dependencies = dependencies;
    executed = false;
}

void Rule::execute(std::map<std::string, Rule*> dictionary) {
    for(std::vector<int>::size_type i = 0; i != cmd.size(); i++) {
        std::string exec = cmd.at(i).substr(0, cmd.at(i).find(' '));

        // If it's a local rule, add ./
        if (dictionary.find(exec) != dictionary.end()) {
            std::stringstream ss;
            ss << "./" << cmd.at(i).c_str();
            system(ss.str().c_str());
        } else {
            system(cmd.at(i).c_str());
        }
    }

    executed = true;
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

bool Rule::hasDependencies() {
    return (this->dependencies.size() != 0);
}

bool Rule::hasBeenExecuted() {
    return executed;
}
