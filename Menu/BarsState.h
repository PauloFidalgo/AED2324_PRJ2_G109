//
// Created by Wagner Pedrosa on 27/12/2023.
//

#ifndef AED2324_PRJ2_G109_BARSSTATE_H
#define AED2324_PRJ2_G109_BARSSTATE_H
#include "State.h"

class BarsState : public State {
private:
    string userInputStr;
    int userInput;
    bool useGraphicBar;
public:
    void displayMenu() override;
    State * handleInput() override;
    bool shouldUseGraphicBar() ;

};

extern BarsState barsState;




#endif //AED2324_PRJ2_G109_BARSSTATE_H
