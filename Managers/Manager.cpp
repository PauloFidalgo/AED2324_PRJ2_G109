//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Manager.h"
#include <iostream>
#include <unordered_map>

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

        if (scc.size() > 1) {
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


vector<Edge> Manager::getOutFlights(const string &code) const {
    auto v = getAirport(code);


    if (v == nullptr) return {};

    auto vertex = connections.findVertex(v);
    if (vertex == nullptr) return {};

    return vertex->getAdj();
}


bool notIn(vector<Airport> &v, const Airport &t) {
    for (auto &it : v) {
        if (it == t) return false;
    }
    return true;
}

vector<Airport> Manager::sheduleTrip(string &u, const string &v, vector<string>& visit) {
    vector<Airport> path;


    visit.push_back(v);
    for (auto &flight : visit) {

        auto res = bfsPathTrip(u, flight);

        for (auto &airport : res) {
            if (notIn(path, airport)) {
                path.push_back(airport);
            }
        }
        u = flight;
    }


    return path;
}

vector<Airport> Manager::bfsPathTrip(const string &s, const string &t) {
    for (auto node : connections.getVertexSet()) {
        node->setVisited(false);
    }

    auto first = connections.findVertex(getAirport(s));
    auto last = connections.findVertex(getAirport(t));

    vector<Airport> path;

    queue<Vertex*> q;
    unordered_map<Vertex*, Vertex*> parent;

    q.push(first);
    first->setVisited(true);

    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();

        for (Edge& flight : current->getAdj()) {
            Vertex* neighbor = flight.getDest();

            if (!neighbor->isVisited()) {
                q.push(neighbor);
                neighbor->setVisited(true);
                parent[neighbor] = current;

                if (neighbor == last) {
                    break;
                }
            }
        }
    }

    Vertex* current = last;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }
    return path;
}

vector<Airport> Manager::findShortestPath(const string &u, const string &v) {
    unordered_map<Vertex*, int> distances;
    for (Vertex* vertex : connections.getVertexSet()) {
        distances[vertex] = numeric_limits<int>::max();
    }

    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*>>> pq;


    Vertex* sourceAirport = connections.findVertex(getAirport(u));
    Vertex* targetAirport = connections.findVertex(getAirport(v));


    if (!sourceAirport || !targetAirport) {
        cerr << "Source or target airport not found." << endl;
        return {};
    }

    distances[sourceAirport] = 0;
    pq.push({0, sourceAirport});

    unordered_map<Vertex*, Vertex*> parent;

    while (!pq.empty()) {
        Vertex* current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distances[current]) {
            continue;
        }

        for (Edge& flight : current->getAdj()) {
            Vertex* neighbor = flight.getDest();
            int weight = flight.getWeight();

            int newDistance = currentDistance + weight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                pq.push({newDistance, neighbor});
                parent[neighbor] = current;
            }
        }
    }

    vector<Airport> path;
    Vertex* current = targetAirport;

    while (current != nullptr) {
        path.insert(path.begin(), current->getInfo());
        current = parent[current];
    }

    return path;
}

int Manager::getDistance(const string &u, const string &v) {
    auto p = findShortestPath(u, v);

    auto it = p.begin();
    double dist = 0.0;

    while (it != p.end()) {
        auto source = connections.findVertex(getAirport(it->getCode()));

        if (source) {
            auto nextIt = std::next(it);

            if (nextIt != p.end()) {
                for (auto &edge : source->getAdj()) {
                    if (edge.getDest()->getInfo().getCode() == nextIt->getCode()) {
                        dist += edge.getWeight();
                        break;
                    }
                }
            } else {
                break;
            }

            it = nextIt;
        } else {
            break;
        }
    }
    return dist;
}



