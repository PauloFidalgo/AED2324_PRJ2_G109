//
// Created by Wagner Pedrosa on 28/12/2023.
//

#include "StatisticsState6.h"
#include "StatisticsState7.h"
#include "BarsState.h"
#include "iostream"
#include "sstream"

using namespace std;
State* statisticsState7 = new StatisticsState7();

/*!@brief  função que mostra o sexto menu das estatisticas, onde deixa o utilizador escolher que estatistica quer visualizar
 *
 */
void StatisticsState6::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|   previous - previous page                                                   next - next page        |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                             Statistics:                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                    1. Top-k airports a given airline travels more to                                 |" << endl;
    cout << "|                    2. Top-k airports a given airline travels less to                                 |" << endl;
    cout << "|                    3. Top-k airports with more airlines                                              |" << endl;
    cout << "|                    4. Top-k airports with less airlines                                              |" << endl;
    cout << "|                    5. Top-k airlines with the greatest air traffic capacity                          |" << endl;
    cout << "|                    6. Top-k airlines with the least air traffic capacity                             |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "| back - Main Menu                                                                                     |" << endl;
    cout << "| exit - Exit                                                                              page - 6    |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que permite ao utilizador navegar entre os varios menus das estatísticas ou consultar alguma estatística.
 *
 */
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
        return statisticsState7;
    }
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                auto airline = getValidSingleAirline();
                auto k = getValidAirportK();
                auto bar = bars();
                if (airline && k != -1 )manager.getTopKAirportsAirlineTravelsTo(k,airline,bar, false);
                return this;
            }
            case 2: {
                auto airline = getValidSingleAirline();
                auto k = getValidAirportK();
                auto bar = bars();
                if (airline && k != -1 )manager.getTopKAirportsAirlineTravelsTo(k,airline,bar, true);
                return this;
            }
            case 3: {
                auto k = getValidAirportK();
                auto bar = bars();
                if( k != -1) manager.getTopKAirportsWithMoreAirlines(k,bar,false);
                return this;
            }
            case 4: {
                auto k = getValidAirportK();
                auto bar = bars();
                if( k != -1) manager.getTopKAirportsWithMoreAirlines(k,bar,true);
                return this;
            }
            case 5: {
                int k = getValidAirlineK();
                auto bar = bars();
                if (k != -1) manager.getTopKGreatestTrafficAirline(k,bar,false);
                return this;
            }
            case 6: {
                int k = getValidAirlineK();
                auto bar = bars();
                if (k != -1) manager.getTopKGreatestTrafficAirline(k,bar,true);
                return this;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}