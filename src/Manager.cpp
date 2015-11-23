#include "Manager.h"

Manager::Manager(std::string master_rule, std::map<std::string, Rule *> dictionary) :
        master_rule(master_rule), dictionary(dictionary) {}

void Manager::execute() {
    // Get initial rule
    Rule* initial = dictionary[master_rule];

    execute_rule(initial);
}

void Manager::execute_rule(Rule *rule) {
    // If file already exists, do nothing
    if (rule->alreadyExists()) {
        std::cout << rule->get_name() << " already exists." << std::endl;
        return;
    }

    // If has dependencies, execute them before
    if (rule->has_dependencies()) {
        std::vector<std::string> dependencies = rule->get_dependencies();

        for(std::vector<int>::size_type i = 0; i != dependencies.size(); i++) {
            std::string ds = dependencies.at(i);
            // If dependency is a simple file like a .c (ie not a rule)
            if (dictionary.find(ds) == dictionary.end()) {
                // If file not found, throw exception
                if (!file_exists(ds)) {
                    throw std::runtime_error("File " + ds + " not found");
                }
            } else {
                Rule* d = dictionary[ds];

                if (!d->has_been_executed()) {
                    execute_rule(d);
                }
            }
        }
    }

    // Finally, execute itself
    rule->execute(dictionary);
    std::cout << rule->get_name() << " done." << std::endl;
}
