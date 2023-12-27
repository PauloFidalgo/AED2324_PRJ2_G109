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
    vector<Airport*> por = {m.getAiportsPerCity("Johannesburg")};
    vector<Airport*> nul = {};
    vector<Airport*> nul2 = {m.getAirportPerCode("GRU"), m.getAirportPerCode("FRA"), m.getAirportPerCode("MUC")};
    unordered_set<Airline*> nul24 = {};

    auto mo = m.manageFlightSearchFromMenu(porks, pork, nul, por, nul2, nul24);

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
