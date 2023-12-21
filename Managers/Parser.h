//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_PARSER_H
#define AED2324_PRJ2_G109_PARSER_H

#include <map>
#include <string>
#include "../DataModel/Airline.h"
#include "../DataStructure/Graph.h"

class Parser {
private:
    std::map<std::string, Airport*> airports;
    std::map<std::string, Airport*> airportsByName;
    std::map<std::string, Airline*> airlines;
    std::map<std::string, Airline*> airlinesByName;
    void readFlights(Graph &g);
public:
    Parser();
    ~Parser();
    void readAirlines();
    Graph getGraph();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    std::map<std::string, Airport*> getAirports();
    std::map<std::string, Airport*> getAirportsByName();
    map<string, Airline*> getAirlines();
    Airline* getAirline(const std::string &airline);
    std::map<std::string, Airline*> getAirlinesByName();
};


#endif //AED2324_PRJ2_G109_PARSER_H
