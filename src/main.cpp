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
    Parser *p = nullptr;

    // if master
    if (world.rank() == 0) {
        // timer
        startT = omp_get_wtime();

        // Check args number
        if (argc < 2 || argc > 3) {
            std::cerr << "usage: distributed_makefile <makefile> [target]" << std::endl;
            exit(1);
        }

        QueueDoable queue;

        //Parse Makefile
        if (argc == 2) {
            p = new Parser(&queue, argv[1]);
        } else {
            p = new Parser(&queue, argv[1], argv[2]);
        }

        Manager m(p->get_master_rule(), p->get_rules(), &queue);
        m.create_building();

        broadcast(world, m, 0);
    } else {
        Manager m;
        broadcast(world, m, 0);
    }

    // Show execution time
    if (world.rank() == 0) {
        delete p;
        std::cout << "Time : " << (omp_get_wtime() - startT) << std::endl;
    }

    /*




    // if master
    if(world.rank() == 0) {


        QueueDoable *queueDoable = new QueueDoable();



        Manager m(p->get_master_rule(), p->get_rules(), queueDoable);
        //m.create_building();

        m.print();
        // send to slaves
        // broadcast(world, m, 0);
    } else { //slaves
        Manager m;
        //broadcast(world, m, 0);
        //m.print();
        //m.execute();
    }

    //Synchronize all machine to get ready for the execution
    MPI_Barrier(MPI_COMM_WORLD);

    if(world.rank() == 0) {
        int nb_slave_done = 0;
        while(nb_slave_done < numprocs -1) {
            int m = MPI_Receiv();
            switch(m) {
                case MSG_DONE : nb_slave_done++;
                    break;
                case MSG_RULE_REQUEST: ;
                    break;
                default : ;
            }
        }
    } else {


    }


    // Show execution time
    if (world.rank() == 0) {
        delete p;
        std::cout << "Time : " << (omp_get_wtime() - startT) << std::endl;
    }
    */

    return 0;
}