#include "parser.h"

void Parser::setTokens(std::queue<int> tokens_) {
    tokens = tokens_;
}
int Parser::getToken() {
    if(tokens.empty()) {
        return -1;
    } 
    int token = tokens.front();
    tokens.pop();
    return token;
}

void Parser::program() {
    int token = getToken();
    if(token == keywordTokenValues::PROGRAM) {
        procedureIdentifier();
    }
    else {
        std::cerr << "The program should start with program word\n";
        exit(-1);
    }
    token = getToken();
    if(token == ';') {
        blockIdentifier();
    }
    else {
        std::cerr << "Block identifier is expected\n";
        exit(-1);
    }
    token = getToken();
    if(token != '.') {
        std::cerr << "Dot is expected as the end of the program";
        exit(-1);
    }
}

void Parser::blockIdentifier() {
    int token = getToken();
    if(token == keywordTokenValues::BEGIN) {
        statementsList();
    }
    else {
        std::cerr << "Wrong block identifier\n";
        exit(-1);
    }
    token = getToken();
    if(token != keywordTokenValues::END) {
        std::cerr << "Wrong end identifier\n";
    }
}

void Parser::procedureIdentifier() {
    int token = getToken();
    bool found = false;
    for(auto& pair : idnTokens) {
        if(pair.second == token) {
            found = true;
        }
    }
    if(!found) {
        std::cerr << "wrong procedure identifier\n"; 
        exit(-1);
    }
}

void Parser::statementsList() {
    statement();    
}

void Parser::statement() {
    int token = getToken();
    if(token == keywordTokenValues::LOOP) {
        statementsList();
        token = getToken();
        if(token != keywordTokenValues::ENDLOOP) {
            std::cerr << "Wrong endloop identified\n";
        }
        token = getToken();
        if(token != ';') {
            std::cerr << "Wrong final delimiter\n";
        }
    }
    else if(token == keywordTokenValues::CASE) {
        expression();
        token = getToken();
        if(token != keywordTokenValues::OF) {
            std::cerr << "Wrong of identifier\n";
            exit(-1);
        }
        altlist();
        token = getToken();
        if(token != keywordTokenValues::ENDCASE) {
            std::cerr << "Wrong endcase identifier\n";
            exit(-1);
        }
        token = getToken();
        if(token != ';') {
            std::cerr << "Wrong endline delimiter\n";
            exit(-1);
        }
    }
}

void Parser::expression() {
    multiplier();
}

void Parser::multiplier() {
    bool found = false;
    int token = getToken();
    for(auto& pair : idnTokens) {
        if(pair.second == token) {
            found = true;
        }
    }    

    for(auto& pair : constTokens) {
        if(pair.second == token) {
            found = true;
        }
    }

    if(!found) {
        std::cerr << "wrong multiplier\n";
        exit(-1);
    }
    multipliersList();
}

void Parser::multipliersList() {

}

void Parser::multiplicationInstruction() {
    int token = getToken();
    if(token != keywordTokenValues::MOD && token != '*') {
        std::cerr << "Wrong multiplication instruction\n";
        exit(-1);
    }
    multiplier();
}

void Parser::setTokens(std::string tokens_) {
    tokenString = std::istringstream(tokens_);
}