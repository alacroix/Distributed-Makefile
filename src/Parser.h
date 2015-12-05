#ifndef DISTRIBUTED_MAKEFILE_PARSER_H
#define DISTRIBUTED_MAKEFILE_PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <set>
#include <boost/algorithm/string.hpp>

#include "Rule.h"
#include "PathUtils.h"

class Parser {
public:
    Parser(std::string fileName);
    Parser(std::string fileName, std::string master_rule);
    virtual ~Parser();

    std::map<std::string, Rule*> get_rules();
    const std::string get_master_rule();
    std::set<std::string> getFileFaisable();

private:
    void redecoreDico(std::string nom, std::string pere);
    void printFileFaisable();

    std::map<std::string, Rule*> rules;
    std::set<std::string> fileFaisable;
    std::string master_rule;

};

#endif //DISTRIBUTED_MAKEFILE_PARSER_H
