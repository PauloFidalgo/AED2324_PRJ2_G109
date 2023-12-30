#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
   Manager m;


   auto  p = m.cc();

   for (auto h : p) {
       for (auto i : h) {
           cout << i->getCode() << " ";
       }
       cout << endl;
   }

   cout << "------------" << endl;

   p = m.scc();

    for (auto h : p) {
        for (auto i : h) {
            cout << i->getCode() << " ";
        }
        cout << endl;
    }
    return 0;
}
