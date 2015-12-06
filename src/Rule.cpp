#include "Rule.h"

Rule::Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies) :
        name(name), cmd(cmd), dependencies(dependencies), executed(false), toExecute(false) {}

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

void Rule::addParent(std::string pereName) {
    //std::cout << name << " : Add pere : " << pereName << std::endl;
    this->parents.push_back(pereName);
}

void Rule::addChild(std::string childName) {
    //std::cout << name << " : Add child : " << childName << std::endl;
    this->childs.push_back(childName);
}

std::vector<std::string> Rule::get_parents() {
    return parents;
}

void Rule::removeChild(std::string childName) {
    for( std::vector<std::string>::iterator iter = childs.begin(); iter != childs.end(); ++iter )
    {
        if(childName.compare(*iter) == 0)
        {
            childs.erase(iter);
            break;
        }
    }
}

void Rule::removeParent(std::string parentName) {
    for( std::vector<std::string>::iterator iter = parents.begin(); iter != parents.end(); ++iter )
    {
        if(parentName.compare(*iter) == 0)
        {
            parents.erase(iter);
            break;
        }
    }
}

bool Rule::have_childs() {
    //std::cout << "Nombre fils : " << childs.size() << std::endl;
    return childs.size() != 0;
}

bool Rule::have_parents() {
    return parents.size() != 0;
}

void Rule::printRule() {
    for( std::vector<std::string>::iterator iter = childs.begin(); iter != childs.end(); ++iter )
    {
        std::cout << *iter << std::endl;
    }
    for( std::vector<std::string>::iterator iter = parents.begin(); iter != parents.end(); ++iter )
    {
        std::cout << *iter << std::endl;
    }
}