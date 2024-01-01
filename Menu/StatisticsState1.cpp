//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState1.h"
#include "StatisticsState2.h"
#include <sstream>
#include "iostream"

using namespace std;
State* statisticsState2 = new StatisticsState2();

/*!@brief  função que mostra o primeiro menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar 
 *
 */
void StatisticsState1::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                 next - next page     |" << endl;
    cout << "|                                             Statistics                                               |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                    1. No. of flights out of an airport and from how many different airlines          |" << endl;
    cout << "|                    2. No. of flights per airline                                                     |" << endl;
    cout << "|                    3. No. of different countries that a given airport flies to                       |" << endl;
    cout << "|                    4. No. of destinations available for a given city (Distance 1)                    |" << endl;
    cout << "|                    5. No. of destinations available for a given country (Distance 1)                 |" << endl;
    cout << "|                    6. No. of reachable destinations from a given airport in a max number of K stops  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                              page - 1   |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}


/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 * 
 */
State* StatisticsState1::handleInput() {
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
    if(userInputStr == "next"){
        State::statisticsHistory.push(this);
        return statisticsState2;
    }
    if(userInputStr == "exit"){
        exit(0);
    }
    else
    {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                Airport *airport = getValidSingleAirport();
                if (airport) manager.getNumFlightsAndAirlines(airport);
                return this;
            }
            case 2: {
                Airline *airline = getValidSingleAirline();
                if (airline) manager.getNumFlightsPerAirline(airline);
                return this;
            }
            case 3: {
                Airport *airport = getValidSingleAirport();
                if (airport) manager.getCountriesCanFlyToAirport(airport);
                return this;
            }
            case 4: {
                vector<Airport*> airports = getValidAirportsSingleCity();
                if (!airports.empty()) manager.getCityDestinationsDistance1(airports,name);
                return this;
            }
            case 5: {
                auto airports = getValidAirportsSingleCountry();
                if (!airports.empty()) manager.getCountryDestinationsDistance1(airports,name);
                return this;
            }
            case 6: {
                Airport *airport = getValidSingleAirport();
                int distance = getValidAirportK();
                if (airport && distance != -1) manager.getAirportDestinantionsUntilDistanceK(airport, distance);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

