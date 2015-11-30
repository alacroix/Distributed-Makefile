#include "Rule.h"

Rule::Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies) :
        name(name), cmd(cmd), dependencies(dependencies), executed(false) {}

void Rule::execute(std::map<std::string, Rule*> dictionary) {
    for(std::vector<int>::size_type i = 0; i != cmd.size(); i++) {
        std::string exec = cmd.at(i).substr(0, cmd.at(i).find(' '));

        // If it's a local rule or existing file, add ./
        if (dictionary.find(exec) != dictionary.end() || file_exists(exec)) {
            std::stringstream ss;
            ss << "./" << cmd.at(i).c_str();
            system(ss.str().c_str());
        } else {
            system(cmd.at(i).c_str());
        }
    }
    executed = true;
}

std::string Rule::get_name() {
    return this->name;
}

std::vector<std::string> Rule::get_cmd() {
    return this->cmd;
}

std::vector<std::string> Rule::get_dependencies() {
    return this->dependencies;
}

bool Rule::has_dependencies() {
    return (this->dependencies.size() != 0);
}

bool Rule::has_been_executed() {
    return executed;
}

bool Rule::alreadyExists() {
    return file_exists(name);
}
