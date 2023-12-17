#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;

    auto v = m.scc();
    auto g = m.getG();

    int i = 1;
    for (auto m : v) {
        cout << "SCC " << i++ << " : ";
        for (auto p : m) {
            cout << p.getCode() << " | ";
        }
        cout << endl;
    }
    


    return 0;
}
