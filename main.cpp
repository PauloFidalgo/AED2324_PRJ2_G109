#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;

    auto v = m.pathMaximumConnectionFlights("OPO", "DUB", 4);
    int i = 1;

    for (auto &n : v) {
        cout << "Path " << i << ": ";
        for (auto &t : n) {
            cout << t.getCode() << " ";
        }
        cout << endl;
        i++;
    }

    return 0;
}
