//
// Created by Wagner Pedrosa on 30/12/2023.
//

#include "StatisticsState8.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;

/*!@brief  função que mostra o oitavo menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar
 *
 */
void StatisticsState8::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|              1. Top-k airlines that fly more to a given airport (% of total airlines flights)        |" << endl;
    cout << "|              2. Top-k airlines that fly less to a given airport (% of total airlines flights)        |" << endl;
    cout << "|              3. Strongly connected Components                                                        |" << endl;
    cout << "|              4. Top-k airline with the greatest air traffic capacity                                 |" << endl;
    cout << "|              5. Top-k airport with the least air traffic capacity                                    |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 8    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 *
 */
State* StatisticsState8::handleInput() {
    cout << "Enter your choice: ";
    cin >> userInputStr;

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
                auto k = getValidAirportK();
                if (k == -1) return this;
                auto airport = getValidSingleAirport();
                if (!airport) return this;
                auto bar = bars();
                manager.getTopKAirlinesThatFlyMoreToAnAirportRatio(k, airport, bar, true);
            }
            case 2: {
                auto k = getValidAirportK();
                if (k == -1) return this;
                auto airport = getValidSingleAirport();
                if (!airport) return this;
                auto bar = bars();
                manager.getTopKAirlinesThatFlyMoreToAnAirportRatio(k, airport, bar, false);
                return this;
            }
            case 3: {
                manager.scc();
                return this;
            }
            case 4: {
                int k = getValidAirlineK();
                if (k != -1) manager.getTopKGreatestTrafficAirline(k);
                return this;
            }
            case 5: {

                auto dist = this->getValidAirportK();
                auto bar = bars();
                if (dist != -1) manager.getTopKGreatestTrafficAirport(dist, bar, false);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}