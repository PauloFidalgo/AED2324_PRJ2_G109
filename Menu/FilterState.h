//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_FILTERSTATE_H
#define AED2324_PRJ2_G109_FILTERSTATE_H
#include "State.h"
class FilterState: public State {
private:
    string from;
    string to;
public:
    // Constructor
    FilterState();

    // Setters
    void setFrom(const std::string& from);
    void setTo(const std::string& to);

    void displayMenu() override;
    State * handleInput() override;
};


#endif //AED2324_PRJ2_G109_FILTERSTATE_H
