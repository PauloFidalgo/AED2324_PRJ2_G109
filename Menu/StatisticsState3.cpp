//
// Created by Wagner Pedrosa on 26/12/2023.
//

#include "StatisticsState3.h"
#include "StatisticsState4.h"
#include "iostream"
#include "sstream"

using namespace std;

State* statisticsState4 = new StatisticsState4();

/*!@brief  função que mostra o terceiro menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar 
 *
 */
void StatisticsState3::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                          Statistics:                                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                1. List airlines per airport                                                          |" << endl;
    cout << "|                2. Airport Info                                                                       |" << endl;
    cout << "|                3. Airline Info                                                                       |" << endl;
    cout << "|                4. No. of destinations available for a given airport (Direct flight)                  |" << endl;
    cout << "|                5. No. of reachable destinations from a given airport in a max number of K stops      |" << endl;
    cout << "|                6. No. of reachable destinations from a given airport                                 |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Main Menu                                                                                    |" << endl;
    cout << "|  exit - Exit                                                                              page - 3   |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 * 
 */
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
        return statisticsState4;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto airport = getValidSingleAirport();
                if(airport) manager.listAirlinesPerAirport(airport);
                return this;
            }
            case 2: {
                auto airport = getValidSingleAirport();
                if (airport) Manager::printAirportInfo(airport);
                return this;
            }
            case 3: {
                auto airline = getValidSingleAirline();
                if (airline) Manager::printAirlineInfo(airline);
                return this;
            }
            case 4:{
                Airport* airport = getValidSingleAirport();
                if (airport) manager.getAirportDestinantionsDistance1(airport);
                return this;
            }

            case 5: {
                Airport *airport = getValidSingleAirport();
                int distance = getValidAirportK();
                if (airport && distance != -1) manager.getAirportDestinantionsUntilDistanceK(airport, distance);
                return this;
            }
            case 6: {
                Airport* airport = getValidSingleAirport();
                if (airport) manager.getAirportDestinantions(airport);
                return this;
            }

            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

