//
// Created by Wagner Pedrosa on 28/12/2023.
//

#include "StatisticsState5.h"
#include "StatisticsState6.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState5 statisticsState5;


void StatisticsState5::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                     1. Top K Greatest Traffic Airport                                |" << endl;
    cout << "|                                     2. Top K Greatest Traffic Airport Per Country                    |" << endl;
    cout << "|                                     3. Top K Lowest Traffic Airport Per Country                      |" << endl;
    cout << "|                                     4. Airport Info                                                  |" << endl;
    cout << "|                                     5. Airline Info                                                  |" << endl;
    cout << "|                                     6. Airports per Country                                          |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 5    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState5::handleInput() {
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
        return &statisticsState6;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto airport = getValidAirports();
                auto city = getValidSingleCity();
                auto dist = this->getValidCityK();
                if(!airport.empty() && dist != -1 && !city.empty()) manager.getCityDestinantionsUntilDistanceK(airport,city,dist);
                return this;
            }
            case 2: {
                auto airport = getValidAirports();
                auto country = getValidSingleCountry();
                auto dist = this->getValidCountryK();
                if(!airport.empty() && dist != -1 && !country.empty())  manager.getCountryDestinantionsUntilDistanceK(airport,country,dist);
                return this;
            }
            case 3: {
                auto k = getValidCityK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars = barsState.shouldUseGraphicBar();
                if(bars && k != -1) manager.getTopKGreatestTrafficCity(k,bars,true);
                return this;
            }
            case 4: {
                auto k = getValidCityK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                if(bars && k != -1) manager.getTopKGreatestTrafficCity(k,bars,false);
                return this;
            }
            case 5: {
                auto k = getValidCountryK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars = barsState.shouldUseGraphicBar();
                if(bars && k != -1) manager.getTopKGreatestTrafficCountry(k,bars,true);
                return this;
            }
            case 6: {
                auto k = getValidCountryK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars = barsState.shouldUseGraphicBar();
                if(bars && k != -1) manager.getTopKGreatestTrafficCountry(k,bars,false);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}