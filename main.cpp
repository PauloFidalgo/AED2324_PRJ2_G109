#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;

        int i = m.getNumStops(m.getAirportPerCode("OPO"), m.getAirportPerCode("DMK"));

    cout << i << endl;

    //auto pt = m.bfsMinConnections(m.getAirportPerCode("MAG"), m.getAirportPerCode("DMK"));

    auto res = m.scheduleTripMinConnection(m.getAirportPerCode("OPO"), m.getAirportPerCode("FAO"), {m.getAirportPerCode("DUB"), m.getAirportPerCode("MEX"), m.getAirportPerCode("LIS")});

    for (auto v : res) {
        cout << "Path : ";
        for (auto p : v) {
            cout << p->getCode() << " ";
        }
        cout << endl;
    }

    return 0;
}
