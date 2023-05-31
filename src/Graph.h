#ifndef DA2_GRAPH_H
#define DA2_GRAPH_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <algorithm>
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
     *
     * @param currentNode
     * @param visitedNodes
     * @param cycle
     * @param count
     * @return
     */
    bool hamiltonianCycleUtil(Node *currentNode, unordered_set<Graph::Node*> &visitedNodes, vector<int> &cycle, int count);
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
     * Function used to do a Depth-First Search (aka DFS)
     * @details Time Complexity - O(|V| + |E|)
     * @details V is the number of nodes and E is the number of edges
     * @param nodeId The Id of the node to be searched
     */
    void dfs(int nodeId);
    /**
     *
     * @return
     */
    vector<int> hamiltonianCycle();

    void tsp_backtracking(int currPos, int count, float distance, float& ans);

};

#endif //DA2_GRAPH_H
