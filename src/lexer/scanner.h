#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <any>

#include "lexerTokens.h"

class Scanner {

    /**
     * DEFINITION
     */
        std::string _source;
        std::vector<Token> _tokens;

        int _start = 0;
        int _current = 0;
        int _line = 1;

        std::map<std::string, TokenType> keywords = {
            {"and", AND},
            {"and", OR},
            {"and", IF},
            {"and", ELSE},
            {"and", TRUE},
            {"and", FALSE},
            {"and", CLASS},
            {"and", FOR},
            {"and", WHILE},
            {"and", SUPER},
            {"and", RETURN},
            {"and", PRINT}
        };

    /**
     * HELPERS
     */
        bool isAtEnd() {
            return _current >= _source.size();
        }

        char advance() {
            return _source[_current++];
        }

        bool match(char expected) {
            if (isAtEnd()) return false;
            if (_source[_current] != expected) return false;

            _current++;
            return true;
        }

        char peek() {
            if (isAtEnd()) return '\0';
            return _source[_current];
        }

        char peekNext() {
            if (_current +1 >= _source.size()) return '\0';
            return _source[_current +1];
        }

        /**
         * Letters and numbers are stored in order, and thus have a climbing index
         * This allows for some... weird checks like this to ensure that a character is in range of their counterparts
         */
        bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        bool isAlpha(char c) {
            return  (c >= 'a' && c <= 'z') ||
                    (c >= 'A' && c <= 'Z') ||
                    c == '_';
        }

        bool isAlphaNumeric(char c) {
            return isAlpha(c) || isDigit(c);
        }

        void identifier() {
            while (isAlphaNumeric(peek())) advance();

            std::string text = _source.substr(_start, _current - _start);
            TokenType type = IDENTIFIER;

            for (auto keyword : keywords) {
                if (text == keyword.first) type = keyword.second;
            }

            addToken(type);
        }
    
    /**
     * TOKENS
     */

        void addToken(TokenType type, std::any literal) {
            std::string text = _source.substr(_start, _current - _start);
            _tokens.push_back(Token(type, text, literal, _line));
        }

        void addToken(TokenType type) {
            addToken(type,nullptr);
        }

    /**
     * TYPES
     */

        void stringType() {
            while (peek() != '"' && !isAtEnd()) {
                if (peek() == '\n') _line++;
                advance();
            }

            if (isAtEnd()) {
                std::cout << "Unterminated string" << std::endl;
                return;
            }

            advance();

            std::string value = _source.substr(_start +1, _current - _start - 1);
            addToken(STRING, value);
        }

        void numberType() {
            while(isDigit(peek())) advance();

            if (peek() == '.' && isDigit(peekNext())) {
                advance();

                while (isDigit(peek())) advance();
            }

            addToken(
                NUMBER,
                (double) stod(_source.substr(_start, _current - _start))
            );
        }

    void scanToken() {
        char c = advance();
        switch (c) {
            case '(': addToken(L_PAREN); break;
            case ')': addToken(R_PAREN); break;
            case '[': addToken(L_BRACE); break;
            case ']': addToken(R_BRACE); break;
            case '{': addToken(L_BRACE); break;
            case '}': addToken(R_BRACE); break;
            case ',': addToken(COMMA); break;
            case '.': addToken(DOT); break;
            case '-': addToken(MINUS); break;
            case '+': addToken(PLUS); break;
            case ';': addToken(SEMICOLON); break;
            case '*': addToken(STAR); break;

            /**
             * Condition detection
             */
            case '!':
                addToken(match('=') ? BANG_EQUAL : BANG);
                break;
            case '=':
                addToken(match('=') ? EQUAL_EQUAL : EQUAL);
                break;
            case '<':
                addToken(match('=') ? LESS_EQUAL : LESS);
                break;
            case '>':
                addToken(match('=') ? GREATER_EQUAL : GREATER);
                break;

            /**
             * Comments
             */
            case '/':
                if (match('/')) {
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    addToken(SLASH);
                }
                break;

            /**
             * Special characters
             */
            case ' ':
            case '\r':
            case '\t':
                // Ignore whitespace.
                break;

            case '\n':
                _line++;
                break;

            /**
             * Types
             */
            case '"': stringType(); break;
            // case '\'': charType(); break;

            /**
             * Errors
             */
            default:
                if (isDigit(c)) {
                    numberType();
                } else if (isAlpha(c)) {
                    identifier();
                } else {
                    std::cout << _line << "Unexpected Character" << std::endl;
                }
        }
    }
    

    public:
        void scanner(std::string source) {
            _source = source;
        }

        std::vector<Token> scanTokens() {

            while (!isAtEnd()) {
                _start = _current;
                scanToken();
            }

            _tokens.push_back(Token(EOD, "", nullptr, _line));
            return _tokens;
        }
};

#endif