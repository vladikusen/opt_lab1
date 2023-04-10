#ifndef __TABLES_H__
#define __TABLES_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

class TokenAnalyser {
public:
    TokenAnalyser() = default;
    TokenAnalyser(std::string fileName);
    void init();
    void showInitialProgram() { std::cout << initialProgram << std::endl; }
    std::pair<char, int> getChar();
    int idnTabSearch(std::string);
    int kTabSearch(std::string);
    int constTabSearch(std::string);
    void analyze();
private:
    int findMax(std::string);
    enum tokenValues {
        WS,
        CNS,
        IDN,
        DM,
        ERR
    };
    enum keywordTokenValues {
        PROGRAM = 401,
        END,
        LOOP,
        ENDLOOP,
        CASE,
        OF,
        ENDCASE,
        MOD,
        BEGIN
    };
    std::vector<tokenValues> tokens{128, tokenValues::ERR};
    std::map<std::string, keywordTokenValues> kTokens;
    std::map<std::string, int> idnTokens;
    std::map<std::string, int> constTokens;
    std::string initialProgram;
    std::ifstream program;
};

#endif 