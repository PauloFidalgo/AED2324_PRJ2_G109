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
    cout << "|                                   1. Country Destinations Until Distance K                           |" << endl;
    cout << "|                                   2. Top K Greatest Traffic City (Ascending)                         |" << endl;
    cout << "|                                   3. Top K Greatest Traffic City (Descending)                        |" << endl;
    cout << "|                                   4. Airlines Per Airport                                            |" << endl;
    cout << "|                                   5. Top K Greatest Traffic Country(Ascending)                       |" << endl;
    cout << "|                                   6. Top K Greatest Traffic Country(Descending)                      |" << endl;
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
                auto country = getValidSingleCountry();
                auto dist = this->getValidCountryK();
                if(!airport.empty() && dist != -1 && !country.empty())  manager.getCountryDestinantionsUntilDistanceK(airport,country,dist);
                return this;
            }
            case 2: {
                auto k = getValidCityK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars = barsState.shouldUseGraphicBar();
                if(k != -1) manager.getTopKGreatestTrafficCity(k,bars,true);
                return this;

            }
            case 3: {
                auto k = getValidCityK();
                auto bar = bars();
                if(k != -1) manager.getTopKGreatestTrafficCity(k,bar,false);
                return this;
            }
            case 4: {
                auto airport = getValidSingleAirport();
                if(airport) manager.listAirlinesPerAirport(airport);
                return this;
            }
            case 5: {
                auto k = getValidCountryK();
                auto bar = bars();
                if( k != -1) manager.getTopKGreatestTrafficCountry(k,bar,true);
                return this;
            }
            case 6: {
                auto k = getValidCountryK();
                auto bar = bars();
                if ( k!= -1) manager.getTopKGreatestTrafficCountry(k,bar,false);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}