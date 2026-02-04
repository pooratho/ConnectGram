#include "UserManager.h"
#include <iostream>

UserManager::~UserManager() {
    for (auto& pair : users) {
        delete pair.second;
    }
}

bool UserManager::signup(const string& username, const string& password) {
    if (users.count(username)) {
        cout << "Error: Username already exists.\n";
        return false;
    }

    User* newUser = new User(username, password);

    users[username] = newUser;

    userTrie.insert(username);

    return true;
}

User* UserManager::login(const string& username, const string& password) {
    if (!users.count(username)) {
        cout << "Error: User not found.\n";
        return nullptr;
    }

    User* user = users[username];
    if (!user->checkPassword(password)) {
        cout << "Error: Incorrect password.\n";
        return nullptr;
    }

    return user;
}

vector<string> UserManager::searchUser(const string& prefix) {
    return userTrie.searchByPrefix(prefix);
}

User* UserManager::getUser(const string& username) {
    if (!users.count(username))
        return nullptr;
    return users[username];
}
