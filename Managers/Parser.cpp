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

Parser::Parser() {}

map<string, Airline*> Parser::readAirlines() {
    fstream iff;

    try {
        iff.open("../dataset/airlines.csv", ios::in);
        map<string, Airline*> airlines;
        string line, code, name, callsign, country;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, callsign, ',');
            getline(iss, country);

            auto* airline = new Airline(code, name, callsign, country);
            airlines.insert({code, airline});
        }

        iff.close();

        return airlines;

    } catch (const ifstream::failure& e) {
        cout << "Falha a abrir o ficheiro" << endl;
    }
    return {};
}

void Parser::readFlights(Graph &g) {
    fstream iff;
    int i = 0;
    try {
        Graph graph = Graph();
        iff.open("../dataset/flights.csv", ios::in);
        map<string, Airline> airlines;
        string line, source, target, airline;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, source, ',');
            getline(iss, target, ',');
            getline(iss, airline, ',');

            auto depart = airports.find(source);
            auto dest = airports.find(target);

            if (depart != airports.end() && dest != airports.end()) {
                double distance = haversine(depart->second->getLatitude(),depart->second->getLongitude(), dest->second->getLatitude(), dest->second->getLongitude());

                auto air = getAirline(airline);
                auto source = g.findVertex(depart->second);
                if (source != nullptr){
                    if (source->hasFlight(dest->second)) {
                        for (auto edge : source->getAdj()) {
                            if (edge.getDest()->getInfo() == *dest->second) {
                                if (air != nullptr) {
                                    edge.addAirline(air);
                                }
                            }
                        }
                    }
                    if (air != nullptr) {
                        g.addEdge(depart->second, dest->second, distance, air);
                    }
                }
                i++;

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
        map<string, Airline> airlines;
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
            graph.addVertex(airport);
        }

        iff.close();

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

std::map<std::string, Airport*> Parser::getAirports() {
    return airports;
}

map<string, Airline *> Parser::getAirlines() {
    return airlines;
}

Airline* Parser::getAirline(const std::string &airline) {
    auto it = airlines.find(airline);

    if (it != airlines.end()) {
        return it->second;
    }
    return nullptr;
}


Parser::~Parser() {
    for(auto &elem : airports) {
        delete elem.second;
    }
    for (auto &elem : airlines) {
        delete elem.second;
    }
}
