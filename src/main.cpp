#include <iostream>
#include <vector>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

#include "Parser.h"
#include "Manager.h"

namespace mpi = boost::mpi;

int main(int argc, char **argv) {
    // Initialize the MPI environment
    mpi::environment env(argc, argv);
    mpi::communicator world;

    double startT;
    Parser *p = NULL;

    // get hostname table
    std::vector<std::string> hostnames;
    std::string name = env.processor_name();
    for (int i = 0; i < world.size(); i++) {
        std::string other;
        broadcast(world, (world.rank() == i ? name : other), i);
        hostnames.push_back((world.rank() == i ? name : other));
    }

    // used for MPI splitting
    bool condition = (world.rank() != 0);
    mpi::communicator slaves = world.split((condition) ? 0 : 1);

    // Check args number
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: distributed_makefile <makefile> [target]" << std::endl;
        exit(1);
    }

    // if master
    if (world.rank() == 0) {
        // timer
        startT = omp_get_wtime();

        QueueDoable queue;

        // parse Makefile
        if (argc == 2) {
            p = new Parser(&queue, argv[1]);
        } else {
            p = new Parser(&queue, argv[1], argv[2]);
        }

        // get manager
        Manager m(p->get_master_rule(), p->get_rules(), &queue);
        m.create_building();
        // send manager to slaves
        broadcast(world, m, 0);

        // get absolute path
        std::string cheminPere = get_absolutePath();
        // send absolute path to slaves
        broadcast(world, cheminPere, 0);

    } else {
        Manager m;
        // get manager from master
        broadcast(world, m, 0);
        std::stringstream adressMaster;
        std::string cheminPere;
        // get absolute path from master
        broadcast(world, cheminPere, 0);
        // build master hostname
        adressMaster << "root@" << hostnames[0];
        // execute rules
        m.execute(slaves, adressMaster.str().c_str(), cheminPere);
    }

    // if master
    if (world.rank() == 0) {
        int numberDone = 0;
        // while still work to do
        while (numberDone < (world.size() - 1)) {
            std::string message;
            // get message from any
            world.recv(mpi::any_source, 0, message);
            std::vector<std::string> tokens;
            boost::split(tokens, message, boost::is_any_of(";"));
            int destinataire = atoi(tokens[0].c_str());
            // if work done
            if (tokens[1].compare("done") == 0) {
                std::cout << "Process " << destinataire << " finish all his work" << std::endl;
                numberDone++;
            } else if (tokens[1].compare("file") == 0) { // if slave wants file
                // build command line
                std::stringstream commandSCP;
                commandSCP << "sshpass -p \"admin\" scp -o StrictHostKeyChecking=no " << tokens[2] << " root@" << hostnames.at(destinataire) << ":~";
                // scp to slave
                system(commandSCP.str().c_str());
                std::string ok = "OK";
                world.send(destinataire, 1, ok);
            }
        }
    }

    // Show execution time
    if (world.rank() == 0) {
        delete p;
        std::cout << "Time : " << (omp_get_wtime() - startT) << std::endl;
    }

    return 0;
}