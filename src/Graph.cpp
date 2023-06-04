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
    itSrc->second->edgesOut.push_back(new Edge{org, destination, dist, distance});
    itTar->second->edgesOut.push_back(new Edge{destination, org, dist, distance});
}

unordered_map<int, Graph::Node*> Graph::getNodes() {
    return nodes;
}

vector<Graph::Edge*> Graph::getEdgesOut(int id) {
    return nodes.find(id)->second->edgesOut;
}

double Graph::convertToRad(double value) {
    return value * (M_PI / 180);
}

double Graph::distanceBetweenNodes(int origin, int destination) {
    double a = pow(sin(convertToRad(nodes[destination]->latitude - nodes[origin]->latitude) / 2), 2) + cos(convertToRad(nodes[origin]->latitude)) *
            cos(convertToRad(nodes[destination]->latitude)) * pow(sin(convertToRad(nodes[destination]->longitude - nodes[origin]->longitude) / 2), 2);
    return 2 * atan2(sqrt(a), sqrt(1 - a)) * 6371;
}

double Graph::getTourDistance(vector<int> visitedNodes) {
    double totalDistance = 0;
    for (int i = 0; i < visitedNodes.size() - 1; ++i) {
        totalDistance += distanceBetweenNodes(visitedNodes[i],visitedNodes[i + 1]);
    }
    totalDistance += distanceBetweenNodes(visitedNodes.back(),visitedNodes.front());
    return totalDistance;
}

double Graph::toyAndExtraComputeDistance(vector<int> path) {
    double totalDistance = 0.0;
    for (int i = 0; i < path.size() - 1; ++i) {
        for (Edge* edge : nodes.find(path[i])->second->edgesOut) {
            if (edge->dest == path[i + 1]) {
                totalDistance += edge->distance;
                break;
            }
        }
    }
    return totalDistance;
}

vector<int> Graph::hamiltonianCycle() {
    for (auto node : nodes) {
        node.second->visited = false;
        node.second->distanceSrc = numeric_limits<double>::max();
    }
    vector<int> cycle;
    cycle.push_back(nodes[0]->Id);
    nodes[0]->visited = true;
    nodes[0]->distanceSrc = 0;
    vector<int> shortestCycle;
    double shortestDistance = numeric_limits<double>::max();
    if (hamiltonianCycleUtil(nodes[0], cycle, 1, 0, shortestDistance, shortestCycle)) {
        shortestCycle.push_back(nodes[0]->Id);
        nodes[0]->distanceSrc = shortestDistance;
        return shortestCycle;
    }
    return {};
}

bool Graph::hamiltonianCycleUtil(Node* currentNode, vector<int>& cycle, int count, double distance, double& shortestDistance, vector<int>& shortestCycle) {
    if (count == nodes.size() && !currentNode->edgesOut.empty() && currentNode->edgesOut[0]->dest == 0) {
        distance += currentNode->edgesOut[0]->distance;
        currentNode->distanceSrc = distance;
        if (distance < shortestDistance) {
            shortestDistance = distance;
            shortestCycle = cycle;
            return true;
        }
        return false;
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
                    break;
            }
            nextNode->visited = false;
            cycle.pop_back();
        }
    }
    return foundShorterCycle;
}

double Graph::triangularApproximationHeur(vector<int> &path) {
    for (auto node : nodes) {
        node.second->visited = false;
        node.second->distanceSrc = 0;
    }
    vector<vector<double>> distances(nodes.size(), vector<double>(nodes.size(), 0.0));
    for (auto node : nodes) {
        for (Edge* edge : node.second->edgesOut) {
            int origin = edge->origin;
            int destination = edge->dest;
            double distance = distanceBetweenNodes(origin, destination);
            distances[origin][destination] = distance;
            distances[destination][origin] = distance;
        }
    }
    double totalDistance = 0;
    int current_node_id = 0;
    nodes.find(current_node_id)->second->visited = true;
    path.push_back(current_node_id);
    for (int i = 0; i < nodes.size() - 1; i++) {
        int nearestNeighbor = -1;
        double minDistance = INT_MAX;
        for (int next = 0; next < nodes.size(); next++) {
            if (!nodes.find(next)->second->visited) {
                double lowerBound = distances[current_node_id][next] + distances[next][0];
                if (lowerBound < minDistance) {
                    minDistance = lowerBound;
                    nearestNeighbor = next;
                }
            }
        }
        current_node_id = nearestNeighbor;
        nodes.find(current_node_id)->second->visited = true;
        path.push_back(current_node_id);
        totalDistance += minDistance;
    }
    path.push_back(0);
    totalDistance += distances[current_node_id][0];
    return totalDistance;
}

