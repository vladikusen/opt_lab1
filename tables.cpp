#include "tables.h"

#include <memory>


void TokenAnalyser::init() {
    for(int i = 0; i < 128; i++) {
        tokens.at(i) = tokenValues::ERR;
    } 
    for(int i = 8; i < 16; i++) {
        tokens.at(i) = tokenValues::WS;
    } 
    tokens.at(32) = tokenValues::WS;
    for(int i = 48; i < 58; i++) {
        tokens.at(i) = tokenValues::CNS; // digits
    }

    for(int i = 65; i < 91; i++) {
        tokens.at(i) = tokenValues::IDN; // letters
    }

    tokens.at(42) = tokenValues::DM1; // *
    tokens.at(58) = tokenValues::DM2; // :
    tokens.at(59) = tokenValues::DM2; // ;
    tokens.at(46) = tokenValues::DM2; // .
    
    kTokens["PROGRAM"] = keywordTokenValues::PROGRAM;
    kTokens["BEGIN"] = keywordTokenValues::BEGIN;
    kTokens["END"] = keywordTokenValues::END;
    kTokens["LOOP"] = keywordTokenValues::LOOP;
    kTokens["ENDLOOP"] = keywordTokenValues::ENDLOOP;
    kTokens["CASE"] = keywordTokenValues::CASE;
    kTokens["OF"] = keywordTokenValues::OF;
    kTokens["ENDCASE"] = keywordTokenValues::ENDCASE;
    kTokens["MOD"] = keywordTokenValues::MOD;
}

TokenAnalyser::TokenAnalyser(std::string fileName) {
    std::ifstream inputFile;
    program.open(std::string("../") + fileName);
    outProgram.open(std::string("../") + "out.txt");
    if(!program.is_open()) {
        writeError("Could not load a program file");
    }
    if(!outProgram.is_open()) {
        writeError("Could not load an output file");
    }
    char c;
    row = 1;
    column = 0;
}

std::pair<char, int> TokenAnalyser::getChar() {
    if(program.is_open()) {
        char c;
        if(program.get(c)) {
            column++;
            return std::pair<char, int>(c, tokens.at(c));
        }
        else {
            return {-1, -1};
        }
    }
}

void TokenAnalyser::writeToken(std::string token, int tokenCode, bool delimiter) {
    outProgram << row << "\t\t" << column - token.length() << "\t\t" << tokenCode << "\t" << token << std::endl; 
}

void TokenAnalyser::writeError(std::string error) {
    outProgram << row << "\t\t" << column << "\t\t" << error << std::endl;
}

int TokenAnalyser::findMax(std::string tokenMap) {
    int value = -1; 
    std::shared_ptr<std::map<std::string, int>> tMap = nullptr;
    if(tokenMap == "idnTokens") {
        tMap = std::make_shared<std::map<std::string, int>>(idnTokens); 
        value = 500; 
    }
    else {
        tMap = std::make_shared<std::map<std::string, int>>(constTokens);
        value = 600;
    } 
    if(tMap->empty()) {
        return value;
    }
    int max = value;
    for(const auto& kv : *tMap) {
        if(kv.second > max) {
            max = kv.second;
        }
    }
    

    return max;
}

int TokenAnalyser::idnTabSearch(std::string keyword) {
    if(idnTokens.find(keyword) == idnTokens.end()) {
        idnTokens[keyword] = findMax("idnTokens") + 1;
    }
    return idnTokens[keyword];
}

int TokenAnalyser::kTabSearch(std::string keyword) {
    if(kTokens.find(keyword) == kTokens.end()) {
        return -1;
    }
    return kTokens[keyword];
}

int TokenAnalyser::constTabSearch(std::string keyword) {
    if(constTokens.find(keyword) == constTokens.end()) {
        constTokens[keyword] = findMax("constTokens") + 1;
    } 
    return constTokens[keyword];
}

void TokenAnalyser::analyze() {
    auto symbol = getChar();
    while(!program.eof()) {
        std::string buffer = std::string("");
        bool supressOutput = false;

        switch(symbol.second) {
            case 0:
                while(!program.eof()) {
                    if(symbol.first == '\n') {
                        row++;
                        column = 0;
                    }
                    symbol = getChar();
                    if(symbol.second > 0 || symbol.second < 0) {
                        break;
                    }
                }
                break;
            case 1:
                while(!program.eof() && symbol.second == 1) {
                    buffer += symbol.first;
                    symbol = getChar();
                }
                writeToken(buffer, constTabSearch(buffer));
                break;
            case 2: {
                while(!program.eof() && symbol.second == 2 || symbol.second == 1) {
                    buffer += symbol.first;
                    symbol = getChar();
                } 
                int tokenCode = kTabSearch(buffer); 
                if(tokenCode == -1) {
                    tokenCode = idnTabSearch(buffer);
                }
                writeToken(buffer, tokenCode);
                break; 
            }
            case 3: {
                if(program.eof()) {
                    std::string token = "";
                    token += symbol.first;
                    writeToken(token, symbol.first);
                }
                else {
                    symbol = getChar();
                    if(symbol.first == '/') {
                        if(program.eof()) {
                            writeError("Expected / but end of file found");
                        }
                        else {
                            symbol = getChar();
                            do {
                                while(!program.eof() && symbol.first != '/') {
                                    symbol = getChar();
                                }
                                if(program.eof()) {
                                    writeError("Expected / but end of file found");
                                    symbol.first = '+';
                                    break;
                                }
                                else {
                                    symbol = getChar();
                                }
                            }while(symbol.first != '*');
                            if(!program.eof()) {
                                symbol = getChar();
                            } 
                        }
                    }
                    else {
                        writeToken("*", '*');
                    }
                }
                break; 
            }
            case 4: {
                std::string delimiterToString = "";
                char delimiterToken = symbol.first; 
                delimiterToString += delimiterToken;
                symbol = getChar();
                writeToken(delimiterToString, delimiterToken);
                break;
            }
            case 5:
                writeError("Illegal symbol");
                symbol = getChar();
        }
    }
    program.close();
    outProgram.close();
}