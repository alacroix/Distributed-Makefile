#include "Parser.h"

Parser::Parser(string fileName) {
    // I/O variables
    string line;
    ifstream myfile;

    // Open file
    myfile.open((char*) fileName.c_str());

    // Get parent path
    chdir(getParentPath(fileName).c_str());

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            //To skip blank lines
            boost::trim(line);
            if (line == "") {
                continue;
            }

            // Rule attributes
            string name;
            vector<string> dependencies;
            vector<string> commands;

            vector<string> tokens;

            // Store name and dependencies
            boost::split(tokens, line, boost::is_any_of(" :"));
            for (size_t i = 0; i < tokens.size(); i++) {
                boost::trim(tokens[i]);
                if (i == 0) {
                    name = tokens[i];
                } else {
                    // If rule has dependencies
                    if (tokens[i] != "") {
                        dependencies.push_back(tokens[i]);
                    }
                }
            }

            // Store commands
            while (getline(myfile, line)) {
                bool goNextLine = false;

                boost::split(tokens, line, boost::is_any_of("\n;"));
                for (size_t i = 0; i < tokens.size(); i++) {
                    boost::trim(tokens[i]);
                    if (tokens[i] == "\\") {
                        goNextLine = true;
                    } else {
                        if (tokens[i] != "") {
                            commands.push_back(tokens[i]);
                        }
                    }
                }
                if (!goNextLine) {
                    break;
                }
            }

            // If it's the first rule encountered
            if (firstRule == "") {
                firstRule = name;
            }

            // Store the new rule in the rules map
            rules[name] = new Rule(name, commands, dependencies);
        }

        // Parsing done, closing file
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
}

Parser::~Parser() {
    for (map<string,Rule*>::iterator it = rules.begin(); it != rules.end(); ++it) {
        delete it->second;
    }
}

map<string, Rule*> Parser::getRules() {
    return rules;
}

const string Parser::getFirstRule() {
    return firstRule;
}

void Parser::printAllRules() {
    for (map<string,Rule*>::iterator it = rules.begin(); it != rules.end(); ++it) {
        it->second->printRule();
    }
}
