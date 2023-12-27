//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState1.h"
#include "StatisticsState2.h"
#include <sstream>
#include "iostream"

using namespace std;

StatisticsState1 statisticsState1;
void StatisticsState1::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                 next - next page     |" << endl;
    cout << "|                                             Statistics                                               |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Nº flights and Airlines                                       |" << endl;
    cout << "|                                     2. Nº flights per Airlines                                       |" << endl;
    cout << "|                                     3. Nº country's                                                  |" << endl;
    cout << "|                                     4. Get destinations distance 1                                   |" << endl;
    cout << "|                                     5. Get destinations                                              |" << endl;
    cout << "|                                     6. Get destinations until certain distance                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                                          |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

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
        return &statisticsState2;
    }
    if(userInputStr == "exit"){
        exit(0);
    }
    else
    {
            istringstream(userInputStr) >> userInput;
            switch (userInput) {
                case 1: {
                    Airport *airport = getValidAirport();
                    manager.getNumFlightsAndAirlines(airport);
                    return this;
                }
                case 2: {
                    Airline *airline = getValidAirline();
                    manager.getNumFlightsPerAirline(airline);
                    return this;
                }
                case 3: {
                    Airport *airport = getValidAirport();
                    manager.getCountriesCanFlyToAirport(airport);
                    return this;
                }
                case 4: {
                    string city = getValidCity();
                    manager.getCityDestinationsDistance1(city);
                    return this;
                }
                case 5: {
                    string *country = getValidCountry();
                    manager.getCountryDestinationsDistance1(country);
                    return this;
                }
                case 6: {
                    Airport *airport = getValidAirport();
                    int distance = getValidAirportK();
                    manager.getAirportDestinantionsUntilDistanceK(airport, distance);
                    return this;
                }
                default:
                    std::cout << " Invalid choice. try again" << std::endl;
                    return this;
            }
        }
    }
