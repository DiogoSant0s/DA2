#include "Data.h"

Data::Data() : Shipping(Graph()), Stadiums(Graph()), Tourism(Graph()), Network1(Graph()), Network2(Graph()), Network3(Graph()) {
    readFiles();
}

Graph Data::getGraph1() {return Network1;}
Graph Data::getGraph2() {return Network2;}
Graph Data::getGraph3() {return Network3;}
Graph Data::getToyGraph1() {return Shipping;}
Graph Data::getToyGraph2() {return Stadiums;}
Graph Data::getToyGraph3() {return Tourism;}

void Data::readFiles() {
    ifstream shipping("../datasets/Toy-Graphs/shipping.csv");
    ifstream stadiums("../datasets/Toy-Graphs/stadiums.csv");
    ifstream tourism("../datasets/Toy-Graphs/tourism.csv");
    string textLine;

    getline(shipping, textLine);
    getline(stadiums, textLine);
    getline(tourism, textLine);

    while (getline(shipping, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        int origin = stoi(Origin);
        int dest = stoi(Destination);
        float distance = stof(Distance);

        Shipping.addNode(origin, 0, 0);
        Shipping.addNode(dest, 0, 0);
        Shipping.addEdge(origin, dest, distance);
    }
    while (getline(stadiums, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        int origin = stoi(Origin);
        int dest = stoi(Destination);
        float distance = stof(Distance);

        Stadiums.addNode(origin, 0, 0);
        Stadiums.addNode(dest, 0, 0);
        Stadiums.addEdge(origin, dest, distance);
    }
    while (getline(tourism, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance, OriginName, DestinationName;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, ',');
        getline(input, OriginName, ',');
        getline(input, DestinationName, '\r');

        int origin = stoi(Origin);
        int dest = stoi(Destination);
        float distance = stof(Distance);

        Tourism.addNode(origin, 0, 0);
        Tourism.addNode(dest, 0, 0);
        Tourism.addEdge(origin, dest, distance);

        Tourism.getNodes().find(origin)->second->name = OriginName;
        Tourism.getNodes().find(dest)->second->name = DestinationName;
    }

    for (int i = 1; i < 4; i++) {
        ifstream nodes("../datasets/Real-World-Graphs/graph" + to_string(i) + "/nodes.csv");
        ifstream edges("../datasets/Real-World-Graphs/graph" + to_string(i) + "/edges.csv");

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

            switch (i) {
                case 1:
                    Network1.addNode(id, longitude, latitude);
                case 2:
                    Network2.addNode(id, longitude, latitude);
                case 3:
                    Network3.addNode(id, longitude, latitude);
                default:
                    break;
            }
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

            switch (i) {
                case 1:
                    Network1.addEdge(origin, dest, distance);
                case 2:
                    Network2.addEdge(origin, dest, distance);
                case 3:
                    Network3.addEdge(origin, dest, distance);
                default:
                    break;
            }
        }
    }
}

void Data::deleteData() {
    Network1.deleteGraph();
    Network2.deleteGraph();
    Network3.deleteGraph();
    Stadiums.deleteGraph();
    Stadiums.deleteGraph();
    Tourism.deleteGraph();
}
