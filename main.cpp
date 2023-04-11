#include <iostream>
#include "analyser.h"

int main() {
    TokenAnalyser t("program.txt");
    t.init();
    t.analyze();
    return 0;
}