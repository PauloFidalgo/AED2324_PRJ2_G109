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
    vector<Airport*> getAirportsPerCoordinatesRange(const double &x, const double &y, const int &range);
    vector<vector<Airport*>> findMinConnectionsExcludeAirports(Airport* s, Airport* t, vector<Airport*> &air);
    vector<vector<Airport*>> findMinConnectionsExcludeCities(Airport* s, Airport* t, vector<string> &cities);
    vector<vector<Airport*>> bfsMinConnectionsExcludeAirports(Airport* s, Airport* t, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines);
    vector<Airport*> minimizeDistace(Airport* u, Airport* v, const vector<Airport*> &excludedAirports, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines);
    Airport* getClosestAirport(const double &x, const double &y);
    unordered_set<string> getCitiesPerCountry(const string& c);
    vector<Airport*> getAirportsPerCountry(const string &c) const;
    vector<Airport*> getAirportsPerCity(const string& city) const;
    vector<Edge> getOutFlights(Airport* airport) const;
    double getDistance(Airport* u, Airport* v);
    double getTripDistance(const vector<Airport*> &trip);
    int getNumStops(Airport* s, Airport* t);
    bool validateCityName(const std::string &name) const;
    bool validateCountryName(const std::string &name) const;
    vector<vector<Airport*>> bfsMinConnections1(Airport* s, Airport* t);
    bool hasConnection(Airport* s, Airport* t);
    void dfsApp(Vertex *v, stack<Airport*> &s, vector<Airport*> &res, int &i);
    vector<Vertex*> airportsAtDistanceK(const string &source, int k);
    vector<vector<Airport*>> scheduleTripMinConnectionCities(Airport* u, Airport* v, vector<string>& visit);
    void dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights);
    bool hasPath(Vertex *v, Vertex *t, vector<Airport> &flights);
    vector<Airport> pathExists(Airport *d, Airport *t);
    void articulationPoints();
    void dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i);
    vector<Airport*> getAirportsPerCountry(const string &c);
    vector<Airport*> getAiportsPerCity(const string& city) const;
    vector<vector<Airport*>> scc();
    unordered_set<string> getCitiesPerCountry(const string& c) const;
    bool dfsVisitBool(Vertex *v, Vertex *t);
    vector<Airport*> hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines);
    void dfsScc(Vertex *v, stack<Airport*> &s, vector<vector<Airport*>> &res, int &i);
    vector<vector<Airport*>> pathMaximumConnectionFlights(Airport* startAirport, Airport* destination, int maxFlights);
    void DFS(Vertex* current, Vertex* destination, int maxFlights, vector<Airport*>& currentPath, vector<vector<Airport*>>& allPaths);
    vector<Airport*> findShortestPath(Airport* u, Airport* v);
    vector<Airport*> scheduleTripMinDistance(Airport* &source, Airport* &destination, vector<Airport*> &airporsToVisit, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<Airport*> findShortestPathExcludeCountries(Airport* u, Airport* v, vector<string> &countries);
    void manageFlightSearchFromMenuMinDistance(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, map<int, vector<Airport*>> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<Airport*> findShortestPathExclude(Airport* u, Airport* v, vector<Airport*> &airpExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    void manageFlightSearchFromMenu(vector<Airport*> &source, vector<Airport*> &destination, vector<Airport*> &airporsToVisit, map<int, vector<Airport*>> &cityCountry, vector<Airport*> &airportsToExclude, unordered_set<Airline*> &airlinesToExclude, unordered_set<Airline*> &flyOnlyAirlines);
    vector<vector<Airport*>> scheduleTripMinConnectionAirports(Airport* u, Airport* v, const vector<Airport*>& visit, const vector<Airport*> &exclude, const unordered_set<Airline*> &airlinesToExclude, const unordered_set<Airline*> &flyOnlyAirlines);
    vector<vector<Airport*>> scheduleTripMinConnectionCountries(Airport* u, Airport* v, vector<string> &visit);
    vector<Airport*> scheduleTripMinDistance(Airport* u, Airport* v, vector<Airport*> & visit);
    vector<vector<Airport*>> bfsMinConnections(Airport* s, Airport* t);
    vector<vector<Airport*>> findMinConnectionsExcludeCountries(Airport* s, Airport* t, vector<string> &countries);
    unordered_map<string, int> outFlightsPerAirport(Airport* s);
    unordered_map<string, int> inFlightsPerAirport(Airport *d);

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

    void findComponentDiameterPairs(Vertex *origin, vector<pair<Airport*, Airport*>> &result, int &i) const;

    void getTopKGreatestTrafficAirport(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficCity(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficCountry(int k, const bool &bars = false, const bool& asc = false) const;

    void getTopKGreatestTrafficAirportPerCity(int k, const vector<Airport *> &airportsPerCity, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficAirportPerCountry(int k, const vector<Airport *> &airportsPerCountry, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficCityPerCountry(int k, pair<string, set<string>> *selectedCountryCities, const bool &bars = false, const bool& asc = false) const;

    void getTopKGreatestTrafficAirline(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKGreatestTrafficAirlinePerCountry(int k, const unordered_set<Airline *> &airlinesCountry, const bool &bars = false, const bool& asc = false) const;

    void getTopKCountriesWithMoreAirlines(int k, const bool &bars = false, const bool& asc = false) const;

    void getTopKAirportsAirlineTravelsTo(int k, Airline *airline, const bool &bars = false, const bool& asc = false) const;
    void getTopKAirportsWithMoreAirlines(int k, const bool &bars = false, const bool& asc = false) const;
    void getTopKAirlinesThatFlyMoreToAnAirport(int k, Airport *airport, const bool &bars = false, const bool& asc = false) const;
    void getTopKAirlinesThatFlyMoreToAnAirportRatio(int k, Airport *airport, const bool &bars = false, const bool& asc = false) const;

    void listAirportsPerCountryCity(const vector<Airport *> &airportsCountry, const string &countryCity) const;



    void searchAirportsByName(const string &airportName);

    void searchAirlinesByName(const string &airlineName);

    static void printAirportInfo(Airport *airport);

    static void printAirlineInfo(Airline *airline);

    void listAirlinesPerAirport(Airport *airport);

    };


#endif //AED2324_PRJ2_G109_MANAGER_H
