#include "Menu.h"

Menu::Menu() : data(Data()) {
    SelectGraphMenu();
}

void Menu::printTitle() {
    cout << R"(
_____________________________________________________________________________________________
____  ____  _  _ ___ ___  _  _  _____      ____  _    _____  ____  ____  ___ ___  _  _  _  _
|__/  |  |  |  |  |   |   |\ |  | __       |__|  |    | __   |  |  |__/   |   |   |__|  |\/|
|  \  |__|  |__|  |  _|_  | \|  |___|      |  |  |___ |___|  |__|  |  \  _|_  |   |  |  |  |
---------------------------------------------------------------------------------------------
    )" << "\n";
}

void Menu::print(const string& s, int length, bool tableOrPath) {
    int spaces;
    bool uneven = false;
    if ((length - int(s.size())) % 2 == 1) uneven = true;
    spaces = (length - int(s.size())) / 2;
    if (tableOrPath) cout << "|";
    else cout << "->";
    if (spaces > 0) cout << string(spaces, ' ');
    cout << s;
    if (spaces > 0) cout << string(spaces, ' ');
    if (uneven) cout << " ";
}

void Menu::clearScreen() {
    for (int i = 0; i < 20; i++) {
        cout << "\n";
    }
}

int Menu::getUserInput(vector<int> inputs) {
    int input;
    if (!cin) {
        cin.ignore();
        cin.ignore(100,'\n');
        cin.clear();
    }
    cin >> input;
    while (cin.fail() || find(inputs.begin(), inputs.end(), input) == inputs.end()) {
        if (cin.eof()) {
            cout << "\nExiting\n\n";
            return 0;
        }
        cin.clear();
        cin.ignore();
        cerr << "\nNot a valid input, please input one of the shown options: ";
        cin >> input;
    }
    cin.ignore(100, '\n');
    return input;
}

