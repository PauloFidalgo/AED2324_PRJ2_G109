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
    return 0;
}
