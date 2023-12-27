//
// Created by Wagner Pedrosa on 26/12/2023.
//
#include "StatisticsState1.h"
#include "StatisticsState4.h"
#include "StatisticsState3.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState4 statisticsState4;


void StatisticsState4::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                                           |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Top K Greatest Traffic Airport                                |" << endl;
    cout << "|                                     2. Top K Greatest Traffic Airport Per Country                    |" << endl;
    cout << "|                                     3. Top K Lowest Traffic Airport Per Country                      |" << endl;
    cout << "|                                     4. Airport Info                                                  |" << endl;
    cout << "|                                     5. Airline Info                                                  |" << endl;
    cout << "|                                     6. Out flights                                                   |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                                          |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

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
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto dist = this->getValidAirportK();
                manager.getTopKGreatestTrafficAirport(dist);
                return this;
            }
            case 2: {
                // verificar se ele vai ao barstate e dps volta para aqui
                // GREATEST
                string country = getValidCountry();
                vector<Airport *> airports = manager.getAirportsPerCountry(country);
                int dist = getValidAirportK();
                statisticsHistory.push(this);

                State *nextState = barsState.handleInput();

                if (nextState == this) {
                    if (barsState.shouldUseGraphicBar()) {
                        manager.getTopKGreatestTrafficAirportPerCountry(dist, airports, true, true);
                    } else {
                        manager.getTopKGreatestTrafficAirportPerCountry(dist, airports, false, true);
                    }
                    return this;
                } else {
                    return nextState;
                }
            }
            case 3: {
                //LOWEST
                string country = getValidCountry();
                vector<Airport *> airports = manager.getAirportsPerCountry(country);
                int dist = getValidAirportK();

                manager.getTopKGreatestTrafficAirportPerCountry(dist, airports, false, false);
                return this;
            }
            case 4: {
                string country = getValidCountry();
                Airport* airport = manager.getAirportPerName(country);
                Manager::printAirportInfo(airport);
                return this;
            }
            case 5: {
                string name = getValidCountry();
                Airline *airline = manager.getAirlinePerName(name);
                Manager::printAirlineInfo(airline);
                return this;
            }
            case 6: {
                string country = getValidCountry();
                auto airports = manager.getAirportsPerCountry(country);
                manager.listAiportsPerCountry(airports, country);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}