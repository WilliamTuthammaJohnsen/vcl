#include <iostream>
#include <string>
#include <vector>

#include "lexerTokens.h"
#include "syntaxTree.h"

using namespace std;

void defineAst(string outputDir, string baseName, vector<string> types) {

}



int main(char* argc[]) {
    
    string outputDir = argc[0];
    
    defineAst(outputDir, "Expr", vector<string> {
        "Binary",
        "Grouping",
        "Literal",
        "Unary"
    });

}