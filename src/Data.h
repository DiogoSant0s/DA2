#ifndef DA2_DATA_H
#define DA2_DATA_H

#include <fstream>
#include <sstream>
#include "Graph.h"

using namespace std;

/**
 * @details The Data class is responsible for reading all the provided data and connecting the Menu class to the Graph class
 */
class Data {
private:
    Graph Network1;
    Graph Network2;
    Graph Network3;
    Graph Shipping;
    Graph Stadiums;
    Graph Tourism;
public:
    /**
     * Data class constructor
     * @details Calls the Graph constructor for each graph in this class and reads all the data from the files.
     */
    Data();
    /**
     * Reads all the data saved in the files and stores them in the correct structures.
     * @details Time Complexity - O((V * E))
     * @details With V being the amount of nodes and E being the amount of edges of all graphs
     */
    void readFiles();
    /**
     * Graph method to get the first real graph
     * @return The first graph - Network1
     */
    Graph getGraph1();
    /**
     * Graph method to get the second real graph
     * @return The second graph - Network2
     */
    Graph getGraph2();
    /**
     * Graph method to get the third real graph
     * @return The third graph - Network3
     */
    Graph getGraph3();
    /**
     * Graph method to get the first toy graph
     * @return The first toy graph - Shipping
     */
    Graph getToyGraph1();
    /**
     * Graph method to get the second toy graph
     * @return The second toy graph - Stadiums
     */
    Graph getToyGraph2();
    /**
     * Graph method to get the third toy graph
     * @return The third toy graph - Tourism
     */
    Graph getToyGraph3();
    /**
     * Void method that deletes all graphs, cleaning the memory
     * @details Time Complexity - O((V * E))
     * @details With V being the amount of nodes and E being the amount of edges of all graphs
     */
    void deleteData();
};

#endif //DA2_DATA_H
