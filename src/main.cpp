#include "../utilities/utils.h"
#include <iostream>
#include <string>

using namespace std;
int main() {
    int guessNum = random_generator(1, 100);    // The correct number the user has to guess
    print_message();                            // Displays the welcome and difficulty selection menu

    int chances;                                // Number of attempts user will get, based on difficulty

    do {
        cout << "Enter your choice: ";
        chances = selection();                  // Requests the user to pick a difficulty
    } while (chances == 0);

    initiate(chances, guessNum);                // Starts the game

    // If difficulty is "Practice" mode (unlimited tries), offer replay loop
    while (chances == INT_MAX) {
        char c;
        cout << "Would you like to play another round? (y/n) "; // Asks the user if they want to play again if on practice mode
        cin >> c;
        if (c == 'y') {
            guessNum = random_generator(1, 100);                // Generate a new number
            initiate(chances,guessNum);                         // Restart the game
        }
        else if(c == 'n') {
            break;  // Exit the loop and program
        }
        else {
            cerr << "You must input either 'y' or 'n'.\n\n";
        }
    }
    cout << "Exiting game..." << endl;                          // Prints this message when the program is about to end
    return 0;
}