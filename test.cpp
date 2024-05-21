#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

void generateDictionary(const map<string, string>& dictionary) {
    ofstream file("dictionary.txt");
    if (file.is_open()) {
        for (const auto& pair : dictionary) {
            file << pair.first << ":" << pair.second << endl;
        }
        file.close();
        cout << "Dictionary file generated successfully!\n";
    } else {
        cout << "Unable to open file!\n";
    }
}

void addWordMeaning(map<string, string>& dictionary) {
    string word, meaning;
    cout << "Enter word: ";
    cin >> word;
    cout << "Enter meaning: ";
    cin.ignore();
    getline(cin, meaning);

    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        cout << "Word already exists in the dictionary. Updating meaning...\n";
        it->second = meaning;
    } else {
        dictionary[word] = meaning;
    }
    
    generateDictionary(dictionary);
}

void searchMeaning(const map<string, string>& dictionary) {
    string word;
    cout << "Enter word to search meaning for: ";
    cin >> word;
    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        cout << "Meaning: " << it->second << endl;
    } else {
        cout << "Word not found in the dictionary!\n";
    }
}

void removeWord(map<string, string>& dictionary) {
    string word;
    cout << "Enter word to remove: ";
    cin >> word;
    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        dictionary.erase(it);
        generateDictionary(dictionary);
        cout << "Word removed successfully!\n";
    } else {
        cout << "Word not found in the dictionary!\n";
    }
}

int getChoice() {
    int choice;
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > 4) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice! Please enter a number between 1 and 4: ";
    }
    return choice;
}

int main() {
    map<string, string> dictionary;
    
    ifstream file("dictionary.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(":");
            if (pos != string::npos) {
                string word = line.substr(0, pos);
                string meaning = line.substr(pos + 1);
                dictionary[word] = meaning;
            }
        }
        file.close();
    } else {
        cout << "No existing dictionary file found.\n";
    }

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add word and meaning\n";
        cout << "2. Search for meaning\n";
        cout << "3. Remove word\n";
        cout << "4. Exit\n";

        choice = getChoice();

        switch (choice) {
            case 1:
                addWordMeaning(dictionary);
                break;
            case 2:
                searchMeaning(dictionary);
                break;
            case 3:
                removeWord(dictionary);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}