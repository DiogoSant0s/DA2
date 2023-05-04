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

        int org = stoi(Origin);
        int dest = stoi(Destination);
        float dist = stof(Distance);


    }
    while (getline(stadiums, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        int org = stoi(Origin);
        int dest = stoi(Destination);
        float dist = stof(Distance);


    }
    while (getline(tourism, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance, OriginName, DestinationName;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, ',');
        getline(input, OriginName, ',');
        getline(input, DestinationName, '\r');

        int org = stoi(Origin);
        int dest = stoi(Destination);
        int dist = stoi(Distance);


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


        }
        while (getline(edges, textLine)) {
            stringstream input(textLine);
            string Origin, Destination, Distance;

            getline(input, Origin, ',');
            getline(input, Destination, ',');
            getline(input, Distance, '\r');

            int org = stoi(Origin);
            int dest = stoi(Destination);
            float dist = stof(Distance);


        }
    }
}
