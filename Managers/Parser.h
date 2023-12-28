//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_PARSER_H
#define AED2324_PRJ2_G109_PARSER_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include "../DataModel/Airline.h"
#include "../DataStructure/Graph.h"

class Parser {
private:
    unordered_map<string, Airport*> airports;
    unordered_map<string, Airline*> airlines;
    unordered_map<string, vector<Airport*>> cityAirports;
    unordered_map<string, unordered_set<string>> countryCities;
    unordered_map<std::string, Airport*> airportsByName;
    unordered_map<std::string, Airline*> airlinesByName;
    unordered_map<std::string, unordered_set<Airline*>> airlinesCountry;
    void readFlights(Graph &g);
public:
    //~Parser();
    void readAirlines();
    Graph getGraph();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    unordered_map<string, Airport*> getAirports();
    unordered_map<string, Airline*> getAirlines();
    unordered_map<string, vector<Airport*>> getCityAirports();
    unordered_map<string, unordered_set<string>> getCountryCities();
    Airline* getAirline(const string &airline);
    std::unordered_map<std::string, Airport*> getAirportsByName();
    std::unordered_map<std::string, unordered_set<Airline*>> getAirlinesCountry();
    std::unordered_map<std::string, Airline*> getAirlinesByName();
};


#endif //AED2324_PRJ2_G109_PARSER_H
