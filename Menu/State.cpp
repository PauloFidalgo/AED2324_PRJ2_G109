#include "State.h"
#include "BarsState.h"
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


/*!
 * @brief Obtém um aeroporto válido com base no código ou nome.
 * @return Apontador para o aeroporto válido ou nullptr se cancelado.
 * O(n)
 */
Airport* State::getValidSingleAirport() {
    Airport* airportCode = nullptr;
    Airport* airportName = nullptr;
    cin.ignore();
    cout << endl;

    while(!airportCode && !airportName) {
        cin.clear();
        cout << "Airport (back to cancel): ";
        getline(cin, code);

        if(code == "back") {
            return nullptr;
        }
        airportCode = manager.getAirportPerCode(code);         //O(n)
        airportName = manager.getAirportPerName(code);   //O(n)

        if (!airportCode and !airportName) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    }

    if (airportCode) return airportCode;
    if (airportName) return airportName;
}


/*!
 * @brief Obtém uma companhia aérea válida com base no código ou nome.
 * @return Apontador para a companhia aérea válida ou nullptr se cancelado.
 * O(n)
 */
Airline* State::getValidSingleAirline() {
    Airline* airlineCode = nullptr;
    Airline* airlineName = nullptr;
    cin.ignore();
    cin.clear();
    cout << endl;

    while (!airlineCode && !airlineName) {
        cout << "Airline (back to cancel): ";
        getline(cin, code);

        if (code == "back") {
            return nullptr;
        }

        airlineCode = manager.getAirlinePerCode(code); //O(n)
        airlineName = manager.getAirlinePerName(code); //O(n)
        if (!airlineCode and !airlineName) {
            cout << "Airline doesn't exist. Try again." << endl;
            cin.ignore();
            cin.clear();
        }
    }
    if (airlineCode) return airlineCode;
    if (airlineName) return airlineName;
}

/*!
 * @brief Obtém um nome de cidade válido.
 * @return Nome de cidade válido ou string vazia se cancelado.
 * O(n)
 */
