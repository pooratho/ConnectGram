#include "User.h"
#include "Post.h"
#include <iostream>
#include <functional>

using namespace std;

class Post;

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

void User::addFollower() { 
    followersCount++; 
}

void User::removeFollower() {
    if (followersCount > 0) followersCount--;
}

int User::getFollowersCount() const {
    return followersCount; 
}

const set<User*>& User::getFollowings() const {
    return following;
}

void User::addFollowing(User* user) {
    if (user && user != this)
        following.insert(user);
}

void User::removeFollowing(User* user) {
    if (user)
        following.erase(user);
}

void User::addPost(Post* post) {
    if (post) posts.push_back(post);
}

const vector<Post*>& User::getPosts() const {
    return posts;
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
    for (const auto& u : following)
        cout << u->username << " ";
    cout << endl;
}

