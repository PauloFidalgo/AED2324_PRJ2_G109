//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MainMenuState.h"
#include "FilghtSearchState.h"
#include <iostream>
using namespace std;
FilghtSearchState flightSearchState;


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
    cout << "|    q - Quit                                                                                              |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

}

State * MainMenuState::handleInput() {
    int userInput;
    std::cout << " Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            State::stateHistory.push(this);
            return &flightSearchState;
        case 2:
            std:: cout << " PorksState"<< std::endl;
            break;
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
}

