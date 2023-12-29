//
// Created by Wagner Pedrosa on 29/12/2023.
//

#include "StatisticsState7.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
StatisticsState7 statisticsState7;


void StatisticsState7::displayMenu() {

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
    cout << "| exit - Exit                                                                              page - 7    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

State* StatisticsState7::handleInput() {
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
                auto airline = getValidSingleAirline();
                auto k = getValidAirportK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirportsAirlineTravelsTo(k,airline,bars,true);
                return this;
            }
            case 2: {
                auto airline = getValidSingleAirline();
                auto k = getValidAirportK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirportsAirlineTravelsTo(k,airline,bars, false);
                return this;
            }
            case 3: {
                auto k = getValidAirportK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirportsWithMoreAirlines(k,bars,true);
                return this;
            }
            case 4: {
                auto k = getValidAirportK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirportsWithMoreAirlines(k,bars,false);
                return this;
            }
            case 5: {
                auto airport = getValidSingleAirport();
                auto k = getValidAirportK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirlinesThatFlyMoreToAnAirport(k,airport,bars, true);
            }
            case 6: {
                auto airport = getValidSingleAirport();
                auto k = getValidAirportK();
                barsState.displayMenu();
                barsState.handleInput();
                auto bars =barsState.shouldUseGraphicBar();
                manager.getTopKAirlinesThatFlyMoreToAnAirport(k,airport,bars, false);
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}