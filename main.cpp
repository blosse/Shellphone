// Ye this is hopefully turning into a music player at some point
#include <iostream>
#include "src/parseInput.cpp"
#include "portaudio.h"
using namespace std;

int main(int argc, char* argv[]) {

    cout << "Welcome to the show\n" << endl;

    return parseInput(argc, argv);

}
