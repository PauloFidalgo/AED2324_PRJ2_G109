//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MainMenuState.h"
#include <iostream>


void MainMenuState::displayMenu() {
  

    std::cout << "Main Menu of the chikis" << std::endl;
    std::cout << "                       " << std::endl;
    std::cout << "option 1" << std::endl;
    std::cout << "Option 2" << std::endl;
    std::cout << "Option 3" << std::endl;

}

State * MainMenuState::handleInput() {
    int userInput;
    std::cout << " Enter your choice: " << std::endl;
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << " ListagensState"<< std::endl;
            break;
        case 2:
            std:: cout << " PorksState"<< std::endl;
            break;
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
}

void MainMenuState::menuNavigation(){
    State* currentState = new MainMenuState();
    while (currentState){
        currentState->displayMenu();
        currentState = currentState->handleInput();
    }

    delete currentState;
}
