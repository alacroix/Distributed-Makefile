#ifndef DISTRIBUTED_MAKEFILE_PARSER_H
#define DISTRIBUTED_MAKEFILE_PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <set>
#include <queue>
#include <boost/algorithm/string.hpp>
#include <omp.h>

#include "Rule.h"
#include "PathUtils.h"
#include "QueueDoable.h"

class Parser {
public:
    Parser(QueueDoable *queueDoable, std::string fileName);
    Parser(QueueDoable *queueDoable, std::string fileName, std::string master_rule);
    virtual ~Parser();

    std::map<std::string, Rule*> get_rules();
    const std::string get_master_rule();

private:
    void parseFile(std::string fileName);
    void redecoreDico(std::string nom, std::string pere);

    QueueDoable *queueDoable;

    std::map<std::string, Rule*> rules;
    std::string master_rule;
    int numberDoable;

};

#endif //DISTRIBUTED_MAKEFILE_PARSER_H
