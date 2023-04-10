#include <iostream>
#include "tables.h"

int main() {
    TokenAnalyser t("program.txt");
    t.init();
    // for(int i = 0; i < 5; i++) {
    //     std::cout << t.getChar() << std::endl;
    // } 
    // t.idnTabSearch("variable1");
    // t.idnTabSearch("var2");
    // auto k = t.kTabSearch("PROGRAM");
    // k = t.kTabSearch("LOOP");
    // t.constTabSearch(std::to_string(10));
    // t.constTabSearch(std::to_string(120));
    // t.constTabSearch(std::to_string(120));
    // t.constTabSearch(std::to_string(123));


    t.analyze();
    return 0;
}