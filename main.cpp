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
using namespace std;

void runSimulation(map<string, array<list<string>, 3>>& house, const int steps) {
    for (int i{1}; i <= steps; ++i) {
        cout << "Time Step " << i << endl;

        for (auto& room : house)
            cout << "Room: " << room.first << '\n';
    }
}

int main() {
    // FIXME: add const for time_period and categ
    map<string, array<list<string>, 3>> house{};

    house["Basement"][0].push_back("Ghost");

    for (const auto& room : house)
        cout << room.first << " loaded\n";
    cout << "----------------\n";

    runSimulation(house, 25);

    return 0;
}