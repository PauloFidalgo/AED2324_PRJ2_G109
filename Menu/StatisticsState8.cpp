//
// Created by Wagner Pedrosa on 30/12/2023.
//

#include "StatisticsState8.h"
#include "StatisticsState9.h"
#include "iostream"
#include "sstream"

using namespace std;
State* statisticsState9 = new StatisticsState9();
/*!@brief  função que mostra o oitavo menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar
 *
 */
void StatisticsState8::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|              1. Top-k cities with the greatest air traffic capacity                                  |" << endl;
    cout << "|              2. Top-k cities with the least air traffic capacity                                     |" << endl;
    cout << "|              3. Top-k cities per country with the greatest air traffic capacity                      |" << endl;
    cout << "|              4. Top-k cities per country with the least air traffic capacity                         |" << endl;
    cout << "|              5. Top-k countries with the greatest air traffic capacity                               |" << endl;
    cout << "|              6. Top-k countries with the least air traffic capacity                                  |" << endl;
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
    if(userInputStr == "next"){
        State::statisticsHistory.push(this);
        return statisticsState9;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto k = getValidCityK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCity(k,bar,false);
                return this;
            }
            case 2: {
                auto k = getValidCityK();
                if (k == -1) return this;
                int bar = bars();
                manager.getTopKGreatestTrafficCity(k,bar,true);
                return this;
            }
            case 3: {
                auto cities = getValidCitiesSingleCountry();
                if (cities.empty()) return this;
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCityPerCountry(k,cities,bar,false);
                return this;
            }
            case 4: {
                auto cities = getValidCitiesSingleCountry();
                if (cities.empty()) return this;
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCityPerCountry(k,cities,bar,true);
                return this;
            }
            case 5: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCountry(k,bar,false);
                return this;
            }
            case 6:{
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCountry(k,bar,true);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}