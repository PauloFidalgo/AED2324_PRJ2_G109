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
    unordered_map<string, Airport*> airportsByName;
    unordered_map<string, Airline*> airlinesByName;
    unordered_map<string, unordered_set<Airline*>> countryAirlines;
    Graph connections;

public:
    Manager();
    unordered_map<string, Airline*> getAirlines();
    unordered_map<string, Airport*> getAirports();
    Airport* getAirportPerCode(const string &code) const;
    vector<Airport*> validateCountry(const string &country) const;
    unordered_set<Airline*> getAirlinesPerCountry(const string& country);
    vector<Airport*> validateCity(const string &city) const;
    Airline* getAirlinePerCode(const std::string &code) const;
    Airport* getAirportPerName(const string &name) const;
    Airline* getAirlinePerName(const std::string &name) const;
    vector<Airport> getPath(Airport *source, Airport *destination);
    vector<Airport*> getAiportsPerCoordinatesRange(const double &x, const double &y, const int &range);
    vector<vector<Airport*>> findMinConnectionsExcludeAirports(Airport* s, Airport* t, vector<Airport*> &air);
    vector<vector<Airport*>> findMinConnectionsExcludeCities(Airport* s, Airport* t, vector<string> &cities);
    vector<vector<Airport*>> bfsMinConnectionsExcludeAirports(Airport* s, Airport* t, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines);
    vector<Airport*> minimizeDistace(Airport* u, Airport* v, const vector<Airport*> &excludedAirports, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines);
    Airport* getClosestAirport(const double &x, const double &y);
    unordered_set<string> getCitiesPerCountry(const string& c);
    vector<Airport*> getAirportsPerCountry(const string &c);
    vector<Airport*> getAiportsPerCity(const string& city) const;
    vector<Edge> getOutFlights(Airport* airport) const;
    double getDistance(Airport* u, Airport* v);
    double getTripDistance(const vector<Airport*> &trip);
    int getNumStops(Airport* s, Airport* t);
    vector<vector<Airport*>> bfsMinConnections1(Airport* s, Airport* t);

    vector<Vertex*> airportsAtDistanceK(const string &source, int k);
    vector<vector<Airport*>> scheduleTripMinConnectionCities(Airport* u, Airport* v, vector<string>& visit);
    void dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights);
    bool hasPath(Vertex *v, Vertex *t, vector<Airport> &flights);
    vector<Airport> pathExists(Airport *d, Airport *t);

    vector<Vertex*> airportsAtDistanceK(Airport *source, int k);
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);


    vector<Airport*> articulationPoints();
    void dfsApp(Vertex *v, stack<Airport*> &s, vector<Airport*> &res, int &i);
    vector<vector<Airport*>> scc();
    bool hasConnection(Airport* s, Airport* t);
    bool dfsVisitBool(Vertex *v, Vertex *t);
    vector<Airport*> hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines);
    void dfsScc(Vertex *v, stack<Airport*> &s, vector<vector<Airport*>> &res, int &i);
    vector<vector<Airport*>> pathMaximumConnectionFlights(Airport* startAirport, Airport* destination, int maxFlights);
    void DFS(Vertex* current, Vertex* destination, int maxFlights, vector<Airport*>& currentPath, vector<vector<Airport*>>& allPaths);
    vector<Airport*> findShortestPath(Airport* u, Airport* v);
    vector<Airport*> scheduleTripMinDistance(Airport* &source, Airport* &destination, vector<Airport*> &airporsToVisit, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<Airport*> findShortestPathExcludeCountries(Airport* u, Airport* v, vector<string> &countries);
    vector<vector<Airport*>> manageFlightSearchFromMenuMinDistance(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, map<int, vector<Airport*>> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<Airport*> findShortestPathExclude(Airport* u, Airport* v, vector<Airport*> &airpExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<vector<Airport*>> manageFlightSearchFromMenu(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, map<int, vector<Airport*>> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<vector<Airport*>> scheduleTripMinConnectionAirports(Airport* u, Airport* v, const vector<Airport*>& visit, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines);
    vector<vector<Airport*>> scheduleTripMinConnectionCountries(Airport* u, Airport* v, vector<string> &visit);
    vector<Airport*> scheduleTripMinDistance(Airport* u, Airport* v, vector<Airport*> & visit);
    vector<vector<Airport*>> bfsMinConnections(Airport* s, Airport* t);
    vector<vector<Airport*>> findMinConnectionsExcludeCountries(Airport* s, Airport* t, vector<string> &countries);
    unordered_map<string, int> outFlightsPerAirport(Airport* s);
    unordered_map<string, int> inFlightsPerAirport(Airport *d);

    //--------------------------------------------------------------------------------------------------
    void getNumAirportsAndFlights() const;

    void getNumFlightsAndAirlines(const string &airportCode) const;
    void getNumFlightsAndAirlinesByName(const string &airportName) const;

    void getNumFlightsPerCity(const string &city) const;

    void getNumFlightsPerAirline(const string &airlineCode) const;
    void getNumFlightsPerAirlineByName(const string &airlineName) const;

    void getCountriesCanFlyToAirport(Airport* airportCode) const;

    void getCountriesCanFlyToCity(const string &city) const;

    void getDestinantionsDistance1(Airport* airportCode) const;
    void getDestinationsDistance1ByName(const string &airportName) const;

    void getDestinantions(const string &airportCode) const;
    void getDestinantionsByName(const string &airportName) const;

    void getDestinantionsUntilDistanceK(const string &airportCode, const int &k) const;
    void getDestinantionsUntilDistanceKByName(const string &airportName, const int &k) const;

    //adicionar por cities e countries, incluir rejected vector, ou airlines obrigatorias

    void diameterPairs() const;

    void findComponentDiameterPairs(Vertex *origin, vector<pair<Airport*, Airport*>> &result, int &i) const;

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
