#include "help.h"
#include "build_no.h"
#include <string>
#include <iostream>
#include <cstring>
#include <cstdlib>
using std::cout;
using std::endl;
using std::cerr;
using std::string;
bool isHelpArg(char* arg) {
    return !(strcmp(arg, "-h") && strcmp(arg, "--help"));
}
bool isBuildNoArg(char* arg) {
    return !(strcmp(arg, "-b") && strcmp(arg, "--build-no"));
}
void argErrorExit(const char* msg, const char* app) {
        cerr << "E: " << msg << endl;
        cerr << "Try `" << app
             << " --help' for more information." << endl;
        exit(1);
}

void parseArgs(int argc, char* argv[], string& in, string& out) {
    bool printHelp = false;
    bool printBuildNo = false;
    int nonoptc = 0; // number of non-option arguments processed
    out = ".";
    for (int i = 1; i < argc; i++) {
        if (isHelpArg(argv[i])) {
            printHelp = true;
        } else if (isBuildNoArg(argv[i])) {
            printBuildNo = true;
        } else if (argv[i][0] == '-') {
            argErrorExit("Invalid argument.", argv[0]);
        } else {
            if (nonoptc == 0) in = argv[i];
            if (nonoptc == 1) out = argv[i];
            nonoptc++;
        }
    }
    out += "/";
    // nonoptc is 1 if only *in* specified, 2 if both *in* and *out*
    if (nonoptc == 0) argErrorExit("Missing file operand.", argv[0]);
    if (nonoptc >= 3) argErrorExit("Too many arguments.", argv[0]);
    { // just print help message or build number if requested
        if (printHelp) {
            for (int i = 0; i < ___HELP_md_len; i++)
                cout << ___HELP_md[i];
            cout << endl;
        }
        if (printBuildNo) {
            for (int i = 0; i < build_no_txt_len; i++)
                cout << build_no_txt[i];
            cout << endl;
        }
        if (printHelp || printBuildNo) exit(0);
    }
}
