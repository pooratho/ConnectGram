#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <deque>

using namespace std;

class User {
private:
    string password;
    int followersCount = 0;
    deque<string> searchHistory;

public:
    string username;

    set<User*> following;

    User(const string& uname, const string& pwd);

    void setPassword(const string& pwd);
    bool checkPassword(const string& pwd) const;

    void addFollower();
    void removeFollower();
    int getFollowersCount() const;

    void addSearchHistory(const string& term);
    void showSearchHistory() const;

    void display() const;
};

#endif
