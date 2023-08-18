// Using 2 libraries and linking 2 implementation files
#include <iostream>
#include <unordered_map>
#include "priorityQ.cpp"
#include "priorityQ.h"

using namespace std; // Using namespace standard

// Function to convert a string to lowercase
string toLowercase(const string& str) {
    string lower; // String lower to return the lowercase string
    for (char c : str) { // For loop used to lowercase each letter of the string
        lower += tolower(c);
    }
    return lower; // Return the lowercase string
}

int main() { // Main function for the Mario Kart simulation
    priorityQ <string, double> racers; //priorityQ object to store the racers

    // unordered map used for bool flags to check for if racers were finished
    // and if the racers were already updated in the same interval
    unordered_map<string, bool> finishedRacers;
    unordered_map<string, bool> updatedInInterval;

    int intervalCounter = 1; // Setting the interval counter to 1
    int totalRacers = 0; // Variable to keep track of the total number of racers

    string racerName = ""; // racerName used to read in the racers name from input
    double racerDistance = 0.0; // racerDistance used to read in the distance of the racer from input
    int rank = 1; // Setting the rank to 1 for first place

    while (true) { // While cin is good
        cin >> racerName; // Read in the racers name
        if (racerName == "END") { // You keep reading until you hit "END"
            break; // Break free from the loop
        }

        string lowerName = toLowercase(racerName); // lowercases the racers name and stores it into lowerName
        racers.push_back(lowerName, 50.0); // inserts a racer object to the back of heapArray
        finishedRacers[lowerName] = false; // Sets the map to false
        updatedInInterval[lowerName] = false; // Sets the map to false
        totalRacers++; // Increment the total number of racers being read in
    }

    while (true) { // While cin is good
        cout << "\nInterval " << intervalCounter << endl << endl; // Output the interval

        for (auto& entry : updatedInInterval) { // Reset racersInCurrentInterval for the new interval
            entry.second = false; // Set their updatedInInterval map to false
        }

        bool allRacersUpdated = true; // Set all allRacersUpdated by default to true
        if (allRacersUpdated) { // If allRacersUpdated is true
            // Checks if their distance is less than or = to 0 AND if the racers aren't empty
            while (!racers.isEmpty() && racers.get_front_priority() <= 0) {
                --totalRacers; // Decrement the amount of total racers
                string racerDone = racers.get_front_key(); // sets racers get front key function to racerDone
                racers.pop_front(); // calls pop front function
                finishedRacers[racerDone] = true; // Sets the map to true
                cout << rank << " " << racerDone << endl << endl; // Outputs the racers rank and name
                rank++; // Increment the next rank number
            }

            if (racers.isEmpty()) { // If all racers are empty
                break; // Break free from the loop
            }
        }
        int numUpdatedRacers = totalRacers; // Track the number of updated racers in the current interval

        while (true) { // While cin is good
            cin >> racerName; // Read in the racers name
            if (racerName == "DONE") { // If the read input is DONE
                break; // Break free from the loop
            }
            string lowerName = toLowercase(racerName); // Set the racers name to lowercase

            if (finishedRacers[lowerName]) { // If the racer was already read but finished the race
                cout << "Racer has already finished the race!\n" << endl; // Output this
                continue; // Continue reading the next racer
            }

            if (updatedInInterval[lowerName]) { // If the racer was updated in the same interval
                cout << "Already updated " << racerName << " in this interval!\n" << endl; // Output this
                continue; // Continue reading the next racer
            }

            cin >> racerDistance; // Read in the racers distance

            // Call decrease_priority and set the name and distance of that racer
            racers.decrease_priority(lowerName, racerDistance);

            cout << "Updating " << racerName << endl; // Output that you updated the racer
            updatedInInterval[lowerName] = true; // Set the map to true
            numUpdatedRacers--; // Decrement the number of updated racers

            if (numUpdatedRacers == 0) { // If number of updated racers is equal to 0
                break; // Move to the next interval if all racers are updated
            }

            allRacersUpdated = false; // Set allRacersUpdated to false
        }

        intervalCounter++; // Increment the interval counter
    }

    return 0; // End of program
}