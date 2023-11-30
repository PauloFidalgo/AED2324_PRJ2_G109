//
// Created by Paulo Fidalgo on 30/11/2023.
//

#ifndef AED2324_PRJ2_G109_AIRPORT_H
#define AED2324_PRJ2_G109_AIRPORT_H
#include<string>

class Airport {
private:
    std::string code, name, city, country;
    double latitude, longitude;

public:
    Airport(const std::string &code, const std::string &name, const std::string &city, const std::string &country, const double &latitude, const double &longitude);
    bool operator==(const Airport &other) const;
};


#endif //AED2324_PRJ2_G109_AIRPORT_H
