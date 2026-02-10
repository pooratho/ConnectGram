#include "UserManager.h"
#include "SearchManager.h"
#include <iostream>

using namespace std;

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

bool UserManager::follow(User* from, const string& targetUsername) {
    if (!from) {
        cout << "Error: No user logged in.\n";
        return false;
    }

    User* target = getUser(targetUsername);
    if (!target) {
        cout << "Error: Target user not found.\n";
        return false;
    }

    if (from->username == targetUsername) {
        cout << "Error: You cannot follow yourself.\n";
        return false;
    }

    if (from->getFollowings().count(target)) {
        cout << "Error: Already following this user.\n";
        return false;
    }

    from->addFollowing(target);
    target->addFollower();

    return true;
}

bool UserManager::unfollow(User* from, const string& targetUsername) {
    if (!from) {
        cout << "Error: No user logged in.\n";
        return false;
    }

    User* target = getUser(targetUsername);
    if (!target) {
        cout << "Error: Target user not found.\n";
        return false;
    }

    if (!from->getFollowings().count(target)) {
        cout << "Error: You are not following this user.\n";
        return false;
    }

    from->removeFollowing(target);
    target->removeFollower();

    return true;
}

vector<string> UserManager::getSmartSuggestions(const string& target, int threshold) const {
    vector<string> suggestions;

    for (const auto& [username, userPtr] : users) {
        if (username.size() != target.size()) continue; 

        int dist = SearchManager::calculateHamming(target, username);
        if (dist <= threshold)
            suggestions.push_back(username);
    }

    return suggestions;
}
