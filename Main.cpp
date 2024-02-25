/*
**
** Developer: Darrell Walker II
* 
** Date: 2024-02-24
* 
** Purpose: read a list of items from a file, track their frequencies, and provide functionality for querying, visualizing, and backing up this data.
**
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

class ItemTracker {
private:
    map<string, int> frequency; // Map to store item frequencies

public:
    // Constructor to initialize ItemTracker with data from file
    ItemTracker(const string& filename = "CS210_Project_Three_Input_File.txt") {
        ifstream infile(filename);
        if (!infile.is_open()) {
            cerr << "Error: Unable to open input file '" << filename << "'" << endl;
            // Handle the error (throw an exception, return, or exit)
            return;
        }

        string item;
        while (infile >> item) {
            frequency[item]++; // Increment frequency of item
        }
        infile.close(); // Close the file after reading
    }

    // Get frequency of a particular item
    int getFrequency(const string& item) const {
        auto it = frequency.find(item);
        return (it != frequency.end()) ? it->second : 0;
    }

    // Print list of items and their frequencies
    void printList() const {
        for (auto it = frequency.begin(); it != frequency.end(); ++it) {
            cout << it->first << " " << it->second << endl;
        }
    }

    // Print histogram of item frequencies
    void printHistogram() const {
        for (auto it = frequency.begin(); it != frequency.end(); ++it) {
            cout << it->first << " ";
            for (int i = 0; i < it->second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }

    // Backup data to a file
    void backupData() const {
        ofstream outfile("frequency.dat");
        for (auto it = frequency.begin(); it != frequency.end(); ++it) {
            outfile << it->first << " " << it->second << endl;
        }
    }
};

int main() {
    ItemTracker tracker;

    while (true) {
        cout << "Menu Options:" << endl;
        cout << "1. Look up item frequency" << endl;
        cout << "2. Print list of item frequencies" << endl;
        cout << "3. Print histogram of item frequencies" << endl;
        cout << "4. Exit program" << endl;

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item to look up frequency: ";
            cin >> item;
            cout << "Frequency of " << item << ": " << tracker.getFrequency(item) << endl;
            break;
        }
        case 2: {
            tracker.printList();
            tracker.backupData();
            break;
        }
        case 3: {
            tracker.printHistogram();
            tracker.backupData();
            break;
        }
        case 4: {
            tracker.backupData();
            return 0;
        }
        default: {
            cout << "Invalid choice, please try again." << endl;
            break;
        }
        }
    }

    return 0;
}



