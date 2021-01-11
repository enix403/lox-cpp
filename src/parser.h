#pragma once

#include <vector>
#include <string>
#include <initializer_list>

#include "token.h"
#include "expr.h"

using namespace std;

class Parser {
private:

    const vector<Token>& tokens;
    int current = 0;

    inline const Token& Previous() const { return tokens[current - 1]; }
    inline const Token& Peek() const { return tokens[current]; }
    inline bool IsAtEnd() const { return Peek().GetType() == TokenType::T_EOF; }
    inline const Token& Advance() {
        if (!IsAtEnd()) current++;
        return Previous();
    }

    inline bool Check(const TokenType type) const {
        if (IsAtEnd()) return false;
        return Peek().GetType() == type;
    }

    bool Match(const std::initializer_list<TokenType> types);
    Expr* Rule_Expression();
    Expr* Rule_Equality();
    Expr* Rule_Comparison();
    Expr* Rule_Term();
    Expr* Rule_Factor();
    Expr* Rule_Unary();
    Expr* Rule_Primary();

    const Token& Consume(TokenType type, const string& msg);

    void Syncronize();

public:
    Parser(vector<Token>& tokens) : tokens(tokens) {}
    Expr* Parse();
};