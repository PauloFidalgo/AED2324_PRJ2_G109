//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include <algorithm>
#include "FilterState.h"
#include "iostream"
#include "FlightSearchState.h"
#include "MainMenuState.h"

using namespace std;
State *homeMenu = new MainMenuState();

/*!@brief Construtor da classe FilterState que atribui as variáveis" fromAirports" e "toAirports" o respetivo valor.
 * @param from aeroporto de partida
 * @param to aeroporto de chegada
 */
FilterState::FilterState(vector<Airport*> &from, vector<Airport*> &to) {
    fromAirports = from;
    toAirports = to;
}

/*! @brief função que mostra o menu com as possibilidades de filtros que o utilizador tem, na sua pesquisa.
 */
void FilterState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|        Filters:                                        Search:                                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|        1 - Exclude 1 or more Airlines                  11 - Minimize Number of Distinct Airlines     |" << endl;
    cout << "|        2 - Include 1 or more Airlines                  12 - Distance Travelled                       |" << endl;
    cout << "|        3 - Exclude Airlines from 1 or more Countries   13 - Minimize Stops                           |" << endl;
    cout << "|        4 - Include Airlines from 1 or more Countries                                                 |" << endl;
    cout << "|        5 - Exclude 1 or more Airports                                                                |" << endl;
    cout << "|        6 - Include 1 or more Airports                                                                |" << endl;
    cout << "|        7 - Exclude 1 or more Cities                                                                  |" << endl;
    cout << "|        8 - Include 1 or more Cities                                                                  |" << endl;
    cout << "|        9 - Exclude 1 or more Countries                                                               |" << endl;
    cout << "|        10 - Include 1 or more Countries                                                              |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  back - Go back                                                                                      |" << endl;
    cout << "|  exit - Exit                                                                                         |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;
}

/*!@brief  função que, consoante a escolha do utilizador, adiciona alguns filtros e realiza uma pesquisa tendo em conta os filtros escolhidos.
 * @return Ponteiro para o próximo estado do programa, com base na escolha do utilizador.
 */

State* FilterState::handleInput() {
    cout << "Enter your choice: ";
    getline(cin, userInputStr);

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
    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;

        switch (userInput) {
            case 1:
                excludedAirlines.clear();
                this->excludeAirlines();
                return this;
            case 2:
                includedAirlines.clear();
                this->includeAirlines();
                return this;
            case 3:
                excludedAirlines.clear();
                this->excludeAirlinesPerCountry();
                return this;
            case 4:
                includedAirlines.clear();
                this->includeAirlinesPerCountry();
                return this;
            case 5:
                excludedAirports.clear();
                this->excludeAirports();
                return this;
            case 6:
                includedAirports.clear();
                this->includeAirports();
                return this;
            case 7:
                excludedAirports.clear();
                this->excludeCities();
                return this;
            case 8:
                cityCountry.clear();
                this->includeCities();
                return this;
            case 9:
                excludedAirports.clear();
                this->excludeCountries();
                return this;
            case 10:
                cityCountry.clear();
                this->includeCountries();
                return this;
            case 11:
                manager.manageFlightSearchFromMenuMinAirlines(fromAirports, toAirports, includedAirports, cityCountry,
                                                              excludedAirports, excludedAirlines, includedAirlines);
                while (!stateHistory.empty()) stateHistory.pop();
                return homeMenu;
            case 12:
                manager.manageFlightSearchFromMenuMinDistance(fromAirports, toAirports, includedAirports, cityCountry,
                                                              excludedAirports, excludedAirlines, includedAirlines);
                while (!stateHistory.empty()) stateHistory.pop();
                return homeMenu;
            case 13:
                manager.manageFlightSearchFromMenu(fromAirports, toAirports, includedAirports, cityCountry,
                                                   excludedAirports, excludedAirlines, includedAirlines);
                while (!stateHistory.empty()) stateHistory.pop();
                return homeMenu;
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return this;
        }
    }
}

/*!@brief  função que exclui companhias aéreas
 */
void FilterState::excludeAirlines() {
    auto aux = this->getValidAirlines();
    if ( excludedAirlines.empty() && !aux.empty()){
        excludedAirlines = aux;
    } else if (!aux.empty()) {
        excludedAirlines.insert(aux.begin(),aux.end());
    }
    verifyExcludedAirlines();
}

/*!@brief  função que exclui companhias aéreas por país
 */
void FilterState::excludeAirlinesPerCountry() {
    auto aux = this->getValidAirlinePerCountry();
    if ( excludedAirlines.empty() && !aux.empty()){
        excludedAirlines = aux;
    } else if (!aux.empty()) {
        for (auto &i : aux) {
            excludedAirlines.insert(i);
        }
    }
    verifyExcludedAirlines();
}

/*!@brief  função que inclui companhias aéreas por país
 */
void FilterState::includeAirlinesPerCountry() {
    auto aux = this->getValidAirlinePerCountry();
    if ( includedAirlines.empty() && !aux.empty()){
        includedAirlines = aux;
    } else if (!aux.empty()) {
        for (auto &i : aux) {
            includedAirlines.insert(i);
        }
    }
    verifyIncludedAirlines();
}

/*!@brief  função que inclui companhias aéreas
 */
void FilterState::includeAirlines() {
    auto aux = this->getValidAirlines();
    if ( includedAirlines.empty() && !aux.empty()){
        includedAirlines = aux;
    } else if (!aux.empty()) {
        for (auto &i : aux) {
            includedAirlines.insert(i);
        }
    }
    verifyIncludedAirlines();
}

/*!@brief  função que exclui aeroportos
 */
