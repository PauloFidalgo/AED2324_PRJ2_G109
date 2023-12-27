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
            case 1: {
                string country = getValidCountry();
                vector<Airport*> airports = this->getValidAirportsPerCountry();
                manager.getCountryDestinantions(airports,country);
                return this;
            }
            case 2: {
                string city = getValidCity();
                vector<Airport*> airports = this->getValidAirportsPerCity();
                int dist = this->getValidCityK();
                manager.getCityDestinantionsUntilDistanceK(airports,city,dist);
                return this;
            }
            case 3: {
                string city = getValidCity();
                manager.getCountriesCanFlyToCity(city);
                return this;
            }
            case 4:
                manager.diameterPairs();
                return this;
            case 5: {
                int k = getValidAirlineK();
                manager.getTopKGreatestTrafficAirline(k);
                return this;

            }
            /*
            case 6: {
                vector<Airline*> airlines = manager.getAirlinesPerCountry();
                int distance = getValidAirlineK();
                manager.getTopKGreatestTrafficAirlinePerCountry(distance, airlines,false,false);
                return this;
            }
             */
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}
