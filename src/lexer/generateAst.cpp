#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ranges>

#include "lexerTokens.h"
#include "syntaxTree.h"

using namespace std;


/*****************************
 * 
 * Make some tools
 * 
 * *****************************
 */
#include <algorithm>
#include <cctype>
#include <any>
string toUpper(string text) {

    // Modifies the string in-place to uppercase
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return toupper(c);
    });

    return text;
}
string trim(string &s) {
    const std::string WHITESPACE = " \n\r\t\f\v";

    size_t start = s.find_first_not_of(WHITESPACE);
    if (start == string::npos) return ""; // All whitespace or empty

    size_t end = s.find_last_not_of(WHITESPACE);
    return s.substr(start, end - start + 1);
}
vector<string> split(string haystack, char delimiter) {

    for (size_t i = 0; i < haystack.size(); i++) {
        if (haystack.at(i) == delimiter) {

            string firstPart  = haystack.substr(0, i);
            string secondPart = haystack.substr(i + 1);

            return {firstPart, secondPart};
        }
    }

    return {haystack};
}


/**************************************
 *  
 * Make some header files
 * 
 * *************************************
 */

void defineAst(string outputDir, string baseName, vector<string> types) {

    string path = outputDir + "/" + baseName + ".h";

    ofstream Writer(path);

    // WRITE HEAD
    string hName = toUpper(trim(baseName)) + "_H";
    Writer << "#ifndef " << hName << "\n";
    Writer << "#define " << hName << "\n";
    Writer << "\n";

    // DEFINE CLASS
    Writer << "class " << baseName << " {" << "\n";

    // FILL CLASS
    for (string type : types) {

    }

    // END CLASS
    Writer << "}" << "\n";

    // WRITE END
    Writer << "\n";
    Writer << "#endif\n";
    Writer.close();
}



int main(int argc, char* argv[]) {

    if (argc < 2)
        return 1;
    
    string outputDir = argv[1];
    
    defineAst(outputDir, "Expr", vector<string> {
        "Binary   : Expr left, Token operator, Expr right",
        "Grouping : Expr expression",
        "Literal  : Object value",
        "Unary    : Token operator, Expr right"
    });

    return 0;
}