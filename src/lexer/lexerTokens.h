#ifndef LEXER_TOKENS_H
#define LEXER_TOKENS_H

#include <iostream>
#include <string>
#include <any>

/**
 * Token Type
 * The different token classifications
 * These are used to flag tokens later
 */
enum TokenType {
    // Single Character Containers
        L_PAREN, R_PAREN      , // ()
        L_BRACE, R_BRACE      , // []
        L_CURLY, R_CURLY      , // {}
        COMMA  , DOT          , // ,.
        MINUS  , PLUS         , // -+
        COLON  , SEMICOLON    , // :;
        SLASH  ,                // /
        STAR   ,                // *
                                //
    // Conditions ------------- //
        BANG   , BANG_EQUAL   , // ! != 
        EQUAL  , EQUAL_EQUAL  , // = ==
        GREATER, GREATER_EQUAL, // < <=
        LESS   , LESS_EQUAL   , // > >=
                                //
    // Literals --------------- //
        IDENTIFIER,             // 
        INT    ,                // 123
        FLOAT  ,                // 1.23
        DECIMAL,                // 1.23~15
        NUMBER ,                // ANY number
        CHAR   ,                // 'a'
        STRING ,                // "abc"
        BOOL   ,                // true
                                // 
    // Planned support -------- //
      // OCT,                   // FFFFFFFF
      // HEX,                   // FFFFFF
      // BINARY,                // 0x1111
                                //
    // Keywords --------------- //
        AND    ,                // &&
        OR     ,                // ||
        IF     ,                // if
        ELSE   ,                // else
        TRUE   ,                // true
        FALSE  ,                // false
        CLASS  ,                // class
        FOR    ,                // for(d,c,f)
        WHILE  ,                // while
        SUPER  ,                // super
        RETURN ,                // return
        PRINT  ,                // print

    // Endings
        EOL, EOD               // EndOfLine, EndOfDocument
};

/**
 * Token
 * This is an object class that stores data
 * it is mostly used for feedback and validation
 */
class Token {
    TokenType _type;
    std::string _lexeme;
    std::any _literal;
    int _line;

    public:

        /**
         * Token
         * @param type    TokenType   - The type of token
         * @param lexeme  std::string - Lexme content
         * @param literal std::any    - Literal type
         * @param line    int         - Line number
         */
        Token(TokenType type, std::string lexeme, std::any literal, int line) {
            _type = type;
            _lexeme = lexeme;
            _literal = literal;
            _line = line;
        }
        /**
         * Allow non-defined declaration
         */
        Token () {}
};

#endif