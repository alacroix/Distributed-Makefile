#ifndef DISTRIBUTED_MAKEFILE_MANAGER_H
#define DISTRIBUTED_MAKEFILE_MANAGER_H

#include <iostream>
#include <map>

#include "Rule.h"


class Manager {
public:
    Manager(std::string firstRule, std::map<std::string, Rule*> dictionary);

    void execute();
private:
    std::string firstRule;
    std::map<std::string, Rule*> dictionary;

    void executeRule(Rule* rule);
};


#endif //DISTRIBUTED_MAKEFILE_MANAGER_H
