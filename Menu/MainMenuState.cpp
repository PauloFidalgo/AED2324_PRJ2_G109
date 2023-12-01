//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MainMenuState.h"
#include <iostream>
using namespace std;

void MainMenuState::displayMenu() {


    cout << "___________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|            1. Search                                           --====|====--                             |" << endl;
    cout << "|            2. Information                                            |                                   |" << endl;
    cout << "|            3. Statistics                                        .-         -.                            |" << endl;
    cout << "|                                                                .'_________'.                             |" << endl;
    cout << "|                                                              /_/_|__|__|_   _                            |" << endl;
    cout << "|                                                             ;'-._       _.-';                            |" << endl;
    cout << "|                                        ,--------------------|    `-. .-'    |--------------------,       |" << endl;
    cout << "|                                        ``  --..__    ___   ;       '       ;   ___    __..--  ``         |" << endl;
    cout << "|                                                  `  -//     .._               /_..//     -  `            |" << endl;
    cout << "|                                                         _//    '._       _.'        _//                  |" << endl;
    cout << "|                                                       `  `        ``---``        `  `                    |" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|    q - sair                                                                                              |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

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
