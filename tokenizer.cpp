#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>

#include "parser.h"

using namespace std;

typedef struct tokenizedArguments {
    vector<string> longFlags;
    vector<string> shortFlags;
    vector<string> parameterArguments;
};

tokenizedArguments tokenizeArguments(int argc, char* argv[]) {

    tokenizedArguments result;

    for(int i=1; i < argc; i++) {

        // Check if argument is a flag
        if (argv[i][0] == '-') {

            // Check if argument is a long flag
            if (argv[i][1] == '-') {

                result.longFlags.push_back((string) argv[i]);
                continue;

            }

            result.shortFlags.push_back((string) argv[i]);
            continue;
        }

        // Else, must be a normal argument
        result.parameterArguments.push_back((string) argv[i]);
        continue;

    }

    return result;
}



string systemPrint(vector<string> tokenLine) {
    return "";
}


void dumpVectorToken(vector<Token> vectorToken) {
        for(Token token : vectorToken) {
            
        }
    }

int main(int argc, char* argv[]) {

    tokenizedArguments tokens = tokenizeArguments(argc, argv);

    vector<Token> shortFlags         = Parser::parseShortFlag        (tokens.shortFlags);
    vector<Token> longFlags          = Parser::parseLongFlag         (tokens.longFlags);
    vector<Token> parameterArguments = Parser::parseParameterArgument(tokens.parameterArguments);

    

    // scanFile();

    // writeResult();

    // compileResult();

}