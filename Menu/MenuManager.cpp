//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MenuManager.h"
#include "MainMenuState.h"

MenuManager::MenuManager(): currentState(new MainMenuState()) {};
MenuManager::~MenuManager() {
    delete currentState;
}

void MenuManager::menuNavigation() {
    while(currentState) {
        currentState->displayMenu();
        State *nextState = currentState->handleInput();

        delete currentState;

        currentState = nextState;
    }
}
