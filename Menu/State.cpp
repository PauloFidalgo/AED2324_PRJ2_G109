#include "State.h"

std::stack<State*> State::stateHistory;
std::stack<State*> State::statisticsHistory;

State::State() {
    this->manager = Manager();
}

State::~State() {
    while (!stateHistory.empty()){
        delete stateHistory.top();
        stateHistory.pop();
    }
    while (!statisticsHistory.empty()){
        delete statisticsHistory.top();
        statisticsHistory.pop();
    }
}


Airport* State::getValidSingleAirport() {
    Airport* airportCode;
    Airport* airportName;
    getline(cin, code);
    airportCode = manager.getAirportPerCode(code);
    airportName = manager.getAirportPerName(code);

    while(!airportCode && !airportName) {
        cout << "Airport (back to cancel): ";
        getline(cin, code);

        if(code == "back") {
            return nullptr;
        }
        airportCode = manager.getAirportPerCode(code);
        airportName = manager.getAirportPerName(code);

        if (!airportCode and !airportName) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    }

    if (airportCode) return airportCode;
    if (airportName) return airportName;
}


Airline* State::getValidSingleAirline() {
    Airline* airlineCode;
    Airline* airlineName;

    getline(cin, code);
    airlineCode = manager.getAirlinePerCode(code);
    airlineName = manager.getAirlinePerName(code);

    while (!airlineCode && !airlineName) {
        cout << "Airline (back to cancel): ";
        getline(cin, code);

        if (code == "back") {
            return nullptr;
        }

        airlineCode = manager.getAirlinePerCode(code);
        airlineName = manager.getAirlinePerName(code);
        if (!airlineCode and !airlineName) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    }
    if (airlineCode) return airlineCode;
    if (airlineName) return airlineName;
}

string State::getValidSingleCity() {
    string city;
    bool s;
    getline(cin, city);
    s = manager.validateCityName(city);
    while (!s) {
        cout << "City (back to cancel):";

        getline(cin, city);

        if (city == "back") {
            return "";
        }
        s = manager.validateCityName(city);
        if (!s) {
            cout << "City doesn't exist. Try again." << endl;
        }
    }
    return city;
}

string State::getValidSingleCountry() {

    do {
        cout << "Country: (back to cancel)";
        getline(cin, code);

        if (code == "back") return "";

        if (!manager.validateCountryName(code)) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCountryName(code));
    return code;
}


