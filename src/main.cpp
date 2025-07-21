#include "../utilities/utils.h"
#include <iostream>
#include <string>

using namespace std;
int main() {
    int guessNum = random_generator();
    print_message();
    int chances;
    do {
        cout << "Enter your choice: ";
        chances = selection();
    } while (chances == 0);
    initiate(chances, guessNum);
    return 0;
}