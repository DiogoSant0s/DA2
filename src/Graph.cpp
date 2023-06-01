#include "Graph.h"
using namespace std;

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

void Graph::dfs(int nodeId) {
    Node* it = nodes.find(nodeId)->second;
    it->visited = true;
    for (Edge* e: it->edgesOut) {
        Node* target_node = nodes.find(e->dest)->second;
        if (!target_node->visited) {
            dfs(e->dest);
        }
    }
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

float Graph::tsp_backtracking(int currPos, int count, float distance, float ans) {
    if (count == nodes.size()) {
        for (Edge* e : nodes.find(currPos)->second->edgesOut) {
            if (e->dest == 0){
                return min(ans, distance + e->distance);
            }
        }
    }
    for (Edge* e : nodes.find(currPos)->second->edgesOut) {
        int nextPos = e->dest;
        if (!nodes.find(nextPos)->second->visited){
            nodes.find(nextPos)->second->visited = true;
            count++;
            tsp_backtracking(nextPos, count,distance + e->distance, ans);
            nodes.find(nextPos)->second->visited = false;
            count--;
        }
    }
    return 0;
}

double Graph::distance_between_nodes(double long1 , double lat1 , double long2 , double lat2) {
    return sqrt(pow(long1 - long2,2) + pow(lat1 - lat2,2));
}

vector<int> Graph::tsp_triangularAproximationHeur() {
    vector<int> path;
    path.push_back(0);
    nodes.find(0)->second->visited = true;
    while (path.size() < nodes.size()) {
        int current_id = path.back();
        int next_node = -1;
        double min_dist = INFINITY;
        for (auto& n : nodes){
            if (!n.second->visited) {
                double distance = distance_between_nodes(nodes.find(current_id)->second->longitude,nodes.find(current_id)->second->latitude,n.second->longitude,n.second->latitude);
                // Check if this node satisfies the triangular inequality with all other unvisited nodes
                for (auto &j : nodes) {
                    if (n.second != j.second && !j.second->visited) {
                        if ((distance_between_nodes(nodes.find(current_id)->second->longitude,nodes.find(current_id)->second->latitude,j.second->longitude,j.second->latitude)
                        + distance_between_nodes(j.second->longitude,j.second->latitude,n.second->longitude,n.second->latitude)) < distance) {
                            break;
                        }
                    }
                }
                // If this node is closer than any other unvisited node seen so far,
                // mark it as the next node to visit
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
