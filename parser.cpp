#include "parser.h"

void Parser::setTokens(std::queue<int> tokens_) {
    tokens = tokens_;
    ts = -1;
}
int Parser::getToken() {
    if(tokens.empty()) {
        return -1;
    } 
    int token = tokens.front();
    tokens.pop();
    return token;
}


void Parser::parse() {
    ts = getToken();
    program();
}

void Parser::program() {
    if(ts == keywordTokenValues::PROGRAM) {
        ts = getToken();
        procedureIdentifier();
    }
    else {
        std::cerr << "The program should start with program word\n";
        exit(-1);
    }
    ts = getToken();
    if(ts == ';') {
        ts = getToken();
        blockIdentifier();
    }
    else {
        std::cerr << "Block identifier is expected\n";
        exit(-1);
    }
    if(ts != '.') {
        std::cerr << "Dot is expected as the end of the program";
        exit(-1);
    }
}

void Parser::blockIdentifier() {
    std::cout << "block identifier" << std::endl;
    if(ts == keywordTokenValues::BEGIN) {
        ts = getToken();
        statementsList();
    }
    else {
        std::cerr << "Wrong block identifier\n";
        exit(-1);
    }
    if(ts != keywordTokenValues::END) {
        std::cerr << "Wrong end identifier\n";
    }
    ts = getToken();
}

void Parser::procedureIdentifier() {
    std::cout << "Procedure identirier" << std::endl;
    bool found = false;
    for(auto& pair : idnTokens) {
        if(pair.second == ts) {
            found = true;
        }
    }
    if(!found) {
        std::cerr << "wrong procedure identifier\n"; 
        exit(-1);
    }
}

void Parser::statementsList() {
    std::cout << "statements-list" << std::endl;
    statement();    
    while(ts == ';') {
        ts = getToken();
        statement();
    }
}

void Parser::statement() {
    if(ts == keywordTokenValues::LOOP) {
        std::cout << "statement" << std::endl;
        ts = getToken();
        statementsList();
        if(ts != keywordTokenValues::ENDLOOP) {
            std::cerr << "Wrong endloop identified\n";
        }
        ts = getToken();
        if(ts != ';') {
            std::cerr << "Wrong final delimiter\n";
        }
    }
    else if(ts == keywordTokenValues::CASE) {
        std::cout << "statement" << std::endl;
        ts = getToken();
        expression();
        
        if(ts != keywordTokenValues::OF) {
            std::cerr << "Wrong of identifier after OF" << ts << "\n";

            exit(-1);
        }
        ts = getToken();
        altlist();
        if(ts != keywordTokenValues::ENDCASE) {
            std::cerr << "Wrong endcase identifier" << ts << "\n";
            exit(-1);
        }
        ts = getToken();
        if(ts != ';') {
            std::cerr << "Wrong endline delimiter\n";
            exit(-1);
        }
    }
}

void Parser::expression() {

    std::cout << "Expression" << std::endl;
    multiplier();
    multipliersList();
}

void Parser::multiplier() {
    std::cout << "Mutiplier" << std::endl;
    bool found = false;
    // int token = getToken();
    for(auto& pair : idnTokens) {
        if(pair.second == ts) {
            found = true;
        }
    }    

    for(auto& pair : constTokens) {
        if(pair.second == ts) {
            found = true;
        }
    }
    if(!found) {
        std::cerr << "wrong multiplier" << ts << "\n";
        exit(-1);
    }
    ts = getToken();
}

void Parser::multipliersList() {
    std::cout << "multipliers-list" << std::endl;
    // if(ts == keywordTokenValues::MOD || ts == '*') {
    //     ts = getToken();
    //     multiplier();
    // }
    multiplicationInstruction();
}

void Parser::altlist() {
    std::cout << "alt-list" << std::endl;
    bool found = false;
    for(auto& pair : idnTokens) {
        if(pair.second == ts) {
            found = true;
        }
    } 
    for(auto& pair : constTokens) {
        if(pair.second == ts) {
            found = true;
        }
    }
    if(found) { 
        alternative();
        altlist();
    }

}

void Parser::alternative() {
    std::cout << "alternative" << std::endl;
    expression();
    if(ts == ':') {
        ts = getToken(); 
        statementsList();
    } 
}
            // VARIABLE3 MOD 51: CASE VARIABLE * 2 OF
            // VARIABLE5: LOOP ENDLOOP;

void Parser::multiplicationInstruction() {
    while(ts == keywordTokenValues::MOD || ts == '*') {
       ts = getToken();
       multiplier(); 
    }

}

void Parser::setTokens(std::string tokens_) {
    tokenString = std::istringstream(tokens_);
}