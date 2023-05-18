#include "Graph.h"

Graph::Graph() = default;

void Graph::addNode(int id, double lon, double lat) {
    bool unique = true;
    if (!nodes.empty()) {
        for (const auto& it : nodes) {
            if (it.first == id) {
                unique = false;
            }
        }
    }
    if (nodes.empty() || unique) {
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
    auto it = nodes.find(nodeId);
    it->second->visited = true;
    for (const auto &e: it->second->edgesOut) {
        auto target_node = nodes.find(e->dest);
        if (!target_node->second->visited) {
            dfs(e->dest);
        }
    }
}
