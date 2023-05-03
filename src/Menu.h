#ifndef DA2_MENU_H
#define DA2_MENU_H

#include <sstream>
#include <iostream>
#include "Data.h"

using namespace std;

/**
 * Classe Menu
 * @details A classe Menu relaciona-se diretamente com a classe Data,
 * por meio do atributo data. Esta classe configura a UI do programa e toda a lógica do menu
 */
class Menu {
    Data data;
public:
    /**
     * Construtor da classe.
     * @see Data
     * @details Complexity: O(n)
     */
    Menu();
    /**
     * Método void que apresenta o título do menu
     * @details Complexity: O(1)
     */
    static void printTitle();
    /**
     * Método normal que verifica se o input do utilizador é válido.
     * @details Complexity: O(1)
     * @param inputs vetor de inteiros
     * @return inteiro input do utilizador
     */
    static int getUserInput(vector<int> inputs);
    /**
     * Método normal que verifica se o input do utilizador é válido,
     * para um número indefinido de inputs possíveis.
     * @details Complexity: O(1)
     * @return string input do utilizador
     */
    static string getUserTextInput();
    /**
     * Complexity: O(1)
     * Método void que "limpa" o ecrã
     */
    static void clearScreen();
    /**
     * Método void que formata uma string segundo um tamanho definido para apresentar no ecrã nas listagens.
     * @details Complexity: O(1)
     * @param s string
     * @param length inteiro
     */
    static void Print(const string &s, int length);
    /**
     * Método void utilizado para apresentar no ecrã as opções do menu principal ao utilizador.
     * @details Complexity: O(1)
     */
    void MainMenu();
};

#endif //DA2_MENU_H
