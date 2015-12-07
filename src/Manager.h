#ifndef DISTRIBUTED_MAKEFILE_MANAGER_H
#define DISTRIBUTED_MAKEFILE_MANAGER_H

#include <iostream>
#include <map>
#include <omp.h>
#include <set>

#include <boost/mpi.hpp>
#include <boost/mpi/communicator.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>

#include "Rule.h"
#include "PathUtils.h"
#include "QueueDoable.h"

namespace mpi = boost::mpi;

class Manager {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & master_rule & currentRank;
        ar & queueDoable;
        ar & dictionary;
        ar & building;
    }
public:
    Manager();

    Manager(std::string master_rule, std::map<std::string, Rule *> dictionary, QueueDoable *queueDoable);

    void execute(mpi::communicator slave, std::string masterComputer, std::string cheminPere);
    void create_building();
private:
    std::string master_rule;

    int currentRank;

    QueueDoable *queueDoable;

    std::map<std::string, Rule *> dictionary;
    std::vector<std::vector<Rule *> > building;

    std::string printCurrentThread();
};

#endif //DISTRIBUTED_MAKEFILE_MANAGER_H
