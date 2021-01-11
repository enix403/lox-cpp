#pragma once

#include <string>
using namespace std;

class ErrorHandler {
private:
    static bool had_error;

public:
    inline static bool HadError() {return had_error;}
    static void Report(int line, const string& where, const string& msg);
    static void Error(int line, const string& msg);

    inline static void ResetHadError() { had_error = false; }
};

