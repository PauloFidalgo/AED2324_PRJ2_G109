//
// Created by Wagner Pedrosa on 28/12/2023.
//

#include "StatisticsState6.h"
#include "StatisticsState7.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState6 statisticsState6;


void StatisticsState6::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                           1. Top K Greatest Traffic Airport Per City (Ascending)                     |" << endl;
    cout << "|                           2. Top K Greatest Traffic Airport Per City (Descending)                    |" << endl;
    cout << "|                           3. Top K Greatest Traffic City Per Country (Ascending)                     |" << endl;
    cout << "|                           4. Top K Greatest Traffic City Per Country (Descending)                    |" << endl;
    cout << "|                           5. Top K Countries With More Airlines (Ascending)                          |" << endl;
    cout << "|                           6. Top K Countries With More Airlines (Descending)                         |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 6    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState6::handleInput() {
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
    if(userInputStr == "next"){
        State::statisticsHistory.push(this);
        return &statisticsState7;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto airports = getValidAirportsSingleCity();
                if (airports.empty()) return this;
                auto k = getValidAirportK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficAirportPerCity(k,airports,bar,true);
                return this;
            }
            case 2: {
                auto airports = getValidAirportsSingleCity();
                if (airports.empty()) return this;
                auto k = getValidAirportK();
                if (k == -1) return this;
                auto bar =  bars();
                manager.getTopKGreatestTrafficAirportPerCity(k,airports,bar,false);
                return this;
            }
            case 3: {
                auto cities = getValidCitiesSingleCountry();
                if (cities.empty()) return this;
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCityPerCountry(k,cities,bar,true);
                return this;
            }
            case 4: {
                auto cities = getValidCitiesSingleCountry();
                if (cities.empty()) return this;
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKGreatestTrafficCityPerCountry(k,cities,bar,false);
                return this;
            }
            case 5: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKCountriesWithMoreAirlines(k,bar, true);
            }
            case 6: {
                auto k = getValidCountryK();
                if (k == -1) return this;
                auto bar = bars();
                manager.getTopKCountriesWithMoreAirlines(k,bar, false);
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}