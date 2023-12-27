//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "FilterState.h"
#include "iostream"
#include "FlightSearchState.h"

using namespace std;

void FilterState::setFrom( Airport* fromAirport) {
    this->fromAirport = fromAirport;
}

void FilterState::setTo( Airport* toAirport) {
    this->toAirport = toAirport;
}
void FilterState::setFrom( vector<Airport*> fromAirports) {
    this->fromAirports = fromAirports;
}

void FilterState::setTo( vector<Airport*> toAirports) {
    this->toAirports = toAirports;
}


void FilterState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                           Filters :                                                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1 - exclude 1 or more airlines                                   |" << endl;
    cout << "|                                     2 - include 1 or more airlines                                   |" << endl;
    cout << "|                                     3 - Avoid passing through 1 or more country's                    |" << endl;
    cout << "|                                     4 - Pass trough 1 or more country's                              |" << endl;
    cout << "|                                     5 - Minimize the number of distinct airlines                     |" << endl;
    cout << "|                                     6 - Distance Travelled                                           |" << endl;
    cout << "|                                     7 - Done                                                         |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  0 - Go back                                                                                         |" << endl;
    cout << "| -1 - Exit                                                                                            |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

State* FilterState::handleInput() {
    int userInput;
    std::cout << "Enter your choice: ";
    std::cin >> userInput;

    switch (userInput) {
        case 1:
            this->excludeAirlines();
            break;
        case 2:
            this->includeAirlines();
            break;
        case 3:
            std::cout << "Country" << std::endl;
            break;
        case 4:
            std::cout << "Coordinates" << std::endl;
            break;
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
    return nullptr;
}



void FilterState::excludeAirlines() {
    std::vector<Airline*> excludedAirlines;

    while (true) {
        Airline* airline = getValidAirline();

        if (!airline) {
            break;
        }

        excludedAirlines.push_back(airline);
    }
}


void FilterState::includeAirlines() {
    std::vector<Airline*> includedAirlines;

    while (true) {
        Airline* airline = getValidAirline();

        if (airline == nullptr) {
            break;
        }

        includedAirlines.push_back(airline);
    }
}