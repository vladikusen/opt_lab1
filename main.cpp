#include <iostream>
#include "analyser.h"
#include "parser.h"

int main() {
    TokenAnalyser* t = new TokenAnalyser("program.txt");
    t->init();
    t->analyze();
    // std::cout << t.out();

    Parser* p = new Parser();
    p->setTokens(t->getTokens());
    p->getToken();
    p->getToken();


    return 0;
}