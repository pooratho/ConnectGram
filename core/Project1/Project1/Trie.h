#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord = false;
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& results);

    void deleteNode(TrieNode* node);

public:
    Trie();
    ~Trie();

    void insert(const string& word);
    vector<string> searchByPrefix(const string& prefix);
};

#endif