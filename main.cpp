#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;

    vector<string> visit = {"IAS", "LIS"};
    auto res = m.findShortestPath("ZAH", "PVR");

    auto v2 = m.bfsPathTrip("ZAH", "PVR");

    cout << m.getDistance("ZAH", "PVR");
    cout << endl;
    for (auto v : res) {
        cout << v.getCode() << " ";
    }

    cout << endl;

    for (auto v : v2) {
        cout << v.getCode() << " ";
    }

    int r = m.getDistance("ZAH", "DXB");
    r += m.getDistance("DXB", "SFO");
    r += m.getDistance("SFO", "PVR");

    cout << r;  




    return 0;
}
