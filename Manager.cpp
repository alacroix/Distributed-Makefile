#include "Manager.h"

Manager::Manager(std::string firstRule, std::map<std::string, Rule *> dictionary) {
    this->firstRule = firstRule;
    this->dictionary = dictionary;
}

void Manager::execute() {
    // Get initial rule
    Rule* initial = dictionary[firstRule];

    executeRule(initial);
}

void Manager::executeRule(Rule *rule) {
    // If has dependencies, execute them before
    if (rule->hasDependencies()) {
        std::vector<std::string> dependencies = rule->getDependencies();

        for(std::vector<int>::size_type i = 0; i != dependencies.size(); i++) {
            // If dependency is a simple file like a .c
            if (dictionary.find(dependencies.at(i)) == dictionary.end()) {
                // TODO: Check if file exists
            } else {
                Rule* d = dictionary[dependencies.at(i)];

                if (!d->hasBeenExecuted()) {
                    executeRule(d);
                }
            }
        }
    }

    // Finally, execute itself
    rule->execute(dictionary);
}
