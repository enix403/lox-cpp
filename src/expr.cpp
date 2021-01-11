#include "expr.h"

void BinaryExpr::Accept(ExprVisitor *visitor, void* result) {
    visitor->VisitBinaryExpr(this, result);
}

void UnaryExpr::Accept(ExprVisitor *visitor, void* result) {
    visitor->VisitUnaryExpr(this, result);
}

void LiteralExpr::Accept(ExprVisitor *visitor, void* result) {
    visitor->VisitLiteralExpr(this, result);
}

void GroupingExpr::Accept(ExprVisitor *visitor, void* result) {
    visitor->VisitGroupingExpr(this, result);
}
