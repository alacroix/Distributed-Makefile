#include "Manager.h"

Manager::Manager(std::string master_rule, std::map<std::string, Rule *> dictionary) :
        master_rule(master_rule), dictionary(dictionary) {}

void Manager::execute() {
    // Get initial rule
    Rule* initial = dictionary[master_rule];

    execute_rule(initial);
}

std::string printCurrentThread() {
    std::stringstream ss;
    ss << "Thread " << omp_get_thread_num() + 1 << "/" << omp_get_num_threads() << " | ";
    return ss.str();
}

void Manager::execute_rule(Rule *rule) {
    // If file already exists, do nothing
    if (rule->alreadyExists()) {
#pragma omp critical
        std::cout << printCurrentThread() << rule->get_name() << " already exists." << std::endl;
        return;
    }

    // If has dependencies, execute them before
    if (rule->has_dependencies()) {
        std::vector<std::string> dependencies = rule->get_dependencies();
#pragma omp parallel shared(dependencies)
        {
#pragma omp for
            for (std::vector<int>::size_type i = 0; i < dependencies.size(); i++) {
                std::string ds = dependencies.at(i);

                // If dependency is a simple file like a .c (ie not a rule)
                if (dictionary.find(ds) == dictionary.end()) {
                    // If file not found, throw exception
                    if (!file_exists(ds)) {
                        throw std::runtime_error("File " + ds + " not found");
                    }
                } else {
                    Rule *d = dictionary[ds];
                    if (!d->has_been_executed()) {
#pragma omp critical
                        {
                            std::cout << printCurrentThread() << "executing " << ds << std::endl;
                        }
                        execute_rule(d);
                    }
                }
            }
#pragma omp barrier
        }
    }

    // Finally, execute itself
    rule->execute(dictionary);
    std::cout << printCurrentThread() << rule->get_name() << " done." << std::endl;
}
