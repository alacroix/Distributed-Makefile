#include <iostream>
#include <omp.h>

#include "Parser.h"
#include "Manager.h"

int main(int argc, char **argv) {

    omp_set_dynamic(1);
    double startT = omp_get_wtime();

    // Check args number
    if (argc < 2 || argc > 3) {
        std::cerr << "usage: distributed_makefile <makefile> [target]" << std::endl;
        exit(1);
    }

    Parser* p = NULL;
    if (argc == 2) {
        p = new Parser(argv[1]);
    } else {
        p = new Parser(argv[1], argv[2]);
    }

    Manager m(p->get_master_rule(), p->get_rules());
    m.execute();

    delete p;

    std::cout << "Time : " << (omp_get_wtime() - startT) << std::endl;

    return 0;
}