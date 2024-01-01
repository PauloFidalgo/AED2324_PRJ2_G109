//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_MENUMANAGER_H
#define AED2324_PRJ2_G109_MENUMANAGER_H
#include "State.h"
#include "stack"
class MenuManager {
private:
    State* currentState;

public:
    MenuManager();
    void displayMenu();
    void handleInput();
    ~MenuManager();
    void menuNavigation();
};


#endif //AED2324_PRJ2_G109_MENUMANAGER_H
