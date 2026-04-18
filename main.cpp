// ------PSEUDOCODE------
// Include libraries
// Define constants if needed

// Function: runSimulation
// Inputs: house map and number of time steps

// main function

    // Create a map called house

    // Open the input file
        // If the file does not open, print an error and stop

    // Read each line from the file
        // Get room name, category, and value
        // If category is manifestation, add to list 0
        // If category is atmospheric change, add to list 1
        // If category is disturbance event, add to list 2

    // Print the starting state of the house

    // Call runSimulation with 25 time steps

// runSimulation function

    // Loop for each time step (at least 25 times)
        // Go through each room

            // add or remove a manifestation

            // add or remove an atmospheric change

            // add trigger a disturbance event

        // Print what changed in this step

    // Print the final state


// ------ACTUAL CODE------
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

constexpr int MAX_ELEMENT{3};
constexpr int MAX_STEPS{25};

constexpr int MANIFESTATIONS{0};
constexpr int ATMOSPHERIC{1};
constexpr int DISTURBANCE{2};

constexpr size_t MAX_DISTURBANCES{5};

void printHouse(map<string, array<list<string>, MAX_ELEMENT>>& house);

void runSimulation(map<string, array<list<string>, MAX_ELEMENT>>& house, int steps);

string randDisturbance(list<string>& distList);


int main() {
    srand(time(nullptr));
    map<string, array<list<string>, MAX_ELEMENT>> house{};

    // open data
    fstream data{"data.txt"};
    if (!data) {
        cerr << "File not found\n";
        return 1;
    }

    string inputLine{};

    while (getline(data, inputLine)) { //
        size_t pos1{inputLine.find(',')}; // starts from 0
        size_t pos2{inputLine.find(',', pos1 + 1)};

        string room{inputLine.substr(0, pos1)};
        string category{inputLine.substr(pos1 + 1, pos2 - (pos1 + 1))};
                                                     // final - initial (position)
        string value{inputLine.substr(pos2 + 1)};

        int index{};
        if (category == "manifestation")
            index = MANIFESTATIONS;
        else if (category == "atmospheric")
            index = ATMOSPHERIC;
        else if (category == "disturbance")
            index = DISTURBANCE;
        house[room][index].push_back(value);
    }

    cout << "Initial State:\n";
    printHouse(house);
    runSimulation(house, MAX_STEPS);

    return 0;
}

void printHouse(map<string, array<list<string>, MAX_ELEMENT>>& house) {
    for (auto& room : house) {
        cout << "Room: " << room.first << '\n';

        cout << "\tManifestations: ";
        for (auto& manif : room.second[MANIFESTATIONS]) {
            cout << manif << " ";
        }
        cout << '\n';

        cout << "\tAtmospheric: ";
        for (auto& atmo : room.second[ATMOSPHERIC]) {
            cout << atmo << " ";
        }
        cout << '\n';

        cout << "\tDisturbance: ";
        for (auto& dist : room.second[DISTURBANCE]) {
            cout << dist << " ";
        }
        cout << '\n';
        cout << "====================================\n";
    }
}

void runSimulation(map<string, array<list<string>, MAX_ELEMENT>>& house, const int steps) {
    map<string, array<list<string>, MAX_ELEMENT>> origHouse{house};
    for (int i{1}; i <= steps; ++i) {
        cout << "\nTime Step " << i << '\n';
        for (auto& room : house) { // remove manif
            if (!room.second[MANIFESTATIONS].empty()) {
                room.second[MANIFESTATIONS].pop_back();
                cout << "\tRemoved manifestation from " << room.first << '\n';
            } else {
                // cout << "\tNo manifestations in " << room.first << '\n';
            }

            if (!room.second[ATMOSPHERIC].empty()) {
                room.second[ATMOSPHERIC].pop_back();
            }

            // FIXME: using hardcoded disturbance, replace with var/event
            string newEvent{ randDisturbance(origHouse[room.first][DISTURBANCE]) };
            room.second[DISTURBANCE].push_back(newEvent);

            if (room.second[DISTURBANCE].size() > MAX_DISTURBANCES) {
                room.second[DISTURBANCE].pop_front();
            }

        }
    }
    printHouse(house);
}

string randDisturbance(list<string>& distList) {
    if (distList.empty())
        return "No disturbance";

    // for (auto& i : distList)
    //     distCollect.emplace_back(i);

    constexpr int rndMin{0};
    size_t rndIndex{ rndMin + rand() % (distList.size() - rndMin) }; // TODO: add rnd

    auto it{distList.begin()};
    for (int i{0}; i < rndIndex; ++i) {
        ++it;
    }

    return *it;
}