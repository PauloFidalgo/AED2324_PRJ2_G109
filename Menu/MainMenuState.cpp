//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MainMenuState.h"
#include "FlightSearchState.h"
#include <iostream>
#include <sstream>
#include "StatisticsState1.h"
using namespace std;

State* stat = new StatisticsState1();
State* flight = new FlightSearchState();

/*!@brief  função que mostra o menu principal com as diferentes opções.
 *
 */
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

/*!@brief  função que consoante o input do utilizador altera o estado para o menu das estatisticas ou para as pesquisas de voos
 *
 */
State * MainMenuState::handleInput() {
    cout << "Enter your choice: ";
    cin >> userInputStr;
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1:
                State::stateHistory.push(this);
                return flight;
            case 2:
                State::stateHistory.push(this);
                return stat;
            case -1:
                exit(0);
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}
