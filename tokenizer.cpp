#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <fstream>

using namespace std;

vector<string> tokenizeShortFlags(char argv[]) {

    // Whops, doesn't account for args like "-hv" for help version

    string arg(argv);

    if (arg == "-h")
        return {"SYSTEM_PRINT", "HELP"};

    if (arg == "-v")
        return {"SYSTEM_PRINT", "VERSION"};

    if (arg == "-o")
        return {
                "STRING_AFFECTING", 
                "NEXT_PARAMETER", 
                "OUTPUT_DESTINATION"
        };

    return {"ERROR", "INVALID PARAMETER", arg};
}

vector<string> tokenizeLongFlags(char argv[]) {

    string arg(argv);

    if (arg == "--help")
        return {"SYSTEM_PRINT", "HELP"};

    if (arg == "--version")
        return {"SYSTEM_PRINT", "VERSION"};

    return {"ERROR", "INVALID_PARAMETER", arg};
}

vector<string> tokenizeParameterArgument(char* argv) {

    // Normally, this is a parameter to use with earlier flags
    // Like: "program compileSource -o saveDestionation"
    //                ^^^^^^^^^^^^^    ^^^^^^^^^^^^^^^^

    return {"PARAMETER_ARGUMENT", "UNKKNOWN_PARAMETER", string(argv)};
}

vector<vector<string>> tokenizeArguments(int argc, char* argv[]) {

    vector<vector<string>> result;

    for(int i=1; i < argc; i++) {

        // Check if argument is a flag
        if (argv[i][0] == '-') {

            // Check if argument is a long flag
            if (argv[i][1] == '-') {

                vector<string> tokenized = tokenizeLongFlags(argv[i]);
                result.push_back(tokenized);
                continue;

            }

            vector<string> tokenized = tokenizeShortFlags(argv[i]);
            result.push_back(tokenized);
            continue;
        }

        // Else, must be a normal param
        vector<string> tokenized = tokenizeParameterArgument(argv[i]);
        result.push_back(tokenized);
        continue;

    }

    return result;
}





string systemPrint(vector<string> tokenLine) {
    
}


int main(int argc, char* argv[]) {

    vector<vector<string>> tokens = tokenizeArguments(argc, argv);

    for (vector<string> tokenLine : tokens) {
    }

    // scanFile();

    // writeResult();

    // compileResult();

}