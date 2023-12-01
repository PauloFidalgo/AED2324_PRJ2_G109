//
// Created by Wagner Pedrosa on 01/12/2023.
//

#ifndef AED2324_PRJ2_G109_STATE_H
#define AED2324_PRJ2_G109_STATE_H


class State {
public:
    virtual void displayMenu() = 0;
    virtual State* handleInput() = 0;
    virtual ~State() = default;
};


#endif //AED2324_PRJ2_G109_STATE_H
