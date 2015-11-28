#include "Parser.h"

Parser::Parser(std::string fileName) : Parser(fileName, "") {}

Parser::Parser(std::string fileName, std::string master_rule) : master_rule(master_rule) {
    // I/O variables
    std::string line;
    std::ifstream myfile;

    // Open file
    myfile.open((char*) fileName.c_str());

    // Switch to parent path
    chdir(parent_path(fileName).c_str());

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            //To skip blank lines
            boost::trim(line);
            if (line.compare("") == 0 || line.at(0) == '#') {
                continue;
            }

            // Rule attributes
            std::string name;
            std::vector<std::string> dependencies;
            std::vector<std::string> commands;

            std::vector<std::string> tokens;

            // Store name and dependencies
            boost::split(tokens, line, boost::is_any_of(" :"));
            for (size_t i = 0; i < tokens.size(); i++) {
                boost::trim(tokens[i]);
                if (i == 0) {
                    name = tokens[i];
                } else {
                    // If rule has dependencies
                    if (tokens[i].compare("") != 0) {
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
                    if (tokens[i].compare("\\") == 0) {
                        goNextLine = true;
                    } else {
                        if (tokens[i].compare("") != 0) {
                            commands.push_back(tokens[i]);
                        }
                    }
                }
                if (!goNextLine) {
                    break;
                }
            }

            // If it's the first rule encountered
            if (this->master_rule.compare("") == 0) {
                this->master_rule = name;
            }

            // Store the new rule in the rules map
            rules[name] = new Rule(name, commands, dependencies);
        }

        // Parsing done, closing file
        myfile.close();
    } else {
        // Parsing done, closing file
        myfile.close();

        throw std::runtime_error("Could not open file");
    }
}

Parser::~Parser() {
    for (std::map<std::string,Rule*>::iterator it = rules.begin(); it != rules.end(); ++it) {
        delete it->second;
    }
}

std::map<std::string, Rule*> Parser::get_rules() {
    return rules;
}

const std::string Parser::get_master_rule() {
    return master_rule;
}
