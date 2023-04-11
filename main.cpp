#include <iostream>
#include "analyser.h"
#include "parser.h"

int main() {
    TokenAnalyser t("program.txt");
    t.init();
    t.analyze();
    // std::cout << t.out();

    Parser p;
    p.setTokenString(t.out());
    p.getToken();

    return 0;
}