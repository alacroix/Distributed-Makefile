#ifndef DISTRIBUTED_MAKEFILE_MANAGER_H
#define DISTRIBUTED_MAKEFILE_MANAGER_H

#include <iostream>
#include <map>
#include <omp.h>

#include "Rule.h"
#include "PathUtils.h"


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
