#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;

    vector<string> visit = {"IAS", "LIS"};
    vector<Airport> res = m.sheduleTrip("OPO", "CRA", visit);

    for (auto v : res) {
        cout << v.getCode() << " ";
    }




    return 0;
}
