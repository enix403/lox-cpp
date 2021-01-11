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
    inline string ToString() const {
        return "TKSTART(" + _TOKEN_NAMES.at(type) + ")::" + lexeme + "::TKEND";
    }

    inline const string& GetLexeme() const { return lexeme; }
    inline const TokenType& GetType() const { return type; }
    inline int GetLine() const { return line; }
};

