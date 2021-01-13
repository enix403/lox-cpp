#pragma once

#include "expr.h"
#include "token_type.h"

#include <string>
#include <limits>

class Interpreter : public ExprVisitor {
private:
    inline void Evaluate(Expr* expr, void* result) {
        expr->Accept(this, result);
    }

public:

    void VisitLiteralExpr(LiteralExpr* expr, void* result) override;
    void VisitGroupingExpr(GroupingExpr* expr, void* result) override;
    void VisitUnaryExpr(UnaryExpr* expr, void* result) override;
    void VisitBinaryExpr(BinaryExpr* expr, void* result) override;
    double Interpret(Expr* expr);

};