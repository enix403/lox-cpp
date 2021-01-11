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

    bool Match(const std::initializer_list<TokenType> types) {
        for (auto& type : types) {
            if (Check(type)) {
                Advance();
                return true;
            }
        }

        return false;
    }
    inline bool Match(const TokenType type) {
        return Check(type);
    }

    Expr* Rule_Expression() {
        return Rule_Equality();
    }

    Expr* Rule_Equality() {
        Expr* expr = Rule_Comparison();
        // Expr* expr;

        while (Match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
            const Token& oper = Previous();
            Expr* right = Rule_Comparison();
            // Expr* right;
            // &oper is not a dangling pointer because even after the function
            // ends, the target token lives in the vector 'tokens'
            expr = new BinaryExpr(expr, &oper, right);
        }

        return expr;
    }

    Expr* Rule_Comparison() {
        Expr* expr = Rule_Term();

        while (Match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
            const Token& oper = Previous();
            Expr* right = Rule_Term();
            expr = new BinaryExpr(expr, &oper, right);
        }

        return expr;
    }


    Expr* Rule_Term() {
        Expr* expr = Rule_Factor();

        while (Match({TokenType::MINUS, TokenType::PLUS})) {
            const Token& oper = Previous();
            Expr* right = Rule_Factor();
            expr = new BinaryExpr(expr, &oper, right);
        }

        return expr;
    }

    Expr* Rule_Factor() {
        Expr* expr = Rule_Unary();

        while (Match({TokenType::SLASH, TokenType::STAR})) {
            const Token& oper = Previous();
            Expr* right = Rule_Unary();
            expr = new BinaryExpr(expr, &oper, right);
        }
        return expr;
    }

    Expr* Rule_Unary() {
        if (Match({TokenType::MINUS, TokenType::BANG})) {
            const Token& oper = Previous();
            Expr* right = Rule_Unary();
            return new UnaryExpr(&oper, right);   
        }

        return Rule_Primary();
    }


    Expr* Rule_Primary() {
        if (Match({TokenType::FALSE})) return &LiteralExpr::LIT_FALSE;
        if (Match({TokenType::TRUE})) return &LiteralExpr::LIT_TRUE;
        if (Match({TokenType::NIL})) return &LiteralExpr::LIT_NIL;
        if (Match({TokenType::NUMBER, TokenType::STRING})) {
            return new LiteralExpr(&Previous());
        }

        if (Match(TokenType::LEFT_PAREN)) {
            Expr* expr = Rule_Expression();
            // Consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return new GroupingExpr(expr);
        }
    }

public:
    Parser(const vector<Token>& tokens) : tokens(tokens) {}
};