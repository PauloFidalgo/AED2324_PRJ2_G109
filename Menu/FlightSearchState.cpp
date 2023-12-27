//
// Created by Paulo Fidalgo on 24/12/2023.
//

#include "FlightSearchState.h"
#include <iostream>
#include <string>
#include "FilterState.h"
#include "CoordinatesFilterState.h"

FilterState filterState;
CoordinatesFilterState coordinatesFilterState;


using namespace std;


FlightSearchState::FlightSearchState(): isSelectingFrom(true){}

void FlightSearchState::displayMenu() {
    const std::string origin = isSelectingFrom ? "From" : "  To";
    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|      "<< origin << "                     Search by:                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - Code                                                         |" << endl;
    cout << "|                                     2 - Airport name                                                 |" << endl;
    cout << "|                                     3 - City                                                         |" << endl;
    cout << "|                                     4 - Country                                                      |" << endl;
    cout << "|                                     5 - Coordinates ( Closest Airport )                              |" << endl;
    cout << "|                                     6 - Coordinates ( 25 Km Range )                                  |" << endl;
    cout << "|                                     7 - Coordinates ( 50 Km Range )                                  |" << endl;
    cout << "|                                     8 - Coordinates ( 100 Km Range )                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State *FlightSearchState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            std::cout << "Code " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromCode = this->getValidAirportCode();
                isSelectingFrom = false;
                return this;
            } else {
                toCode = this->getValidAirportCode();
                isSelectingFrom = true;
                filterState.setFrom(fromCode);
                filterState.setTo(toCode);

                return &filterState;
            }
        case 2:
            std::cout << "Airport Name " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromCode = this->getValidAirportName();
                isSelectingFrom = false;
                return this;
            } else {
                fromCode = this->getValidAirportName();
                isSelectingFrom = true;
                filterState.setFrom(fromCode);
                filterState.setTo(toCode);

                return &filterState;
            }
        case 3:
            std::cout << "City Name " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromAirports = this->getValidAirportsPerCity();
                isSelectingFrom = false;
                return this;
            } else {
                toAirports = this->getValidAirportsPerCity();
                isSelectingFrom = true;
                filterState.setFrom(fromCode);
                filterState.setTo(toCode);

                return &filterState;
            }
        case 4:
            std::cout << "Country Name " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromAirports = this->getValidAirportsPerCountry();
                isSelectingFrom = false;
                return this;
            } else {
                toAirports = this->getValidAirportsPerCountry();
                isSelectingFrom = true;
                filterState.setFrom(fromAirports);
                filterState.setTo(toAirports);

                return &filterState;
            }
        case 5:
            std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromCode = this->getValidAirportPerCoordinates();
                isSelectingFrom = false;
                return this;
            } else {
                toCode = this->getValidAirportPerCoordinates();
                isSelectingFrom = true;
                filterState.setFrom(fromCode);
                filterState.setTo(toCode);

                return &filterState;
            }
        case 6:
            std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromAirports = this->getAirportsRange(25);
                isSelectingFrom = false;
                return this;
            } else {
                toAirports = this->getAirportsRange(25);
                isSelectingFrom = true;
                filterState.setFrom(fromAirports);
                filterState.setTo(toAirports);

                return &filterState;
            }
        case 7:
            std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromAirports = this->getAirportsRange(50);
                isSelectingFrom = false;
                return this;
            } else {
                toAirports = this->getAirportsRange(50);
                isSelectingFrom = true;
                filterState.setFrom(fromAirports);
                filterState.setTo(toAirports);

                return &filterState;
            }
        case 8:
            std::cout << "Coordinates " << (isSelectingFrom ? "From" : "To") << ": ";
            if (isSelectingFrom) {
                fromAirports = this->getAirportsRange(100);
                isSelectingFrom = false;
                return this;
            } else {
                toAirports = this->getAirportsRange(100);
                isSelectingFrom = true;
                filterState.setFrom(fromAirports);
                filterState.setTo(toAirports);

                return &filterState;
            }
        case 0:
            if(!State::stateHistory.empty()){
                State* previousState = State::stateHistory.top();
                State::stateHistory.pop();
                isSelectingFrom = true;
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