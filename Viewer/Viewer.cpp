//
// Created by nelson on 25-12-2023.
//

#include <iomanip>
#include "Viewer.h"

void Viewer::printNumAirportsNumFlights(const int &numAirports, const int &numFlights) {
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

void Viewer::printNumFlightsOutAndAirlines(const string &code, const string &name, const int &numFlights, const int &numAirlines) {
    int space = name.length() > 7 ? name.length() + 2: 7;
    int lenAirportCode = (space - code.length()) / 2;
    int lenFAirportCode = (space - code.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - name.length()) / 2;
    int lenFAirportName = (space - name.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    int lenNumAirlines = (space - to_string(numAirlines).length()) / 2;
    int lenFNumAirlines = (space - to_string(numAirlines).length()) % 2 == 0 ? lenNumAirlines : lenNumAirlines + 1;

    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airport Code    |" << string(lenAirportCode, ' ') << code << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|    Airport Name    |" << string(lenAirportName, ' ') << name << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "| Number of airlines |" << string(lenNumAirlines, ' ') << numAirlines << string(lenFNumAirlines, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;

}

void Viewer::printNumFlightsPerCity(const string &city, const int &numFlights) {
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

void Viewer::printNumFlightsPerAirline(const string &code, const string &name, const int &numFlights) {
    int space = name.length() > to_string(numFlights).length() ? name.length() + 2: to_string((numFlights)).length() + 2;
    int lenAirlineCode = (space - code.length()) / 2;
    int lenFAirlineCode = (space - code.length()) % 2 == 0 ? lenAirlineCode : lenAirlineCode + 1;
    int lenAirlineName = (space - name.length()) / 2;
    int lenFAirportName = (space - name.length()) % 2 == 0 ? lenAirlineName : lenAirlineName + 1;
    int lenNumFlights = (space - to_string(numFlights).length()) / 2;
    int lenFNumFlights = (space - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights + 1;
    cout << "----------------------" << string(space + 1, '-') << endl;
    cout << "|    Airline code    |" << string(lenAirlineCode, ' ') << code << string(lenFAirlineCode, ' ') << '|' << endl;
    cout << "|    Airline name    |" << string(lenAirlineName, ' ') << name << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of flights  |" << string(lenNumFlights, ' ') << numFlights << string(lenFNumFlights, ' ') << '|' << endl;
    cout << "----------------------" << string(space + 1, '-') << endl;
}

void Viewer::printCountriesAirportCanFlyTo(const string &code, const string &name, const int &numCountries) {
    int space = name.length() > 7 ? name.length() + 2: 7;
    int lenAirportCode = (space - code.length()) / 2;
    int lenFAirportCode = (space - code.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - name.length()) / 2;
    int lenFAirportName = (space - name.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
    cout << "|            Airport Code            |" << string(lenAirportCode, ' ') << code << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|            Airport Name            |" << string(lenAirportName, ' ') << name << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of Countries you can fly to |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
}

void Viewer::printCountriesCityCanFlyTo(const string &city, const int &numCountries) {
    int space = city.length() > 7 ? city.length() + 2: 7;
    int lenCity = (space - city.length()) / 2;
    int lenFCity = (space - city.length()) % 2 == 0 ? lenCity : lenFCity + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
    cout << "|                City                |" << string(lenCity, ' ') << city << string(lenFCity, ' ') << '|' << endl;
    cout << "| Number of Countries you can fly to |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "--------------------------------------" << string(space + 1, '-') << endl;
}

void Viewer::printAirportDestinationsDistance1(const string &code, const string &name, const int &numAirports, const int &numCities, const int &numCountries) {
    int space = name.length() > 7 ? name.length() + 2: 7;
    int lenAirportCode = (space - code.length()) / 2;
    int lenFAirportCode = (space - code.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - name.length()) / 2;
    int lenFAirportName = (space - name.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
    cout << "|          Airport Code           |" << string(lenAirportCode, ' ') << code << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|          Airport Name           |" << string(lenAirportName, ' ') << name << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of destination Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of destination Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of destination Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
}
void Viewer::printCityDestinationsDistance1(const string &city, const int &numAirports, const int &numCities, const int &numCountries) {
    int space = city.length() > 7 ? city.length() + 2: 7;
    int lenCity = (space - city.length()) / 2;
    int lenFCity = (space - city.length()) % 2 == 0 ? lenCity : lenCity + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
    cout << "|              City               |" << string(lenCity, ' ') << city << string(lenFCity, ' ') << '|' << endl;
    cout << "| Number of destination Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of destination Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of destination Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
}

void Viewer::printCountryDestinationsDistance1(const string &country, const int &numAirports, const int &numCities, const int &numCountries) {
    int space = country.length() > 7 ? country.length() + 2: 7;
    int lenCountry = (space - country.length()) / 2;
    int lenFCountry = (space - country.length()) % 2 == 0 ? lenCountry : lenCountry + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
    cout << "|             Country             |" << string(lenCountry, ' ') << country << string(lenFCountry, ' ') << '|' << endl;
    cout << "| Number of destination Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of destination Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of destination Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "-----------------------------------" << string(space + 1, '-') << endl;
}

void
Viewer::printAirportDestinations(const string &code, const string &name, const int &numAirports, const int &numCities, const int &numCountries) {
    int space = name.length() > 7 ? name.length() + 2: 7;
    int lenAirportCode = (space - code.length()) / 2;
    int lenFAirportCode = (space - code.length()) % 2 == 0 ? lenAirportCode : lenAirportCode + 1;
    int lenAirportName = (space - name.length()) / 2;
    int lenFAirportName = (space - name.length()) % 2 == 0 ? lenAirportName : lenAirportName + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|         Airport Code          |" << string(lenAirportCode, ' ') << code << string(lenFAirportCode, ' ') << '|' << endl;
    cout << "|         Airport Name          |" << string(lenAirportName, ' ') << name << string(lenFAirportName, ' ') << '|' << endl;
    cout << "| Number of reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}

void Viewer::printCityDestinations(const string &city, const int &numAirports, const int &numCities, const int &numCountries) {
    int space = city.length() > 7 ? city.length() + 2: 7;
    int lenCity = (space - city.length()) / 2;
    int lenFCity = (space - city.length()) % 2 == 0 ? lenCity : lenCity + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|             City              |" << string(lenCity, ' ') << city << string(lenFCity, ' ') << '|' << endl;
    cout << "| Number of reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}

void Viewer::printCountryDestinations(const string &country, const int &numAirports, const int &numCities, const int &numCountries) {
    int space = country.length() > 7 ? country.length() + 2: 7;
    int lenCountry = (space - country.length()) / 2;
    int lenFCountry = (space - country.length()) % 2 == 0 ? lenCountry : lenCountry + 1;
    int lenNumAirports = (space - to_string(numAirports).length()) / 2;
    int lenFNumAirports = (space - to_string(numAirports).length()) % 2 == 0 ? lenNumAirports : lenNumAirports + 1;
    int lenNumCountries = (space - to_string(numCountries).length()) / 2;
    int lenFNumCountries = (space - to_string(numCountries).length()) % 2 == 0 ? lenNumCountries : lenNumCountries + 1;
    int lenNumCities = (space - to_string(numCities).length()) / 2;
    int lenFNumCities = (space - to_string(numCities).length()) % 2 == 0 ? lenNumCities : lenNumCities + 1;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
    cout << "|            Country            |" << string(lenCountry, ' ') << country << string(lenFCountry, ' ') << '|' << endl;
    cout << "| Number of reachable Airports  |" << string(lenNumAirports, ' ') << numAirports << string(lenFNumAirports, ' ') << '|' << endl;
    cout << "| Number of reachable Countries |" << string(lenNumCountries, ' ') << numCountries << string(lenFNumCountries, ' ') << '|' << endl;
    cout << "|  Number of reachable Cities   |" << string(lenNumCities, ' ') << numCities << string(lenFNumCities, ' ') << '|' << endl;
    cout << "---------------------------------" << string(space + 1, '-') << endl;
}

void Viewer::printDiameterPairs(const vector<pair<Airport, Airport>> &result, const int &maxDiameter) {
    int maxNameLength = 0;
    for (auto& elem : result) {
        int maxLength = max(elem.first.getName().length(), elem.second.getName().length());
        if (maxLength > maxNameLength) maxNameLength = maxLength;
    }
    int space = maxNameLength + 8 > 22 ? maxNameLength + 8 : 22;
    int lenSourceAirportsLabel = (space - 15) / 2;
    int lenFSourceAirportsLabel = (space - 15) % 2 == 0 ? lenSourceAirportsLabel : lenSourceAirportsLabel + 1;
    int lenDestAirportsLabel = (space - 21) / 2;
    int lenFDestAirportsLabel = (space - 21) % 2 == 0 ? lenDestAirportsLabel : lenDestAirportsLabel + 1;
    cout << string(space * 2 + 3, '-') << endl;
    cout << '|' << string(lenSourceAirportsLabel, ' ') << "Source Airports" << string (lenFSourceAirportsLabel, ' ') << "| " << string(lenDestAirportsLabel, ' ') << "Destination Airports" << string(lenFDestAirportsLabel, ' ') << '|' << endl;
    cout << string(space * 2 + 3, '-') << endl;
    for (auto& elem : result) {
        cout << "| Code: " << elem.first.getCode() << string(space - 10, ' ') << "| Code: " << elem.second.getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem.first.getName() << string(space - 7 - elem.first.getName().length(), ' ') << "| Name: " << elem.second.getName() << string(space - 7 - elem.second.getName().length(), ' ') << '|' << endl;
        cout << string(space * 2 + 3, '-') << endl;
    }
    cout << "The maximum trip between two airports has " << maxDiameter << " stops." << endl;

}


void Viewer::printAirportGreatestTraffic(const vector<Airport *> &airportsByTraffic, const int &nameSize) {
    int space1 = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirportsLabel = (space1 - 8) / 2;
    int lenFAirportsLabel = (space1 - 8) % 2 == 0 ? lenAirportsLabel : lenAirportsLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenAirportsLabel, ' ') << "Airports" << string (lenFAirportsLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : airportsByTraffic) {
        int numFlights = elem->getNumFlightsOut() + elem->getNumFlightsIn();
        int lenNumFlights = (19 - to_string(numFlights).length()) / 2;
        int lenFNumFlights = (19 - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Code: " << elem->getCode() << string(space1 - 10, ' ') << "|                   |" << endl;
        cout << '|' << string(space1, ' ') << '|' << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space1 - 8 - elem->getName().length(), ' ') <<" |                   |" << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
    }
}

void Viewer::printCityGreatestTraffic(const vector<pair<string, int>> &citiesByTraffic, const int &nameSize) {
    int space1 = nameSize + 8;
    int lenCitiesLabel = (space1 - 6) / 2;
    int lenFCitiesLabel = (space1 - 6) % 2 == 0 ? lenCitiesLabel : lenCitiesLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenCitiesLabel, ' ') << "Cities" << string (lenFCitiesLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : citiesByTraffic) {
        int lenNumFlights = (19 - to_string(elem.second).length()) / 2;
        int lenFNumFlights = (19 - to_string(elem.second).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| City: " << elem.first << string(space1 - 7 - elem.first.length(), ' ') << '|' << string(lenNumFlights, ' ') << elem.second << string (lenFNumFlights, ' ') << '|' << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
    }
}

void Viewer::printCountryGreatestTraffic(const vector<pair<string, int>> &countriesByTraffic, const int &nameSize) {
    int space1 = nameSize + 11;
    int lenCountriesLabel = (space1 - 9) / 2;
    int lenFCountriesLabel = (space1 - 9) % 2 == 0 ? lenCountriesLabel : lenCountriesLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenCountriesLabel, ' ') << "Countries" << string (lenFCountriesLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : countriesByTraffic) {
        int lenNumFlights = (19 - to_string(elem.second).length()) / 2;
        int lenFNumFlights = (19 - to_string(elem.second).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Country: " << elem.first << string(space1 - 10 - elem.first.length(), ' ') << '|' << string(lenNumFlights, ' ') << elem.second << string (lenFNumFlights, ' ') << '|' << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
    }
}

void Viewer::printTopKVector(const vector<pair<pair<string, string>, int>> &airports,const string &label1, const string &label2, const int &nameSize) {
    int space1 = nameSize + 8 > label1.length() + 2 ? nameSize + 8 : label1.length() + 2;
    int lenLabel1 = (space1 - label1.length()) / 2;
    int lenFLabel1 = (space1 - label1.length()) % 2 == 0 ? lenLabel1 : lenLabel1 + 1;
    int space2 = label2.length() + 2 > 7 ? label2.length() + 2 : 7;
    int lenLabel2 = (space2 - label2.length()) / 2;
    int lenFLabel2 = (space2 - label2.length()) % 2 == 0 ? lenLabel2 : lenLabel2 + 1;
    cout << string(space1 + space2 + 2, '-') << endl;
    cout << '|' << string(lenLabel1, ' ') << label1 << string (lenFLabel1, ' ') << '|' << string(lenLabel2, ' ') << label2 << string(lenFLabel2, ' ') << '|' << endl;
    cout << string(space1 + space2 + 3, '-') << endl;
    for (auto& elem : airports) {
        int numFlights = elem.second;
        int lenNum = (space2 - to_string(numFlights).length()) / 2;
        int lenFNum = (space2 - to_string(numFlights).length()) % 2 == 0 ? lenNum : lenNum + 1;
        cout << "| Code: " << elem.first.first << string(space1 - 10, ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << '|' << string(space1, ' ') << '|' << string(lenNum , ' ') << numFlights << string (lenFNum, ' ') << '|' << endl;
        cout << "| Name: " << elem.first.second << string(space1 - 7 - elem.first.second.length(), ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << string(space1 + space2 + 3, '-') << endl;
    }
}

void Viewer::printAirlinesPerAirport(const set<Airline *> &airlines, const int &nameSize) {
    int space = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirlinesLabel = (space - 8) / 2;
    int lenFAirlinesLabel= (space - 8) % 2 == 0 ? lenAirlinesLabel : lenAirlinesLabel+ 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenAirlinesLabel, ' ') << "Airlines" << string(lenFAirlinesLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : airlines) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Viewer::printListAirportsPerCountry(const vector<Airport *> &airports, const int &nameSize, const string &country) {
    int space = nameSize + 8 > 40 ? nameSize + 8 : 40;
    int lenEssentialAirportsLabel = (space - 12 - country.length()) / 2;
    int lenFEssentialAirportsLabel = (space - 12 - country.length()) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Airports in " << country << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : airports) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Viewer::printSearchAirports(const vector<Airport *> &airports, const int &nameSize, const string &airportName) {
    if (airports.empty()) {
        cout << "No airports with the name " << airportName << " were found." << endl;
        return;
    }
    int space = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirportsLabel = (space - 8) / 2;
    int lenFAirportsLabel = (space - 8) % 2 == 0 ? lenAirportsLabel : lenAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenAirportsLabel, ' ') << "Airports" << string(lenFAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : airports) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Viewer::printSearchAirlines(const vector<Airline *> &airlines, const int &nameSize, const string &airlineName) {
    if (airlines.empty()) {
        cout << "No airlines with the name " << airlineName << " were found." << endl;
        return;
    }
    int space = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirlinesLabel = (space - 8) / 2;
    int lenFAirlinesLabel = (space - 8) % 2 == 0 ? lenAirlinesLabel : lenAirlinesLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenAirlinesLabel, ' ') << "AirLines" << string(lenFAirlinesLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : airlines) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Viewer::printAirportInfo(Airport *airport) {
    int nameLength = airport->getName().length();
    int space = nameLength + 8 > 41 ? nameLength + 8 : 41;
    cout << string(space + 2, '-') << endl;
    cout << "| Code: " << airport->getCode() << string(space - 10, ' ') << '|' << endl;
    cout << "| Name: " << airport->getName() << string(space - 7 - nameLength, ' ') << '|' << endl;
    cout << "| City: " << airport->getCity() << string(space - 7 - airport->getCity().length(), ' ') << '|' << endl;
    cout << "| Country: " << airport->getCountry() << string(space - 10 - airport->getCountry().length(), ' ') << '|' << endl;
    cout << "| Coordinates: " << '(' << to_string(airport->getLatitude()) << ", " << to_string(airport->getLongitude()) << ')' << string(space - 18 - to_string(airport->getLatitude()).length() - to_string(airport->getLongitude()).length(), ' ') << '|' << endl;
    cout << "| Number of Departures: " << airport->getNumFlightsOut() << string(space - 23 - to_string(airport->getNumFlightsOut()).length(), ' ') << '|' << endl;
    cout << "| Number of Arrivals: " << airport->getNumFlightsIn() << string(space - 21 - to_string(airport->getNumFlightsIn()).length(), ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
}

void Viewer::printAirlineInfo(Airline *airline) {
    int nameLength = airline->getName().length();
    int space = nameLength + 8 > 27 ? nameLength + 8 : 27;
    cout << string(space + 2, '-') << endl;
    cout << "| Code: " << airline->getCode() << string(space - 10, ' ') << '|' << endl;
    cout << "| Name: " << airline->getName() << string(space - 7 - nameLength, ' ') << '|' << endl;
    cout << "| Callsign: " << airline->getCallsign() << string(space - 11 - airline->getCallsign().length(), ' ') << '|' << endl;
    cout << "| Country: " << airline->getCountry() << string(space - 10 - airline->getCountry().length(), ' ') << '|' << endl;
    cout << "| Number of Flights: " << airline->getNumFlights() << string(space - 20 - to_string(airline->getNumFlights()).length(), ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
}

void Viewer::printAirlineGreatestTraffic(const vector<Airline *> &airlinesByTraffic, const int &nameSize) {
    int space1 = nameSize + 8 > 10 ? nameSize + 8 : 10;
    int lenAirlinesLabel = (space1 - 8) / 2;
    int lenFAirlinesLabel = (space1 - 8) % 2 == 0 ? lenAirlinesLabel : lenAirlinesLabel + 1;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    cout << '|' << string(lenAirlinesLabel, ' ') << "Airlines" << string (lenFAirlinesLabel, ' ') << "| Number of flights |" << endl;
    cout << string(space1 + 2, '-') << "--------------------" << endl;
    for (auto& elem : airlinesByTraffic) {
        int numFlights = elem->getNumFlights();
        int lenNumFlights = (19 - to_string(numFlights).length()) / 2;
        int lenFNumFlights = (19 - to_string(numFlights).length()) % 2 == 0 ? lenNumFlights : lenNumFlights+ 1;
        cout << "| Code: " << elem->getCode() << string(space1 - 10, ' ') << "|                   |" << endl;
        cout << string(space1 + 1, ' ') << '-' << string(lenNumFlights, ' ') << numFlights << string (lenFNumFlights, ' ') << '-' << endl;
        cout << "| Name: " << elem->getName() << string(space1 - 8 - elem->getName().length(), ' ') <<" |                   |" << endl;
        cout << string(space1 + 2, '-') << "--------------------" << endl;
    }
}


void Viewer::printAirportGreatestTrafficBars(const vector<Airport *> &airportsByTraffic, const bool &asc = false) {
    if (!airportsByTraffic.empty()) {
        float size;
        if (!asc) size = airportsByTraffic.front()->getNumFlightsIn() + airportsByTraffic.front()->getNumFlightsOut();
        else size = airportsByTraffic.back()->getNumFlightsIn() + airportsByTraffic.back()->getNumFlightsOut();
        cout << "     |" << endl;
        for (auto& elem : airportsByTraffic) {
            int numFlights = elem->getNumFlightsOut() + elem->getNumFlightsIn();
            int lenBar = (numFlights / size) * 120;
            if (lenBar == 0) {
                cout << "     |" << endl;
                cout << ' ' << elem->getCode() << " |" << endl;
                cout << "     |" << endl;
                cout << "     |" << endl;
            }
            else {
                cout << "     |" << string(lenBar, '-') << endl;
                cout << ' ' << elem->getCode() << " |" << string(lenBar - 1, ' ') << "| " << numFlights << endl;
                cout << "     |" << string(lenBar, '-') << endl;
                cout << "     |" << endl;
            }
        }
    }
}

void Viewer::printAirlineGreatestTrafficBars(const vector<Airline *> &airlinesByTraffic, const bool &asc) {
    if (!airlinesByTraffic.empty()) {
        float size;
        if (!asc) size = airlinesByTraffic.front()->getNumFlights();
        else size = airlinesByTraffic.back()->getNumFlights();
        cout << "     |" << endl;
        for (auto& elem : airlinesByTraffic) {
            int numFlights = elem->getNumFlights();
            int lenBar = (numFlights / size) * 120;
            if (lenBar == 0) {
                cout << "     |" << endl;
                cout << ' ' << elem->getCode() << " |" << endl;
                cout << "     |" << endl;
                cout << "     |" << endl;
            }
            else {
                cout << "     |" << string(lenBar, '-') << endl;
                cout << ' ' << elem->getCode() << " |" << string(lenBar - 1, ' ') << "| " << numFlights << endl;
                cout << "     |" << string(lenBar, '-') << endl;
                cout << "     |" << endl;
            }
        }
    }
}
void Viewer::printCityOrCountryGreatestTrafficBars(const vector<pair<string, int>> &traffic, const int& nameSize, const bool &asc) {
    if (!traffic.empty()) {
        float size;
        if (!asc) size = traffic.front().second;
        else size = traffic.back().second;

        int space = nameSize + 2;
        cout << string(space, ' ') << '|' << endl;
        for (auto& elem : traffic) {
            int numFlights = elem.second;
            int lenBar = (numFlights / size) * 120;
            int lenName = (space - elem.first.length()) / 2;
            int lenFName = (space - elem.first.length()) % 2 == 0 ? lenName : lenName + 1;
            if (lenBar == 0) {
                cout << string(space, ' ') << '|' << endl;
                cout << string(lenName, ' ') << elem.first << string(lenFName, ' ') << '|' << endl;
                cout << string(space, ' ') << '|' << endl;
                cout << string(space, ' ') << '|' << endl;
            }
            else {
                cout << string(space, ' ') << '|' << string(lenBar, '-') << endl;
                cout << string(lenName, ' ') << elem.first << string(lenFName, ' ') << '|' << string(lenBar - 1, ' ') << "| " << numFlights << endl;
                cout << string(space, ' ') << '|' << string(lenBar, '-') << endl;
                cout << string(space, ' ') << '|' << endl;
            }
        }
    }
}

void Viewer::printTopKVectorBars(const vector<pair<pair<string, string>, int>> &airportsOrAirlines, const bool &asc) {
    if (!airportsOrAirlines.empty()) {
        float size;
        if (!asc) size = airportsOrAirlines.front().second;
        else size = airportsOrAirlines.back().second;
        cout << "     |" << endl;
        for (auto& elem : airportsOrAirlines) {
            int numFlights = elem.second;
            int lenBar = (numFlights / size) * 120;
            if (lenBar == 0) {
                cout << "     |" << endl;
                cout << ' ' << elem.first.first << " |" << endl;
                cout << "     |" << endl;
                cout << "     |" << endl;
            }
            else {
                cout << "     |" << string(lenBar, '-') << endl;
                cout << ' ' << elem.first.first << " |" << string(lenBar - 1, ' ') << "| " << numFlights << endl;
                cout << "     |" << string(lenBar, '-') << endl;
                cout << "     |" << endl;
            }
        }
    }
}

void Viewer::printArticulationPoints(const vector<Airport> res, const int &nameSize) {
    int space = nameSize + 8 > 35 ? nameSize + 8 : 35;
    int lenEssentialAirportsLabel = (space - 33) / 2;
    int lenFEssentialAirportsLabel = (space - 33) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Essential Airports to the network" << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : res) {
        cout << "| Code: " << elem.getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem.getName() << string(space - 7 - elem.getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

void Viewer::printTopKVectorBarsRatio(const vector<pair<Airline *, double>> &airlines, const bool &asc) {
    if (!airlines.empty()) {
        float size;
        if (!asc) size = airlines.front().second;
        else size = airlines.back().second;
        cout << "     |" << endl;
        for (auto& elem : airlines) {
            double numFlights = elem.second;
            int lenBar = (numFlights / size) * 120;
            if (lenBar == 0) {
                cout << "     |" << endl;
                cout << ' ' << elem.first->getCode() << " |" << endl;
                cout << "     |" << endl;
                cout << "     |" << endl;
            }
            else {
                cout << "     |" << string(lenBar, '-') << endl;
                cout << fixed << setprecision(2) << ' ' << elem.first->getCode() << " |" << string(lenBar - 1, ' ') << "| " << numFlights << '%' << endl;
                cout << "     |" << string(lenBar, '-') << endl;
                cout << "     |" << endl;
            }
        }
    }
}

void Viewer::printTopKVectorRatio(const vector<pair<Airline *, double>> &airlines, const string &label1, const string &label2, const int &nameSize) {
    int space1 = nameSize + 8 > label1.length() + 2 ? nameSize + 8 : label1.length() + 2;
    int lenLabel1 = (space1 - label1.length()) / 2;
    int lenFLabel1 = (space1 - label1.length()) % 2 == 0 ? lenLabel1 : lenLabel1 + 1;
    int space2 = label2.length() + 2 > 7 ? label2.length() + 2 : 7;
    int lenLabel2 = (space2 - label2.length()) / 2;
    int lenFLabel2 = (space2 - label2.length()) % 2 == 0 ? lenLabel2 : lenLabel2 + 1;
    cout << string(space1 + space2 + 2, '-') << endl;
    cout << '|' << string(lenLabel1, ' ') << label1 << string (lenFLabel1, ' ') << '|' << string(lenLabel2, ' ') << label2 << string(lenFLabel2, ' ') << '|' << endl;
    cout << string(space1 + space2 + 3, '-') << endl;
    for (auto& elem : airlines) {
        double numFlights = elem.second;
        int aux = numFlights >= 10 ? 5 : 4;
        int lenNum = (space2 - to_string(numFlights).length()) / 2;
        int lenFNum = (space2 - to_string(numFlights).length()) % 2 == 0 ? lenNum : lenNum + 1;
        cout << "| Code: " << elem.first->getCode() << string(space1 - 10, ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << fixed << setprecision(2) << '|' << string(space1, ' ') << '|' << string(lenNum , ' ') << numFlights << string (lenFNum, ' ') << '|' << endl;
        cout << "| Name: " << elem.first->getName() << string(space1 - 7 - elem.first->getName().length(), ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << string(space1 + space2 + 3, '-') << endl;
    }
}





