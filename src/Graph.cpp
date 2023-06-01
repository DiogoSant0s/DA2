#include "Graph.h"

Graph::Graph() = default;

void Graph::addNode(int id, double lon, double lat) {
    bool unique = true;
    if (!nodes.empty()) {
        for (auto node : nodes) {
            if (node.first == id) {
                unique = false;
            }
        }
    }
    if (unique) {
        nodes.insert({id, new Node{id, lat, lon}});
    }
}

void Graph::addEdge(int org, int destination, float dist, const string& distance) {
    auto itSrc = nodes.find(org);
    auto itTar = nodes.find(destination);
    if (itSrc == nodes.end() || itTar == nodes.end() || itSrc == itTar) {
        return;
    }
    itSrc->second->edgesIn.push_back(new Edge{destination, org, dist, distance});
    itTar->second->edgesIn.push_back(new Edge{org, destination, dist, distance});
    itSrc->second->edgesOut.push_back(new Edge{org, destination, dist, distance});
    itTar->second->edgesOut.push_back(new Edge{destination, org, dist, distance});
}

unordered_map<int, Graph::Node*> Graph::getNodes() {
    return nodes;
}

vector<Graph::Edge*> Graph::getEdgesOut(int id) {
    return nodes.find(id)->second->edgesOut;
}

vector<int> Graph::hamiltonianCycle() {
    vector<int> cycle;
    cycle.push_back(nodes[0]->Id);
    //nodes[0]->visited = true;
    nodes[0]->distanceSrc = 0;
    vector<int> shortestCycle;
    double shortestDistance = numeric_limits<double>::max();
    if (hamiltonianCycleUtil(nodes[0], cycle, 1, 0, shortestDistance, shortestCycle)) {
        shortestCycle.push_back(nodes[0]->Id);
        nodes[0]->distanceSrc = shortestDistance;
        return shortestCycle;
    }
    for (auto node : nodes) {
        node.second->visited = false;
        node.second->distanceSrc = 0;
    }
    return {};
}

bool Graph::hamiltonianCycleUtil(Graph::Node* currentNode, vector<int>& cycle, int count, double distance, double& shortestDistance, vector<int>& shortestCycle) {
    if (count == nodes.size() && !currentNode->edgesOut.empty() && currentNode->edgesOut[0]->dest == 0) {
        // Update the distance traveled for the last edge
        distance += currentNode->edgesOut[0]->distance;
        currentNode->distanceSrc = distance;
        if (distance < shortestDistance) {
            shortestDistance = distance;
            shortestCycle = cycle;
            return true;  // A shorter cycle was found
        }
        return false;  // No shorter cycle found
    }
    bool foundShorterCycle = false;
    for (Edge* edge : currentNode->edgesOut) {
        Node* nextNode = nodes[edge->dest];
        if (!nextNode->visited) {
            nextNode->visited = true;
            cycle.push_back(nextNode->Id);
            if (distance + edge->distance < shortestDistance) {
                foundShorterCycle = hamiltonianCycleUtil(nextNode, cycle, count + 1, distance + edge->distance, shortestDistance, shortestCycle);
                if (foundShorterCycle)
                    break;  // Exit early if a shorter cycle was found
            }
            nextNode->visited = false;
            cycle.pop_back();
        }
    }
    return foundShorterCycle;
}

vector<int> Graph::triangularAproximationHeur() {
    vector<int> path;
    path.push_back(0);
    nodes.find(0)->second->visited = true;
    while (path.size() < nodes.size()) {
        int current_id = path.back();
        int next_node = -1;
        double min_dist = INFINITY;
        for (auto& n : nodes){
            if (!n.second->visited) {
                double distance = computeDistance(current_id, n.first);
                // Check if this node satisfies the triangular inequality with all other unvisited nodes
                for (auto &j : nodes) {
                    if (n.second != j.second && !j.second->visited) {
                        if ((computeDistance(current_id, j.first) + computeDistance(j.first, n.first)) < distance) {
                            break;
                        }
                    }
                }
                // If this node is closer than any other unvisited node seen so far, mark it as the next node to visit
                if (distance < min_dist) {
                    next_node = n.second->Id;
                    min_dist = distance;
                }
            }
        }
        // If no unvisited node satisfies the triangular inequality with all other unvisited nodes, terminate the algorithm early
        if (next_node == -1) {
            break;
        }
        // Add the next node to the path and mark it as visited
        path.push_back(next_node);
        nodes.find(next_node)->second->visited=true;
    }
    // Add node 0 back to the end of the path to complete the cycle
    path.push_back(0);
    return path;
}

