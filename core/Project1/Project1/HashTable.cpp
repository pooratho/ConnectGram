#include "HashTable.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int size) : capacity(size) {
    buckets.resize(capacity);
}

int HashTable::hash(const string& key) const {
    unsigned long hashValue = 5381;
    for (char c : key) {
        hashValue = ((hashValue << 5) + hashValue) + c;
    }
    return hashValue % capacity;
}

void HashTable::insert(const string& hashtag, Post* post) {
    if (!post) return;

    int index = hash(hashtag);

    for (auto& entry : buckets[index]) {
        if (entry.hashtag == hashtag) {
            entry.posts.push_back(post);
            return;
        }
    }

    Entry newEntry;
    newEntry.hashtag = hashtag;
    newEntry.posts.push_back(post);
    buckets[index].push_back(newEntry);
}

vector<Post*> HashTable::get(const string& hashtag) const {
    int index = hash(hashtag);

    for (const auto& entry : buckets[index]) {
        if (entry.hashtag == hashtag) {
            return entry.posts;
        }
    }

    return {};
}

bool HashTable::contains(const string& hashtag) const {
    int index = hash(hashtag);

    for (const auto& entry : buckets[index]) {
        if (entry.hashtag == hashtag)
            return true;
    }
    return false;
}

void HashTable::remove(const std::string& hashtag, Post* post) {
    if (!post) return;

    int index = hash(hashtag);

    for (auto it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        if (it->hashtag == hashtag) {
            auto& postsVec = it->posts;
            postsVec.erase(std::remove(postsVec.begin(), postsVec.end(), post), postsVec.end());

            if (postsVec.empty()) {
                buckets[index].erase(it);
            }

            return;
        }
    }
}

