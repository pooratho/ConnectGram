#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <unordered_map>
#include <vector>

#include "User.h"
#include "Trie.h"

using namespace std;

class UserManager {
private:
    unordered_map<string, User*> users;
    Trie userTrie;

public:
    UserManager() = default;
    ~UserManager();

    bool signup(const string& username, const string& password);

    User* login(const string& username, const string& password);

    vector<string> searchUser(const string& prefix);

    User* getUser(const string& username);
};

#endif