#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include "utils.h"

using namespace std;
int random_generator() {
    random_device seed;
    mt19937 generate(seed());
    uniform_int_distribution distr(1,100);
    return distr(generate);
}

void print_message() {
    cout << "Welcome to Number Guessing Game!\n";
    cout << "I'm thinking of a number between 1 and 100.\n";
    cout << "You have 5 chances to guess the correct number.\n";
    cout << "Please select the difficulty level:\n";
    cout << "1. Easy (10 chances)\n";
    cout << "2. Medium (5 chances)\n";
    cout << "3. Hard (3 chances)\n";
    cout << "4. Practice (Unlimited chances)\n" << endl;
}

int selection() {
    string difficulty;
    int guessNum;
    int chances = 0;
    cin >> guessNum;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cerr << "Invalid Input! Please enter a number.\n\n";
        return chances;
    }
    if (guessNum == 1) {
        cout << "\nGreat! You have selected the Easy difficulty level.\n"; 
        cout << "Let's start the game!\n" << endl;
        chances = 10;
    }
    else if (guessNum == 2) {
        cout << "\nGreat! You have selected the Medium difficulty level.\n"; 
        cout << "Let's start the game!\n" << endl;
        chances = 5;
    }
    else if (guessNum == 3) {
        cout << "\nGreat! You have selected the Hard difficulty level.\n"; 
        cout << "Let's start the game!\n" << endl;
        chances = 3;
    }
    else if (guessNum == 4) {
        cout << "\nYou have selected the Practice Mode.\n";
        cout << "Let's practice shall we!\n" << endl; 
        chances = INT_MAX;
    }
    else {
        cerr << "\nYou must input the difficulties from 1 to 3.\n\n";
    }
    return chances;
}

void initiate(int chances, int guessNum) {
    int user_input;
    int counter = 0;
    auto firstPoint = chrono::high_resolution_clock::now();
    while (counter < chances) {
        cout << "Enter your guess: ";
        cin >> user_input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cerr << "Invalid Input! Please enter a number.\n\n";
            continue;
        }
        if (user_input == guessNum) {
            counter++;
            cout << "\nCongratulations! You guessed the correct number in " << counter << " attempts.\n";
            auto secondPoint = chrono::high_resolution_clock::now();
            auto durationSec = chrono::duration_cast<chrono::seconds>(secondPoint - firstPoint);
            auto durationMilli = chrono::duration_cast<chrono::milliseconds>(secondPoint - firstPoint);    
            int milliseconds = durationMilli.count() - (durationSec.count() * 1000);
            cout << "You completed the game in " << durationSec.count() << " seconds and " << milliseconds << " milliseconds.\n" << endl;
            return;
        }
        else if (user_input > 100 || user_input < 1) {
            cout << "Invalid Input! Your number has to be between 1 and 100.\n\n";
        }
        else if (user_input > guessNum) {
            counter++;
            cout << "Incorrect! The number is lesser than " << user_input << ".\n\n";
        }
        else if (user_input < guessNum) {
            counter++;
            cout << "Incorrect! The number is greater than " << user_input << ".\n\n";
        }
    }
    cout << "You have unfortunately ran out of chances." << endl;
}