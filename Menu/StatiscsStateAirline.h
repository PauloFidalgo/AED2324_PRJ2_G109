//
// Created by Wagner Pedrosa on 26/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATISCSSTATEAIRLINE_H
#define AED2324_PRJ2_G109_STATISCSSTATEAIRLINE_H
#include "State.h"

class StatiscsStateAirline: public State {
private:
    string airline;

public:
    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_STATISCSSTATEAIRLINE_H
