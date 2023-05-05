#ifndef DA2_MENU_H
#define DA2_MENU_H

#include <sstream>
#include <iostream>
#include <vector>
#include "algorithm"
#include "Data.h"

using namespace std;

/**
 * @details The Menu class configures the User Interface, dealing with all inputs and outputs, and connects to the project's data through the attribute data
 */
class Menu {
    Data data;
public:
    /**
     * Menu class constructor
     * @details Complexity: O(n)
     * @details Calls the Data class constructor and initializes the Main Menu
     */
    Menu();
    /**
     * Void method that shows the projects' title
     * @details Complexity: O(1)
     */
    static void printTitle();
    /**
     * Void method that ensures the user's input integer is valid
     * @details Complexity: O(1)
     * @param inputs Integer vector
     * @return The integer provided by the user, verified to be valid
     */
    static int getUserInput(vector<int> inputs);
    /**
     * Void method that returns the string provided by the user
     * @details Complexity: O(1)
     * @return The string provided by the user,
     */
    static string getUserTextInput();
    /**
     * Complexity: O(1)
     * Void method that clears the screen
     */
    static void clearScreen();
    /**
     * Void method that outputs a string in a table block
     * @details Complexity: O(1)
     * @param s String to print
     * @param length Space given to the string in the table
     */
    static void Print(const string &s, int length);
    /**
     * Void method used to start the interaction between the user and this projects' data
     * @details Complexity: O(1)
     */
    void MainMenu();
};

#endif //DA2_MENU_H
