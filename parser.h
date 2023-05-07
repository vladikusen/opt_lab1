#ifndef __PARSER_H__
#define __PARSER_H__
//program
#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <memory>
#include "analyser.h"

struct tokenInfo;
class Parser {
public:
    Parser() = default;
    ~Parser() = default;
    void program();
    void statementsList();
    void statement();
    void procedureIdentifier();
    void blockIdentifier();
    void expression();
    void multiplier();
    void multipliersList();
    void multiplicationInstruction();
    void altlist();
    void alternative();
    void parse();
public:
    int getToken();
    void setTokens(std::string tokens_);
    void setTokens(std::queue<int> tokens_);

    void setKTokens(std::map<std::string, keywordTokenValues> kTokens_) {
        kTokens = kTokens_;
    }
    void setIdnTokens(std::map<std::string, int> idnTokens_) {
        idnTokens = idnTokens_;
    }
    void setConstTokens(std::map<std::string, int> constTokens_) {
        constTokens = constTokens_;
    }
private:
    std::queue<int> tokens;
    std::istringstream tokenString;
    std::map<std::string, keywordTokenValues> kTokens;
    std::map<std::string, int> idnTokens;
    std::map<std::string, int> constTokens;
    int ts;
};

#endif