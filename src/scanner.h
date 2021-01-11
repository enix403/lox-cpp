#pragma once

#include <string>
#include <vector>

#include "token_type.h"
#include "token.h"

class Scanner {
private:
    const string& source;
    vector<Token> tokens;

    int start = 0;
    int next_unobserved = 0;
    int line = 1;

    int len_source;

    void Setup();

    inline bool IsAtEnd() const { return next_unobserved >= len_source; }
    inline bool IsInRange(int index) const { return index < len_source; }

    void AddToken(TokenType type);

    bool ExploreIfMatch(char expected);
    char ExploreNext();
    char PeekNext(int num);

public:
    Scanner(const string& source) : source(source) {
        Setup();
    }
    vector<Token>& ScanAllTokens();
};