#ifndef DISTRIBUTED_MAKEFILE_RULE_H
#define DISTRIBUTED_MAKEFILE_RULE_H

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <sstream>

#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/mpi.hpp>
#include <boost/mpi/communicator.hpp>

#include "PathUtils.h"

namespace mpi = boost::mpi;

class Rule {
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & name;
        ar & cmd;
        ar & dependencies;
        ar & childs;
        ar & parents;
        ar & executed;
    }
public:
    Rule();

    Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies);

    void execute(std::map<std::string, Rule*> dictionary, std::string  masterComputer);

    std::string get_name();
    std::vector<std::string> get_cmd();
    std::vector<std::string> get_dependencies();
    std::vector<std::string> get_parents();

    void addParent(std::string pereName);
    void addChild(std::string childName);
    void removeChild(std::string childName);
    void removeParent(std::string parentName);

    void printRule();

    bool have_childs();
    bool have_parents();
    bool toExecute;
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
