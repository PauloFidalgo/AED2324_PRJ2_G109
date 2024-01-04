//
// Created by Wagner Pedrosa on 27/12/2023.
//

#include "BarsState.h"
#include <sstream>

BarsState barsState;
/*!@brief função que retorna a opção escolhida pelo utilizador em relação à visualização dos dados.
 *
 * @return true para mostrar os resultados num gráfico de barras e false para mostrar numa tabela.
 * O(1)
 */
bool BarsState::shouldUseGraphicBar()   {
    return useGraphicBar;
}

/*!@brief  função que mostra um menu, onde solicita ao utilizador se deseja visualizar os dados num gráfico de barras.
 */
void BarsState::displayMenu() {

    cout << endl;
    cout << "________________________________________________________________________________________________________" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                       Do you want graphic bar?                                       |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                 1. Yes                                                        2. No                  |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|                                                                                                      |" << endl;
    cout << "|  exit - Exit                                                                                         |" << endl;
    cout << "--------------------------------------------------------------------------------------------------------" << endl;

}

/*!@brief  função que, consoante a escolha do utilizador, mete a variável "useGraphicBar" a true ou false.
 * @return chamada recursiva, até ser um input válido
 */

State* BarsState::handleInput() {
    cin.clear();
    cout << "Enter your choice: ";
    getline(cin, userInputStr);

    if (userInputStr == "exit") {
        exit(0);
    } else {
        istringstream(userInputStr) >> userInput;
        switch (userInput) {
            case 1: {
                useGraphicBar = true;
                break;
            }
            case 2: {
                useGraphicBar = false;
                break;
            }
            default:
                std::cout << " Invalid choice. try again" << std::endl;
                return handleInput();
        }
    }
}
