//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FlightSearchState.h"
#include <iostream>
#include <string>
#include "FilterState.h"
#include <sstream>
#include "CoordinatesFilterState.h"


using namespace std;


FlightSearchState::FlightSearchState(): isSelectingFrom(true){}

void FlightSearchState::displayMenu() {
    const std::string origin = isSelectingFrom ? "From" : "  To";
    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|      "<< origin << "                     Search by:                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Airport                                                      |" << endl;
    cout << "|                                     2 - City                                                         |" << endl;
    cout << "|                                     3 - Country                                                      |" << endl;
    cout << "|                                     4 - Coordinates ( Closest Airport )                              |" << endl;
    cout << "|                                     5 - Coordinates ( 25 Km Range )                                  |" << endl;
    cout << "|                                     6 - Coordinates ( 50 Km Range )                                  |" << endl;
    cout << "|                                     7 - Coordinates ( 100 Km Range )                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Go back                                                                                       |" << endl;
    cout << "| exit - Exit                                                                                          |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State *FlightSearchState::handleInput() {
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
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1:
                std::cout << "Airport code or name " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromCode = this->getValidAirport();
                    fromAirports.push_back(fromCode);
                    isSelectingFrom = false;
                    return this;
                } else {
                    fromCode = this->getValidAirport();
                    toAirports.push_back(fromCode);
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 2:
                std::cout << "City Name " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getValidAirportsPerCity();
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getValidAirportsPerCity();
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 3:
                std::cout << "Country Name " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getValidAirportsPerCountry();
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getValidAirportsPerCountry();
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 4:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromCode = this->getValidAirportPerCoordinates();
                    isSelectingFrom = false;
                    return this;
                } else {
                    toCode = this->getValidAirportPerCoordinates();
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 5:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getAirportsRange(25);
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getAirportsRange(25);
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 6:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getAirportsRange(50);
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getAirportsRange(50);
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 7:
                std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
                if (isSelectingFrom) {
                    fromAirports = this->getAirportsRange(100);
                    isSelectingFrom = false;
                    return this;
                } else {
                    toAirports = this->getAirportsRange(100);
                    isSelectingFrom = true;
                    auto* f = new FilterState(fromAirports, toAirports);
                    return f;
                }
            case 0:
                if (!State::stateHistory.empty()) {
                    State *previousState = State::stateHistory.top();
                    State::stateHistory.pop();
                    isSelectingFrom = true;
                    return previousState;
                } else {
                    std::cout << "No previous Menu available" << std::endl;
                    return this;
                }
            case -1:
                exit(0);
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}