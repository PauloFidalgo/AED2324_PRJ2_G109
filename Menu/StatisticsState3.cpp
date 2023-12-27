//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState3.h"
#include "StatisticsState4.h"
#include "iostream"

using namespace std;
StatisticsState3 statisticsState3;

void StatisticsState3::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   98 - previous page                                                           99 - next page        |" << endl;
    cout << "|                                       Statistics by airline :                                        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Articulation Points                                           |" << endl;
    cout << "|                                     2. Nº Flights per city                                           |" << endl;
    cout << "|                                     3. Countries that have flies to a specific city                  |" << endl;
    cout << "|                                     4. Diameter Pairs                                                |" << endl;
    cout << "|                                     5. Top k greatest traffic airline                                |" << endl;
    cout << "|                                     6. Top k greatest traffic airline per country                    |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Main Menu                                                                                       |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState3::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

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
            manager.getTopKGreatestTrafficAirlinePerCountry(this->distance,this->airline);
            return this;
        case 98:
            if(!State::statisticsHistory.empty()){
                State* previousState = State::statisticsHistory.top();
                State::statisticsHistory.pop();
                return previousState;
            }
        case 99:
            State::statisticsHistory.push(this);
            return &statisticsState4;
        case 0:
            if(!State::stateHistory.empty()){
                State* previousState = State::stateHistory.top();
                State::stateHistory.pop();
                return previousState;
            }
            else {
                std::cout << "No previous Menu available" << std::endl;
                return this;
            }
        case -1:
            exit(0);
        default:
            std:: cout << " Invalid choice. try again"<< std::endl;
            return this;
    }
}

string *StatisticsState3::getValidCity() {
    do {
        cout << "City : ";
        cin >> airline;
        if (manager.getCityAirports().find(airline) == manager.getCityAirports().end()) {
            cout << "City doesn't exist. Try again." << endl;
        }
    } while (manager.getCityAirports().find(airline) == manager.getCityAirports().end());
    return &airline;
}

string *StatisticsState3::getValidCountry() {
    do {
        cout << "Country : ";
        cin >> airline;
        if (manager.getCountryCities().find(airline) == manager.getCountryCities().end()) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (manager.getCountryCities().find(airline) == manager.getCountryCities().end());
    return &airline;
}