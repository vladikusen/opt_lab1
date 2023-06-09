#ifndef __ANALYSER_H__
#define __ANALYSER_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <queue>

enum tokenValues {
    WS,
    CNS,
    IDN,
    DM1,
    DM2,
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

struct tokenInfo {
    tokenInfo(int row_, int column_, int token_, std::string& value_) : row(row_), column(column_), token(token_), value(value_) {}
    int row;
    int column;
    int token;
    std::string value;
};

class TokenAnalyser {
public:
    TokenAnalyser() = default;
    TokenAnalyser(std::string fileName);
    void init();
    std::pair<char, int> getChar();
    void writeToken(std::string token, int tokenCode, bool delimiter = false);
    void writeError(std::string);
    int idnTabSearch(std::string);
    int kTabSearch(std::string);
    int constTabSearch(std::string);
    void analyze();
    std::string out();
    std::queue<int> getTokens();
    std::map<std::string, keywordTokenValues> getkTokens() {
        return kTokens;
    }
    std::map<std::string, int> getIdnTokens() {
        return idnTokens;
    }
    std::map<std::string, int> getConstTokens() {
        return constTokens;
    }
private:
    int findMax(std::string);

    std::vector<tokenValues> tokens{128, tokenValues::ERR};
    std::map<std::string, keywordTokenValues> kTokens;
    std::map<std::string, int> idnTokens;
    std::map<std::string, int> constTokens;
    std::string initialProgram;
    std::ifstream program;
    std::ofstream outProgram;
    std::string outStringProgram;
    int row;
    int column;
    std::queue<int> outTokens;
};

#endif 