#ifndef DISTRIBUTED_MAKEFILE_MANAGER_H
#define DISTRIBUTED_MAKEFILE_MANAGER_H

#include <iostream>
#include <map>

#include "Rule.h"


class Manager {
public:
    Manager(std::string master_rule, std::map<std::string, Rule*> dictionary);

    void execute();
private:
    std::string master_rule;
    std::map<std::string, Rule*> dictionary;

    void execute_rule(Rule *rule);
};


#endif //DISTRIBUTED_MAKEFILE_MANAGER_H
