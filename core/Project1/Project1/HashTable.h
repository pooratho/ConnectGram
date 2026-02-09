#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include "Post.h"

class HashTable {
private:
    struct Entry {
        std::string hashtag;
        std::vector<Post*> posts;
    };

    std::vector<std::vector<Entry>> buckets;
    int capacity;

    int hash(const std::string& key) const;

public:
    HashTable(int size = 101);

    void insert(const std::string& hashtag, Post* post);
    std::vector<Post*> get(const std::string& hashtag) const;
    bool contains(const std::string& hashtag) const;
};

#endif
