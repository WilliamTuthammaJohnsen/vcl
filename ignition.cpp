#include <iostream>
#include <fstream>
#include <cstdio>

#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

map<string, string> getCodeLanguage(bool getAsFlipped) {


    map<string, string> codeLanguage = {
        
        // Headers
        {"include",             "inkluder"},
        {"define",              "definer"},
        {"ifndef",              "hvisikkedefinert"},
        {"endif",               "slutthvis"},
        // Commonly used
        {"string",              "streng"},
        {"vector",              "vektor"},
        {"list",                "liste"},
        {"stack",               "stabel"},
        {"queue",               "kø"},
        {"dequeue",             "nedkø"},
        {"map",                 "kart"},
        // Standard Library
        {"alignas",             "plassersom"},
        {"alignof",             "plasserav"},
        {"and",                 "og"},
        {"and_eq",              "og_erlik"},
        {"asm",                 "asm"},         // assembly
        {"atomic_cancel",       "atomisk_kansellering"},
        {"atomic_commit",       "atomisk_utføring"},
        {"atomic_noexcept",     "atomisk_ingenunntak"},
        {"auto",                "automatisk"},
        {"bitand",              "bitog"},
        {"bitor",               "biteller"},
        {"bool",                "bool"},
        {"break",               "knus"},
        {"case",                "sak"},
        {"catch",               "fang"},
        {"char",                "karakter"},
        {"char8_t",             "karakter_8t"},
        {"char_16t",            "karakter_16t"},
        {"char_32t",            "karakter_32t"},
        {"class",               "klasse"},
        {"compl",               "compl"},       // flips bytes
        {"concept",             "konsept"},
        {"const",               "konstant"},
        {"consteval",           "konstantvurd"},
        {"constexpr",           "konstantutrk"},
        {"constinit",           "konstantstrt"},
        {"const_cast",          "constant_støp"},
        {"continue",            "fortsett"},
        {"contract_assert",     "konstant_hevd"},
        {"co_await",            "co_vent"},
        {"co_return",           "co_returner"},
        {"co_yield",            "co_innhøst"},
        {"decltype",            "erklærtype"},
        {"default",             "standard"},
        {"felete",              "fslett"},
        {"do",                  "gjør"},
        {"double",              "dobbel"},
        {"dynamic_cast",        "dynamisk_støp"},
        {"else",                "ellers"},
        {"enum",                "fortegnelse"},
        {"explicit",            "eksplisitt"},
        {"export",              "eksporter"},
        {"extern",              "ekstern"},
        {"false",               "falskt"},
        {"float",               "flyt"},
        {"for",                 "forhver"},
        {"friend",              "venn"},
        {"goto",                "gåtil"},
        {"if",                  "hvis"},
        {"inline",              "ilinjen"},
        {"int",                 "tall"},
        {"long",                "lang"},
        {"mutable",             "muterbar"},
        {"namespace",           "navnerom"},
        {"new",                 "ny"},
        {"noexcept",            "ikkeeksplisitt"},
        {"not",                 "ikke"},
        {"not_eq",              "ikke_erlik"},
        {"nullptr",             "nullpunkt"},
        {"operator",            "opperatør"},
        {"or",                  "eller"},
        {"or_eq",               "eller_erlik"},
        {"private",             "privat"},
        {"protected",           "beskyttet"},
        {"public",              "offentlig"},
        {"reflexpr",            "refleksutrykk"},
        {"register",            "registrer"},
        {"reinterpret_cast",    "omtolk_støp"},
        {"requires",            "trenger"},
        {"return",              "returner"},
        {"short",               "kort"},
        {"signed",              "signert"},
        {"sizeof",              "størrelsenav"},
        {"static",              "statisk"},
        {"static_assert",       "statisk_hev"},
        {"static_cast",         "statisk_støp"},
        {"struct",              "strukt"},
        {"switch",              "bytt"},
        {"synchronized",        "synkronisert"},
        {"template",            "templat"},
        {"this",                "dette"},
        {"thread_local",        "tråd_lokal"},
        {"throw",               "kast"},
        {"true",                "sant"},
        {"try",                 "prøv"},
        {"typedef",             "typedef"},
        {"typeid",              "typeid"},
        {"typename",            "typenavn"},
        {"union",               "forening"},
        {"unsigned",            "usignert"},
        {"using",               "bruker"},
        {"virtual",             "virituell"},
        {"void",                "tomrom"},
        {"volatile",            "flyktig"},
        {"wchar_t",             "bkarakter_t"},     // Bred Karakter _ t
        {"while",               "imens"},
        {"xor",                 "ekskludereller"},
        {"xor_eq",              "ekskluder_erlik"},
        {"main",                "hoved"}
    };

    if (getAsFlipped == false) return codeLanguage;

    map<string, string> reversedLang;
    for (auto word : codeLanguage) {
        reversedLang[word.second] = word.first;
    }

    return reversedLang;
}
map<string, string> codeLanguage = getCodeLanguage(true);

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

int main(int argc, char* argv[]) {

    if (argc < 3 || string(argv[1]).empty() || string(argv[2]).empty()) {
        cout << "Usage: " << argv[0] << " <source> <destination>" << endl;
        return 1;
    }

    char* expectedSourceFileName      = argv[1];
    char* expectedDestinationFileName = argv[2];

    ifstream Source(expectedSourceFileName);
    string line;
    string output;

    /**
     * =======================
     * | Read Source
     * =======================
     * | Reads the source
     * | file provided, and
     * | takes a copy
     */
    if (Source.is_open()) {
        while (getline(Source, line)) {

            vector<string> actions = explodeString(line);

            bool inString = false;
            for (string& action : actions) {
                if (action == "\"" || action == "'") {
                    inString = !inString;
                } else if (!inString && codeLanguage.count(action)) {
                    action = codeLanguage[action];
                }
            }

            for (const string& action : actions) {
                output += action;
            }
            output += "\n";

        }
        Source.close();

    } else {
        cout << "Failed to open file: " << expectedSourceFileName << endl;
        return 1;
    }

    /**
     * =======================
     * | Write to destination
     * =======================
     * | Writes the resulting
     * | convertion to the
     * | destination file
     */
    ofstream Destination(".temp_vcl.cpp");
    if (Destination.is_open()) {
        Destination << output;
    } else {
        cout << "Failed to open file: " << expectedSourceFileName << endl;
        return 1;
    }

    Destination.close();

    /**
     * COMPILE INTO MACHINE CODE AND CLEAN UP TMP FILE
     */
    string compileString = string("g++ .temp_vcl.cpp -o ") + expectedDestinationFileName;
    system(compileString.c_str());

    if(remove(".temp_vcl.cpp") != 0) {
        cout << "Failed to delete tmp file: .temp_vcl.cpp" << endl;
        return 1;
    }

    return 0;
}