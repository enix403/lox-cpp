#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "error_handling.h"
// #include "ast_printer.h"
#include "interpreter.h"

using namespace std;

class Lox {
private:
    void Run(const string& source) const {
        Scanner scanner(source);
        vector<Token>& tokens = scanner.ScanAllTokens();

        // for (int i = 0; i < tokens.size(); i++) {
            // const Token& token = tokens[i];
            // cout << token.ToString() << "\n";
        // }

        Parser parser(tokens);
        Expr* expression = parser.Parse();

        if (ErrorHandler::HadError()) {
            return;
        }

        // print using ast printer
        Interpreter printer;
        cout << printer.Interpret(expression) << '\n'; 
    }

public:
    void RunPrompt() const {
        string line;
        cout << "Lox 0.0.1\n";
        while (true) {
            cout << ">> ";
            if (!getline(cin, line)) {
                break;
            }
            this->Run(line);
            ErrorHandler::ResetHadError();
        }
        cout << "\nExiting...\n";
    }

    void RunFile(const string& path) const {
        ifstream file(path);
        string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        Run(content);
    }
};

int main(int argc, char** argv) {
    Lox lox;
    if (argc == 1) {
        lox.RunPrompt();
    } else if (argc == 2) {
        string path = argv[1];
        lox.RunFile(path);
    } else {
        std::cout << "Invalid command\n";
    }
}
