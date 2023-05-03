#ifndef DA_RAILWAYS_GRAPH_H
#define DA_RAILWAYS_GRAPH_H

#include <iostream>
#include <utility>
#include <list>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    /**
     * Represents the edges of the graph/network segments.
     */
    struct Edge {
        /**
         * Origin Station's Name
         */
        string origin;
        /**
         * Destination Station's Name
         */
        string dest;
        /**
         * Type of service provided (STANDARD or ALFA PENDULAR)
         */
        string service;
        /**
         * Number of trains that can simultaneously travel on the respective network segment
         */
         int capacity;
        /**
         * Flow
         */
         int flow = 0;
    };
    /**
     * Represents the content of each node.
     */
    struct Node {
        //TODO
        //Ships not here
        /**
         * List of outgoing edges, to adjacent nodes.
         */
        list<Edge*> edges = {};
        /**
         * Verifies if the node has been visited on a previous search.
         * @details This variable set to True means that the node has been visited and False otherwise.
         */
        bool visited = false;
        /**
         * Path from src to this node
         */
        Edge* path = nullptr;
        /**
         * Cost from source to the vertex
         */
        int distance = 0;
    };
    /**
     * A hash table.
     * @details When searching the Time Complexity is O(1).
     */
    unordered_map<string, Node*> nodes;
public:
    /**
     * Creates a new Graph.
     * @details Constructor of the Graph class.
     */
    Graph();
};

#endif //DA_RAILWAYS_GRAPH_H
