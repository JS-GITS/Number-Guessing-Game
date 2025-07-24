#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include "utils.h"

using namespace std;
/**
 * @brief Generates a randomly generated number from lowerNum to upperNum
 * 
 * This function takes in two arguments, that being the lowerNum and upperNum. It uses the random library
 * to generate a random number from lowerNum to upperNum by using uniform distribution.
 * 
 * @param lowest range for a randomly generated number
 * @param highest range for a randomly generated number
 * 
 * @return a randomly generated number between lowerNum and upperNum
 */
int random_generator(int lowerNum, int upperNum) {
    random_device seed;
    mt19937 generate(seed());
    uniform_int_distribution distr(lowerNum, upperNum);
    return distr(generate);
}

/**
 * @brief Prints a welcoming message when the you run the program
 * 
 * Function will display a message welcoming the user, telling the user
 * to guess a number between 1 and 100. It will then list out the difficulties: 
 * Easy, Medium, Hard, and Practice, and the option to check your highscore.
 * 
 */
void print_message() {
    cout << "Welcome to Number Guessing Game!\n";
    cout << "I'm thinking of a number between 1 and 100.\n";
    cout << "You have a fixed number of chances to guess the correct number.\n";
    cout << "Please select the difficulty level:\n";
    cout << "1. Easy (10 chances)\n";
    cout << "2. Medium (5 chances)\n";
    cout << "3. Hard (3 chances)\n";
    cout << "4. Practice (Unlimited chances)\n";
    cout << "5. Check your highscores\n" << endl;
}

/**
 * @brief Gives the user a selection to choose a difficulty or check the highscore
 * 
 * This function gives the user a promp in the CLI(Command Line Interface) to choose 
 * a difficulty between 1 and 4, or check the highscore with 5. After picking one of
 * the difficulties, the function returns an integer indicating the number of chances
 * the user have to guess the randomized number.
 * 
 * @return the number of chances the user have depending on the difficulty chosen
 */
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

/**
 * @brief Checks the highscore for each difficulty from the JSON file
 * 
 * This function reads the JSON file, "./data/highscore.json", and creates a vector
 * with the highscores of each difficulty level. If there are no highscore yet, it
 * will be 0, otherwise, it will be non-zero.
 * 
 * @return a vector of highscores of type integer with each difficulty scores
 */
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

/**
 * @brief Writes the new highscore to the JSON file
 * 
 * This function will read the JSON file, "./data/highscore.JSON", and compare
 * the current score with the highscore of that difficulty. If the current score is
 * higher(lower no of attempts), it will replace the highscore and write that score
 * to the JSON file. 
 * 
 * @param the number of attempts needed to guess the correct number
 * @param number of chances given to guess the correct number
 */
void write_highscore(int score, int chances) {
        vector<int> highscore = check_highscore();
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
        ofstream writeFile("./data/highscore.json");
        writeFile << "{\n";
        writeFile << "  \"Easy\": " << highscore[0] << ",\n";
        writeFile << "  \"Medium\": " << highscore[1] << ",\n";
        writeFile << "  \"Hard\": " << highscore[2] << "\n";
        writeFile << "}\n";
        writeFile.close();
}

/**
 * @brief Generates a number that deviates from guessNum by a range of 1 to 15 
 * 
 * Takes in guessNum and generate a random number from 1 to 15, and it either
 * add to subtract it from guessNum. It will then assign it to hintNum, and
 * returns hintNum.
 * 
 * @param the randomly generated number the user is intended to guess
 * 
 * @return a number that is deviated from guessNum by 1 to 15
 */
int hint_system(int guessNum) {
    int rangeNum = random_generator(1,5);
    int sign = random_generator(0,1);
    if (sign == 0) {sign = -1;}
    int hintNum = (sign * rangeNum) + guessNum;
    return hintNum;
}

/**
 * @brief Starts the whole game with the selected difficulty
 * 
 * This function takes in the number of chances and the randomly generated
 * number, and requests user input for a number guess. A time point is recorded as
 * soon as the game starts, and calculates the duration at the end of the game.
 * Hints are given if they make a certain amount of attempts; if the user ran
 * out of chances, there will be a message shown that the game has ended.
 * 
 * @param number of chances given to guess the correct number
 * @param the randomly generated number the user is intended to guess
 * 
 */
void initiate(int chances, int guessNum) {
    int user_input;
    int counter = 0;
    auto firstPoint = chrono::high_resolution_clock::now();
    vector<int> hintCounter = {5, 3, 2};
    vector<int> chancesIndex = {10, 5, 3};
    while (counter < chances) {
            for (int i = 0; i < chancesIndex.size(); i++) {
                if (chancesIndex[i] == chances) {
                    if (counter == hintCounter[i]) {
                        cout << "Hint: The number is near " << hint_system(guessNum) << ".\n";
                    }
                }
            }
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
    cout << "The correct number is: " << guessNum <<  endl;
    cout << "You have unfortunately ran out of chances.\n" << endl;
}