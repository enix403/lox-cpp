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

LiteralExpr* LiteralExpr::LIT_FALSE = new LiteralExpr(TokenType::FALSE, "false");
LiteralExpr* LiteralExpr::LIT_TRUE = new LiteralExpr(TokenType::TRUE, "true");
LiteralExpr* LiteralExpr::LIT_NIL = new LiteralExpr(TokenType::NIL, "nil");

void GroupingExpr::Accept(ExprVisitor *visitor, void* result) {
    visitor->VisitGroupingExpr(this, result);
}