void Menu::SelectGraphMenu() {
    printTitle();
    cout << "\n";
    cout << "\tSelect Menu\n";
    cout << "(1) Real Graphs\n";
    cout << "(2) Extra Graphs\n";
    cout << "(3) Toy Graphs\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            clearScreen();
            printTitle();
            cout << "\n";
            cout << "\tReal Graphs Menu\n";
            cout << "(1) Graph 1\n";
            cout << "(2) Graph 2\n";
            cout << "(3) Graph 3\n";
            cout << "(4) Go back\n";
            cout << "(0) Exit\n";
            cout << " > ";

            input = getUserInput({0, 1, 2, 3, 4});
            switch (input) {
                case 1:
                    data.readRealGraphs(1);
                    MainMenu();
                case 2:
                    data.readRealGraphs(2);
                    MainMenu();
                case 3:
                    data.readRealGraphs(3);
                    MainMenu();
                case 4:
                    clearScreen();
                    SelectGraphMenu();
                case 0:
                    exit(0);
                default:
                    break;
            }
        case 2:
            clearScreen();
            printTitle();
            cout << "\n";
            cout << "\t\t\tExtra Graphs Menu\n";
            cout << "(1) 25\t\t(2) 50\t\t(3) 75\t\t(4) 100\n";
            cout << "(5) 200\t\t(6) 300\t\t(7) 400\t\t(8) 500\n";
            cout << "(9) 600\t\t(10) 700\t(11) 800\t(12) 900\n\n";
            cout << "(13) Go back\t";
            cout << "(0) Exit\n";
            cout << " > ";

            input = getUserInput({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
            switch (input) {
                case 1:
                    data.readExtraGraphs(25);
                    MainMenu();
                case 2:
                    data.readExtraGraphs(50);
                    MainMenu();
                case 3:
                    data.readExtraGraphs(75);
                    MainMenu();
                case 4:
                    data.readExtraGraphs(100);
                    MainMenu();
                case 5:
                    data.readExtraGraphs(200);
                    MainMenu();
                case 6:
                    data.readExtraGraphs(300);
                    MainMenu();
                case 7:
                    data.readExtraGraphs(400);
                    MainMenu();
                case 8:
                    data.readExtraGraphs(500);
                    MainMenu();
                case 9:
                    data.readExtraGraphs(600);
                    MainMenu();
                case 10:
                    data.readExtraGraphs(700);
                    MainMenu();
                case 11:
                    data.readExtraGraphs(800);
                    MainMenu();
                case 12:
                    data.readExtraGraphs(900);
                    MainMenu();
                case 13:
                    clearScreen();
                    SelectGraphMenu();
                case 0:
                    exit(0);
                default:
                    break;
            }
        case 3:
            clearScreen();
            printTitle();
            cout << "\n";
            cout << "\tToy Graphs Menu\n";
            cout << "(1) Shipping\n";
            cout << "(2) Stadiums\n";
            cout << "(3) Tourism\n";
            cout << "(4) Go back\n";
            cout << "(0) Exit\n";
            cout << " > ";

            input = getUserInput({0, 1, 2, 3, 4});
            switch (input) {
                case 1:
                    data.readToyGraphs("shipping");
                    MainMenu();
                case 2:
                    data.readToyGraphs("stadiums");
                    MainMenu();
                case 3:
                    data.readToyGraphs("tourism");
                    MainMenu();
                case 4:
                    clearScreen();
                    SelectGraphMenu();
                case 0:
                    exit(0);
                default:
                    break;
            }
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::MainMenu() {
    clearScreen();
    printTitle();
    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) Graph Information\n";
    cout << "(2) Backtracking Algorithm\n";
    cout << "(3) Triangular Approximation Heuristic\n";
    cout << "(4) Ant Colony Optimization\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4});
    switch (input) {
        case 1:
            InfoMenu();
        case 2:
            if (!data.getGraph().getNodes().empty()) {
                clearScreen();
                printTitle();
                cout << "\nFinding Hamiltonian cycle in the graph. Please wait\n\n";
                vector<int> cycle = data.getGraph().hamiltonianCycle();
                for (int i = 0; i < cycle.size(); i++) {
                    print(to_string(cycle[i]), 6, false);
                    if (i % 25 == 0 and i != 0) {
                        cout << "\n";
                    }
                }
                cout << "\n\nThe distance the travelling salesman travels is " << fixed << data.getGraph().getNodes()[0]->distanceSrc;
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                MainMenu();
            }
        case 3:
            if (!data.getGraph().getNodes().empty()) {
                vector<int> path;
                cout << "\nFinding cycle in the graph using this Heuristic. Please wait\n";
                double dist;
                if (data.getRealGraph()) {
                    dist = data.getGraph().triangularAproximationHeur(path);
                } else {
                    dist = data.getGraph().triangularAproximationHeurToy(path);
                }
                for (int i = 0; i < path.size(); i++) {
                    print(to_string(path[i]), 6, false);
                    if (i % 25 == 0 and i != 0) {
                        cout << "\n";
                    }
                }
                cout << "\nThe distance the travelling salesman travels is " << fixed << dist << "\n";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                MainMenu();
            }
        case 4:
            if (!data.getGraph().getNodes().empty()) {
                int iterations, numAnts;
                double alpha, beta, evaporationRate;
                if (data.getGraph().getNodes().size() < 1000) {
                    iterations = 200;
                    numAnts = 10;
                    alpha = 1;
                    beta = 2;
                    evaporationRate = 0.5;
                } else if (data.getGraph().getNodes().size() < 5000) {
                    iterations = 100;
                    numAnts = 15;
                    alpha = 1;
                    beta = 2;
                    evaporationRate = 0.3;
                } else if (data.getGraph().getNodes().size() < 10000) {
                    iterations = 500;
                    numAnts = 40;
                    alpha = 2;
                    beta = 4;
                    evaporationRate = 0.4;
                } else {
                    iterations = 1000;
                    numAnts = 70;
                    alpha = 4;
                    beta = 7;
                    evaporationRate = 0.5;
                }
                double bestTourLength = numeric_limits<double>::max();
                cout << "\nPlease wait a bit while the ants do what you told them to: resolve the TSP problem. Tsk, never expected to see this type of animal cruelty\n";
                vector<int> squirrelsInMyPants = data.getGraph().sosACO(iterations, numAnts, alpha, beta, evaporationRate, bestTourLength, data.getRealGraph());
                for (int i = 0; i < squirrelsInMyPants.size(); i++) {
                    print(to_string(squirrelsInMyPants[i]), 6, false);
                    if (i % 25 == 0 and i != 0) {
                        cout << "\n";
                    }
                }
                cout << "\nThe distance the travelling salesman travels is " << fixed << bestTourLength;
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                MainMenu();
            }
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::InfoMenu() {
    clearScreen();
    printTitle();
    cout << "\n";
    cout << "\tGraph Information Menu\n";
    cout << "(1) All nodes of a graph\n";
    cout << "(2) Information about a specific node of a graph\n";
    cout << "(3) Back to the Main Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            if (!data.getGraph().getNodes().empty()) {
                if (data.getRealGraph()) {
                    cout << "\nDue to the number of nodes of this graph, choose the amount of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph().getNodes().size()) + "\n" + " > ";
                    vector<int> inputs;
                    for (int i = 1; i <= data.getGraph().getNodes().size(); i++) inputs.push_back(i);
                    int size = getUserInput(inputs);
                    cout << "\n\n";
                    for (int i = 0; i < 56; i++) cout << "-";
                    cout << "\n";
                    print("Node Id", 10, true);
                    print("Longitude", 21, true);
                    print("Latitude", 21, true);
                    cout << "|\n";
                    for (int i = 0; i < 56; i++) cout << "-";
                    cout << "\n";
                    for (int i = 0; i < size; i++) {
                        print(to_string(data.getGraph().getNodes().at(i)->Id), 10, true);
                        cout << "| " << fixed << setprecision(15) << data.getGraph().getNodes().at(i)->longitude << " ";
                        cout << "| " << fixed << setprecision(15) << data.getGraph().getNodes().at(i)->latitude << " ";
                        cout << "|\n";
                    }
                    for (int i = 0; i < 56; i++) cout << "-";
                } else if (data.getExtraGraph()) {
                    int size = (int) data.getGraph().getNodes().size();
                    if (size > 100) {
                        cout <<
                        "\nDue to the number of nodes of this graph, choose the amount of entries about to be shown to you from 1 to " +
                             to_string(data.getGraph().getNodes().size()) + "\n" + " > ";
                        vector<int> inputs;
                        for (int i = 1; i <= data.getGraph().getNodes().size(); i++) inputs.push_back(i);
                        size = getUserInput(inputs);
                    }
                    cout << "\n\n";
                    for (int i = 0; i < 12; i++) cout << "-";
                    cout << "\n";
                    print("Node Id", 10, true);
                    cout << "|\n";
                    for (int i = 0; i < 12; i++) cout << "-";
                    cout << "\n";
                    for (int i = 0; i < size; i++) {
                        print(to_string(data.getGraph().getNodes().at(i)->Id), 10, true);
                        cout << "|\n";
                    }
                    for (int i = 0; i < 12; i++) cout << "-";
                } else {
                    if (data.getHasName()) {
                        cout << "\n\n";
                        for (int i = 0; i < 23; i++) cout << "-";
                        cout << "\n";
                        print("Node Id", 9, true);
                        print("Node Name", 11, true);
                        cout << "|\n";
                        for (int i = 0; i < 23; i++) cout << "-";
                        cout << "\n";
                        for (int i = 0; i < data.getGraph().getNodes().size(); i++) {
                            print(to_string(data.getGraph().getNodes().at(i)->Id), 9, true);
                            print(data.getGraph().getNodes().at(i)->name, 11, true);
                            cout << "|\n";
                        }
                        for (int i = 0; i < 23; i++) cout << "-";
                    } else {
                        cout << "\n\n";
                        for (int i = 0; i < 12; i++) cout << "-";
                        cout << "\n";
                        print("Node Id", 10, true);
                        cout << "|\n";
                        for (int i = 0; i < 12; i++) cout << "-";
                        cout << "\n";
                        for (int i = 0; i < data.getGraph().getNodes().size(); i++) {
                            print(to_string(data.getGraph().getNodes().at(i)->Id), 10, true);
                            cout << "|\n";
                        }
                        for (int i = 0; i < 12; i++) cout << "-";
                    }
                }
            }
            cout << "\n\n";
            cout << "Press 7 to continue\n";
            getUserInput({7});
            InfoMenu();
        case 2:
            if (!data.getGraph().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getGraph().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getGraph().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                int size = (int) data.getGraph().getEdgesOut(Id).size();
                if (size > 100) {
                    vector<int> inputs1;
                    cout << "\nDue to the number of edges of this node, choose the amount of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph().getEdgesOut(Id).size()) + "\n" + " > ";
                    for (int i = 1; i <= data.getGraph().getEdgesOut(Id).size(); i++) inputs1.push_back(i);
                    size = getUserInput(inputs1);
                }
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                print("Origin", 8, true);
                print("Destination", 13, true);
                print("Distance", 10, true);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    print(to_string(data.getGraph().getEdgesOut(Id).at(i)->origin), 8, true);
                    print(to_string(data.getGraph().getEdgesOut(Id).at(i)->dest), 13, true);
                    print(data.getGraph().getEdgesOut(Id).at(i)->distanceStr, 10, true);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
            }
            cout << "\n\n";
            cout << "Press 7 to continue\n";
            getUserInput({7});
            InfoMenu();
        case 3:
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}
