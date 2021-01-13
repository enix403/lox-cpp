#pragma once

#include <vector>
#include <initializer_list>
#include <memory>
#include <string>

#include "token.h"
#include "expr.h"


class Parser {
private:
    const vector<Token>& tokens;
    int next_token_index = 0;

    inline const Token& Peek() const { return tokens[next_token_index]; }
    inline const Token& Previous() const { return tokens[next_token_index - 1]; }
    inline bool CheckNext(TokenType type) const { return Peek().GetType() == type; }
    inline bool IsAtEnd() const { return CheckNext(TokenType::T_EOF); }
    
    inline const Token& Advance() {
        next_token_index++;
        return tokens[next_token_index - 1];
    }

    bool MatchNext(const std::initializer_list<TokenType> types);
    bool MatchNext(TokenType type);


    Expr* RuleMatch_Primary();
    Expr* RuleMatch_Unary();
    Expr* RuleMatch_Factor();
    Expr* RuleMatch_Term();
    Expr* RuleMatch_UnequalComparison();
    Expr* RuleMatch_EqualComparison();
    Expr* RuleMatch_Expression();
    

    // bool Consume(TokenType type);
    const Token& Consume(TokenType type, const string& msg);
    void Syncronize();

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}

    Expr* Parse();
    
};