#ifndef DA2_GRAPH_H
#define DA2_GRAPH_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>
#include <random>
#include <unordered_map>
#include <unordered_set>

using namespace std;

/**
 * @details The Graph class configures the attributes of a graph and the more complicated functions developed
 */
class Graph {
private:
    /**
     * Represents the edges of the graph
     */
    struct Edge {
        /**
         * Origin Node's Id
         */
        int origin;
        /**
         * Destination Node's Id
         */
        int dest;
        /**
         * Distance between the two nodes in the edge
         */
        float distance;
        /**
         * Distance between the two nodes in the edge as a string (used only by the printing function)
         */
        string distanceStr;
    };
    /**
     * Represents the content of each node
     */
    struct Node {
        /**
         * Node's Id
         */
        int Id;
        /**
         * Node's latitude
         */
        double latitude;
        /**
         * Node's longitude
         */
        double longitude;
        /**
         * Node's name (only used for the Tourism Toy Graph really)
         */
        string name;
        /**
         * List of outgoing edges, to adjacent nodes
         */
        vector<Edge*> edgesOut = {};
        /**
         * Verifies if the node has been visited on a previous search
         * @details This variable set to True means that the node has been visited and False otherwise
         */
        bool visited = false;
        /**
         * Distance between this node and the src
         */
        double distanceSrc;
    };
    /**
     * A hash table
     * @details When searching the Time Complexity is O(1)
     */
    unordered_map<int, Node*> nodes;
    /**
     * Backtacking function used to discover the shortest Hamiltonion Cycle that exists in a graph, if it exists
     * @param currentNode Node the function is currently on
     * @param cycle Integer vector that stores the Id's of the nodes currently in the cycle
     * @param count Integer used to keep count of how many nodes have been visited
     * @param distance Double used to keep track of the distance travelled
     * @param shortestCycle Integer vector that stores the Id's of the nodes currently in the shortestCycle
     * @param shortestDistance Double used to keep track of the shortestDistance travelled
     * @details Time Complexity - O(E)
     * @details E is the number of edges
     * @return True if the base case has been found
     * @return False otherwise
     */
    bool hamiltonianCycleUtil(Node* currentNode, vector<int>& cycle, int count, double distance, double& shortestDistance, vector<int>& shortestCycle);
    /**
     * Auxiliary function used to convert degrees to radians
     * @param value Value to be converted to radians
     * @details Time Complexity - O(1)
     * @return Radian equivalent to the provided degree
     */
    static double convertToRad(double value);
    /**
     * Auxiliary function used to determine the distance between to nodes using the Haversine formula
     * @param origin Id of the origin node
     * @param destination Id of the destination node
     * @details Time Complexity - O(1)
     * @return Distance between the two nodes
     */
    double distanceBetweenNodes(int origin, int destination);
    /**
     * Function used to determine the total distance travelled in a cycle
     * @param cycle Provided cycle
     * @details Time Complexity - O(N)
     * @details N is the size of the vector
     * @return Distance travelled in the cycle
     */
    double computeTourLength(vector<int> cycle);
public:
    /**
     * Graph class constructor
     * @details Creates a default Graph
     */
    Graph();
    /**
     * Add a node to the Graph
     * @param id The node's id
     * @param lon The node's longitude
     * @param lat The node's latitude
     * @details Time Complexity - O(V)
     * @details V is the number of nodes
     */
    void addNode(int id, double lon, double lat);
    /**
     * Add an edge from a source node to a target node
     * @param org The source node
     * @param destination The target node
     * @param dist Distance between the source and target nodes
     * @param distance Distance between the source and target nodes as a string
     * @details Time Complexity - O(1)
     */
    void addEdge(int org, int destination, float dist, const string& distance);
    /**
     * Getter for the object nodes
     * @details Time Complexity: O(1)
     * @return The object nodes
     */
    unordered_map<int, Node*> getNodes();
    /**
     * Getter for the outgoing edges of a certain node
     * @param id Id of the node that has the edges you are looking for
     * @details Time Complexity: O(1)
     * @return The object edgesOut of said node
     */
    vector<Edge*> getEdgesOut(int id);
    /**
     * Function used to determine the total distance travelled in a cycle for the toy and extra graphs
     * @param path Provided cycle
     * @details Time Complexity - O(N)
     * @details N is the size of the vector
     * @return Distance travelled in the cycle
     */
    double toyAndExtraComputeDistance(vector<int> path);
    /**
     * Funtion used to call the hamiltonianCycleUtil backtracking function after initializing the cycle variable
     * @details Time Complexity - O(V)
     * @details V is the number of nodes
     * @return Integer vector 'cycle' that stores the Id's of the nodes in the Hamiltonian cycle if one was found
     * @return An empty vector otherwise
     */
    vector<int> hamiltonianCycle();
    /**
     * Nearest Neighbour Heuristic function to resolve the TSP
     * @param path Vector that is passed by reference so the function can update it. Contains the path travelled
     * @details Time Complexity - O(V^2)
     * @details V is the number of nodes
     * @return Total distance travelled in the path
     */
    double nearestNeighbourHeur(vector<int> &path);
    /**
     * Triangular Approximation Heuristic function to resolve the TSP in the Toy graphs
     * @param path Vector that is passed by reference so the function can update it. Contains the path travelled
     * @details Time Complexity - O(V^2 * E^2)
     * @details V is the number of nodes and E is the number of edges
     * @return Total distance travelled in the path
     */
    double nearestNeighbourToy(vector<int> &path);
    /**
     * Self-Organizing System based Ant Colony Optimization function to resolve the TSP
     * @param iterations The number of iterations or generations of the SOS-ACO algorithm
     * @param numAnts The number of ants used in each iteration of the ACO algorithm
     * @param alpha The alpha parameter controls the influence of the pheromone levels on the ant's decision-making process
     * @param beta The beta parameter controls the influence of the heuristic information (e.g: distance) on the ant's decision-making process
     * @param evaporationRate The evaporation rate determines the rate at which the pheromone levels evaporate or decay over time
     * @param bestTourLength Total distance travelled in the path
     * @param realGraph Boolean used to know if the graph we are currently working on is a real graph or not
     * @details Time Complexity - O(N * I * V^2)
     * @details V is the number of nodes, N is the numAnts and I is the iterations
     * @return Integer vector 'uniqueTour' that stores the Id's of the nodes in cycle
     */
    vector<int> sosACO(int iterations, int numAnts, double alpha, double beta, double evaporationRate, double &bestTourLength, bool realGraph);


    double getTourDistance(vector<int> visitedVertices);

    vector<int> primMST();
};

#endif //DA2_GRAPH_H
