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
    cout << "|                                   1. Country Destinations Until Distance K                           |" << endl;
    cout << "|                                   2. Top K Greatest Traffic City (Ascending)                         |" << endl;
    cout << "|                                   3. Top K Greatest Traffic City (Descending)                        |" << endl;
    cout << "|                                   4. Airlines Per Airport                                            |" << endl;
    cout << "|                                   5. Top K Greatest Traffic Country(Ascending)                       |" << endl;
    cout << "|                                   6. Top K Greatest Traffic Country(Descending)                      |" << endl;
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
                auto airport = getValidAirports();
                if (airport.empty()) return this;
                auto country = getValidSingleCountry();
                if (country.empty()) return this;
                auto dist = this->getValidCountryK();
                if(dist != -1)  manager.getCountryDestinantionsUntilDistanceK(airport,country,dist);
                return this;
            }
            case 2: {
                auto k = getValidCityK();
                if (k == -1) return this;
                int bar = bars();
                if(bar == 1 or bar == 0) manager.getTopKGreatestTrafficCity(k,bar,true);
                return this;

            }
            case 3: {
                auto k = getValidCityK();
                if (k == -1) return this;
                auto bar = bars();
                if(bar == 1 or bar == 0) manager.getTopKGreatestTrafficCity(k,bar,false);
                return this;
            }
            case 4: {
                auto airport = getValidSingleAirport();
                if(airport) manager.listAirlinesPerAirport(airport);
                return this;
            }
            case 5: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCountry(k,bar,true);
                return this;
            }
            case 6: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCountry(k,bar,false);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

