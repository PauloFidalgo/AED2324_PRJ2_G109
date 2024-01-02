//
// Created by Wagner Pedrosa on 26/12/2023.
//
#include "StatisticsState1.h"
#include "StatisticsState4.h"
#include "StatisticsState3.h"
#include "StatisticsState5.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
State* statisticsState5 = new StatisticsState5();

/*!@brief  função que mostra o quarto menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar
 *
 */

void StatisticsState4::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                 1. No. of destinations available for a given city (Direct flight)                    |" << endl;
    cout << "|                 2. No. of reachable destinations from a given city in a maximum number of K stops    |" << endl;
    cout << "|                 3. No. of reachable destinations from a given city                                   |" << endl;
    cout << "|                 4. No. of destinations available for a given country (Direct flight)                 |" << endl;
    cout << "|                 5. No. of reachable destinations from a given country in a maximum number of K stops |" << endl;
    cout << "|                 6. No. of reachable destinations from a given country                                |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 4    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas e consultar alguma estatística.
 *
 */
State* StatisticsState4::handleInput() {
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
    if (userInputStr == "next") {
        State::statisticsHistory.push(this);
        return statisticsState5;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                vector<Airport*> airports = getValidAirportsSingleCity();
                if (!airports.empty()) manager.getCityDestinationsDistance1(airports,name);
                return this;
            }
            case 2: {
                vector<Airport*> airports = this->getValidAirportsPerCity();
                int dist = this->getValidCityK();
                if (!airports.empty() && dist != -1) manager.getCityDestinantionsUntilDistanceK(airports,dist);
                return this;
            }
            case 3: {
                vector<Airport*> airports = getValidAirportsSingleCity();
                if (!airports.empty()) manager.getCityDestinantions(airports);
                return this;
            }
            case 4: {
                auto airports = getValidAirportsSingleCountry();
                if (!airports.empty()) manager.getCountryDestinationsDistance1(airports,name);
                return this;

            }
            case 5: {
                vector<Airport*> airports = this->getValidAirportsPerCountry();
                int dist = this->getValidCountryK();
                if (!airports.empty() && dist != -1) manager.getCountryDestinantionsUntilDistanceK(airports,dist);
                return this;
            }
            case 6: {
                vector<Airport*> airports = this->getValidAirportsPerCountry();
                if (!airports.empty()) manager.getCountryDestinantions(airports);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}