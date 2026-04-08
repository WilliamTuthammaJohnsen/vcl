#include <iostream>
#include <fstream>

#include <string>
#include <map>
#include <vector>

#include "language.h"
#include "stringUtils.h"

using namespace std;


map<string, string> language = getLanguage();




int main(int argc, char* argv[]) {


    char* expectedSourceFileName      = argv[1];
    char* expectedDestinationFileName = argv[2];

    ifstream file(expectedSourceFileName);
    string line;
    string output;

    if (file.is_open()) {
        while (getline(file, line)) {

            vector<string> actions = explodeString(line);

            for (string& action : actions) {
                if (language.count(action)) {
                    action = language[action];
                }
            }

            for (const string& action : actions) {
                output += action;
            }
            output += "\n";

        }
        file.close();
    } else {
        cout << "Failed to open file: " << expectedSourceFileName << endl;
    }

    cout << output;

    return 0;
}