#ifndef DA2_MENU_H
#define DA2_MENU_H

#include <iomanip>
#include "Data.h"

/**
 * @details The Menu class configures the User Interface, dealing with all inputs and outputs, and connects to the project's data through the object data
 */
class Menu {
    /**
     * Object of the class Data that connects the user with the project's data
     */
    Data data;
public:
    /**
     * Menu class constructor
     * @details Complexity: O(1)
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
     * Void method that clears the screen
     * @details Complexity: O(1)
     */
    static void clearScreen();
    /**
     * Void method that outputs a string in a table block
     * @details Complexity: O(1)
     * @param s String to print
     * @param length Space given to the string in the table
     */
    static void print(const string &s, int length);
    /**
     * Void method that outputs the path of a cycle
     * @details Complexity: O(1)
     * @param s String to print
     * @param length Space given to the string in the terminal
     */
    static void printPath(const string &s, int length);
    /**
     * Void method used to choose which graph to read from the datasets
     * @details Complexity: O(1)
     */
    void SelectGraphMenu();
    /**
     * Void method used to start the interaction between the user and this projects' data
     * @details Complexity: O(1)
     */
    void MainMenu();
    /**
     * Void method used to continue the interaction between the user and this projects' data
     * @details Complexity: O(1)
     */
    void InfoMenu();
};

#endif //DA2_MENU_H
