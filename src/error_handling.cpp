#include <iostream>
#include "error_handling.h"

bool ErrorHandler::had_error = false;
void ErrorHandler::Report(int line, const string& where, const string& msg) {
    // cerr << "[line " << line << "] Error : " << msg;
    cerr << "[line " << line << "] Error" << where << ": " << msg << '\n';
    ErrorHandler::had_error = true;
}

void ErrorHandler::Error(int line, const string& msg) {
    Report(line, "", msg);
}
