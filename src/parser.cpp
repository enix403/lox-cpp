#include "parser.h"
#include "error_handling.h"


/*

primary 			-> literals | '(' expression ')'
unary 				-> ('-' | '!') unary | primary
factor 				-> unary (( '*' | '/') unary)*
term 				-> factor (( '+' | '-' ) factor)*
unequal comparison 	-> term (( '>=' | '<=' | '<' | '>' ) term)*
equal comparison 	-> unequal comparison (( '==' | '!=' ) unequal comparison)*
expression			-> equal comparison

*/

int error(const Token& token, const string& msg) {
    if (token.GetType() == TokenType::T_EOF) {
        ErrorHandler::Report(token.GetLine(), " at end", msg);
    } else {
        ErrorHandler::Report(token.GetLine(), " at '" + token.GetLexeme() + "'", msg);
    }
    return 1;
}

bool Parser::MatchNext(const std::initializer_list<TokenType> types) {
    for (const auto type : types) {
        if (CheckNext(type)) {
            Advance();
            return true;
        }
    }

    return false;
}

bool Parser::MatchNext(TokenType type) {
    if (CheckNext(type)) {
        Advance();
        return true;
    }

    return false;
}

Expr* Parser::RuleMatch_Primary() {
    if (MatchNext(TokenType::FALSE)) return LiteralExpr::LIT_FALSE;
    if (MatchNext(TokenType::TRUE)) return LiteralExpr::LIT_TRUE;
    if (MatchNext(TokenType::NIL)) return LiteralExpr::LIT_NIL;

    if (MatchNext({TokenType::NUMBER, TokenType::STRING})) {
        const Token& literal = Previous();
        return new LiteralExpr(literal.GetType(), literal.GetLexeme());
    }

    if (MatchNext(TokenType::LEFT_PAREN)) {
        Expr* expr = RuleMatch_Expression();
        Consume(TokenType::RIGHT_PAREN, "Expected closing parenthesis");
        return new GroupingExpr(expr);
    }
    
    throw error(Peek(), "Expected expression");
}

Expr* Parser::RuleMatch_Unary() {
    if (MatchNext({TokenType::BANG, TokenType::MINUS})) {
        const Token& oper = Previous();
        return new UnaryExpr(&oper, RuleMatch_Unary());
    }
    return RuleMatch_Primary();
}

Expr* Parser::RuleMatch_Factor() {
    Expr* left = RuleMatch_Unary();
    while (MatchNext({TokenType::STAR, TokenType::SLASH})) {
        const Token& oper = Previous();
        left = new BinaryExpr(left, &oper, RuleMatch_Unary());
    }

    return left;
}

Expr* Parser::RuleMatch_Term() {
    Expr* left = RuleMatch_Factor();
    while (MatchNext({TokenType::PLUS, TokenType::MINUS})) {
        const Token& oper = Previous();
        left = new BinaryExpr(left, &oper, RuleMatch_Factor());
    }

    return left;
}

Expr* Parser::RuleMatch_UnequalComparison() {
    Expr* left = RuleMatch_Term();
    while (MatchNext({TokenType::GREATER_EQUAL, TokenType::LESS_EQUAL, TokenType::LESS, TokenType::GREATER})) {
        const Token& oper = Previous();
        left = new BinaryExpr(left, &oper, RuleMatch_Term());
    }

    return left;
}

Expr* Parser::RuleMatch_EqualComparison() {
    Expr* left = RuleMatch_UnequalComparison();
    while (MatchNext({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
        const Token& oper = Previous();
        left = new BinaryExpr(left, &oper, RuleMatch_UnequalComparison());
    }

    return left;
}


Expr* Parser::RuleMatch_Expression() {
    return RuleMatch_EqualComparison();
}

const Token& Parser::Consume(TokenType type, const string& msg) {
    if (CheckNext(type)) return Advance();
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
        return RuleMatch_Expression();
    }
    catch (int error_code) {
        return nullptr;
    }
}