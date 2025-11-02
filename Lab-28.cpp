#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <vector>
#include <algorithm>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;

        // milestone 1: sort by age
        case 5: {
            int minAge;
            cout << "Sort goats older than age: "; cin >> minAge;
            list<Goat> subList;
            for (auto &g : trip) if (g.get_age() > minAge) subList.push_back(g);
            subList.sort([](const Goat &a, const Goat &b){ return a.get_age() < b.get_age(); });
            cout << "Goats older than " << minAge << " sorted by age:\n";
            display_trip(subList);
            break;
        }

        // milestone 2: find oldest goat
        case 6: {
            auto it = max_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b){ return a.get_age() < b.get_age(); });
            cout << "Oldest goat: " << it->get_name() << 
        }

        // milestone 3: remove young goats
        case 7: {
            int minAge;
            cout << "Remove goats younger than: "; cin >> minAge;
            trip.remove_if([&](const Goat g){ return g.get_age() < minAge; });
            cout << "Young goats removed.\n";
            display_trip(trip);
            break;
        }


        // milestone 4: count goats by color
        case 8: {
            string colorInput;
            cout << "Enter color to count: "; cin >> colorInput;
            int count = count_if(trip.begin(), trip.end(), [&](const Goat &g){ return g.get_color() == colorInput; });
            cout << "Number of goats with color " << colorInput << ": " << count << endl;
            break;
        }

        // milestone 5: search for a goat by name
        case 9:


        // milestone 6: reverse list
        case 10:


        // milestone 7: copy to vector
        case 11: {
            vector<Goat> goatVector(trip.begin(), trip.end());
            cout << "Goat copied to vector. Vector contents:\n";
            int i = 1;
            for (auto &g : goatVector)
                cout << "\t[" << i++ << "] " << g.get_name() 
                     << " (" << g.get_age() << ", " << g.get_color() << ")\n";
            break;
        }


        // milestone 8: celebrate a birthday
        case 12:


        default:
                cout << "Invalid selection.\n";
                break;

        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "[5] Sort goats by age\n";
    cout << "[6] Find oldest goat\n";
    cout << "[7] Remove young goats\n";
    cout << "[8] Count goats by color\n";
    cout << "[9] Search for a goat by name\n";
    cout << "[10] Reverse goat list\n";
    cout << "[11] Copy goats to a vector\n";
    cout << "[12] Celebrate a birthday\n";
    cout << "Choice --> ";

    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}