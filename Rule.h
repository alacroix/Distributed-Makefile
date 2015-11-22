#ifndef DISTRIBUTED_MAKEFILE_RULE_H
#define DISTRIBUTED_MAKEFILE_RULE_H

#include <iostream>
#include <vector>

class Rule {
public:
    Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies);

    void printRule();

    std::string getName();
    std::vector<std::string> getCmd();
    std::vector<std::string> getDependencies();
private:
    std::string name;
    std::vector<std::string> cmd;
    std::vector<std::string> dependencies;
};

#endif //DISTRIBUTED_MAKEFILE_RULE_H