void FilterState::excludeAirports() {
    auto aux = this->getValidAirports();
    if ( excludedAirports.empty() && !aux.empty()){
        excludedAirports = aux;
    } else if (!aux.empty()) {
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
    verifyExcludeAirports();
}

/*!@brief  função que inclui aeroportos
 */
void FilterState::includeAirports() {
    auto aux = this->getValidAirports();
    if (includedAirports.empty() && !aux.empty()) {
        includedAirports = aux;
    }
    else if (!aux.empty()) {
        includedAirports.insert(includedAirports.end(), aux.begin(), aux.end());
    }
    verifyIncludedAirports();
}

/*!@brief  função que inclui países
 */
void FilterState::includeCountries() {
    auto aux = this->getValidAirportsPerCountries();
    if ( cityCountry.empty() && !aux.empty()){
        cityCountry = aux;
    } else if (!aux.empty()) {
        int size = cityCountry.size();
        for(auto& x : aux){
            cityCountry.insert({size + x.first,x.second});
        }
    }
    verifyVisitCountryCity();
}

/*!@brief  função que exclui países
 */
void FilterState::excludeCountries() {
    auto aux = this->getValidAirportsPerCountry();
    if ( excludedAirports.empty() && !aux.empty()){
        excludedAirports = aux;
    } else if (!aux.empty()) {
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
    verifyExcludeAirports();
}

/*!@brief  função que inclui cidades
 */
void FilterState::includeCities() {
    auto aux = this->getValidAirportsPerCities();
    if ( cityCountry.empty() && !aux.empty()){
        cityCountry = aux;
    } else if (!aux.empty()) {
        int size = cityCountry.size();
        for(auto& x : aux){
            cityCountry.insert({size + x.first,x.second});
        }
    }
    verifyVisitCountryCity();
}

/*!@brief  função que exclui cidades
 */
void FilterState::excludeCities() {
    auto aux = this->getValidAirportsPerCity();
    if ( excludedAirports.empty() && !aux.empty()){
        excludedAirports = aux;
    } else if (!aux.empty()) {
        excludedAirports.insert(excludedAirports.end(),aux.begin(),aux.end());
    }
    verifyExcludeAirports();
}

/*!@brief  função que verifica se existe algum aeroporto excluído que está no vetor de aeroportos incluídos.
 */
void FilterState::verifyExcludeAirports() {
    vector<Airport*> res;

    for (auto &it : excludedAirports) {
        bool found = false;
        for (auto &i : includedAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }
    vector<Airport*> aux;
    for (auto &it : res) {
        bool found = false;
        for (auto &i : fromAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) aux.push_back(it);
    }

    res.clear();
    for (auto &it : aux) {
        bool found = false;
        for (auto &i : toAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }

    excludedAirports = res;
}

/*!@brief  função que verifica se existe algum aeroporto incluído que está no vetor de aeroportos excluídos
 */
void FilterState::verifyIncludedAirports() {
    vector<Airport*> res;

    for (auto &it : includedAirports) {
        bool found = false;
        for (auto &i : excludedAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }
    vector<Airport*> aux;
    for (auto &it : res) {
        bool found = false;
        for (auto &i : fromAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) aux.push_back(it);
    }

    res.clear();
    for (auto &it : aux) {
        bool found = false;
        for (auto &i : toAirports) {
            if (i->getCode() == it->getCode()) found = true;
        }
        if (!found) res.push_back(it);
    }

    includedAirports = res;
}

/*!@brief  função que verifica se existe alguma companhia aérea no vetor de incluídas que está no vetor de companhias aéreas excluídas
 */
void FilterState::verifyIncludedAirlines() {
    unordered_set<Airline*> res;

    for (auto it : includedAirlines) {
        auto p = excludedAirlines.find(it);

        if (p == excludedAirlines.end()) {
            res.insert(it);
        }
    }
    includedAirlines = res;
}

/*!@brief  função que verifica se existe alguma companhia aérea no vetor de excluídas que está no vetor de companhias aéreas incluídas
 */
void FilterState::verifyExcludedAirlines() {
    unordered_set<Airline*> res;

    for (auto it : excludedAirlines) {
        auto p = includedAirlines.find(it);

        if (p == includedAirlines.end()) {
            res.insert(it);
        }
    }
    excludedAirlines = res;
}

/*! @brief função que determina se um aeroporto deve ser removido, consoante a sua presença nos vetores de aeroportos. Para além disso caso após remoção se a entrada ficar vazia então tambem é removida
 */
void FilterState::verifyVisitCountryCity() {
    for (auto it = cityCountry.begin(); it != cityCountry.end(); ) {
        auto &airportVector = it->second;

        airportVector.erase(
                std::remove_if(
                        airportVector.begin(),
                        airportVector.end(),
                        [this](auto airport) {
                            return isAirportToBeRemoved(airport);
                        }
                ),
                airportVector.end()
        );

        if (airportVector.empty()) {
            it = cityCountry.erase(it);
        } else {
            ++it;
        }
    }
}

/*! @brief função que verfica se um dado aeroporto está presente em algum dos vetores
 * @param airport
 * @return true se o aeroporto estiver presente em algum vetor de toAirports, fromAirports, excludedAirports, includedAirports.
 * @return false se o aeroporto não estiver presente em nunhum desses vetores e por isso não é para remover
 */
bool FilterState::isAirportToBeRemoved(Airport* airport) const {

    return std::find(toAirports.begin(), toAirports.end(), airport) != toAirports.end() ||
           std::find(fromAirports.begin(), fromAirports.end(), airport) != fromAirports.end() ||
           std::find(excludedAirports.begin(), excludedAirports.end(), airport) != excludedAirports.end() ||
           std::find(includedAirports.begin(), includedAirports.end(), airport) != includedAirports.end();
}


