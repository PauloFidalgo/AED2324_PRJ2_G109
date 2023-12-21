//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_AIRLINE_H
#define AED2324_PRJ2_G109_AIRLINE_H
#include <string>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    std::string country;
    int numFlights = 0;

public:
    Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country);
    std::string getName() const;
    void increaseNumFlights();
    int getNumFlights() const;
    std::string getCode() const;
};


#endif //AED2324_PRJ2_G109_AIRLINE_H
