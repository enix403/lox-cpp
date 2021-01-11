#include <iostream>

#include "scanner.h"

#include "error_handling.h"
#include "keywords.h"

inline string get_substring(const string& str, int start, int end) {
    return str.substr(start, end - start);
}

// Checks if character is letter or underscore
inline bool is_alpha(const char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

inline bool is_alphanumeric(const char ch) {
    return is_alpha(ch) || isdigit(ch);
}

void Scanner::Setup() {
    start = 0;
    next_unobserved = 0;
    line = 1;
    len_source = source.length();
    tokens.clear();
}

void Scanner::AddToken(TokenType type) {
    string text(get_substring(source, start, next_unobserved));
    tokens.push_back(Token(type, text, line));
}

bool Scanner::ExploreIfMatch(char expected) {
    if (IsAtEnd()) return false;
    if (source[next_unobserved] != expected) return false;
    next_unobserved++;
    return true;
}

char Scanner::ExploreNext() {
    char ch = source[next_unobserved];
    next_unobserved++;
    return ch;
}

char Scanner::PeekNext(int num = 1) {
    int index = next_unobserved + num - 1;
    if (!IsInRange(index)) return '\0';
    return source[index];
}

vector<Token>& Scanner::ScanAllTokens() {
    while (!IsAtEnd()) {
        char ch = ExploreNext();

        // 'ch' has been consumed at this point, so PeekNext
        // will return the next character after 'ch'

        switch (ch) {
            case '(':
                AddToken(TokenType::LEFT_PAREN);
                break;
            case ')':
                AddToken(TokenType::RIGHT_PAREN);
                break;
            case '{':
                AddToken(TokenType::LEFT_BRACE);
                break;
            case '}':
                AddToken(TokenType::RIGHT_BRACE);
                break;
            case ',':
                AddToken(TokenType::COMMA);
                break;
            case '.':
                AddToken(TokenType::DOT);
                break;
            case '-':
                AddToken(TokenType::MINUS);
                break;
            case '+':
                AddToken(TokenType::PLUS);
                break;
            case ';':
                AddToken(TokenType::SEMICOLON);
                break;
            case '*':
                AddToken(TokenType::STAR);
                break;
            case '/':
                if (ExploreIfMatch('/')) {
                    // A comment goes until the end of the line.
                    char next;
                    while (true) {
                        next = PeekNext();
                        if (next == '\n' || next == '\0') break;
                        ExploreNext();
                    }
                } else {
                    AddToken(TokenType::SLASH);
                }
                break;

            case '"':
                char current;

                while (true) {
                    if (!IsAtEnd()) {
                        current = ExploreNext();
                        if (current == '"') {
                            string str{get_substring(source, start + 1, next_unobserved - 1)};
                            tokens.push_back(Token(TokenType::STRING, str, line));
                            break;
                        }
						else if (current == '\n') {
							line++;
						}
                    } else {
                        ErrorHandler::ReportError(line, "Unterminated string\n");
                        break;
                    }
                }

                break;

            case '!':
                AddToken((ExploreIfMatch('=')) ? TokenType::BANG_EQUAL : TokenType::BANG);
                break;
            case '=':
                AddToken((ExploreIfMatch('=')) ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
                break;
            case '<':
                AddToken((ExploreIfMatch('=')) ? TokenType::LESS_EQUAL : TokenType::LESS);
                break;
            case '>':
                AddToken((ExploreIfMatch('=')) ? TokenType::GREATER_EQUAL : TokenType::GREATER);
                break;

            case ' ':
            case '\r':
            case '\t':
                // Ignore whitespace.
                break;

            case '\n':
                line++;
                break;

            default:
                // handle digits (didn't want to write case '1', case '2', .....)
                if (isdigit(ch)) {
                    char next = PeekNext();
                    // consume all digits afterward
                    while (isdigit(next)) {
                        ExploreNext();
                        next = PeekNext();
                    }

                    // now 'next' is next uncomsumed non digit character

                    // only consume the period if the char after it is a digit
                    if (next == '.' && isdigit(PeekNext(2))) {
                        // consume the period
                        ExploreNext();

                        next = PeekNext();
                        // consume all digits afterward
                        while (isdigit(next)) {
                            ExploreNext();
                            next = PeekNext();
                        }
                    }

                    AddToken(TokenType::NUMBER);
                } else if (is_alpha(ch)) {  // potential identifier or keyword
                    while (is_alphanumeric(PeekNext())) {
                        ExploreNext();
                    }

                    string identifier = get_substring(source, start, next_unobserved);
                    TokenType ident_type;
                    if (keywords.find(identifier) != keywords.end()) {
                        ident_type = keywords.at(identifier);
                    } else {
                        ident_type = TokenType::IDENTIFIER;
                    }
                    tokens.push_back(Token(ident_type, identifier, line));
                } else {
                    ErrorHandler::ReportError(line, "Unexpected Character\n");
                }

                break;
        }
        start = next_unobserved;
    }

    tokens.push_back(Token(TokenType::T_EOF, "--EOF--", line));
    return tokens;
}