double Graph::triangularApproximationHeurToy(vector<int> &path) {
    for (auto& node : nodes) {
        node.second->visited = false;
        node.second->distanceSrc = 0;
    }
    double totalDistance = 0;
    double lowerBound = 0;
    int current_node_id = 0;
    nodes.find(current_node_id)->second->visited = true;
    path.push_back(current_node_id);
    for (int i = 0; i < nodes.size() - 1; i++) {
        int nearestNeighbor = -1;
        double minDistance = INT_MAX;
        for (int next = 0; next < nodes.size(); next++) {
            if (!nodes.find(next)->second->visited) {
                for (auto &e: nodes.find(current_node_id)->second->edgesOut) {
                    if (e->dest == next) {
                        lowerBound = e->distance;
                        for (Edge* edge: nodes.find(next)->second->edgesOut) {
                            if (edge->dest == 0) {
                                lowerBound += edge->distance;
                            }
                        }
                    }
                }
                if (lowerBound < minDistance) {
                    minDistance = lowerBound;
                    nearestNeighbor = next;
                }
            }
        }
        current_node_id = nearestNeighbor;
        nodes.find(current_node_id)->second->visited = true;
        path.push_back(current_node_id);
        totalDistance += minDistance;
    }
    path.push_back(0);
    for (Edge* edges: nodes.find(current_node_id)->second->edgesOut) {
        if (edges->dest == 0) {
            totalDistance += edges->distance;
        }
    }
    return totalDistance;
}

vector<int> Graph::sosACO(int iterations, int numAnts, double alpha, double beta, double evaporationRate, bool realGraph) {
    int numNodes = static_cast<int>(nodes.size());
    vector<vector<double>> distances(numNodes, vector<double>(numNodes, 0.0));
    for (auto& node : nodes) {
        for (Edge* edge : node.second->edgesOut) {
            int origin = edge->origin;
            int destination = edge->dest;
            double distance = distanceBetweenNodes(origin, destination);
            distances[origin][destination] = distance;
            distances[destination][origin] = distance;
        }
    }
    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution<double> distribution(0.0, 1.0);

    vector<vector<double>> pheromones(numNodes, vector<double>(numNodes, 0.01));
    vector<int> bestTour;
    double bestTourLength;
    vector<bool> visited(numNodes, false);
    vector<double> probabilities(numNodes, 0.0);

    for (int iter = 0; iter < iterations; ++iter) {
        vector<vector<int>> antTours(numAnts);
        for (int ant = 0; ant < numAnts; ++ant) {
            int currentNode = 0;
            for (int i = 0; i < numNodes - 1; ++i) {
                visited[currentNode] = true;
                antTours[ant].push_back(currentNode);
                double totalProb = 0.0;
                int nextNode = 0;
                double minProbability = numeric_limits<double>::max();
                for (int j = 0; j < numNodes; ++j) {
                    if (!visited[j]) {
                        double probability = pow(pheromones[currentNode][j], alpha) * pow(1.0 / distances[currentNode][j], beta);
                        probabilities[j] = probability;
                        totalProb += probability;
                        if (probability < minProbability) {
                            minProbability = probability;
                            nextNode = j;
                        }
                    }
                }
                double roulette = distribution(rng) * totalProb;
                double cumProb = 0.0;
                for (int j = 0; j < numNodes; ++j) {
                    if (!visited[j]) {
                        cumProb += probabilities[j];
                        if (cumProb >= roulette) {
                            nextNode = j;
                            break;
                        }
                    }
                }
                currentNode = nextNode;
            }
            antTours[ant].push_back(currentNode);
        }
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                pheromones[i][j] *= (1.0 - evaporationRate);
            }
        }
        vector<int> tour;
        for (int ant = 0; ant < numAnts; ++ant) {
            tour = antTours[ant];
            double tourLength;
            if (realGraph) {
                tourLength = getTourDistance(tour);
            } else {
                tourLength = toyAndExtraComputeDistance(tour);
            }
            for (int i = 0; i < numNodes - 1; ++i) {
                int node1 = tour[i];
                int node2 = tour[i + 1];
                pheromones[node1][node2] += (1.0 / tourLength);
                pheromones[node2][node1] += (1.0 / tourLength);
            }
            if (tourLength < bestTourLength) {
                bestTour = tour;
                bestTourLength = tourLength;
            }
        }
    }
    bestTour.push_back(bestTour[0]);
    vector<int> uniqueTour;
    unordered_set<int> visitedNodes;
    for (int node : bestTour) {
        if (visitedNodes.find(node) == visitedNodes.end()) {
            uniqueTour.push_back(node);
            visitedNodes.insert(node);
        }
    }
    for (auto& node : nodes) {
        if (visitedNodes.find(node.first) == visitedNodes.end()) {
            uniqueTour.push_back(node.first);
        }
    }
    uniqueTour.push_back(nodes[0]->Id);
    return uniqueTour;
}

vector<int> Graph::primMST() {
    int numNodes = (int) nodes.size();
    vector<int> key(numNodes, INT_MAX);
    vector<int> parent(numNodes, -1);
    vector<bool> inMST(numNodes, false);
    key[0] = 0;
    for (int count = 0; count < numNodes - 1; ++count) {
        int minKey = INT_MAX;
        int u;
        for (int v = 0; v < numNodes; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        inMST[u] = true;
        for (int v = 0; v < numNodes; ++v) {
            int weight = (int) distanceBetweenNodes(u,v);
            if (weight && !inMST[v] && key[v] > weight) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }
    vector<int> visitedNodes;
    for (int i = 1; i < numNodes; ++i) {
        visitedNodes.push_back(parent[i]);
        visitedNodes.push_back(i);
    }
    return visitedNodes;
}
