#ifndef DISTRIBUTED_MAKEFILE_RULE_H
#define DISTRIBUTED_MAKEFILE_RULE_H

#include <iostream>
#include <vector>
#include <map>
#include <sstream>

class Rule {
public:
    Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies);

    void execute(std::map<std::string, Rule*> dictionary);

    std::string getName();
    std::vector<std::string> getCmd();
    std::vector<std::string> getDependencies();

    bool hasDependencies();
    bool hasBeenExecuted();
private:
    std::string name;
    std::vector<std::string> cmd;
    std::vector<std::string> dependencies;
    bool executed;
};

#endif //DISTRIBUTED_MAKEFILE_RULE_H
