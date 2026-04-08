#include "stringUtils.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>
using namespace std;

vector<string> explodeString(string text) {

    set<char> delimiters  = {
        // Common seperators
        ' ',',','.',';',':',
        // Math
        '+','-','*','/','=','#',
        // Enclosure
        '{','}','[',']',
        '(',')','\'','"',
        '<','>',
        // Pointers
        '*','&',
        // Boolean logic
        '|','!',
        // text specific
        '\n'
    };

    vector<string> result;
    string current;

    for (size_t i = 0; i < text.size(); i++) {
        if (delimiters.count(text[i])) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
            // Make exception for header tags
            if (text[i] == '#') {
                result.push_back(" ");
            }
            result.push_back(string(1, text[i]));
        } else {
            current += text[i];
        }
    }

    if (!current.empty()) {
        result.push_back(current);
    }

    return result;
}