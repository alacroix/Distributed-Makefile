#include <iostream>

#include "Parser.h"

using namespace std;

int main() {
    Parser p("../makefiles/premier/Makefile");
    p.printAllRules();
    std::cout << "First rule : " << p.getFirstRule() << std::endl;
    return 0;
}