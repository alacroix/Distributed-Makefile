#ifndef DISTRIBUTED_MAKEFILE_PARSER_H
#define DISTRIBUTED_MAKEFILE_PARSER_H

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <boost/algorithm/string.hpp>

#include "Rule.h"
#include "PathUtils.h"

using namespace std;

class Parser {
public:
    Parser(string fileName);
    virtual ~Parser();

    map<string, Rule*> getRules();
    const string getFirstRule();
private:
    map<string, Rule*> rules;
    string firstRule;
};

#endif //DISTRIBUTED_MAKEFILE_PARSER_H
