#pragma once

#include <string>
using namespace std;

class ErrorHandler {
private:
    static bool had_error;

public:
    inline static bool HadError() {return had_error;}
    static void ReportError(int line, const string& msg);
};

