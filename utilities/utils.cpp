#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
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
    cout << "4. Practice (Unlimited chances)\n";
    cout << "5. Check your highscores\n" << endl;
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
    else if (guessNum == 5) {
        vector<int> highscores = check_highscore();
        vector<string> difficulties = {"Easy: ", "Medium: ", "Hard: "};
        cout << "\n";
        for (int i = 0; i < highscores.size(); i++) {
            if (highscores[i] != 0) {
                cout << difficulties[i] << highscores[i] << " attempts\n";
            }
            else {
                cout << difficulties[i] << "No highscore yet\n";
            }
        }
        cout << "\n";
    }
    else {
        cerr << "\nYou must input the difficulties from 1 to 4.\n\n";
    }
    return chances;
}

vector<int> check_highscore() {
    ifstream readFile("./data/highscore.json");
    vector<int> scores = {0, 0, 0};
    vector<string> difficulties = {"\"Easy\": ", "\"Medium\": ", "\"Hard\": "};
    if (!readFile) {
        return scores;
    }
    string line;
    int counter = 0;
    while (getline(readFile, line)) {
        for (string i:difficulties) {
            size_t position = line.find(i);
            if (position != string::npos) {
                string num = line.substr(position + i.size());
                scores[counter] = stoi(num);
                counter++;
            }
        }
    }
    readFile.close();
    return scores;
}

void write_highscore(int score, int chances) {
        vector<int> highscore = check_highscore();
        ofstream writeFile("./data/highscore.json");
        int pos;
        if (chances == 10) {
            pos = 0;
        }
        else if (chances == 5) {
            pos = 1;
        }
        else if (chances == 3) {
            pos = 2;
        }
        else {
            return;
        }
        if (score < highscore[pos] || highscore[pos] == 0) {
            highscore[pos] = score;
        }
        writeFile << "{\n";
        writeFile << "  \"Easy\": " << highscore[0] << ",\n";
        writeFile << "  \"Medium\": " << highscore[1] << ",\n";
        writeFile << "  \"Hard\": " << highscore[2] << "\n";
        writeFile << "}\n";
        writeFile.close();
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
            write_highscore(counter, chances);
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