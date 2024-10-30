// Ye this is hopefully turning into a music player at some point
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    cout << "Welcome to the show\n" << endl;

    if (argc < 2) {
        cout << "You didn't select a song :(" << endl;
        return 0;
    }

    for (char i = 1; i < argc; i++) {

        cout << argv[i] << endl;
    }

    return 0;
}
