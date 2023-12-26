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

public:
    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATE3_H
