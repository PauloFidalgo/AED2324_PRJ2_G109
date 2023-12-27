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

Airport* State::getValidAirportCode() {
    Airport* airport;
    do {
        cout << "Airport code: ";
        cin >> code;
        airport = manager.getAirportPerCode(code);
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}
Airport* State::getValidAirportName() {
    Airport* airport;
    do {
        cout << "Airport Name: ";
        cin >> name;
        airport = manager.getAirportPerName(name);
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}

Airline* State::getValidAirlineCode() {
    Airline* airline;
    do {
        cout << "Airline code: ";
        cin >> code;
        airline = manager.getAirlinePerCode(code);
        if (!airline) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (!airline);
    return airline;
}

Airline* State::getValidAirlineName() {
    Airline* airline;
    do {
        cout << "Airline code: ";
        cin >> name;
        airline = manager.getAirlinePerCode(name);
        if (!airline) {
            cout << "Airline doesn't exist. Try again." << endl;
        }
    } while (!airline);
    return airline;
}

string* State::getValidCity() {

    do {
        cout << "City: ";
        cin >> code;
        if (!manager.validateCityName(code)) {
            cout << "City doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCityName(code));
    return &code;
}

string* State::getValidCountry() {

    do {
        cout << "Country: ";
        cin >> code;
        if (!manager.validateCountryName(code)) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (!manager.validateCountryName(code));
    return &code;
}

int *State::getValidAirportK() {
    do {
        cout << "K : ";
        cin >> distance;
        if (distance < 0 or distance > manager.getAirports().size()) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (distance < 0 or distance > manager.getAirports().size());
    return &distance;
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

vector<Airport*> State::getValidAirportsPerCity(){
    vector<Airport*> airports;

    do {
        cout << "City: ";
        cin >> name;
        airports = manager.validateCity(name);
        if (airports.empty()) {
            cout << "City doesn't exist. Try again." << endl;
        }
    } while (airports.empty());
    return airports;
}

vector<Airport*> State::getValidAirportsPerCountry(){
    vector<Airport*> airports;

    do {
        cout << "Country: ";
        cin >> name;
        airports = manager.validateCountry(name);
        if (airports.empty()) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    } while (airports.empty());
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

        airports = manager.getAiportsPerCoordinatesRange(latitude,longitude,x);
        if (airports.empty()) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (airports.empty());
    return airports;
}