#inkluder <iostream>
#inkluder <fstream>
#inkluder <cstdio>

#inkluder <streng>
#inkluder <kart>
#inkluder <vektor>
#inkluder <set>

bruker navnerom std;

kart<streng, streng> getLanguage(bool getAsFlipped) {


    kart<streng, streng> language = {
        
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

    hvis (getAsFlipped == falskt) returner language;

    kart<streng, streng> reversedLang;
    forhver (automatisk word : language) {
        reversedLang[word.second] = word.first;
    }

    returner reversedLang;
}
kart<streng, streng> language = getLanguage(true);

vektor<streng> explodeString(streng text) {

    set<karakter> delimiters  = {
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

    vektor<streng> result;
    streng current;

    forhver (size_t i = 0; i < text.size(); i++) {
        hvis (delimiters.count(text[i])) {
            hvis (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
            result.push_back(streng(1, text[i]));
        } ellers {
            current += text[i];
        }
    }

    hvis (!current.empty()) {
        result.push_back(current);
    }

    returner result;
}

tall hoved(tall argc, karakter* argv[]) {

    hvis (argc < 3 || streng(argv[1]).empty() || streng(argv[2]).empty()) {
        cout << "Usage: " << argv[0] << " <source> <destination>" << endl;
        returner 1;
    }

    karakter* expectedSourceFileName      = argv[1];
    karakter* expectedDestinationFileName = argv[2];

    ifstream Source(expectedSourceFileName);
    streng line;
    streng output;

    /**
     * =======================
     * | Read Source
     * =======================
     * | Reads the source
     * | file provided, og
     * | takes a copy
     */
    hvis (Source.is_open()) {
        imens (getline(Source, line)) {

            vektor<streng> actions = explodeString(line);

            bool inString = falskt;
            forhver (streng& action : actions) {
                hvis (action == "\"" || action == "'") {
                    inString = !inString;
                } ellers hvis (!inString og language.count(action)) {
                    action = language[action];
                }
            }

            forhver (konstant streng& action : actions) {
                output += action;
            }
            output += "\n";

        }
        Source.close();

    } ellers {
        cout << "Failed to open file: " << expectedSourceFileName << endl;
        returner 1;
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
    hvis (Destination.is_open()) {
        Destination << output;
    } ellers {
        cout << "Failed to open file: " << expectedSourceFileName << endl;
        returner 1;
    }

    Destination.close();

    /**
     * COMPILE INTO MACHINE CODE AND CLEAN UP TMP FILE
     */
    streng compileString = streng("g++ .temp_vcl.cpp -o ") + expectedDestinationFileName;
    system(compileString.c_str());

    hvis(remove(".temp_vcl.cpp") != 0) {
        cout << "Failed to delete tmp file: .temp_vcl.cpp" << endl;
        returner 1;
    }

    returner 0;
}
