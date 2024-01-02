//
// Created by nelson on 25-12-2023.
//

#ifndef AED2324_PRJ2_G109_VIEWER_H
#define AED2324_PRJ2_G109_VIEWER_H

#include <string>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <set>
#include "../DataModel/Airport.h"
#include "../DataModel/Airline.h"

using namespace std;

class Viewer {
public:
    static void printNumAirportsNumFlights(const int& numAirports, const int& numFlights);
    static void printNumFlightsOutAndAirlines(const string& code, const string& name, const int& numFlights, const int& numAirlines);
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
    static void printDiameterPairs(const vector<pair<Airport *, Airport *>>& result, const int &maxDiameter);
    static void printArticulationPoints(vector<Airport *> airports, const int &nameSize);

    static void printAirportGreatestTraffic(const vector<Airport *> &airportsByTraffic, const int& nameSize);
    static void printAirlineGreatestTraffic(const vector<Airline *> &airlinesByTraffic, const int& nameSize);
    static void printAirlinesPerAirport (const set<Airline *> &airlines, const int& nameSize);
    static void printListAirportsPerCountryCity(const vector<Airport *> &airports, const int &nameSize, const string &countryCity);
    static void printListAirlinesPerCountry(const unordered_set<Airline *> &airlines, const int &nameSize, const string &country);
    static void printSearchAirports(const vector<Airport *> &airports, const int &nameSize, const string &airportName);
    static void printSearchAirlines(const vector<Airline *> &airlines, const int &nameSize, const string &airlineName);
    static void printAirportInfo(Airport *airport);
    static void printAirlineInfo(Airline *airline);

    static void printAirportGreatestTrafficBars(const vector<Airport *> &airportsByTraffic, const bool &asc);
    static void printAirlineGreatestTrafficBars(const vector<Airline *> &airlinesByTraffic, const bool &asc);
    static void printCityOrCountryGreatestTrafficBars(const vector<pair<string, int>> &traffic, const int &nameSize, const bool &asc);

    static void printTopKVector(const vector<pair<Airport *, int>> &airports,const string &label1, const string &label2, const int &nameSize);
    static void printTopKVector(const vector<pair<Airline *, int>> &airlines,const string &label1, const string &label2, const int &nameSize);
    static void printTopKVectorBars(const vector<pair<Airport *, int>> &airports, const bool &asc);
    static void printTopKVectorBars(const vector<pair<Airline *, int>> &airlines, const bool &asc);
    static void printTopKVectorRatio(const vector<pair<Airline *, double>> &airlines, const int &nameSize);
    static void printTopKVectorBarsRatio(const vector<pair<Airline *, double>> &airlines, const bool &asc);


    static void printCountryCityStats(const vector<pair<string, int>> &countriesCities, const string &label1, const string &label2, const int &nameSize);
    static void printScc(const vector<vector<Airport *>> &airports);
    static void printFlightOptions(const vector<vector<Airport *>> &airports);

};


#endif //AED2324_PRJ2_G109_VIEWER_H
