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

    tokens.at(42) = tokenValues::DM; // *
    tokens.at(58) = tokenValues::DM; // :
    tokens.at(59) = tokenValues::DM; // ;
    tokens.at(46) = tokenValues::DM; // .
    
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
    char c;
    initialProgram = std::string("");
    // if(inputFile.is_open()) {
    //     while(inputFile.get(c)) {
    //         initialProgram += c;
    //     }
    // }
}

std::pair<char, int> TokenAnalyser::getChar() {
    if(program.is_open()) {
        char c;
        if(program.get(c)) {
            return std::pair<char, int>(c, tokens.at(c));
        }
        else {
            return {-1, -1};
        }
    }
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
    while(!program.eof()) {
        auto symbol = getChar();
        std::string buffer = std::string("");
        bool supressOutput = false;

        switch(symbol.second) {
            case 0:
                while(!program.eof()) {
                    symbol = getChar();
                    if(symbol.second > 0 || symbol.second < 0) {
                        break;
                    }
                }
            case 1:
                while(!program.eof() && symbol.second == 1) {
                    buffer += symbol.first;
                    symbol = getChar();
                }
                if(!buffer.empty()) {
                    constTabSearch(buffer);
                    buffer = "";
                }
            case 2:
                while(!program.eof() && symbol.second == 2 || symbol.second == 1) {
                    buffer += symbol.first;
                    symbol = getChar();
                } 
                if(!buffer.empty()) {
                    if(kTabSearch(buffer) == -1) {
                        idnTabSearch(buffer);
                    }
                    buffer = "";
                }
                break; 
            case 3:
                // symbol = getChar();
                std::cout << "DEL" << symbol.first << "DEL" << std::endl;

        }
    }
    program.close();
}