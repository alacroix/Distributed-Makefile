#include <iostream>

#include "Parser.h"
#include "Manager.h"

int main(int argc, char **argv) {
    Parser p("../makefiles/premier/Makefile-small");

    Manager m(p.get_master_rule(), p.get_rules());
    m.execute();

    return 0;
}