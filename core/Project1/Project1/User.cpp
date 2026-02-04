#include "User.h"
#include <iostream>
#include <functional>

using namespace std;

User::User(const string& uname, const string& pwd)
    : username(uname), followersCount(0)
{
    setPassword(pwd);
}

void User::setPassword(const string& pwd) {
    hash<string> hasher;
    password = to_string(hasher(pwd));
}

bool User::checkPassword(const string& pwd) const {
    hash<string> hasher;
    return password == to_string(hasher(pwd));
}

void User::follow(const string& other) {
    following.insert(other);
}

void User::unfollow(const string& other) {
    following.erase(other);
}

void User::addFollower() { 
    followersCount++; 
}

void User::removeFollower() {
    if (followersCount > 0) followersCount--;
}

int User::getFollowersCount() const {
    return followersCount; 
}

void User::addSearchHistory(const string& term) {
    if (searchHistory.size() == 5) searchHistory.pop_front();
    searchHistory.push_back(term);
}

void User::showSearchHistory() const {
    cout << "Search History for " << username << ": ";
    for (const auto& term : searchHistory)
        cout << term << " ";
    cout << endl;
}

void User::display() const {
    cout << "Username: " << username << endl;
    cout << "Followers: " << followersCount << endl;
    cout << "Following: ";
    for (const auto& f : following) cout << f << " ";
    cout << endl;
    cout << "Search History: ";
    for (const auto& s : searchHistory) cout << s << " ";
    cout << endl;
}
