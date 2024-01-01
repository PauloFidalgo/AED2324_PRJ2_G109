//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_CHOOSETYPEOFAIRPORTSTATE_H
#define AED2324_PRJ2_G109_CHOOSETYPEOFAIRPORTSTATE_H
#include "State.h"
#include "string"

class ChooseTypeOfAirportState: public State{

private:
    std::string previousStateType;

public:
    void displayMenu();
    State * handleInput();


};


#endif //AED2324_PRJ2_G109_CHOOSETYPEOFAIRPORTSTATE_H
