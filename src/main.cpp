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
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // timer
    double startT = omp_get_wtime();

    // Check args number
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: distributed_makefile <makefile> [target]" << std::endl;
        exit(1);
    }

    QueueDoable *queueDoable = new QueueDoable();

    Parser *p = NULL;
    if (argc == 2) {
        p = new Parser(queueDoable, argv[1]);
    } else {
        p = new Parser(queueDoable, argv[1], argv[2]);
    }

    Manager m(p->get_master_rule(), p->get_rules(), queueDoable, p->getNumberDoable());

    m.execute();

    delete p;

    // Show execution time
    if (world_rank == 0) {
        std::cout << "Time : " << (omp_get_wtime() - startT) << std::endl;
    }

    MPI_Finalize();
     */

    mpi::environment env;
    mpi::communicator world;
    std::cout << "source : " << mpi::environment::processor_name() << std::endl;
    std::cout << "I am process " << world.rank() << " of " << world.size() << "." << std::endl;

    return 0;
}