//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_MANAGER_H
#define AED2324_PRJ2_G109_MANAGER_H


#include "Parser.h"
#include "../DataStructure/Graph.h"
#include <map>
#include <unordered_map>
#include <string>
#include "../DataModel/Airline.h"
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Manager {
private:
    Parser parser;
    unordered_map<string, Airline*> airlines;
    unordered_map<string, Airport*> airports;
    unordered_map<string, vector<Airport*>> cityAirports;
    unordered_map<string, unordered_set<string>> countryCities;
    Graph connections;

public:
    Manager();
    Graph getG() {return connections;}
    unordered_map<string, Airline*> getAirlines();
    unordered_map<string, Airport*> getAirports();
    Airport* getAirport(const string &code) const;
    Airline* getAirline(const string &code) const;
    vector<Vertex*> airportsAtDistanceK(const string &source, int k);
    vector<Airport> articulationPoints();
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);
    unordered_set<string> getCitiesPerCountry(const string& c);
    vector<Airport*> getAirportsPerCountry(const string &c);
    vector<vector<Airport>> scc();
    bool hasConnection(const string &s, const string &t);
    vector<Airport*> getAiportsPerCity(const string& city);
    bool dfsVisitBool(Vertex *v, Vertex *t);
    vector<Airport> hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines);
    void dfsScc(Vertex *v, stack<Airport> &s, vector<vector<Airport>> &res, int &i);
    vector<vector<Airport>> pathMaximumConnectionFlights(const string& startAirport, const string& destination, int maxFlights);
    void DFS(Vertex* current, Vertex* destination, int maxFlights, vector<Airport>& currentPath, vector<vector<Airport>>& allPaths);
    vector<Airport> findShortestPath(const string &u, const string &v);
    vector<Edge> getOutFlights(const string &code) const;
    vector<Airport> findShortestPathExcludeCountries(const string &u, const string &v, vector<string> &countries);
    int getDistance(const string &u, const string &v);
    int getTripDistance(const vector<string> &trip);
    vector<Airport> scheduleTripMinConnection(const string &u, const string &v, vector<string> & visit);
    vector<Airport> scheduleTripMinDistance(const string &u, const string &v, vector<string> & visit);
    vector<Airport> bfsMinConnections(const string &s, const string &t);
    vector<Airport> findMinConnectionsExcludeCountries(const string &s, const string &t, vector<string> & countries);
    unordered_map<string, int> outFlightsPerAirport(const string &s);
    unordered_map<string, int> inFlightsPerAirport(const string &d);
};


#endif //AED2324_PRJ2_G109_MANAGER_H
