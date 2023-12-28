//
// Created by Wagner Pedrosa on 28/12/2023.
//

#include "StatisticsState5.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState5 statisticsState5;


void StatisticsState5::displayMenu() {

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
    cout << "|                                     6. Airports per Country                                          |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                                          |" << endl;
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
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto airport = getValidAirports();
                auto city = getValidCity();
                auto dist = this->getValidCityK();
                manager.getCityDestinantionsUntilDistanceK(airport,city,dist);
                return this;
            }
            case 2: {
                auto airport = getValidAirports();
                auto country = getValidCountry();
                auto dist = this->getValidCountryK();
                manager.getCountryDestinantionsUntilDistanceK(airport,country,dist);
                return this;
            }
            case 3: {
                auto k = getValidCityK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKGreatestTrafficCity(k,bars,true);

            }
            case 4: {
                auto k = getValidCityK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                cout << bars << endl;
                manager.getTopKGreatestTrafficCity(k,bars,false);
                return this;
            }
            case 5: {
                auto k = getValidCountryK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKGreatestTrafficCountry(k,bars,true);
            }
            case 6: {
                auto k = getValidCountryK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKGreatestTrafficCountry(k,bars,false);
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}