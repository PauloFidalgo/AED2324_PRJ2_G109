#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;
    m.getNumAirportsAndFlights();
    m.getNumFlightsAndAirlines("HGU");
    m.getNumFlightsPerCity("Mount Hagen");
    m.getNumFlightsPerAirline("TAP");
    m.getCountriesCanFlyToAirport("JFK");
    m.getCountriesCanFlyToCity("New York");
    m.getDestinantions("AAQ");
    m.getDestinantionsUntilDistanceK("JFK", 3);
    m.diameterPairs();
    /*
    auto res = m.scc();
    for (auto elem : res) {
        for (auto ze : elem) {
            cout << ze.getCode() << ' ';
        }
        cout << endl;
    }
    cout << "-------------------------------------" << endl;
    auto pila = m.articulationPoints();
    for (auto elem : pila) {
        cout << elem.getCode() << endl;
    }*/
    return 0;
}
