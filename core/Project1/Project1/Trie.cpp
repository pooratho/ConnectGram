#include "Trie.h"

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    deleteNode(root);
}

void Trie::deleteNode(TrieNode* node) {
    for (auto& [ch, child] : node->children)
        deleteNode(child);
    delete node;
}

void Trie::insert(const string& word) {
    TrieNode* node = root;
    for (char ch : word) {
        if (!node->children.count(ch))
            node->children[ch] = new TrieNode();
        node = node->children[ch];
    }
    node->isEndOfWord = true;
}

vector<string> Trie::searchByPrefix(const string& prefix) {
    TrieNode* node = root;
    vector<string> results;
    for (char ch : prefix) {
        if (!node->children.count(ch))
            return results;
        node = node->children[ch];
    }

    dfs(node, prefix, results);
    return results;
}

void Trie::dfs(TrieNode* node, string prefix, vector<string>& results) {
    if (node->isEndOfWord)
        results.push_back(prefix);
    for (auto& [ch, child] : node->children)
        dfs(child, prefix + ch, results);
}
