//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_MANAGER_H
#define AED2324_PRJ2_G109_MANAGER_H


#include "Parser.h"
#include "../DataStructure/Graph.h"
#include "../Viewer/Viewer.h"
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
    unordered_map<std::string, Airport*> airportsByName;
    unordered_map<std::string, Airline*> airlinesByName;
    Graph connections;

public:
    Manager();
    Graph getG() {return connections;}
    unordered_map<string, Airline*> getAirlines();
    unordered_map<string, Airport*> getAirports();
    Airport* getAirport(const string &code) const;
    Airline* getAirline(const string &code) const;
    vector<Vertex*> airportsAtDistanceK(const string &source, int k);
    void dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights);
    bool hasPath(Vertex *v, Vertex *t, vector<Airport> &flights);
    vector<Airport> pathExists(Airport *d, Airport *t);
    vector<Airport> getPath(Airport *source, Airport *destination);
    vector<Vertex*> airportsAtDistanceK(Airport *source, int k);
    void articulationPoints();
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);
    unordered_set<string> getCitiesPerCountry(const string& c) const;
    vector<Airport*> getAirportsPerCountry(const string &c) const;
    vector<vector<Airport>> scc();
    bool hasConnection(const string &s, const string &t);
    vector<Airport*> getAirportsPerCity(const string& city) const;
    bool dfsVisitBool(Vertex *v, Vertex *t);
    vector<Airport> hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines);
    void dfsScc(Vertex *v, stack<Airport> &s, vector<vector<Airport>> &res, int &i);
    vector<vector<Airport>> pathMaximumConnectionFlights(const string& startAirport, const string& destination, int maxFlights);
    void DFS(Vertex* current, Vertex* destination, int maxFlights, vector<Airport>& currentPath, vector<vector<Airport>>& allPaths);
    vector<Airport> findShortestPath(const string &u, const string &v);
    vector<Edge> getOutFlights(const string &code) const;
    vector<Airport> findShortestPathExcludeCountries(const string &u, const string &v, vector<string> &countries);
    double getDistance(const string &u, const string &v);
    double getTripDistance(const vector<string> &trip);
    vector<Airport> scheduleTripMinConnection(const string &u, const string &v, vector<string> & visit);
    vector<Airport> scheduleTripMinDistance(const string &u, const string &v, vector<string> & visit);
    vector<Airport> bfsMinConnections(const string &s, const string &t);
    vector<Airport> findMinConnectionsExcludeCountries(const string &s, const string &t, vector<string> & countries);
    unordered_map<string, int> outFlightsPerAirport(const string &s);
    unordered_map<string, int> inFlightsPerAirport(const string &d);

    //--------------------------------------------------------------------------------------------------
    void getNumAirportsAndFlights() const;

    void getNumFlightsAndAirlines(Airport *airport) const;

    void getNumFlightsPerCity(const string &city) const;

    void getNumFlightsPerAirline(Airline *airline) const;

    void getCountriesCanFlyToAirport(Airport *airport) const;

    void getCountriesCanFlyToCity(const string &city) const;

    void getAirportDestinantionsDistance1(Airport *airport) const;
    void getCityDestinationsDistance1(vector<Airport *> air, const string& city) const;
    void getCountryDestinationsDistance1(vector<Airport *> air, const string& country) const;

    void getAirportDestinantions(Airport *airport) const;
    void getCityDestinantions(const vector<Airport *> &airportsCity, const string& city) const;
    void getCountryDestinantions(const vector<Airport *> &airportsCountry, const string& country) const;

    void getAirportDestinantionsUntilDistanceK(Airport *airport, const int &k) const;
    void getCityDestinantionsUntilDistanceK(const vector<Airport *> &airportsCity, const string& city, const int &k) const;
    void getCountryDestinantionsUntilDistanceK(const vector<Airport *> &airportsCountry, const string& country, const int &k) const;

    void diameterPairs() const;

    void findComponentDiameterPairs(Vertex *origin, vector<pair<Airport, Airport>> &result, int &i) const;

    void getTopKGreatestTrafficAirport(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficCity(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficCountry(int k, const bool &bars = false, const bool& asc = false) const;

    void getTopKGreatestTrafficAirportPerCity(int k, const vector<Airport *> &airportsPerCity, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficAirportPerCountry(int k, const vector<Airport *> &airportsPerCountry, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficCityPerCountry(int k, pair<string, set<string>> *selectedCountryCities, const bool &bars = false, const bool& asc = false) const;

    void getTopKGreatestTrafficAirline(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficAirlinePerCountry(int k, const vector<Airline *> &airlinesCountry, const bool &bars = false, const bool& asc = false) const;

    void getTopKAirportsAirlineTravelsTo(int k, Airline *airline, const bool &bars = false, const bool& asc = false) const;
    void getTopKAirportsWithMoreAirlines(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKAirlinesThatFlyMoreToAnAirport(int k, Airport *airport, const bool &bars = false, const bool& asc = false) const;
    //falta ratio

    void listAiportsPerCountry(const vector<Airport *> &airportsCountry, const string &country) const;


    void searchAirportsByName(const string &airportName);

    void searchAirlinesByName(const string &airlineName);

    static void printAirportInfo(Airport *airport);

    static void printAirlineInfo(Airline *airline);

    void listAirlinesPerAirport(Airport *airport);

};


#endif //AED2324_PRJ2_G109_MANAGER_H
