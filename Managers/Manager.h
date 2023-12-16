//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_MANAGER_H
#define AED2324_PRJ2_G109_MANAGER_H


#include "Parser.h"
#include "../DataStructure/Graph.h"
#include <map>
#include <string>
#include "../DataModel/Airline.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Manager {
private:
    Parser parser;
    std::map<std::string, Airline*> airlines;
    std::map<std::string, Airport*> airports;
    Graph connections;

public:
    Manager();
    std::map<std::string, Airline*> getAirlines();
    std::map<std::string, Airport*> getAirports();
    void dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights);
    bool hasPath(Vertex *v, Vertex *t, vector<Airport> &flights);
    vector<Airport> pathExists(Airport *d, Airport *t);
    vector<Airport> getPath(Airport *source, Airport *destination);
    vector<Vertex*> airportsAtDistanceK(Vertex *source, int k);
    vector<Airport> articulationPoints();
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);
    vector<Airport> hasFlightAirline(Airport *source, Airport *target, vector<Airline> &setOfAirlines);
};


#endif //AED2324_PRJ2_G109_MANAGER_H
