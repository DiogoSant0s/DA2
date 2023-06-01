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
    if (hamiltonianCycleUtil(nodes[0], cycle, 1)) {
        cycle.push_back(nodes[0]->Id);
        return cycle;
    }
    for (auto node : nodes) {
        node.second->visited = false;
        node.second->distanceSrc = 0;
    }
    return {};
}

bool Graph::hamiltonianCycleUtil(Node* currentNode, vector<int>& cycle, int count) {
    if (count == nodes.size() && currentNode->edgesOut[0]->dest == 0) {
        nodes[0]->distanceSrc = currentNode->distanceSrc + currentNode->edgesOut[0]->distance;
        return true;
    }
    for (Edge* edge : currentNode->edgesOut) {
        Node* nextNode = nodes[edge->dest];
        if (!nextNode->visited) {
            nextNode->distanceSrc = currentNode->distanceSrc + edge->distance;
            nextNode->visited = true;
            cycle.push_back(nextNode->Id);
            if (hamiltonianCycleUtil(nextNode, cycle, count + 1)) {
                return true;
            }
            cycle.pop_back();
            nextNode->visited = false;
        }
    }
    return false;
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

double Graph::distance_between_nodes( double long1 , double lat1 , double long2 , double lat2){

return std::sqrt(std::pow(long1-long2,2) + std::pow(lat1-lat2,2));
}

vector<int> Graph::tsp_triangularAproximationHeur() {
    vector<int> path;
    path.push_back(0);
    nodes.find(0)->second->visited=true;

    while(path.size() < nodes.size()) {
        int current_id = path.back();

        int next_node =-1;
        double min_dist = INFINITY;

        for(auto& n : nodes){
            if(!n.second->visited){
                double distance = distance_between_nodes(nodes.find(current_id)->second->longitude,nodes.find(current_id)->second->latitude,
                                                         n.second->longitude,n.second->latitude);
// Check if this node satisfies the triangular inequality with all other unvisited nodes
                for(auto & j : nodes){
                    if(n.second!=j.second && !j.second->visited ){
                        if((distance_between_nodes(nodes.find(current_id)->second->longitude,nodes.find(current_id)->second->latitude,
                                                  j.second->longitude,j.second->latitude) + distance_between_nodes(j.second->longitude,j.second->latitude,
                                                                                                                   n.second->longitude,n.second->latitude))<distance ){
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

// If no unvisited node satisfies the triangular inequality with all other unvisited nodes,
                // terminate the algorithm early
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

