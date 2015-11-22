#include <iostream>

#include "Parser.h"
#include "Manager.h"

using namespace std;

int main(int argc, char **argv) {
    Parser p("../makefiles/premier/Makefile-small");

    Manager m(p.getFirstRule(), p.getRules());
    m.execute();

    return 0;
}