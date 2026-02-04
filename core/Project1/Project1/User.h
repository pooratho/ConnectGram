#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <deque>
using namespace std;

class User {
private:
    string password;
    int followersCount;

public:
    string username;
    set<string> following;
    deque<string> searchHistory;


    User(const string& uname, const string& pwd);

    void setPassword(const string& pwd);
    bool checkPassword(const string& pwd) const;

    void follow(const string& other);
    void unfollow(const string& other);
    void addFollower();
    void removeFollower();
    int getFollowersCount() const;

    void addSearchHistory(const string& term);
    void showSearchHistory() const;

    void display() const;
};

#endif
