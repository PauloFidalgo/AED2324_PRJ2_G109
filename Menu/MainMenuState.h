//
// Created by Wagner Pedrosa on 0;1/12/2023.
//

#ifndef AED2324_PRJ2_G109_MAINMENUSTATE_H
#define AED2324_PRJ2_G109_MAINMENUSTATE_H
#include "State.h"


class MainMenuState : public State{
private:
    string userInputStr;
    int userInput;

public:
    void displayMenu() override;
    State * handleInput() override;

};


#endif //AED2324_PRJ2_G109_MAINMENUSTATE_H
