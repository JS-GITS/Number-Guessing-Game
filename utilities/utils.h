#ifndef UTILS_H
#define UTILS_H

#include <vector>


int random_generator(int lowerNum, int higherNum);      // Returns a randomly generated number between the numbers lowerNum and higherNum
void print_message();                                   // Prints a message when you start the program
int selection();                                        // Gives a selection of the difficulties, as well as the highscore
std::vector<int> check_highscore();                     // Checks the current highscore for all the difficulties
void write_highscore(int score, int chances);           // Writes the current score if it's higher than the current highscore of that difficulty
int hint_system(int guessNum);                          // Gives a hint if the user has exceeded a set amount of attempts
void initiate(int chances, int guessNum);               // Starts the whole game on that difficulty
#endif