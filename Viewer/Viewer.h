//
// Created by nelson on 25-12-2023.
//

#ifndef AED2324_PRJ2_G109_VIEWER_H
#define AED2324_PRJ2_G109_VIEWER_H

#include <string>

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "../DataModel/Airport.h"

using namespace std;

class Viewer {
public:
    static void printNumAirportsNumFlights(const int& numAirports, const int& numFlights);
    static void printNumFlightsOutAndAirlines(const string& name, const string& code, const int& numFlights, const int& numAirlines);
    static void printNumFlightsPerCity(const string& city, const int& numFlights);
    static void printNumFlightsPerAirline(const string& code, const string& name, const int& numFlights);
    static void printCountriesAirportCanFlyTo(const string &code, const string &name, const int &numCountries);
    static void printCountriesCityCanFlyTo(const string& city, const int &numCountries);
    static void printAirportDestinationsDistance1(const string &code, const string &name, const int &numAirports, const int &numCities, const int &numCountries);
    static void printCityDestinationsDistance1(const string &city, const int &numAirports, const int &numCities, const int &numCountries);
    static void printCountryDestinationsDistance1(const string &city, const int &numAirports, const int &numCities, const int &numCountries);
    static void printAirportDestinations(const string &code, const string &name, const int &numAirports, const int &numCities, const int &numCountries);
    static void printCityDestinations(const string& city, const int &numAirports, const int &numCities, const int &numCountries);
    static void printCountryDestinations(const string &country, const int &numAirports, const int &numCities, const int &numCountries);
    static void printDiameterPairs(const vector<pair<Airport, Airport>>& result, const int &maxDiameter);
    static void printAirportGreatestTraffic(vector<Airport *> airportsByTraffic, const int& nameSize);
    static void printCityGreatestTraffic(vector<pair<string, int>> citiesByTraffic, const int& nameSize);
    static void printCountryGreatestTraffic(vector<pair<string, int>> countriesByTraffic, const int& nameSize);
};


#endif //AED2324_PRJ2_G109_VIEWER_H
