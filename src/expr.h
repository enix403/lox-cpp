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
    const Expr* left_operand;
    const Token* oper;
    const Expr* right_operand;

    BinaryExpr(const Expr* left_operand, const Token* oper, const Expr* right_operand) {
        this->left_operand = left_operand;
        this->oper = oper;
        this->right_operand = right_operand;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};

struct UnaryExpr : public Expr {
public:
    const Token* oper;
    const Expr* operand;

    UnaryExpr(const Token* oper, const Expr* operand) {
        this->oper = oper;
        this->operand = operand;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};


struct LiteralExpr : public Expr {
public:
    const Token* val_token;

    LiteralExpr(const Token* val_token) {
        this->val_token = val_token;
    }

    void Accept(ExprVisitor *visitor, void* result) override;


    static LiteralExpr LIT_FALSE;
    static LiteralExpr LIT_TRUE;
    static LiteralExpr LIT_NIL;
};


struct GroupingExpr : public Expr {
public:
    const Expr* expression;

    GroupingExpr(const Expr* expression) {
        this->expression = expression;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};

