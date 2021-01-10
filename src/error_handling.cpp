#include <iostream>
#include "error_handling.h"

bool ErrorHandler::had_error = false;
void ErrorHandler::ReportError(int line, const string& msg) {
    cerr << "[line " << line << "] Error : " << msg;
    // had_error = true;
    ErrorHandler::had_error = true;
}
