#include "parser.h"
#include "error_handling.h"

int error(const Token& token, const string& msg) {
    if (token.GetType() == TokenType::T_EOF) {
        ErrorHandler::Report(token.GetLine(), " at end", msg);
    } else {
        ErrorHandler::Report(token.GetLine(), " at '" + token.GetLexeme() + "'", msg);
    }
    return 1;
}

bool Parser::Match(const std::initializer_list<TokenType> types) {
    for (auto& type : types) {
        if (Check(type)) {
            Advance();
            return true;
        }
    }

    return false;
}

Expr* Parser::Rule_Expression() {
    return Rule_Equality();
}

Expr* Parser::Rule_Equality() {
    Expr* expr = Rule_Comparison();

    while (Match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        const Token& oper = Previous();
        Expr* right = Rule_Comparison();
        // &oper is not a dangling pointer because even after the function
        // ends, the target token lives in the vector 'tokens'
        expr = new BinaryExpr(expr, &oper, right);
    }

    return expr;
}

Expr* Parser::Rule_Comparison() {
    Expr* expr = Rule_Term();

    while (Match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
        const Token& oper = Previous();
        Expr* right = Rule_Term();
        expr = new BinaryExpr(expr, &oper, right);
    }

    return expr;
}

Expr* Parser::Rule_Term() {
    Expr* expr = Rule_Factor();

    while (Match({TokenType::MINUS, TokenType::PLUS})) {
        const Token& oper = Previous();
        Expr* right = Rule_Factor();
        expr = new BinaryExpr(expr, &oper, right);
    }

    return expr;
}

Expr* Parser::Rule_Factor() {
    Expr* expr = Rule_Unary();

    while (Match({TokenType::SLASH, TokenType::STAR})) {
        const Token& oper = Previous();
        Expr* right = Rule_Unary();
        expr = new BinaryExpr(expr, &oper, right);
    }
    return expr;
}

Expr* Parser::Rule_Unary() {
    if (Match({TokenType::MINUS, TokenType::BANG})) {
        const Token& oper = Previous();
        Expr* right = Rule_Unary();
        return new UnaryExpr(&oper, right);
    }

    return Rule_Primary();
}

Expr* Parser::Rule_Primary() {
    if (Match({TokenType::FALSE})) return new LiteralExpr(TokenType::FALSE, "false");
    if (Match({TokenType::TRUE})) return new LiteralExpr(TokenType::TRUE, "true");
    if (Match({TokenType::NIL})) return new LiteralExpr(TokenType::NIL, "nil");
    if (Match({TokenType::NUMBER, TokenType::STRING})) {
        const Token& prev = Previous();
        return new LiteralExpr(prev.GetType(), prev.GetLexeme());
    }

    if (Match({TokenType::LEFT_PAREN})) {
        Expr* expr = Rule_Expression();
        Consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return new GroupingExpr(expr);
    }

    throw error(Peek(), "Expect expression.");
}

const Token& Parser::Consume(TokenType type, const string& msg) {
    if (Check(type)) return Advance();
    throw error(Peek(), msg);
}

void Parser::Syncronize() {
    Advance();

    while (!IsAtEnd()) {
        if (Previous().GetType() == TokenType::SEMICOLON) return;

        switch (Peek().GetType()) {
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
            default:
                break;
        }

        Advance();
    }
}

Expr* Parser::Parse() {
    try {
        return Rule_Expression();
    }
    catch (int status_code) {
        return NULL;
    }
}