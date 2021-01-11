#pragma once

#include <iostream>
#include <array>

#include "token.h"

class BinaryExpr;
class UnaryExpr;
class LiteralExpr;
class GroupingExpr;

class ExprVisitor {
public:
    virtual void VisitBinaryExpr(BinaryExpr *element, void* result) = 0;
    virtual void VisitUnaryExpr(UnaryExpr *element, void* result) = 0;
    virtual void VisitLiteralExpr(LiteralExpr *element, void* result) = 0;
    virtual void VisitGroupingExpr(GroupingExpr *element, void* result) = 0;
};


class Expr {
public:
    virtual ~Expr() {}
    virtual void Accept(ExprVisitor *visitor, void* result) = 0;
};


class BinaryExpr : public Expr {
    /**
   * Note that we're calling `visitConcreteComponentA`, which matches the
   * current class name. This way we let the visitor know the class of the
   * component it works with.
   */
public:
    Expr* left_operand;
    Token* oper;
    Expr* right_operand;

    BinaryExpr(Expr* left_operand, Token* oper, Expr* right_operand) {
        this->left_operand = left_operand;
        this->oper = oper;
        this->right_operand = right_operand;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};

class UnaryExpr : public Expr {
    /**
   * Same here: visitConcreteComponentB => ConcreteComponentB
   */
public:

    Token* oper;
    Expr* operand;

    UnaryExpr(Token* oper, Expr* operand) {
        this->oper = oper;
        this->operand = operand;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};


struct LiteralExpr : public Expr {
    Token* val_token;

    LiteralExpr(Token* val_token) {
        this->val_token = val_token;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};


struct GroupingExpr : public Expr {
    Expr* expression;

    GroupingExpr(Expr* expression) {
        this->expression = expression;
    }

    void Accept(ExprVisitor *visitor, void* result) override;
};

