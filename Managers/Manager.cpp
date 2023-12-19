//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include <iostream>
#include "Manager.h"

Manager::Manager() {
    this->parser = Parser();
    this->connections = parser.getGraph();
    this->airports = parser.getAirports();
    this->airlines = parser.getAirlines();
}

map<std::string, Airline*> Manager::getAirlines() {
    return this->airlines;
}

map<string, Airport*> Manager::getAirports() {
    return this->airports;
}

Airport* Manager::getAirport(const std::string &code) const {
    auto it = airports.find(code);

    if (it != airports.end()) {
        return it->second;
    }

    return nullptr;
}

Airline* Manager::getAirline(const std::string &code) const {
    auto it = airlines.find(code);

    if (it != airlines.end()) {
        return it->second;
    }

    return nullptr;
}

bool Manager::hasPath(Vertex *v, Vertex *t, vector<Airport> &flights) {
    v->setVisited(true);
    flights.push_back(v->getInfo());

    if (v == t) return true;

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();

        if (!dest->isVisited()) {
            if (hasPath(dest, t, flights)) return true;
        }
     }
}

vector<Airport> Manager::pathExists(Airport *d, Airport *t) {
    auto dest = connections.findVertex(d);
    auto target = connections.findVertex(t);

    for (auto &edge : connections.getVertexSet()) {
        edge->setVisited(false);
    }

    vector<Airport> flights;

    if (dest != nullptr && target != nullptr) {
        hasPath(dest, target, flights);
    }

    return flights;
}

void Manager::dfsVisit(Vertex *v, Vertex *t, vector<Airport> &flights) {
    v->setVisited(true);

    if (v == t) return;

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();

        if (!dest->isVisited()) {
            flights.push_back(dest->getInfo());
            dfsVisit(dest, t, flights);
        }
    }
}

vector<Vertex*> Manager::airportsAtDistanceK(Airport *source, int k) {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(true);
    }

    auto depart = connections.findVertex(source);

    queue<Vertex*> q;
    q.push(depart);
    vector<Vertex*> res;

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            auto next = q.front();
            next->setVisited(true);
            q.pop();

            if (k == 0) {
                res.push_back(next);
            }

            for (auto &edge : next->getAdj()) {
                auto w = edge.getDest();

                if (!w->isVisited()) {
                    q.push(w);
                }
            }
        }
        k--;
    }
    return res;
}

vector<Airport> Manager::articulationPoints() {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }

    vector<Airport> res;
    stack<Airport> s;
    int i = 0;

    for (auto &airport : connections.getVertexSet()) {
        if (!airport->isVisited()) {
            dfsApp(airport, s, res, i);
        }
    }
    return res;
}

void Manager::dfsApp(Vertex *v, stack<Airport> &s, vector<Airport> &res, int &i) {
    v->setNum(i);
    v->setLow(i);
    i++;
    s.push(v->getInfo());
    v->setVisited(true);
    v->setProcessing(true);
    int child = 0;

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();
        if (!dest->isVisited()) {
            child++;
            dfsApp(dest, s, res, i);
            v->setLow(min(v->getLow(), dest->getLow()));

            if (dest->getLow() >= v->getNum() && v->getNum() != 0) {
                res.push_back(dest->getInfo());
            }
        }
        else if (dest->isProcessing()) {
            v->setLow(min(v->getLow(), dest->getNum()));
        }
        if (child > 1 && v->getNum() == 0) {
            res.push_back(v->getInfo());
        }
    }
    v->setProcessing(false);
    s.pop();
}

bool hasAirline(Edge &e, vector<Airline*> &air) {
    for (auto &airline : air) {
        if (e.hasAirline(airline)) {
            return true;
        }
    }
    return false;
}


vector<Airport> Manager::hasFlightAirline(Airport *source, Airport *target, vector<Airline*> &setOfAirlines) {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }
    vector<Airport> res;
    queue<Vertex*> q;

    auto init = connections.findVertex(source);
    q.push(init);

    while (!q.empty()) {
        auto next = q.front();
        q.pop();
        next->setVisited(true);

        for (auto edge : next->getAdj()) {
            if (hasAirline(edge, setOfAirlines)) {
                auto dest = edge.getDest();
                if (!dest->isVisited()) {
                    q.push(dest);
                }
            }
        }
    }
    return res;
}

vector<vector<Airport>> Manager::scc() {
    for (auto &airport : connections.getVertexSet()) {
        airport->setVisited(false);
    }

    vector<vector<Airport>> res;
    stack<Airport> s;

    int i = 0;
    for (auto &airport : connections.getVertexSet()) {
        if (!airport->isVisited()) {
            dfsScc(airport, s, res, i);
        }
    }

    return res;

}

