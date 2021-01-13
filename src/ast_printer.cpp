// #if 0
#include "ast_printer.h"

string AstPrinter::Print(Expr* expr) {
    string res("");
    expr->Accept(this, &res);
    return res;
}

// string AstPrinter::Parenthesize(const string& name, Expr* exprs[], int num_expr) {
string AstPrinter::Parenthesize(const string& name, std::initializer_list<Expr*> exprs) {
    string res("(" + name);
    for (Expr* expr: exprs) {
        res += ' ' + Print(expr);
    }
    res += ')';

    return res;
}

void AstPrinter::VisitBinaryExpr(BinaryExpr* expr, void* result) {
    string* res = ((string*)result);
    *res = Parenthesize(expr->oper->GetLexeme(), {expr->left_operand, expr->right_operand});
}
void AstPrinter::VisitUnaryExpr(UnaryExpr* expr, void* result) {
    // Expr* exprs[1] = {expr->operand};
    string* res = ((string*)result);
    *res = Parenthesize(expr->oper->GetLexeme(), {expr->operand});
}

void AstPrinter::VisitLiteralExpr(LiteralExpr* expr, void* result) {
    string* res = ((string*)result);
    // if (expr->literal_type == TokenType::NIL) {
        // *res = "nil";
    // } else {
        // *res = expr->lexeme;
    // }
    *res = expr->lexeme;
}
void AstPrinter::VisitGroupingExpr(GroupingExpr* expr, void* result) {
    string* res = ((string*)result);
    // Expr* exprs[1] = {expr->expression};
    *res = Parenthesize("group", {expr->expression});
}
// #endif
