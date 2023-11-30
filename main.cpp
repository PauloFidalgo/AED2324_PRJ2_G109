#include <iostream>
#include "Managers/Manager.h"

int main() {
    Manager manager = Manager();
    for (auto& elem : manager.getAirports()) {
        cout << elem.first << ' ' << elem.second->getName() << endl;
    }
    return 0;
}


//alterar parse das airlines
//criar campo airlines no parser
//a funçao que adiciona a airline, meter pointer em vez de string para uma conexao