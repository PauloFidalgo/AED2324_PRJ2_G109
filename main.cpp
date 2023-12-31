#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
   Manager m;

   auto v = m.getAirportPerCode("OPO");
   auto d = m.getAirportPerCode("MAG");

   auto i = m.findAllEquivalentPaths(v, d);

   for (auto &e : i) {
       for (auto air : e.airports) {
           cout << air->getCode() << " ";
       }
       cout << e.airlines.size();
       cout << endl;
   }

}
