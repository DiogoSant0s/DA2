#include "Menu.h"

Menu::Menu() : data(Data()) {
    MainMenu();
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

void Menu::Print(const string& s, int length) {
    int spaces;
    bool uneven = false;
    if ((length - int(s.size())) % 2 == 1) uneven = true;
    spaces = (length - int(s.size())) / 2;
    cout << "|";
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
    if(!cin){
        cin.ignore();
        cin.ignore(100,'\n');
        cin.clear();
    }
    cin >> input;
    while (cin.fail() || find(inputs.begin(), inputs.end(), input) == inputs.end()) {
        if (cin.eof() || input == 0) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore();
        cerr << "Not a valid input, please input one of the shown options: ";
        cin >> input;
    }
    cin.ignore(100, '\n');
    return input;
}

void Menu::MainMenu() {
    printTitle();
    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) Graph Information\n";
    cout << "(2) \n";
    cout << "(3) \n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            clearScreen();
            InfoMenu();
        case 2:
            clearScreen();
            
        case 3:
            clearScreen();

        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::InfoMenu() {
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
            clearScreen();
            GraphNodes();
        case 2:
            clearScreen();
            NodeEdges();
        case 3:
            clearScreen();
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::GraphNodes() {
    printTitle();
    cout << "\n";
    cout << "\t\tChoose a graph\n";
    cout << "(1) The 1st Real Graph\n";
    cout << "(2) The 2nd Real Graph\n";
    cout << "(3) The 3rd Real Graph\n";
    cout << "(4) The 1st Toy Graph\n";
    cout << "(5) The 2nd Toy Graph\n";
    cout << "(6) The 3rd Toy Graph\n";
    cout << "(7) Go back to the Graph Information Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4, 5, 6, 7});
    switch (input) {
        case 1:
            if (!data.getGraph1().getNodes().empty()) {
                cout << "\nDue to the number of nodes of this graph, choose the amout of entries about to be shown to you from 1 to " +
                        to_string(data.getGraph1().getNodes().size()) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 1; i <= data.getGraph1().getNodes().size(); i++) inputs.push_back(i);
                int size = getUserInput(inputs);
                cout << "\n\n";
                for (int i = 0; i < 56; i++) cout << "-";
                cout << "\n";
                Print("Node Id", 10);
                Print("Longitude", 21);
                Print("Latitude", 21);
                cout << "|\n";
                for (int i = 0; i < 56; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph1().getNodes().at(i)->Id), 10);
                    cout << "| " << fixed << setprecision(15) << data.getGraph1().getNodes().at(i)->longitude << " ";
                    cout << "| " << fixed << setprecision(15) << data.getGraph1().getNodes().at(i)->latitude << " ";
                    cout << "|\n";
                }
                for (int i = 0; i < 56; ++i) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                GraphNodes();
            }
        case 2:
            if (!data.getGraph2().getNodes().empty()) {
                cout << "\nDue to the number of nodes of this graph, choose the amout of entries about to be shown to you from 1 to " +
                        to_string(data.getGraph2().getNodes().size()) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 1; i <= data.getGraph2().getNodes().size(); i++) inputs.push_back(i);
                int size = getUserInput(inputs);
                cout << "\n\n";
                for (int i = 0; i < 56; i++) cout << "-";
                cout << "\n";
                Print("Node Id", 10);
                Print("Longitude", 21);
                Print("Latitude", 21);
                cout << "|\n";
                for (int i = 0; i < 56; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph2().getNodes().at(i)->Id), 10);
                    cout << "| " << fixed << setprecision(15) << data.getGraph2().getNodes().at(i)->longitude << " ";
                    cout << "| " << fixed << setprecision(15) << data.getGraph2().getNodes().at(i)->latitude << " ";
                    cout << "|\n";
                }
                for (int i = 0; i < 56; ++i) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                GraphNodes();
            }
        case 3:
            if (!data.getGraph3().getNodes().empty()) {
                cout << "\nDue to the number of nodes of this graph, choose the amout of entries about to be shown to you from 1 to " +
                        to_string(data.getGraph3().getNodes().size()) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 1; i <= data.getGraph3().getNodes().size(); i++) inputs.push_back(i);
                int size = getUserInput(inputs);
                cout << "\n\n";
                for (int i = 0; i < 56; i++) cout << "-";
                cout << "\n";
                Print("Node Id", 10);
                Print("Longitude", 21);
                Print("Latitude", 21);
                cout << "|\n";
                for (int i = 0; i < 56; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph3().getNodes().at(i)->Id), 10);
                    cout << "| " << fixed << setprecision(15) << data.getGraph3().getNodes().at(i)->longitude << " ";
                    cout << "| " << fixed << setprecision(15) << data.getGraph3().getNodes().at(i)->latitude << " ";
                    cout << "|\n";
                }
                for (int i = 0; i < 56; ++i) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                GraphNodes();
            }
        case 4:
            cout << "\n\n";
            for (int i = 0; i < 12; i++) cout << "-";
            cout << "\n";
            Print("Node Id", 10);
            cout << "|\n";
            for (int i = 0; i < 12; i++) cout << "-";
            cout << "\n";
            for (int i = 0; i < data.getToyGraph1().getNodes().size(); ++i) {
                Print(to_string(data.getToyGraph1().getNodes().at(i)->Id), 10);
                cout << "|\n";
            }
            for (int i = 0; i < 12; ++i) cout << "-";
            cout << "\n\n";
            cout << "Press 7 to continue\n";
            getUserInput({7});
            GraphNodes();
        case 5:
            cout << "\n\n";
            for (int i = 0; i < 12; i++) cout << "-";
            cout << "\n";
            Print("Node Id", 10);
            cout << "|\n";
            for (int i = 0; i < 12; i++) cout << "-";
            cout << "\n";
            for (int i = 0; i < data.getToyGraph2().getNodes().size(); ++i) {
                Print(to_string(data.getToyGraph2().getNodes().at(i)->Id), 10);
                cout << "|\n";
            }
            for (int i = 0; i < 12; ++i) cout << "-";
            cout << "\n\n";
            cout << "Press 7 to continue\n";
            getUserInput({7});
            GraphNodes();
        case 6:
            cout << "\n\n";
            for (int i = 0; i < 23; i++) cout << "-";
            cout << "\n";
            Print("Node Id", 9);
            Print("Node Name", 11);
            cout << "|\n";
            for (int i = 0; i < 23; i++) cout << "-";
            cout << "\n";
            for (int i = 0; i < data.getToyGraph3().getNodes().size(); ++i) {
                Print(to_string(data.getToyGraph3().getNodes().at(i)->Id), 9);
                Print(data.getToyGraph3().getNodes().at(i)->name, 11);
                cout << "|\n";
            }
            for (int i = 0; i < 23; i++) cout << "-";
            cout << "\n\n";
            cout << "Press 7 to continue\n";
            getUserInput({7});
            GraphNodes();
        case 7:
            clearScreen();
            InfoMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::NodeEdges() {
    printTitle();
    cout << "\n";
    cout << "\t\tChoose a graph\n";
    cout << "(1) The 1st Real Graph\n";
    cout << "(2) The 2nd Real Graph\n";
    cout << "(3) The 3rd Real Graph\n";
    cout << "(4) The 1st Toy Graph\n";
    cout << "(5) The 2nd Toy Graph\n";
    cout << "(6) The 3rd Toy Graph\n";
    cout << "(7) Go back to the Graph Information Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4, 5, 6, 7});
    switch (input) {
        case 1:
            if (!data.getGraph1().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getGraph1().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getGraph1().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                int size = 100;
                if (data.getGraph1().getEdges(Id).size() > 100) {
                    vector<int> inputs1;
                    cout << "\nDue to the number of edges of this node, choose the amout of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph1().getEdges(Id).size()) + "\n" + " > ";
                    for (int i = 1; i <= data.getGraph1().getEdges(Id).size(); i++) inputs1.push_back(i);
                    size = getUserInput(inputs1);
                }
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Distance", 10);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph1().getEdges(Id).at(i)->origin), 8);
                    Print(to_string(data.getGraph1().getEdges(Id).at(i)->dest), 13);
                    Print(data.getGraph1().getEdges(Id).at(i)->distanceStr, 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                NodeEdges();
            }
        case 2:
            if (!data.getGraph2().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getGraph2().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getGraph2().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                int size = 100;
                if (data.getGraph2().getEdges(Id).size() > 100) {
                    vector<int> inputs1;
                    cout << "\nDue to the number of edges of this node, choose the amout of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph2().getEdges(Id).size()) + "\n" + " > ";
                    for (int i = 1; i <= data.getGraph2().getEdges(Id).size(); i++) inputs1.push_back(i);
                    size = getUserInput(inputs1);
                }
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Distance", 10);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph2().getEdges(Id).at(i)->origin), 8);
                    Print(to_string(data.getGraph2().getEdges(Id).at(i)->dest), 13);
                    Print(data.getGraph2().getEdges(Id).at(i)->distanceStr, 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                NodeEdges();
            }
        case 3:
            if (!data.getGraph3().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getGraph3().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getGraph3().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                int size = 100;
                if (data.getGraph3().getEdges(Id).size() > 100) {
                    vector<int> inputs1;
                    cout << "\nDue to the number of edges of this node, choose the amout of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph3().getEdges(Id).size()) + "\n" + " > ";
                    for (int i = 1; i <= data.getGraph3().getEdges(Id).size(); i++) inputs1.push_back(i);
                    size = getUserInput(inputs1);
                }
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Distance", 10);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph3().getEdges(Id).at(i)->origin), 8);
                    Print(to_string(data.getGraph3().getEdges(Id).at(i)->dest), 13);
                    Print(data.getGraph3().getEdges(Id).at(i)->distanceStr, 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                NodeEdges();
            }
        case 4:
            if (!data.getToyGraph1().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getToyGraph1().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getToyGraph1().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Distance", 10);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < data.getToyGraph1().getEdges(Id).size(); i++) {
                    Print(to_string(data.getToyGraph1().getEdges(Id).at(i)->origin), 8);
                    Print(to_string(data.getToyGraph1().getEdges(Id).at(i)->dest), 13);
                    Print(data.getToyGraph1().getEdges(Id).at(i)->distanceStr, 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                NodeEdges();
            }
        case 5:
            if (!data.getToyGraph2().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getToyGraph2().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getToyGraph2().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Distance", 10);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < data.getToyGraph2().getEdges(Id).size(); i++) {
                    Print(to_string(data.getToyGraph2().getEdges(Id).at(i)->origin), 8);
                    Print(to_string(data.getToyGraph2().getEdges(Id).at(i)->dest), 13);
                    Print(data.getToyGraph2().getEdges(Id).at(i)->distanceStr, 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                NodeEdges();
            }
        case 6:
            if (!data.getToyGraph3().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getToyGraph3().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getToyGraph3().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8);
                Print("Destination", 13);
                Print("Distance", 10);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < data.getToyGraph3().getEdges(Id).size(); i++) {
                    Print(to_string(data.getToyGraph3().getEdges(Id).at(i)->origin), 8);
                    Print(to_string(data.getToyGraph3().getEdges(Id).at(i)->dest), 13);
                    Print(data.getToyGraph3().getEdges(Id).at(i)->distanceStr, 10);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n\n";
                cout << "Press 7 to continue\n";
                getUserInput({7});
                NodeEdges();
            }
        case 7:
            clearScreen();
            InfoMenu();
        case 0:
            exit(0);
        default:
            break;
    }
}
