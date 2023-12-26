//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MainMenuState.h"
#include "FlightSearchState.h"
#include <iostream>
#include "StatisticsStateCode.h"
using namespace std;

FlightSearchState flightSearchState;
StatisticsStateCode statisticsStateCode;


void MainMenuState::displayMenu() {


    cout << "___________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                --====|====--                             |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                 .-         -.                            |" << endl;
    cout << "|                                                                .'_________'.                             |" << endl;
    cout << "|            1. Flight Search                                  /_/_|__|__|_   _                            |" << endl;
    cout << "|            2. Statistics                                    ;'-._       _.-';                            |" << endl;
    cout << "|                                        ,--------------------|    `-. .-'    |--------------------,       |" << endl;
    cout << "|                                        ``  --..__    ___   ;       '       ;   ___    __..--  ``         |" << endl;
    cout << "|                                                  `  -//     .._               /_..//     -  `            |" << endl;
    cout << "|                                                         _//    '._       _.'        _//                  |" << endl;
    cout << "|                                                       `  `        ``---``        `  `                    |" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|    -1 - Quit                                                                                             |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

}

State * MainMenuState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            State::stateHistory.push(this);
            return &flightSearchState;
        case 2:
            State::stateHistory.push(this);
            return &statisticsStateCode;
        case -1:
            exit(0);
        default:
            std::cout << " Invalid choice. try again" << std::endl;
            return this;
    }
    return nullptr;
}

