//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE3_H
#define AED2324_PRJ2_G109_STATISTICSSTATE3_H
#include "State.h"
#include "StatisticsState4.h"

class StatisticsState3: public State {
private:
    string userInputStr;
    int userInput;
public:
    void displayMenu();
    State * handleInput();
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATE3_H
