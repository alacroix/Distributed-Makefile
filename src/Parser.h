#ifndef DISTRIBUTED_MAKEFILE_PARSER_H
#define DISTRIBUTED_MAKEFILE_PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
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
private:
    std::map<std::string, Rule*> rules;
    std::string master_rule;
};

#endif //DISTRIBUTED_MAKEFILE_PARSER_H
