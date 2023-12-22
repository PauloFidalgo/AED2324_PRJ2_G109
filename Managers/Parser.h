//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_PARSER_H
#define AED2324_PRJ2_G109_PARSER_H

#include <unordered_map>
#include <string>
#include "../DataModel/Airline.h"
#include "../DataStructure/Graph.h"

class Parser {
private:
    std::unordered_map<std::string, Airport*> airports;
    std::unordered_map<std::string, Airline*> airlines;
    void readFlights(Graph &g);
public:
    Parser();
    ~Parser();
    void readAirlines();
    Graph getGraph();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    std::unordered_map<std::string, Airport*> getAirports();
    unordered_map<string, Airline*> getAirlines();
    Airline* getAirline(const std::string &airline);
};


#endif //AED2324_PRJ2_G109_PARSER_H
