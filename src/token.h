#pragma once

#include <string>
#include "token_type.h"

using namespace std;


class Token {
private:
    int line;
    TokenType type;
    string lexeme;

public:
    Token(TokenType type, string lexeme, int line);
    inline string ToString() const { return "TKSTART(" + to_string((int)type) + ")::" + lexeme + "::TKEND"; }
};
