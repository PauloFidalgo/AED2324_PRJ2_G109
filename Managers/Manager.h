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
    Graph getG() {return connections;}
    std::map<std::string, Airline*> getAirlines();
    std::map<std::string, Airport*> getAirports();
    Airport* getAirport(const string &code) const;
    Airline* getAirline(const string &code) const;
    void dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights);
    bool hasPath(Vertex *v, Vertex *t, vector<Airport> &flights);
    vector<Airport> pathExists(Airport *d, Airport *t);
    vector<Airport> getPath(Airport *source, Airport *destination);
    vector<Vertex*> airportsAtDistanceK(Airport *source, int k);
    vector<Airport> articulationPoints();
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);
    vector<vector<Airport>> scc();
    vector<Airport> hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines);
    void dfsScc(Vertex *v, stack<Airport> &s, vector<vector<Airport>> &res, int &i);
    vector<Airport> findPathExcludeCountries(Airport *source, Airport *target, vector<string> &countries);
    vector<Airport> pathMaximumConnectionFlights(Airport *source, Airport *target, int &max);
    vector<Airport> getAirportsPerCountry(const string &country);
    int minPath(Vertex *v, Vertex *t, stack<Airport> &res, int &last);
    vector<Airport> shortesPath(Airport *source, Airport *target);
    vector<Edge> getOutFlights(const string &code) const;

    //--------------------------------------------------------------------------------------------------
    void getNumAirportsAndFlights() const;

    void getNumFlightsAndAirlines(const string &airportCode) const;

    void getNumFlightsPerCity(const string &city) const;

    void getNumFlightsPerAirline(const string &airlineCode) const;

    void getCountriesCanFlyToAirport(const string &airportCode) const;

    void getCountriesCanFlyToCity(const string &city) const;

    void getDestinantions(const string &airportCode) const;
};


#endif //AED2324_PRJ2_G109_MANAGER_H
