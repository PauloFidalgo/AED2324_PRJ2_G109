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
                case 1:
                    getValidAirportCode();
                    manager.getNumFlightsAndAirlines(airport);
                    return this;
                case 2:
                    getValidAirlineCode();
                    manager.getNumFlightsPerAirline(airline);
                    return this;
                case 3:
                    getValidAirportCode();
                    manager.getCountriesCanFlyToAirport(airport);
                    return this;
                case 4:
                    getValidCity();
                    manager.getCityDestinationsDistance1(code);
                    return this;
                case 5:
                    getValidCountry();
                    manager.getCountryDestinationsDistance1(code);
                    return this;
                case 6:
                    getValidAirportCode();
                    getValidAirportK();
                    manager.getAirportDestinantionsUntilDistanceK(airport,distance);
                    return this;
                default:
                    std::cout << " Invalid choice. try again" << std::endl;
                    return this;
            }
        }
    }

Airport* StatisticsState1::getValidAirportCode() {

    do {
        cout << "Airport code: ";
        cin >> code;
        airport = manager.getAirportPerCode(code);
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}

Airline* StatisticsState1::getValidAirlineCode() {

    do {
        cout << "Airline code: ";
        cin >> code;
        airline = manager.getAirlinePerCode(code);
        if (!airline) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (!airline);
    return airline;
}

string* StatisticsState1::getValidCity() {

    do {
        cout << "Airline code: ";
        cin >> code;
        if (!manager.validateCityName(code)) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCityName(code));
    return &code;
}

string* StatisticsState1::getValidCountry() {

    do {
        cout << "Airline code: ";
        cin >> code;
        if (!manager.validateCountryName(code)) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCountryName(code));
    return &code;
}

int *StatisticsState1::getValidAirportK() {
    do {
        cout << "K : ";
        cin >> distance;
        if (distance < 0 or distance > manager.getAirports().size()) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (distance < 0 or distance > manager.getAirports().size());
    return &distance;
}