//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MainMenuState.h"
#include <iostream>
#include <sstream>
using namespace std;


FlightSearchState flight;
StatisticsState1 stat;

void MainMenuState::displayMenu() {


    cout << "___________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                --====|====--                             |" << endl;
    cout << "|                                                                      |                                   |" << endl;
    cout << "|                                                                 .-         -.                            |" << endl;
    cout << "|                                                               .'_________'. .'                           |" << endl;
    cout << "|            1. Flight Search                                  /_/_|__|__|_|_                              |" << endl;
    cout << "|            2. Statistics                                    ;'-._       _.-';                            |" << endl;
    cout << "|                                        ,--------------------|    `-. .-'    |--------------------,       |" << endl;
    cout << "|                                        ``  --..__    ___   ;       '       ;   ___    __..--  ``         |" << endl;
    cout << "|                                                  `  -//     .._               /_..//     -  `            |" << endl;
    cout << "|                                                         _//    '._       _.'        _//                  |" << endl;
    cout << "|                                                       `  `        ``---``        `  `                    |" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|                                                                                                          |" << endl;
    cout << "|    exit - Exit                                                                                           |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;

}

State* MainMenuState::handleInput() {
    cout << "Enter your choice: ";
    cin >> userInputStr;
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1:
                State::stateHistory.push(this);
                return &flight;
            case 2:
                State::stateHistory.push(this);
                return &stat;
            case -1:
                exit(0);
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}
