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

vector<int> Graph::bfs() {
    vector<int> res;
    queue<int> temp;
    auto it = nodes.find(0);
    temp.push(it->second->Id);
    while(!temp.empty()) {
        int id = temp.front();
        res.push_back(id);
        temp.pop();
        for (auto & edge : getEdgesOut(id)) {
            if (!nodes.find(edge->dest)->second->visited and edge->dest != it->second->Id) {
                nodes.find(edge->dest)->second->visited = true;
                temp.push(edge->dest);
            }
        }
    }
    it->second->visited = true;
    res.push_back(it->second->Id);
    vector<int> empty = {0};
    return checkIfAllNodesVisited() ? res : empty;
}

bool Graph::checkIfAllNodesVisited() {
    return all_of(nodes.begin(), nodes.end(), [](pair<const int, Node*> node) {return node.second->visited;});
}

void Graph::tsp_backtracking(int currPos, int count, float distance, float& ans) {


if(count == nodes.size()){
    for (auto&  e: nodes.find(currPos)->second->edgesOut){
        if(e->dest==0){
            ans= min(ans, distance + e->distance);
            return;
        }
    }
}

    for(auto&  e:nodes.find(currPos)->second->edgesOut){
        int nextPos = e->dest;
        if(!nodes.find(nextPos)->second->visited){
            nodes.find(nextPos)->second->visited= true;
            count++;
            tsp_backtracking(nextPos,count,distance+e->distance,ans);
            nodes.find(nextPos)->second->visited= false;

        }
    }
}