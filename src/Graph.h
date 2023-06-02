#ifndef DA2_GRAPH_H
#define DA2_GRAPH_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

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
         * List of edges incoming from adjacent nodes
         */
        vector<Edge*> edgesIn = {};
        /**
         * Verifies if the node has been visited on a previous search
         * @details This variable set to True means that the node has been visited and False otherwise
         */
        bool visited = false;
        /**
         * Path from src to this node
         */
        Edge* path = nullptr;
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
     *
     * @param node1
     * @param node2
     * @return
     */
    double computeDistance(int node1, int node2);
public:
    /**
     * Graph class constructor
     * @details Creates a default Graph
     */
    Graph();
    /**
     * Add a node to the Graph
     * @details Time Complexity - O(V)
     * @details V is the number of nodes
     * @param id The node's id
     * @param lon The node's longitude
     * @param lat The node's latitude
     */
    void addNode(int id, double lon, double lat);
    /**
     * Add an edge from a source node to a target node
     * @details Time Complexity - O(1)
     * @param org The source node
     * @param destination The target node
     * @param dist Distance between the source and target nodes
     * @param distance Distance between the source and target nodes as a string
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
     * @details Time Complexity: O(1)
     * @param id Id of the node that has the edges you are looking for
     * @return The object edgesOut of said node
     */
    vector<Edge*> getEdgesOut(int id);
    /**
     * Funtion used to call the hamiltonianCycleUtil backtracking function after initializing the cycle variable
     * @details Time Complexity - O(V)
     * @details V is the number of nodes
     * @return Integer vector 'cycle' that stores the Id's of the nodes in the Hamiltonian cycle if one was found
     * @return An empty vector otherwise
     */
    vector<int> hamiltonianCycle();
    /**
     *
     * @param long1
     * @param lat1
     * @param long2
     * @param lat2
     * @return
     */
    /**
     *
     * @param iterations
     * @param numAnts
     * @param alpha
     * @param beta
     * @param evaporationRate
     * @return
     */
    double distance_between_nodes(double long1, double lat1, double long2, double lat2);
    vector<int> sosACO(int iterations, int numAnts, double alpha, double beta, double evaporationRate);
    /**
     *
     * @param tour
     * @return
     */
    double tsp_triangularAproximationHeur();

     auto convert_to_rad(double value);

    double tsp_triangularAproximationHeuristic_toy();
    double computeTourLength(vector<int> tour);
};

#endif //DA2_GRAPH_H