int State::getValidAirportK() {
    do {
        cout << "K (-1 to cancel): ";
        cin >> distance;
        if (distance == -1) return -1;
        if (!manager.getMaxKAirports(distance)) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (!manager.getMaxKAirports(distance));
    return distance;
}

int State::getValidAirlineK() {
    do {
        cout << "K (-1 to cancel): ";
        cin >> distance;
        if (distance == -1) return -1;
        if (!manager.getMaxKAirlines(distance)) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (!manager.getMaxKAirlines(distance));
    return distance;
}

int State::getValidCityK() {
    do {
        cout << "K (-1 to cancel): ";
        cin >> distance;
        if (distance == -1) return -1;
        if (distance < 0 ) {
            cout << "K needs to be > 0. Try again." << endl;
        }

    } while (!manager.getMaxKCities(distance));
    return distance;
}

int State::getValidCountryK(){
    do {
        cout << "K (-1 to cancel): ";
        cin >> distance;

        if (distance == -1) return -1;
        if (distance < 0 ) {
            cout << "K needs to be > 0. Try again." << endl;
        }

    } while (!manager.getMaxKCountries(distance));
    return distance;
}

Airport* State::getValidAirportPerCoordinates() {
    Airport* airport;
    do {
        double latitude = -100, longitude = -200;
        while (latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
            cout << "Latitude: ";
            cin >> latitude ;
            cout << "Longitude: ";
            cin >> longitude;
        }
        airport = manager.getClosestAirport(latitude,longitude);
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}

vector<Airport*> State::getValidAirportsSingleCountry() {
    vector<Airport*> airports;
    getline(cin, name);
    airports = manager.validateCountry(name);

    while (airports.empty()) {
        cout << "Country (back to cancel): ";
        getline(cin, name);

        if (name == "back") return {};

        airports = manager.validateCountry(name);

        if (airports.empty()) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    }

    return airports;
}

map<int,vector<Airport*>> State::getValidAirportsPerCities(){
    map <int,vector<Airport*>> airports;
    int i = 1;
    bool in = true;
    bool first = true;
    while (in) {
        vector<Airport*> aux;
        do {
            if (!first) cout << "City (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }

            if (name == "back") return {};

            aux = manager.validateCity(name);

            if (aux.empty() && !first) {
                cout << "City doesn't exist. Try again." << endl;
            }
            first = false;

        } while (aux.empty());
        airports.insert({i,aux});
        i++;
    }
    return airports;
}

vector<Airport*> State::getValidAirportsSingleCity() {
    vector<Airport*> airports;
    getline(cin, name);
    airports = manager.validateCity(name);

    while (airports.empty())
    {
        cout << "City (back to cancel): ";
        getline(cin, name);

        if (name == "back") return {};
        airports = manager.validateCity(name);

        if (airports.empty()) {
            cout << "City doesn't exist. Try again." << endl;
        }
    }

    return airports;
}

vector<Airport*> State::getValidAirportsPerCity(){
   vector<Airport*> airports;
    vector<Airport*> aux;
    bool in = true;
    bool first = true;
    while (in) {
        do {
            if (!first) cout << "City (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                return airports;
            }

            if (name == "back") return {};

            aux = manager.validateCity(name);

            if ((aux.empty() || !in) && !first) {
                cout << "City doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty() || !in);
        airports.insert(airports.end(),aux.begin(),aux.end());
    }
    return airports;
}

map<int,vector<Airport*>> State::getValidAirportsPerCountries() {
    map <int,vector<Airport*>> airports;
    int i = 1;
    bool first = true;
    bool in = true;
    while (in) {
        vector<Airport*> aux;
        do {
            if (!first) cout << "Country (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }
            if (name == "back") return {};

            aux = manager.validateCountry(name);

            if (aux.empty() && !first) {
                cout << "Country doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty());
       airports.insert({i,aux});
       i++;
    }
    return airports;
}

vector<Airport*> State::getValidAirportsPerCountry() {
   vector<Airport*> airports;
    bool first = true;
    bool in = true;
    while (in) {
        vector<Airport*> aux;
        do {
            if (!first) cout << "Country (ok to confirm, back to cancel): ";

            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }

            if (name == "back") return {};

            aux = manager.validateCountry(name);

            if (aux.empty() && !first) {
                cout << "Country doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty());
        airports.insert(airports.end(),aux.begin(),aux.end());
    }
    return airports;
}

vector<Airport*> State::getAirportsRange(int x) {
    vector<Airport*> airports;
    do {
        double latitude = -100, longitude = -200;
        while (latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
            cout << "Latitude: ";
            cin >> latitude ;
            cout << "Longitude: ";
            cin >> longitude;

            if (latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
                cout << "Invalid numbers!\nLatitude must be between -90 and 90\nLongitude must be between -180 and 180\n" << endl;
            }
        }

        airports = manager.getAirportsPerCoordinatesRange(latitude, longitude, x);
        if (airports.empty()) {
            cout << "There are no airports in that range" << endl;
        }
    } while (airports.empty());
    return airports;
}


vector<Airport*> State::getValidAirports() {
    vector<Airport *> airports;
    bool in = true;
    bool first = true;
    while (in) {
        Airport* aux;
        Airport* aux2;

        do {
            if (!first) cout << "Airport Name or Code (ok to confirm, back to cancel): ";
            getline(cin, name);
            if (name == "ok") {
                in = false;
                break;
            }
            if (name == "back") return {};

             aux = manager.getAirportPerCode(name);
             aux2 = manager.getAirportPerName(name);

            if (!aux && !aux2 && !first) {
                cout << "Airport doesn't exist. Try again." << endl;
            }
            first = false;
        } while (!aux && !aux2);

        if (aux) airports.push_back(aux);
        if (aux2) airports.push_back(aux2);
    }
    return airports;
}

unordered_set<Airline*> State::getValidAirlines() {
    unordered_set<Airline *> airlines;
    Airline* aux;
    Airline* aux2;
    bool first = true;
    bool in = true;
    while (in) {
        do {
            if (!first) cout << "Airline Name or Code (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }

            if (name == "back") return {};
            aux = manager.getAirlinePerCode(name);
            aux2 = manager.getAirlinePerName(name);

            if (!aux && !aux2 && !first) {
                cout << "Airline doesn't exist. Try again." << endl;
            }
            first = false;
        } while (!aux and !aux2);

        if (aux) airlines.insert(aux);
        if (aux2) airlines.insert(aux2);
    }
    return airlines;
}

unordered_set<Airline*> State::getValidAirlinePerCountry() {
    unordered_set<Airline *> airlines;
    bool in = true;
    bool first = true;

    while (in) {
        unordered_set<Airline*> aux;

        do {
            if (!first) cout << "Country Name (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            } else if (name == "back") {
                return {};
            }

            aux = manager.getAirlinesPerCountry(name);

            if (aux.empty() && !first) {
                cout << "Country doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty());

        airlines.insert(aux.begin(), aux.end());
    }

    return airlines;
}
