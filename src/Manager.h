#ifndef DISTRIBUTED_MAKEFILE_MANAGER_H
#define DISTRIBUTED_MAKEFILE_MANAGER_H

#include <iostream>
#include <map>
#include <omp.h>
#include <set>

#include "Rule.h"
#include "PathUtils.h"
#include "QueueDoable.h"

class Manager {
public:
    Manager(std::string master_rule, std::map<std::string, Rule*> dictionary, QueueDoable *queueDoable, int nbrRules);

    void execute();
private:
    std::string master_rule;
    std::map<std::string, Rule*> dictionary;
    QueueDoable *queueDoable;
    int nbrRules;

    void execute_rule(Rule *rule);
};


#endif //DISTRIBUTED_MAKEFILE_MANAGER_H
