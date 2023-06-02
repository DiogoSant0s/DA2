#include "Graph.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
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

auto Graph::convert_to_rad(double value){
    return value*(M_PI/180);
}

double Graph::distance_between_nodes(double long1 , double lat1 , double long2 , double lat2) {
    double earth_radius = 6371;

     double delta_latitude = convert_to_rad(lat2-lat1);
     double delta_longitude = convert_to_rad(long2-long1);

    const auto converted_lat1 = convert_to_rad(lat1);
    const auto converted_lat2 = convert_to_rad(lat2);

    const auto a = pow(sin(delta_latitude/2),2) + cos(converted_lat1)*cos(converted_lat2)* pow(sin(delta_longitude/2),2);
    const auto c = 2 * atan2(sqrt(a), sqrt(1 - a));
    const auto d = c * earth_radius;

    return d;

}

double Graph::tsp_triangularAproximationHeur() {
    vector<vector<double>> distances(nodes.size(), vector<double>(nodes.size(), 0.0));

    for (auto& node : nodes) {
        for (auto& edge : node.second->edgesOut) {
            int origin = edge->origin;
            int destination = edge->dest;
            double distance = distance_between_nodes(nodes.find(origin)->second->longitude, nodes.find(origin)->second->latitude, nodes.find(destination)->second->longitude, nodes.find(destination)->second->latitude);
            distances[origin][destination] = distance;
            distances[destination][origin] = distance;
        }
    }

    vector<int> path;
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

double Graph::tsp_triangularAproximationHeuristic_toy(){
    vector<int> path;
    double totalDistance = 0;
    double lowerBound =0;

    int current_node_id = 0;
    nodes.find(current_node_id)->second->visited = true;
    path.push_back(current_node_id);

    for (int i = 0; i < nodes.size() - 1; i++) {
        int nearestNeighbor = -1;
        double minDistance = INT_MAX;

        for (int next = 0; next < nodes.size(); next++) {
            if (!nodes.find(next)->second->visited) {
                for(auto& e: nodes.find(current_node_id)->second->edgesOut){
                    if(e->dest==next){

                         lowerBound =e->distance;
                        for(auto& edge: nodes.find(next)->second->edgesOut){
                                if(edge->dest==0){
                                    lowerBound+=edge->distance;
                                }
                        }
                } }
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
    for(auto & edges:nodes.find(current_node_id)->second->edgesOut){
        if(edges->dest==0) totalDistance+=edges->distance;
    }

    return totalDistance;

}