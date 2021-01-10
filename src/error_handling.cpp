#include <iostream>
#include "error_handling.h"

bool ErrorHandler::had_error = false;
void ErrorHandler::ReportError(int line, const string& msg) {
    cout << "[line " << line << "] Error : " << msg;
    // had_error = true;
}
