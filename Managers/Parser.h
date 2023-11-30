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
    std::map<std::string, Airport> airports;
    void readFlights(Graph &g);
public:
    Parser();
    std::map<std::string, Airline> readAirlines();
    Graph getGraph();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
};


#endif //AED2324_PRJ2_G109_PARSER_H
