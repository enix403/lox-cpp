#pragma once

#include <iostream>
#include <array>

#include "token.h"

struct BinaryExpr;
struct UnaryExpr;
struct LiteralExpr;
struct GroupingExpr;

class ExprVisitor {
public:
    virtual void VisitBinaryExpr(BinaryExpr *expr, void* result) = 0;
    virtual void VisitUnaryExpr(UnaryExpr *expr, void* result) = 0;
    virtual void VisitLiteralExpr(LiteralExpr *expr, void* result) = 0;
    virtual void VisitGroupingExpr(GroupingExpr *expr, void* result) = 0;
};


struct Expr {
public:
    virtual ~Expr() {}
    virtual void Accept(ExprVisitor *visitor, void* result) = 0;
};


struct BinaryExpr : public Expr {
public:
    Expr* left_operand;
    const Token* oper;
    Expr* right_operand;

    BinaryExpr(Expr* left_operand, const Token* oper, Expr* right_operand) {
        this->left_operand = left_operand;
        this->oper = oper;
        this->right_operand = right_operand;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};

struct UnaryExpr : public Expr {
public:
    const Token* oper;
    Expr* operand;

    UnaryExpr(const Token* oper, Expr* operand) {
        this->oper = oper;
        this->operand = operand;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};


struct LiteralExpr : public Expr {
public:
    const TokenType literal_type;
    const string& lexeme;

    LiteralExpr(const TokenType type, const string& lexeme) : literal_type(type), lexeme(lexeme) {}

    void Accept(ExprVisitor *visitor, void* result) override;

};


struct GroupingExpr : public Expr {
public:
    Expr* expression;

    GroupingExpr(Expr* expression) {
        this->expression = expression;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};

