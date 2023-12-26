//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISTICSSTATECITY_H
#define AED2324_PRJ2_G109_STATISTICSSTATECITY_H
#include "State.h"

class StatisticsStateCity: public State {
private:
    string city;

public:
    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_STATISTICSSTATECITY_H
