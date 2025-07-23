#include "../utilities/utils.h"
#include <iostream>
#include <string>

using namespace std;
int main() {
    int guessNum = random_generator(1, 100);
    print_message();
    int chances;
    do {
        cout << "Enter your choice: ";
        chances = selection();
    } while (chances == 0);
    initiate(chances, guessNum);
    while (chances == INT_MAX) {
        char c;
        cout << "Would you like to play another round? (y/n) ";
        cin >> c;
        if (c == 'y') {
            guessNum = random_generator(1, 100);
            initiate(chances,guessNum);
        }
        else if(c == 'n') {
            break;
        }
        else {
            cerr << "You must input either \'y\' or \'n\'.\n";
        }
    }
    cout << "Exiting game..." << endl;
    return 0;
}