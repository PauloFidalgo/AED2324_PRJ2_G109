//
// Created by nelson on 25-12-2023.
//

#include <iomanip>
#include <algorithm>
#include <valarray>
#include "Viewer.h"
#include <sstream>


/*!
 * @brief Imprime o número de aeroportos e o número de voos em formato tabular.
 * @param numAirports Número de aeroportos.
 * @param numFlights Número de voos.
 * O(1)
 */
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

/*!
 * @brief Imprime o número de voos de saída e o número de companhias aéreas associadas a um aeroporto em formato tabular.
 * @param code Código do aeroporto.
 * @param name Nome do aeroporto.
 * @param numFlights Número de voos de saída.
 * @param numAirlines Número de companhias aéreas associadas ao aeroporto.
 * O(1)
 */
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

/*!
 * @brief Imprime o número de voos por cidade em formato tabular.
 * @param city Nome da cidade.
 * @param numFlights Número de voos.
 * O(1)
 */
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

/*!
 * @brief Imprime o número de voos por companhia aérea em formato tabular.
 * @param code Código da companhia aérea.
 * @param name Nome da companhia aérea.
 * @param numFlights Número de voos.
 * O(1)
 */
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

/*!
 * @brief Imprime os países para os quais um aeroporto pode voar em formato tabular.
 * @param code Código do aeroporto.
 * @param name Nome do aeroporto.
 * @param numCountries Número de países para os quais o aeroporto pode voar.
 * O(1)
 */
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

/*!
 * @brief Imprime os países para os quais uma cidade pode voar em formato tabular.
 * @param city Nome da cidade.
 * @param numCountries Número de países para os quais a cidade pode voar.
 * O(1)
 */
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

/*! @brief Imprime o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um voo direto de um
 * dado aeroporto, em formato tabular.
 *  @param code Código do aeroporto.
 *  @param name Nome do aeorporto.
 *  @param numAirports Número de aeroportos alcançáveis a partir de um voo direto.
 *  @param numCities Número de cidades alcançáveis a partir de um voo direto.
 *  @param numCountries Número de países alcançáveis a partir de um voo direto.
 *  O(1)
 */
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

/*! @brief Imprime o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um voo direto
 * com origem numa dada cidade, em formato tabular.
 *  @param city Nome da cidade.
 *  @param numAirports Número de aeroportos alcançáveis a partir de um voo direto.
 *  @param numCities Número de cidades alcançáveis a partir de um voo direto.
 *  @param numCountries Número de países alcançáveis a partir de um voo direto.
 *  O(1)
 */
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

/*! @brief Imprime o número de destinos (aeroportos, cidades e países) alcançáveis a partir de um voo direto com
 * origem num dado país, em formato tabular.
 *  @param country Nome do país.
 *  @param numAirports Número de aeroportos alcançáveis a partir de um voo direto.
 *  @param numCities Número de cidades alcançáveis a partir de um voo direto.
 *  @param numCountries Número de países alcançáveis a partir de um voo direto.
 *  O(1)
 */
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

/*! @brief Imprime o número total de destinos (aeroportos, cidades e países) alcançáveis a partir de um dado aeroporto,
 * em formato tabular.
 *  @param code Código do aeroporto.
 *  @param name Nome do aeroporto.
 *  @param numAirports Número de aeroportos alcançáveis a partir de um voo direto.
 *  @param numCities Número de cidades alcançáveis a partir de um voo direto.
 *  @param numCountries Número de países alcançáveis a partir de um voo direto.
 *  O(1)
 */
