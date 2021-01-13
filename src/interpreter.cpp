#include "interpreter.h"


void Interpreter::VisitLiteralExpr(LiteralExpr* expr, void* result) {
    *((double*)result) = (double)std::stod(expr->lexeme);
};
void Interpreter::VisitGroupingExpr(GroupingExpr* expr, void* result) {
    Evaluate(expr->expression, result);
}
void Interpreter::VisitUnaryExpr(UnaryExpr* expr, void* result) {
    double right;
    Evaluate(expr->operand, &right);

    switch (expr->oper->GetType()) {
        case TokenType::MINUS:
            *((double*)result) = -1.0 * right;
        default:
            break;
    }
}

void Interpreter::VisitBinaryExpr(BinaryExpr* expr, void* result) {
    double left, right;
    Evaluate(expr->left_operand, &left);
    Evaluate(expr->right_operand, &right);

    switch (expr->oper->GetType()) {
        case TokenType::MINUS:
            *((double*)result) = left - right;
            break;

        case TokenType::PLUS:
            *((double*)result) = left + right;
            break;

        case TokenType::STAR:
            *((double*)result) = left * right;
            break;

        case TokenType::SLASH:
            if (right != 0) {
                *((double*)result) = left / right;
            } else {
                *((double*)result) = std::numeric_limits<double>::infinity();
            }
            break;

        default:
            break;
    }
}

double Interpreter::Interpret(Expr* expr) {
    double res;
    Evaluate(expr, &res);
    return res;
}
