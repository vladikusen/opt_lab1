#ifndef __PARSER_H__
#define __PARSER_H__
//program
#include <string>
#include <sstream>
#include <iostream>

class Parser {
public:
    Parser() = default;
    void program();
public:
    int getToken();
    void setTokenString(std::string);
    std::istringstream tokenString;
};

#endif