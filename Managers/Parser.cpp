//
// Created by Paulo Fidalgo e escrito por Mafarrica on 30/11/2023.
//

#include "Parser.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

void Parser::readAirlines() {
    fstream iff;

    try {
        iff.open("../dataset/airlines.csv", ios::in);
        unordered_map<string, Airline*> air;
        unordered_map<string, Airline*> airByName;
        string line, code, name, callsign, country;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, callsign, ',');
            getline(iss, country);

            auto* airline = new Airline(code, name, callsign, country);
            air.insert({code, airline});
            airByName.insert({name, airline});
        }

        iff.close();

        this->airlines = air;
        this->airlinesByName = airByName;

    } catch (const ifstream::failure& e) {
        cout << "Falha a abrir o ficheiro" << endl;
    }
}

void Parser::readFlights(Graph &g) {
    fstream iff;
    try {
        iff.open("../dataset/flights.csv", ios::in);
        string line, s, target, airline;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, s, ',');
            getline(iss, target, ',');
            getline(iss, airline, ',');

            auto depart = airports.find(s);
            auto dest = airports.find(target);

            if (depart != airports.end() && dest != airports.end()) {
                double distance = haversine(depart->second->getLatitude(),depart->second->getLongitude(), dest->second->getLatitude(), dest->second->getLongitude());
                depart->second->increaseNumFlightsOut();
                dest->second->increaseNumFlightsIn();
                auto air = getAirline(airline);
                air->increaseNumFlights();
                auto source = g.findVertex(depart->second);
                if (source != nullptr){
                    if (source->hasFlight(dest->second)) {
                        for (auto &edge : source->getAdj()) {
                            if (edge.getDest()->getInfo() == *dest->second) {
                                if (air != nullptr) {
                                    edge.addAirline(air);
                                }
                            }
                        }
                    }
                    else if (air != nullptr) {
                        g.addEdge(depart->second, dest->second, distance, air);
                    }
                }
            }
        }

        iff.close();

    } catch (const ifstream::failure& e) {
        cout << "Falha a abrir o ficheiro" << endl;
    }
}

Graph Parser::getGraph() {
    fstream iff;

    try {
        Graph graph = Graph();
        iff.open("../dataset/airports.csv", ios::in);
        string line, code, name, city, country, temp;
        double latitude, longitude;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, city, ',');
            getline(iss, country, ',');
            getline(iss, temp, ',');
            latitude = stod(temp);
            getline(iss, temp, ',');
            longitude = stod(temp);

            auto* airport = new Airport(code, name, city, country, latitude, longitude);
            airports.insert({code, airport});
            airportsByName.insert({name, airport});

            auto cityAir = cityAirports.find(city);
            auto countryAir = countryCities.find(country);

            if (cityAir != cityAirports.end()) {
                cityAir->second.push_back(airport);
            }
            else {
                cityAirports.insert({city, {airport}});
            }

            if (countryAir != countryCities.end()) {
                countryAir->second.insert({city});
            }
            else {
                countryCities.insert({country, {city}});
            }
            graph.addVertex(airport);
        }

        iff.close();
        this->readAirlines();
        this->readFlights(graph);

        return graph;
    } catch (const ifstream::failure& e) {
        cout << "Falha a abrir o ficheiro" << endl;
    }
    return {};
}

double Parser::haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

std::unordered_map<std::string, Airport*> Parser::getAirports() {
    return airports;
}

unordered_map<string, Airline *> Parser::getAirlines() {
    return airlines;
}

unordered_map<string, vector<Airport*>> Parser::getCityAirports() {
    return cityAirports;
}

Airline* Parser::getAirline(const std::string &airline) {
    auto it = airlines.find(airline);

    if (it != airlines.end()) {
        return it->second;
    }
    return nullptr;
}

unordered_map<string, unordered_set<string>> Parser::getCountryCities() {
    return countryCities;
}


Parser::~Parser() {

}

std::unordered_map<std::string, Airport *> Parser::getAirportsByName() {
    return airportsByName;
}

std::unordered_map<std::string, Airline *> Parser::getAirlinesByName() {
    return airlinesByName;
}


