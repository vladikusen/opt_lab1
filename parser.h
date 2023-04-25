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
public:
    int getToken();
    void setTokens(std::queue<tokenInfo> tokens_);

private:
    std::unique_ptr<std::queue<tokenInfo>> tokens;
};

#endif