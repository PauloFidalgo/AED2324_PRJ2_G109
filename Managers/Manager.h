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
    Airport* getAirportPerCode(const string &code) const;
    Airline* getAirlinePerCode(const string &code) const;
    vector<Vertex*> airportsAtDistanceK(const string &source, int k);
    void dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights);
    bool hasPath(Vertex *v, Vertex *t, vector<Airport> &flights);
    vector<Airport> pathExists(Airport *d, Airport *t);
    vector<Airport> getPath(Airport *source, Airport *destination);
    vector<Vertex*> airportsAtDistanceK(Airport *source, int k);
    void articulationPoints();
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);
    Airport* getClosestAirport(const double &x, const double &y);
    vector<Airport*> getAiportsPerCoordinatesRange(const double &x, const double &y, const int &range);
    vector<Airport*> articulationPoints();
    void dfsApp(Vertex *v, stack<Airport*> &s, vector<Airport*> &res, int &i);
    unordered_set<string> getCitiesPerCountry(const string& c);
    vector<Airport*> getAirportsPerCountry(const string &c);
    vector<vector<Airport*>> scc();
    bool hasConnection(const string &s, const string &t);
    vector<Airport*> getAiportsPerCity(const string& city);
    bool dfsVisitBool(Vertex *v, Vertex *t);
    vector<Airport> hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines);
    void dfsScc(Vertex *v, stack<Airport*> &s, vector<vector<Airport*>> &res, int &i);
    vector<vector<Airport*>> pathMaximumConnectionFlights(const string& startAirport, const string& destination, int maxFlights);
    void DFS(Vertex* current, Vertex* destination, int maxFlights, vector<Airport*>& currentPath, vector<vector<Airport*>>& allPaths);
    vector<Airport*> findShortestPath(const string &u, const string &v);
    vector<Edge> getOutFlights(const string &code) const;
    vector<Airport*> findShortestPathExcludeCountries(const string &u, const string &v, vector<string> &countries);
    double getDistance(const string &u, const string &v);
    double getTripDistance(const vector<string> &trip);
    vector<Airport*> scheduleTripMinConnection(const string &u, const string &v, vector<string> & visit);
    vector<Airport*> scheduleTripMinDistance(const string &u, const string &v, vector<string> & visit);
    vector<Airport*> bfsMinConnections(const string &s, const string &t);
    vector<Airport*> findMinConnectionsExcludeCountries(const string &s, const string &t, vector<string> & countries);
    unordered_map<string, int> outFlightsPerAirport(const string &s);
    unordered_map<string, int> inFlightsPerAirport(const string &d);

    //--------------------------------------------------------------------------------------------------
    void getNumAirportsAndFlights() const;

    void getNumFlightsAndAirlines(const string &airportCode) const;
    void getNumFlightsAndAirlinesByName(const string &airportName) const;

    void getNumFlightsPerCity(const string &city) const;

    void getNumFlightsPerAirline(const string &airlineCode) const;
    void getNumFlightsPerAirlineByName(const string &airlineName) const;

    void getCountriesCanFlyToAirport(const string &airportCode) const;
    void getCountriesCanFlyToAirportByName(const string &airportName) const;

    void getCountriesCanFlyToCity(const string &city) const;

    void getDestinantionsDistance1(const string &airportCode) const;
    void getDestinationsDistance1ByName(const string &airportName) const;

    void getDestinantions(const string &airportCode) const;
    void getDestinantionsByName(const string &airportName) const;

    void getDestinantionsUntilDistanceK(const string &airportCode, const int &k) const;
    void getDestinantionsUntilDistanceKByName(const string &airportName, const int &k) const;

    //adicionar por cities e countries, incluir rejected vector, ou airlines obrigatorias

    void diameterPairs() const;

    void findComponentDiameterPairs(Vertex *origin, vector<pair<Airport, Airport>> &result, int &i) const;

    void getTopKGreatestTrafficAirport(int k) const;

    void getTopKGreatestTrafficAirportPerCountry(int k, const string &country) const;

    void getTopKGreatestTrafficAirline(int k) const;

    void getTopKGreatestTrafficAirlinePerCountry(int k, const string &country) const;
    //fazer para mais e menos traffic
    //fazer para cidades e paises

    //top k airports com para onde voa uma companhia x;
    //top k airports com mais e menos companhias diferentes;
    //top k airports para onde voa mais a companhia x (racio entre voos para o aeroporto e voos totais); absoluto ou relativo
    //listar ailines por aeroporto



    void listAiportsPerCountry(const string &country) const;

    void searchAirportsByName(const string &airportName);

    void searchAirlinesByName(const string &airlineName);

    void printAirportInfo(const string &airportCode);

    void printAirlineInfo(const string &airlineCode);
};


#endif //AED2324_PRJ2_G109_MANAGER_H
