#include <iostream>
#include "ast_printer.h"
#include "expr.h"
#include "token.h"

/*

 Expr expression = new Expr.BinaryExpr(
    new Expr.UnaryExpr(
        new Token(TokenType.MINUS, "-", null, 1),
        new Expr.LiteralExpr(123)
    ),
    new Token(TokenType.STAR, "*", null, 1),
    new Expr.GroupingExpr(
        new Expr.LiteralExpr(45.67)
    )
);


*/

int main() {
    std::cout << "Hello world\n";
    
    Expr* expresssion = new BinaryExpr(
        new UnaryExpr(
            new Token(TokenType::MINUS, "-", 1),
            new LiteralExpr(TokenType::NUMBER, "123")
        ),
        new Token(TokenType::STAR, "*", 1),
        new GroupingExpr(
            new LiteralExpr(TokenType::NUMBER, "45.34")
        )
    );

    AstPrinter printer;
    std::cout << printer.Print(expresssion) << '\n'; 
}