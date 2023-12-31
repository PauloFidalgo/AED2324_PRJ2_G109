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
    cout << "|                                     1. Country Destinations                                          |" << endl;
    cout << "|                                     2. City Destinations until specific Distance                     |" << endl;
    cout << "|                                     3. Countries that can fly to certain city                        |" << endl;
    cout << "|                                     4. Diameter Pairs                                                |" << endl;
    cout << "|                                     5. Top k greatest traffic airline per country (Ascending)        |" << endl;
    cout << "|                                     6. Top k greatest traffic airline per country (Descending)       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                              page - 3   |" << endl;
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
                vector<Airport*> airports = this->getValidAirportsPerCountry();
                if (!airports.empty()) manager.getCountryDestinantions(airports,name);
                return this;
            }
            case 2: {
                vector<Airport*> airports = this->getValidAirportsPerCity();
                int dist = this->getValidCityK();
                if (!airports.empty() && dist != -1) manager.getCityDestinantionsUntilDistanceK(airports,name,dist);
                return this;
            }
            case 3: {
                string city = getValidSingleCity();
                if (!city.empty()) manager.getCountriesCanFlyToCity(city);
                return this;
            }
            case 4:
                manager.diameterPairs();
                return this;
            case 5: {
                int k = getValidAirlineK();
                if (k != -1) manager.getTopKGreatestTrafficAirline(k);
                return this;

            }
            case 6: {
                unordered_set<Airline*> airlines = getValidAirlinePerCountry();
                int distance = getValidAirlineK();
                if (!airlines.empty() && distance != -1) manager.getTopKGreatestTrafficAirlinePerCountry(distance, airlines,false,false);
                return this;
            }

            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}
