#include <iostream>
#include <omp.h>
//#include <mpi.h>

#include "Parser.h"
#include "Manager.h"
#include "QueueDoable.h"

int main(int argc, char **argv) {

   // omp_set_dynamic(1);
    double startT = omp_get_wtime();

    // Check args number
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: distributed_makefile <makefile> [target]" << std::endl;
        exit(1);
    }

    QueueDoable *queueDoable = new QueueDoable();

    Parser* p = NULL;
    if (argc == 2) {
        p = new Parser(queueDoable, argv[1]);
    } else {
        p = new Parser(queueDoable, argv[1], argv[2]);
    }

    /*
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    // Find out rank, size
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    */

    Manager m(p->get_master_rule(), p->get_rules(), queueDoable, p->getNumberDoable());
    m.execute();

    delete p;

    std::cout << "Time : " << (omp_get_wtime() - startT) << std::endl;

    return 0;
}