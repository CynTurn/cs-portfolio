#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

class GroceryTracker {
private:
    map<string, int> itemFrequency;
    string inputFileName;
    string backupFileName;

public:
    GroceryTracker(string inputFile) {
        inputFileName = inputFile;
        backupFileName = "frequency.dat";
    }

    void LoadDataFromFile() {
        ifstream inputFile(inputFileName);

        if (!inputFile.is_open()) {
            cout << "Error opening input file." << endl;
            return;
        }

        string item;
        while (inputFile >> item) {
            itemFrequency[item]++;
        }

        inputFile.close();
    }

    void CreateBackupFile() {
        ofstream outFile(backupFileName);

        for (auto const& pair : itemFrequency) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close();
    }

    int GetItemFrequency(string item) {
        if (itemFrequency.find(item) != itemFrequency.end()) {
            return itemFrequency[item];
        }
        return 0;
    }

    void PrintAllFrequencies() {
        for (auto const& pair : itemFrequency) {
            cout << setw(15) << left << pair.first
                << pair.second << endl;
        }
    }

    void PrintHistogram() {
        for (auto const& pair : itemFrequency) {
            cout << setw(15) << left << pair.first;

            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }

            cout << endl;
        }
    }
};

void DisplayMenu() {
    cout << "\nCorner Grocer Menu\n";
    cout << "-------------------\n";
    cout << "1. Search for item frequency\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display histogram\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt");

    tracker.LoadDataFromFile();
    tracker.CreateBackupFile();

    int choice;

    do {
        DisplayMenu();
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter 1-4: ";
            cin >> choice;
        }

        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item name: ";
            cin >> item;

            int frequency = tracker.GetItemFrequency(item);

            cout << item << " was purchased "
                << frequency << " time(s).\n";
            break;
        }
        case 2:
            tracker.PrintAllFrequencies();
            break;

        case 3:
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Exiting program. Goodbye!\n";
            break;
        }

    } while (choice != 4);

    return 0;
}
