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
