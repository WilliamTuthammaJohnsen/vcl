#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>

typedef struct Token {
        std::vector<std::string> context;
        int size;

        /**
         * Can be made empty
         */
        Token() {}

        /**
         * Or with an existing vector
         */
        Token(std::vector<std::string> _context) {
            this->context = _context;
            this->size = _context.size();
        }
    };

class Parser {
    public:

    /**
     * Parse short flags
     */
    static Token parseShortFlag(std::string flag) {
        if (flag == "-h")
            return {{"SYSTEM_PRINT", "HELP"}};

        if (flag == "-v")
            return {{"SYSTEM_PRINT", "VERSION"}};

        if (flag == "-o")
            return {{"STRING_AFFECTING", "NEXT_PARAMETER", "OUTPUT_DESTINATION"}};

        return {{"ERROR", "INVALID PARAMETER", flag}};
    }

    static std::vector<Token> parseShortFlag(std::vector<std::string> flags) {

        std::vector<Token> result;
        for (std::string flag : flags ){
            result.push_back(parseShortFlag(flag));
        }
        return result;
    }



    /**
     * Parse long flags
     */
    static Token parseLongFlag(std::string flag) {
        if (flag == "--help")
            return {{"SYSTEM_PRINT", "HELP"}};

        if (flag == "--version")
            return {{"SYSTEM_PRINT", "VERSION"}};

        return {{"ERROR", "INVALID_PARAMETER", flag}};
    }

    static std::vector<Token> parseLongFlag(std::vector<std::string> flags) {
        std::vector<Token> result;
        for (std::string flag : flags) {
            result.push_back(parseLongFlag(flag));
        }
        return result;
    }



    /**
     * Parse other parameters
     */
    static Token parseParameterArgument(std::string flag) {
        return {{"PARAMETER_ARGUMENT", "UNKNOWN_PARAMETER", flag}};
    }

    static std::vector<Token> parseParameterArgument(std::vector<std::string> flags) {
        std::vector<Token> result;
        for (std::string flag : flags) {
            result.push_back(parseParameterArgument(flag));
        }
        return result;
    }
};

#endif
