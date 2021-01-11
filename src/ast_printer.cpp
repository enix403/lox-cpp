#include "ast_printer.h"

string AstPrinter::Print(Expr* expr) {
    string res("");
    expr->Accept(this, &res);
    return res;
}

string AstPrinter::Parenthesize(const string& name, Expr* exprs[], int num_expr) {
    string res("(" + name);
    for (int i = 0; i < num_expr; i++) {
        Expr* expr = exprs[i];
        res += ' ' + Print(expr);
    }
    res += ')';

    return res;
}

void AstPrinter::VisitBinaryExpr(BinaryExpr* expr, void* result) {
    Expr* exprs[2] = {expr->left_operand, expr->right_operand};
    string* res = ((string*)result);
    *res = Parenthesize(expr->oper->GetLexeme(), exprs, 2);
}
void AstPrinter::VisitUnaryExpr(UnaryExpr* expr, void* result) {
    Expr* exprs[1] = {expr->operand};
    string* res = ((string*)result);
    *res = Parenthesize(expr->oper->GetLexeme(), exprs, 1);
}

void AstPrinter::VisitLiteralExpr(LiteralExpr* expr, void* result) {
    string* res = ((string*)result);
    if (expr->val_token->GetType() == TokenType::NIL) {
        *res = "nil";
    } else {
        *res = expr->val_token->GetLexeme();
    }
}
void AstPrinter::VisitGroupingExpr(GroupingExpr* expr, void* result) {
    string* res = ((string*)result);
    Expr* exprs[1] = {expr->expression};
    *res = Parenthesize("group", exprs, 1);
}
#if 0

#endif