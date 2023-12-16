//
// Created by Paulo Fidalgo on 30/11/2023.
//

#include "Manager.h"

Manager::Manager() {
    this->parser = Parser();
    this->airlines = parser.getAirlines();
    this->connections = parser.getGraph();
    this->airports = parser.getAirports();
}

map<std::string, Airline*> Manager::getAirlines() {
    return this->airlines;
}

map<string, Airport*> Manager::getAirports() {
    return this->airports;
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
    }

    if (!scc.empty()) {
        res.push_back(scc);
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






