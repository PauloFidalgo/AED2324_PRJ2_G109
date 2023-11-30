//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Parser.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

map<string, Airline> Parser::readAirlines() const {
    fstream iff;

    try {
        iff.open("../dataset/airlines.csv", ios::in);
        map<string, Airline> airlines;
        string line, code, name, callsign, country;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, callsign, ',');
            getline(iss, country);

            Airline airline = Airline(code, name, callsign, country);
            airlines.insert({code, airline});
        }

        iff.close();

        return airlines;

    } catch (const ifstream::failure& e) {
        cout << "Falha a abrir o ficheiro" << endl;
    }
    return {};
}

void Parser::readFlights(Graph &g) const {
    fstream iff;

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

            auto* departure = graph.findVertex(Airport(source, "", "", "", 0, 0));
            auto* arrival = graph.findVertex(Airport(target, "", "", "", 0, 0));
            Edge e = Edge(arrival, 0);
            departure->addAdj(e, airline);
        }

        iff.close();

    } catch (const ifstream::failure& e) {
        cout << "Falha a abrir o ficheiro" << endl;
    }
}

Graph Parser::getGraph() const {
    fstream iff;

    try {
        Graph graph = Graph();
        iff.open("../dataset/airports.csv", ios::in);
        map<string, Airline> airlines;
        string line, code, name, city, country, temp;
        float latitude, longitude;

        getline(iff, line);

        while (getline(iff, line)) {
            stringstream iss(line);

            getline(iss, code, ',');
            getline(iss, name, ',');
            getline(iss, city, ',');
            getline(iss, country, ',');
            getline(iss, temp, ',');
            latitude = stof(temp);
            getline(iss, temp, ',');
            longitude = stof(temp);

            Airport airport = Airport(code, name, city, country, latitude, longitude);
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