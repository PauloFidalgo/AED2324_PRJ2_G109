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

Airport* State::getValidAirport() {
    Airport* airportCode;
    Airport* airportName;
    do {
        cout << "Airport: ";
        cin >> code;
        if(code == "done"){
            return nullptr;
        }
        airportCode = manager.getAirportPerCode(code);
        airportName = manager.getAirportPerName(code);
        if (!airportCode and !airportName) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!!airportCode and !airportName);
    return (airportCode) ? airportCode : airportName;
}

Airline* State::getValidAirline() {
    Airline* airlineCode;
    Airline* airlineName;
    do {
        cout << "Airline: ";
        cin >> code;
        if(code == "done"){
            return nullptr;
        }
        airlineCode = manager.getAirlinePerCode(code);
        airlineName = manager.getAirlinePerName(code);
        if (!airlineCode and !airlineName) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (airlineCode != nullptr and airlineName == nullptr);
    return (airlineCode) ? airlineCode : airlineName;
}

string State::getValidCity() {
    string city;
    do {
        cout << "City: ";
        cin >> city;

        if (!manager.validateCityName(city)) {
            cout << "City doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCityName(city));
    return city;
}

string State::getValidCountry() {

    do {
        cout << "Country: ";
        cin >> code;
        if(code == "done"){
            return "";
        }
        if (!manager.validateCountryName(code)) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCountryName(code));
    return code;
}

int State::getValidAirportK() {
    do {
        cout << "K : ";
        cin >> distance;
        if (distance < 0 or distance > manager.getAirports().size()) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (distance < 0 or distance > manager.getAirports().size());
    return distance;
}

int State::getValidAirlineK() {
    do {
        cout << "K : ";
        cin >> distance;
        if (distance < 0 or distance > manager.getAirlines().size()) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (distance < 0 or distance > manager.getAirlines().size());
    return distance;
}

int State::getValidCityK() {
    do {
        cout << "K : ";
        cin >> distance;
    /*    if (distance < 0 or distance > manager.getairportsperc().size()) {
            cout << "K doesn't exist. Try again." << endl;
        }
        */
    } while (distance < 0 or distance > manager.getAirports().size());
    return distance;
}

int State::getValidCountryK(){
    do {
        cout << "K : ";
        cin >> distance;
        /*
            if (distance < 0 or distance > manager.getCountries().size()) {
                cout << "K doesn't exist. Try again." << endl;
            }
            */
    } while (distance < 0 or distance > manager.getAirports().size());
    return distance;
}

Airport* State::getValidAirportPerCoordinates(){
    Airport* airport;
    double latitude, longitude;
    do {
        cout << "Latitude: ";
        cin >> latitude ;
        cout << endl;
        cout << "Longitude: ";
        cin >> longitude;
        airport = manager.getClosestAirport(latitude,longitude);
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}

map<int,vector<Airport*>> State::getValidAirportsPerCities(){
    map <int,vector<Airport*>> airports;
    int i = 1;
    bool in = true;
    while (in) {
        vector<Airport*> aux;
        do {
            cout << "City( ok to confirm ): ";
            cin >> name;
            if (code == "ok") {
                in = false;
                break;
            }
            aux = manager.validateCity(name);
            if (aux.empty()) {
                cout << "City doesn't exist. Try again." << endl;
            }
        } while (aux.empty());
        airports.insert({i,aux});
        i++;
    }
    return airports;
}

vector<Airport*> State::getValidAirportsPerCity(){
   vector<Airport*> airports;
    vector<Airport*> aux;
    bool in = true;
    while (in) {
        do {
            cout << "City( ok to confirm ): ";
            cin >> name;
            if (name == "ok") {
                return airports;
            }
            aux = manager.validateCity(name);
            if (aux.empty() or in == false) {
                cout << "City doesn't exist. Try again." << endl;
            }
        } while (aux.empty() or in == false);
        airports.insert(airports.end(),aux.begin(),aux.end());
    }
    return airports;
}

map<int,vector<Airport*>> State::getValidAirportsPerCountries() {
    map <int,vector<Airport*>> airports;
    int i = 1;
    bool in = true;
    while (in) {
        vector<Airport*> aux;
        do {
            cout << "Country( ok to confirm ): ";
            cin >> name;
            if (name == "ok") {
                in = false;
                break;
            }
            aux = manager.validateCountry(name);
            if (aux.empty()) {
                cout << "Country doesn't exist. Try again." << endl;
            }
        } while (aux.empty());
       airports.insert({i,aux});
       i++;
    }
    return airports;
}

vector<Airport*> State::getValidAirportsPerCountry() {
   vector<Airport*> airports;
    bool in = true;
    while (in) {
        vector<Airport*> aux;
        do {
            cout << "Country( ok to confirm ): ";
            cin >> name;
            if (name == "ok") {
                in = false;
                break;
            }
            aux = manager.validateCountry(name);
            if (aux.empty()) {
                cout << "Country doesn't exist. Try again." << endl;
            }
        } while (aux.empty());
        airports.insert(airports.end(),aux.begin(),aux.end());
    }
    return airports;
}

vector<Airport*> State::getAirportsRange(int x){
    vector<Airport*> airports;
    double longitude, latitude;
    do {
        cout << "Latitude: ";
        cin >> latitude ;
        cout << endl;
        cout << "Longitude: ";
        cin >> longitude;

        airports = manager.getAirportsPerCoordinatesRange(latitude, longitude, x);
        if (airports.empty()) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (airports.empty());
    return airports;
}


vector<Airport*> State::getValidAirports() {
    vector<Airport *> airports;
    bool in = true;
    while (in) {
        Airport* aux;
        Airport* aux2;

        do {
            cout << "Airport ( ok to confirm ): ";
            cin >> name;
            if (name == "ok") {
                in = false;
                break;
            }

             aux = manager.getAirportPerCode(code);
             aux2 = manager.getAirportPerName(code);

            if (!aux and !aux2) {
                cout << "Airport doesn't exist. Try again." << endl;
            }
        } while (!aux and !aux2);

        airports.push_back((aux) ? aux : aux2);
    }
    return airports;
}

unordered_set<Airline*> State::getValidAirlines() {
    unordered_set<Airline *> airlines;
    bool in = true;
    while (in) {
        Airline* aux;
        Airline* aux2;

        do {
            cout << "Airline ( ok to confirm ): ";
            cin >> name;
            if (name == "ok") {
                in = false;
                break;
            }

            aux = manager.getAirlinePerCode(code);
            aux2 = manager.getAirlinePerName(code);

            if (!aux and !aux2) {
                cout << "Airline doesn't exist. Try again." << endl;
            }
        } while (!aux and !aux2);

        airlines.insert((aux) ? aux : aux2);
    }
    return airlines;
}

unordered_set<Airline*> State::getValidAirlinePerCountry() {
    unordered_set<Airline *> airlines;
    bool in = true;
    while (in) {
        unordered_set<Airline*> aux;


        do {
            cout << "Country ( ok to confirm ): ";
            cin >> name;
            if (name == "ok") {
                in = false;
                break;
            }

            aux = manager.getAirlinesPerCountry(code);

            if (aux.empty()) {
                cout << "Airline doesn't exist. Try again." << endl;
            }
        } while (aux.empty());
        airlines.insert(aux.begin(),aux.end());
    }
    return airlines;
}