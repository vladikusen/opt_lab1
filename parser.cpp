#include "parser.h"

void Parser::setTokenString(std::string _tokenString) {
    tokenString = std::istringstream(_tokenString);
}

int Parser::getToken() {
    std::string line;
    int pos = 0;
    int last_pos = 0;
    if(!tokenString.eof()) {
        
        std::getline(tokenString, line);
        line += '\0'; 
        std::cout << line << std::endl; 
        while((pos = line.find("\t\t", last_pos)) != std::string::npos) {
            std::cout << line.substr(last_pos, pos - last_pos) << std::endl;
            last_pos += 2;
        }
    }
}

void Parser::program() {

}