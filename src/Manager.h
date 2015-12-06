#ifndef DISTRIBUTED_MAKEFILE_MANAGER_H
#define DISTRIBUTED_MAKEFILE_MANAGER_H

#include <iostream>
#include <map>
#include <omp.h>
#include <set>
#include <mpi.h>

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

    int currentRank;
    int numprocs, rank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    std::string printCurrentThread();

    std::vector<std::vector<Rule *> > building;

    void create_building();
};


#endif //DISTRIBUTED_MAKEFILE_MANAGER_H
