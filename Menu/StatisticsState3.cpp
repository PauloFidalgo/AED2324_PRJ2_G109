//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState3.h"
#include "StatisticsState4.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState3 statisticsState3;

void StatisticsState3::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                          Statistics:                                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Articulation Points                                           |" << endl;
    cout << "|                                     2. Nº Flights per city                                           |" << endl;
    cout << "|                                     3. Countries that have flies to a specific city                  |" << endl;
    cout << "|                                     4. Diameter Pairs                                                |" << endl;
    cout << "|                                     5. Top k greatest traffic airline                                |" << endl;
    cout << "|                                     6. Top k greatest traffic airline per country                    |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                                         |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState3::handleInput() {
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
        return &statisticsState4;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1:
                manager.articulationPoints();
                return this;
            case 2:
                getValidCity();
                manager.getNumFlightsPerCity(this->airline);
                return this;
            case 3:
                getValidCity();
                manager.getCountriesCanFlyToCity(this->airline);
                return this;
            case 4:
                manager.diameterPairs();
                return this;
            case 5:
                cout << "K: ";
                cin >> distance;
                manager.getTopKGreatestTrafficAirline(this->distance);
                return this;
            case 6:
                getValidCountry();
                cout << "K: ";
                cin >> distance;
                manager.getTopKGreatestTrafficAirlinePerCountry(this->distance, this->airline);
                return this;
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}
string *StatisticsState3::getValidCity() {
    do {
        cout << "City : ";
        cin >> airline;
        if (!manager.validateCityName(airline)) {
            cout << "City doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCityName(airline));
    return &airline;
}

string *StatisticsState3::getValidCountry() {
    do {
        cout << "Country : ";
        cin >> airline;
        if (!manager.validateCountryName(airline)) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCountryName(airline));
    return &airline;
}

