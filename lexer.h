#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

typedef struct parsedFlag {
        std::vector<std::string> context;
        int size;

        /**
         * Can be made empty
         */
        parsedFlag() {}

        /**
         * Or with an existing vector
         */
        parsedFlag(std::vector<std::string> _context) {
            this->context = _context;
            this->size = _context.size();
        }
    };

class Lexer {
    public:

    /**
     * Parse short flags
     */
    static parsedFlag parseShortFlag(std::string flag) {
        if (flag == "-h")
            return {{"SYSTEM_PRINT", "HELP"}};
        
        if (flag == "-v")
            return {{"SYSTEM_PRINT", "VERSION"}};

        if (flag == "-o")
            return {{"STRING_AFFECTING", "NEXT_PARAMETER", "OUTPUT_DESTINATION"}};

        return {{"ERROR", "INVALID PARAMETER", flag}};
    }

    static std::vector<parsedFlag> parseShortFlag(std::vector<std::string> flags) {

        std::vector<parsedFlag> result;
        for (std::string flag : flags ){
            result.push_back(parseShortFlag(flag));
        }
        return result;
    }



    /**
     * Parse long flags
     */
    static parsedFlag parseLongFlag(std::string flag) {
        if (flag == "--help")
            return {{"SYSTEM_PRINT", "HELP"}};

        if (flag == "--version")
            return {{"SYSTEM_PRINT", "VERSION"}};

        return {{"ERROR", "INVALID_PARAMETER", flag}};
    }

    static std::vector<parsedFlag> parseLongFlag(std::vector<std::string> flags) {
        std::vector<parsedFlag> result;
        for (std::string flag : flags) {
            result.push_back(parseLongFlag(flag));
        }
        return result;
    }



    /**
     * Parse other parameters
     */
    static parsedFlag parseParameterArgument(std::string flag) {
        return {{"PARAMETER_ARGUMENT", "UNKKNOWN_PARAMETER", flag}};
    }

    static std::vector<parsedFlag> parseParameterArgument(std::vector<std::string> flags) {
        std::vector<parsedFlag> result;
        for (std::string flag : flags) {
            result.push_back(parseParameterArgument(flag));
        }
        return result;
    }
};

#endif
