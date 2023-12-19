#include <iostream>
#include <string>
#include "Menu/MainMenuState.h"
#include "Menu/MenuManager.h"
#include "Managers/Manager.h"

int main() {
    Manager m;


    vector<string> c = {"CRL", "ERF", "POR"};
    auto v = m.sheduleTripMinConnection("OPO", "DUB", c);

    for (auto &r : v) {
        cout << r.getCode() << " ";
    }

    cout << endl;

    int i = m.getDistance("OPO", "CRL");
    i += m.getDistance("CRL", "MAN");
    i += m.getDistance("MAN", "IOM");
    i += m.getDistance("IOM", "LGW");
    i += m.getDistance("LGW", "ERF");
    i += m.getDistance("ERF", "GOT");
    i += m.getDistance("GOT", "ARN");
    i += m.getDistance("ARN", "POR");
    i += m.getDistance("POR", "DUB");

    cout << i << endl;

    int j = m.getDistance("OPO", "CRL");
    j += m.getDistance("CRL", "FUE");
    j += m.getDistance("FUE", "ERF");
    j += m.getDistance("ERF", "LGW");
    j += m.getDistance("LGW", "ARN");
    j += m.getDistance("ARN", "POR");
    j += m.getDistance("POR", "DUB");

    cout << endl << j << endl;

    return 0;
}
