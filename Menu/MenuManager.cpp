//
// Created by Wagner Pedrosa on 01/12/2023.
//

#include "MenuManager.h"
#include "MainMenuState.h"
/*!@brief Construtor da classe MenuManager. Inicia o estado atual com o estado do menu principal
 *
 */
MenuManager::MenuManager(): currentState(new MainMenuState()) {};

/*!@brief Destrutor da classe MenuManager. Liberta a memória alocada para o estado atual
 *
 */
MenuManager::~MenuManager() {
    delete currentState;
}
/*!@brief Função que é o loop prinipal do funcionamento dos menus, onde exibe o menu do estado atual, e consoante o input do utilizador altera o estado atual
 *
 */
void MenuManager::menuNavigation() {
    while (currentState) {
        currentState->displayMenu();
        State* nextState = currentState->handleInput();

        currentState = nextState;
    }
}