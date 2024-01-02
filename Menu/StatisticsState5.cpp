//
// Created by Wagner Pedrosa on 28/12/2023.
//

#include "StatisticsState5.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;

State* statisticsState6 = new StatisticsState6();

/*!@brief  função que mostra o quinto menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar 
 *
 */
void StatisticsState5::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|             1. Top-k airports with the greatest air traffic capacity                                 |" << endl;
    cout << "|             2. Top-k airports with the least air traffic capacity                                    |" << endl;
    cout << "|             3. Top-k airports in a given city with the greatest air traffic capacity                 |" << endl;
    cout << "|             4. Top-k airports in a given city with the least air traffic capacity                    |" << endl;
    cout << "|             5. Top-k airports in a given country with the greatest air traffic capacity              |" << endl;
    cout << "|             6. Top-k airports in a given country with the least air traffic capacity                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 5    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 * 
 */
State* StatisticsState5::handleInput() {
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
    if (userInputStr == "next") {
        State::statisticsHistory.push(this);
        return statisticsState6;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                int k = getValidAirportK();
                auto bar = bars();
                if (k != -1) manager.getTopKGreatestTrafficAirport(k,bar ,false);
                return this;
            }
            case 2: {
                int k = getValidAirportK();
                auto bar = bars();
                if (k != -1) manager.getTopKGreatestTrafficAirport(k,bar ,true);
                return this;

            }
            case 3: {
                auto airports = getValidAirportsSingleCity();
                auto k = getValidAirportK();
                auto bar =  bars();
                if (!airports.empty() && k != -1 ) manager.getTopKGreatestTrafficAirportPerCity(k,airports,bar,false);
                return this;
            }
            case 4: {
                auto airports = getValidAirportsSingleCity();
                auto k = getValidAirportK();
                auto bar =  bars();
                if (!airports.empty() && k != -1 ) manager.getTopKGreatestTrafficAirportPerCity(k,airports,bar,true);
                return this;
            }
            case 5: {
                auto airports = getValidAirportsSingleCountry();
                auto k = getValidAirportK();
                auto bar =  bars();
                if (!airports.empty() && k != -1 ) manager.getTopKGreatestTrafficAirportPerCountry(k,airports,bar,false);
                return this;
            }
            case 6: {
                auto airports = getValidAirportsSingleCountry();
                auto k = getValidAirportK();
                auto bar =  bars();
                if (!airports.empty() && k != -1 ) manager.getTopKGreatestTrafficAirportPerCountry(k,airports,bar, true);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

