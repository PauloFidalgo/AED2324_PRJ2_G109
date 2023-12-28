#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;

    vector<string> porst = {"London"};

    //auto res = m.scheduleTripMinConnectionCities(m.getAirportPerCode("OPO"), m.getAirportPerCode("LIS"), porst);

    vector<Airport*> porks = {m.getAirportPerCode("OPO")};
    vector<Airport*> pork = {m.getAirportPerCode("LIS")};
    vector<Airport*> por = {m.getAiportsPerCity("Madrid")};
    vector<Airport*> por2 = {m.getAiportsPerCity("Brussels")};
    vector<Airport*> por3 = {m.getAirportsPerCountry("Germany")};
    map<int, vector<Airport*>> re;
    re.insert({1, por});
    re.insert({2, por2});
    re.insert({3, por3});
    vector<Airport*> nul = {};
    vector<Airport*> nul2 = {m.getAirportPerCode("GRU"), m.getAirportPerCode("FRA"), m.getAirportPerCode("MUC")};
    unordered_set<Airline*> nul24 = {};

    auto mo = m.manageFlightSearchFromMenu(porks, pork, nul, re, nul2, nul24, nul24);

    /*
    for (auto &v : res) {
        cout << "Path : ";
        for (auto p: v) {
            cout << p->getCode() << " ";
        }
        cout << endl;
    }*/

    cout << "___________________________________" << endl;

    for (auto &v : mo) {
        cout << "Path : ";
        for (auto p: v) {
            cout << p->getCode() << " ";
        }
        cout << endl;
    }

    return 0;
}