void Manager::dfsScc(Vertex *v, stack<Airport> &s, vector<vector<Airport>> &res, int &i) {
    v->setLow(i);
    v->setNum(i);
    v->setProcessing(true);
    v->setVisited(true);
    i++;
    s.push(v->getInfo());

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();

        if (!dest->isVisited()) {
            dfsScc(dest, s, res, i);

            v->setLow(min(v->getLow(), dest->getLow()));
        }
        else if (dest->isProcessing()) {
            v->setLow(min(v->getLow(), dest->getNum()));
        }
    }

    v->setProcessing(false);

    vector<Airport> scc;
    if (v->getNum() == v->getLow()) {
        while (!s.empty() && s.top().getCode() != v->getInfo().getCode()){
            scc.push_back(s.top());
            s.pop();
        }
        if (!s.empty()) {
            scc.push_back(s.top());
            s.pop();
        }

        if (!scc.empty()) {
            res.push_back(scc);
        }
    }
}

bool excludeCountries(Vertex* v, vector<string> &countries) {
    for (const auto& country : countries) {
        if (v->getInfo().getCountry() == country) {
            return true;
        }
    }
    return false;
}

vector<Airport> Manager::findPathExcludeCountries(Airport *source, Airport *target, vector<string> &countries) {
    for (auto &node : connections.getVertexSet()) {
        if (!excludeCountries(node, countries)) {
            node->setVisited(false);
        }
        else {
            node->setVisited(true);
        }
    }

    auto depart = connections.findVertex(source);
    auto arrival = connections.findVertex(target);

    vector<Airport> res;

    if (depart != nullptr && arrival != nullptr) {
        hasPath(depart, arrival, res);
    }

    return res;
}

