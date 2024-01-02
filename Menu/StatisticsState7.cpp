//
// Created by Wagner Pedrosa on 29/12/2023.
//

#include "StatisticsState7.h"
#include "StatisticsState8.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
State* statisticsState8 = new StatisticsState8();

/*!@brief  função que mostra o sétimo menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar
 *
 */

void StatisticsState7::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                            Statistics:                                               |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                1. Top-k airlines in a given country with the greatest air traffic capacity           |" << endl;
    cout << "|                2. Top-k airlines in a given country with the least air traffic capacity              |" << endl;
    cout << "|                3. Top-k airlines that fly more to a given airport                                    |" << endl;
    cout << "|                4. Top-k airlines that fly less to a given airport                                    |" << endl;
    cout << "|                5. Top-k airlines that fly more to a given airport (% of total airlines flights)      |" << endl;
    cout << "|                6. Top-k airlines that fly less to a given airport (% of total airlines flights)      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 7    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 *
 */
State* StatisticsState7::handleInput() {
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
    if(userInputStr == "next"){
        State::statisticsHistory.push(this);
        return statisticsState8;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                unordered_set<Airline*> airlines = getValidAirlineSingleCountry();
                int distance = getValidAirlineK();
                auto bar = bars();
                if (!airlines.empty() && distance != -1) manager.getTopKGreatestTrafficAirlinePerCountry(distance, airlines,bar,false);
                return this;
            }
            case 2: {
                unordered_set<Airline*> airlines = getValidAirlineSingleCountry();
                int distance = getValidAirlineK();
                auto bar = bars();
                if (!airlines.empty() && distance != -1) manager.getTopKGreatestTrafficAirlinePerCountry(distance, airlines,bar,true);
                return this;
            }
            case 3: {
                auto airport = getValidSingleAirport();
                auto k = getValidAirportK();
                auto bar = bars();
                if (airport && k != -1) manager.getTopKAirlinesThatFlyMoreToAnAirport(k,airport,bar, false);
                return this;
            }
            case 4: {
                auto airport = getValidSingleAirport();
                auto k = getValidAirportK();
                auto bar = bars();
                if (airport && k != -1) manager.getTopKAirlinesThatFlyMoreToAnAirport(k,airport,bar, true);
                return this;
            }
            case 5: {
                auto k = getValidAirportK();
                auto airport = getValidSingleAirport();
                auto bar = bars();
                if (airport && k != -1) manager.getTopKAirlinesThatFlyMoreToAnAirportRatio(k, airport, bar, true);
                return this;
            }
            case 6: {
                auto k = getValidAirportK();
                auto airport = getValidSingleAirport();
                auto bar = bars();
                if (airport && k != -1) manager.getTopKAirlinesThatFlyMoreToAnAirportRatio(k, airport, bar, false);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}