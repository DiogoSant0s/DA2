#include "Menu.h"

Menu::Menu() : data(Data()) {
    MainMenu();
}

void Menu::printTitle() {
    cout << R"(
_____________________________________________________________________________________________
____ ____ ___  _   _       _  ____ _  _      _  _ ____ _  _ ____ ____ ____ _  _ ____ _  _ ___
|__/ |__|  |   |    \  /\  /  |__|  \/       |\/| |__| |\ | |__| | _  |___ |\/| |___ |\ |  |
|  \ |  | _|_  |___  \/  \/   |  |  ||       |  | |  | | \| |  | |__] |___ |  | |___ | \|  |
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

string Menu::getUserTextInput() {
    string input;
    getline(cin, input);
    if (cin.fail()) cout << "Something went wrong here";
    while (cin.fail() || input.length() == 0) {
        if (cin.eof()) {
            cout << "\nExiting\n\n";
            exit(0);
        }
        cin.clear();
        cin.ignore(100, '\n');
        cerr << "Not a valid input, please try again: ";
        getline(cin, input);
    }
    return input;
}

void Menu::exitMenu() {
    data.deleteData();
    exit(0);
}

void Menu::MainMenu() {
    printTitle();
    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) \n";
    cout << "(2) \n";
    cout << "(3) \n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            clearScreen();

        case 2:
            clearScreen();

        case 3:
            clearScreen();

        case 0:
            exitMenu();
        default:
            break;
    }
}
