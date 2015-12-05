#ifndef DISTRIBUTED_MAKEFILE_RULE_H
#define DISTRIBUTED_MAKEFILE_RULE_H

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

#include "PathUtils.h"

class Rule {
public:
    Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies);

    void execute(std::map<std::string, Rule*> dictionary);

    std::string get_name();
    std::vector<std::string> get_cmd();
    std::vector<std::string> get_dependencies();
    std::vector<std::string> get_parents();

    void addParent(std::string pereName);
    void addChild(std::string childName);
    void removeChild(std::string childName);

    void printRule();

    bool have_childs();
    bool has_dependencies();
    bool has_been_executed();
    bool alreadyExists();
private:
    std::string name;
    std::vector<std::string> cmd;
    std::vector<std::string> dependencies;
    std::vector<std::string> childs;
    std::vector<std::string> parents;
    bool executed;
};

#endif //DISTRIBUTED_MAKEFILE_RULE_H
