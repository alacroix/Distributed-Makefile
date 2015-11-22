#include <iostream>

#include "Parser.h"
#include "Manager.h"

int main(int argc, char **argv) {
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

    return 0;
}