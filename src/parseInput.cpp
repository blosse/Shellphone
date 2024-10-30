// This file contains the logic for parsing the CLI input
#include <iostream>
using namespace std;

int parseInput(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "You didn't select a song :(" << endl;
        return -1;
    }
    for (char i = 1; i < argc; i++) {
        cout << argv[i] << endl;
    }
    return 0;
}
