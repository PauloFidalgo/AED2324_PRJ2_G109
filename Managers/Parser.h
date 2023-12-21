//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_PARSER_H
#define AED2324_PRJ2_G109_PARSER_H

#include <map>
#include <string>
#include "../DataModel/Airline.h"
#include "../DataStructure/Graph.h"
struct CompareByTraffic {
    bool operator()(Airport *a, Airport *b) const {
        int trafficA = a->getNumFlightsIn() + a->getNumFlightsOut();
        int trafficB = b->getNumFlightsIn() + b->getNumFlightsOut();

        if (trafficA == trafficB) {
            return a->getName() < b->getName();
        }

        return trafficA > trafficB;
    }
};

class Parser {
private:
    std::map<std::string, Airport*> airports;
    std::map<std::string, Airline*> airlines;
    void readFlights(Graph &g);
public:
    Parser();
    ~Parser();
    void readAirlines();
    Graph getGraph();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    std::map<std::string, Airport*> getAirports();
    map<string, Airline*> getAirlines();
    Airline* getAirline(const std::string &airline);
};


#endif //AED2324_PRJ2_G109_PARSER_H
