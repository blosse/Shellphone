// This file contains the logic for parsing the CLI input
#include <iostream>
#include <string>
using namespace std;

bool isWavFile(string filename) {
    size_t dotPosition = filename.find_last_of('.');
    if (dotPosition == string::npos) {
        return false;
    }
    if (filename.substr(dotPosition + 1) == "wav") {
        return true;
    }
    return false;
}

int parseInput(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "You didn't select a song :(" << endl;
        return -1;
    }
    for (char i = 1; i < argc; i++) {
        if (isWavFile(argv[i])) {
            cout << "Playing: ";
            cout << argv[i] << endl;
        }
        else {
            cout << "Hey! Thats no .wav file!";
        }
    }
    return 1;
}
