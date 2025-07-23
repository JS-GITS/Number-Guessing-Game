#ifndef UTILS_H
#define UTILS_H

#include <vector>

int random_generator(int lowerNum, int higherNum);
void print_message();
int selection();
std::vector<int> check_highscore();
void write_highscore(int score, int chances);
int hint_system(int guessNum);
void initiate(int chances, int guessNum);
#endif