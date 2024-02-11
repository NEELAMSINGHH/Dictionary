#include <iostream>
#include <unordered_map>
#include <string>

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
            return current->definition;
        } else {
            return "Word not found in dictionary.";
        }
    }
};

int main() {
    Trie dictionary;

    // Adding some words and their definitions
    dictionary.insert("apple", "A fruit that grows on trees and is typically red, yellow, or green.");
    dictionary.insert("banana", "A long curved fruit that grows in clusters and has soft pulpy flesh and yellow skin when ripe.");
    dictionary.insert("cat", "A small domesticated carnivorous mammal with soft fur, a short snout, and retractile claws.");

    // Searching for definitions
    cout << "Definition of 'apple': " << dictionary.search("apple") << endl;
    cout << "Definition of 'banana': " << dictionary.search("banana") << endl;
    cout << "Definition of 'dog': " << dictionary.search("dog") << endl;

    return 0;
}