vector<int> Graph::sosACO(int iterations, int numAnts, double alpha, double beta, double evaporationRate) {
    // Get the number of nodes in the graph
    int numNodes = (int) nodes.size();
    // Initialize the pheromone matrix with small initial values
    vector<vector<double>> pheromones(numNodes, vector<double>(numNodes, 0.01));
    // Create a random number generator
    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);
    // Initialize the best tour and its length
    vector<int> bestTour;
    double bestTourLength = numeric_limits<double>::max();
    // Perform iterations
    for (int iter = 0; iter < iterations; ++iter) {
        // Create a vector to store the tours constructed by each ant
        vector<vector<int>> antTours(numAnts);
        // Construct tours for each ant
        for (int ant = 0; ant < numAnts; ++ant) {
            vector<bool> visited(numNodes, false);  // Track visited nodes
            int currentNode = 0;  // Start from node 0
            // Construct the tour
            for (int i = 0; i < numNodes - 1; ++i) {
                visited[currentNode] = true;  // Mark the current node as visited
                antTours[ant].push_back(currentNode);
                // Compute the selection probabilities for the next node
                double totalProb = 0.0;
                vector<double> probabilities(numNodes, 0.0);
                for (int nextNode = 0; nextNode < numNodes; ++nextNode) {
                    if (!visited[nextNode]) {
                        double probability = pow(pheromones[currentNode][nextNode], alpha) * pow(1.0 / computeDistance(currentNode, nextNode), beta);
                        probabilities[nextNode] = probability;
                        totalProb += probability;
                    }
                }
                // Select the next node based on the selection probabilities
                double cumProb = 0.0;
                int nextNode = -1;
                for (int j = 0; j < numNodes; ++j) {
                    if (!visited[j]) {
                        cumProb += probabilities[j];
                        if (cumProb >= distribution(rng) * totalProb) {
                            nextNode = j;
                            break;
                        }
                    }
                }
                // Set the next node as the current node for the next iteration
                currentNode = nextNode;
            }
            // Add the last node to complete the tour
            antTours[ant].push_back(currentNode);
        }
        // Update the pheromone levels
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                pheromones[i][j] *= (1.0 - evaporationRate);  // Evaporation
            }
        }
        vector<int> tour;
        // Update the pheromone levels for each ant's tour
        for (int ant = 0; ant < numAnts; ++ant) {
            tour = antTours[ant];
            double tourLength = computeTourLength(tour);
            // Update the pheromone levels based on the tour length
            for (int i = 0; i < numNodes - 1; ++i) {
                int node1 = tour[i];
                int node2 = tour[i + 1];
                pheromones[node1][node2] += (1.0 / tourLength);
                pheromones[node2][node1] += (1.0 / tourLength);
            }
            // Update the best tour if the current tour is better
            if (tourLength < bestTourLength) {
                bestTour = tour;
                bestTourLength = tourLength;
            }
        }
    }
    // Return the best tour found
    return bestTour;
}

// Helper function to compute the distance between two nodes
double Graph::computeDistance(int node1, int node2) {
    // Retrieve the coordinates of the nodes from the graph
    double lat1 = nodes[node1]->latitude;
    double lon1 = nodes[node1]->longitude;
    double lat2 = nodes[node2]->latitude;
    double lon2 = nodes[node2]->longitude;
    // Compute the Euclidean distance between the coordinates
    return sqrt(pow(lat2 - lat1, 2) + pow(lon2 - lon1, 2));
}

// Helper function to compute the length of a tour
double Graph::computeTourLength(vector<int> tour) {
    double tourLength = 0.0;
    for (int i = 0; i < tour.size() - 1; ++i) {
        tourLength += computeDistance(tour[i], tour[i + 1]);
    }
    return tourLength;
}
