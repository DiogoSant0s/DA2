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

void Graph::addEdge(int org, int destination, float dist) {
    auto itSrc = nodes.find(org);
    auto itTar = nodes.find(destination);
    if (itSrc == nodes.end() || itTar == nodes.end() || itSrc == itTar) {
        return;
    }
    itSrc->second->edgesIn.push_back(new Edge{destination, org, dist});
    itTar->second->edgesIn.push_back(new Edge{org, destination, dist});
    itSrc->second->edgesOut.push_back(new Edge{org, destination, dist});
    itTar->second->edgesOut.push_back(new Edge{destination, org, dist});
}

unordered_map<int, Graph::Node*> Graph::getNodes() {
    return nodes;
}

list<Graph::Edge*> Graph::getEdges(int id) {
    return nodes.find(id)->second->edgesOut;
}