vector<Airport> Manager::pathMaximumConnectionFlights(Airport *source, Airport *target, int &max) {
    for (auto &node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    auto depart = connections.findVertex(source);
    queue<Vertex*> q;
    vector<Airport> res;

    q.push(depart);

    while (!q.empty() && max > 0) {
        auto next = q.front();
        q.pop();
        next->setVisited(true);

        for (const auto& edge : next->getAdj()) {
            auto dest = edge.getDest();

            if (!dest->isVisited()) {
                q.push(dest);
            }

            res.push_back(dest->getInfo());
        }
        max--;
    }
    return res;
}

vector<Airport> Manager::getAirportsPerCountry(const string &country) {
    vector<Airport> res;

    for (auto &node : connections.getVertexSet()) {
        if (node->getInfo().getCountry() == country) {
            res.push_back(node->getInfo());
        }
    }
    return res;
}

vector<Airport> Manager::shortesPath(Airport *source, Airport *target) {
    for (auto &node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    auto depart = connections.findVertex(source);
    auto destination = connections.findVertex(target);

    stack<Airport> s;
    int i = 0;
    if (destination != nullptr && depart != nullptr) {
        minPath(depart, destination, s, i);
    }

    vector<Airport> res;

    while (!s.empty()) {
        res.push_back(s.top());
        s.pop();
    }

    return res;
}

int Manager::minPath(Vertex *v, Vertex *t, stack<Airport> &res, int &last) {
    if (v == t) return 0;
    v->setVisited(true);

    res.push(v->getInfo());

    int ans = INT32_MAX;

    for (auto &edge : v->getAdj()) {
        auto dest = edge.getDest();

        if (!dest->isVisited()) {
            int current = minPath(dest, t, res, last);

            if (current < INT32_MAX) {
                last += current;
                if (last < ans) {
                    ans = last;
                }
            }
        }
    }

    v->setVisited(false);

    return ans;
}


vector<Edge> Manager::getOutFlights(const string &code) const {
    auto v = getAirport(code);


    if (v == nullptr) return {};

    auto vertex = connections.findVertex(v);
    if (vertex == nullptr) return {};

    return vertex->getAdj();
}

void Manager::getNumAirportsAndFlights() const {
    int numAirports = airports.size();
    int numFlights = 0;
    for (auto& elem : connections.getVertexSet()) {
        numFlights += elem->getInfo().getNumFlightsOut();
    }
    int space = numFlights > numAirports ? to_string(numFlights).length() + 2  : to_string(numAirports).length() + 2;
    int lenAirports = (space - to_string(numAirports).length()) / 2;
    int lenFAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenAirports : lenAirports + 1;
    int lenFlights = (space - to_string(numFlights).length()) / 2;
    int lenFFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenFlights : lenFlights + 1;
    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "| Number of airports |" << string(lenAirports, ' ') << numAirports << string(lenFAirports, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenFlights, ' ') << numFlights << string(lenFFlights, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Manager::getNumFlightsAndAirlines(const string &airportCode) const {
    auto airport = airports.find(airportCode);
    int numFlights = airport->second->getNumFlightsOut();
    int numAirlines = 0;
    for (auto &elem : connections.getVertexSet()) {
        if (*airport->second == elem->getInfo()) {
            set<Airline*> air;
            for (auto& edge : elem->getAdj()) {
                for (auto& airline : edge.getAirlines()) {
                    air.emplace(airline);
                }
            }
            numAirlines = air.size();
            break;
        }
    }
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    int lenNumAirlines = (space - to_string(numAirlines).length()) / 2;
    int lenFNumAirlines = (space - to_string(numAirlines).length()) % 2 == 0 ? lenNumAirlines : lenNumAirlines + 1;

    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airport Code    |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|    Airport Name    |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "| Number of airlines |" << string(lenNumAirlines, ' ') << numAirlines << string(lenFNumAirlines, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Manager::getNumFlightsPerCity(const string &city) const {
    int numFlights = 0;
    for (auto& elem : connections.getVertexSet()) {
        if (elem->getInfo().getCity() == city) {
            numFlights += elem->getInfo().getNumFlightsOut();
            numFlights += elem->getInfo().getNumFlightsIn();
        }
    }
    int space = city.length() > to_string(numFlights).length() ? city.length() + 2: to_string((numFlights)).length() + 2;
    int lenCity = (space - city.length()) / 2;
    int lenFCity = (space - city.length()) % 2 == 0 ? lenCity : lenFCity + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    cout << "---------------------" << string(space + 1, '-') << endl;
    cout << "|       City        |" << string(lenCity, ' ') << city << string (lenFCity, ' ') << '|' << endl;
    cout << "| Number of flights |" << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '|' << endl;
    cout << "---------------------" << string(space + 1, '-') << endl;
}

void Manager::getNumFlightsPerAirline(const string &airlineCode) const {
    auto airline = airlines.find(airlineCode);
    int numFlights = airline->second->getNumFlights();
    int space = airline->second->getName().length() > to_string(numFlights).length() ? airline->second->getName().length() + 2: to_string((numFlights)).length() + 2;
    int lenAirlineCode = (space - airlineCode.length()) / 2;
    int lenFAirlineCode = (space - airlineCode.length()) % 2 == 0 ? lenAirlineCode : lenAirlineCode + 1;
    int lenAirlineName = (space - airline->second->getName().length()) / 2;
    int lenFAirportName = (space - airline->second->getName().length()) % 2 == 0 ? lenAirlineName : lenAirlineName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airline code    |" << string(lenAirlineCode, ' ') << airlineCode << string(lenFAirlineCode, ' ') << '|' << endl;
    cout << "|    Airline name    |" << string(lenAirlineName, ' ') << airline->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Manager::getCountriesCitiesCanFlyTo(const string &airportCode) const {
    auto airport = airports.find(airportCode);
    vector<Edge> edges = getOutFlights(airportCode);
    set<string> countries;
    set<string> cities;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo().getCountry());
        cities.emplace(edge.getDest()->getInfo().getCity());
    }
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
    cout << "|            Airport Code            |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|            Airport Name            |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Countries you can fly to |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of Cities you can fly to   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
}


void Manager::getDestinantions(const string &airportCode) const {
    auto airport = airports.find(airportCode);
    vector<Edge> edges = getOutFlights(airportCode);
    int numAiports = edges.size();
    set<string> countries;
    set<string> cities;
    for (auto& edge : edges) {
        countries.emplace(edge.getDest()->getInfo().getCountry());
        cities.emplace(edge.getDest()->getInfo().getCity());
    }
    int numCountries = countries.size();
    int numCities = cities.size();
    int space = airport->second->getName().length() > 7 ? airport->second->getName().length() + 2: 7;
    int lenAirportCode = (space - airportCode.length()) / 2;
    int lenFAirportCode = (space - airportCode.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - airport->second->getName().length()) / 2;
    int lenFAirportName = (space - airport->second->getName().length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAiports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAiports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "-------------------------" << string(space + 1, '-') << endl;
    cout << "|     Airport Code      |" << string(lenAirportCode, ' ') << airportCode << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|     Airport Name      |" << string(lenAirportName, ' ') << airport->second->getName() << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Destination Airports  |" << string(lenNumAirports, ' ') << numAiports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Destination Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Destination Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "-------------------------" << string(space + 1, '-') << endl;
}