//
// Created by Wagner Pedrosa on 02/01/2024.
//

#include "StatisticsState9.h"
#include "iostream"
#include "sstream"

using namespace std;

/*!@brief  função que mostra o oitavo menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar
 *
 */
void StatisticsState9::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                              1. Top-k country with more airlines                                     |" << endl;
    cout << "|                              2. Top-k country with less airlines                                     |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 9    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 *
 */
State* StatisticsState9::handleInput() {
    cout << "Enter your choice: ";
    getline(cin, userInputStr);

    if (userInputStr == "back") {
        if (!State::stateHistory.empty()) {
            State *previousState = State::stateHistory.top();
            State::stateHistory.pop();
            return previousState;
        } else {
            std::cout << "No previous Menu available" << std::endl;
            return this;
        }
    }
    if (userInputStr == "previous") {
        if (!State::statisticsHistory.empty()) {
            State *previousState = State::statisticsHistory.top();
            State::statisticsHistory.pop();
            return previousState;
        }
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKCountriesWithMoreAirlines(k,bar, false);
                return this;
            }
            case 2: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKCountriesWithMoreAirlines(k,bar, true);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}