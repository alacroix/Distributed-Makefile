#include <iostream>
#include <omp.h>

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

#include "Parser.h"
#include "Manager.h"
#include "QueueDoable.h"

namespace mpi = boost::mpi;

int main(int argc, char **argv) {
/*
    // timer
    double startT = omp_get_wtime();

    // Check args number
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: distributed_makefile <makefile> [target]" << std::endl;
        exit(1);
    }
*/

    mpi::environment env;
    mpi::communicator world;


    bool is_generator = (world.rank() != 0);
    mpi::communicator slaves = world.split((is_generator) ? 0 : 1);
    std::cout << "Nombre de slaves " << slaves.size() << std::endl;

    std::cout << "source : " << mpi::environment::processor_name() << std::endl;
    std::cout << "I am process " << world.rank() << " of " << world.size() << "." << std::endl;

    QueueDoable *queueDoable = new QueueDoable();

    Parser *p = NULL;
    if (argc == 2) {
        p = new Parser(queueDoable, argv[1]);
    } else {
        p = new Parser(queueDoable, argv[1], argv[2]);
    }

    Manager m(p->get_master_rule(), p->get_rules(), queueDoable, p->getNumberDoable());


    if (world.rank() != 0) {
        m.execute(slaves);
    }
    delete p;


    if (world.rank() == 0) {
        int numberDone = 0;
        while (numberDone < (world.size() - 1)) {
            std::string message;
            world.recv(mpi::any_source, 0, message);
            std::cout << "master recoit : " << message << std::endl;
            std::vector<std::string> tokens;
            boost::split(tokens, message, boost::is_any_of(";"));
            //Faire le scp
            int destinataire = atoi(tokens[0].c_str());

            if (tokens[1].compare("done") == 0) {
                std::cout << "Process " << destinataire << " finish all his work" << std::endl;
                numberDone++;
            } else if (tokens[1].compare("file") == 0) {
                std::cout << "master envoit : OK à " << destinataire << std::endl;
                std::string ok = "OK";
                world.send(destinataire, 1, ok);
            }
        }
    }

/*
    boost::mpi::environment env;
    boost::mpi::communicator world;
    mpi::communicator local = world.split((world.rank() > 1) ? 1 : 0);
    std::string s;
    if (world.rank() == 0)
        s = "Hello, world!";
    boost::mpi::broadcast(local, s, 0);
    std::cout << world.rank() << ": " << s << '\n';

    */
    return 0;
}