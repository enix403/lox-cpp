// #if 0
#pragma once

#include <string>
#include <initializer_list>
#include "expr.h"

using namespace std;

class AstPrinter : public ExprVisitor {
public:
    string Print(Expr* expr);
    // string Parenthesize(const string& name, Expr* exprs[], int num_expr);
    string Parenthesize(const string& name, const std::initializer_list<Expr*> exprs);

    void VisitBinaryExpr(BinaryExpr* expr, void* result) override;
    void VisitUnaryExpr(UnaryExpr* expr, void* result) override;
    void VisitLiteralExpr(LiteralExpr* expr, void* result) override;
    void VisitGroupingExpr(GroupingExpr* expr, void* result) override;
};
// #endif