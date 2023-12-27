//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATE3_H
#define AED2324_PRJ2_G109_STATISTICSSTATE3_H
#include "State.h"

class StatisticsState3: public State {
private:
    string airline;
    int distance;
    string userInputStr;
    int userInput;
public:
    void displayMenu() override;
    State * handleInput() override;
    string* getValidCity();
    string* getValidCountry();
    int* getValidKForAirport();
};

extern StatisticsState3 statisticsState3;

#endif //AED2324_PRJ2_G109_STATISTICSSTATE3_H
