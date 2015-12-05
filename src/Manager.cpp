#include "Manager.h"

Manager::Manager(std::string master_rule, std::map<std::string, Rule *> dictionary, std::set<std::string> fileFaisable)
        :
        master_rule(master_rule), dictionary(dictionary), fileFaisable(fileFaisable) { }

std::string printCurrentThread() {
    std::stringstream ss;
    ss << "Thread " << omp_get_thread_num() + 1 << "/" << omp_get_num_threads() << " | ";
    return ss.str();
}

void Manager::execute() {

    std::set<std::string>::iterator it;

    while (!fileFaisable.empty()) {
        it = fileFaisable.begin();
        std::string nomRegle = *it;
        Rule *rule = dictionary[nomRegle];

        rule->execute(dictionary);

        //On supprime cette dépendances des parents, car elle est faite
        for (std::vector<int>::size_type i = 0; i < rule->get_parents().size(); i++) {
            std::string nomParent = rule->get_parents().at(i);

            Rule *parent = dictionary[nomParent];
            if (dictionary[nomParent] != NULL) {
                parent->removeChild(rule->get_name());
                //Si ce noeud n'a plus de fils,
                if (!parent->have_childs()) {
                    std::cout << "Ajout dans la file " << parent->get_name() << std::endl;
                    fileFaisable.insert(parent->get_name());
                }
            }
        }
        std::cout << "Suppression de la file " << *it << std::endl;
        fileFaisable.erase(it);
    }

/*
	// If has dependencies, execute them before
	if (rule->has_dependencies()) {
		std::vector<std::string> dependencies = rule->get_dependencies();
		#pragma omp parallel shared(dependencies)
		{
			#pragma omp for nowait
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
						std::cout << printCurrentThread() << "executing " << ds << std::endl;
						execute_rule(d);
					}
				}
			}
		}
	}

	// Finally, execute itself
	rule->execute(dictionary);
	#pragma omp critical
	std::cout << printCurrentThread() << rule->get_name() << " done." << std::endl;

 */
}
