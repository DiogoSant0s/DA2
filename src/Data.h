#ifndef DA2_DATA_H
#define DA2_DATA_H

#include <fstream>
#include <sstream>
#include "Graph.h"

/**
 * @details The Data class is responsible for reading all the provided data and connecting the Menu class to the Graph class
 */
class Data {
private:
    /**
     * The graph
     */
    Graph graph;
    /**
     * Bool used to know if the graph is one of the Real World Graphs
     */
    bool realGraph;
    /**
     * Bool used to know if the graph is the Tourism Toy Graph, the only graph whose nodes have names
     */
    bool hasName;
    /**
     * Bool used to know if the graph is one of the Extra Fully Connected Graphs
     */
    bool extraGraph;
public:
    /**
     * Data class constructor
     * @details Calls the Graph constructor for the graph in this class and initializes all bools to false
     */
    Data();
    /**
     * Reads the data in the nodes and edges files from the real graph corresponding to the given graphNumber and stores it in the correct structures
     * @details Time Complexity - O(V * E)
     * @details With V being the amount of nodes and E being the amount of edges of the graph
     * @param graphNumber Number of the graph to be read
     */
    void readRealGraphs(int graphNumber);
    /**
     * Reads the data in the edges file from the toy graph corresponding to the given graphName and stores it in the correct structures
     * @details Time Complexity - O(E)
     * @details With E being the amount of edges of the graph
     * @param graphName Name of the graph to be read
     */
    void readToyGraphs(const string& graphName);
    /**
     * Reads the data in the edges file from the extra graph corresponding to the given graphNumber and stores it in the correct structures
     * @details Time Complexity - O(E)
     * @details With E being the amount of edges of the graph
     * @param graphNumber Number of the graph to be read
     */
    void readExtraGraphs(int graphNumber);
    /**
     * Graph method to get the Graph graph
     * @return graph
     */
    Graph getGraph();
    /**
     * Bool method to get the boolean realGraph
     * @return realGraph
     */
    bool getRealGraph() const;
    /**
     * Bool method to get the boolean extraGraph
     * @return extraGraph
     */
    bool getExtraGraph() const;
    /**
     * Bool method to get the boolean hasName
     * @return hasName
     */
    bool getHasName() const;
};

#endif //DA2_DATA_H
