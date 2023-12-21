#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;
    //m.getNumAirportsAndFlights();
    //m.getNumFlightsAndAirlines("HGU");
    //m.getNumFlightsPerCity("Mount Hagen");
    //m.getNumFlightsPerAirline("TAP");
    //m.getCountriesCanFlyToAirport("JFK");
    //m.getCountriesCanFlyToCity("New York");
    //m.getDestinantions("AAQ");
    //m.getDestinantionsUntilDistanceK("JFK", 3);
    m.diameterPairs();
    //m.getTopKGreatestTrafficAirport(1);
    //m.getTopKGreatestTrafficAirportPerCountry(3,"Portugal");
    //m.getTopKGreatestTrafficAirline(3);
    //m.getTopKGreatestTrafficAirlinePerCountry(3,"Portugal");
    return 0;
}
