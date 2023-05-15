#include "Data.h"

Data::Data() : graph(Graph()), realGraph(false), hasName(false), extraGraph(false) {}

Graph Data::getGraph() {return graph;}
bool Data::getRealGraph() const {return realGraph;}
bool Data::getExtraGraph() const {return extraGraph;}
bool Data::getHasName() const {return hasName;}

void Data::readRealGraphs(int graphNumber) {
    realGraph = true;
    ifstream nodes("../datasets/Real-World-Graphs/graph" + to_string(graphNumber) + "/nodes.csv");
    ifstream edges("../datasets/Real-World-Graphs/graph" + to_string(graphNumber) + "/edges.csv");
    string textLine;

    getline(nodes, textLine);
    getline(edges, textLine);

    while (getline(nodes, textLine)) {
        stringstream input(textLine);
        string Id, Longitude, Latitude;

        getline(input, Id, ',');
        getline(input, Longitude, ',');
        getline(input, Latitude, '\r');

        int id = stoi(Id);
        double longitude = stod(Longitude);
        double latitude = stod(Latitude);

        graph.addNode(id, longitude, latitude);
    }
    while (getline(edges, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        int origin = stoi(Origin);
        int dest = stoi(Destination);
        float distance = stof(Distance);

        graph.addEdge(origin, dest, distance, Distance);
    }
}

void Data::readToyGraphs(const string& graphName) {
    ifstream edges("../datasets/Toy-Graphs/" + graphName + ".csv");
    string textLine;

    getline(edges, textLine);
    string Origin, Destination, Distance;

    if (graphName == "tourism") {
        hasName = true;
        while (getline(edges, textLine)) {
            stringstream input(textLine);
            string OriginName, DestinationName;

            getline(input, Origin, ',');
            getline(input, Destination, ',');
            getline(input, Distance, ',');
            getline(input, OriginName, ',');
            getline(input, DestinationName, '\r');

            int origin = stoi(Origin);
            int dest = stoi(Destination);
            float distance = stof(Distance);

            graph.addNode(origin, 0, 0);
            graph.addNode(dest, 0, 0);
            graph.addEdge(origin, dest, distance, Distance);

            graph.getNodes().find(origin)->second->name = OriginName;
            graph.getNodes().find(dest)->second->name = DestinationName;
        }
    } else {
        while (getline(edges, textLine)) {
            stringstream input(textLine);

            getline(input, Origin, ',');
            getline(input, Destination, ',');
            getline(input, Distance, '\r');

            int origin = stoi(Origin);
            int dest = stoi(Destination);
            float distance = stof(Distance);

            graph.addNode(origin, 0, 0);
            graph.addNode(dest, 0, 0);
            graph.addEdge(origin, dest, distance, Distance);
        }
    }
}

void Data::readExtraGraphs(int graphNumber) {
    extraGraph = true;
    ifstream edges("../datasets/Extra_Fully_Connected_Graphs/edges_" + to_string(graphNumber) + ".csv");
    string textLine;

    getline(edges, textLine);

    while (getline(edges, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        int origin = stoi(Origin);
        int dest = stoi(Destination);
        float distance = stof(Distance);

        graph.addNode(origin, 0, 0);
        graph.addNode(dest, 0, 0);
        graph.addEdge(origin, dest, distance, Distance);
    }
}
