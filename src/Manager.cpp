#include "Manager.h"

Manager::Manager() {}

Manager::Manager(std::string master_rule, std::map<std::string, Rule *> dictionary, QueueDoable *queueDoable) :
        master_rule(master_rule), dictionary(dictionary), queueDoable(queueDoable), currentRank(0) {
    //create_building();
}

std::string Manager::printCurrentThread() {
    mpi::communicator world;

    std::stringstream ss;
    ss << "Process: " << (world.rank() + 1) << "/" << world.size() << " | " << "Thread " <<
    omp_get_thread_num() + 1 << "/" << omp_get_num_threads() << " | ";
    return ss.str();
}

void Manager::create_building() {
    std::string nomRegle;

    while (!queueDoable->empty()) {

        //Ajout d'un étage;
        std::vector<Rule *> floor;
        while (!queueDoable->empty()) {
            nomRegle = queueDoable->popDoable();
            Rule *rule = dictionary[nomRegle];
            floor.push_back(rule);
        }
        //Mise à jour des parents des noeuds de l'etage que l'on vient de rajouter
        for (std::vector<int>::size_type i = 0; i < floor.size(); i++) {
            while (floor.at(i)->have_parents()) {
                std::string nomParent = floor.at(i)->get_parents().at(0);
                Rule *parent = dictionary[nomParent];

                if (dictionary[nomParent] != NULL) {
                    parent->removeChild(floor.at(i)->get_name());
                    floor.at(i)->removeParent(parent->get_name());
                    //Si ce noeud n'a plus de fils,
                    if (!parent->have_childs()) {
                        //std::cout << "Ajout dans la file " << parent->get_name() << std::endl;
                        queueDoable->pushDoable(parent->get_name());
                    }
                }
            }
        }
        building.push_back(floor);
    }

    int i = 1;
    for (std::vector<std::vector<Rule *> >::iterator it1 = building.begin(); it1 != building.end(); ++it1) {
        std::cout << "etage " << i << std::endl;
        for (std::vector<Rule *>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
            std::cout << (*it2)->get_name() << "-";
        }
        std::cout << std::endl;
        i++;
    }
}

void Manager::execute() {
    mpi::communicator world;
    // for each floor
    for (std::vector<std::vector<Rule *> >::iterator it1 = building.begin(); it1 != building.end(); ++it1) {
        // for each rule
        for (std::vector<Rule *>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2) {
            // execute rule if it's our turn
            if (currentRank % world.size() == world.rank()) {
                std::cout << printCurrentThread() << "executing " << (*it2)->get_name() << std::endl;
                (*it2)->execute(dictionary);
                std::cout << printCurrentThread() << "finished " << (*it2)->get_name() << std::endl;
            }
            currentRank++;
        }
        // wait all rules on the current floor to finish
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

void Manager::print() {
    std::cout << dictionary.size() << std::endl;

    typedef std::map<std::string, Rule*>::iterator it_type;
    for(it_type iterator = dictionary.begin(); iterator != dictionary.end(); iterator++) {
        std::cout << iterator->first << std::endl;
        // iterator->first = key
        // iterator->second = value
        // Repeat if you also want to iterate through the second map.
    }
}
