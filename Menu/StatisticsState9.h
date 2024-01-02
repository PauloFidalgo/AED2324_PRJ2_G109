//
// Created by Wagner Pedrosa on 02/01/2024.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE9_H
#define AED2324_PRJ2_G109_STATISTICSSTATE9_H
#include "State.h"

class StatisticsState9: public State {
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu();
    State * handleInput();
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATE9_H
