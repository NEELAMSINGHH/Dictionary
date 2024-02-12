#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <random>
#include <ctime>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    string definition;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    unordered_set<string> recentSearchCache;
    queue<string> recentSearchQueue;

    void addToRecentSearchCache(const string& word) {
        if (recentSearchCache.size() >= 10) {
            string oldestWord = recentSearchQueue.front();
            recentSearchQueue.pop();
            recentSearchCache.erase(oldestWord);
        }
        recentSearchQueue.push(word);
        recentSearchCache.insert(word);
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Function to insert a word and its definition into the trie
    void insert(const string& word, const string& definition) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
        current->definition = definition;
    }

    // Function to search for the definition of a word in the trie
    string search(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return "Word not found in dictionary.";
            }
            current = current->children[ch];
        }
        if (current->isEndOfWord) {
            addToRecentSearchCache(word);
            return current->definition;
        } else {
            return "Word not found in dictionary.";
        }
    }

    // Function to get a random word from the trie
    string getRandomWord() {
        if (recentSearchCache.size() == 0) {
            return "No recent searches available.";
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, recentSearchQueue.size() - 1);

        int randIndex = dis(gen);
        queue<string> tempQueue = recentSearchQueue;
        for (int i = 0; i < randIndex; ++i) {
            tempQueue.pop();
        }
        return tempQueue.front();
    }

    // Function to access recent searches
    queue<string> getRecentSearches() const {
        return recentSearchQueue;
    }
};

int main() {
    Trie dictionary;

    // Adding some words and their definitions
    dictionary.insert("apple", "A fruit that grows on trees and is typically red, yellow, or green.");
    dictionary.insert("banana", "A long curved fruit that grows in clusters and has soft pulpy flesh and yellow skin when ripe.");
    dictionary.insert("cat", "A small domesticated carnivorous mammal with soft fur, a short snout, and retractile claws.");

    while (true) {
        cout << "\nWordWeb Menu:" << endl;
        cout << "1. Search for a word" << endl;
        cout << "2. Get word of the day" << endl;
        cout << "3. Recent searches" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                string word;
                cout << "Enter the word to search: ";
                cin >> word;
                cout << "Definition: " << dictionary.search(word) << endl;
                break;
            }
            case 2: {
                cout << "Word of the day: " << dictionary.getRandomWord() << endl;
                break;
            }
            case 3: {
                cout << "Recent searches:" << endl;
                queue<string> recentSearches = dictionary.getRecentSearches();
                while (!recentSearches.empty()) {
                    cout << recentSearches.front() << endl;
                    recentSearches.pop();
                }
                break;
            }
            case 4: {
                cout << "Exiting..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

    return 0;
}
