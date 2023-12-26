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
#include "../DataModel/Airline.h"

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
    static void printAirportGreatestTraffic(const vector<Airport *> &airportsByTraffic, const int& nameSize);
    static void printCityGreatestTraffic(const vector<pair<string, int>> &citiesByTraffic, const int& nameSize);
    static void printCountryGreatestTraffic(const vector<pair<string, int>> &countriesByTraffic, const int& nameSize);
    static void printTopKAirportsAirlineTravelsTo(const vector<pair<pair<string,string>,int>> &airports, const int &nameSize);
    static void printTopKAirportsWithMoreAirlines(const vector<pair<int, pair<string,string>>> &airports, const int &nameSize);
    static void printTopKAirlinesThatTravelToAnAirport (const vector<pair<pair<string,string>,int>> &airports, const int &nameSize);
    static void printAirlinesPerAirport (const set<Airline *> &airlines, const int& nameSize);
    static void printListAirportsPerCountry(const vector<Airport *> &airports, const int &nameSize, const string &country);
    static void printSearchAirports(const vector<Airport *> &airports, const int &nameSize, const string &airportName);
    static void printSearchAirlines(const vector<Airline *> &airlines, const int &nameSize, const string &airlineName);
    static void printAirportInfo(Airport *airport);
    static void printAirlineInfo(Airline *airline);
};


#endif //AED2324_PRJ2_G109_VIEWER_H
