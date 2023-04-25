#include "parser.h"

void Parser::setTokens(std::queue<tokenInfo> tokens_) {
    tokens = std::make_unique<std::queue<tokenInfo>>(tokens_);
}
int Parser::getToken() {
    auto token = tokens->front();
    tokens->pop();
    std::cout << token.row << " " << token.column << " " << token.token << " " << token.value << std::endl;
}

void Parser::program() {

}