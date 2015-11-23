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

    bool has_dependencies();
    bool has_been_executed();
    bool alreadyExists();
private:
    std::string name;
    std::vector<std::string> cmd;
    std::vector<std::string> dependencies;
    bool executed;
};

#endif //DISTRIBUTED_MAKEFILE_RULE_H