string State::getValidSingleCity() {
    string city;
    bool s = false;
    cin.ignore();
    cout << endl;

    while (!s) {
        cin.clear();
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

/*!
 * @brief Obtém um nome de país válido.
 * @return Nome de país válido ou string vazia se cancelado.
 * O(n)
 */
string State::getValidSingleCountry() {
    cout << endl;
    cin.ignore();

    while(!manager.validateCountryName(code)){
        cin.clear();
        cout << "Country: (back to cancel)";
        getline(cin, code);

        if (code == "back") return "";

        if (!manager.validateCountryName(code)) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    }
    return code;
}

/*!
 * @brief Obtém um valor válido para K relacionado a aeroportos.
 * @return Valor de K válido ou -1 se cancelado.
 * O(1)
 */
int State::getValidAirportK() {
    cin.ignore();
    cout << endl;

    do {
        bool s = false;
        while (!s) {
            cin.clear();
            cout << "K (-1 to cancel): ";
            getline(cin, userInputStr);
            try {
                distance = stoi(userInputStr);
                s = true;
            }
            catch (exception &e) {
                cin.clear();
            }
        }

        if (distance == -1) return -1;

        if (!manager.getMaxKAirports(distance)) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (!manager.getMaxKAirports(distance));
    return distance;
}

/*!
 * @brief Obtém um valor válido para K relacionado a companhias aéreas.
 * @return Valor de K válido ou -1 se cancelado.
 * O(1)
 */
int State::getValidAirlineK() {
    cin.ignore();
    cout << endl;

    do {
        bool s = false;

        while (!s) {
            cin.clear();
            cout << "K (-1 to cancel): ";
            getline(cin, userInputStr);
            try {
                distance = stoi(userInputStr);
                s = true;
            }
            catch (exception &e) {
                cin.clear();
            }
        }

        if (distance == -1) return -1;
        if (!manager.getMaxKAirlines(distance)) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (!manager.getMaxKAirlines(distance));
    return distance;
}

/*!
 * @brief Obtém um valor válido para K relacionado a cidades.
 * @return Valor de K válido ou -1 se cancelado.
 * O(1)
 */
int State::getValidCityK() {
    cin.ignore();
    cout << endl;

    do {
        bool s = false;

        while (!s) {
            cin.clear();
            cout << "K (-1 to cancel): ";
            getline(cin, userInputStr);
            try {
                distance = stoi(userInputStr);
                s = true;
            }
            catch (exception &e) {
                ;
                cin.clear();
            }
        }

        if (distance == -1) return -1;
        if (!manager.getMaxKCities(distance)) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (!manager.getMaxKCities(distance));
    return distance;
}

/*!
 * @brief Obtém um valor válido para K relacionado a países.
 * @return Valor de K válido ou -1 se cancelado.
 * O(n)
 */
int State::getValidCountryK(){
    cin.ignore();
    cout << endl;

    do {
        bool s = false;

        while (!s) {
            cin.clear();
            cout << "K (-1 to cancel): ";
            getline(cin, userInputStr);
            try {
                distance = stoi(userInputStr);
                s = true;
            }
            catch (exception &e) {
                ;
                cin.clear();
            }
        }

        if (distance == -1) return -1;
        if (!manager.getMaxKCountries(distance)) {
            cout << "K doesn't exist. Try again." << endl;
        }
    } while (!manager.getMaxKCountries(distance));
    return distance;
}

/*!
 * @brief Obtém um aeroporto com base em coordenadas.
 * @return Apontador para o aeroporto mais próximo válido.
 * O(|V|)
 */
Airport* State::getValidAirportPerCoordinates() {
    Airport* airport = nullptr;
    cin.ignore();
    cout << endl;

    do {
        double latitude = -100, longitude = -200;
        while (latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
            cout << "Latitude: ";
            bool s = false;

            while (!s) {
                cin.clear();
                getline(cin, userInputStr);
                try {
                    latitude = stoi(userInputStr);
                    s = true;
                }
                catch (exception &e) {
                    cin.clear();
                }
            }
            s = false;
            cout << "Longitude: ";
            while (!s) {
                cin.clear();
                getline(cin, userInputStr);
                try {
                    longitude = stoi(userInputStr);
                    s = true;
                }
                catch (exception &e) {
                    cin.clear();
                }
            }
        }
        airport = manager.getClosestAirport(latitude,longitude); // O(|V|)
        if (!airport) {
            cout << "Airport doesn't exist. Try again." << endl;
        }
    } while (!airport);
    return airport;
}

/*!
 * @brief Obtém uma lista de aeroportos de um país.
 * @return Vetor de aeroportos válidos ou vetor vazio caso seja cancelado
 * O(n * k)
 */
vector<Airport*> State::getValidAirportsSingleCountry() {
    vector<Airport*> airports;
    cin.ignore();
    cout << endl;

    while (airports.empty()) {
        cin.clear();
        cout << "Country (back to cancel): ";
        getline(cin, name);

        if (name == "back") return {};

        airports = manager.getAirportsPerCountry(name); //O(n * k)

        if (airports.empty()) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    }

    return airports;
}

/*!
 * @brief Obtém um mapa de aeroportos por cidades.
 * @return Mapa de inteiro (correspondente á ordem de visita) para vetores de aeroportos, ou mapa vazio casa seja cancelado
 * O(n)
 */
map<int,vector<Airport*>> State::getValidAirportsPerCities(){
    map <int,vector<Airport*>> airports;
    int i = 1;
    bool in = true;
    bool first = true;
    cout << endl;

    while (in) {
        vector<Airport*> aux;
        do {
            cin.clear();
            if (!first) cout << "City (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }

            if (name == "back") return {};

            aux = manager.getAirportsPerCity(name); // O(n)

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

/*!
 * @brief Obtém uma lista de aeroportos de uma cidade.
 * @return Vetor de aeroportos válidos ou vetor vazio se for cancelado
 * O(n)
 */
vector<Airport*> State::getValidAirportsSingleCity() {
    vector<Airport*> airports;
    cin.ignore();
    cout << endl;

    while (airports.empty())
    {
        cin.clear();
        cout << "City (back to cancel): ";
        getline(cin, name);

        if (name == "back") return {};
        airports = manager.getAirportsPerCity(name); //O(n)

        if (airports.empty()) {
            cout << "City doesn't exist. Try again." << endl;
        }
    }

    return airports;
}

/*!
 * @brief Obtém uma lista de aeroportos de uma ou mais cidades.
 * @return Vetor de aeroportos válidos ou vetor vazio se for cancelado
 * O(n*m) sendo n o numero de imput do utilizador e m o numero de aeroportos da cidade que o utilizador escolheu
 */
vector<Airport*> State::getValidAirportsPerCity(){
    vector<Airport*> airports;
    vector<Airport*> aux;
    bool in = true;
    bool first = true;
    cout << endl;

    while (in) {
        do {
            cin.clear();
            if (!first) cout << "City (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                return airports;
            }

            if (name == "back") return {};

            aux = manager.getAirportsPerCity(name); // O(n)

            if ((aux.empty() || !in) && !first) {
                cout << "City doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty() || !in);

        airports.insert(airports.end(),aux.begin(),aux.end()); // O(1)
    }
    return airports;
}

/*!
 * @brief Obtém uma lista de aeroportos de um ou mais países.
 * @return Mapa de inteiro, correspondente à ordem de visita para vetores de aeroportos ou mapa vazio caso seja cancelado
 * O(n * k)
 */
map<int,vector<Airport*>> State::getValidAirportsPerCountries() {
    map <int,vector<Airport*>> airports;
    int i = 1;
    bool first = true;
    bool in = true;
    cout << endl;

    while (in) {
        vector<Airport*> aux;
        do {
            cin.clear();
            if (!first) cout << "Country (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }
            if (name == "back") return {};

            aux = manager.getAirportsPerCountry(name); //O(n * k)

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

/*!
 * @brief Obtém uma lista de aeroportos de um país.
 * @return Vetor de aeroportos válidos ou vetor vazio se cancelado
 *  O(n * k)
 */
vector<Airport*> State::getValidAirportsPerCountry() {
   vector<Airport*> airports;
    bool first = true;
    bool in = true;
    cout << endl;

    while (in) {
        vector<Airport*> aux;
        do {
            cin.clear();
            if (!first) cout << "Country (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }

            if (name == "back") return {};

            aux = manager.getAirportsPerCountry(name); // O(n * k)

            if (aux.empty() && !first) {
                cout << "Country doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty());
        airports.insert(airports.end(),aux.begin(),aux.end());
    }
    return airports;
}

/*!
 * @brief Obtém uma lista de aeroportos num determinado range centrado num ponto.
 * @param x Valor do range.
 * @return Vetor de aeroportos válidos.
 * O(|V|)
 */
vector<Airport*> State::getAirportsRange(int x) {
    vector<Airport*> airports;
    cin.ignore();
    cout << endl;

    do {
        cin.clear();
        double latitude = -100, longitude = -200;
        while (latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
            cout << "Latitude: ";
            bool s = false;

            while (!s) {
                cin.clear();
                getline(cin, userInputStr);
                try {
                    latitude = stoi(userInputStr);
                    s = true;
                }
                catch (exception &e) {
                    cin.clear();
                }
            }
            s = false;
            cout << "Longitude: ";
            while (!s) {
                cin.clear();
                getline(cin, userInputStr);
                try {
                    longitude = stoi(userInputStr);
                    s = true;
                }
                catch (exception &e) {
                    cin.clear();
                }
            }
        }

        airports = manager.getAirportsPerCoordinatesRange(latitude, longitude, x); // O(|V|)
        if (airports.empty()) {
            cout << "There are no airports in that range" << endl;
        }
    } while (airports.empty());
    return airports;
}

/*!
 * @brief Obtém uma lista de aeroportos com base no nome ou código.
 * @return Vetor de aeroportos válidos ou vetor vazio se cancelado
 * O(n)
 */
vector<Airport*> State::getValidAirports() {
    vector<Airport *> airports;
    bool in = true;
    bool first = true;
    cin.ignore();
    cout << endl;

    while (in) {
        Airport* aux = nullptr;
        Airport* aux2 = nullptr;

        do {
            cin.clear();
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

/*!
 * @brief Obtém um conjunto de companhias aéreas com base no nome ou código.
 * @return Conjunto de companhias aéreas válidas ou unordered_set vazio se cancelado
 * O(n)
 */
unordered_set<Airline*> State::getValidAirlines() {
    unordered_set<Airline *> airlines;
    Airline* aux = nullptr;
    Airline* aux2 = nullptr;
    bool first = true;
    bool in = true;
    cin.ignore();
    cout << endl;

    while (in) {
        do {
            cin.clear();
            if (!first) cout << "Airline Name or Code (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            }

            if (name == "back") return {};
            aux = manager.getAirlinePerCode(name); // O(n)
            aux2 = manager.getAirlinePerName(name); // O(n)

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

/*!
 * @brief Obtém um conjunto de companhias aéreas de um país.
 * @return Conjunto de companhias aéreas válidas ou unordered_set vazio se cancelado
 * O(n), sendo que o numero de inputs do utilizador é relativamente baixo senão era O (n *k ) sendo k o numero de inputs do utilizador
 */
unordered_set<Airline*> State::getValidAirlinePerCountry() {
    unordered_set<Airline *> airlines;
    bool in = true;
    bool first = true;
    cin.ignore();
    cout << endl;

    while (in) {
        unordered_set<Airline*> aux;

        do {
            cin.clear();
            if (!first) cout << "Country Name (ok to confirm, back to cancel): ";
            getline(cin, name);

            if (name == "ok") {
                in = false;
                break;
            } else if (name == "back") {
                return {};
            }

            aux = manager.getAirlinesPerCountry(name); // O(n)

            if (aux.empty() && !first) {
                cout << "Country doesn't exist. Try again." << endl;
            }
            first = false;
        } while (aux.empty());

        airlines.insert(aux.begin(), aux.end());
    }

    return airlines;
}

/*!
 * @brief Obtém um conjunto de companhias aéreas de um país.
 * @return Conjunto de companhias aéreas válidas ou unordered_set vazio se cancelado
 * O(n)
 */
unordered_set<Airline*> State::getValidAirlineSingleCountry() {
    unordered_set<Airline *> airlines;
    bool first = true;
    cout << endl;

        do {
            cin.clear();
            if (!first) cout << "Country Name (back to cancel): ";
            getline(cin, name);

            if (name == "back") {
                return {};
            }

            airlines = manager.getAirlinesPerCountry(name); //O(n)

            if (airlines.empty() && !first) {
                cout << "Country doesn't exist. Try again." << endl;
            }
            first = false;
        } while (airlines.empty());

    return airlines;
}

/*!
 * @brief Obtém um conjunto de cidades de um país.
 * @return Conjunto de cidades válidas ou unordered_set vazio se cancelado
 *O(n)
 */
unordered_set<string> State::getValidCitiesSingleCountry() {
    unordered_set<string> cities;
    cin.ignore();
    cout << endl;

    while (cities.empty()) {
        cin.clear();
        cout << "Country (back to cancel): ";
        getline(cin, name);

        if (name == "back") return {};

        cities = manager.getCitiesPerCountry(name); //O(n)

        if (cities.empty()) {
            cout << "Country doesn't exist. Try again." << endl;
        }
    }

    return cities;
}

/*!
 * @brief Manipula a interface de barras.
 * @return true se a interface de barras deve ser usada, false caso contrário.
 */
bool State::bars() {
    barsState.displayMenu();
    barsState.handleInput();
    auto bars = barsState.shouldUseGraphicBar();
    return bars;
}