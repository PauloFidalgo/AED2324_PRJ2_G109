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
StatisticsState4 statisticsState4;

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
    cout << "|                                 1. Top K Greatest Traffic Airport                                    |" << endl;
    cout << "|                                 2. Top K Greatest Traffic Airport Per Country (Ascending)            |" << endl;
    cout << "|                                 3. Top K Greatest Traffic Airport Per Country (Descending)           |" << endl;
    cout << "|                                 4. Airport Info                                                      |" << endl;
    cout << "|                                 5. Airline Info                                                      |" << endl;
    cout << "|                                 6. Airports per Country                                              |" << endl;
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
        return &statisticsState5;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto dist = this->getValidAirportK();
                if(dist != -1) manager.getTopKGreatestTrafficAirport(dist);
                return this;
            }
            case 2: {
                auto airports = getValidAirports();
                if (airports.empty()) return this;
                auto dist = getValidAirportK();
                if (dist == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficAirportPerCountry(dist, airports,bar, true);
                return this;
            }
            case 3: {
                auto airports = getValidAirports();
                if (airports.empty()) return this;
                auto dist = getValidAirportK();
                if (dist == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficAirportPerCountry(dist, airports, bar, false);
                return this;
            }
            case 4: {
                auto airport = getValidSingleAirport();
                if (airport) Manager::printAirportInfo(airport);
                return this;
            }
            case 5: {
                auto airline = getValidSingleAirline();
                if (airline) Manager::printAirlineInfo(airline);
                return this;
            }
            case 6: {
                auto airports = getValidAirportsSingleCountry();
                if (!airports.empty()) manager.listAirportsPerCountryCity(airports, name);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}