#include <iostream>
#include "analyser.h"
#include "parser.h"

int main() {
    TokenAnalyser* t = new TokenAnalyser("program.txt");
    t->init();
    t->analyze();
    // std::cout << t->out();

    Parser* p = new Parser();
    // p->setTokens(t->out());
    p->setTokens(t->getTokens());
    p->setIdnTokens(t->getIdnTokens());
    p->setConstTokens(t->getConstTokens());
    p->setKTokens(t->getkTokens());
    // p->getToken();
    // p->getToken();
    p->parse();


    return 0;
}