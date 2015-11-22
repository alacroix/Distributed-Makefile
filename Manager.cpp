#include "Manager.h"

Manager::Manager(std::string master_rule, std::map<std::string, Rule *> dictionary) {
    this->master_rule = master_rule;
    this->dictionary = dictionary;
}

void Manager::execute() {
    // Get initial rule
    Rule* initial = dictionary[master_rule];

    execute_rule(initial);
}

void Manager::execute_rule(Rule *rule) {
    // If has dependencies, execute them before
    if (rule->has_dependencies()) {
        std::vector<std::string> dependencies = rule->get_dependencies();

        for(std::vector<int>::size_type i = 0; i != dependencies.size(); i++) {
            // If dependency is a simple file like a .c
            if (dictionary.find(dependencies.at(i)) == dictionary.end()) {
                // TODO: Check if file exists
            } else {
                Rule* d = dictionary[dependencies.at(i)];

                if (!d->has_been_executed()) {
                    execute_rule(d);
                }
            }
        }
    }

    // Finally, execute itself
    rule->execute(dictionary);
}