void Viewer::printAirportDestinations(const string &code, const string &name, const int &numAirports, const int &numCities, const int &numCountries) {
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

/*! @brief Imprime o número total de destinos (aeroportos, cidades e países) alcançáveis a partir de uma dada cidade, em formato tabular.
 *  @param city Nome da cidade
 *  @param numAirports Número de aeroportos alcançáveis a partir de um voo direto.
 *  @param numCities Número de cidades alcançáveis a partir de um voo direto.
 *  @param numCountries Número de países alcançáveis a partir de um voo direto.
 *  O(1)
 */
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

/*! @brief Imprime o número total de destinos (aeroportos, cidades e países) alcançáveis a partir de um dado país, em formato tabular.
 *  @param country Nome do país
 *  @param numAirports Número de aeroportos alcançáveis a partir de um voo direto.
 *  @param numCities Número de cidades alcançáveis a partir de um voo direto.
 *  @param numCountries Número de países alcançáveis a partir de um voo direto.
 *  O(1)
 */
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

/*! @brief Imprime os pares de aeroportos origem-destino, cuja viagem entre estes tem um número de escalas igual ao
 * número máximo de escalas que se verifica para qualquer viagem, em formato tabular.
 *  @param result vetor de pares de aeroportos origem-destino.
 *  @param maxDiameter número máximo de escalas que se verifica para qualquer viagem.
 *  O(n)
 */
void Viewer::printDiameterPairs(const vector<pair<Airport *, Airport *>> &result, const int &maxDiameter) {
    int maxNameLength = 0;
    for (auto& elem : result) {
        int maxLength = max(elem.first->getName().length(), elem.second->getName().length());
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
        cout << "| Code: " << elem.first->getCode() << string(space - 10, ' ') << "| Code: " << elem.second->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem.first->getName() << string(space - 7 - elem.first->getName().length(), ' ') << "| Name: " << elem.second->getName() << string(space - 7 - elem.second->getName().length(), ' ') << '|' << endl;
        cout << string(space * 2 + 3, '-') << endl;
    }
    cout << "The maximum trip between two airports has " << maxDiameter << " stops." << endl;

}

/*! @brief Imprime um número pré-definido de aeroportos que apresentam maior ou menor tráfego aéreo, em formato tabular.
 *  @param airportsByTraffic vetor de aeroportos com mais ou menos tráfego aéreo.
 *  @param nameSize tamanho do maior nome de um aeroporto que vai ser impresso.
 *  O(n)
 */
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
/*! @brief Imprime um número pré-definido de países ou cidades e um valor correspondente,
 * por ordem crescente ou decrescente desse valor, em formato tabular.
 *  @param countriesCities vetor de pares com o nome de um país ou cidade e um valor correspondente
 *  @param label1 legenda da primeira coluna da tabela a ser impressa.
 *  @param label2 legenda da segunda coluna da tabela a ser impressa.
 *  @param nameSize tamanho do maior nome de um país ou cidade que vai ser impresso.
 *  O(n)
 */
void Viewer::printCountryCityStats(const vector<pair<string, int>> &countriesCities,const string &label1, const string &label2, const int &nameSize) {
    string label3 = label1 == "Countries" ? "| Country: " : "| City: ";
    int space1 = nameSize + label3.length() > label1.length() + 2 ? nameSize + label3.length() : label1.length() + 2;
    int lenLabel1 = (space1 - label1.length()) / 2;
    int lenFLabel1 = (space1 - label1.length()) % 2 == 0 ? lenLabel1 : lenLabel1 + 1;
    int space2 = label2.length() + 2 > 7 ? label2.length() + 2 : 7;
    int lenLabel2 = (space2 - label2.length()) / 2;
    int lenFLabel2 = (space2 - label2.length()) % 2 == 0 ? lenLabel2 : lenLabel2 + 1;
    cout << string(space1 + space2 + 3, '-') << endl;
    cout << '|' << string(lenLabel1, ' ') << label1 << string (lenFLabel1, ' ') << '|' << string(lenLabel2, ' ') << label2 << string(lenFLabel2, ' ') << '|' << endl;
    cout << string(space1 + space2 + 3, '-') << endl;

    for (auto& elem : countriesCities) {
        int lenNum = (space2 - to_string(elem.second).length()) / 2;
        int lenFNum = (space2 - to_string(elem.second).length()) % 2 == 0 ? lenNum : lenNum + 1;
        cout << label3 << elem.first << string(space1 - (label3.length() - 1) - elem.first.length(), ' ') << '|' << string(lenNum, ' ') << elem.second << string (lenFNum, ' ') << '|' << endl;
        cout << string(space1 + space2 + 3, '-') << endl;
    }
}
/*! @brief Imprime um número pré-definido de aeroportos e um valor correspondente,
 * por ordem crescente ou decrescente desse valor, em formato tabular.
 *  @param airports vetor de pares com um aeroporto e um valor correspondente
 *  @param label1 legenda da primeira coluna da tabela a ser impressa.
 *  @param label2 legenda da segunda coluna da tabela a ser impressa.
 *  @param nameSize tamanho do maior nome de um aeroporto que vai ser impresso.
 *  O(n)
 */
void Viewer::printTopKVector(const vector<pair<Airport *, int>> &airports,const string &label1, const string &label2, const int &nameSize) {
    int space1 = nameSize + 8 > label1.length() + 2 ? nameSize + 8 : label1.length() + 2;
    int lenLabel1 = (space1 - label1.length()) / 2;
    int lenFLabel1 = (space1 - label1.length()) % 2 == 0 ? lenLabel1 : lenLabel1 + 1;
    int space2 = label2.length() + 2 > 7 ? label2.length() + 2 : 7;
    int lenLabel2 = (space2 - label2.length()) / 2;
    int lenFLabel2 = (space2 - label2.length()) % 2 == 0 ? lenLabel2 : lenLabel2 + 1;
    cout << string(space1 + space2 + 3, '-') << endl;
    cout << '|' << string(lenLabel1, ' ') << label1 << string (lenFLabel1, ' ') << '|' << string(lenLabel2, ' ') << label2 << string(lenFLabel2, ' ') << '|' << endl;
    cout << string(space1 + space2 + 3, '-') << endl;
    for (auto& elem : airports) {
        int numFlights = elem.second;
        int lenNum = (space2 - to_string(numFlights).length()) / 2;
        int lenFNum = (space2 - to_string(numFlights).length()) % 2 == 0 ? lenNum : lenNum + 1;
        cout << "| Code: " << elem.first->getCode() << string(space1 - 10, ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << '|' << string(space1, ' ') << '|' << string(lenNum , ' ') << numFlights << string (lenFNum, ' ') << '|' << endl;
        cout << "| Name: " << elem.first->getName() << string(space1 - 7 - elem.first->getName().length(), ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << string(space1 + space2 + 3, '-') << endl;
    }
}
/*! @brief Imprime as companhias aéreas que operam num dado aeroporto, em formato tabular.
 * @param airlines set de companhias que operam no dado aeroporto.
 *  @param nameSize tamanho do maior nome de uma companhia aérea que vai ser impresso.
 *  O(n)
 */
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
/*! @brief Imprime as aeroportos existentes num dado país ou cidade, em formato tabular.
 * @param airports vetor de aeroportos existentes no país ou cidade escolhido.
 *  @param nameSize tamanho do maior nome de aeroporto que vai ser impresso.
 *  @param countryCity nome do país ou cidade escolhidos.
 *  O(n)
 */
void Viewer::printListAirportsPerCountryCity(const vector<Airport *> &airports, const int &nameSize, const string &countryCity) {
    int space = nameSize + 8 > 40 ? nameSize + 8 : 40;
    int lenEssentialAirportsLabel = (space - 12 - countryCity.length()) / 2;
    int lenFEssentialAirportsLabel = (space - 12 - countryCity.length()) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Airports in " << countryCity << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : airports) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

/*!
 * @brief Imprime a lista de companhias aéreas para um determinado país.
 * @param airlines Vetor contendo apontadores para objetos de companhias aéreas.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * @param country Nome do país para o qual listar as companhias aéreas.
 * O(n)
 */
void Viewer::printListAirlinesPerCountry(const unordered_set<Airline *> &airlines, const int &nameSize, const string &country) {
    int space = nameSize + 8 > 40 ? nameSize + 8 : 40;
    int lenEssentialAirportsLabel = (space - 12 - country.length()) / 2;
    int lenFEssentialAirportsLabel = (space - 12 - country.length()) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Airlines in " << country << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : airlines) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

/*!
 * @brief Imprime informações sobre aeroportos com base em um nome de pesquisa.
 * @param airports Vetor contendo apontadores para objetos de aeroportos.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * @param airportName Nome do aeroporto a ser pesquisado.
 * O(n)
 */
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

/*!
 * @brief Imprime informações sobre companhias aéreas com base em um nome de pesquisa.
 * @param airlines Vetor contendo apontadores para objetos de companhias aéreas.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * @param airlineName Nome da companhia aérea a ser pesquisada.
 * O(n)
 */
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

/*!
 * @brief Imprime informações sobre um aeroporto.
 * @param airport Apontador para o objeto de aeroporto.
 * O(1)
 */
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

/*!
 * @brief Imprime informações sobre uma companhia aérea.
 * @param airline apontador para o objeto de companhia aérea.
 * O(1)
 */
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

/*!
 * @brief Imprime as companhias aéreas com maior tráfego.
 * @param airlinesByTraffic Vetor de apontadors para objetos de companhia aérea ordenados por tráfego.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * O(n)
 */
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

/*!
 * @brief Imprime gráficos de barras representando o tráfego dos aeroportos.
 * @param airportsByTraffic Vetor de apontadors para objetos de aeroporto ordenados por tráfego.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
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

/*!
 * @brief Imprime gráficos de barras representando o tráfego das companhias aéreas.
 * @param airlinesByTraffic Vetor de apontadors para objetos de companhia aérea ordenados por tráfego.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
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

/*!
 * @brief Imprime gráficos de barras representando o tráfego de cidades ou países.
 * @param traffic Vetor de pares representando tráfego de cidades ou países.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
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

/*!
 * @brief Imprime gráficos de barras representando o tráfego dos principais elementos em um vetor.
 * @param airports Vetor de pares representando tráfego de aeroportos.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
void Viewer::printTopKVectorBars(const vector<pair<Airport *, int>> &airports, const bool &asc) {
    if (!airports.empty()) {
        float size;
        if (!asc) size = airports.front().second >= 1 ? airports.front().second : 1;
        else size = airports.back().second >= 1 ? airports.back().second : 1;
        cout << "     |" << endl;
        for (auto& elem : airports) {
            int numFlights = elem.second;
            int lenBar = (numFlights / size) * 120;
            if (lenBar == 0) {
                cout << "     |" << endl;
                cout << ' ' << elem.first->getCode() << " |" << endl;
                cout << "     |" << endl;
                cout << "     |" << endl;
            }
            else {
                cout << "     |" << string(lenBar, '-') << endl;
                cout << ' ' << elem.first->getCode() << " |" << string(lenBar - 1, ' ') << "| " << numFlights << endl;
                cout << "     |" << string(lenBar, '-') << endl;
                cout << "     |" << endl;
            }
        }
    }
}

/*!
 * @brief Imprime gráficos de barras representando o tráfego dos principais elementos em um vetor.
 * @param airlines Vetor de pares representando tráfego de companhias aéreas.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
void Viewer::printTopKVectorBars(const vector<pair<Airline *, int>> &airlines, const bool &asc) {
    if (!airlines.empty()) {
        float size;
        if (!asc) size = airlines.front().second >= 1 ? airlines.front().second : 1;
        else size = airlines.back().second >= 1 ? airlines.back().second : 1;
        cout << "     |" << endl;
        for (auto& elem : airlines) {
            int numFlights = elem.second;
            int lenBar = (numFlights / size) * 120;
            if (lenBar == 0) {
                cout << "     |" << endl;
                cout << ' ' << elem.first->getCode() << " |" << endl;
                cout << "     |" << endl;
                cout << "     |" << endl;
            }
            else {
                cout << "     |" << string(lenBar, '-') << endl;
                cout << ' ' << elem.first->getCode() << " |" << string(lenBar - 1, ' ') << "| " << numFlights << endl;
                cout << "     |" << string(lenBar, '-') << endl;
                cout << "     |" << endl;
            }
        }
    }
}

/*!
 * @brief Imprime os pontos de articulação no grafo de aeroportos.
 * @param res Vetor de apontadors para objetos de aeroporto representando os pontos de articulação.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * O(n)
 */
void Viewer::printArticulationPoints(const unordered_set<Airport *> &res, const int &nameSize) {
    int space = nameSize + 8 > 35 ? nameSize + 8 : 35;
    int lenEssentialAirportsLabel = (space - 33) / 2;
    int lenFEssentialAirportsLabel = (space - 33) % 2 == 0 ? lenEssentialAirportsLabel : lenEssentialAirportsLabel + 1;
    cout << string(space + 2, '-') << endl;
    cout << '|' << string(lenEssentialAirportsLabel, ' ') << "Essential Airports to the network" << string(lenFEssentialAirportsLabel, ' ') << '|' << endl;
    cout << string(space + 2, '-') << endl;
    for (auto &elem : res) {
        cout << "| Code: " << elem->getCode() << string(space - 10, ' ') << '|' << endl;
        cout << "| Name: " << elem->getName() << string(space - 7 - elem->getName().length(), ' ') << '|' << endl;
        cout << string(space + 2, '-') << endl;
    }
}

/*!
 * @brief Imprime gráficos de barras representando a proporção do tráfego das companhias aéreas.
 * @param airlines Vetor de pares representando tráfego de companhias aéreas.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
void Viewer::printTopKVectorBarsRatio(const vector<pair<Airline *, double>> &airlines, const bool &asc) {
    if (!airlines.empty()) {
        float size;
        if (!asc) size = airlines.front().second >= 1 ? airlines.front().second : 1;
        else size = airlines.back().second >= 1 ? airlines.back().second : 1;
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

/*!
 * @brief Imprime gráficos de barras representando a proporção do tráfego das companhias aéreas.
 * @param airlines Vetor de pares representando tráfego de companhias aéreas.
 * @param asc Indica se a ordenação é ascendente.
 * O(n)
 */
void Viewer::printTopKVectorRatio(const vector<pair<Airline *, double>> &airlines, const int &nameSize) {
    int space1 = nameSize + 8 > 10 ? nameSize + 8 : 10 + 2;
    int lenLabel1 = (space1 - 8) / 2;
    int lenFLabel1 = (space1 - 8) % 2 == 0 ? lenLabel1 : lenLabel1 + 1;
    cout << string(space1 + 36, '-') << endl;
    cout << '|' << string(lenLabel1, ' ') << "Airlines" << string (lenFLabel1, ' ') << "| Percentage of total flights (%) |" << endl;
    cout << string(space1 + 36, '-') << endl;
    for (auto& elem : airlines) {
        double numFlights = elem.second;
        int aux = numFlights >= 10 ? 5 : 4;
        int lenNum = (33 - aux) / 2;
        int lenFNum = (33 - aux) % 2 == 0 ? lenNum : lenNum + 1;
        cout << "| Code: " << elem.first->getCode() << string(space1 - 10, ' ') << "|                                 |" << endl;
        cout << fixed << setprecision(2) << '|' << string(space1, ' ') << '|' << string(lenNum , ' ') << numFlights << string (lenFNum, ' ') << '|' << endl;
        cout << "| Name: " << elem.first->getName() << string(space1 - 7 - elem.first->getName().length(), ' ') << "|                                 |" << endl;
        cout << string(space1 + 36, '-') << endl;
    }
}

/*!
 * @brief Imprime gráficos de barras representando o tráfego dos principais elementos em um vetor.
 * @param airlines Vetor de pares representando tráfego de companhias aéreas.
 * @param label1 Rótulo para o primeiro conjunto de dados.
 * @param label2 Rótulo para o segundo conjunto de dados.
 * @param nameSize Tamanho do nome a ser considerado ao formatar a saída.
 * O(n)
 */
void Viewer::printTopKVector(const vector<pair<Airline *, int>> &airlines, const string &label1, const string &label2, const int &nameSize) {
    int space1 = nameSize + 8 > label1.length() + 2 ? nameSize + 8 : label1.length() + 2;
    int lenLabel1 = (space1 - label1.length()) / 2;
    int lenFLabel1 = (space1 - label1.length()) % 2 == 0 ? lenLabel1 : lenLabel1 + 1;
    int space2 = label2.length() + 2 > 7 ? label2.length() + 2 : 7;
    int lenLabel2 = (space2 - label2.length()) / 2;
    int lenFLabel2 = (space2 - label2.length()) % 2 == 0 ? lenLabel2 : lenLabel2 + 1;
    cout << string(space1 + space2 + 3, '-') << endl;
    cout << '|' << string(lenLabel1, ' ') << label1 << string (lenFLabel1, ' ') << '|' << string(lenLabel2, ' ') << label2 << string(lenFLabel2, ' ') << '|' << endl;
    cout << string(space1 + space2 + 3, '-') << endl;
    for (auto& elem : airlines) {
        int numFlights = elem.second;
        int lenNum = (space2 - to_string(numFlights).length()) / 2;
        int lenFNum = (space2 - to_string(numFlights).length()) % 2 == 0 ? lenNum : lenNum + 1;
        cout << "| Code: " << elem.first->getCode() << string(space1 - 10, ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << '|' << string(space1, ' ') << '|' << string(lenNum , ' ') << numFlights << string (lenFNum, ' ') << '|' << endl;
        cout << "| Name: " << elem.first->getName() << string(space1 - 7 - elem.first->getName().length(), ' ') << '|' << string(space2, ' ') << '|' << endl;
        cout << string(space1 + space2 + 3, '-') << endl;
    }
}

/*!
 * @brief Imprime as opções de voos disponíveis.
 * @param flights Vetor de vetores representando as opções de voos.
 * O(n * m)
 */
void Viewer::printFlightOptions(const vector<vector<Airport *>> &flights) {
    if (flights.empty()) {
        cout << "There are no flights meeting that criteria" << endl;
        return;
    }

    vector<vector<Airport *>> sortedFlights = flights;
    std::sort(sortedFlights.begin(), sortedFlights.end(), [](const auto& a, const auto& b) {return a.size() < b.size();});
    int numAirports = sortedFlights.back().size();
    int nameSize = 0;

    for (auto &elem : flights) {
        for(auto &airport : elem) {
            if (airport->getName().length() > nameSize) nameSize = airport->getName().length();
        }
    }

    int space1 = nameSize + 8;
    int totalSpace = (space1 + 1) * numAirports - 1;
    int lenLabel = (totalSpace - 26) / 2;
    int lenFLabel = (totalSpace - 26) % 2 == 0 ? lenLabel : lenLabel + 1;
    cout << string(totalSpace + 2, '-') << endl;
    cout << '|' << string(lenLabel, ' ') << "-> -> Flight Options -> ->" << string(lenFLabel, ' ') << '|' << endl;
    cout << string(totalSpace + 2, '-') << endl;

    for (auto &elem : sortedFlights) {
        int aux = numAirports;
        for (auto air : elem) {
            cout << "| Code: " << air->getCode() << string(space1 - 10, ' ');
            aux--;
        }
        while (aux != 0) {
            cout << '|' << string (space1, ' ');
            aux--;
        }
        cout << '|' << endl;
        aux = numAirports;
        for (auto air : elem) {
            cout << "| Name: " << air->getName() << string(space1 - 7 - air->getName().length(), ' ');
            aux--;
        }
        while (aux != 0) {
            cout << '|' << string (space1, ' ');
            aux--;
        }
        cout << '|' << endl;
        cout << string(totalSpace + 2, '-') << endl;
    }
}

/*!
 * @brief Imprime os strongly connected components.
 * @param airports Vetor de vetores representando os airports e cada vetor contem outro vetor com os aeroportos pertencentes a uma SCC
 * O (n * j * k)
 */
void Viewer::printScc(const vector<vector<Airport *>> &airports) {
    if (airports.empty()) {
        cout << "There are no strongly connected components" << endl;
        return;
    }
    int i = 0;
    for (auto &elem : airports) {
        i++;
        int nameSize = 0;
        for (auto& airport : elem) {
            if (airport->getName().length() > nameSize) nameSize = airport->getName().length();
        }
        int rows = sqrt(elem.size());
        int cols = (elem.size() + rows - 1) / rows;
        int spaceBox = nameSize + 8 > 31 + to_string(i).length() ? nameSize + 8 : 31 + to_string(i).length();
        int totalSpace = (spaceBox + 1) * cols - 1;
        int lenLabel = (totalSpace - 29 - to_string(i).length()) / 2;
        int lenFLabel = (totalSpace - 29 - to_string(i).length()) % 2 == 0 ? lenLabel : lenLabel + 1;
        cout << string(totalSpace + 2, '-') << endl;
        cout << '|' << string(lenLabel, ' ') << "Strongly Connected Component " << i << string(lenFLabel, ' ') << '|' << endl;
        cout << string(totalSpace + 2, '-') << endl;
        int it = 0;
        for (int j = 0; j < rows; j++) {
            ostringstream os1;
            ostringstream os2;
            for (int k = 0; k < cols; k++) {
                if (it != elem.size()) {
                    os1 << "| Code: " << elem[it]->getCode() << string(spaceBox - 10, ' ');
                    os2 << "| Name: " << elem[it]->getName() << string(spaceBox - 7 - elem[it]->getName().length(), ' ');
                    it++;
                }
                else {
                    os1 << '|' << string (spaceBox, ' ');
                    os2 << '|' << string (spaceBox, ' ');
                }
            }
            os1 << '|' << endl;
            os2 << '|' << endl;
            cout << os1.str();
            cout << os2.str();
            cout << string(totalSpace + 2, '-') << endl;
        }
    }
}
