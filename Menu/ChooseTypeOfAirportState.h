//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_CHOOSETYPEOFAIRPORTSTATE_H
#define AED2324_PRJ2_G109_CHOOSETYPEOFAIRPORTSTATE_H
#include "State.h"

class ChooseTypeOfAirportState: public State{
    void displayMenu() override;
    State * handleInput() override;


};


#endif //AED2324_PRJ2_G109_CHOOSETYPEOFAIRPORTSTATE_H
